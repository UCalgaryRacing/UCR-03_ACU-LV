#include "aculv_svc_sdc_logging.h"
#include "sdc_data.h"

#include "can_svc_can.h"
#include "can_config.h"

void aculv_svc_can_tx_sdc_voltages()
{
    can_msg_t msg;
    msg.channel = CAN1;
    msg.id = SDC_VOLTAGES_CAN_ID;
    msg.dlc = 24;

    sdc_data_t sdc_data;
    sdc_data_get_sdc_voltages(&sdc_data);

    struct ucr_03_sdc_voltages_t sdc_voltages_can_msg;
    sdc_voltages_can_msg.sdc_mid1 =     sdc_data.sdc_mid1_voltage;
    sdc_voltages_can_msg.sdc_mid2 =     sdc_data.sdc_mid2_voltage;
    sdc_voltages_can_msg.sdc7 =         sdc_data.sdc_7_voltage;
    sdc_voltages_can_msg.sdc8 =         sdc_data.sdc_8_voltage;
    sdc_voltages_can_msg.sdc_end =      sdc_data.sdc_end_voltage;
    sdc_voltages_can_msg.sdc_reserve =  sdc_data.sdc_reserve_voltage;

    ucr_03_sdc_voltages_pack(msg.data, &sdc_voltages_can_msg, msg.dlc);

    com_svc_can_transmit(&msg);
}