#include "sdc_data.h"
#include <string.h>

static sdc_data_t g_sdc_data;
static bool g_initialized;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/

status_t sdc_data_init(void)
{
    memset(&g_sdc_data, 0, sizeof(g_sdc_data));
    g_sdc_data.sdc_mid1_voltage = 0.0f;
    g_sdc_data.sdc_mid2_voltage = 0.0f;
    g_sdc_data.sdc_7_voltage = 0.0f;
    g_sdc_data.sdc_8_voltage = 0.0f;
    g_sdc_data.sdc_end_voltage = 0.0f;
    g_sdc_data.sdc_reserve_voltage = 0.0f;

    g_initialized = true;

    return OK;
}

/*============================================================================*/
/* SDC  Data Setters                                                           */
/*============================================================================*/

status_t sdc_data_set_sdc_data(const sdc_data_t *sdc_data)
{
    if (sdc_data == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    g_sdc_data = *sdc_data;

    return OK;
}

void sdc_data_set_sdc_mid1_voltage(float voltage)
{
    g_sdc_data.sdc_mid1_voltage = voltage;
}

void sdc_data_set_sdc_mid2_voltage(float voltage)
{
    g_sdc_data.sdc_mid2_voltage = voltage;
}

void sdc_data_set_sdc_7_voltage(float voltage)
{
    g_sdc_data.sdc_7_voltage = voltage;
}

void sdc_data_set_sdc_8_voltage(float voltage)
{
    g_sdc_data.sdc_8_voltage = voltage;
}

void sdc_data_set_sdc_end_voltage(float voltage)
{
    g_sdc_data.sdc_end_voltage = voltage;
}

void sdc_data_set_sdc_reserve_voltage(float voltage)
{
    g_sdc_data.sdc_reserve_voltage = voltage;
}

/*============================================================================*/
/* SDC Data Getters                                                           */
/*============================================================================*/

status_t sdc_data_get_sdc_voltages(sdc_data_t *sdc_data)
{
	*sdc_data = g_sdc_data;
	return OK;
}

float sdc_data_get_mid1_voltage(void)
{
    return g_sdc_data.sdc_mid1_voltage;
}

float sdc_data_get_mid2_voltage(void)
{
    return g_sdc_data.sdc_mid2_voltage;
}

float sdc_data_get_sdc_8_voltage(void)
{
    return g_sdc_data.sdc_8_voltage;
}

float sdc_data_get_sdc_7_voltage(void)
{
    return g_sdc_data.sdc_7_voltage;
}

float sdc_data_get_sdc_end_voltage(void)
{
    return g_sdc_data.sdc_end_voltage;
}

float sdc_data_get_sdc_reserve_voltage(void)
{
    return g_sdc_data.sdc_reserve_voltage;
}
