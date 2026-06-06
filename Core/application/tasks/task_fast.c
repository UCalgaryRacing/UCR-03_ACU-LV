#include "task_fast.h"
#include "cmsis_os2.h"

#include "mcu_svc_analog.h"
#include "mcu_svc_dfsdm.h"

#include "acuhv_config.h"

#include "acuhv_svc_batt_voltage.h"
#include "acuhv_svc_batt_current.h"
#include "acuhv_svc_ts.h"
#include "acuhv_svc_batt_power.h"

#include "acuhv_svc_air.h"
#include "acu_svc_soh.h"
#include "aculv_svc_sdc.h"

#include "acu_svc_logging.h"
#include "rco_svc_can_route.h"
#include "aculv_svc_sdc_logging.h"

static const uint32_t period = 10;
static uint32_t nextWakeTime;


void task_fast_init(void)
{
    nextWakeTime = osKernelGetTickCount();

    //---------------- SDC ----------------//
    // toggle sdc latches and set ok pins high
    aculv_svc_sdc_init();

    //---------------- MCU DFSDM ----------------//
    mcu_svc_dfsdm_start(TS_VOLTAGE);
    mcu_svc_dfsdm_start(BATT_VOLTAGE);
    mcu_svc_dfsdm_start(BATT_CURRENT);
    acu_svc_init_acu_energy_state(); 

    //---------------- MCU ADC ----------------//
    mcu_svc_analog_init();

    mcu_svc_analog_start(SDC_RESERVE);
    mcu_svc_analog_start(SDC_7);
    mcu_svc_analog_start(SDC_8);
    mcu_svc_analog_start(SDC_MID_1);
    mcu_svc_analog_start(SDC_MID_2);
    mcu_svc_analog_start(SDC_END);
    
    //---------------- AIRs ----------------//
    acuhv_svc_air_init(); // open both airs

    //---------------- CAN ----------------//
    rco_svc_can_route_init();

}

void task_fast_loop(void){
    nextWakeTime += period;

    //---------------- Battery Pack + TS  ----------------//

    acuhv_svc_update_batt_voltage();
    acuhv_svc_update_batt_current();
    acuhv_svc_update_ts_voltage();
    acuhv_svc_update_batt_power();
    // ts active is updated by app state manager --> task manager

    acu_svc_update_acu_energy_state();

    //---------------- SDC ----------------//
    aculv_svc_update_sdc_voltages();
    aculv_svc_update_sdc_latches();

    //---------------- CAN ----------------//
    acu_svc_can_tx_acu_measurements();
    acu_svc_can_tx_acu_energy_state();
    aculv_svc_can_tx_sdc_voltages();

    osDelayUntil(nextWakeTime);

}
