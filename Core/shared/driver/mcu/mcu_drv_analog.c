#include "mcu_drv_analog.h"
#include "stm32h7xx_hal_adc.h"

static uint16_t adc_dma_buffers[MCU_MAX_ADC_COUNT][MCU_MAX_ADC_CHANNELS];
static bool g_initialized = false;

/*============================================================================*/
/* Initialization Functions                                           */
/*============================================================================*/
status_t mcu_drv_analog_driver_init(void)
{

    if (g_initialized)
    {
        return OK;
    }

    g_initialized = true;
    return OK;
}

status_t mcu_drv_analog_init(const analog_hw_t *hw)
{
    if (hw == NULL)
    {
        return ERROR_GENERAL;
    }

    if (hw->adc_context->calibrated == false)
    {
        if (HAL_ADCEx_Calibration_Start(hw->adc_context->adc_handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
        {
            return ERROR_GENERAL;
        }
        hw->adc_context->calibrated = true;
    }

    g_initialized = true;
    return OK;
}

/*============================================================================*/
/* Private Start/Stop Functions                                               */
/*============================================================================*/

status_t mcu_drv_analog_start_adc(const analog_hw_t *hw)
{
    if (hw == NULL)
        return ERROR_GENERAL;

    if (hw->adc_context->dma_started == false)
    {
        if (HAL_ADC_Start_DMA(hw->adc_context->adc_handle, (uint32_t *)adc_dma_buffers[hw->adc_buffer_number], hw->adc_context->adc_channels) != HAL_OK)
        {
            return ERROR_GENERAL;
        }

        hw->adc_context->dma_started = true;
    }

    return OK;
}

/*============================================================================*/
/* Data Access                                                                */
/*============================================================================*/

status_t mcu_drv_analog_read_raw(const analog_hw_t *hw, uint16_t *adc_value)
{
    if (adc_value == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    *adc_value = adc_dma_buffers[hw->adc_buffer_number][hw->adc_buffer_index];

    return OK;
}
