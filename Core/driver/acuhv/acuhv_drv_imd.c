#include "acuhv_config.h"

bool acuhv_drv_imd_read_fault_status()
{
    //high = no fault, low = fault
    return !(HAL_GPIO_ReadPin(IMD_OK_PORT, IMD_OK_PIN));
}


