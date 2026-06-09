#ifndef BMS_SVC_LOGGING_H_
#define BMS_SVC_LOGGING_H_

#include "bms_config.h"

void bms_svc_can_tx_all_cell_voltages(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC]);
void bms_svc_can_tx_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC]);

#endif /* BMS_SVC_LOGGING_H_ */
