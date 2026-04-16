#ifndef DATA_ACU_DATA_H_
#define DATA_ACU_DATA_H_

#include <stdint.h>
#include <stdbool.h>
#include "com_typ_common.h"

/*============================================================================*/
/* Accumulator LV Data Structure                                              */
/*============================================================================*/

typedef struct
{
    float battery_current;
    float battery_voltage;
    float battery_power;
    float ts_voltage;
    bool ts_active;
} acu_aculv_data_t;

typedef struct
{
    bool bms_fault;
    bool imd_fault;
} acu_fault_t;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/

status_t acu_data_init(void);
status_t acu_fault_init(void);

/*============================================================================*/
/* Setters                                                                    */
/*============================================================================*/

status_t acu_data_set_aculv(const acu_aculv_data_t *aculv_data);
status_t acu_data_set_fault_status(const acu_fault_t *acu_fault_status);

void acu_data_set_bms_fault_status(bool fault_status);
void acu_data_set_bms_fault_status(bool fault_status);

/*============================================================================*/
/* Getters                                                                    */
/*============================================================================*/

float acu_data_get_aculv_battery_voltage(void);
float acu_data_get_aculv_battery_current(void);
float acu_data_get_aculv_battery_power(void);
float acu_data_get_aculv_ts_voltage(void);
bool acu_data_get_aculv_ts_active(void);

bool acu_data_get_bms_fault_status(void);
bool acu_data_get_imd_fault_status(void);


status_t acu_data_get_fault_status(acu_fault_t *acu_fault_status);


#endif /* DATA_ACU_DATA_H_ */
