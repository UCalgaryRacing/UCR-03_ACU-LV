#include "bms_svc_thermistor.h"
#include "bms_config.h"
#include "bms_drv_adbms6830.h"

#include <math.h>
#include <stdbool.h>

float max_slave_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC] = {0};

static void bms_svc_apply_therm_exclusions(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
    for (uint8_t exclusion_idx = 0U; exclusion_idx < bms_therm_exclusion_count; exclusion_idx++)
    {
        const uint8_t slave = bms_therm_exclusions[exclusion_idx].slave;
        const uint8_t therm = bms_therm_exclusions[exclusion_idx].therm;
		cell_temps[slave][therm] = NAN;
    }
}

void bms_svc_acquire_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
    adbms6830_read_all_cell_temps(ADBMS_NUM_SLAVES, ADBMS_THERMS_PER_IC, cell_temps);
    bms_svc_apply_therm_exclusions(cell_temps);
}

void bms_svc_acquire_max_slave_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
    adbms6830_read_all_cell_temps(ADBMS_NUM_SLAVES, ADBMS_THERMS_PER_IC, cell_temps);
    bms_svc_apply_therm_exclusions(cell_temps);

    for (int i = 0; i < ADBMS_NUM_SLAVES; i++) {
    	for (int j = 0; j < ADBMS_THERMS_PER_IC; j++){
    		if (cell_temps[i][j] > max_slave_temps[0][i]) {
    			max_slave_temps[0][i] = cell_temps[i][j];
    		}
    	}
    }
}

bool bms_svc_check_all_cell_temperature_limits(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
    //TODO grab cell_voltages from data layer not as an input
    for (uint8_t slave_idx = 0U; slave_idx < ADBMS_NUM_SLAVES; slave_idx++)
    {
        for (uint8_t therm_idx = 0U; therm_idx < ADBMS_THERMS_PER_IC; therm_idx++)
        {
            if (isnan(cell_temps[slave_idx][therm_idx]))
            {
                continue;
            }

            if (cell_temps[slave_idx][therm_idx] > CELL_MAX_TEMPERATURE
                || cell_temps[slave_idx][therm_idx] < CELL_MIN_TEMPERATURE)
            {
                return true;
            }
        }
    }

    return false;
}
