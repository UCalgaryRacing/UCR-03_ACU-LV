#ifndef BMS_SVC_THERMISTOR_H
#define BMS_SVC_THERMISTOR_H

#include <stdint.h>
#include <stdbool.h>
#include "bms_drv_adbms6830_regs.h"

/**
 * @brief Select a mux channel by driving GPIO3..GPIO6 on every slave.
 *
 * The 4 LSBs of @p channel are written to S0..S3 of both per-slave muxes
 * (GPIO3 = S0, GPIO4 = S1, GPIO5 = S2, GPIO6 = S3). All other CFGA bits
 * (REFON, comparator, other GPOs, etc.) are preserved.
 *
 * @param channel  Mux channel 0..15.
 */
void bms_svc_set_mux(uint8_t channel);

void bms_svc_acquire_all_cell_temperatures(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC]);
bool bms_svc_check_all_cell_temperature_limits(float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC]); 
#endif
