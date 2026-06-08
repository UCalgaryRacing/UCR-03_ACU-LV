#ifndef CONFIG_ACUHV_CONFIG_H_
#define CONFIG_ACUHV_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32h7xx_hal.h"

#include "mcu_config_dfsdm.h"
#include "mcu_dfsdm_filters.h"

/*============================================================================*/
/* DFSDM ACUHV Mapping                                                         */
/*============================================================================*/

#define TS_VOLTAGE                  DFSDM1_FILT0
#define BATT_VOLTAGE                DFSDM1_FILT1
#define BATT_CURRENT                DFSDM1_FILT2

/*============================================================================*/
/* Accumulator Voltage Configuration                                          */
/*============================================================================*/
/*scaling factors determined by using a known voltage and averaging the raw values*/

#define BATT_VOLTAGE_SCALING_FACTOR         0.00000126344f
#define BATT_VOLTAGE_MIN_V                  325.0f                      // Valid Expected pack voltage range (V)
#define BATT_VOLTAGE_MAX_V                  546.0f


#define TS_SCALING_FACTOR                   0.00032845893948625697f
#define TS_VOLTAGE_MIN_V                    0U                          // valid ts voltage range  (TODO: check numbers)
#define TS_VOLTAGE_MAX_V                    546.0f

#define TS_DISCHARGED_V                     60.0f

/*============================================================================*/
/* Shunt Configuration                                                        */
/*============================================================================*/

#define SHUNT_RESISTANCE_OHMS                0.0002f
#define SHUNT_SCALING_FACTOR                 0.00015422103651609282f

#define SHUNT_MIN                            0 // amps? 
#define SHUNT_MAX                            10

/*============================================================================*/
/* external config                                                             */
/*============================================================================*/

extern const mcu_dfsdm_config_t mcu_dfsdm_config[DFSDM_FILTER_COUNT];

#endif /*CONFIG_ACUHV_CONFIG_H_*/
