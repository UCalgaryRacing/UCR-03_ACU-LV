/*
 * can_drv.c
 *
 *  Created on: Apr 10, 2026
 *      Author: clayd
 */

#include "can_drv.h"
#include "cmsis_os2.h"

static uint8_t fdcan_dlc_to_bytes(uint32_t dlc);
static uint32_t dlc_to_fdcan_dlc(uint8_t dlc);
static const can_hw_t *can_drv_get_hw_from_handle(FDCAN_HandleTypeDef *hfdcan);
static void can_drv_isr_handler(FDCAN_HandleTypeDef *hfdcan);
static status_t can_drv_receive(const can_hw_t *hw, can_msg_t *message);