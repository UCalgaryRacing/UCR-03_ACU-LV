/**
 * Configuration for the entire ACU LV
 * 
 */

#include "acu_lv_config.h"
#include "acu_lv_config_pinout.h"
#include "stm32h7xx_hal.h"

/*============================================================================*/
/* Shunt, TS and ACCU Measurement Configuration */
/*============================================================================*/

float g_shunt_data_float;
int32_t g_shunt_data_raw;

acu_lv_pack_measurement_t pack_current= {
    .hw = {
        .status_port = SHUNT_STATUS_PORT,
        .status_pin = SHUNT_STATUS_PIN,
        .dma_started = false,
        .filter_handle = CURRENT_SHUNT_FILTER_HANDLE
    },
    .settings = {
        .measurement_type = ACU_LV_MEASUREMENT_PACK_CURRENT,
        .scaling_factor = ACU_LV_SHUNT_SCALING_FACTOR,
        .valid_max = 10,
        .valid_min = 0
    },
    .data = &g_shunt_data_float,
    .raw_data = &g_shunt_data_raw
};

float g_accu_voltage_float;
int32_t g_accu_voltage_raw;

acu_lv_pack_measurement_t accu_voltage = {
    .hw = {
        .status_port = ACCU_VOLTAGE_STATUS_PORT,
        .status_pin = ACCU_VOLTAGE_STATUS_PIN,
        .dma_started = false,
        .filter_handle = ACCU_VOLTAGE_FILTER
    },
    .settings = {
        .measurement_type = ACU_LV_MEASUREMENT_ACCU_VOLTAGE,
        .scaling_factor = ACU_LV_ACCU_SCALING_FACTOR,
        .valid_max = ACCU_VOLTAGE_MAX_V,
        .valid_min = ACCU_VOLTAGE_MIN_V
    },
    .data = &g_accu_voltage_float,
    .raw_data = &g_accu_voltage_raw
};

float g_ts_data_float;
int32_t g_ts_data_raw;

acu_lv_pack_measurement_t ts_voltage = {
    .hw = {
        .status_port = TS_VOLTAGE_STATUS_PORT,
        .status_pin = TS_VOLTAGE_STATUS_PIN,
        .dma_started = false,
        .filter_handle = TS_VOLTAGE_FILTER
    },
    .settings = {
        .measurement_type = ACU_LV_MEASUREMENT_TS_VOLTAGE,
        .scaling_factor = ACU_LV_TS_SCALING_FACTOR,
        .valid_min = 0,
        .valid_max = ACCU_VOLTAGE_MAX_V //should this be 90% of acu?
    },
    .data = &g_ts_data_float,
    .raw_data = &g_ts_data_raw
};

/*============================================================================*/
/* Debug LEDs*/
/*============================================================================*/

debug_led_t blue_led = {
    .port = LED_1_PORT,
    .pin = LED_1_PIN,
    .state = GPIO_PIN_RESET
};

debug_led_t green_led = {
    .port = LED_2_PORT,
    .pin = LED_2_PIN,
    .state = GPIO_PIN_RESET
};

debug_led_t red_led = {
    .port = LED_3_PORT,
    .pin = LED_3_PIN,
    .state = GPIO_PIN_RESET
};
