/*============================================================================*/
/* Includes                                                                   */
/*============================================================================*/
// TODO: add a data point that takes the moving average filtered difference between TS and ACCU voltage (tell if it's welded, or not active, etc. check in every state)
#include "acu_app_state_manager.h"
#include "cmsis_os2.h"

#include "acuhv_svc_air.h"
#include "aculv_svc_sdc.h"
#include "acuhv_svc_precharge.h"

#include "aculv_config.h"
#include "acuhv_config.h"

#include "acu_data.h"
#include "sdc_data.h"
#include "rco_data.h"

#include "com_typ_common.h"

/*============================================================================*/
/* Private Variables                                                          */
/*============================================================================*/

static acu_app_state_t g_current_state = ACU_APP_STATE_STARTUP;
static acu_app_state_t g_previous_state = ACU_APP_STATE_STARTUP;

/*============================================================================*/
/* Private Function Prototypes                                                */
/*============================================================================*/
static acu_app_state_t handle_startup_state();
static acu_app_state_t handle_idle_state();
static acu_app_state_t handle_precharge_state();
static acu_app_state_t handle_active_state();
static acu_app_state_t handle_fault_state();
// static acu_app_state_t handle_charging_state();
// static acu_app_state_t handle_balancing_state();

static void on_state_entry(acu_app_state_t state);
static void on_state_exit(acu_app_state_t state);

/*============================================================================*/
/* Private Functions                                                          */
/*============================================================================*/
static acu_app_state_t handle_startup_state()
{
    osDelay(2500); // delay before checking IMD, otherwise auto fault (datasheet says 2s)
    // if init in fast task fails, fault? 

    return ACU_APP_STATE_IDLE;
}

static acu_app_state_t handle_idle_state()
{

    if (((sdc_data_get_sdc_reserve_voltage() >= SDC_CHARGED_V)) && (acu_data_get_acu_ts_voltage() < TS_DISCHARGED_V)) // maybe should be a small range around zero? float is hardly ever exactly zero
    {
        return ACU_APP_STATE_PRECHARGE;
    }

    if (aculv_svc_sdc_is_sdc_faulted())    
    {
        return ACU_APP_STATE_FAULT;
    }

    return ACU_APP_STATE_IDLE;
}

static acu_app_state_t handle_precharge_state()
{
    acuhv_svc_precharge_update_fault_timeout();

    // check if ts voltage is at least 90% of acu voltage
    if ((acu_data_get_acu_ts_voltage() > BATT_VOLTAGE_MIN_V) && (acu_data_get_acu_ts_voltage() >= (0.9f * acu_data_get_acu_battery_voltage())))
    {
        return ACU_APP_STATE_ACTIVE;
    }

    if (aculv_svc_sdc_is_sdc_faulted() || (acu_data_get_precharge_timeout_fault_status()))
    {
        return ACU_APP_STATE_FAULT;
    }

    return ACU_APP_STATE_PRECHARGE;
}

static acu_app_state_t handle_active_state()
{
    if (aculv_svc_sdc_is_sdc_faulted())    
    {
        return ACU_APP_STATE_FAULT;
    }

    return ACU_APP_STATE_ACTIVE;
}

static acu_app_state_t handle_fault_state()
{
    if (rco_data_get_reset_pressed())
    {
        return ACU_APP_STATE_IDLE;
    }

    return ACU_APP_STATE_FAULT;
}

// static acu_app_state_t handle_charging_state()
// {
//     return ACU_APP_STATE_IDLE;
// }

// static acu_app_state_t handle_balancing_state()
// {
//     return ACU_APP_STATE_IDLE;
// }

/*============================= ENTRY / EXIT =================================*/
static void on_state_entry(acu_app_state_t state)
{
    switch (state)
    {
    case ACU_APP_STATE_STARTUP:
        acuhv_svc_air_close_air_neg(false);
        acuhv_svc_air_close_air_pos(false);      
        break;

    case ACU_APP_STATE_IDLE:
        acuhv_svc_air_close_air_neg(false);
        acuhv_svc_air_close_air_pos(false);      
        break;

    case ACU_APP_STATE_PRECHARGE:
        acuhv_svc_precharge_start();

        acuhv_svc_air_close_air_neg(true);
        acuhv_svc_air_close_air_pos(false);
    	osDelay(3000);
        break;

    case ACU_APP_STATE_ACTIVE:
        // close air if precharge --> active state
        acuhv_svc_air_close_air_neg(true);
        acuhv_svc_air_close_air_pos(true); // if AIR POS was not able to be closed, state machine will read as STATE_ACTIVE but shouldnt be able to drive
        break;
    
    case ACU_APP_STATE_FAULT:
        acuhv_svc_air_close_air_neg(false);
        acuhv_svc_air_close_air_pos(false);        

        break;

    default:
        break;
    }
}

static void on_state_exit(acu_app_state_t state)
{
    switch (state)
    {
    case ACU_APP_STATE_PRECHARGE:
        acu_data_set_precharge_timeout_fault_status(false); // clear precharge timeout flag 
        break;
    default:
        break;
    }
}

/*============================================================================*/
/* Public Functions                                                           */
/*============================================================================*/
void acu_app_state_machine_init()
{
    g_current_state = ACU_APP_STATE_STARTUP;
    g_previous_state = ACU_APP_STATE_STARTUP;
}

void acu_app_state_machine_step()
{
    acu_app_state_t next_state;
    switch (g_current_state)
    {
    case ACU_APP_STATE_STARTUP:
        next_state = handle_startup_state();
        break;
    
    case ACU_APP_STATE_IDLE:
        next_state = handle_idle_state();
        break;
    
    case ACU_APP_STATE_PRECHARGE:
        next_state = handle_precharge_state();
        break;

    case ACU_APP_STATE_ACTIVE:
        next_state = handle_active_state();
        break;

    case ACU_APP_STATE_FAULT:
        next_state = handle_fault_state();
        break;

    // case ACU_APP_STATE_CHARGING:
    //     next_state = handle_charging_state();
    //     break;

    // case ACU_APP_STATE_BALANCING:
    //     next_state = handle_balancing_state();
    //     break;

    default:
        next_state = ACU_APP_STATE_STARTUP;
        break;
    }

    // state transition
    if(next_state != g_current_state)
    {   
        // do anything that needs to be done when leaving the current state
        on_state_exit(g_current_state);

        // actually do the state change
        g_previous_state = g_current_state;
        g_current_state = next_state;

        // do anything that needs to be done when entering new state
        on_state_entry(g_current_state);
    }
}

void acu_app_state_machine_update_state(void)
{
    acu_data_set_acu_state(g_current_state);
}
