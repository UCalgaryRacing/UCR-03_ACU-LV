#ifndef SERVICE_ACUHV_SVC_AIR_H_
#define SERVICE_ACUHV_SVC_AIR_H_

#include <stdbool.h>
#include "com_typ_common.h"

status_t acuhv_svc_air_init(void);

void acuhv_svc_air_close_air_neg(bool close);
void acuhv_svc_air_close_air_pos(bool close);

#endif /*SERVICE_ACUHV_SVC_AIR_H_*/
