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

// the amc3306 has 16-bits of resolution
// has a different voltage mapping than normal adc, look at section 7.3.4 in datasheet
#define AMC33X6XX_ADC_RESOLUTION (1<<16)

#define ACM3306M05_ADC_MAX_VOLTAGE 0.05f
#define AMC3336_ADC_MAX_VOLTAGE 1.0f



#endif // DRIVERS_AMC33X6XX_H_