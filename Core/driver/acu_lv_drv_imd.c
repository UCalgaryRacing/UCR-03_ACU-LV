/*
 * acu_lv_drv_imd.c
 *
 *  Created on: Apr 9, 2026
 *      Author: clayd
 */


#include "acu_lv_drv_imd.h"
#include "stm32h7xx_hal.h"

extern acu_lv_imd_t imd;

void acu_lv_drv_update_imd_state()
{
    // check IMD polarity
    if(HAL_GPIO_ReadPin(imd.hw.imd_ok_port, imd.hw.imd_ok_pin) == GPIO_PIN_RESET)
    {
        imd.state  = ACU_LV_IMD_FAULT;
    }
    else
    {
        imd.state = ACU_LV_IMD_OK;
    }
}

acu_lv_imd_state_t acu_lv_drv_get_imd_state()
{
    return imd.state;
}
