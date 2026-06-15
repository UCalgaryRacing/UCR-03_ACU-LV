#include "bms_config.h"

const bms_therm_exclusion_t bms_therm_exclusions[] =
{
    /* Slave 2: open/damaged mux1 channels (read ~-65 C). */
    { 1, 0 },
    { 1, 2 },
    { 1, 4 },
    { 1, 6 },
	{ 5, 1 },
	{ 5, 3 },
	{ 5, 5 },
	{ 5, 7 },
	{ 5, 9 },
	{ 5, 11},
	{ 5, 13},
	{ 5, 15},
	{ 5, 17},
	{ 6, 8 },
	{ 7, 0 }
};

const uint8_t bms_therm_exclusion_count =
    (uint8_t)(sizeof(bms_therm_exclusions) / sizeof(bms_therm_exclusions[0]));
