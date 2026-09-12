#ifndef APPLICATION_ACU_APP_STATE_MANAGER_H_
#define APPLICATION_ACU_APP_STATE_MANAGER_H_

// public function prototypes
void acu_app_state_machine_init(void);
void acu_app_state_machine_step(void);

typedef enum
{
    ACU_APP_STATE_STARTUP = 0U,
    ACU_APP_STATE_IDLE,
    ACU_APP_STATE_PRECHARGE,
    ACU_APP_STATE_ACTIVE,
    ACU_APP_STATE_FAULT,
    // ACU_APP_STATE_CHARGING,
    // ACU_APP_STATE_BALANCING
} acu_app_state_t;

void acu_app_state_machine_update_state(void);


#endif /* APPLICATION_ACU_APP_STATE_MANAGER_H_ */