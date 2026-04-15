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
#include "acu_lv_svc_adbms6830.h"

#include "acu_lv_drv_debug_led.h"
#include "acu_lv_drv_imd.h"
#include "acu_lv_drv_analog.h"
#include "acu_lv_drv_air.h"
#include "acu_lv_drv_sdc.h"
#include "acu_lv_drv_adbms6830.h"

#include "bms_svc_thermistor.h"

#include "stm32h7xx_hal.h"

const static uint32_t period = 10;
static uint32_t next_wake;

extern debug_led_t blue_led;
extern analog_hw_t adc_2_hw, adc_3_hw;

extern uint16_t g_adc_2_dma_buffer[ACU_LV_ADC_2_MAX_NUMBER_CHANNELS];
extern uint16_t g_adc_3_dma_buffer[ACU_LV_ADC_3_MAX_NUMBER_CHANNELS];

extern volatile uint8_t adc_dma;

extern analog_adc_context_t adc_2_context;
extern ADC_HandleTypeDef hadc2;

uint32_t g_test_buffer;
int g_result;
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
//    acu_lv_drv_adc_init(adc_2_hw.adc_context);
    acu_lv_drv_adc_init(adc_3_hw.adc_context);

    //start the DMA for ADCs
//    acu_lv_drv_adc_start_dma(&adc_2_hw, &g_test_buffer);
    // acu_lv_drv_adc_start_dma(&adc_3_hw,(uint32_t*)g_adc_2_dma_buffer);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
    HAL_ADC_Start_DMA(&hadc2,&g_test_buffer,1);

    // initialize airs, should make svc layer do it eventually
    acu_lv_drv_air_init();

    // initialize sdc
    acu_lv_drv_sdc_init();

    bms_manager_init();

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

    acu_lv_drv_update_imd_state();

    // update sdc reserve
    acu_lv_drv_update_sdc_reserve();
    
    if(adc_dma == 1)
    {
    	adc_dma = 0;
    }

    g_result=  voltage_acquisition_sample();


    bms_svc_acquire_thermistor_temps();

    bms_svc_admbs_toggle_mux(ADBMS_GPO_PIN_1);

    osDelay(500);

    acu_lv_drv_toggle_led(&blue_led);

}
