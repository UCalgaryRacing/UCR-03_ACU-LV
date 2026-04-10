/*
 * acu_lv_drv_sdc.c
 *
 *  Created on: Apr 10, 2026
 *      Author: clayd
 */

#include "acu_lv_drv_sdc.h"
#include "stm32h7xx_hal.h"

extern acu_lv_sdc_t sdc;

void acu_lv_drv_sdc_init()
{
    // write the default config for the shutdown
    HAL_GPIO_WritePin(sdc.hw.imd_latch_reset_port, sdc.hw.imd_latch_reset_pin, sdc.hw.imd_latch_state);
    HAL_GPIO_WritePin(sdc.hw.ams_latch_reset_port, sdc.hw.ams_latch_reset_pin, sdc.hw.ams_latch_state);
    HAL_GPIO_WritePin(sdc.hw.ams_ok_port, sdc.hw.ams_ok_pin, sdc.hw.ams_ok_state);
}

void acu_lv_drv_set_imd_latch()
{   
    sdc.hw.imd_latch_state = GPIO_PIN_SET;
    HAL_GPIO_WritePin(sdc.hw.imd_latch_reset_port, sdc.hw.imd_latch_reset_pin, sdc.hw.imd_latch_state);
}
void acu_lv_drv_reset_imd_latch()
{
    sdc.hw.imd_latch_state = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(sdc.hw.imd_latch_reset_port, sdc.hw.imd_latch_reset_pin, sdc.hw.imd_latch_state);
}

void acu_lv_drv_set_ams_latch()
{
    sdc.hw.ams_latch_state = GPIO_PIN_SET;
    HAL_GPIO_WritePin(sdc.hw.ams_latch_reset_port, sdc.hw.ams_latch_reset_pin, sdc.hw.ams_latch_state);
}
void acu_lv_drv_reset_ams_latch()
{
    sdc.hw.ams_latch_state = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(sdc.hw.ams_latch_reset_port, sdc.hw.ams_latch_reset_pin, sdc.hw.ams_latch_state);
}

void acu_lv_drv_set_ams_ok()
{
    sdc.hw.ams_ok_state = GPIO_PIN_SET;
    HAL_GPIO_WritePin(sdc.hw.ams_ok_port, sdc.hw.ams_ok_pin, sdc.hw.ams_ok_state);
}
void acu_lv_drv_reset_ams_ok()
{
    sdc.hw.ams_ok_state = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(sdc.hw.ams_ok_port, sdc.hw.ams_ok_pin, sdc.hw.ams_ok_state);
}

