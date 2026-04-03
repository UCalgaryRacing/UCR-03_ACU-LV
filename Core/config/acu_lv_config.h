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
#include "acu_lv_types_common.h"
#include "stm32h7xx_hal.h"

 


/*============================================================================*/
/* ADC Common Settings                                                        */
/*============================================================================*/

// ADC resolution (12-bit = 4096 counts)
#define ADC_RESOLUTION              4096U

#define ADC_SCALING_FACTOR 0.18458f

// ADC reference voltage in volts
#define ADC_VREF                    3.3f

/*============================================================================*/
/* Accumulator Voltage Configuration                                          */
/*============================================================================*/

// Voltage divider ratio (Vpack / Vadc) - determined by resistor values on HV board
#define ACCU_VOLTAGE_DIVIDER_RATIO          551.0f

// Precharge completion threshold (TS voltage must be >= this fraction of pack)
#define ACCU_PRECHARGE_THRESHOLD            0.90f

// Expected pack voltage range (V)
#define ACCU_VOLTAGE_MIN_V                  325.0f
#define ACCU_VOLTAGE_MAX_V                  546.0f

/*============================================================================*/
/* Current Shunt Configuration                                          */
/*============================================================================*/

// shunt scaling factor, done by measuring the raw value and then printing it with the virtual com port 
#define CURRENT_SHUNT_DATA_LENGTH 16
#define CURRENT_SHUNT_SCALING_FACTOR 6484.1997f

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
/* ADBMS6830 Settings and Configuration                                       */
/*============================================================================*/

/* Battery Pack / Daisy Chain Topology                                        */

/** Number of ADBMS6830B slave ICs in the daisy chain. */
#define ADBMS_NUM_SLAVES            10U

/** Number of cells monitored per slave IC (max 16). */
#define ADBMS_CELLS_PER_IC          13U

/** Number of thermistors per slave IC (9 per MUX bank × 2 banks). */
#define ADBMS_THERMS_PER_IC         18U

/** Number of GPIO pins on the ADBMS6830B (GPIO1-10). */
#define ADBMS_NUM_GPIOS             10U

/** Number of thermistors per MUX bank (GPIO2-10 = 9 inputs). */
#define ADBMS_THERMS_PER_BANK       9U

/** Number of MUX banks (GPO1 selects between 2 banks). */
#define ADBMS_THERM_MUX_BANKS       2U

// number of adbms slaves per segment
#define NUMBER_ADBMS_PER_SEGMENT 2U

// Total number of cells per segment
#define NUMBER_ADBMS_CELLS_PER_SEG (NUMBER_ADBMS_PER_SEGMENT * ADBMS_CELLS_PER_IC)

// Total number of thermisters per segment
#define NUMBER_THERMS_PER_SEG (ADBMS_CELLS_PER_IC * ADBMS_THERMS_PER_IC)

/** Total cells in the battery pack. */
#define ADBMS_TOTAL_CELLS           (ADBMS_NUM_SLAVES * ADBMS_CELLS_PER_IC)

/** Total thermistors in the battery pack. */
#define ADBMS_TOTAL_THERMS          (ADBMS_NUM_SLAVES * ADBMS_THERMS_PER_IC)



/*============================================================================*/
/* GPIO Pin Assignments (on the ADBMS6830B slaves)                            */
/*============================================================================*/

/**
 * GPO pin used to control thermistor multiplexer.
 * Pull-down ON (GPO=0):  selects thermistor bank A (thermistors 0-8)
 * Pull-down OFF (GPO=1): selects thermistor bank B (thermistors 9-17)
 */
#define ADBMS_THERM_MUX_GPO         ADBMS_GPO_PIN_1

/**
 * GPIO pins used to read thermistor voltages.
 * GPIO2-10 are connected to thermistors via the MUX.
 * GPIO1 is not used for thermistor reading (reserved or other use).
 */
#define ADBMS_THERM_GPIO_FIRST      2U   /**< First GPIO for thermistors (GPIO2) */
#define ADBMS_THERM_GPIO_LAST       10U  /**< Last GPIO for thermistors (GPIO10) */

/*============================================================================*/
/* Thermistor Parameters                                                      */
/*============================================================================*/

/** NTC resistance at 25°C (ohms). */
#define ADBMS_NTC_R25_OHMS          10000.0f

/** NTC beta coefficient (K). */
#define ADBMS_NTC_BETA              3984.0f

/** Reference temperature for NTC (25°C in Kelvin). */
#define ADBMS_NTC_T25_KELVIN        298.15f

/** Series resistor for thermistor voltage divider (ohms). */
#define ADBMS_NTC_RSERIES_OHMS      10000.0f

/** Reference voltage for GPIO ADC (V). */
#define ADBMS_GPIO_VREF             5.0f

/*============================================================================*/
/* Default Register Configuration                                             */
/*============================================================================*/

/** Default comparator threshold for C-ADC vs S-ADC comparison. */
#define ADBMS_DEFAULT_CTH           ADBMS_CFGA_CTH_8_1MV

/** Default IIR filter setting. */
#define ADBMS_DEFAULT_FC            ADBMS_CFGA_FC_DISABLED

/** Default open wire soak time. */
#define ADBMS_DEFAULT_OWA           ADBMS_CFGA_OWA_32US

/** Default GPO configuration (all pull-downs off). */
#define ADBMS_DEFAULT_GPO           ADBMS_GPO_ALL_PULLDOWN_OFF

/**
 * Number of bytes per ADBMS6830 register group payload (e.g. CFGA, CFGB, cell groups).
 *
 * Note: Some SPI frames append PEC bytes, but the raw register payload itself
 * is 6 bytes for these groups.
 */
#define ADBMS_REG_GROUP_SIZE 6U

typedef struct 
{

} adbms6830_config_t;

/**
 * ADBMS6830 Shadow Register
 * 
 * TODO: write comments explaining what it is (rip off the pdm) and get AI to slop out the shadow reg
 */
typedef struct
{
    uint8_t cfga[ADBMS_REG_GROUP_SIZE];

} adbms6830_shadow_t;


/**
 * hardware type
 */
typedef struct
{
    adbms6830_shadow_t * shadow;
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
    GPIO_TypeDef *wakeup_port;
    uint16_t wakeup_pin;
    GPIO_TypeDef *interrupt_port;
    uint16_t interrupt_pin;
    uint8_t ic;
} adbms6830_hw_t;

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
    float * data;
    int32_t * raw_data;
} acu_lv_pack_current_t;

/*============================================================================*/
/* Cell Structure                                                             */
/*============================================================================*/

typedef struct
{
    adbms6830_hw_t hw;
    const uint16_t cell_id;
    float cell_voltage;
    uint16_t voltage_raw; // raw adc value from reading cell voltage
} acu_lv_cell_voltage_t;

typedef struct
{
    adbms6830_hw_t hw;
    const uint16_t cell_id;
    float cell_temp;
    uint16_t temp_raw;
} acu_lv_cell_temp_t;

/*============================================================================*/
/* Segment Structure                                                          */
/*============================================================================*/

typedef struct
{
    adbms6830_hw_t *adbms_slaves[NUMBER_ADBMS_PER_SEGMENT]; 
    acu_lv_cell_voltage_t *cell_voltages[NUMBER_ADBMS_CELLS_PER_SEG];
    acu_lv_cell_temp_t *cell_temps[NUMBER_THERMS_PER_SEG];
} acu_lv_segment_t;




#endif /* CONFIG_CONFIG_H_ */
