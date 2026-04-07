/*
 * acu_lv_svc_ts.c
 *
 *  Created on: Apr 7, 2026
 *      Author: clayd
 */

#include "acu_lv_config.h" 
#include "acu_lv_svc_ts.h"
#include "acu_lv_drv_dfsdm.h"

extern acu_lv_pack_measurement_t ts_voltage;

acu_lv_status_t acu_lv_svc_update_ts_voltage()
{
    if(ts_voltage.hw.dma_started == true)
    {
        *ts_voltage.data = ((float)*ts_voltage.raw_data)* ts_voltage.settings.scaling_factor;
    }
    else
    {
        return ACU_LV_ERROR;
    }
    return ACU_LV_OK;
}

float acu_lv_svc_get_ts_voltage()
{
    return * ts_voltage.data;
}

acu_lv_status_t acu_lv_svc_start_ts_filter()
{
    acu_lv_status_t status;
    status = acu_lv_start_DFSDM_filter(ts_voltage.hw.filter_handle, ts_voltage.raw_data);
    return status;
}

acu_lv_status_t acu_lv_svc_stop_ts_filter()
{   
    acu_lv_status_t status;
    status = acu_lv_stop_DFSDM_filter(ts_voltage.hw.filter_handle);
    return status;
}
