#include "task_slow.h"
#include "cmsis_os2.h"

#include "rco_data.h"
#include "acu_data.h"
#include "acu_app_state_manager.h"

static const uint32_t period = 100;
static uint32_t nextWakeTime;

void task_slow_init(void)
{
	nextWakeTime = osKernelGetTickCount();
}

void task_slow_loop(void)
{
	nextWakeTime += period;
	acu_app_state_t state = acu_data_get_acu_state();
	if (state == ACU_APP_STATE_FAULT)
	{
		osDelay(5000);
		rco_data_set_reset_pressed(true);

		osDelay(50);
		rco_data_set_reset_pressed(false);
	}

	osDelayUntil(nextWakeTime);	
}
