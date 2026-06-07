#include "acu_data.h"
#include <string.h>
#include "acuhv_config.h"

static bool g_initialized;

static acu_measurements_t g_acu_measurements;
static acu_fault_t g_acu_fault;
static acu_energy_state_t g_acu_energy_state;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/
//TODO configure default values as invaldi
status_t acu_data_init(void)
{
    memset(&g_acu_measurements, 0, sizeof(g_acu_measurements));
    g_acu_measurements.battery_current = 0.0f;
    g_acu_measurements.battery_power = 0.0f;
    g_acu_measurements.battery_voltage = 0.0f;
    g_acu_measurements.ts_voltage = 0.0f;
    g_acu_measurements.ts_active = false;

    g_acu_measurements.air_neg_closed = false;
    g_acu_measurements.air_pos_closed = false;

    g_acu_measurements.acu_state = ACU_APP_STATE_STARTUP;

    memset(&g_acu_fault, 0, sizeof(g_acu_fault));
    g_acu_fault.bms_fault = false;
    g_acu_fault.imd_fault = false;
    g_acu_fault.precharge_timeout = false;

    memset(&g_acu_energy_state, 0, sizeof(g_acu_energy_state));
    g_acu_energy_state.battery_capacity_ah = 0.0f;
    g_acu_energy_state.battery_energy_wh = 0.0f;
    g_acu_energy_state.battery_soc = 0.0f;
    g_acu_energy_state.battery_soe = 0.0f;

    g_initialized = true;

    return OK;
}
/*============================================================================*/
/* Accumulator Measurement Data Setters                                                   */
/*============================================================================*/

//TODO: add mutex protection for these data accesses
status_t acu_data_set_acu_measurements(const acu_measurements_t *acu_measurements)
{
    if (acu_measurements == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    g_acu_measurements = *acu_measurements;

    return OK;
}

void acu_data_set_acu_battery_current(float current)
{
    g_acu_measurements.battery_current = current;
}

void acu_data_set_acu_battery_power(float power)
{
    g_acu_measurements.battery_power = power;
}

void acu_data_set_acu_battery_voltage(float voltage)
{
    g_acu_measurements.battery_voltage = voltage;
}

void acu_data_set_acu_ts_active(bool ts_active)
{
    g_acu_measurements.ts_active = ts_active;
}

void acu_data_set_acu_ts_voltage(float ts_voltage)
{
    g_acu_measurements.ts_voltage = ts_voltage;
}

void acu_data_set_air_neg_is_closed(bool state_closed)
{
    g_acu_measurements.air_neg_closed = state_closed;
}

void acu_data_set_air_pos_is_closed(bool state_closed)
{
    g_acu_measurements.air_pos_closed = state_closed;
}

/*============================================================================*/
/* Accumulator Measurement Data Getters                                                   */
/*============================================================================*/

status_t acu_data_get_acu_measurements(acu_measurements_t *acu_data)
{
	*acu_data = g_acu_measurements;
	return OK;
}

float acu_data_get_acu_battery_voltage(void)
{
    return g_acu_measurements.battery_voltage;
}

float acu_data_get_acu_battery_current(void)
{
    return g_acu_measurements.battery_current;
}

float acu_data_get_acu_battery_power(void)
{
    return g_acu_measurements.battery_power;
}

float acu_data_get_acu_ts_voltage(void)
{
    return g_acu_measurements.ts_voltage;
}

bool acu_data_get_acu_ts_active(void)
{
    return g_acu_measurements.ts_active;
}

bool acu_data_get_air_neg_is_closed(bool state_closed)
{
    return g_acu_measurements.air_neg_closed;
}

bool acu_data_get_air_pos_is_closed(bool state_closed)
{
    return g_acu_measurements.air_pos_closed;
}

/*============================================================================*/
/* Accumulator State Getter and Setter                                        */
/*============================================================================*/

void acu_data_set_acu_state(acu_app_state_t acu_state)
{
    g_acu_measurements.acu_state = acu_state;
}

acu_app_state_t acu_data_get_acu_state(void)
{
    return g_acu_measurements.acu_state;
}

/*============================================================================*/
/* Accumulator Fault Status Setters                                           */
/*============================================================================*/
status_t acu_data_set_fault_status(const acu_fault_t *acu_fault_status)
{
    if(acu_fault_status == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    g_acu_fault = *acu_fault_status;

    return OK;
}

void acu_data_set_bms_fault_status(bool fault_status)
{
    g_acu_fault.bms_fault = fault_status;
}

void acu_data_set_imd_fault_status(bool fault_status)
{
    g_acu_fault.imd_fault = fault_status;
}

void acu_data_set_precharge_timeout_fault_status(bool fault_status)
{
    g_acu_fault.precharge_timeout = fault_status;
}
/*============================================================================*/
/* Accumulator Fault Status Getters                                           */
/*============================================================================*/

status_t acu_data_get_fault_status(acu_fault_t *acu_fault_status)
{
	*acu_fault_status = g_acu_fault;
	return OK;
}

bool acu_data_get_bms_fault_status(void)
{
    return g_acu_fault.bms_fault;
}

bool acu_data_get_imd_fault_status(void)
{
    return g_acu_fault.imd_fault;
}

bool acu_data_get_precharge_timeout_fault_status(void)
{
    return g_acu_fault.precharge_timeout;
}

/*============================================================================*/
/* Accumulator Energy State Setters                                           */
/*============================================================================*/
void acu_data_set_acu_energy_states(float soc_percent, float soe_percent, float energy_wh, float charge_ah){

    g_acu_energy_state.battery_soc = soc_percent;
    g_acu_energy_state.battery_soe = soe_percent;
    g_acu_energy_state.battery_energy_wh = energy_wh;
    g_acu_energy_state.battery_capacity_ah = charge_ah;
    
}

/*============================================================================*/
/* Accumulator Energy State Getters                                           */
/*============================================================================*/
status_t acu_data_get_acu_energy_states(acu_energy_state_t *acu_energy_state)
{
	*acu_energy_state = g_acu_energy_state;
	return OK;
}

float acu_data_get_acu_charge_Ah(void)
{
    return g_acu_energy_state.battery_capacity_ah;
}

float acu_data_get_acu_energy_Wh(void)
{
    return g_acu_energy_state.battery_energy_wh;
}
