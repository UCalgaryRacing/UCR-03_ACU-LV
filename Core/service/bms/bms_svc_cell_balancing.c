
/*
 * bms_svc_cell_balancing.c
 *
 * Accumulator Cell Balancing Service Module
 *
 * Acquires clean cell voltage readings from ADBMS. Decides which cells fall within the
 * parameters to discharge and requests ADBMS to toggle the discharge mosfets for those
 * particular cells.
 *
 * Will never discharge a cell that is below 2.75 volts.
 *
 * Only discharges for 15 seconds before allowing the cells to recover, take new readings
 * and begin the next discharge cycle.
 *
 * Currently discharges cells that are 100mV higher than the lowest cell. This threshold
 * will be changed to 10mV after further testing.
 *
 * Redundant safety mechanisms:
 *
 * ADBMS Thermal Shutdown at 150 degrees Celcius.
 * DCTO (discharge timer) cells are set to only ever discharge for 1 minute unless
 * an updated discharge command is sent.
 *
 *  Created on: Jul 18, 2026
 *      Author: SamT
 */

#include "bms_svc_cell_balancing.h"
#include "bms_svc_cell_voltage.h"
#include "bms_drv_adbms6830.h"
#include "cmsis_os2.h"
#include "cco_data.h"
#include "string.h"

/* Variables of interest declared here so they may be watched in debug live expressions view  */
static float highest_v = 0.0f;
static float lowest_v = 0.0f;
static float cell_deviation = 0.0f;
static int highest_slave = 0;
static int highest_cell = 0;
static int lowest_slave = 0;
static int lowest_cell = 0;

/* Balancing state machine typedefs */
typedef enum {
	BAL_STATE_START = 0,
	BAL_STATE_SETTLE_WAIT,
	BAL_STATE_ACTIVE_BALANCING,
	BAL_STATE_CYCLE_COMPLETE
} bal_state_t;

/**
 * @brief Main cell balancing logic to be called in task medium.
 *
 * Acquires clean cell voltage readings by pausing discharge during ADC conversions.
 *
 * Discharges cells in 15 second cycles, then waits 5 seconds for physical cell chemistry to
 * recover before taking new voltage readings and starting the next 15 second discharge cycle.
 *
 *
 * @param No parameters
 * @returns Nothing
 */

void cell_balance_init(void){
	uint8_t duration = cco_data_get_balance_duration();
	if (duration > 1 && duration < 60) {
		uint32_t time_to_balance_ms = HAL_GetTick() + (duration * 60 * 1000);
		while (HAL_GetTick() < time_to_balance_ms){
			bms_svc_balance();
		}
	}
}

void bms_svc_balance(void) {

    /* Trigger ADC conversions with discharging paused */
    adbms6830_start_cell_adc(false);

    /* Wait for conversions to complete ( 2ms to 8ms depending on filtering) */
    osDelay(10);

	/* Preserve state, timer, and targets across function calls */
	static bal_state_t state = BAL_STATE_START;
	static uint32_t timer = 0;


	float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC];

	/* Retrieve fresh cell voltages */
	bms_svc_acquire_all_cell_voltages(cell_voltages);

	switch (state) {
		case BAL_STATE_START:
			uint16_t clear_masks[ADBMS_NUM_SLAVES] = {0};
			adbms6830_bal_start_1min(clear_masks);

			/* Capture baseline time */
			timer = HAL_GetTick();
			state = BAL_STATE_SETTLE_WAIT;
			break;

		case BAL_STATE_SETTLE_WAIT:
			/* Non-blocking delay for 5 seconds to let cell chemistry recover */
			if (HAL_GetTick() - timer >= 15000) {

				/* Capture lowest and highest cell voltages */
				bms_svc_acquire_lowest_cell(cell_voltages, &lowest_v, &lowest_slave, &lowest_cell);
				bms_svc_acquire_highest_cell(cell_voltages, &highest_v, &highest_slave, &highest_cell);
				cell_deviation = highest_v - lowest_v;

				/* Prepare balancing masks */
				uint16_t masks[ADBMS_NUM_SLAVES] = {0};

				/* Identify high cells (cells that are 10mV higher than lowest V */
				for (int slave = 0; slave < ADBMS_NUM_SLAVES; slave++) {
					for (int cell = 0; cell < ADBMS_CELLS_PER_IC; cell ++){
						if (cell_voltages[slave][cell] > (2.75f)) {
							if (cell_voltages[slave][cell] > (lowest_v + 0.005f))
							masks[slave] |= (1U << cell); // Enable discharge switch for that cell
						}
					}
				}
				/* Build Tx data packet and send SPI write command */
				adbms6830_bal_start_1min(masks);

				/* Move to active state and reset timer for balancing duration */
				timer = HAL_GetTick();
				state = BAL_STATE_ACTIVE_BALANCING;
			}
			break;

		case BAL_STATE_ACTIVE_BALANCING:
			/* Balance for 15 seconds */
			if (HAL_GetTick() - timer >= 15000){
				state = BAL_STATE_CYCLE_COMPLETE;
			}
			break;

		case BAL_STATE_CYCLE_COMPLETE:
			/* Reset the state machine to start the next sequence */
			state = BAL_STATE_START;
			break;

		default:
			state = BAL_STATE_START;
			break;
	}
}

