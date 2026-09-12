#include "acuhv_svc_batt_power.h"

#include "acu_data.h"

status_t acuhv_svc_update_batt_power()
{
    status_t status = ERROR;

    float voltage = acu_data_get_acu_battery_voltage();
    float current = acu_data_get_acu_battery_current();

    float power = voltage * current;

    acu_data_set_acu_battery_power(power);

    status = OK;

    return status;

}