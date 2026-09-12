#ifndef CONFIG_ACUHV_CONFIG_PINOUT_H_
#define CONFIG_ACUHV_CONFIG_PINOUT_H_

#include "stm32h7xx_hal.h"

/*============================================================================*/
/* DFSDM Buffer Mapping                                                       */
/*============================================================================*/

#define ACUHV_DFSDM1_DATIN2_BUFFER_NUMBER  0U          // PE7 TS Data
#define ACUHV_DFSDM1_DATIN4_BUFFER_NUMBER  1U          // PE10 ACCU Data
#define ACUHV_DFSDM1_DATIN6_BUFFER_NUMBER  2U          // PF13 Shunt Data

/*============================================================================*/
/* TS Voltage Measurement  (AMC33X6XX)                                        */
/*============================================================================*/

extern DFSDM_Filter_HandleTypeDef hdfsdm1_filter0;
#define TS_VOLTAGE_FILTER_HANDLE    (&hdfsdm1_filter0)

#define TS_VOLTAGE_STATUS_PORT GPIOG
#define TS_VOLTAGE_STATUS_PIN GPIO_PIN_1

/*============================================================================*/
/* ACUHV Pack Voltage Measurement (AMC33X6XX)                                 */
/*============================================================================*/

extern DFSDM_Filter_HandleTypeDef hdfsdm1_filter1;
#define BATT_VOLTAGE_FILTER_HANDLE  (&hdfsdm1_filter1)

#define BATT_VOLTAGE_STATUS_PORT GPIOF
#define BATT_VOLTAGE_STATUS_PIN GPIO_PIN_14

/*============================================================================*/
/* Current Shunt (AMC33X6XX)                                                  */
/*============================================================================*/

extern DFSDM_Filter_HandleTypeDef hdfsdm1_filter2;
#define BATT_CURRENT_FILTER_HANDLE (&hdfsdm1_filter2)

#define BATT_CURRENT_STATUS_PORT GPIOG
#define BATT_CURRENT_STATUS_PIN GPIO_PIN_0

/*============================================================================*/
/* AIR                                                                        */
/*============================================================================*/

#define AIR_NEG_EN_PORT GPIOJ
#define AIR_NEG_EN_PIN GPIO_PIN_3

#define AIR_POS_EN_PORT GPIOB
#define AIR_POS_EN_PIN GPIO_PIN_0

/*============================================================================*/
/* IMD                                                                        */
/*============================================================================*/

// IMD_OK cannot be written to (hardwired to IMD relay). Can read for data/logging purposes.
#define IMD_OK_PORT GPIOJ
#define IMD_OK_PIN GPIO_PIN_2

#define IMD_M_PORT GPIOA
#define IMD_M_PIN GPIO_PIN_3



#endif /*CONFIG_ACUHV_CONFIG_PINOUT_H_*/
