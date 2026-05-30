#ifndef SERVICE_ACULV_SVC_SDC_H_
#define SERVICE_ACULV_SVC_SDC_H_

#include <stdbool.h>
#include "com_typ_common.h"

// initialization
status_t aculv_svc_sdc_init();

// imd/bms status
void aculv_svc_set_bms_ok(bool enable);
void aculv_svc_set_imd_ok(bool enable);

// update latch based on reset button
void aculv_svc_update_sdc_latches();

// data voltage update
status_t aculv_svc_update_sdc_voltages();


#endif /*SERVICE_ACULV_SVC_SDC_H_*/