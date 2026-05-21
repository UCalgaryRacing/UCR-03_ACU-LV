/*
 * acu_lv_config.h
 *
 * System configuration parameters for the accumulator.
 * All tunable values should be defined here for easy adjustment.
 *
 *  Created on: Mar 23, 2026
 *      Author: f-dunnwolbaum
 */

#ifndef CONFIG_ACU_LV_CONFIG_H_
#define CONFIG_ACU_LV_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32h7xx_hal.h"

/*============================================================================*/
/* ADC Common Settings                                                        */
/*============================================================================*/

// ADC resolution, use 12-bits for LV due to charge bucket sizing
#define ACU_LV_ADC_2_RESOLUTION_BITS 12U
#define ACU_LV_ADC_2_MAX_COUNTS ((1U << ACU_LV_ADC_2_RESOLUTION_BITS) -1)
#define ACU_LV_ADC_2_MAX_NUMBER_CHANNELS 2U

#define ACU_LV_ADC_2_RESOLUTION_BITS 12U
#define ACU_LV_ADC_3_MAX_COUNTS ((1U << ACU_LV_ADC_2_RESOLUTION_BITS) -1)
#define ACU_LV_ADC_3_MAX_NUMBER_CHANNELS 4U

#define ACU_LV_ADC_SCALING_FACTOR 8.064f

#define ACU_LV_ADC_VREF                    2.5f

/*============================================================================*/
/* Accumulator Voltage Configuration                                          */
/*============================================================================*/

// Scaling factor for tractive and accumulator
// determined by using a known voltage and averaging the raw values
#define ACU_LV_ACCU_SCALING_FACTOR 0.00000126344f
#define ACU_LV_TS_SCALING_FACTOR 0.00032845893948625697f

// Precharge completion threshold (TS voltage must be >= this fraction of pack)
#define ACCU_PRECHARGE_THRESHOLD            0.90f

// Expected pack voltage range (V)
#define ACCU_VOLTAGE_MIN_V                  325.0f
#define ACCU_VOLTAGE_MAX_V                  546.0f

// timeout for precharge based on os tick counts
#define ACU_LV_PRECHARGE_TIMEOUT 3000

/*============================================================================*/
/* Current Shunt Configuration                                          */
/*============================================================================*/

// shunt scaling factor
#define ACU_LV_SHUNT_SCALING_FACTOR 0.00015422103651609282f

// Threshold for considering current as "idle" (A)
#define CURRENT_IDLE_THRESHOLD_A            2.0f

// Expected current range (A)
#define CURRENT_MAX_DISCHARGE_A             300.0f
#define CURRENT_MAX_REGEN_A                 100.0f

#define CURRENT_SHUNT_RESISTANCE 0.0002f

/*============================================================================*/
/* SOC Estimation Configuration                                               */
/*============================================================================*/

// Pack capacity in amp-hours (Ah)
#define PACK_CAPACITY_AH                    15.0f

// Pack nominal energy in watt-hours (Wh)
#define PACK_ENERGY_WH                      7000.0f

// Coulomb counting efficiency (accounts for losses)
#define COULOMB_EFFICIENCY                  0.98f

// SOC bounds
#define SOC_MIN_PERCENT                     0.0f
#define SOC_MAX_PERCENT                     100.0f

/*============================================================================*/
/* Power Limiting Configuration                                               */
/*============================================================================*/

// Maximum continuous discharge power (kW)
#define POWER_LIMIT_DISCHARGE_KW            80.0f

// SOC threshold for power derating
#define SOC_LOW_THRESHOLD                   10.0f   // Start derating discharge below this

// Temperature thresholds for power derating (°C)
#define TEMP_LOW_THRESHOLD_C                0.0f    // Start derating below this
#define TEMP_HIGH_THRESHOLD_C               45.0f   // Start derating above this
#define TEMP_CRITICAL_HIGH_C                55.0f   // Zero power above this



/*============================================================================*/
/* System States                                                          */
/*============================================================================*/

typedef enum
{
    ACU_LV_OK = 0U,
    ACU_LV_ERROR
} acu_lv_status_t;

/*============================================================================*/
/* Pack Measurement Structure                                                 */
/*============================================================================*/

typedef enum
{
    ACU_LV_MEASUREMENT_TEMP = 0U,
    ACU_LV_MEASUREMENT_PACK_CURRENT,
    ACU_LV_MEASUREMENT_TS_VOLTAGE,
    ACU_LV_MEASUREMENT_ACCU_VOLTAGE
} acu_lv_measurement_type_t;

