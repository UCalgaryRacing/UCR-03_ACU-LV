#include "can_config.h"
#include "com_typ_common.h"
#include "can_typ_common.h"
#include "cmsis_os.h"
#include "can_drv_can.h"

extern osMessageQueueId_t Can1TxQueueHandle;
extern osMessageQueueId_t Can2TxQueueHandle;

static const uint32_t period = 10; // ms
static uint32_t nextWakeTime;

void task_can_tx_init()
{
    can_config_t can_1_config = can_config[CAN1];
	can_drv_start(&can_1_config.hw);

    nextWakeTime = osKernelGetTickCount();

}


void task_can_tx_loop()
{
    //nextWakeTime += period;
    //osDelayUntil(nextWakeTime);

    can_msg_t msg;

    if (osMessageQueueGet(Can1TxQueueHandle, &msg, NULL, osWaitForever) == osOK)
    {
        can_drv_transmit(&msg);
    }

}
