/*
 * acu_lv_sdc.c
 *
 *  Created on: Apr 10, 2026
 *      Author: clayd
 */

#include "acu_lv_drv_sdc.h"
#include "acu_lv_svc_sdc.h"

extern acu_lv_sdc_t sdc;

void acu_lv_svc_open_sdc()
{   
    acu_lv_drv_reset_imd_latch();
    acu_lv_drv_reset_ams_latch();
    acu_lv_drv_reset_ams_ok();
    sdc.shutdown_closed = false;
}
void acu_lv_svc_close_sdc()
{
    acu_lv_drv_set_imd_latch();
    acu_lv_drv_set_ams_latch();
    acu_lv_drv_set_ams_ok();
    sdc.shutdown_closed = true;
}