typedef struct
{   
    acu_lv_measurement_type_t measurement_type; 
    float valid_min; // minimum valid value for a given sensor, if below then trigger a fault
    float valid_max; //max valid value, if above then trigger fault
    float scaling_factor; // scaling factor if voltage divider is used
} acu_lv_measurement_setting_t;

/*============================================================================*/
/* ACM33X6XX Settings and Configuration                                       */
/*============================================================================*/

typedef struct
{
    GPIO_TypeDef * status_port;
    uint16_t status_pin;
    DFSDM_Filter_HandleTypeDef *filter_handle;
    bool dma_started;
} acm33x6xx_hw_t;

typedef struct
{
    acm33x6xx_hw_t hw;
    acu_lv_measurement_setting_t settings;
    float *const data;
    int32_t *const raw_data;
} acu_lv_pack_measurement_t;

/*============================================================================*/
/* Cell Structure                                                             */
/*============================================================================*/
// add stuff to use this, TODO after hybrid
// typedef struct
// {
//     adbms6830_hw_t hw;
//     const uint16_t cell_id;
//     float cell_voltage;
//     uint16_t voltage_raw; // raw adc value from reading cell voltage
// } acu_lv_cell_voltage_t;

// typedef struct
// {
//     adbms6830_hw_t hw;
//     const uint16_t cell_id;
//     float cell_temp;
//     uint16_t temp_raw;
// } acu_lv_cell_temp_t;

/*============================================================================*/
/* Segment Structure                                                          */
/*============================================================================*/

// typedef struct
// {
//     adbms6830_hw_t *adbms_slaves[NUMBER_ADBMS_PER_SEGMENT]; 
//     acu_lv_cell_voltage_t *cell_voltages[NUMBER_ADBMS_CELLS_PER_SEG];
//     acu_lv_cell_temp_t *cell_temps[NUMBER_THERMS_PER_SEG];
// } acu_lv_segment_t;

/*============================================================================*/
/* ADC Structure                                                              */
/*============================================================================*/

typedef struct {
    ADC_HandleTypeDef *adc_handle;
    float adc_vref;
    float adc_scaling; // all adcs on the LV have the same scaling factor
    uint16_t adc_max;  
    bool calibrated;
    bool dma_started;
    uint8_t adc_channels;
} analog_adc_context_t;

typedef struct
{
    analog_adc_context_t *adc_context;
    uint16_t * adc_buffer;
} analog_hw_t;

/*============================================================================*/
/* AIRs                                                            */
/*============================================================================*/

typedef struct
{
    GPIO_TypeDef * air_pos_port;
    uint16_t air_pos_pin;
    GPIO_PinState pos_state;

    GPIO_TypeDef * air_neg_port;
    uint16_t air_neg_pin;
    GPIO_PinState neg_state;
} acu_lv_air_hw_t;

typedef struct 
{
    acu_lv_air_hw_t air_hw;
    analog_hw_t *analog_hw;
    float sdc_reserve;
    const uint8_t adc_buffer_index;
    bool air_closed;
} acu_lv_air_t;

/*============================================================================*/
/* IMD                                                            */
/*============================================================================*/

typedef enum
{
    ACU_LV_IMD_FAULT = 0U,
    ACU_LV_IMD_OK
} acu_lv_imd_state_t;

// add timer for measuring m pulse width
typedef struct
{
    GPIO_TypeDef * imd_ok_port;
    uint16_t imd_ok_pin;
    GPIO_TypeDef * imd_m_port;
    uint16_t imd_m_pin;
} acu_lv_imd_hw_t;

typedef struct
{
    acu_lv_imd_hw_t hw;
    acu_lv_imd_state_t state;
} acu_lv_imd_t;

typedef struct
{
    GPIO_TypeDef * imd_latch_reset_port;
    uint16_t imd_latch_reset_pin;
    GPIO_PinState imd_latch_state;

    GPIO_TypeDef * ams_latch_reset_port;
    uint16_t ams_latch_reset_pin;
    GPIO_PinState ams_latch_state;

    GPIO_TypeDef * ams_ok_port;
    uint16_t ams_ok_pin;
    GPIO_PinState ams_ok_state;
} acu_lv_sdc_hw_t;

typedef struct 
{
    acu_lv_sdc_hw_t hw;
    bool shutdown_closed;
} acu_lv_sdc_t;



/*============================================================================*/
/* Debug LEDs                                                            */
/*============================================================================*/

typedef struct
{
    GPIO_TypeDef * port;
    uint16_t pin;
    GPIO_PinState state;
} debug_led_t;



#endif /* CONFIG_CONFIG_H_ */
