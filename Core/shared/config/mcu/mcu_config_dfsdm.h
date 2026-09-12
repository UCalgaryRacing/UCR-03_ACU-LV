#ifndef MCU_CONFIG_DFSDM_FILTERS_H_
#define MCU_CONFIG_DFSDM_FILTERS_H_


#include <stdint.h>
#include <stdbool.h>
#include "stm32h7xx_hal.h"

/*============================================================================*/
/* AMC33X6XX Settings and Configuration                                       */
/*============================================================================*/

typedef struct 
{
    DFSDM_Filter_HandleTypeDef *filter_handle;
    bool dma_started;
} mcu_dfsdm_context_t;

typedef struct
{
    mcu_dfsdm_context_t *dfsdm_context;
    uint8_t dfsdm_buffer_number;
} mcu_dfsdm_hw_t;

typedef struct
{
    float valid_min;
    float valid_max;
    float scaling_factor;    
} mcu_dfsdm_settings_t;

typedef struct
{
    mcu_dfsdm_hw_t hw;
    mcu_dfsdm_settings_t settings;
} mcu_dfsdm_config_t;

#endif /*MCU_CONFIG_DFSDM_FILTERS_H_*/