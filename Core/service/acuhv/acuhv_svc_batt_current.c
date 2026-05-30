#include "acuhv_svc_batt_current.h"

#include "acu_data.h"
#include "mcu_svc_dfsdm.h"

/*============================================================================*/
/* Current Reading                                                            */
/*============================================================================*/
status_t acuhv_svc_update_batt_current()
{
    float current;
    status_t status = mcu_svc_dfsdm_get_scaled_shift(BATT_CURRENT, &current);

    if (status != OK)
    {
        return ERROR;
    }

    acu_data_set_acu_battery_current(current);
    return OK;

}