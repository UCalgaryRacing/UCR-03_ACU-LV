#include "bms_svc_logging.h"

#include "can_svc_can.h"
#include "ucr_03.h"

#include <string.h>

#define BMS_CAN_DLC                     (64U)
#define BMS_THERMS_PRIMARY_PER_MSG      (13U)
#define BMS_THERMS_EXT_PER_MSG          (5U)

static void bms_svc_can_tx_slave_voltages(uint8_t slave_idx, const float cell_voltages[ADBMS_CELLS_PER_IC])
{
    can_msg_t msg;
    struct ucr_03_slave_voltage1_t payload;

    msg.channel = CAN1;
    msg.id = UCR_03_SLAVE_VOLTAGE1_FRAME_ID + slave_idx;
    msg.dlc = BMS_CAN_DLC;

    memcpy(&payload, cell_voltages, sizeof(payload));
    ucr_03_slave_voltage1_pack(msg.data, &payload, msg.dlc);

    com_svc_can_transmit(&msg);
}

static void bms_svc_can_tx_slave_temperatures(uint8_t slave_idx, const float cell_temps[ADBMS_THERMS_PER_IC])
{
    can_msg_t msg;
    struct ucr_03_slave_temperature1_t primary_payload;
    struct ucr_03_slave_temperature_ext1_t ext_payload;

    msg.channel = CAN1;
    msg.dlc = BMS_CAN_DLC;

    msg.id = UCR_03_SLAVE_TEMPERATURE1_FRAME_ID + slave_idx;
    memcpy(&primary_payload, cell_temps, BMS_THERMS_PRIMARY_PER_MSG * sizeof(float));
    ucr_03_slave_temperature1_pack(msg.data, &primary_payload, msg.dlc);
    com_svc_can_transmit(&msg);

    msg.id = UCR_03_SLAVE_TEMPERATURE_EXT1_FRAME_ID + slave_idx;
    memcpy(&ext_payload, &cell_temps[BMS_THERMS_PRIMARY_PER_MSG], BMS_THERMS_EXT_PER_MSG * sizeof(float));
    ucr_03_slave_temperature_ext1_pack(msg.data, &ext_payload, msg.dlc);
    com_svc_can_transmit(&msg);
}

void bms_svc_can_tx_all_cell_voltages(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC])
{
    for (uint8_t slave_idx = 0U; slave_idx < ADBMS_NUM_SLAVES; slave_idx++)
    {
        bms_svc_can_tx_slave_voltages(slave_idx, cell_voltages[slave_idx]);
    }
}

void bms_svc_can_tx_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC])
{
    for (uint8_t slave_idx = 0U; slave_idx < ADBMS_NUM_SLAVES; slave_idx++)
    {
        bms_svc_can_tx_slave_temperatures(slave_idx, cell_temps[slave_idx]);
    }
}
