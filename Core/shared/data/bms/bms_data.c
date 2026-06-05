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
    .cell_min_v     = 4.1f,
    .cell_max_v     = 2.6f,
    .cell_avg_v     = 3.6f,
    .pack_v         = 0.0f,
    .cell_min_slave = 0U,
    .cell_min_idx   = 0U,
    .cell_max_slave = 0U,
    .cell_max_idx   = 0U,
};

bms_temp_stats_t temp_stats =
{
    .temp_min_c = 59.0f,
    .temp_max_c = 0.0f,
    .temp_avg_c = 25.0f,
    .temp_min_slave = 0,
    .temp_min_idx = 0,
    .temp_max_slave = 0,
    .temp_max_idx = 0,
};
