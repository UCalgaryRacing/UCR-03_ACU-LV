#include "rco_svc_can_route.h"

#include "can_svc_can.h"
#include "ucr_03.h"

#include "rco_data.h"

extern FDCAN_HandleTypeDef hfdcan2;

static bool g_initialized = false;

status_t rco_svc_can_route_init(void)
{
    //TODO start CAN here
    com_svc_can_register(REAR_CONTROL_CAN_ID, rco_svc_can_rx_reset_data);

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


void rco_svc_can_rx_reset_data(can_msg_t *msg)
{
    //received by front controller and aculv from rear controller
    struct ucr_03_rear_control_t rear_control_can_msg;
    ucr_03_rear_control_unpack(&rear_control_can_msg, msg->data, msg->dlc);

    rco_data_t rco_data;  
    
    rco_data.tssi_faulted = rear_control_can_msg.tssi_faulted;
    rco_data.brake_light_on = rear_control_can_msg.brake_light;
    rco_data.drs_active = rear_control_can_msg.drs;
    rco_data.reset_pressed = rear_control_can_msg.reset_button;
    
    rco_data_set_data(&rco_data);
}
