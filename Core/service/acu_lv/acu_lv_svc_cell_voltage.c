/*
 * acu_lv_svc_cell_voltage.c
 *
 *  Created on: Apr 14, 2026
 *      Author: clayd
 */

#include "acu_lv_svc_cell_voltage.h"
#include "acu_lv_config.h"

extern float voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC];

/* Private functions*/
static float get_lowest_cell_voltage()
{
    float min = 100.0f;
    for(uint8_t slave_index = 0; slave_index < ADBMS_NUM_SLAVES; slave_index ++)
    {
        for(uint8_t cell_index = 0; cell_index < ADBMS_CELLS_PER_IC; cell_index++)
        {
            if(voltages[slave_index][cell_index] < min)
            {
                min = voltages[slave_index][cell_index];
            }
        }
    }
    return min;
}
static float get_highest_cell_voltage()
{
    float max = 0.0f;
    for(uint8_t slave_index = 0; slave_index < ADBMS_NUM_SLAVES; slave_index ++)
    {
        for(uint8_t cell_index = 0; cell_index < ADBMS_CELLS_PER_IC; cell_index++)
        {
            if(voltages[slave_index][cell_index] > max)
            {
                max = voltages[slave_index][cell_index];
            }
        }
    }
    return max;
}

status_t acu_lv_svc_check_cell_voltage()
{
    if((get_highest_cell_voltage() > ACU_LV_CELL_MAXIMUM_VOLTAGE) || (get_lowest_cell_voltage() < ACU_LV_CELL_MINIMUM_VOLTAGE))
    {
        return ERROR_GENERAL;
    }

    return OK;
}
