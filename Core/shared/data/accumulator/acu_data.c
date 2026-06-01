#include "acu_data.h"
#include <string.h>
#include "acuhv_config.h"

static bool g_initialized;
static bool g_acu_fault_initialized;

static acu_data_t g_acu_data;
static acu_fault_t g_acu_fault;
static acu_app_state_t g_acu_state = ACU_APP_STATE_STARTUP;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/
//TODO configure default values as invaldi
status_t acu_data_init(void)
{
    memset(&g_acu_data, 0, sizeof(g_acu_data));
    g_acu_data.battery_current = 0.0f;
    g_acu_data.battery_power = 0.0f;
    g_acu_data.battery_voltage = 0.0f;
    g_acu_data.ts_voltage = 0.0f;
    g_acu_data.ts_active = false;

    memset(&g_acu_fault, 0, sizeof(g_acu_fault));
    g_acu_fault.bms_fault = false;
    g_acu_fault.imd_fault = false;
    g_acu_fault.precharge_timeout = false;

    g_initialized = true;

    return OK;
}

status_t acu_fault_init(void)
{
    memset(&g_acu_fault, 0, sizeof(g_acu_fault));
    g_acu_fault.bms_fault = false;
    g_acu_fault.imd_fault = false;
    g_acu_fault.precharge_timeout = false;

    g_acu_fault_initialized = true;

    return OK;
}
/*============================================================================*/
/* Accumulator Data Setters                                                   */
/*============================================================================*/

//TODO: add mutex protection for these data accesses
status_t acu_data_set_acu_data(const acu_data_t *acu_data)
{
    if (acu_data == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    g_acu_data = *acu_data;

    return OK;
}

void acu_data_set_acu_battery_current(float current)
{
    g_acu_data.battery_current = current;
}

void acu_data_set_acu_battery_power(float power)
{
    g_acu_data.battery_power = power;
}

void acu_data_set_acu_battery_voltage(float voltage)
{
    g_acu_data.battery_voltage = voltage;
}

void acu_data_set_acu_ts_active(bool ts_active)
{
    g_acu_data.ts_active = ts_active;
}

void acu_data_set_acu_ts_voltage(float ts_voltage)
{
    g_acu_data.ts_voltage = ts_voltage;
}

void acu_data_set_acu_bms_stats(float soc_percent,float soe_percent, float energy_wh, float charge_ah){

    g_acu_data.soc = soc_percent;
    g_acu_data.soe = soe_percent;
    g_acu_data.energy_wh = energy_wh;
    g_acu_data.capacity_ah = charge_ah;


}

/*============================================================================*/
/* Accumulator Data Getters                                                   */
/*============================================================================*/

status_t acu_data_get_acu_data(acu_data_t *acu_data)
{
	*acu_data = g_acu_data;
	return OK;
}

float acu_data_get_acu_battery_voltage(void)
{
    return g_acu_data.battery_voltage;
}

float acu_data_get_acu_battery_current(void)
{
    return g_acu_data.battery_current;
}

float acu_data_get_acu_battery_power(void)
{
    return g_acu_data.battery_power;
}

float acu_data_get_acu_ts_voltage(void)
{
    return g_acu_data.ts_voltage;
}

float acu_data_get_acu_charge_Ah(void)
{
    return g_acu_data.capacity_ah;
}

float acu_data_get_acu_energy_Wh(void)
{
    return g_acu_data.energy_wh;
}

bool acu_data_get_acu_ts_active(void)
{
    return g_acu_data.ts_active;
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
/* Accumulator State                                                          */
/*============================================================================*/

void acu_data_set_acu_state(acu_app_state_t acu_state)
{
    g_acu_state = acu_state;
}

acu_app_state_t acu_data_get_acu_state(void)
{
    return g_acu_state;
}
