/**
 ******************************************************************************
 * @file    ISM303DAC_ACC_MAG_driver_HL.c
 * @author  MEMS Application Team
 * @version V4.2.0
 * @date    01-February-2018
 * @brief   This file provides a set of high-level functions needed to manage
            the ISM303DAC sensor
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "ISM303DAC_ACC_MAG_driver_HL.h"
#include <math.h>



/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup COMPONENTS COMPONENTS
 * @{
 */

/** @addtogroup ISM303DAC ISM303DAC
 * @{
 */

/* Link function for sensor peripheral */
extern uint8_t Sensor_IO_Write( void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite );
extern uint8_t Sensor_IO_Read( void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead );

/** @addtogroup ISM303DAC_Callable_Private_Function_Prototypes Callable private function prototypes
 * @{
 */

static DrvStatusTypeDef ISM303DAC_X_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_X_DeInit( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_X_Sensor_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_X_Sensor_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_X_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i );
static DrvStatusTypeDef ISM303DAC_X_Check_WhoAmI( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_X_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration );
static DrvStatusTypeDef ISM303DAC_X_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value );
static DrvStatusTypeDef ISM303DAC_X_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity );
static DrvStatusTypeDef ISM303DAC_X_Get_ODR( DrvContextTypeDef *handle, float *odr );
static DrvStatusTypeDef ISM303DAC_X_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_Value( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef ISM303DAC_X_Get_FS( DrvContextTypeDef *handle, float *fullScale );
static DrvStatusTypeDef ISM303DAC_X_Set_FS( DrvContextTypeDef *handle, SensorFs_t fs );
static DrvStatusTypeDef ISM303DAC_X_Set_FS_Value( DrvContextTypeDef *handle, float fullScale );
static DrvStatusTypeDef ISM303DAC_X_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data );
static DrvStatusTypeDef ISM303DAC_X_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data );
static DrvStatusTypeDef ISM303DAC_X_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status );

static DrvStatusTypeDef ISM303DAC_M_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_M_DeInit( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_M_Sensor_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_M_Sensor_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_M_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i );
static DrvStatusTypeDef ISM303DAC_M_Check_WhoAmI( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM303DAC_M_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *angular_velocity );
static DrvStatusTypeDef ISM303DAC_M_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value );
static DrvStatusTypeDef ISM303DAC_M_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity );
static DrvStatusTypeDef ISM303DAC_M_Get_ODR( DrvContextTypeDef *handle, float *odr );
static DrvStatusTypeDef ISM303DAC_M_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM303DAC_M_Set_ODR_Value( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef ISM303DAC_M_Get_FS( DrvContextTypeDef *handle, float *fullScale );
static DrvStatusTypeDef ISM303DAC_M_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale );
static DrvStatusTypeDef ISM303DAC_M_Set_FS_Value( DrvContextTypeDef *handle, float fullScale );
static DrvStatusTypeDef ISM303DAC_M_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data );
static DrvStatusTypeDef ISM303DAC_M_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data );
static DrvStatusTypeDef ISM303DAC_M_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status );

/**
 * @}
 */

/** @addtogroup ISM303DAC_Private_Function_Prototypes Private function prototypes
 * @{
 */

static DrvStatusTypeDef ISM303DAC_X_Get_Axes_Raw( DrvContextTypeDef *handle, int16_t *pData );
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr );

static DrvStatusTypeDef ISM303DAC_M_Get_Axes_Raw( DrvContextTypeDef *handle, int16_t *pData );

/**
 * @}
 */

/** @addtogroup ISM303DAC_Public_Variables Public variables
 * @{
 */

/**
 * @brief ISM303DAC accelero driver structure
 */
ACCELERO_Drv_t ISM303DAC_X_Drv =
{
  ISM303DAC_X_Init,
  ISM303DAC_X_DeInit,
  ISM303DAC_X_Sensor_Enable,
  ISM303DAC_X_Sensor_Disable,
  ISM303DAC_X_Get_WhoAmI,
  ISM303DAC_X_Check_WhoAmI,
  ISM303DAC_X_Get_Axes,
  ISM303DAC_X_Get_AxesRaw,
  ISM303DAC_X_Get_Sensitivity,
  ISM303DAC_X_Get_ODR,
  ISM303DAC_X_Set_ODR,
  ISM303DAC_X_Set_ODR_Value,
  ISM303DAC_X_Get_FS,
  ISM303DAC_X_Set_FS,
  ISM303DAC_X_Set_FS_Value,
  0,
  0,
  ISM303DAC_X_Read_Reg,
  ISM303DAC_X_Write_Reg,
  ISM303DAC_X_Get_DRDY_Status
};

