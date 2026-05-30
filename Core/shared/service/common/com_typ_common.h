#ifndef TYPES_COM_TYP_COMMON_H_
#define TYPES_COM_TYP_COMMON_H_


#include <stdint.h>
#include <stdbool.h>

/*============================================================================*/
/* Return Codes and Error Types                                               */
/*============================================================================*/

typedef enum
{
    OK = 0,
    ERROR_GENERAL,
    ERROR_NOT_INITIALIZED,
    ERROR_INVALID_PARAM,
    ERROR_BUSY
} status_t;

typedef enum
{
    ACU_LV_OK = 0U,
    ACU_LV_ERROR
} acu_lv_status_t;

#endif /* TYPES_COM_TYP_COMMON_H_ */
