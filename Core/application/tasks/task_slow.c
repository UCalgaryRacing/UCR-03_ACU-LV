#include "task_slow.h"
#include "cmsis_os2.h"

static const uint32_t period = 100;
static uint32_t nextWakeTime;

void task_slow_init(void)
{
	nextWakeTime = osKernelGetTickCount();
}

void task_slow_loop(void)
{
	nextWakeTime += period;
	osDelayUntil(nextWakeTime);	
}