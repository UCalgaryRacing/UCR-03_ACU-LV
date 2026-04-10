/*
 * medium_task.c
 *
 *  Created on: Apr 7, 2026
 *      Author: clayd
 */

#include "medium_task.h"
#include "cmsis_os2.h"
#include "acu_lv_drv_debug_led.h"
#include "acu_lv_drv_imd.h"
#include "acu_lv_drv_analog.h"
#include "acu_lv_config.h"

const static uint32_t period = 50;
static uint32_t next_wake;

extern debug_led_t green_led;
extern analog_hw_t adc_2_hw, adc_3_hw;

void medium_task_init()
{
    next_wake = osKernelGetTickCount();

    acu_lv_drv_turn_on_led(&green_led);

    // calibrate both the ADCs
    acu_lv_drv_adc_init(adc_2_hw.adc_context);
    acu_lv_drv_adc_init(adc_3_hw.adc_context);

    //start the DMA for ADCs
    acu_lv_drv_adc_start_dma(&adc_2_hw);
    acu_lv_drv_adc_start_dma(&adc_3_hw);
}
void medium_task_loop()
{
    next_wake += period;
    osDelayUntil(next_wake);
    acu_lv_drv_toggle_led(&green_led);

    acu_lv_drv_update_imd_state();


//    acu_lv_drv_turn_off_led(&green_led);
}

