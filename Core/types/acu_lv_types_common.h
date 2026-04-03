/*
 * acu_lv_types_common.h
 *  
 *  Contains types that are used accross multiple files
 *  for the LV board and states for the BMS
 * 
 *  Created on: Mar 23, 2026
 *      Author: f-dunnwolbaum
 */

#ifndef TYPES_ACU_LV_TYPES_COMMON_H_
#define TYPES_ACU_LV_TYPES_COMMON_H_

#include <stdint.h>
#include <stdbool.h>
#include "acu_lv_config.h"

/*============================================================================*/
/* BMS System States                                                          */
/*============================================================================*/

typedef enum
{
    BMS_IDLE = 0U,
    BMS_STARTUP,
    BMS_PRECHARGE,
    BMS_TS_ACTIVE,
    BMS_FAULT
} bms_state_t;


typedef enum
{
    ACU_LV_MEASUREMENT_TEMP = 0U,
    ACU_LV_MEASUREMENT_CURRENT,
    ACU_LV_MEASUREMENT_VOLTAGE
} acu_lv_measurement_type_t;

typedef struct
{   
    acu_lv_measurement_type_t measurement_type; 
    float valid_min; // minimum valid value for a given sensor, if below then trigger a fault
    float valid_max; //max valid value, if above then trigger fault
    float scaling_factor; // scaling factor if voltage divider is used
} acu_lv_measurement_setting_t;

#endif /* TYPES_ACU_LV_TYPES_COMMON_H_ */
