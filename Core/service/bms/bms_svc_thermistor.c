#include "bms_drv_adbms6830.h"
#include "bms_drv_adbms6830_regs.h"
#include "bms_svc_thermistor.h"
#include "cmsis_os2.h"
#include <stdlib.h>


/*============================================================================*/
/* Temperature Sampling                                                       */
/*============================================================================*/

/*
 * Mux wiring (per slave, two muxes share the same select lines):
 *   GPIO3 -> S0   GPIO4 -> S1   GPIO5 -> S2   GPIO6 -> S3
 *
 * In CFGA register A (CFGAR3) the GPO bits are laid out as:
 *   bit 7..0  =  GPO[8] GPO[7] GPO[6] GPO[5] GPO[4] GPO[3] GPO[2] GPO[1]
 *                                S3     S2     S1     S0
 * so the 4 mux select lines occupy bits [5:2] of cfga[3] in MSB-first order.
 *
 * GPO bit polarity (per datasheet): 0 = pull-down on (pin low),
 *                                   1 = pull-down off (pin high via ext pull-up).
 * With external pull-ups present on GPIO3..6, the GPO bit value matches the
 * logic level driven into the mux S input directly.
 */
#define BMS_MUX_SELECT_MASK     ((uint8_t)0x3CU)   /* bits [5:2] of cfga[3] */
#define BMS_MUX_SELECT_SHIFT    (2U)
#define BMS_CFGA0_REFON_MASK    ((uint8_t)0x80U)   /* bit 7 of cfga[0] */

/* We get two thermistor samples per mux state (G1V + G2V). Cover all 18
 * thermistors with ceil(ADBMS_THERMS_PER_IC / 2) channel selections. */
#define BMS_MUX_NUM_STATES      ((ADBMS_THERMS_PER_IC + 1U) / 2U)

/* Settling time after switching the mux selects before starting the ADC.
 * GPIO RC + mux propagation is well under 100 us in practice; 1 ms is the
 * RTOS tick granularity and is plenty of margin. */
#define BMS_MUX_SETTLE_MS       (1U)

void bms_svc_set_mux(uint8_t channel)
{
    adbms6830_shadow_t bms_shadow;

    /* Pull current config so we don't clobber REFON / other GPOs / comparator
     * threshold / etc. that may have been set up at init time. */
    adbms6830_read_cfga(&bms_shadow);

    /* Defensive: make sure the internal reference stays on regardless of
     * whatever else might have touched cfga[0]. ADC conversions need REFON. */
    bms_shadow.cfga[0] |= BMS_CFGA0_REFON_MASK;

    /* Replace just the 4 mux select bits in cfga[3]. */
    bms_shadow.cfga[3] = (uint8_t)((bms_shadow.cfga[3] & (uint8_t)~BMS_MUX_SELECT_MASK)
                                   | (uint8_t)((channel & 0x0FU) << BMS_MUX_SELECT_SHIFT));

    adbms6830_write_cfga(&bms_shadow);

    adbms6830_read_cfga(&bms_shadow);

    return;
}

void bms_svc_acquire_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
    for (uint8_t mux_state = 0U; mux_state < BMS_MUX_NUM_STATES; mux_state++)
    {
        bms_svc_set_mux(mux_state);

        osDelay(BMS_MUX_SETTLE_MS);

        adbms6830_read_two_cell_temps(ADBMS_NUM_SLAVES, ADBMS_THERMS_PER_IC, cell_temps, mux_state);
    }
}


bool bms_svc_check_all_cell_temperature_limits(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
	//TODO grab cell_voltages from data layer not as an input
	for (uint8_t slave_idx = 0U; slave_idx < ADBMS_NUM_SLAVES; slave_idx++)
    {
        //loop through all cells in each slave
        for (uint8_t cell_idx = 0U; cell_idx < ADBMS_THERMS_PER_IC; cell_idx++)
        {
            if (cell_temps[slave_idx][cell_idx] > CELL_MAX_TEMPERATURE || cell_temps[slave_idx][cell_idx] < CELL_MIN_TEMPERATURE)
			{
				//fault
				return true;
			}
        }
    }
	//no fault
	return false;
}
