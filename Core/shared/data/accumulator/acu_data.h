#ifndef DATA_ACU_DATA_H_
#define DATA_ACU_DATA_H_

#include <stdint.h>
#include <stdbool.h>
#include "com_typ_common.h"
#include "acu_app_state_manager.h"


/*============================================================================*/
/* Accumulator Data Structure                                                  */
/*============================================================================*/

typedef struct
{
    float battery_current;
    float battery_voltage;
    float battery_power;
    float ts_voltage;
    float soc;
    float soe;
    float energy_wh;
    float capacity_ah;
    bool ts_active;
} acu_data_t;

typedef struct
{
    bool bms_fault;
    bool imd_fault;

    bool precharge_timeout;
} acu_fault_t;



/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/

status_t acu_data_init(void);
status_t acu_fault_init(void);

/*============================================================================*/
/* Setters                                                                    */
/*============================================================================*/

status_t acu_data_set_acu_data(const acu_data_t *acu_data);
status_t acu_data_set_fault_status(const acu_fault_t *acu_fault_status);

void acu_data_set_acu_battery_current(float current);
void acu_data_set_acu_battery_power(float power);
void acu_data_set_acu_battery_voltage(float voltage);
void acu_data_set_acu_ts_active(bool ts_active);
void acu_data_set_acu_ts_voltage(float ts_voltage);
void acu_data_set_acu_bms_stats(float soc_percent,float soe_percent, float energy_wh, float charge_ah);

void acu_data_set_bms_fault_status(bool fault_status);
void acu_data_set_imd_fault_status(bool fault_status);

void acu_data_set_precharge_timeout_fault_status(bool fault_status);

/*============================================================================*/
/* Getters                                                                    */
/*============================================================================*/

status_t acu_data_get_acu_data(acu_data_t *acu_data);
status_t acu_data_get_fault_status(acu_fault_t *acu_fault_status);

float acu_data_get_acu_battery_voltage(void);
float acu_data_get_acu_battery_current(void);
float acu_data_get_acu_battery_power(void);
float acu_data_get_acu_ts_voltage(void);
float acu_data_get_acu_charge_Ah(void);
float acu_data_get_acu_energy_Wh(void);
bool acu_data_get_acu_ts_active(void);


bool acu_data_get_bms_fault_status(void);
bool acu_data_get_imd_fault_status(void);

bool acu_data_get_precharge_timeout_fault_status(void);


/*============================================================================*/
/* Accumulator State                                                          */
/*============================================================================*/

void acu_data_set_acu_state(acu_app_state_t acu_state);
acu_app_state_t acu_data_get_acu_state(void);

#endif /* DATA_ACU_DATA_H_ */
