#ifndef DRIVER_ACULV_DRV_SDC_H_
#define DRIVER_ACULV_DRV_SDC_H_

#include <stdbool.h>

// IMD
void aculv_drv_set_imd_latch_en(bool enable);

// BMS
void aculv_drv_set_bms_latch_en(bool enable);
void aculv_drv_set_bms_ok(bool enable);

#endif  /*DRIVER_ACULV_DRV_SDC_H_*/
