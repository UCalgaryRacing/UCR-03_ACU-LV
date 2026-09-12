#ifndef MCU_CONFIG_ANALOG_H_
#define MCU_CONFIG_ANALOG_H_

#include "stm32h7xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

#include "mcu_analog_channels.h"

/*============================================================================*/
/* ADC Structures                                                              */
/*============================================================================*/

typedef struct {
    ADC_HandleTypeDef *adc_handle;
    float adc_vref;
    float adc_scaling; // all adcs on the LV have the same scaling factor
    uint16_t adc_max;  
    bool calibrated;
    bool dma_started;
    uint8_t adc_channels;
} mcu_adc_context_t;

/*============================================================================*/
/* Channel Hardware Mapping                                                   */
/*============================================================================*/

typedef struct
{
    mcu_adc_context_t *adc_context;
    uint16_t adc_buffer_number;
    uint16_t adc_buffer_index;
} analog_hw_t;

/*============================================================================*/
/* Analog calibration (one row in mcu_analog_config)                          */
/*============================================================================*/

typedef struct
{
    float scaling_factor; // all adcs on the LV have the same scaling factor
} mcu_analog_settings_t;

typedef struct
{
    bool enabled;
    mcu_analog_settings_t settings;
    analog_hw_t hw;
} mcu_analog_config_t;

#endif /*MCU_CONFIG_ANALOG_H_*/