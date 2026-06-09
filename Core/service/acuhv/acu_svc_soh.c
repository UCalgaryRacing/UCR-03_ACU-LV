#include "acu_svc_soh.h"
#include "acuhv_svc_batt_voltage.h"
#include "acu_data.h"
#include <math.h>

#include "stm32h7xx_hal.h"

/*============================================================================*/
/* Private Variables                                                          */
/*============================================================================*/
static float initial_soc = 100.0f; // Start at 100% SOC, will be updated on first run of task_fast
static float initial_soe = 100.0f; // Start at 100% SOE, will be updated on first run of task_fast
static float initial_energy_wh = ACU_PACK_ENERGY_WH;
static float initial_capacity_ah = ACU_PACK_CAPACITY_AH;

static float completion_time_of_last_update; // Time in milliseconds when the last update was completed, used for calculating time delta for coulomb counting.
static uint32_t time_delta_ms;

static float internal_resistance_accu_to_shunt = 0.0f; // will use this for more accurate energy calculations.
static float initial_unsagged_accu_voltage = 0.0f; // this is the voltage of the accu without the voltage drop from the internal resistance, will be used for more accurate energy calculations.
static bool internal_resistance_calculated = false;




/*********************** SOC CALCULATION MACROS **************************/
// this one I made manually.
#define VOLTAGE_TO_SOC_OPEN_VOLTAGE(v) \
    (100*((v) >= 4.2f ? 100.0f : \
    (v) >= 4.1 ? (v)*0.9 -2.765 : \
    (v) >= 4.0 ? (v)*0.75 - 2.1575 : \
    (v) >= 3.50f ? (v)*1.01 -3.205 : \
    (v) >= 3.0f ? (v)*0.5 - 1.41666667 : \
    (v) >= 2.50f ?  (v)*0.166666 - 0.416666 : 0.0f))




/*                                                  INITIALIZE SOC                                      */
/* function needs to grab the voltage of the acu bus and calculate the state of charge                  */
/* this function should be called during the 1st initialization function, so propably fast task init    */
void acu_svc_init_acu_energy_state(void){

	float acu_bus_voltage;
    acuhv_svc_update_batt_voltage();
    acu_bus_voltage = acu_data_get_acu_battery_voltage();
    initial_unsagged_accu_voltage = acu_bus_voltage; 
    float soc_average = VOLTAGE_TO_SOC_OPEN_VOLTAGE((acu_bus_voltage/ACU_PACK_SERIES_CELL_COUNT));



    float Capacity_Ah = ACU_PACK_CAPACITY_AH * (soc_average / 100.0f);
    float Energy_Wh = Capacity_Ah * acu_bus_voltage; 
    float soe = (Energy_Wh / ACU_PACK_ENERGY_WH) * 100.0f;

    /*set the initial values in this file, these will be used since the INA gives you the time intregal of charge and energy, no need to perform time intregal ourselves*/

    initial_soc = soc_average;
    initial_soe = soe;
    initial_energy_wh = Energy_Wh;
    initial_capacity_ah = Capacity_Ah;

    acu_data_set_acu_energy_states(soc_average, soe, Energy_Wh, Capacity_Ah);

}


/*                                                  UPDATE SOC                                                                   */
/* function reads the values for the accumelated charge and energy spent form the INA229 and subtracts it from the initial values*/
/* function then updates the data layer                                                                                          */
void acu_svc_update_acu_energy_state(void){

    /*--------------------------------HANDLE INITIAL CALIBRATIONS--------------------------------*/
    if (completion_time_of_last_update == 0.0f)
    {
        // This is the first update, so we just set the completion time and return without updating SOC
        completion_time_of_last_update = HAL_GetTick();
        return;
    }

    float current_A = acu_data_get_acu_battery_current();

    if (!internal_resistance_calculated && (current_A) > 10.0) // only calculate internal resistance once we have a significant current to improve accuracy, and only do it once.
    {
        float voltage_at_shunt_V = acu_data_get_acu_battery_voltage();
        internal_resistance_accu_to_shunt = (initial_unsagged_accu_voltage - voltage_at_shunt_V) / current_A; // calculate internal resistance using Ohm's law.

        internal_resistance_calculated = true;
    }


/*--------------------------------FIND TIME DELTA--------------------------------*/
    /* find the amount of time passed to integrate the current over*/
    uint32_t previous_complete_time = completion_time_of_last_update;
    uint32_t current_time = HAL_GetTick();
    time_delta_ms = current_time - previous_complete_time;
    completion_time_of_last_update = current_time; // update the completion time for the next iteration


/*--------------------------------CALCULATE SOC FROM CURRENT--------------------------------*/
	float capacity_discharged_Ah;
    
    capacity_discharged_Ah = (current_A * (float)time_delta_ms) / (3600.0f * 1000.0f); // Convert current and time delta to Ah

    float previous_acu_capacity_Ah = acu_data_get_acu_charge_Ah();
    float current_acu_capacity_Ah = previous_acu_capacity_Ah - capacity_discharged_Ah; // Add because current will be negative during discharge
    float soc_current_calculated = (current_acu_capacity_Ah / ACU_PACK_CAPACITY_AH) * 100.0f;

    /*--------------------------------CALCULATE SOC FROM VOLTAGE--------------------------------*/
    float acu_bus_voltage = acu_data_get_acu_battery_voltage();
    float unsagged_acu_voltage = acu_bus_voltage + (current_A * internal_resistance_accu_to_shunt); // compensate for voltage drop across internal resistance for more accurate energy calculations.
    float soc_voltage_calculated = VOLTAGE_TO_SOC_OPEN_VOLTAGE((unsagged_acu_voltage/ACU_PACK_SERIES_CELL_COUNT)); // calculate SOC from voltage using the open circuit voltage curve.
      
    
    /*--------------------------------CALCULATE SOC AVERAGE--------------------------------*/
    
       float soc_average = (soc_current_calculated + soc_voltage_calculated) / 2.0f;

    
  /*--------------------------------CALCULATE SOE FROM CURRENT AND SOC BASED ON VOLTAGE--------------------------------*/
    float energy_discharged_Wh;
    energy_discharged_Wh = capacity_discharged_Ah * unsagged_acu_voltage; // calculating energy discharge in order to update soe, uses current accumelator battery voltage. 
    float previous_acu_energy_Wh = acu_data_get_acu_energy_Wh();
    float current_acu_energy_Wh = previous_acu_energy_Wh - energy_discharged_Wh;
    float soe_current_calculated = (current_acu_energy_Wh / ACU_PACK_ENERGY_WH) * 100.0f;

    float soe_soc_calculated = (soc_average/100.0f) *ACU_PACK_CAPACITY_AH * unsagged_acu_voltage;
    float soe_average = (soe_current_calculated + soe_soc_calculated) / 2.0f;


    acu_data_set_acu_energy_states(soc_average, soe_average, current_acu_energy_Wh, current_acu_capacity_Ah);

}