/**
 * @brief Called once cell balancing logic is done, acts as the interface between service
 * and driver layers to tell the ADBMS which cells should be discharged.
 *
 * @param masks		Array holding 2 bytes x 10 slaves. Bits set to 1 indicate a cell to be discharged
 *
 * @returns nothing
 */
void adbms6830_bal_start_1min(uint16_t *masks) {
	// Command to write configuration register group B
	uint16_t WRCFGB = 0x0024U;

	// Array to hold the 6 configuration bytes for each slave
	uint8_t tx_data[ADBMS_NUM_SLAVES][ADBMS_REG_GROUP_SIZE];
	for (int i = 0; i < ADBMS_NUM_SLAVES; i++) {
		/* Bytes 0 to 2: Safe defaults for Undervoltage and Overvoltage limits */
		tx_data[i][0] = 0x00; /* CFGBR0: VUV[7:0] */
		tx_data[i][1] = 0xF8; /* CFGBR1: VOV[3:0] (1111) | VUV[11:8] (1000) */
		tx_data[i][2] = 0x7F; /* CFGBR2: VOV[11:4] */

		/* Byte 3 (CFGBR3): Safety Discharge Timer Configuration
		 * DTMEN = 0, DTRNG = 0, DCTO = 1 (1 minute timeout) */
		tx_data[i][3] = 0x01;

		/* Bytes 4 & 5 (CFGBR4 & CFGBR5): Load 16-bit discharge switch (DCC) mask */
		tx_data[i][4] = (uint8_t)(masks[i] & 0xFF);        /* DCC[8:1] (Lower 8 cells) */
		tx_data[i][5] = (uint8_t)((masks[i] >> 8) & 0xFF); /* DCC[16:9] (Upper 8 cells) */
	}

	    /* Send the data table to all devices */
//	    adbms6830_write_register_group(WRCFGB, tx_data);
}

/**
 * @brief Finds the voltage and location of the lowest cell in the pack.
 *
 * @param cell_voltages     Array holding all 130 cell voltages, acquired from ADBMS
 * @param lowest_voltage		Actual lowest voltage value in volts
 * @param lowest_slave_idx		Slave that cell with lowest voltage is on
 * @param lowest_slave_cell		Cell with lowest voltage
 *
 * @returns Nothing
 */
void bms_svc_acquire_lowest_cell(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC],
		float *lowest_voltage,
		int *lowest_slave_idx,
		int *lowest_cell_idx) {


	float min_v = cell_voltages[0][0];

	int min_slave = 0;
	int min_cell = 0;

	for (int i = 0; i < ADBMS_NUM_SLAVES; i++) {
		for (int j = 0; j < ADBMS_CELLS_PER_IC; j++) {
			if (cell_voltages[i][j] < min_v) {
				min_v = cell_voltages[i][j];
				min_slave = i;
				min_cell = j;
			}
		}
	}

	*lowest_voltage = min_v;
	*lowest_slave_idx = min_slave;
	*lowest_cell_idx = min_cell;
}

/**
 * @brief Finds the voltage and location of the lowest cell in the pack.
 *
 * @param cell_voltages     Array holding all 130 cell voltages, acquired from ADBMS
 * @param highest_voltage		Actual highest voltage value in volts
 * @param highest_slave_idx		Slave that cell with highest voltage is on
 * @param highest_slave_cell		Cell with highest voltage
 *
 * @returns Nothing
 */
void bms_svc_acquire_highest_cell(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC],
		float *highest_voltage,
		int *highest_slave_idx,
		int *highest_cell_idx) {


	float max_v = cell_voltages[0][0];

	int max_slave = 0;
	int max_cell = 0;

	for (int i = 0; i < ADBMS_NUM_SLAVES; i++) {
		for (int j = 0; j < ADBMS_CELLS_PER_IC; j++) {
			if (cell_voltages[i][j] > max_v) {
				max_v = cell_voltages[i][j];
				max_slave = i;
				max_cell = j;
			}
		}
	}

	*highest_voltage = max_v;
	*highest_slave_idx = max_slave;
	*highest_cell_idx = max_cell;
}


/*
 * PWM Balancing stuff, probably not going to use but leaving here just in case.
 */