/**
 * @brief ISM303DAC megneto driver structure
 */
MAGNETO_Drv_t ISM303DAC_M_Drv =
{
  ISM303DAC_M_Init,
  ISM303DAC_M_DeInit,
  ISM303DAC_M_Sensor_Enable,
  ISM303DAC_M_Sensor_Disable,
  ISM303DAC_M_Get_WhoAmI,
  ISM303DAC_M_Check_WhoAmI,
  ISM303DAC_M_Get_Axes,
  ISM303DAC_M_Get_AxesRaw,
  ISM303DAC_M_Get_Sensitivity,
  ISM303DAC_M_Get_ODR,
  ISM303DAC_M_Set_ODR,
  ISM303DAC_M_Set_ODR_Value,
  ISM303DAC_M_Get_FS,
  ISM303DAC_M_Set_FS,
  ISM303DAC_M_Set_FS_Value,
  ISM303DAC_M_Read_Reg,
  ISM303DAC_M_Write_Reg,
  ISM303DAC_M_Get_DRDY_Status
};

/**
 * @brief ISM303DAC combo data structure definition
 */
ISM303DAC_Combo_Data_t ISM303DAC_Combo_Data[ISM303DAC_SENSORS_MAX_NUM];

/**
 * @}
 */

/** @addtogroup ISM303DAC_Callable_Private_Functions Callable private functions
 * @{
 */

