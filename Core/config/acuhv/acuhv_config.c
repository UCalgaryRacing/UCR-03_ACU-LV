#include "acuhv_config.h"
#include "acuhv_config_pinout.h"

#include "mcu_config_dfsdm.h"
#include "mcu_dfsdm_filters.h"

/*============================================================================*/
/* Private Contexts                                                           */
/*============================================================================*/

static mcu_dfsdm_context_t batt_current_context = 
{
    .dma_started = false,
    .filter_handle = BATT_CURRENT_FILTER_HANDLE
};

static mcu_dfsdm_context_t batt_voltage_context = 
{
    .dma_started = false,
    .filter_handle = BATT_VOLTAGE_FILTER_HANDLE
};

static mcu_dfsdm_context_t ts_voltage_context = 
{
    .dma_started = false,
    .filter_handle = TS_VOLTAGE_FILTER_HANDLE
};

const mcu_dfsdm_config_t mcu_dfsdm_config[DFSDM_FILTER_COUNT] =
{
    /*------------------------------------------------------------------------*/
    /* TS Voltage                                                              */
    /*------------------------------------------------------------------------*/
    [TS_VOLTAGE] =
    {
        .hw = {
            .dfsdm_context = &ts_voltage_context,
            .dfsdm_buffer_number = ACUHV_DFSDM1_DATIN2_BUFFER_NUMBER,
        },
        .settings = {
            .scaling_factor = TS_SCALING_FACTOR,
            .valid_max = TS_VOLTAGE_MAX_V,
            .valid_min = TS_VOLTAGE_MIN_V,
        },
    },

    [BATT_VOLTAGE] = 
    {
        .hw = {
            .dfsdm_context = &batt_voltage_context,
            .dfsdm_buffer_number = ACUHV_DFSDM1_DATIN4_BUFFER_NUMBER,
        },
        .settings = {
            .scaling_factor = BATT_VOLTAGE_SCALING_FACTOR,
            .valid_max = BATT_VOLTAGE_MAX_V,
            .valid_min = BATT_VOLTAGE_MIN_V,
        },
    },

    [BATT_CURRENT] = 
    {
        .hw = {
            .dfsdm_context = &batt_current_context,
            .dfsdm_buffer_number = ACUHV_DFSDM1_DATIN6_BUFFER_NUMBER,
        },
        .settings = {
            .scaling_factor = SHUNT_SCALING_FACTOR,
            .valid_max = SHUNT_MAX,
            .valid_min = SHUNT_MIN,
        },
    },
};