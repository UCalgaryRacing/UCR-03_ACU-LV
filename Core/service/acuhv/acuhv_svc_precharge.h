#ifndef SERVICE_ACUHV_SVC_PRECHARGE_H_
#define SERVICE_ACUHV_SVC_PRECHARGE_H_
// NOT USED ANYMORE (NO PRECHARGE TIMEOUT FAULT)


#define ACUHV_PRECHARGE_MAX_DURATION_MS 15000

void acuhv_svc_precharge_start(void);
void acuhv_svc_precharge_update_fault_timeout(void);

#endif /* SERVICE_ACUHV_SVC_PRECHARGE_H_ */
