/*
 * fast_task.c
 *
 *  Created on: Apr 7, 2026
 *      Author: clayd
 */
// test commit
#include <stdint.h>
#include <stdbool.h>
#include "cmsis_os2.h"
#include "acu_lv_config.h"

#include "fast_task.h"
#include "acu_lv_svc_accu.h"
#include "acu_lv_svc_ts.h"
#include "acu_lv_svc_shunt.h"
#include "acu_lv_svc_adbms6830.h"

#include "acu_lv_drv_debug_led.h"
#include "acu_lv_drv_imd.h"
#include "acu_lv_drv_analog.h"
#include "acu_lv_drv_air.h"
#include "acu_lv_drv_sdc.h"
#include "bms_drv_adbms6830.h"
#include "bms_drv_adbms6830_regs.h"
#include "aculv_drv_ds18b20.h"

#include "acu_lv_svc_adbms6830.h"
#include "bms_svc_thermistor.h"
#include "bms_svc_fault.h"
#include "bms_svc_can.h"

#include "rco_data.h"
#include "acu_data.h"
#include "acu_lv_svc_sdc.h"

#include "stm32h7xx_hal.h"
#include "acu_lv_config_pinout.h"

#include "acu_svc_can_route.h"

#include "bms_svc_cell_voltage.h"

const static uint32_t period = 10;
static uint32_t next_wake;

static float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC];
static float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC];

// initialization functions for the fast task
void fast_task_init()
{   
    // add code to turn on one of the three leds
    next_wake = osKernelGetTickCount();


    //bms_manager_init();


    osDelay(5000);
}

// code that runs in the infinite loop for the fast task
void fast_task_loop()
{
    next_wake += period;
    osDelayUntil(next_wake);

    bms_svc_acquire_all_cell_voltages(cell_voltages);
    bool bms_fault = bms_svc_check_all_cell_voltage_limits(cell_voltages);
    
    
    bms_svc_acquire_all_cell_temperatures(cell_temps);
    bms_fault |=  bms_svc_check_all_cell_temperature_limits(cell_temps);

    // code to reset imd and ams latch based on message from rear controller (rco), shouldn't need because it is handled in hardware
    if(rco_data_get_reset_button() == 1)
    {
        acu_lv_svc_reset_ams_latch();
        acu_lv_svc_reset_imd_latch();
    }
  
}
