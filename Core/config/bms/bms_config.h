#ifndef CONFIG_BMS_CONFIG_H_
#define CONFIG_BMS_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32h7xx_hal.h"

/*============================================================================*/
/* Thermistor Configuration                                                   */
/*============================================================================*/
#define ADBMS_NTC_R25_OHMS          10000.0f    // NTC resistance at 25°C (ohms)
#define ADBMS_NTC_BETA              3984.0f     // NTC beta coefficient (K)
#define ADBMS_NTC_T25_KELVIN        298.15f     // Reference temperature for NTC (25°C in Kelvin)
#define ADBMS_NTC_RSERIES_OHMS      10000.0f    // Series resistor for thermistor voltage divider (ohms)
#define ADBMS_AVG_THERM_VOLTAGE     20.215f     // average thermal voltage

#define ADBMS_GPIO_VREF_V             5.0f      // Reference voltage for GPIO ADC (V)

/*============================================================================*/
/* ADBMS6830 Configuration                                                    */
/*============================================================================*/

/* Battery Pack (Daisy Chain Topology) */
#define ADBMS_NUM_SLAVES               10U // Number of ADBMS6830B slave ICs in the daisy chain.
#define ADBMS_CELLS_PER_SLAVE          13U // Number of cells monitored per slave IC (max 16)
#define ADBMS_THERMS_PER_SLAVE         18U // Number of thermistors per slave IC (9 per MUX bank × 2 banks)
#define ADBMS_NUM_GPIOS                10U // Number of GPIO pins on the ADBMS6830B (GPIO1-10)
#define ADBMS_THERMS_PER_BANK           9U // Number of thermistors per MUX bank (GPIO2-10 = 9 inputs)
#define ADBMS_NUM_MUX_BANK              2U // Number of MUX banks (GPO1 selects between 2 banks)
#define ADBMS_SLAVES_PER_SEG            2U // Number of adbms slaves per segment

/* Derived totals */
#define ADBMS_CELLS_PER_SEG         (ADBMS_SLAVES_PER_SEG * ADBMS_CELLS_PER_SLAVE)      // total number of cells per segment
#define ADBMS_THERMS_PER_SEG        (ADBMS_CELLS_PER_SLAVE * ADBMS_THERMS_PER_SLAVE)    // total number of thermistors per segment
#define ADBMS_TOTAL_CELLS           (ADBMS_NUM_SLAVES * ADBMS_CELLS_PER_SLAVE)          // total number of cells
#define ADBMS_TOTAL_THERMS          (ADBMS_NUM_SLAVES * ADBMS_THERMS_PER_SLAVE)         // total number of thermistors

/* ADBMS6830B slave GPIO Pin Assignments*/
/*
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
/* ADBMS6830 Default Register Configuration                                   */
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

/*============================================================================*/
/* Cell Parameters                                                            */
/*============================================================================*/

// TODO: change to what the actual max and min values are instead of placeholders
#define BMS_CELL_MAX_VOLTAGE 4.2f
#define BMS_CELL_MIN_VOLTAGE 2.5f

#define BMS_CELL_MIN_TEMP 0.0f
#define BMS_CELL_MAX_TEMP 60.0f

/*============================================================================*/
/* Register Structs                                                            */
/*============================================================================*/

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

#endif /*CONFIG_BMS_CONFIG_H_*/