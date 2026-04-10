/*
 * fast_task.c
 *
 *  Created on: Apr 7, 2026
 *      Author: clayd
 */

#include <stdint.h>
#include "cmsis_os2.h"
#include "acu_lv_config.h"

#include "fast_task.h"
#include "acu_lv_svc_accu.h"
#include "acu_lv_svc_ts.h"
#include "acu_lv_svc_shunt.h"

#include "acu_lv_drv_debug_led.h"
#include "acu_lv_drv_imd.h"
#include "acu_lv_drv_analog.h"
#include "acu_lv_drv_air.h"
#include "acu_lv_drv_sdc.h"

const static uint32_t period = 10;
static uint32_t next_wake;

extern debug_led_t blue_led;
extern analog_hw_t adc_2_hw, adc_3_hw;

// initialization functions for the fast task
void fast_task_init()
{   
    // add code to turn on one of the three leds
    next_wake = osKernelGetTickCount();

    // start the conversion for measuring accumulator and tractive voltage
    acu_lv_svc_start_ts_filter();
    acu_lv_svc_start_accu_filter();
    acu_lv_svc_start_shunt_filter();
    
    // calibrate both the ADCs
    acu_lv_drv_adc_init(adc_2_hw.adc_context);
    acu_lv_drv_adc_init(adc_3_hw.adc_context);

    //start the DMA for ADCs
    acu_lv_drv_adc_start_dma(&adc_2_hw);
    acu_lv_drv_adc_start_dma(&adc_3_hw);

    // initialize airs, should make svc layer do it eventually
    acu_lv_drv_air_init();

    // initialize sdc
    acu_lv_drv_sdc_init();

    acu_lv_drv_turn_on_led(&blue_led);
}

// code that runs in the infinite loop for the fast task
void fast_task_loop()
{
    next_wake += period;
    osDelayUntil(next_wake);
    

    // update the values for tractive and accumulator voltage
    acu_lv_svc_update_ts_voltage();
    acu_lv_svc_update_accu_voltage();
    acu_lv_svc_update_shunt();
    
    acu_lv_drv_toggle_led(&blue_led);
}
