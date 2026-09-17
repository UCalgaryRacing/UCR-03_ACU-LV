#ifndef DATA_BMS_DATA_H_
#define DATA_BMS_DATA_H_

#include <stdint.h>
#include "com_typ_common.h"

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


#endif /*DATA_BMS_DATA_H_*/
