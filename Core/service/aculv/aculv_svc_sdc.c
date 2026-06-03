#include "aculv_svc_sdc.h"
#include "aculv_drv_sdc.h"
#include "mcu_svc_analog.h"

#include "sdc_data.h"
#include "rco_data.h"
#include "acu_data.h"

#include "cmsis_os2.h"

static bool g_initialized = false;

/*============================================================================*/
/* Private Function Prototypes                                                */
/*============================================================================*/
static void aculv_svc_set_imd_latch_en(bool enable);
static void aculv_svc_set_bms_latch_en(bool enable);

static status_t update_sdc_voltage(mcu_analog_channel_id_t channel_id, void (*setter)(float));

/*============================================================================*/
/* Private Functions                                                          */
/*============================================================================*/
static void aculv_svc_set_bms_latch_en(bool enable)
{
    aculv_drv_set_bms_latch_en(enable);
}

static void aculv_svc_set_imd_latch_en(bool enable)
{
    aculv_drv_set_imd_latch_en(enable);
}


static status_t update_sdc_voltage(mcu_analog_channel_id_t channel_id, void (*setter)(float))
{
    float voltage;
    status_t status = mcu_svc_get_analog_voltage(channel_id, &voltage);

    if (status != OK)
    {
        return ERROR;
    }
    setter(voltage);

    return OK;
}
/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/
status_t aculv_svc_sdc_init()
{
    aculv_svc_set_bms_ok(true);
    aculv_svc_set_bms_latch_en(false);

    aculv_svc_set_imd_latch_en(false);

    g_initialized = true;
    return OK;
}
// reset button (hardware toggle latches) on startup

/*============================================================================*/
/* BMS Status                                                              */
/*============================================================================*/
void aculv_svc_set_bms_ok(bool enable)
{
    aculv_drv_set_bms_ok(enable);
}


void aculv_svc_update_sdc_bms_ok()
{
    if (acu_data_get_bms_fault_status())
    {
        aculv_svc_set_bms_ok(false);
    }

    else
    {
        aculv_svc_set_bms_ok(true);
    }
}

/*============================================================================*/
/* SDC Latch Update (based on reset button)                                   */
/*============================================================================*/

void aculv_svc_update_sdc_latches()
{
    if (rco_data_get_reset_pressed())
    {
        aculv_svc_set_imd_latch_en(true);
        aculv_svc_set_bms_latch_en(true);
    }

    else
    {
        aculv_svc_set_imd_latch_en(false);
        aculv_svc_set_bms_latch_en(false);
    }
}

/*============================================================================*/
/* SDC Voltage Data Update                                                    */
/*============================================================================*/
status_t aculv_svc_update_sdc_voltages()
{
    status_t status = OK;

    if (update_sdc_voltage(SDC_RESERVE, sdc_data_set_sdc_reserve_voltage) != OK) status = ERROR;
    if (update_sdc_voltage(SDC_END,     sdc_data_set_sdc_end_voltage)     != OK) status = ERROR;
    if (update_sdc_voltage(SDC_8,       sdc_data_set_sdc_8_voltage)       != OK) status = ERROR;
    if (update_sdc_voltage(SDC_7,       sdc_data_set_sdc_7_voltage)       != OK) status = ERROR;
    if (update_sdc_voltage(SDC_MID_2,   sdc_data_set_sdc_mid2_voltage)    != OK) status = ERROR;
    if (update_sdc_voltage(SDC_MID_1,   sdc_data_set_sdc_mid1_voltage)    != OK) status = ERROR;
    
    return status;
}
