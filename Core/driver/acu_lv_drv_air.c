/*
 * acu_lv_drv_air.c
 *
 *  Created on: Apr 9, 2026
 *      Author: clayd
 */

#include "acu_lv_drv_air.h"

extern acu_lv_air_t air;

void acu_lv_drv_air_init()
{
    air.air_hw.neg_state = GPIO_PIN_RESET;
    air.air_hw.pos_state = GPIO_PIN_RESET;

    HAL_GPIO_WritePin(air.air_hw.air_neg_port, air.air_hw.air_neg_pin,air.air_hw.neg_state);

    HAL_GPIO_WritePin(air.air_hw.air_pos_port, air.air_hw.air_pos_pin,air.air_hw.pos_state);
}

acu_lv_status_t acu_lv_drv_update_sdc_reserve();
acu_lv_status_t acu_lv_drv_open_air();
acu_lv_status_t acu_lv_drv_close_air_pos();
acu_lv_status_t acu_lv_drv_close_air_neg();
