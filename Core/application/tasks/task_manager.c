#include "task_manager.h"
#include "acu_app_state_manager.h"
#include "cmsis_os2.h"

#include "acu_data.h"
#include "acu_svc_logging.h"

static const uint32_t period = 10;
static uint32_t nextWakeTime;

void task_manager_init(void)
{
    nextWakeTime = osKernelGetTickCount();
    acu_app_state_machine_init();
}

void task_manager_loop()
{
    nextWakeTime += period;
    osDelayUntil(nextWakeTime);

    acu_app_state_machine_step();

    // update states + transmit
    acu_app_state_machine_update_state();
    acu_svc_can_tx_ts_state_update();

    acu_svc_can_tx_acu_measurements();
}
