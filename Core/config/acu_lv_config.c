/**
 * Configuration for the entire ACU LV
 * 
 */

#include "acu_lv_config.h"
#include "acu_lv_config_pinout.h"

float shunt_data;

acu_lv_pack_current_t current= {
    .hw = {
        .status_port = SHUNT_STATUS_PORT,
        .status_pin = SHUNT_STATUS_PIN,
        .dma_started = false,
        .filter_handle = CURRENT_SHUNT_FILTER_HANDLE
    },
    .data = &shunt_data
};
