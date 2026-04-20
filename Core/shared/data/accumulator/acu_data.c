#include "acu_data.h"
#include <string.h>

static bool g_initialized;

static acu_aculv_data_t g_aculv_data;
static acu_fault_t g_aculv_fault;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/
//TODO configure default values as invaldi
status_t acu_data_init(void)
{
    memset(&g_aculv_data, 0, sizeof(g_aculv_data));
    g_aculv_data.battery_current = 0.0f;
    g_aculv_data.battery_power = 0.0f;
    g_aculv_data.battery_voltage = 0.0f;
    g_aculv_data.ts_voltage = 0.0f;
    g_aculv_data.ts_active = false;

    memset(&g_aculv_fault, 0, sizeof(g_aculv_fault));
    g_aculv_fault.bms_fault = false;
    g_aculv_fault.imd_fault = false;

    g_initialized = true;

    return OK;
}

/*============================================================================*/
/* ACULV Data Access                                                          */
/*============================================================================*/

//TODO: add mutex protection for these data accesses
status_t acu_data_set_aculv(const acu_aculv_data_t *aculv_data)
{
    if (aculv_data == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    g_aculv_data = *aculv_data;

    return OK;
}

float acu_data_get_aculv_battery_voltage(void)
{
    return g_aculv_data.battery_voltage;
}

float acu_data_get_aculv_battery_current(void)
{
    return g_aculv_data.battery_current;
}

float acu_data_get_aculv_battery_power(void)
{
    return g_aculv_data.battery_power;
}

float acu_data_get_aculv_ts_voltage(void)
{
    return g_aculv_data.ts_voltage;
}

bool acu_data_get_aculv_ts_active(void)
{
    return g_aculv_data.ts_active;
}

/*============================================================================*/
/* ACULV Fault Status Access                                                  */
/*============================================================================*/
status_t acu_data_set_fault_status(const acu_fault_t *acu_fault_status)
{
    if(acu_fault_status == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    g_aculv_fault = *acu_fault_status;

    return OK;
}

	status_t acu_data_get_fault_status(acu_fault_t *acu_fault_status)
	{
		*acu_fault_status = g_aculv_fault;
		return OK;
	}

void acu_data_set_bms_fault_status(bool fault_status)
{
    g_aculv_fault.bms_fault = fault_status;
}

void acu_data_set_imd_fault_status(bool fault_status)
{
    g_aculv_fault.imd_fault = fault_status;
}

bool acu_data_get_bms_fault_active(void)
{
    return g_aculv_fault.bms_fault;
}

bool acu_data_get_imd_fault_active(void)
{
    return g_aculv_fault.imd_fault;
}
