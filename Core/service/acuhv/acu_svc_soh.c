#include "acu_svc_soh.h"
#include "acuhv_svc_batt_voltage.h"
#include "acu_data.h"

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


/* function that splits the curve into multiple straight line segments using nested if statements*/
#define VOLTAGE_TO_SOC_1C(v) \
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

    float soc = VOLTAGE_TO_SOC_1C((acu_bus_voltage/ACU_PACK_SERIES_CELL_COUNT)); // convert bus voltage to cell voltage for SOC calculation

    float Capacity_Ah = ACU_PACK_CAPACITY_AH * (soc / 100.0f);
    float Energy_Wh = Capacity_Ah * acu_bus_voltage; 
    float soe = (Energy_Wh / ACU_PACK_ENERGY_WH) * 100.0f;

    /*set the initial values in this file, these will be used since the INA gives you the time intregal of charge and energy, no need to perform time intregal ourselves*/

    initial_soc = soc;
    initial_soe = soe;
    initial_energy_wh = Energy_Wh;
    initial_capacity_ah = Capacity_Ah;

    acu_data_set_acu_energy_states(soc, soe, Energy_Wh, Capacity_Ah);

}


/*                                                  UPDATE SOC                                                                   */
/* function reads the values for the accumelated charge and energy spent form the INA229 and subtracts it from the initial values*/
/* function then updates the data layer                                                                                          */
void acu_svc_update_acu_energy_state_alternative(void){
    if (completion_time_of_last_update == 0.0f)
    {
        // This is the first update, so we just set the completion time and return without updating SOC
        completion_time_of_last_update = HAL_GetTick();
        return;
    }

    /* find the amount of time passed to integrate the current over*/
    uint32_t previous_complete_time = completion_time_of_last_update;
    uint32_t current_time = HAL_GetTick();
    time_delta_ms = current_time - previous_complete_time;
    completion_time_of_last_update = current_time; // update the completion time for the next iteration


    /* read the value of the shunt current in AMPs passing through the shunt board and then perform time intregal to fina capacity*/
	float capacity_discharged_Ah;
    float current_A = acu_data_get_acu_battery_current();
    capacity_discharged_Ah = (current_A * (float)time_delta_ms) / (3600.0f * 1000.0f); // Convert current and time delta to Ah

    float previous_acu_capacity_Ah = acu_data_get_acu_charge_Ah();
    float current_acu_capacity_Ah = previous_acu_capacity_Ah - capacity_discharged_Ah; // Add because current will be negative during discharge
    float current_soc = (current_acu_capacity_Ah / ACU_PACK_CAPACITY_AH) * 100.0f;

    

    float energy_discharged_Wh;
    float voltage_V = acu_data_get_acu_battery_voltage();
    energy_discharged_Wh = capacity_discharged_Ah * voltage_V; // calculating energy discharge in order to update soe, uses current accumelator battery voltage. 

    float previous_acu_energy_Wh = acu_data_get_acu_energy_Wh();
    float current_acu_energy_Wh = previous_acu_energy_Wh - energy_discharged_Wh;
    float current_soe = (current_acu_energy_Wh / ACU_PACK_ENERGY_WH) * 100.0f;

    
    acu_data_set_acu_energy_states(current_soc, current_soe, current_acu_energy_Wh, current_acu_capacity_Ah);

}

                                    /* ALTERNATIVE IMPLEMENTATION */
// this one grabs the "open circuit" voltage by grabbing the voltage when the current going into the pack is below some values (say 10)
// then it applies the same soc init function from open voltage and resets SOC.

void acu_svc_update_acu_energy_state(void){

    float current_A = acu_data_get_acu_battery_current();
    if (current_A < 10.0f && current_A >= 0.0f) // If the current is very low in magnitude and flowing forward, we can assume the pack is at open circuit voltage and use that to update SOC
    {
        float acu_bus_voltage = acu_data_get_acu_battery_voltage();
        float soc = VOLTAGE_TO_SOC_1C((acu_bus_voltage/ACU_PACK_SERIES_CELL_COUNT)); // convert bus voltage to cell voltage for SOC calculation

        float Capacity_Ah = ACU_PACK_CAPACITY_AH * (soc / 100.0f);
        float Energy_Wh = Capacity_Ah * acu_bus_voltage; 
        float soe = (Energy_Wh / ACU_PACK_ENERGY_WH) * 100.0f;

        acu_data_set_acu_energy_states(soc, soe, Energy_Wh, Capacity_Ah);
    }

    return; // If the current is not low enough, we do not update SOC and just return.


}

