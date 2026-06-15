#include "acuhv_svc_imd.h"
#include "acuhv_drv_imd.h"
#include <stdbool.h>
#include "acu_data.h"

void acuhv_svc_update_imd_ok()
{
    bool imd_fault = acuhv_drv_imd_read_fault_status();

    acu_app_state_t state = acu_data_get_acu_state();

    if (state != ACU_APP_STATE_STARTUP)
    {
        acu_data_set_imd_fault_status(imd_fault);
    }

}
