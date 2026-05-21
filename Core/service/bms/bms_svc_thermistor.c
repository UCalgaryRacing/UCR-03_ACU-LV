#include "cmsis_os2.h"
#include "bms_drv_adbms6830.h"
#include "acu_lv_svc_adbms6830.h"
#include "bms_drv_adbms6830_regs.h"
#include "bms_svc_thermistor.h"
#include "acu_data.h"
#include "acu_lv_config.h"
#include <stdlib.h>
// void bms_svc_admbs_toggle_mux(uint16_t gpio);

/* Private Functions */
static float get_highest_temp();
static float get_lowest_temp();

/*============================================================================*/
/* Temperature Sampling                                                       */
/*============================================================================*/

static uint16_t raw_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC];
static float processed_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC];

extern bms_temp_stats_t temp_stats;


//TODO add this to adbms drivers
void bms_svc_admbs_toggle_mux(adbms_gpo_pin_t pin)
{
    adbms6830_shadow_t *shadow = bms_manager_get_shadow();

    //mux control connected to gpio1 which is bit 0 of byte 3
    shadow->cfga[3] ^= ADBMS_GPO1_MASK;

    adbms6830_write_cfga(shadow);

    adbms6830_read_cfga(shadow);
}

void bms_svc_acquire_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
    for(int mux_state = 0; mux_state < 1; mux_state++)
    {
        adbms6830_read_half_cell_temps(ADBMS_NUM_SLAVES, ADBMS_THERMS_PER_IC, cell_temps, mux_state);
    }
}

// void bms_svc_acquire_thermistor_temps(uint8_t mux_state)
// {   
//     uint8_t mux_index = mux_state * 9;
//     uint16_t count = 0;
//     int result = adbms6830_start_gpio_adc();
//     float therm_sum = 0.0f;
//     // Wait for ADC conversion to complete (~4ms)
//     osDelay(5);

//     result = adbms6830_read_gpio_voltages_raw(raw_temps,mux_state);

//     for (int slave = 0; slave < ADBMS_NUM_SLAVES; slave++)
//     {
//         for (int thermistor = mux_index; thermistor < mux_index + 9; thermistor++)
//         {   
//             float thermistor_voltage = adbms6830_adc_to_volts(raw_temps[slave][thermistor]);
//             processed_temps[slave][thermistor] = calculate_thermistor_temperature(thermistor_voltage);

//             if(processed_temps[slave][thermistor] > temp_stats.temp_max_c)
//             {
//                 temp_stats.temp_max_c = processed_temps[slave][thermistor];
//                 temp_stats.temp_max_idx = thermistor;
//                 temp_stats.temp_max_slave = slave;
//             }
//             else if (processed_temps[slave][thermistor] < -50.0f)
//             {
//                processed_temps[slave][thermistor] = temp_stats.temp_avg_c;
//             }
//             else if (processed_temps[slave][thermistor] > 1000.0f)
//             {
//                 processed_temps[slave][thermistor] = temp_stats.temp_avg_c;
//             }
//             else if(processed_temps[slave][thermistor] < temp_stats.temp_min_c)
//             {
//                 temp_stats.temp_min_c = processed_temps[slave][thermistor];
//                 temp_stats.temp_min_idx = thermistor;
//                 temp_stats.temp_max_slave = slave;
//             }else
//             {
//                 therm_sum += processed_temps[slave][thermistor];
//                 count++;
//             }
            
//         }

//     }
//     temp_stats.temp_avg_c = therm_sum / (float)count;
// }

// void vw_temps()
// {
//     float vw_temp = 23.0f;

//     temp_stats.temp_min_c = vw_temp;
//     temp_stats.temp_max_c = vw_temp;

//     for(uint8_t slave_idx = 0U; slave_idx < ADBMS_NUM_SLAVES; slave_idx++)
//     {
//         for (uint8_t therm_idx = 0U; therm_idx < ADBMS_THERMS_PER_IC; therm_idx++)
//         {
//             processed_temps[slave_idx][therm_idx] = vw_temp + ((float)rand()/(float)(RAND_MAX)) * 0.25f - 0.125f; // Add random noise of +/- 0.5C
//             if (processed_temps[slave_idx][therm_idx] < temp_stats.temp_min_c)
//             {
//                 temp_stats.temp_min_c = processed_temps[slave_idx][therm_idx];
//             }
//             if (processed_temps[slave_idx][therm_idx] > temp_stats.temp_max_c)
//             {
//                 temp_stats.temp_max_c = processed_temps[slave_idx][therm_idx];
//             }
//         }
//     }

// }




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