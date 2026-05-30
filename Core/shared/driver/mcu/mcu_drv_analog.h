#ifndef DRIVER_MCU_ANALOG_H_
#define DRIVER_MCU_ANALOG_H_

#include <stdint.h>
#include <stdbool.h>
#include "com_typ_common.h"
#include "stm32h7xx_hal.h"
#include "mcu_config_analog.h"

#define MCU_MAX_ADC_CHANNELS 16U

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/
status_t mcu_drv_analog_init(const analog_hw_t *hw);
status_t mcu_drv_analog_driver_init(void); // fix
/*============================================================================*/
/* Start ADC                                                             */
/*============================================================================*/
status_t mcu_drv_analog_start_adc(const analog_hw_t *hw);

/*============================================================================*/
/* Raw ADC Access                                                             */
/*============================================================================*/

status_t mcu_drv_analog_read_raw(const analog_hw_t *hw, uint16_t *adc_value);

#endif /* DRIVER_MCU_ANALOG_H_ */
