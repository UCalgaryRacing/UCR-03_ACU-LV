#include <string.h>
#include "rco_data.h"


/*============================================================================*/
/* Private Data Storage                                                       */
/*============================================================================*/

static rco_data_t g_rco_data;
static bool g_initialized;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/

status_t rco_data_init(void)
{
    memset(&g_rco_data, 0, sizeof(g_rco_data));
    g_rco_data.tssi_faulted = false;
    g_rco_data.brake_light_on = false;
    g_rco_data.drs_active = false;
    g_rco_data.reset_pressed = false;

    g_initialized = true;

    return OK;
}


status_t rco_data_get_data(rco_data_t *rco_data)
{
    if (rco_data == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    *rco_data = g_rco_data;

    return OK;
}

status_t rco_data_set_data(rco_data_t *rco_data)
{
    if (rco_data == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    g_rco_data = *rco_data;

    return OK;
}


/*============================================================================*/
/* Brake Light Data Access                                                    */
/*============================================================================*/

void rco_data_set_brake_light(bool brake_light_on)
{
    g_rco_data.brake_light_on = brake_light_on;
}

/*============================================================================*/
/* TSSI Data Access                                                           */
/*============================================================================*/

void rco_data_set_tssi_faulted(bool tssi_faulted)
{
    g_rco_data.tssi_faulted = tssi_faulted; // red light on
}

/*============================================================================*/
/* Reset Button Data Access                                                   */
/*============================================================================*/

void rco_data_set_reset_pressed(bool reset_pressed)
{
    g_rco_data.reset_pressed = reset_pressed;
}

bool rco_data_get_reset_pressed(void)
{
    return g_rco_data.reset_pressed;
}
