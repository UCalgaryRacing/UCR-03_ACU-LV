#ifndef BMS_SVC_THERMISTOR_H
#define BMS_SVC_THERMISTOR_H

#include <stdbool.h>
#include "bms_config.h"

void bms_svc_acquire_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC]);
bool bms_svc_check_all_cell_temperature_limits(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC]);

#endif
