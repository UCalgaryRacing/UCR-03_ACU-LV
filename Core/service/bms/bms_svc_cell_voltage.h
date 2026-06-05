#ifndef BMS_SVC_CELL_VOLTAGE_H
#define BMS_SVC_CELL_VOLTAGE_H

#include <stdbool.h>
#include "bms_config.h"

void bms_svc_acquire_all_cell_voltages(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC]);

bool bms_svc_check_all_cell_voltage_limits(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC]);

#endif