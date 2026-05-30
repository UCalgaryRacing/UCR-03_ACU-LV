#ifndef DATA_SDC_DATA_H_
#define DATA_SDC_DATA_H_

#include "com_typ_common.h"
#include <stdbool.h>
#include <stdio.h>

/*============================================================================*/
/* SDC ADCs Data Structure                                                    */
/*============================================================================*/

typedef struct
{
    float sdc_mid1_voltage;
    float sdc_mid2_voltage;
    float sdc_7_voltage;
    float sdc_8_voltage;
    float sdc_end_voltage;
    float sdc_reserve_voltage;
} sdc_data_t;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/
status_t sdc_data_init(void);

/*============================================================================*/
/* Setters                                                                    */
/*============================================================================*/
status_t sdc_data_set_sdc_data(const sdc_data_t *sdc_data);
void sdc_data_set_sdc_mid1_voltage(float voltage);
void sdc_data_set_sdc_mid2_voltage(float voltage);
void sdc_data_set_sdc_7_voltage(float voltage);
void sdc_data_set_sdc_8_voltage(float voltage);
void sdc_data_set_sdc_end_voltage(float voltage);
void sdc_data_set_sdc_reserve_voltage(float voltage);

/*============================================================================*/
/* Getters                                                                    */
/*============================================================================*/
status_t sdc_data_get_sdc_voltages(sdc_data_t *sdc_data);
float sdc_data_get_mid1_voltage(void);
float sdc_data_get_mid2_voltage(void);
float sdc_data_get_sdc_8_voltage(void);
float sdc_data_get_sdc_7_voltage(void);
float sdc_data_get_sdc_end_voltage(void);
float sdc_data_get_sdc_reserve_voltage(void);

#endif /*DATA_SDC_DATA_H_*/