/**
 * @brief Initialize the ISM303DAC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Init( DrvContextTypeDef *handle )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM303DAC_X_Data_t *pComponentData = ( ISM303DAC_X_Data_t * )pData->pComponentData;
  ISM303DAC_Combo_Data_t *comboData = pComponentData->comboData;

  if ( ISM303DAC_X_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* SW reset */
  if ( ism303dac_xl_reset_set( &ctx, PROPERTY_ENABLE) == 1 )
  {
    return COMPONENT_ERROR;
  }
  
  /* Enable register address automatically incremented during a multiple byte
     access with a serial interface. */
  if ( ism303dac_xl_auto_increment_set( &ctx, PROPERTY_ENABLE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Enable BDU */
  if ( ism303dac_xl_block_data_update_set( &ctx, PROPERTY_ENABLE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* FIFO mode selection */
  if ( ism303dac_xl_fifo_mode_set( &ctx, ISM303DAC_XL_BYPASS_MODE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Select default output data rate. */
  pComponentData->Previous_ODR = 100.0f;

  /* Output data rate selection - power down. */
  if ( ism303dac_xl_data_rate_set( &ctx, ISM303DAC_XL_ODR_OFF ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Full scale selection. */
  if ( ISM303DAC_X_Set_FS( handle, FS_LOW ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  comboData->isAccInitialized = 1;

  handle->isInitialized = 1;

  return COMPONENT_OK;
}

/**
 * @brief Deinitialize the ISM303DAC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_DeInit( DrvContextTypeDef *handle )
{

  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM303DAC_X_Data_t *pComponentData = ( ISM303DAC_X_Data_t * )pData->pComponentData;
  ISM303DAC_Combo_Data_t *comboData = pComponentData->comboData;

  if ( ISM303DAC_X_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Disable the component */
  if( ISM303DAC_X_Sensor_Disable( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
 
  /* Reset output data rate. */
  pComponentData->Previous_ODR = 0.0f;

  comboData->isAccInitialized = 0;

  handle->isInitialized = 0;

  return COMPONENT_OK;
}

/**
 * @brief Enable the ISM303DAC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Sensor_Enable( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM303DAC_X_Data_t *pComponentData = ( ISM303DAC_X_Data_t * )pData->pComponentData;

  /* Check if the component is already enabled */
  if ( handle->isEnabled == 1 )
  {
    return COMPONENT_OK;
  }

  /* Output data rate selection. */
  if ( ISM303DAC_X_Set_ODR_Value_When_Enabled( handle, pComponentData->Previous_ODR ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 1;

  return COMPONENT_OK;
}

/**
 * @brief Disable the ISM303DAC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Sensor_Disable( DrvContextTypeDef *handle )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM303DAC_X_Data_t *pComponentData = ( ISM303DAC_X_Data_t * )pData->pComponentData;

  /* Check if the component is already disabled */
  if ( handle->isEnabled == 0 )
  {
    return COMPONENT_OK;
  }

  /* Store actual output data rate. */
  if ( ISM303DAC_X_Get_ODR( handle, &( pComponentData->Previous_ODR ) ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Output data rate selection - power down. */
  if ( ism303dac_xl_data_rate_set( &ctx, ISM303DAC_XL_ODR_OFF ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 0;

  return COMPONENT_OK;
}

/**
 * @brief Get the WHO_AM_I ID of the ISM303DAC accelerometer sensor
 * @param handle the device handle
 * @param who_am_i pointer to the value of WHO_AM_I register
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i )
{
   ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  /* Read WHO AM I register */
  if ( ism303dac_xl_device_id_get( &ctx, ( uint8_t* )who_am_i ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Check the WHO_AM_I ID of the ISM303DAC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Check_WhoAmI( DrvContextTypeDef *handle )
{
  uint8_t who_am_i = 0x00;

  if ( ISM303DAC_X_Get_WhoAmI( handle, &who_am_i ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  if ( who_am_i != handle->who_am_i )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC accelerometer sensor axes
 * @param handle the device handle
 * @param acceleration pointer where the values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration )
{

  int16_t dataRaw[3];
  float sensitivity = 0;

  /* Read raw data from ISM303DAC output register. */
  if ( ISM303DAC_X_Get_Axes_Raw( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Get ISM303DAC actual sensitivity. */
  if ( ISM303DAC_X_Get_Sensitivity( handle, &sensitivity ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Calculate the data. */
  acceleration->AXIS_X = ( int32_t )( dataRaw[0] * sensitivity );
  acceleration->AXIS_Y = ( int32_t )( dataRaw[1] * sensitivity );
  acceleration->AXIS_Z = ( int32_t )( dataRaw[2] * sensitivity );

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC accelerometer sensor raw axes
 * @param handle the device handle
 * @param value pointer where the raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value )
{

  int16_t dataRaw[3];

  /* Read raw data from ISM303DAC output register. */
  if ( ISM303DAC_X_Get_Axes_Raw( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Set the raw data. */
  value->AXIS_X = dataRaw[0];
  value->AXIS_Y = dataRaw[1];
  value->AXIS_Z = dataRaw[2];

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC accelerometer sensor sensitivity
 * @param handle the device handle
 * @param sensitivity pointer where the sensitivity value is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_xl_fs_t fullScale;

  /* Read actual full scale selection from sensor. */
  if ( ism303dac_xl_full_scale_get( &ctx, &fullScale ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Store the sensitivity based on actual full scale. */
  switch( fullScale )
  {
    case ISM303DAC_XL_2g:
      *sensitivity = ( float )ISM303DAC_ACC_SENSITIVITY_FOR_FS_2G;
      break;
    case ISM303DAC_XL_4g:
      *sensitivity = ( float )ISM303DAC_ACC_SENSITIVITY_FOR_FS_4G;
      break;
    case ISM303DAC_XL_8g:
      *sensitivity = ( float )ISM303DAC_ACC_SENSITIVITY_FOR_FS_8G;
      break;
    case ISM303DAC_XL_16g:
      *sensitivity = ( float )ISM303DAC_ACC_SENSITIVITY_FOR_FS_16G;
      break;
    default:
      *sensitivity = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr pointer where the output data rate is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Get_ODR( DrvContextTypeDef *handle, float *odr )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_xl_odr_t odr_low_level;

  if ( ism303dac_xl_data_rate_get( &ctx, &odr_low_level ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  switch( odr_low_level )
  {
    case ISM303DAC_XL_ODR_OFF:
      *odr =     0.0f;
      break;
    case ISM303DAC_XL_ODR_1Hz_LP:
      *odr =     1.0f;
      break;
    case ISM303DAC_XL_ODR_12Hz5_LP:
      *odr =    12.5f;
      break;
    case ISM303DAC_XL_ODR_25Hz_LP:
      *odr =    25.0f;
      break;
    case ISM303DAC_XL_ODR_50Hz_LP:
      *odr =    50.0f;
      break;
    case ISM303DAC_XL_ODR_100Hz_LP:
      *odr =   100.0f;
      break;
    case ISM303DAC_XL_ODR_200Hz_LP:
      *odr =   200.0f;
      break;
    case ISM303DAC_XL_ODR_400Hz_LP:
      *odr =   400.0f;
      break;
    case ISM303DAC_XL_ODR_800Hz_LP:
      *odr =   800.0f;
      break;
    case ISM303DAC_XL_ODR_12Hz5_HR:
      *odr =    12.5f;
      break;
    case ISM303DAC_XL_ODR_25Hz_HR:
      *odr =    25.0f;
      break;
    case ISM303DAC_XL_ODR_50Hz_HR:
      *odr =    50.0f;
      break;
    case ISM303DAC_XL_ODR_100Hz_HR:
      *odr =   100.0f;
      break;
    case ISM303DAC_XL_ODR_200Hz_HR:
      *odr =   200.0f;
      break;
    case ISM303DAC_XL_ODR_400Hz_HR:
      *odr =   400.0f;
      break;
    case ISM303DAC_XL_ODR_800Hz_HR:
      *odr =   800.0f;
      break;
    case ISM303DAC_XL_ODR_1k6Hz_HF:
      *odr =  1600.0f;
      break;
    case ISM303DAC_XL_ODR_3k2Hz_HF:
      *odr =  3200.0f;
      break;
    case ISM303DAC_XL_ODR_6k4Hz_HF:
      *odr =  6400.0f;
      break;
    default:
      *odr =    -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  if(handle->isEnabled == 1)
  {
    if(ISM303DAC_X_Set_ODR_When_Enabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if(ISM303DAC_X_Set_ODR_When_Disabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_Value( DrvContextTypeDef *handle, float odr )
{
  if(handle->isEnabled == 1)
  {
    if(ISM303DAC_X_Set_ODR_Value_When_Enabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if(ISM303DAC_X_Set_ODR_Value_When_Disabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale pointer where the full scale is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Get_FS( DrvContextTypeDef *handle, float *fullScale )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_xl_fs_t fs_low_level;

  if ( ism303dac_xl_full_scale_get( &ctx, &fs_low_level ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  switch( fs_low_level )
  {
    case ISM303DAC_XL_2g:
      *fullScale =  2.0f;
      break;
    case ISM303DAC_XL_4g:
      *fullScale =  4.0f;
      break;
    case ISM303DAC_XL_8g:
      *fullScale =  8.0f;
      break;
    case ISM303DAC_XL_16g:
      *fullScale = 16.0f;
      break;
    default:
      *fullScale = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the functional full scale to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_xl_fs_t new_fs;

  switch( fullScale )
  {
    case FS_LOW:
      new_fs = ISM303DAC_XL_2g;
      break;
    case FS_MID_LOW:  
    case FS_MID:
      new_fs = ISM303DAC_XL_4g;
      break;
    case FS_MID_HIGH:
      new_fs = ISM303DAC_XL_8g;
      break;
    case FS_HIGH:
      new_fs = ISM303DAC_XL_16g;
      break;
    default:
      return COMPONENT_ERROR;
  }

  if ( ism303dac_xl_full_scale_set( &ctx, new_fs ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the full scale value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Set_FS_Value( DrvContextTypeDef *handle, float fullScale )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_xl_fs_t new_fs;

  new_fs = ( fullScale <= 2.0f ) ? ISM303DAC_XL_2g
         : ( fullScale <= 4.0f ) ? ISM303DAC_XL_4g
         : ( fullScale <= 8.0f ) ? ISM303DAC_XL_8g
         :                         ISM303DAC_XL_16g;

  if ( ism303dac_xl_full_scale_set( &ctx, new_fs ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Read the data from register
 * @param handle the device handle
 * @param reg register address
 * @param data register data
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  
  if ( ism303dac_read_reg( &ctx, reg, data, 1 ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Write the data to register
 * @param handle the device handle
 * @param reg register address
 * @param data register data
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  
  if ( ism303dac_write_reg( &ctx, reg, &data, 1 ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get accelerometer data ready status
 * @param handle the device handle
 * @param status the data ready status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  if ( ism303dac_xl_flag_data_ready_get( &ctx, status ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Initialize the ISM303DAC magnetometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Init( DrvContextTypeDef *handle )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  MAGNETO_Data_t *pData = ( MAGNETO_Data_t * )handle->pData;
  ISM303DAC_M_Data_t *pComponentData = ( ISM303DAC_M_Data_t * )pData->pComponentData;
  ISM303DAC_Combo_Data_t *comboData = pComponentData->comboData;

  if ( ISM303DAC_M_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  /* SW reset */
  if ( ism303dac_mg_reset_set( &ctx, PROPERTY_ENABLE) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Enable BDU */
  if ( ism303dac_mg_block_data_update_set( &ctx, PROPERTY_ENABLE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Select default output data rate. */
  pComponentData->Previous_ODR = 100.0f;

  /* Output data rate selection - power down */
  if ( ism303dac_mg_operating_mode_set( &ctx, ISM303DAC_MG_POWER_DOWN ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Mode selection - High resolution*/
  if ( ism303dac_mg_power_mode_set( &ctx, ISM303DAC_MG_HIGH_RESOLUTION ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  comboData->isMagInitialized = 1;

  handle->isInitialized = 1;

  return COMPONENT_OK;
}

/**
 * @brief Deinitialize the ISM303DAC magnetometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_DeInit( DrvContextTypeDef *handle )
{
  MAGNETO_Data_t *pData = ( MAGNETO_Data_t * )handle->pData;
  ISM303DAC_M_Data_t *pComponentData = ( ISM303DAC_M_Data_t * )pData->pComponentData;
  ISM303DAC_Combo_Data_t *comboData = pComponentData->comboData;

  if ( ISM303DAC_M_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Disable the component */
  if ( ISM303DAC_M_Sensor_Disable( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Reset output data rate. */
  pComponentData->Previous_ODR = 0.0f;

  comboData->isMagInitialized = 0;

  handle->isInitialized = 0;

  return COMPONENT_OK;
}

/**
 * @brief Enable the ISM303DAC magnetometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Sensor_Enable( DrvContextTypeDef *handle )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  /* Check if the component is already enabled */
  if ( handle->isEnabled == 1 )
  {
    return COMPONENT_OK;
  }

  /* Operating mode selection - continuous */
  if ( ism303dac_mg_operating_mode_set( &ctx, ISM303DAC_MG_CONTINUOUS_MODE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 1;

  return COMPONENT_OK;
}

/**
 * @brief Disable the ISM303DAC megnetometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Sensor_Disable( DrvContextTypeDef *handle )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  MAGNETO_Data_t *pData = ( MAGNETO_Data_t * )handle->pData;
  ISM303DAC_M_Data_t *pComponentData = ( ISM303DAC_M_Data_t * )pData->pComponentData;

  /* Check if the component is already disabled */
  if ( handle->isEnabled == 0 )
  {
    return COMPONENT_OK;
  }

  /* Store actual output data rate. */
  if ( ISM303DAC_M_Get_ODR( handle, &( pComponentData->Previous_ODR ) ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Operating mode selection - power down */
  if ( ism303dac_mg_operating_mode_set( &ctx, ISM303DAC_MG_POWER_DOWN ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 0;

  return COMPONENT_OK;
}

/**
 * @brief Get the WHO_AM_I ID of the ISM303DAC megnetometer sensor
 * @param handle the device handle
 * @param who_am_i pointer to the value of WHO_AM_I register
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  /* Read WHO AM I register */
  if ( ism303dac_mg_device_id_get( &ctx, ( uint8_t* )who_am_i ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Check the WHO_AM_I ID of the ISM303DAC magnetometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Check_WhoAmI( DrvContextTypeDef *handle )
{
  uint8_t who_am_i = 0x00;

  if ( ISM303DAC_M_Get_WhoAmI( handle, &who_am_i ) == 1 )
  {
    return COMPONENT_ERROR;
  }
  
  if ( who_am_i != handle->who_am_i )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC magnetometer sensor axes
 * @param handle the device handle
 * @param angular_velocity pointer where the values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *angular_velocity )
{
  int16_t dataRaw[3];
  float   sensitivity = 0;

  /* Read raw data from ISM303DAC output register. */
  if ( ISM303DAC_M_Get_Axes_Raw( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Get ISM303DAC actual sensitivity. */
  if ( ISM303DAC_M_Get_Sensitivity( handle, &sensitivity ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Calculate the data. */
  angular_velocity->AXIS_X = ( int32_t )( dataRaw[0] * sensitivity );
  angular_velocity->AXIS_Y = ( int32_t )( dataRaw[1] * sensitivity );
  angular_velocity->AXIS_Z = ( int32_t )( dataRaw[2] * sensitivity );

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC magnetometer sensor raw axes
 * @param handle the device handle
 * @param value pointer where the raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value )
{
  int16_t dataRaw[3];

  /* Read raw data from ISM303DAC output register. */
  if ( ISM303DAC_M_Get_Axes_Raw( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Set the raw data. */
  value->AXIS_X = dataRaw[0];
  value->AXIS_Y = dataRaw[1];
  value->AXIS_Z = dataRaw[2];

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC magnetometer sensor sensitivity
 * @param handle the device handle
 * @param sensitivity pointer where the sensitivity value is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity )
{
  *sensitivity = ( float )ISM303DAC_MAG_SENSITIVITY_FOR_FS_50G;
  
  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC magnetometer sensor output data rate
 * @param handle the device handle
 * @param odr pointer where the output data rate is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Get_ODR( DrvContextTypeDef *handle, float *odr )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_mg_odr_t odr_low_level;

  if ( ism303dac_mg_data_rate_get( &ctx, &odr_low_level ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  switch( odr_low_level )
  {
    case ISM303DAC_MG_ODR_10Hz:
      *odr =   10.0f;
      break;
    case ISM303DAC_MG_ODR_20Hz:
      *odr =   20.0f;
      break;
    case ISM303DAC_MG_ODR_50Hz:
      *odr =   50.0f;
      break;
    case ISM303DAC_MG_ODR_100Hz:
      *odr =  100.0f;
      break;
    default:
      *odr =   -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC magnetomer sensor output data rate
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_mg_odr_t new_odr;

  switch( odr )
  {
    case ODR_LOW:
      new_odr = ISM303DAC_MG_ODR_10Hz;
      break;
    case ODR_MID_LOW:
      new_odr = ISM303DAC_MG_ODR_20Hz;
      break;
    case ODR_MID:
      new_odr = ISM303DAC_MG_ODR_50Hz;
      break;
    case ODR_MID_HIGH:
    case ODR_HIGH:
      new_odr = ISM303DAC_MG_ODR_100Hz;
      break;
    default:
      return COMPONENT_ERROR;
  }

  if ( ism303dac_mg_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC magnetometer sensor output data rate
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Set_ODR_Value( DrvContextTypeDef *handle, float odr )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_mg_odr_t new_odr;
  
  new_odr =   ( ( odr <= 10.000f ) ? ISM303DAC_MG_ODR_10Hz
              : ( odr <= 20.000f ) ? ISM303DAC_MG_ODR_20Hz
              : ( odr <= 50.000f ) ? ISM303DAC_MG_ODR_50Hz
              :                      ISM303DAC_MG_ODR_100Hz );
              
  if ( ism303dac_mg_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC magnetometer sensor full scale
 * @param handle the device handle
 * @param fullScale pointer where the full scale is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Get_FS( DrvContextTypeDef *handle, float *fullScale )
{
  *fullScale = 50.0f;

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC magnetometer sensor full scale
 * @param handle the device handle
 * @param fullScale the functional full scale to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale )
{
  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC magnetometer sensor full scale
 * @param handle the device handle
 * @param fullScale the full scale value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Set_FS_Value( DrvContextTypeDef *handle, float fullScale )
{
  return COMPONENT_OK;
}

/**
 * @brief Read the data from register
 * @param handle the device handle
 * @param reg register address
 * @param data register data
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  
  if ( ism303dac_read_reg( &ctx, reg, data, 1 ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Write the data to register
 * @param handle the device handle
 * @param reg register address
 * @param data register data
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  
  if ( ism303dac_write_reg( &ctx, reg, &data, 1 ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get magnetometer data ready status
 * @param handle the device handle
 * @param status the data ready status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  if ( ism303dac_mg_data_ready_get( &ctx, status ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @}
 */

/** @addtogroup ISM303DAC_Private_Functions Private functions
 * @{
 */

/**
 * @brief Get the ISM303DAC accelerometer sensor raw axes
 * @param handle the device handle
 * @param pData pointer where the raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Get_Axes_Raw(DrvContextTypeDef *handle, int16_t *pData)
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  uint8_t regValue[6] = {0, 0, 0, 0, 0, 0};

  /* Read output registers from ISM303DAC_OUT_X_L_A to ISM303DAC_OUT_Z_H_A. */
  if ( ism303dac_acceleration_raw_get( &ctx, ( uint8_t* )regValue ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Format the data. */
  pData[0] = ( ( ( ( int16_t )regValue[1] ) << 8 ) + ( int16_t )regValue[0] );
  pData[1] = ( ( ( ( int16_t )regValue[3] ) << 8 ) + ( int16_t )regValue[2] );
  pData[2] = ( ( ( ( int16_t )regValue[5] ) << 8 ) + ( int16_t )regValue[4] );

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_xl_odr_t new_odr;

  switch( odr )
  {
    case ODR_LOW:
      new_odr = ISM303DAC_XL_ODR_12Hz5_HR;
      break;
    case ODR_MID_LOW:
      new_odr = ISM303DAC_XL_ODR_25Hz_HR;
      break;
    case ODR_MID:
      new_odr = ISM303DAC_XL_ODR_50Hz_HR;
      break;
    case ODR_MID_HIGH:
      new_odr = ISM303DAC_XL_ODR_100Hz_HR;
      break;
    case ODR_HIGH:
      new_odr = ISM303DAC_XL_ODR_200Hz_HR;
      break;
    default:
      return COMPONENT_ERROR;
  }

  if ( ism303dac_xl_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM303DAC_X_Data_t *pComponentData = ( ISM303DAC_X_Data_t * )pData->pComponentData;

  switch( odr )
  {
    case ODR_LOW:
      pComponentData->Previous_ODR = 12.5f;
      break;
    case ODR_MID_LOW:
      pComponentData->Previous_ODR = 25.0f;
      break;
    case ODR_MID:
      pComponentData->Previous_ODR = 50.0f;
      break;
    case ODR_MID_HIGH:
      pComponentData->Previous_ODR = 100.0f;
      break;
    case ODR_HIGH:
      pComponentData->Previous_ODR = 200.0f;
      break;
    default:
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr )
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism303dac_xl_odr_t new_odr;

  new_odr = ( odr <=   12.5f ) ? ISM303DAC_XL_ODR_12Hz5_HR
          : ( odr <=   25.0f ) ? ISM303DAC_XL_ODR_25Hz_HR
          : ( odr <=   50.0f ) ? ISM303DAC_XL_ODR_50Hz_HR
          : ( odr <=  100.0f ) ? ISM303DAC_XL_ODR_100Hz_HR
          : ( odr <=  200.0f ) ? ISM303DAC_XL_ODR_200Hz_HR
          : ( odr <=  400.0f ) ? ISM303DAC_XL_ODR_400Hz_HR
          : ( odr <=  800.0f ) ? ISM303DAC_XL_ODR_800Hz_HR
          : ( odr <= 1600.0f ) ? ISM303DAC_XL_ODR_1k6Hz_HF
          : ( odr <= 3200.0f ) ? ISM303DAC_XL_ODR_3k2Hz_HF
          :                      ISM303DAC_XL_ODR_6k4Hz_HF;

  if ( ism303dac_xl_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM303DAC accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_X_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM303DAC_X_Data_t *pComponentData = ( ISM303DAC_X_Data_t * )pData->pComponentData;

  pComponentData->Previous_ODR = ( odr <=   12.5f ) ? 12.5f
                               : ( odr <=   25.0f ) ? 25.0f
                               : ( odr <=   50.0f ) ? 50.0f
                               : ( odr <=  100.0f ) ? 100.0f
                               : ( odr <=  200.0f ) ? 200.0f
                               : ( odr <=  400.0f ) ? 400.0f
                               : ( odr <=  800.0f ) ? 800.0f
                               : ( odr <= 1600.0f ) ? 1600.0f
                               : ( odr <= 3200.0f ) ? 3200.0f
                               :                      6400.0f;

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM303DAC magnetometer sensor raw axes
 * @param handle the device handle
 * @param pData pointer where the raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM303DAC_M_Get_Axes_Raw(DrvContextTypeDef *handle, int16_t *pData)
{
  ism303dac_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  uint8_t regValue[6] = {0, 0, 0, 0, 0, 0};

  /* Read output registers from ISM303DAC_OUTX_L_REG_M to ISM303DAC_OUTZ_H_REG_M. */
  if ( ism303dac_magnetic_raw_get( &ctx, ( uint8_t* )regValue ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Format the data. */
  pData[0] = ( ( ( ( int16_t )regValue[1] ) << 8 ) + ( int16_t )regValue[0] );
  pData[1] = ( ( ( ( int16_t )regValue[3] ) << 8 ) + ( int16_t )regValue[2] );
  pData[2] = ( ( ( ( int16_t )regValue[5] ) << 8 ) + ( int16_t )regValue[4] );

  return COMPONENT_OK;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
