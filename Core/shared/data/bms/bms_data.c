#include "bms_data.h"
#include "bms_config.h"

static bool g_initialized;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/

status_t bms_data_init(void)
{
    g_initialized = true;
    return OK;
}

bms_voltage_stats_t voltage_stats = 
{
    .cell_min_v     = BMS_CELL_MAX_VOLTAGE,  
    .cell_max_v     = BMS_CELL_MIN_VOLTAGE,   
    .cell_avg_v     = 3.6f,
    .pack_v         = 0.0f,
    .cell_min_slave = 0U,
    .cell_min_idx   = 0U,
    .cell_max_slave = 0U,
    .cell_max_idx   = 0U,
};

bms_temp_stats_t temp_stats =
{
    .temp_min_c = BMS_CELL_MIN_TEMP, 
    .temp_max_c = BMS_CELL_MAX_TEMP,    
    .temp_avg_c = ADBMS_AVG_THERM_VOLTAGE,
    .temp_min_slave = 0,
    .temp_min_idx = 0,
    .temp_max_slave = 0,
    .temp_max_idx = 0,
};