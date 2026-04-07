/*
 * fast_task.c
 *
 *  Created on: Apr 7, 2026
 *      Author: clayd
 */

#include <stdint.h>
#include "fast_task.h"
#include "acu_lv_svc_accu.h"
#include "acu_lv_svc_ts.h"
#include "cmsis_os2.h"

const static uint32_t period = 10;
static uint32_t next_wake;

// initialization functions for the fast task
void fast_task_init()
{   
    // add code to turn on one of the three leds
    next_wake = osKernelGetTickCount();

    // start the conversion for measuring accumulator and tractive voltage
    acu_lv_svc_start_ts_filter();
    acu_lv_svc_start_accu_filter();
}

// code that runs in the infinite loop for the fast task
void fast_task_loop()
{
    next_wake += period;
    osDelayUntil(next_wake);

    // update the values for tractive and accumulator voltage
    acu_lv_svc_update_ts_voltage();
    acu_lv_svc_update_accu_voltage();
}
