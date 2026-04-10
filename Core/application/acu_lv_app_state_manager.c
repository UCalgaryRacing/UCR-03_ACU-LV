/*
 * acu_lv_app_stat_manager.c
 *
 *  Created on: Apr 8, 2026
 *      Author: clayd
 */

#include "acu_lv_app_state_manager.h"
#include "acu_lv_drv_imd.h"


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
    // check imd
    if(acu_lv_drv_get_imd_state() != ACU_LV_IMD_OK)
    {
        return ACU_LV_APP_STATE_FAULT;
    }
    // tssi enabled

    // if imd good and after first voltage and temp then transition to idle
    // otherwise stay here
}

static acu_lv_app_state_t handle_idle_state()
{
    // start measuring ts and accu voltage
    // write the getter function for accu and ts voltage

    // measure sdc reserve, must reach 9V
    //write getter and svc function
    
    // monitor cell voltage and temps
    // monitor imd
    // tssi enabled

    // transition to precharge once sdc reserve is 9V
    // fault transition if imd fault, cell voltage or temp out of range
}

static acu_lv_app_state_t handle_precharge_state()
{
    // monitor accu and ts voltage
    // monitor pack current
    // monitor cell voltage and temp
    // monitor sdc
    // monitor imd
    // tssi enabled

    //transition to active when ts and accu reach 90%
    //transition to fault if watchdog timeout
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
}

static acu_lv_app_state_t handle_fault_state()
{   
    // monitor ts and accu voltage
    // monitor temps and voltage
    // monitor imd
    // disable logging
    // tssi enabled/ flash red
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
}