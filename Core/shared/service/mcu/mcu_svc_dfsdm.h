#ifndef SERVICE_ACUHV_SVC_DFSDM_H_
#define SERVICE_ACUHV_SVC_DFSDM_H_

#include "acuhv_config.h"
#include "com_typ_common.h"

status_t mcu_svc_dfsdm_start(mcu_dfsdm_filters_id_t dfsdm_id);
status_t mcu_svc_dfsdm_stop(mcu_dfsdm_filters_id_t dfsdm_id);

status_t mcu_svc_dfsdm_read_raw(mcu_dfsdm_filters_id_t dfsdm_id, int32_t *raw_val);
status_t mcu_svc_dfsdm_get_scaled(mcu_dfsdm_filters_id_t dfsdm_id, float *scaled_val);
status_t mcu_svc_dfsdm_get_scaled_shift(mcu_dfsdm_filters_id_t dfsdm_id, float *scaled_val);


#endif /*SERVICE_ACUHV_SVC_DFSDM_H_*/