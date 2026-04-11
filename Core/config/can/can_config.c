/*
 * can_config.c
 *
 *  Created on: Apr 10, 2026
 *      Author: clayd
 */

#include "can_config.h"
#include "can_config_pinout.h"

static can_context_t can_2_context = {
    .started = false
};

const can_config_t can_config = 
{
    .enabled = true,
    .hw =
    {
        .can_handle = CAN_2_HANDLE,
        .context = &can_2_context,
    }
};


