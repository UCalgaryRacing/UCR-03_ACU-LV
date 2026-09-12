#include "mcu_drv_dfsdm.h"
#include "mcu_dfsdm_filters.h"

static int32_t dfsdm_dma_buffers[DFSDM_FILTER_COUNT];

/*============================================================================*/
/*  Initialization                                                             */
/*============================================================================*/


/*============================================================================*/
/* Start/Stop Functions                                                       */
/*============================================================================*/
status_t mcu_drv_start_DFSDM_filter(const mcu_dfsdm_hw_t *hw)
{   
    if(hw == NULL)
    {
        return ERROR_GENERAL;
    }

    if(hw->dfsdm_context->dma_started == false)
    {
        //length of all filter conversions should be one because we only need one reading per filter
        //becuase filter does the oversampling and averaging
        if (HAL_DFSDM_FilterRegularStart_DMA(hw->dfsdm_context->filter_handle, &dfsdm_dma_buffers[hw->dfsdm_buffer_number],1) != HAL_OK)
        {
            return ERROR_GENERAL;
        }

        hw->dfsdm_context->dma_started = true;
    }

    return OK;
}

status_t mcu_drv_stop_DFSDM_filter(const mcu_dfsdm_hw_t *hw)
{
    if (hw == NULL)
    {
        return ERROR_GENERAL;
    }

    if (hw->dfsdm_context->dma_started == true)
    {
        if (HAL_DFSDM_FilterRegularStop_DMA(hw->dfsdm_context->filter_handle) != HAL_OK)
        {
        return ERROR_GENERAL;
        }

        hw->dfsdm_context->dma_started = false;

    }

    return OK;

}

/*============================================================================*/
/* Data Acccess                                                               */
/*============================================================================*/

status_t mcu_drv_DFSDM_read_raw(const mcu_dfsdm_hw_t *hw, int32_t *dfsdm_val)
{
    if (dfsdm_val == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    *dfsdm_val = dfsdm_dma_buffers[hw->dfsdm_buffer_number];

    return OK;
}
