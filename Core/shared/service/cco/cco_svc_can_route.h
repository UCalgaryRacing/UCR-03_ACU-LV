/*
 * cco_svc_can_route.h
 *
 *  Created on: Aug 17, 2026
 *      Author: SamT
 */

#ifndef SHARED_SERVICE_CCO_CCO_SVC_CAN_ROUTE_H_
#define SHARED_SERVICE_CCO_CCO_SVC_CAN_ROUTE_H_


#include "com_typ_common.h"
#include <stdbool.h>
#include "can_typ_common.h"

void cco_svc_can_rx_balance(can_msg_t *msg);

#endif /* SHARED_SERVICE_CCO_CCO_SVC_CAN_ROUTE_H_ */
