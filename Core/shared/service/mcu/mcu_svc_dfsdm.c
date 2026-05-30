#include "mcu_svc_dfsdm.h"
#include "mcu_drv_dfsdm.h"

#include "acuhv_config.h"

/*============================================================================*/
/* Private function Prototypes                                                  */
/*============================================================================*/
static const mcu_dfsdm_config_t * mcu_svc_get_dfsdm_config(mcu_dfsdm_filters_id_t dfsdm_id);
static float mcu_svc_dfsdm_scale(int32_t raw, const mcu_dfsdm_settings_t *dfsdm_settings);
static float mcu_svc_dfsdm_scale_shift(int32_t raw, const mcu_dfsdm_settings_t *dfsdm_settings);

/*============================================================================*/
/* Helper                                                                     */
/*============================================================================*/

static const mcu_dfsdm_config_t * mcu_svc_get_dfsdm_config(mcu_dfsdm_filters_id_t dfsdm_id)
{
    return &mcu_dfsdm_config[dfsdm_id];
}

/*============================================================================*/
/* Filter Start/Stop                                                          */
/*============================================================================*/
// to start just from the name of what ur measuring 

status_t mcu_svc_dfsdm_start(mcu_dfsdm_filters_id_t dfsdm_id)
{
    const mcu_dfsdm_config_t *dfsdm_config = mcu_svc_get_dfsdm_config(dfsdm_id);

    if (dfsdm_config == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    return mcu_drv_start_DFSDM_filter(&dfsdm_config->hw);
}

status_t mcu_svc_dfsdm_stop(mcu_dfsdm_filters_id_t dfsdm_id)
{
    const mcu_dfsdm_config_t *dfsdm_config = mcu_svc_get_dfsdm_config(dfsdm_id);

    if (dfsdm_config == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    return mcu_drv_stop_DFSDM_filter(&dfsdm_config->hw);
}

/*============================================================================*/
/* Data Access                                                                */
/*============================================================================*/

static float mcu_svc_dfsdm_scale(int32_t raw, const mcu_dfsdm_settings_t *dfsdm_settings)
{
    return raw * dfsdm_settings->scaling_factor;
}

static float mcu_svc_dfsdm_scale_shift(int32_t raw, const mcu_dfsdm_settings_t *dfsdm_settings)
{
    return ((raw >> 8) * dfsdm_settings->scaling_factor);
}

status_t mcu_svc_dfsdm_read_raw(mcu_dfsdm_filters_id_t dfsdm_id, int32_t *raw_val)
{
    const mcu_dfsdm_config_t *dfsdm_config = mcu_svc_get_dfsdm_config(dfsdm_id);

    if (dfsdm_config == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    return mcu_drv_DFSDM_read_raw(&dfsdm_config->hw, raw_val);
}

status_t mcu_svc_dfsdm_get_scaled(mcu_dfsdm_filters_id_t dfsdm_id, float *scaled_val)
{
    const mcu_dfsdm_config_t *dfsdm_config = mcu_svc_get_dfsdm_config(dfsdm_id);
    if (dfsdm_config == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    int32_t unscaled_val;

    status_t status = mcu_drv_DFSDM_read_raw(&dfsdm_config->hw, &unscaled_val);
    if (status != OK)
    {
        return ERROR_INVALID_PARAM;
    }

    *scaled_val = mcu_svc_dfsdm_scale(unscaled_val, &dfsdm_config->settings);

    return OK;
}

status_t mcu_svc_dfsdm_get_scaled_shift(mcu_dfsdm_filters_id_t dfsdm_id, float *scaled_val)
{
    const mcu_dfsdm_config_t *dfsdm_config = mcu_svc_get_dfsdm_config(dfsdm_id);
    if (dfsdm_config == NULL)
    {
        return ERROR_INVALID_PARAM;
    }

    int32_t unscaled_val;

    status_t status = mcu_drv_DFSDM_read_raw(&dfsdm_config->hw, &unscaled_val);
    if (status != OK)
    {
        return ERROR_INVALID_PARAM;
    }

    *scaled_val = mcu_svc_dfsdm_scale_shift(unscaled_val, &dfsdm_config->settings);

    return OK;
}