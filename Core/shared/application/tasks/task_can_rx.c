#include "task_can_rx.h"
#include "cmsis_os.h"
#include "can_typ_common.h"
#include "can_svc_can.h"

extern osMessageQueueId_t Can1RxQueueHandle;
extern osMessageQueueId_t Can2RxQueueHandle;

static const uint32_t period = 10; // ms
static uint32_t nextWakeTime;

void task_can_rx_init()
{
    nextWakeTime = osKernelGetTickCount();
    return;
}


void task_can_rx_loop()
{
    nextWakeTime += period;
	osDelayUntil(nextWakeTime);

    can_msg_t msg;

    if (osMessageQueueGet(Can1RxQueueHandle, &msg, NULL, osWaitForever) == osOK) 
        {
            com_svc_can_route(&msg);
        }
    
    return;
}
