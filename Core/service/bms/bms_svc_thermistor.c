#include "cmsis_os2.h"
#include "acu_lv_drv_adbms6830.h"
#include "acu_lv_svc_adbms6830.h"
#include "acu_lv_drv_adbms6830_regs.h"

// void bms_svc_admbs_toggle_mux(uint16_t gpio);



/*============================================================================*/
/* Temperature Sampling                                                       */
/*============================================================================*/

static uint16_t raw_temps[ADBMS_NUM_SLAVES][ADBMS_NUM_GPIOS];
static float processed_temps[ADBMS_NUM_SLAVES][ADBMS_NUM_GPIOS];



static float calculate_thermistor_temperature(float adc_voltage)
{
  //stole this shit from arduino forum!!!
  float steinhart;
  float resistance = 10000 * adc_voltage / (3 - adc_voltage);
  steinhart = resistance / 10000;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= 3950;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (25 + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;

  return steinhart;

  
}

//TODO add this to adbms drivers
void bms_svc_admbs_toggle_mux(adbms_gpo_pin_t pin)
{
    adbms6830_shadow_t *shadow = bms_manager_get_shadow();

    //mux control connected to gpio1 which is bit 0 of byte 3
    shadow->cfga[3] ^= ADBMS_GPO1_MASK;

    adbms6830_write_cfga(shadow);

    adbms6830_read_cfga(shadow);
}



void bms_svc_acquire_thermistor_temps()
{
    int result = adbms6830_start_gpio_adc();

    //TODO remove hardcoded delay
    osDelay(1);

    result = adbms6830_read_gpio_voltages_raw(raw_temps);

    for (int slave = 0; slave < ADBMS_NUM_SLAVES; slave++)
    {
        for (int thermistor = 0; thermistor < 18; thermistor++)
        {
            float thermistor_voltage = adbms6830_adc_to_volts(raw_temps[slave][thermistor]);
            processed_temps[slave][thermistor] = calculate_thermistor_temperature(thermistor_voltage);
        }

    }

    // bms_svc_admbs_toggle_gpio(ADBMS_GPO_PIN_1);
    
}

