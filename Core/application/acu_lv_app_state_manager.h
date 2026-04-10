/*
 * acu_lv_app_state_manager.h
 *
 *  Created on: Mar 23, 2026
 *      Author: f-dunnwolbaum
 */

#ifndef APPLICATION_ACU_LV_APP_STATE_MANAGER_H_
#define APPLICATION_ACU_LV_APP_STATE_MANAGER_H_

typedef enum
{
    ACU_LV_APP_STATE_STARTUP = 0U,
    ACU_LV_APP_STATE_IDLE,
    ACU_LV_APP_STATE_PRECHARGE,
    ACU_LV_APP_STATE_ACTIVE,
    ACU_LV_APP_STATE_FAULT,
    ACU_LV_APP_STATE_CHARGING,
    ACU_LV_APP_STATE_BALANCING
} acu_lv_app_state_t;

// private function prototype
static acu_lv_app_state_t handle_startup_state();
static acu_lv_app_state_t handle_idle_state();
static acu_lv_app_state_t handle_precharge_state();
static acu_lv_app_state_t handle_active_state();
static acu_lv_app_state_t handle_fault_state();
static acu_lv_app_state_t handle_charging_state();
static acu_lv_app_state_t handle_balencing_state();

static void state_entry(acu_lv_app_state_t state);
static void state_exit(acu_lv_app_state_t state);

// public function prototype
void acu_lv_app_state_machine_init();
void acu_lv_app_state_machine_step();




#endif /* APPLICATION_ACU_LV_APP_STATE_MANAGER_H_ */
