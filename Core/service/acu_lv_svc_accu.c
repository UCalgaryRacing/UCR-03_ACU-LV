/*
 * acu_lv_svc_acu.c
 *
 *  Created on: Apr 7, 2026
 *      Author: clayd
 */

#include "acu_lv_config.h"
#include "acu_lv_svc_accu.h"
#include "acu_lv_drv_dfsdm.h"

extern acu_lv_pack_measurement_t accu_voltage;

acu_lv_status_t acu_lv_svc_update_accu_voltage()
{
    if(accu_voltage.hw.dma_started == true)
    {
        *accu_voltage.data = ((float)*accu_voltage.raw_data)* accu_voltage.settings.scaling_factor;
    }
    else
    {
        return ACU_LV_ERROR;
    }
    return ACU_LV_OK;
}

float acu_lv_svc_get_acu_voltage()
{
    return *accu_voltage.data;
}

acu_lv_status_t acu_lv_svc_start_accu_filter()
{
    acu_lv_status_t status;
    status = acu_lv_start_DFSDM_filter(accu_voltage.hw.filter_handle, accu_voltage.raw_data);
    return status;
}

acu_lv_status_t acu_lv_svc_stop_accu_filter()
{
    acu_lv_status_t status;
    status = acu_lv_stop_DFSDM_filter(accu_voltage.hw.filter_handle);
    return status;
}
