#include "acu_svc_logging.h"
#include "can_svc_can.h"
#include "can_config.h"
#include "acu_data.h"

#include "acu_app_state_manager.h"

void acu_svc_can_tx_acu_data()
{
    can_msg_t msg;
    msg.channel = CAN1;
    msg.id = ACCUMULATOR_DATA_CAN_ID;
    msg.dlc = 20;

    acu_data_t acu_data;
    acu_data_get_acu_data(&acu_data);

    struct ucr_03_accumulator_data_t accumulator_can_msg;
    accumulator_can_msg.battery_current = acu_data.battery_current;
    accumulator_can_msg.battery_power = acu_data.battery_power;
    accumulator_can_msg.battery_voltage = acu_data.battery_voltage;
    accumulator_can_msg.ts_active = acu_data.ts_active;
    accumulator_can_msg.ts_voltage = acu_data.ts_voltage;
    
    ucr_03_accumulator_data_pack(msg.data, &accumulator_can_msg, msg.dlc);

    com_svc_can_transmit(&msg);
}


void acu_svc_can_tx_ts_state_update()
{
    if (acu_data_get_acu_state() == ACU_APP_STATE_ACTIVE)
    {
        acu_data_set_acu_ts_active(true);
    }
}