#include "aculv_config.h"
#include "aculv_config_pinout.h"
#include "mcu_analog_channels.h"

// adc 
static mcu_adc_context_t adc_2_context = {
    .adc_channels = ACULV_ADC_2_MAX_NUMBER_CHANNELS,
    .adc_handle = ACULV_ADC_2_HANDLE,
    .adc_max = ACULV_ADC_2_MAX_COUNTS,
    .adc_vref = ACULV_ADC_VREF,
    .adc_scaling = ACULV_ADC_SCALING_FACTOR,
    .calibrated = false,
    .dma_started = false,
};

static mcu_adc_context_t adc_3_context = {
    .adc_channels = ACULV_ADC_3_MAX_NUMBER_CHANNELS,
    .adc_handle = ACULV_ADC_3_HANDLE,
    .adc_max = ACULV_ADC_3_MAX_COUNTS,
    .adc_vref = ACULV_ADC_VREF,
    .adc_scaling = ACULV_ADC_SCALING_FACTOR,
    .calibrated = false,
    .dma_started = false,
};

// adc: config
const mcu_analog_config_t mcu_adc_config[MCU_MAX_ADC_COUNT] = 
{
    /*------------------------------------------------------------------------*/
    /* SDC_MID_1, ADC3 Channel 3 Rank 1                                                  */
    /*------------------------------------------------------------------------*/
    [SDC_MID_1] = 
    {
        .hw = 
        {
            .adc_context = &adc_3_context,
            .adc_buffer_index = MCU_ADC3_3_BUFFER_INDEX,
            .adc_buffer_number = MCU_ADC3_3_BUFFER_NUMBER,
        },
        .settings = 
        {
            .scaling_factor = ACULV_ADC_SCALING_FACTOR,
        },
        .enabled = true,
    },
    /*------------------------------------------------------------------------*/
    /* SDC_MID_2, ADC3 Channel 5 Rank 2                                       */
    /*------------------------------------------------------------------------*/
    [SDC_MID_2] = 
    {
        .hw = 
        {
            .adc_context = &adc_3_context,
            .adc_buffer_index = MCU_ADC3_5_BUFFER_INDEX,
            .adc_buffer_number = MCU_ADC3_5_BUFFER_NUMBER,
        },
        .settings = 
        {
            .scaling_factor = ACULV_ADC_SCALING_FACTOR,
        },
        .enabled = true,
    },
    /*------------------------------------------------------------------------*/
    /* SDC_7, ADC2 Channel 5 Rank 1                                           */
    /*------------------------------------------------------------------------*/
    [SDC_7] = 
    {
        .hw = 
        {
            .adc_context = &adc_2_context,
            .adc_buffer_index = MCU_ADC2_5_BUFFER_INDEX,
            .adc_buffer_number = MCU_ADC2_5_BUFFER_NUMBER,
        },
        .settings = 
        {
            .scaling_factor = ACULV_ADC_SCALING_FACTOR,
        },
        .enabled = true,
    },
    /*------------------------------------------------------------------------*/
    /* SDC_8, ADC3 Channel 2 Rank 3                                           */
    /*------------------------------------------------------------------------*/
    [SDC_8] = 
    {
        .hw = 
        {
            .adc_context = &adc_3_context,
            .adc_buffer_index = MCU_ADC3_2_BUFFER_INDEX,
            .adc_buffer_number = MCU_ADC3_2_BUFFER_NUMBER,
        },
        .settings = 
        {
            .scaling_factor = ACULV_ADC_SCALING_FACTOR,
        },
        .enabled = true,
    },
    /*------------------------------------------------------------------------*/
    /* SDC_END, ADC3 Channel 4 Rank 4                                                 */
    /*------------------------------------------------------------------------*/
    [SDC_END] = 
    {
        .hw = 
        {
            .adc_context = &adc_3_context,
            .adc_buffer_index = MCU_ADC3_4_BUFFER_INDEX,
            .adc_buffer_number = MCU_ADC3_4_BUFFER_NUMBER,

        },
        .settings = 
        {
            .scaling_factor = ACULV_ADC_SCALING_FACTOR,
        },
        .enabled = true,
    },
    /*------------------------------------------------------------------------*/
    /* SDC_RESERVE, ADC2 Channel 3 Rank 2                                      */
    /*------------------------------------------------------------------------*/
    [SDC_RESERVE] = 
    {
        .hw = 
        {
            .adc_context = &adc_2_context,
            .adc_buffer_index = MCU_ADC2_3_BUFFER_INDEX,
            .adc_buffer_number = MCU_ADC2_3_BUFFER_NUMBER,
        },
        .settings = 
        {
            .scaling_factor = ACULV_ADC_SCALING_FACTOR,
        },
        .enabled = true,
    },
};