//void bms_svc_pwm_bal_init(void){
//
//	const uint16_t WRCFGB_CMD = 0x24u;  // 0b00000100100
//
//	uint8_t tx_data[ADBMS_NUM_SLAVES][ADBMS_REG_GROUP_SIZE] = {0};
//
//	for (uint8_t slave = 0; slave < ADBMS_NUM_SLAVES; slave++)
//	{
//		tx_data[slave][0] = 0x17u;  // 0b00010111: VUV[7:0]
//		tx_data[slave][1] = 0x53u;  // 0b01010011: VOV[3:0] + VUV[11:8]
//		tx_data[slave][2] = 0x46u;  // 0b01000110: VOV[11:4]
//		tx_data[slave][3] = 0xBCu;  // 0b10111100: DTMEN = 1, DTRNG = 0, DCTO = 60
//		tx_data[slave][4] = 0x00u;  // DCC1–DCC8 cleared
//		tx_data[slave][5] = 0x00u;  // DCC9–DCC16 cleared
//	}
//
//	adbms6830_write_register_group(WRCFGB_CMD, tx_data);
//
//
//
//	const uint16_t CMD_WRPWMA = 0x20u;  // 0b00000100000
//	const uint16_t CMD_WRPWMB = 0x21u;  // 0b00000100001
//
//	uint8_t PWMA[ADBMS_NUM_SLAVES][ADBMS_REG_GROUP_SIZE] = {0};
//	uint8_t PWMB[ADBMS_NUM_SLAVES][ADBMS_REG_GROUP_SIZE] = {0};
//
//	for (uint8_t slave = 0; slave < ADBMS_NUM_SLAVES; slave++)
//	{
//		// Cells 1–12: each PWM value is 0b0100.
//		PWMA[slave][0] = 0x44u;  // 0b01000100: PWM2 = 0100, PWM1  = 0100
//		PWMA[slave][1] = 0x44u;  // 0b01000100: PWM4 = 0100, PWM3  = 0100
//		PWMA[slave][2] = 0x44u;  // 0b01000100: PWM6 = 0100, PWM5  = 0100
//		PWMA[slave][3] = 0x44u;  // 0b01000100: PWM8 = 0100, PWM7  = 0100
//		PWMA[slave][4] = 0x44u;  // 0b01000100: PWM10 = 0100, PWM9 = 0100
//		PWMA[slave][5] = 0x44u;  // 0b01000100: PWM12 = 0100, PWM11 = 0100
//
//		// Cell 13 enabled; cells 14–16 stay off.
//		PWMB[slave][0] = 0x04u;  // 0b00000100: PWM14 = 0000, PWM13 = 0100
//		PWMB[slave][1] = 0x00u;  // PWM16 = 0, PWM15 = 0
//
//		// Required fixed-one bytes in PWM Group B.
//		PWMB[slave][2] = 0xFFu;  // 0b11111111
//		PWMB[slave][3] = 0xFFu;  // 0b11111111
//		PWMB[slave][4] = 0xFFu;  // 0b11111111
//		PWMB[slave][5] = 0xFFu;  // 0b11111111
//	}
//
//	adbms6830_write_register_group(CMD_WRPWMA, PWMA);
//	adbms6830_write_register_group(CMD_WRPWMB, PWMB);
//
//	uint16_t CMD_ADCV = 0x2E0u; // 0b01011100000
//
//	adbms6830_send_command(CMD_ADCV);
//
//}

// Do every 100ms, redundant and open wire voltage readings
//int bms_pwm_diagnostic_cycle(void)
//{
//	const uint16_t CMD_ADSV_REDUNDANT = 0x1E8u;  // 0b00111101000: CONT = 1, DCP = 0, OW = 00
//	const uint16_t CMD_ADSV_EVEN_OW = 0x169u;  // 0b00101101001: CONT = 0, DCP = 0, OW = 01
//	const uint16_t CMD_ADSV_ODD_OW = 0x16Au;  // 0b00101101010: CONT = 0, DCP = 0, OW = 10
//
//	int result;
//
//    result = adbms6830_send_command(CMD_ADSV_REDUNDANT);
//    if (result != 0)
//    {
//        return result;
//    }
////
////    osDelay(16);  // Wait 16 ms for the synchronized ADC comparison.
//
//    // cells 2, 4, 6, 8, 10, and 12.
//    result = adbms6830_send_command(CMD_ADSV_EVEN_OW);
//	if (result != 0)
//	{
//		return result;
//	}
//
////	osDelay(8);
//
//	// cells 1, 3, 5, 7, 9, 11, and 13.
//	result = adbms6830_send_command(CMD_ADSV_ODD_OW);
//	if (result != 0)
//	{
//		return result;
//	}
//
////	osDelay(8);
//
//    return 0;
//}
