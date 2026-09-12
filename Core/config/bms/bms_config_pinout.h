#ifndef CONFIG_BMS_CONFIG_PINOUT_H_
#define CONFIG_BMS_CONFIG_PINOUT_H_

#include "stm32h7xx_hal.h"

/*============================================================================*/
/* BMS1 ISO SPI                                                               */
/*============================================================================*/

extern SPI_HandleTypeDef hspi5;

#define ADBMS_1_SPI_HANDLE (&hspi5)

#define ADBMS_1_CSN_PORT GPIOD
#define ADBMS_1_CSN_PIN GPIO_PIN_9

#define ADBMS_1_WAKE_PORT GPIOD
#define ADBMS_1_WAKE_PIN GPIO_PIN_14

#define ADMBS_1_INTR_PORT GPIOD
#define ADBMS_1_INTR_PIN GPIO_PIN_13


/*============================================================================*/
/* BMS2 ISO SPI                                                               */
/*============================================================================*/

extern SPI_HandleTypeDef hspi2;
//debug
// #define ADBMS_2_SPI_HANDLE (&hspi5)

// #define ADBMS_2_CSN_PORT GPIOD
// #define ADBMS_2_CSN_PIN GPIO_PIN_9 

// #define ADBMS_2_WAKE_PORT GPIOD
// #define ADBMS_2_WAKE_PIN GPIO_PIN_14

// #define ADMBS_2_INTR_PORT GPIOD
// #define ADBMS_2_INTR_PIN GPIO_PIN_13

// normal
// extern SPI_HandleTypeDef hspi2;
// #define ADBMS_2_SPI_HANDLE (&hspi2)

// #define ADBMS_2_CSN_PORT GPIOD
// #define ADBMS_2_CSN_PIN GPIO_PIN_11

// #define ADBMS_2_WAKE_PORT GPIOD
// #define ADBMS_2_WAKE_PIN GPIO_PIN_8

// #define ADMBS_2_INTR_PORT GPIOD
// #define ADBMS_2_INTR_PIN GPIO_PIN_10

/*============================================================================*/
/* DS18B20                                                                    */
/*============================================================================*/
extern UART_HandleTypeDef huart4;

#define DS18B20_UART_HANDLE (&huart4)

#define DS18B20_VDD_EN_PORT GPIOD
#define DS18B20_VDD_EN_PIN GPIO_PIN_12

#define DS18B20_WEAK_PULL_UP_PORT GPIOI
#define DS18B20_WEAK_PULL_UP_PIN GPIO_PIN_0

#endif /*CONFIG_BMS_CONFIG_PINOUT_H_*/
