#ifndef RCO_DATA_H_
#define RCO_DATA_H_

#include <stdint.h>
#include <stdbool.h>
#include "com_typ_common.h"

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/

status_t rco_data_init(void);

/*============================================================================*/
/* RCO Data Struct                                                            */
/*============================================================================*/

typedef struct
{
    bool tssi_faulted;
    bool brake_light_on;
    bool drs_active;
    bool reset_pressed;
} rco_data_t;

/*============================================================================*/
/* Setters                                                                    */
/*============================================================================*/

void rco_data_set_reset_pressed(bool reset_pressed);
void rco_data_set_brake_light(bool brake_light_on);
void rco_data_set_tssi_faulted(bool tssi_faulted);
status_t rco_data_set_data(rco_data_t *rco_data);

/*============================================================================*/
/* Getters                                                                    */
/*============================================================================*/

status_t rco_data_get_data(rco_data_t *rco_data);
bool rco_data_get_reset_pressed(void);


#endif /* RCO_DATA_H_ */
