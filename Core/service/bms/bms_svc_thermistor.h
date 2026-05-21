#ifndef BMS_SVC_THERMISTOR_H
#define BMS_SVC_THERMISTOR_H

#include "bms_drv_adbms6830_regs.h"
#include "com_typ_common.h"

void bms_svc_acquire_thermistor_temps(uint8_t mux_state);
void bms_svc_admbs_toggle_mux(adbms_gpo_pin_t pin);
bool bms_svc_check_temps();
void vw_temps();

void bms_svc_acquire_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC]);
bool bms_svc_check_all_cell_temperature_limits(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC]); 
#endif