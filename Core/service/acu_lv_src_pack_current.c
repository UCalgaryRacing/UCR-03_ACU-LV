/*
 * acu_lv_src_pack_current.c
 *
 *  Created on: Apr 2, 2026
 *      Author: clayd
 */

#include "acu_lv_svc_pack_current.h"

float average_shunt_current(int32_t * data, uint8_t length)
{   
    int32_t sum = 0;
    float averaged_value;

    for(uint8_t i = 0; i < length; i++)
    {
        sum += data[i];
    }

    return averaged_value = ((float)sum/((float)CURRENT_SHUNT_DATA_LENGTH * CURRENT_SHUNT_SCALING_FACTOR));
}
