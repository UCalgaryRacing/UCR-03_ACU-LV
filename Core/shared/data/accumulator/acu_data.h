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
    bool ts_active;

    bool air_neg_closed;
    bool air_pos_closed;

    acu_app_state_t acu_state;
    
} acu_measurements_t;

typedef struct 
{
    float battery_soc;
    float battery_soe;
    float battery_energy_wh;
    float battery_capacity_ah;
} acu_energy_state_t;

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

/*============================================================================*/
/* Setters                                                                    */
/*============================================================================*/

// pack measurements
status_t acu_data_set_acu_measurements(const acu_measurements_t *acu_data);
void acu_data_set_acu_battery_current(float current);
void acu_data_set_acu_battery_power(float power);
void acu_data_set_acu_battery_voltage(float voltage);
void acu_data_set_acu_ts_active(bool ts_active);
void acu_data_set_acu_ts_voltage(float ts_voltage);

void acu_data_set_air_neg_is_closed(bool state_closed);
void acu_data_set_air_pos_is_closed(bool state_closed);

// energy states
void acu_data_set_acu_energy_states(float soc_percent,float soe_percent, float energy_wh, float charge_ah);

// faults
status_t acu_data_set_fault_status(const acu_fault_t *acu_fault_status);
void acu_data_set_bms_fault_status(bool fault_status);
void acu_data_set_imd_fault_status(bool fault_status);
void acu_data_set_precharge_timeout_fault_status(bool fault_status);

/*============================================================================*/
/* Getters                                                                    */
/*============================================================================*/
// pack measurements
status_t acu_data_get_acu_measurements(acu_measurements_t *acu_data);
float acu_data_get_acu_battery_voltage(void);
float acu_data_get_acu_battery_current(void);
float acu_data_get_acu_battery_power(void);
float acu_data_get_acu_ts_voltage(void);
bool acu_data_get_acu_ts_active(void);

bool acu_data_get_air_neg_is_closed(bool state_closed);
bool acu_data_get_air_pos_is_closed(bool state_closed);

// energy states
status_t acu_data_get_acu_energy_states(acu_energy_state_t *acu_energy_state);
float acu_data_get_acu_charge_Ah(void);
float acu_data_get_acu_energy_Wh(void);

// faults
status_t acu_data_get_fault_status(acu_fault_t *acu_fault_status);
bool acu_data_get_bms_fault_status(void);
bool acu_data_get_imd_fault_status(void);
bool acu_data_get_precharge_timeout_fault_status(void);


/*============================================================================*/
/* Accumulator State                                                          */
/*============================================================================*/

void acu_data_set_acu_state(acu_app_state_t acu_state);
acu_app_state_t acu_data_get_acu_state(void);

#endif /* DATA_ACU_DATA_H_ */
