#include "can_svc_can.h"
#include "acu_data.h"


void bms_svc_can_tx_acu_fault_data()
{
    can_msg_t msg;
    msg.channel = CAN1;
	msg.id = ACCUMULATOR_FAULT_CAN_ID;
	msg.dlc = 1;

    acu_fault_t acu_fault;
    acu_data_get_fault_status(&acu_fault);

    struct ucr_03_accumulator_fault_t accumulator_fault_struct;
    accumulator_fault_struct.bms_fault = acu_fault.bms_fault;
    accumulator_fault_struct.imd_fault = acu_fault.imd_fault;
    ucr_03_accumulator_fault_pack(msg.data, &accumulator_fault_struct, msg.dlc);

    com_svc_can_transmit(&msg);
}