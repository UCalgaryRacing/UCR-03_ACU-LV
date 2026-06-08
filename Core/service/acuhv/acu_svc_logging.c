#include "acu_svc_logging.h"
#include "can_svc_can.h"
#include "can_config.h"
#include "acu_data.h"

#include "acu_app_state_manager.h"

void acu_svc_can_tx_acu_measurements()
{
    can_msg_t msg;
    msg.channel = CAN1;
    msg.id = ACCUMULATOR_MEASUREMENTS_CAN_ID;
    msg.dlc = 20;

    acu_measurements_t acu_measurements;
    acu_data_get_acu_measurements(&acu_measurements);

    struct ucr_03_accumulator_measurements_t accumulator_measurements_can_msg;
    accumulator_measurements_can_msg.battery_current =      acu_measurements.battery_current;
    accumulator_measurements_can_msg.battery_power =        acu_measurements.battery_power;
    accumulator_measurements_can_msg.battery_voltage =      acu_measurements.battery_voltage;
    accumulator_measurements_can_msg.ts_active =            acu_measurements.ts_active;
    accumulator_measurements_can_msg.ts_voltage =           acu_measurements.ts_voltage;
    
    accumulator_measurements_can_msg.air_neg_closed =       acu_measurements.air_neg_closed;
    accumulator_measurements_can_msg.air_pos_closed =       acu_measurements.air_pos_closed;

    accumulator_measurements_can_msg.accu_state =           acu_measurements.acu_state;
    
    ucr_03_accumulator_measurements_pack(msg.data, &accumulator_measurements_can_msg, msg.dlc);

    com_svc_can_transmit(&msg);
}

void acu_svc_can_tx_acu_energy_state()
{
    can_msg_t msg;
    msg.channel = CAN1;
    msg.id = ACCUMULATOR_ENERGY_STATE_CAN_ID;
    msg.dlc = 16;

    acu_energy_state_t acu_energy_state;
    acu_data_get_acu_energy_states(&acu_energy_state);

    struct ucr_03_accumulator_energy_state_t accumulator_energy_state_can_msg;
    accumulator_energy_state_can_msg.accu_capacity_ah = acu_energy_state.battery_capacity_ah;
    accumulator_energy_state_can_msg.accu_energy_wh =   acu_energy_state.battery_energy_wh;
    accumulator_energy_state_can_msg.accu_soc =         acu_energy_state.battery_soc;
    accumulator_energy_state_can_msg.accu_soe =         acu_energy_state.battery_soe;

    ucr_03_accumulator_energy_state_pack(msg.data, &accumulator_energy_state_can_msg, msg.dlc);

    com_svc_can_transmit(&msg);
}

