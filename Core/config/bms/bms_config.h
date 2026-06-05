#ifndef BMS_CONFIG_H_
#define BMS_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32h7xx_hal.h"

/*============================================================================*/
/* ADBMS6830 Settings and Configuration                                       */
/*============================================================================*/

/* Battery Pack / Daisy Chain Topology                                        */

/** Number of ADBMS6830B slave ICs in the daisy chain. */
#define ADBMS_NUM_SLAVES           2U

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
#define NUMBER_ADBMS_PER_SEGMENT    2U

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

#define ADBMS_AVERGAE_THERM_VOLTAGE 20.215f

/** Reference voltage for GPIO ADC (V). */
#define ADBMS_GPIO_VREF             5.0f

/*============================================================================*/
/* Cell Parameters                                                      */
/*============================================================================*/

// TODO: change to what the actual max and min values are instead of placeholders
#define CELL_MAX_VOLTAGE 4.2f
#define CELL_MIN_VOLTAGE 2.5f

#define CELL_MIN_TEMPERATURE 0.0f
#define CELL_MAX_TEMPERATURE 60.0f

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


#endif
