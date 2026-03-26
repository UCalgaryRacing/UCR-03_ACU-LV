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
    BMS_IDLE = 0U,
    BMS_STARTUP,
    BMS_PRECHARGE,
    BMS_TS_ACTIVE,
    BMS_FAULT
} bms_state_t;



#endif /* TYPES_ACU_LV_TYPES_COMMON_H_ */
