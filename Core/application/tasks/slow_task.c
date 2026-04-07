/*
 * slow_task.c
 *
 *  Created on: Apr 7, 2026
 *      Author: clayd
 */

#include "slow_task.h"
#include "cmsis_os2.h"

const static uint32_t period = 100;
static uint32_t next_wake;

void slow_task_init()
{
    next_wake = osKernelGetTickCount();
}
void slow_task_loop()
{
    next_wake += period;
    osDelayUntil(next_wake);
}

