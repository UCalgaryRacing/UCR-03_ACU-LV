/*
 * acu_lv_svc_precharge.c
 *
 *  Created on: Apr 10, 2026
 *      Author: clayd
 */

#include "acu_lv_svc_precharge.h"
#include "acu_lv_svc_accu.h"
#include "acu_lv_svc_ts.h"

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
