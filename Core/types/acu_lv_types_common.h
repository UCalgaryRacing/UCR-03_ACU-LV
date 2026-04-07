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

/*============================================================================*/
/* BMS System States                                                          */
/*============================================================================*/

typedef enum
{
    ACU_LV_IDLE = 0U,
    ACU_LVSTARTUP,
    ACU_LVPRECHARGE,
    ACU_LVTS_ACTIVE,
    ACU_LV_FAULT
} acu_lv_state_t;

typedef enum
{
    ACU_LV_OK = 0U,
    ACU_LV_ERROR
} acu_lv_status_t;


typedef enum
{
    ACU_LV_MEASUREMENT_TEMP = 0U,
    ACU_LV_MEASUREMENT_PACK_CURRENT,
    ACU_LV_MEASUREMENT_TS_VOLTAGE,
    ACU_LV_MEASUREMENT_ACCU_VOLTAGE
} acu_lv_measurement_type_t;

typedef struct
{   
    acu_lv_measurement_type_t measurement_type; 
    float valid_min; // minimum valid value for a given sensor, if below then trigger a fault
    float valid_max; //max valid value, if above then trigger fault
    float scaling_factor; // scaling factor if voltage divider is used
} acu_lv_measurement_setting_t;

#endif /* TYPES_ACU_LV_TYPES_COMMON_H_ */
