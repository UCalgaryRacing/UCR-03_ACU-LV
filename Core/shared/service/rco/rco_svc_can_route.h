#ifndef RCO_SVC_CAN_ROUTE_H_
#define RCO_SVC_CAN_ROUTE_H_

#include "com_typ_common.h"
#include <stdbool.h>
#include "can_typ_common.h"

status_t rco_svc_can_route_init(void);
void rco_svc_can_rx_reset_data(can_msg_t *msg);

#endif /* ACU_SVC_CAN_ROUTE_H_ */