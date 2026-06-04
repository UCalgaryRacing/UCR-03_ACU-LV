#include "acuhv_svc_air.h"
#include "acuhv_drv_air.h"

#include "acu_data.h"

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

void acuhv_svc_air_close_air_pos(bool close)
{
    acuhv_drv_air_close_air_pos(close);

    // data set
    acu_data_set_air_pos_is_closed(close);
}
