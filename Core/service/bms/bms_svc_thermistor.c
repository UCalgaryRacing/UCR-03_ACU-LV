#include "bms_svc_thermistor.h"
#include "bms_config.h"
#include "bms_drv_adbms6830.h"

#include <stdbool.h>

void bms_svc_acquire_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
	adbms6830_read_all_cell_temps(ADBMS_NUM_SLAVES, ADBMS_THERMS_PER_IC, cell_temps);
	return;
}

bool bms_svc_check_all_cell_temperature_limits(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
	//TODO grab cell_voltages from data layer not as an input
	for (uint8_t slave_idx = 0U; slave_idx < ADBMS_NUM_SLAVES; slave_idx++)
    {
        //loop through all cells in each slave
        for (uint8_t therm_idx = 0U; therm_idx < ADBMS_THERMS_PER_IC; therm_idx++)
        {
            if (cell_temps[slave_idx][therm_idx] > CELL_MAX_TEMPERATURE || cell_temps[slave_idx][therm_idx] < CELL_MIN_TEMPERATURE)
			{
				//fault
				return true;
			}
        }
    }
	//no fault
	return false;
}
