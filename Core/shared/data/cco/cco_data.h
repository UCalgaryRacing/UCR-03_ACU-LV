/*
 * cco_data.h
 *
 *  Created on: Aug 19, 2026
 *      Author: sushi
 */

#ifndef CCO_DATA_H_
#define CCO_DATA_H_

#include <stdint.h>
#include <stdbool.h>
#include "com_typ_common.h"

typedef struct
{
    bool   balance_request;         /**< Do we want to balance at all */
    uint8_t   balance_duration;         /**< How long to balnce for in minutes */
} cco_data_t;

/*============================================================================*/
/* Setters                                                                    */
/*============================================================================*/

void cco_data_set_balance(bool balance);
void cco_data_set_balance_duration(uint8_t balance_duration);
status_t cco_data_set_data(cco_data_t *cco_data);

/*============================================================================*/
/* Getters                                                                    */
/*============================================================================*/

status_t cco_data_get_data(cco_data_t *cco_data);
bool cco_data_get_balance(void);
uint8_t cco_data_get_balance_duration(void);
#endif /* SHARED_DATA_CCO_CCO_DATA_H_ */
