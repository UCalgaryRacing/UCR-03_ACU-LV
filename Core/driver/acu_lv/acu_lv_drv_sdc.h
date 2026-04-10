/*
 * acu_lv_drv_sdc.h
 *
 *  Created on: Apr 10, 2026
 *      Author: clayd
 */

#ifndef DRIVER_ACU_LV_DRV_SDC_H_
#define DRIVER_ACU_LV_DRV_SDC_H_

#include "acu_lv_config.h"

void acu_lv_drv_sdc_init();

void acu_lv_drv_set_imd_latch();
void acu_lv_drv_reset_imd_latch();

void acu_lv_drv_set_ams_latch();
void acu_lv_drv_reset_ams_latch();

void acu_lv_drv_set_ams_ok();
void acu_lv_drv_reset_ams_ok();


#endif /* DRIVER_ACU_LV_DRV_SDC_H_ */
