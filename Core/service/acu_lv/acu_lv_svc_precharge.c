/*
 * acu_lv_svc_precharge.c
 *
 *  Created on: Apr 10, 2026
 *      Author: clayd
 */

#include <stdint.h>
#include "cmsis_os2.h"
#include "acu_lv_config.h"
#include "acu_lv_svc_precharge.h"
#include "acu_lv_svc_accu.h"
#include "acu_lv_svc_ts.h"

static uint32_t precharge_start_time, current_time;

bool acu_lv_svc_check_precharge_done()
{   
    if(acu_lv_svc_get_accu_voltage() > acu_lv_svc_get_accu_min())
    {
        if((acu_lv_svc_get_accu_voltage() * 0.9f) <= acu_lv_svc_get_ts_voltage())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    
}

status_t acu_lv_svc_check_precharge_timeout()
{
    current_time = osKernelGetTickCount();
    if((current_time - precharge_start_time) > ACU_LV_PRECHARGE_TIMEOUT)
    {
        return ERROR_GENERAL;
    }
    return OK;
}

void acu_lv_svc_start_precharge_timer()
{
    precharge_start_time = osKernelGetTickCount();
}
