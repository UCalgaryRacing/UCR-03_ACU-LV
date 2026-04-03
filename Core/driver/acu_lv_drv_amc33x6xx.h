/**
 * acu_lv_drv_amc3306m05.h
 * 
 * Driver layer file for AMC3306M05 and AMC3336
 * 
 * AMC3306M05 --> +/-50mV adc used on shunt board
 * 
 * AMC3336 --> +/-1V adc used on hv for measuring ACCU and TS
 */

#ifndef DRIVERS_AMC33X6XX_H_
#define DRIVERS_AMC33X6XX_H_

#include "acu_lv_config.h"
#include "acu_lv_config_pinout.h"

#define AMC33X6XX_ADC_RESOLUTION (1<<24)


static inline void start_DFSDM_filter_conversion(DFSDM_Filter_HandleTypeDef * filter, int32_t * buffer, uint8_t length)
{
    HAL_DFSDM_FilterRegularStart_DMA(filter,buffer,length);
}

static inline void stop_DFSDM_filter_conversion(DFSDM_Filter_HandleTypeDef * filter)
{
    HAL_DFSDM_FilterRegularStop_DMA(filter);
}

static inline void shift_input_data(int32_t * raw_data, int32_t *shifted_data)
{
    for(uint8_t i = 0; i < CURRENT_SHUNT_DATA_LENGTH; i++)
    {
        shifted_data[i] = raw_data[i] >> 8;
    }
}


#endif // DRIVERS_AMC33X6XX_H_