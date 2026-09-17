/*
 * cco_data.c
 *
 *  Created on: Aug 19, 2026
 *      Author: sushi
 */

#include <string.h>
#include "cco_data.h"

/*============================================================================*/
/* Private Data Storage                                                       */
/*============================================================================*/

static cco_data_t g_cco_data;
static bool g_initialized;

/*============================================================================*/
/* Initialization                                                             */
/*============================================================================*/

status_t cco_data_init(void)
{
    memset(&g_cco_data, 0, sizeof(g_cco_data));
    g_cco_data.balance_request = false;
    g_cco_data.balance_duration = 0;

    g_initialized = true;

    return OK;
}


status_t cco_data_get_data(cco_data_t *cco_data)
{
    if (cco_data == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    *cco_data = g_cco_data;

    return OK;
}

status_t cco_data_set_data(cco_data_t *cco_data)
{
    if (cco_data == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    g_cco_data = *cco_data;

    return OK;
}


/*============================================================================*/
/* Balance Init Data Access                                                    */
/*============================================================================*/

void cco_data_set_balance(bool balance)
{
    g_cco_data.balance_request = balance;
}

/*============================================================================*/
/* Balance Duration Data Access                                                           */
/*============================================================================*/

void cco_data_set_balance_duration(uint8_t balance_duration)
{
    g_cco_data.balance_duration = balance_duration; // Balance time in minutes
}

bool cco_data_get_balance(void)
{
    return g_cco_data.balance_request;
}

uint8_t cco_data_get_balance_duration(void)
{
    return g_cco_data.balance_duration;
}
