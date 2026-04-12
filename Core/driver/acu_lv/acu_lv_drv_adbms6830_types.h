/*
 * bms_types.h
 *
 * Core data structures for the BMS system.
 * Defines slave-level and pack-level data types.
 *
 *  Created on: Dec 8, 2025
 *      Author: esall
 */

#ifndef TYPES_BMS_TYPES_H_
#define TYPES_BMS_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include "acu_lv_config.h"

/*============================================================================*/
/* Slave-Level Data (one ADBMS6830B IC)                                       */
/*============================================================================*/

/**
 * Cell voltage and temperature data from a single BMS slave (ADBMS6830B).
 *
 * Voltages are stored in volts (V).
 * Temperatures are stored in degrees Celsius (°C).
 */
typedef struct
{
    float cell_v[ADBMS_CELLS_PER_IC];       /**< Cell voltages in V */
    float temp_c[ADBMS_THERMS_PER_IC];      /**< Temperatures in °C */
} bms_slave_data_t;

/*============================================================================*/
/* Pack-Level Aggregates                                                      */
/*============================================================================*/

/**
 * Voltage statistics for the entire battery pack.
 */
typedef struct
{
    float   cell_min_v;         /**< Minimum cell voltage in V */
    float   cell_max_v;         /**< Maximum cell voltage in V */
    float   cell_avg_v;         /**< Average cell voltage in V */
    float   pack_v;             /**< Total pack voltage in V */
    uint8_t cell_min_slave;     /**< Slave index containing min cell */
    uint8_t cell_min_idx;       /**< Cell index within slave for min */
    uint8_t cell_max_slave;     /**< Slave index containing max cell */
    uint8_t cell_max_idx;       /**< Cell index within slave for max */
} bms_voltage_stats_t;

/**
 * Temperature statistics for the entire battery pack.
 */
typedef struct
{
    float   temp_min_c;         /**< Minimum temperature in °C */
    float   temp_max_c;         /**< Maximum temperature in °C */
    float   temp_avg_c;         /**< Average temperature in °C */
    uint8_t temp_min_slave;     /**< Slave index containing min temp */
    uint8_t temp_min_idx;       /**< Thermistor index within slave for min */
    uint8_t temp_max_slave;     /**< Slave index containing max temp */
    uint8_t temp_max_idx;       /**< Thermistor index within slave for max */
} bms_temp_stats_t;

#endif /* TYPES_BMS_TYPES_H_ */
