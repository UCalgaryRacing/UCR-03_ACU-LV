/*
 * bms_svc_cell_balancing.h
 *
 *  Created on: Jul 18, 2026
 *      Author: SamT
 */

#ifndef SERVICE_BMS_BMS_SVC_CELL_BALANCING_H_
#define SERVICE_BMS_BMS_SVC_CELL_BALANCING_H_

#include "bms_svc_cell_balancing.h"
#include "bms_svc_cell_voltage.h"
#include "bms_config.h"
#include "bms_data.h"
#include "bms_drv_adbms6830.h"

#include <stdbool.h>

void cell_balance_init(void);

void bms_svc_pwm_bal_init(void);

int bms_pwm_diagnostic_cycle(void);

void bms_svc_balance(void);

void bms_svc_balance_only_highest(void);

void bms_svc_acquire_lowest_cell(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC],
		float *lowest_voltage,
		int *lowest_slave_idx,
		int *lowest_cell_idx);

void bms_svc_acquire_highest_cell(float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC],
		float *highest_voltage,
		int *highest_slave_idx,
		int *highest_cell_idx);


void adbms6830_bal_start_1min(uint16_t *masks);

#endif /* SERVICE_BMS_BMS_SVC_CELL_BALANCING_H_ */
