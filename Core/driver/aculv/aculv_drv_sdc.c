#include "aculv_drv_sdc.h"
#include "stm32h7xx_hal.h"
#include "aculv_config_pinout.h"

/*============================================================================*/
/* IMD                                                                        */
/*============================================================================*/

void aculv_drv_set_imd_latch_en(bool enable) 
{
    HAL_GPIO_WritePin(IMD_LATCH_EN_PORT, IMD_LATCH_EN_PIN, enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}


/*============================================================================*/
/* BMS                                                                        */
/*============================================================================*/

void aculv_drv_set_bms_latch_en(bool enable) 
{
    HAL_GPIO_WritePin(BMS_LATCH_EN_PORT, BMS_LATCH_EN_PIN, enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void aculv_drv_set_bms_ok(bool enable)
{
    HAL_GPIO_WritePin(BMS_OK_PORT, BMS_OK_PIN, enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
