/*
 * adbms6830_types.h
 *
 * ADBMS6830B Internal Types and Shadow Register Structures.
 * These structures mirror the IC's internal registers for efficient
 * read-modify-write operations and state tracking.
 *
 *  Created on: Dec 8, 2025
 *      Author: esall
 */

#ifndef DRIVERS_ADBMS6830_TYPES_H_
#define DRIVERS_ADBMS6830_TYPES_H_

#include <stdint.h>
#include "adbms6830_regs.h"

/**
 * Minimal shadow of configuration register A.
 * Holds the last known/intended payload.
 */
typedef struct
{
    uint8_t cfga[ADBMS_REG_GROUP_SIZE];
} adbms6830_shadow_t;

#endif /* DRIVERS_ADBMS6830_TYPES_H_ */
