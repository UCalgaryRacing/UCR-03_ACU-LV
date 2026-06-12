#include "task_medium.h"
#include "cmsis_os2.h"

#include "bms_config.h"
#include "bms_svc_thermistor.h"
#include "bms_svc_cell_voltage.h"
#include "bms_svc_logging.h"
#include "acu_data.h"

static const uint32_t period = 1;
static uint32_t nextWakeTime;

static float cell_voltages[ADBMS_NUM_SLAVES][ADBMS_CELLS_PER_IC];
static float cell_temps[ADBMS_NUM_SLAVES][ADBMS_THERMS_PER_IC];
static bool bms_fault = false;

void task_medium_init(void)
{
	nextWakeTime = osKernelGetTickCount();
}

void task_medium_loop(void)
{
	nextWakeTime += period;

	bms_fault = false;

	bms_svc_acquire_all_cell_voltages(cell_voltages);
	//bms_fault |= bms_svc_check_all_cell_voltage_limits(cell_voltages);


    bms_svc_acquire_all_cell_temperatures(cell_temps);
	//bms_fault |=  bms_svc_check_all_cell_temperature_limits(cell_temps);

    bms_svc_can_tx_all_cell_voltages(cell_voltages);
    bms_svc_can_tx_all_cell_temperatures(cell_temps);

	acu_data_set_bms_fault_status(bms_fault);


	osDelayUntil(nextWakeTime);
}
