#include "acuhv_svc_air.h"
#include "acuhv_drv_air.h"

#include "sdc_data.h"
#include "aculv_config.h"

#include "acu_data.h"
#include "acuhv_config.h"
#include "acu_svc_logging.h"


static bool g_initialized = false;


status_t acuhv_svc_air_init()
{
    acuhv_drv_air_close_air_neg(false);
    acuhv_drv_air_close_air_pos(false);

    g_initialized = true;
    return OK;
}

void acuhv_svc_air_close_air_neg(bool close)
{
    acuhv_drv_air_close_air_neg(close);

    // data set
    acu_data_set_air_neg_is_closed(close);

}

status_t acuhv_svc_air_close_air_pos(bool close)
{
    if (close)
    {
        // SDC not charged yet, not yet 90%, or TS less than 325V
        if ((sdc_data_get_sdc_reserve_voltage() < SDC_CHARGED_V) || 
        (acu_data_get_acu_ts_voltage() <= (0.9f * acu_data_get_acu_battery_voltage())) ||
        (acu_data_get_acu_ts_voltage() < BATT_VOLTAGE_MIN_V))
        {
            return ERROR;
        }
    }

    acuhv_drv_air_close_air_pos(close);

    // data set
    acu_data_set_air_pos_is_closed(close);

    // send data over can
    acu_svc_can_tx_acu_measurements();

    return OK;
}
