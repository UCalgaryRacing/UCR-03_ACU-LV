/*
 * task_manager.c
 *
 *  Created on: Apr 7, 2026
 *      Author: clayd
 */


#include "slow_task.h"
#include "cmsis_os2.h"

const static uint32_t period = 10;
static uint32_t next_wake;

void task_manager_init()
{
    next_wake = osKernelGetTickCount();
}
void task_manager_loop()
{
    next_wake += period;
    osDelayUntil(next_wake);
}
