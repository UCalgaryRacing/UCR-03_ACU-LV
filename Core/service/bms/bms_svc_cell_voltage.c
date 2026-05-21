#include "bms_svc_cell_voltage.h"
#include "bms_config.h"
#include "bms_drv_adbms6830.h"

#include <stdbool.h>

void bms_svc_acquire_all_cell_voltages(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC])
{
	adbms6830_read_all_cell_voltages(ADBMS_NUM_SLAVES, ADBMS_CELLS_PER_IC, cell_voltages);
	return;
}

bool bms_svc_check_all_cell_voltage_limits(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC])
{
	//TODO grab cell_voltages from data layer not as an input
	for (uint8_t slave_idx = 0U; slave_idx < ADBMS_NUM_SLAVES; slave_idx++)
    {
        //loop through all cells in each slave
        for (uint8_t cell_idx = 0U; cell_idx < ADBMS_CELLS_PER_IC; cell_idx++)
        {
            if (cell_voltages[slave_idx][cell_idx] > CELL_MAX_VOLTAGE || cell_voltages[slave_idx][cell_idx] < CELL_MIN_VOLTAGE)
			{
				//fault
				return true;
			}
        }
    }
	//no fault
	return false;
}
