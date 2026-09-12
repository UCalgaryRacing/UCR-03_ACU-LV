#include "acuhv_svc_ts.h"

#include "mcu_svc_dfsdm.h"
#include "acu_data.h"

/*============================================================================*/
/* Read TS Voltage                                                          */
/*============================================================================*/
status_t acuhv_svc_update_ts_voltage()
{
    float voltage;
    status_t status = mcu_svc_dfsdm_get_scaled_shift(TS_VOLTAGE, &voltage);

    if (status != OK)
    {
        return ERROR;
    }
    acu_data_set_acu_ts_voltage(voltage);
    return OK;

}