/*
 * acu_lv_drv_imd.c
 *
 *  Created on: Apr 9, 2026
 *      Author: clayd
 */


#include "acu_lv_drv_imd.h"
#include "stm32h7xx_hal.h"
#include "cmsis_os2.h"

extern acu_lv_imd_t imd;

void acu_lv_drv_update_imd_state()
{

    if(HAL_GPIO_ReadPin(imd.hw.imd_ok_port, imd.hw.imd_ok_pin) == GPIO_PIN_SET)
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


acu_lv_status_t acu_lv_drv_reset_imd_latch()
{   
    // check that imd is ok before resetting relay
    if(imd.state == ACU_LV_IMD_OK)
    {
        HAL_GPIO_WritePin(imd.hw.latch_reset_port,imd.hw.imd_m_pin,GPIO_PIN_SET);
        osDelay(20);
        HAL_GPIO_WritePin(imd.hw.latch_reset_port,imd.hw.imd_m_pin,GPIO_PIN_RESET);

        return ACU_LV_OK;
    }

    return ACU_LV_ERROR;
}
