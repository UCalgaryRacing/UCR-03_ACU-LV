#ifndef CONFIG_ACULV_CONFIG_PINOUT_H_
#define CONFIG_ACULV_CONFIG_PINOUT_H_

#include "stm32h7xx_hal.h"

/*============================================================================*/
/* ADC                                                                        */
/*============================================================================*/

// ADCs for monitoring where in SDC the voltage is dropped (many in series)

// TODO determine how to define the dma buffers for the ADCs
// could copy TCU and have a large array to support all ADC channels
// or change it to be one array per ADC and use the defines for index
// that way would have to have define to map the name to the ADC array

// Adcs handles SDC monitering and power for AIR coils
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;

#define ACULV_ADC_2_HANDLE (&hadc2)
#define ACULV_ADC_3_HANDLE (&hadc3)

//rank # - 1 = index # 
//rank 1 on adc2, channel 5
#define MCU_ADC2_5_BUFFER_INDEX         0U
#define MCU_ADC2_5_BUFFER_NUMBER        1U

//rank 2 on adc2, channel 3
#define MCU_ADC2_3_BUFFER_INDEX         1U
#define MCU_ADC2_3_BUFFER_NUMBER        1U

//rank 1 on adc3, channel 3
#define MCU_ADC3_3_BUFFER_INDEX         0U
#define MCU_ADC3_3_BUFFER_NUMBER        2U

//rank 2 on adc3, channel 5
#define MCU_ADC3_5_BUFFER_INDEX         1U
#define MCU_ADC3_5_BUFFER_NUMBER        2U

//rank 3 on adc3, channel 2
#define MCU_ADC3_2_BUFFER_INDEX         2U
#define MCU_ADC3_2_BUFFER_NUMBER        2U

//rank 4 on adc3, channel 4
#define MCU_ADC3_4_BUFFER_INDEX         3U
#define MCU_ADC3_4_BUFFER_NUMBER        2U

/*============================================================================*/
/* BMS (fault and latch for relays in SDC)                                     */
/*============================================================================*/

#define BMS_OK_PORT GPIOA
#define BMS_OK_PIN GPIO_PIN_5

#define BMS_LATCH_EN_PORT GPIOH
#define BMS_LATCH_EN_PIN GPIO_PIN_4

/*============================================================================*/
/* IMD  (fault and latch for relays in SDC)                                   */
/*============================================================================*/

#define IMD_OK_PORT GPIOJ
#define IMD_OK_PIN GPIO_PIN_2

#define IMD_M_PORT GPIOA
#define IMD_M_PIN GPIO_PIN_3

#define IMD_LATCH_EN_PORT GPIOH
#define IMD_LATCH_EN_PIN GPIO_PIN_3

/*============================================================================*/
/* Debug LEDs                                                                 */
/*============================================================================*/

#define LED_1_PORT GPIOB
#define LED_1_PIN GPIO_PIN_8

#define LED_2_PORT GPIOB
#define LED_2_PIN GPIO_PIN_9

#define LED_3_PORT GPIOE
#define LED_3_PIN GPIO_PIN_3

#endif /* CONFIG_ACULV_CONFIG_PINOUT_H_ */
