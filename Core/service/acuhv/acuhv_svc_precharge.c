#include "acuhv_svc_precharge.h"
#include "acu_data.h"
#include "stm32h7xx_hal.h"
#include <stdint.h>
#include "aculv_svc_sdc.h"


static uint32_t g_precharge_time_start;

void acuhv_svc_precharge_start(void)
{
    g_precharge_time_start = HAL_GetTick();
}

void acuhv_svc_precharge_update_fault_timeout(void)
{
    uint32_t precharge_time_elapsed = HAL_GetTick() - g_precharge_time_start;
    if (precharge_time_elapsed >= ACUHV_PRECHARGE_MAX_DURATION_MS)
    {
        acu_data_set_precharge_timeout_fault_status(true);
        aculv_svc_set_bms_ok(false);
    }
}