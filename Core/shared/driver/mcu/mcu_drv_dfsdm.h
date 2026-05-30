#ifndef DRIVER_MCU_DRV_DFSDM_H_
#define DRIVER_MCU_DRV_DFSDM_H_

#include "acuhv_config.h"
#include "stm32h7xx_hal.h"
#include "com_typ_common.h"

// start and stop
status_t mcu_drv_start_DFSDM_filter(const mcu_dfsdm_hw_t *hw);
status_t mcu_drv_stop_DFSDM_filter(const mcu_dfsdm_hw_t *hw);

// read data
status_t mcu_drv_DFSDM_read_raw(const mcu_dfsdm_hw_t *hw, int32_t *dfsdm_val);

#endif /*DRIVER_MCU_DRV_DFSDM_H_*/