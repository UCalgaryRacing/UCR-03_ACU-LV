#include "acuhv_drv_air.h"
#include "stm32h7xx_hal.h"
#include "acuhv_config_pinout.h"

void acuhv_drv_air_close_air_pos(bool close)
{
    HAL_GPIO_WritePin(AIR_POS_EN_PORT, AIR_POS_EN_PIN, close ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void acuhv_drv_air_close_air_neg(bool close)
{
    HAL_GPIO_WritePin(AIR_NEG_EN_PORT, AIR_NEG_EN_PIN, close ? GPIO_PIN_SET : GPIO_PIN_RESET);
}