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

/*============================================================================*/
/* ADC Common Settings                                                        */
/*============================================================================*/

// ADC resolution (12-bit = 4096 counts)
#define ADC_RESOLUTION              4096U

// ADC reference voltage in volts
#define ADC_VREF                    3.3f

/*============================================================================*/
/* Accumulator Voltage Configuration                                          */
/*============================================================================*/

// Voltage divider ratio (Vpack / Vadc) - determined by resistor values on HV board
#define ACCU_VOLTAGE_DIVIDER_RATIO          551.0f

// ADC on the hv board can measure a max of +/-1V
#define ACCU_ADC_MAX_INPUT_VOLTAGE 1.0f
#define ACCU_ADC_MAX_COUNT (1<<16) // this might not be right for the max value, look at datasheet section 7.3.4


// Precharge completion threshold (TS voltage must be >= this fraction of pack)
#define ACCU_PRECHARGE_THRESHOLD            0.90f

// Expected pack voltage range (V)
#define ACCU_VOLTAGE_MIN_V                  325.0f
#define ACCU_VOLTAGE_MAX_V                  546.0f

/*============================================================================*/
/* Current Shunt Configuration                                          */
/*============================================================================*/

// Resistance of the shunt resistor on the shunt board
#define CURRENT_SHUNT_RESISTANCE 0.0002f

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



#endif /* CONFIG_CONFIG_H_ */
