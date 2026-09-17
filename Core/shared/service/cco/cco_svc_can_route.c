#include "cco_svc_can_route.h"

#include "can_svc_can.h"
#include "ucr_03.h"

#include "cco_data.h"

extern FDCAN_HandleTypeDef hfdcan2;

static bool g_initialized = false;

status_t cco_svc_can_route_init(void)
{
    //TODO start CAN here
    com_svc_can_register(BALANCE_CAN_ID, cco_svc_can_rx_balance);

    FDCAN_FilterTypeDef sFilterConfig;

    // sFilterConfig.IdType = FDCAN_STANDARD_ID;
    // sFilterConfig.FilterIndex = 0;
    // sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    // sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    // sFilterConfig.FilterID1 = 405;
    // sFilterConfig.FilterID2 = 0x7FF;
    // sFilterConfig.RxBufferIndex = 0;
    // HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig);

    // HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

    g_initialized = true;
    return OK;
}

void cco_svc_can_rx_balance(can_msg_t *msg)
{
    struct ucr_03_balancing_t charge_control_can_msg;
    ucr_03_balancing_unpack(&charge_control_can_msg, msg->data, msg->dlc);

    cco_data_t cco_data;

    cco_data.balance_request = charge_control_can_msg.balance_request;
    cco_data.balance_duration = charge_control_can_msg.balance_duration;
    
    cco_data_set_data(&cco_data);

}
