#ifndef CONFIG_ACULV_CONFIG_H_
#define CONFIG_ACULV_CONFIG_H_

#include <stdbool.h>
#include "mcu_config_analog.h"

/*============================================================================*/
/* SDC to ADC mapping                                                          */
/*============================================================================*/
#define SDC_MID_1                       MCU_ADC3_3
#define SDC_MID_2                       MCU_ADC3_5
#define SDC_7                           MCU_ADC2_5
#define SDC_8                           MCU_ADC3_2
#define SDC_END                         MCU_ADC3_4
#define SDC_RESERVE                     MCU_ADC2_3

#define SDC_DISCHARGED_V                    1.0f
#define SDC_CHARGED_V                       9.0f

/*============================================================================*/
/* ADC Common Settings (STM32 Internal)                                       */
/*============================================================================*/

// ADC resolution, use 12-bits for LV due to charge bucket sizing
#define ACULV_ADC_2_RESOLUTION_BITS          12U
#define ACULV_ADC_2_MAX_COUNTS               ((1U << ACULV_ADC_2_RESOLUTION_BITS) -1)
#define ACULV_ADC_2_MAX_NUMBER_CHANNELS      2U

#define ACULV_ADC_3_RESOLUTION_BITS          12U
#define ACULV_ADC_3_MAX_COUNTS               ((1U << ACULV_ADC_3_RESOLUTION_BITS) -1)
#define ACULV_ADC_3_MAX_NUMBER_CHANNELS      4U

#define ACULV_ADC_SCALING_FACTOR             8.064f

#define ACULV_ADC_VREF                       2.5f

extern const mcu_analog_config_t mcu_adc_config[MCU_MAX_ADC_COUNT];

#endif /* CONFIG_ACULV_CONFIG_H_ */
