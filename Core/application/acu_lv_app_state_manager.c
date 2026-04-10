/*
 * acu_lv_app_stat_manager.c
 *
 *  Created on: Apr 8, 2026
 *      Author: clayd
 */

#include "acu_lv_app_state_manager.h"

#include "acu_lv_svc_imd.h"
#include "acu_lv_svc_air.h"
#include "acu_lv_svc_precharge.h"
#include "acu_lv_svc_sdc.h"

#include "acu_lv_drv_air.h"
#include "acu_lv_drv_imd.h"
#include "acu_lv_drv_sdc.h"

/* Private Prototypes*/
static acu_lv_app_state_t handle_startup_state();
static acu_lv_app_state_t handle_idle_state();
static acu_lv_app_state_t handle_precharge_state();
static acu_lv_app_state_t handle_active_state();
static acu_lv_app_state_t handle_fault_state();
static acu_lv_app_state_t handle_charging_state();
static acu_lv_app_state_t handle_balencing_state();

static void state_entry(acu_lv_app_state_t state);
static void state_exit(acu_lv_app_state_t state);

static acu_lv_app_state_t g_current_state = ACU_LV_APP_STATE_STARTUP;
static acu_lv_app_state_t g_previous_state = ACU_LV_APP_STATE_STARTUP;

void acu_lv_app_state_machine_init()
{
    g_current_state = ACU_LV_APP_STATE_STARTUP;
    g_previous_state = ACU_LV_APP_STATE_STARTUP;
}

void acu_lv_app_state_machine_step()
{   
    acu_lv_app_state_t next_state;
    switch (g_current_state)
    {
    case ACU_LV_APP_STATE_STARTUP:
        next_state = handle_startup_state();
        break;
    
    case ACU_LV_APP_STATE_IDLE:
        next_state = handle_idle_state();
        break;
    
    case ACU_LV_APP_STATE_PRECHARGE:
        next_state = handle_precharge_state();
        break;

    case ACU_LV_APP_STATE_ACTIVE:
        next_state = handle_active_state();
        break;

    case ACU_LV_APP_STATE_FAULT:
        next_state = handle_fault_state();
        break;

    case ACU_LV_APP_STATE_CHARGING:
        next_state = handle_charging_state();
        break;

    case ACU_LV_APP_STATE_BALANCING:
        next_state = handle_balencing_state();
        break;

    default:
        next_state = ACU_LV_APP_STATE_STARTUP;
        break;
    }

    // state transition
    if(next_state != g_current_state)
    {   
        // do anything that needs to be done when leaving the current state
        state_exit(g_current_state);

        // actually do the state change
        g_previous_state = g_current_state;
        g_current_state = next_state;

        // do anything that needs to be done when entering new state
        state_entry(g_current_state);
    }
}

static acu_lv_app_state_t handle_startup_state()
{

    // start cell temp and voltage measurement
    // check imd, potentially change to happen in idle to allow imd time to boot or add delay
    if(!acu_lv_svc_imd_ok())
    {
        return ACU_LV_APP_STATE_FAULT;
    }
    // tssi enabled

    // if imd good and after first voltage and temp then transition to idle
    return ACU_LV_APP_STATE_IDLE;
}

static acu_lv_app_state_t handle_idle_state()
{
    // start measuring ts and accu voltage, add logic to fast task
    // write the getter function for accu and ts voltage

    // check cell voltage and temps out of range

    // check state transition, start with transition case
    // then move through to check for errors based on safety/priority
    if(acu_lv_svc_sdc_reserve_good() && acu_lv_svc_imd_ok())
    {
        return ACU_LV_APP_STATE_IDLE;
    }
    else if(!acu_lv_svc_imd_ok())
    {   
        return ACU_LV_APP_STATE_FAULT;
    }
    else if(!acu_lv_svc_sdc_reserve_good())
    {
        return ACU_LV_APP_STATE_IDLE;
    }

    // tssi enabled

    // transition to precharge once sdc reserve is 9V
    // fault transition if imd fault, cell voltage or temp out of range
    return ACU_LV_APP_STATE_PRECHARGE;
}

static acu_lv_app_state_t handle_precharge_state()
{
    // monitor accu and ts voltage
    if(acu_lv_svc_check_precharge_done())
    {
        return ACU_LV_APP_STATE_ACTIVE;
    }
    // monitor pack current
    // monitor cell voltage and temp
    // monitor sdc
    // monitor imd
    // tssi enabled

    //transition to active when ts and accu reach 90%
    //transition to fault if watchdog timeout
    return ACU_LV_APP_STATE_FAULT;
}

static acu_lv_app_state_t handle_active_state()
{
    // monitor accu and ts voltage
    // monitor pack current
    // monitor cell voltage and temp
    // monitor sdc
    // monitor imd
    // tssi enabled

    //transition to charge if charging message recieved
    //fault transition if imd fault, cell voltage or temp out of range
    return ACU_LV_APP_STATE_FAULT;
}

static acu_lv_app_state_t handle_fault_state()
{   
    // monitor ts and accu voltage
    // monitor temps and voltage
    // monitor imd
    // disable logging
    // tssi enabled/ flash red
    return ACU_LV_APP_STATE_FAULT;
}

static acu_lv_app_state_t handle_charging_state()
{
    // monitoring cell temp and voltage
    // monitor accu and ts
    // tssi disabled
    // imd monitoring
    // current measurement disabled

    //transition to fault if voltage or temp out of range, charger comm lost,charger fault
    // transition to balance if balance command rx or any cell reaches max voltage
    return ACU_LV_APP_STATE_FAULT;
}

static acu_lv_app_state_t handle_balencing_state()
{
    //voltage and temp monitor
    // accu and ts voltage monitor
    //disabled ts current monitor
    // imd monitor
    //charging disabled

    //transition to fault if imd fault, voltage or temp out of range, charger fault
    //transition to charge once cells are within 10mV
    return ACU_LV_APP_STATE_FAULT;
}

static void state_entry(acu_lv_app_state_t state)
{   
    // no startup entry because the start up state should not be entered
    switch (state)
    {
    case ACU_LV_APP_STATE_IDLE:
        /* code */
        break;
    case ACU_LV_APP_STATE_PRECHARGE:
        /* code */
        break;
    case ACU_LV_APP_STATE_ACTIVE:
        // send 
        break;
    case ACU_LV_APP_STATE_FAULT:
        // check what faulted and send tssi red signal
        break;
    case ACU_LV_APP_STATE_CHARGING:
        /* code */
        break; 
    case ACU_LV_APP_STATE_BALANCING:
        /* code */
        break;    
    default:
        break;
    }
}

static void state_exit(acu_lv_app_state_t state)
{
    switch (state)
    {
    case ACU_LV_APP_STATE_STARTUP:
        // send tssi good signal
        break;
    case ACU_LV_APP_STATE_IDLE:
        // close shutdown
        acu_lv_svc_close_sdc();        
        //close negative air when leaving idle
        acu_lv_drv_close_air_neg();
        break;
    case ACU_LV_APP_STATE_PRECHARGE:
        //close positive air when leaving precharge
        acu_lv_drv_close_air_pos();
        break;
    case ACU_LV_APP_STATE_ACTIVE:
        /* code */
        break;
    case ACU_LV_APP_STATE_FAULT:
        /* code */
        break;
    case ACU_LV_APP_STATE_CHARGING:
        /* code */
        break; 
    case ACU_LV_APP_STATE_BALANCING:
        /* code */
        break;    
    default:
        break;
    }
}