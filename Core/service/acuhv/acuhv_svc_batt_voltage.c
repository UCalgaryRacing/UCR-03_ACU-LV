#include "acuhv_svc_batt_voltage.h"

#include "acu_data.h"
#include "mcu_svc_dfsdm.h"

/*============================================================================*/
/* Voltage Reading                                                            */
/*============================================================================*/
status_t acuhv_svc_update_batt_voltage()
{
    float voltage;
    status_t status = mcu_svc_dfsdm_get_scaled(BATT_VOLTAGE, &voltage);

    if (status != OK)
    {
        return ERROR;
    }

    acu_data_set_acu_battery_voltage(voltage);
    return OK;

}
