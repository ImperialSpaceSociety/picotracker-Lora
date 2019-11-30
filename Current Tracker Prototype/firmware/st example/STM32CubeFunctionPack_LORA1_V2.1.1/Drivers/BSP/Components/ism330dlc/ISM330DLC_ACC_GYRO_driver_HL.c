/**
 ******************************************************************************
 * @file    ISM330DLC_ACC_GYRO_driver_HL.c
 * @author  MEMS Application Team
 * @version V4.2.0
 * @date    01-February-2018
 * @brief   This file provides a set of high-level functions needed to manage
            the ISM330DLC sensor
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

#include "ISM330DLC_ACC_GYRO_driver_HL.h"
#include <math.h>



/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup COMPONENTS COMPONENTS
 * @{
 */

/** @addtogroup ISM330DLC ISM330DLC
 * @{
 */

/* Link function for sensor peripheral */
extern uint8_t Sensor_IO_Write( void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite );
extern uint8_t Sensor_IO_Read( void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead );

/** @addtogroup ISM330DLC_Callable_Private_Function_Prototypes Callable private function prototypes
 * @{
 */

static DrvStatusTypeDef ISM330DLC_X_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_X_DeInit( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_X_Sensor_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_X_Sensor_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_X_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i );
static DrvStatusTypeDef ISM330DLC_X_Check_WhoAmI( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_X_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration );
static DrvStatusTypeDef ISM330DLC_X_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value );
static DrvStatusTypeDef ISM330DLC_X_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity );
static DrvStatusTypeDef ISM330DLC_X_Get_ODR( DrvContextTypeDef *handle, float *odr );
static DrvStatusTypeDef ISM330DLC_X_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_Value( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef ISM330DLC_X_Get_FS( DrvContextTypeDef *handle, float *fullScale );
static DrvStatusTypeDef ISM330DLC_X_Set_FS( DrvContextTypeDef *handle, SensorFs_t fs );
static DrvStatusTypeDef ISM330DLC_X_Set_FS_Value( DrvContextTypeDef *handle, float fullScale );
static DrvStatusTypeDef ISM330DLC_X_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data );
static DrvStatusTypeDef ISM330DLC_X_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data );
static DrvStatusTypeDef ISM330DLC_X_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status );

static DrvStatusTypeDef ISM330DLC_G_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_G_DeInit( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_G_Sensor_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_G_Sensor_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_G_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i );
static DrvStatusTypeDef ISM330DLC_G_Check_WhoAmI( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_G_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *angular_velocity );
static DrvStatusTypeDef ISM330DLC_G_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value );
static DrvStatusTypeDef ISM330DLC_G_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity );
static DrvStatusTypeDef ISM330DLC_G_Get_ODR( DrvContextTypeDef *handle, float *odr );
static DrvStatusTypeDef ISM330DLC_G_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_Value( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef ISM330DLC_G_Get_FS( DrvContextTypeDef *handle, float *fullScale );
static DrvStatusTypeDef ISM330DLC_G_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale );
static DrvStatusTypeDef ISM330DLC_G_Set_FS_Value( DrvContextTypeDef *handle, float fullScale );
static DrvStatusTypeDef ISM330DLC_G_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data );
static DrvStatusTypeDef ISM330DLC_G_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data );
static DrvStatusTypeDef ISM330DLC_G_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status );

/**
 * @}
 */

/** @addtogroup ISM330DLC_Private_Function_Prototypes Private function prototypes
 * @{
 */

static DrvStatusTypeDef ISM330DLC_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i );
static DrvStatusTypeDef ISM330DLC_Check_WhoAmI( DrvContextTypeDef *handle );
static DrvStatusTypeDef ISM330DLC_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data );
static DrvStatusTypeDef ISM330DLC_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data );

static DrvStatusTypeDef ISM330DLC_X_Get_Axes_Raw( DrvContextTypeDef *handle, int16_t *pData );
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr );

static DrvStatusTypeDef ISM330DLC_G_Get_Axes_Raw( DrvContextTypeDef *handle, int16_t *pData );
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr );

/**
 * @}
 */

/** @addtogroup ISM330DLC_Public_Variables Public variables
 * @{
 */

/**
 * @brief ISM330DLC accelero driver structure
 */
ACCELERO_Drv_t ISM330DLC_X_Drv =
{
  ISM330DLC_X_Init,
  ISM330DLC_X_DeInit,
  ISM330DLC_X_Sensor_Enable,
  ISM330DLC_X_Sensor_Disable,
  ISM330DLC_X_Get_WhoAmI,
  ISM330DLC_X_Check_WhoAmI,
  ISM330DLC_X_Get_Axes,
  ISM330DLC_X_Get_AxesRaw,
  ISM330DLC_X_Get_Sensitivity,
  ISM330DLC_X_Get_ODR,
  ISM330DLC_X_Set_ODR,
  ISM330DLC_X_Set_ODR_Value,
  ISM330DLC_X_Get_FS,
  ISM330DLC_X_Set_FS,
  ISM330DLC_X_Set_FS_Value,
  0,
  0,
  ISM330DLC_X_Read_Reg,
  ISM330DLC_X_Write_Reg,
  ISM330DLC_X_Get_DRDY_Status
};

/**
 * @brief ISM330DLC gyro driver structure
 */
GYRO_Drv_t ISM330DLC_G_Drv =
{
  ISM330DLC_G_Init,
  ISM330DLC_G_DeInit,
  ISM330DLC_G_Sensor_Enable,
  ISM330DLC_G_Sensor_Disable,
  ISM330DLC_G_Get_WhoAmI,
  ISM330DLC_G_Check_WhoAmI,
  ISM330DLC_G_Get_Axes,
  ISM330DLC_G_Get_AxesRaw,
  ISM330DLC_G_Get_Sensitivity,
  ISM330DLC_G_Get_ODR,
  ISM330DLC_G_Set_ODR,
  ISM330DLC_G_Set_ODR_Value,
  ISM330DLC_G_Get_FS,
  ISM330DLC_G_Set_FS,
  ISM330DLC_G_Set_FS_Value,
  0,
  0,
  ISM330DLC_G_Read_Reg,
  ISM330DLC_G_Write_Reg,
  ISM330DLC_G_Get_DRDY_Status
};

/**
 * @brief ISM330DLC combo data structure definition
 */
ISM330DLC_Combo_Data_t ISM330DLC_Combo_Data[ISM330DLC_SENSORS_MAX_NUM];

/**
 * @}
 */

/** @addtogroup ISM330DLC_Callable_Private_Functions Callable private functions
 * @{
 */

/**
 * @brief Initialize the ISM330DLC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Init( DrvContextTypeDef *handle )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM330DLC_X_Data_t *pComponentData = ( ISM330DLC_X_Data_t * )pData->pComponentData;
  ISM330DLC_Combo_Data_t *comboData = pComponentData->comboData;

  if ( ISM330DLC_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* SW reset */
  if ( ism330dlc_reset_set( &ctx, PROPERTY_ENABLE) == 1 )
  {
    return COMPONENT_ERROR;
  }
  
  /* Enable register address automatically incremented during a multiple byte
     access with a serial interface. */
  if ( ism330dlc_auto_increment_set( &ctx, PROPERTY_ENABLE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Enable BDU */
  if ( ism330dlc_block_data_update_set( &ctx, PROPERTY_ENABLE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* FIFO mode selection */
  if ( ism330dlc_fifo_mode_set( &ctx, ISM330DLC_BYPASS_MODE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Select default output data rate. */
  pComponentData->Previous_ODR = 104.0f;

  /* Output data rate selection - power down. */
  if ( ism330dlc_xl_data_rate_set( &ctx, ISM330DLC_XL_ODR_OFF ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Full scale selection. */
  if ( ISM330DLC_X_Set_FS( handle, FS_LOW ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  comboData->isAccInitialized = 1;

  handle->isInitialized = 1;

  return COMPONENT_OK;
}


/**
 * @brief Deinitialize the ISM330DLC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_DeInit( DrvContextTypeDef *handle )
{

  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM330DLC_X_Data_t *pComponentData = ( ISM330DLC_X_Data_t * )pData->pComponentData;
  ISM330DLC_Combo_Data_t *comboData = pComponentData->comboData;

  if ( ISM330DLC_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Disable the component */
  if( ISM330DLC_X_Sensor_Disable( handle ) == COMPONENT_ERROR )
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
 * @brief Enable the ISM330DLC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Sensor_Enable( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM330DLC_X_Data_t *pComponentData = ( ISM330DLC_X_Data_t * )pData->pComponentData;

  /* Check if the component is already enabled */
  if ( handle->isEnabled == 1 )
  {
    return COMPONENT_OK;
  }

  /* Output data rate selection. */
  if ( ISM330DLC_X_Set_ODR_Value_When_Enabled( handle, pComponentData->Previous_ODR ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 1;

  return COMPONENT_OK;
}



/**
 * @brief Disable the ISM330DLC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Sensor_Disable( DrvContextTypeDef *handle )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM330DLC_X_Data_t *pComponentData = ( ISM330DLC_X_Data_t * )pData->pComponentData;

  /* Check if the component is already disabled */
  if ( handle->isEnabled == 0 )
  {
    return COMPONENT_OK;
  }

  /* Store actual output data rate. */
  if ( ISM330DLC_X_Get_ODR( handle, &( pComponentData->Previous_ODR ) ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Output data rate selection - power down. */
  if ( ism330dlc_xl_data_rate_set( &ctx, ISM330DLC_XL_ODR_OFF ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 0;

  return COMPONENT_OK;
}


/**
 * @brief Get the WHO_AM_I ID of the ISM330DLC accelerometer sensor
 * @param handle the device handle
 * @param who_am_i pointer to the value of WHO_AM_I register
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i )
{

  return ISM330DLC_Get_WhoAmI(handle, who_am_i);
}

/**
 * @brief Check the WHO_AM_I ID of the ISM330DLC accelerometer sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Check_WhoAmI( DrvContextTypeDef *handle )
{

  return ISM330DLC_Check_WhoAmI(handle);
}


/**
 * @brief Get the ISM330DLC accelerometer sensor axes
 * @param handle the device handle
 * @param acceleration pointer where the values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration )
{

  int16_t dataRaw[3];
  float sensitivity = 0;

  /* Read raw data from ISM330DLC output register. */
  if ( ISM330DLC_X_Get_Axes_Raw( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Get ISM330DLC actual sensitivity. */
  if ( ISM330DLC_X_Get_Sensitivity( handle, &sensitivity ) == COMPONENT_ERROR )
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
 * @brief Get the ISM330DLC accelerometer sensor raw axes
 * @param handle the device handle
 * @param value pointer where the raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value )
{

  int16_t dataRaw[3];

  /* Read raw data from ISM330DLC output register. */
  if ( ISM330DLC_X_Get_Axes_Raw( handle, dataRaw ) == COMPONENT_ERROR )
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
 * @brief Get the ISM330DLC accelerometer sensor sensitivity
 * @param handle the device handle
 * @param sensitivity pointer where the sensitivity value is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
	ism330dlc_fs_xl_t fullScale;

  /* Read actual full scale selection from sensor. */
  if ( ism330dlc_xl_full_scale_get( &ctx, &fullScale ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Store the sensitivity based on actual full scale. */
  switch( fullScale )
  {
    case ISM330DLC_2g:
      *sensitivity = ( float )ISM330DLC_ACC_SENSITIVITY_FOR_FS_2G;
      break;
    case ISM330DLC_4g:
      *sensitivity = ( float )ISM330DLC_ACC_SENSITIVITY_FOR_FS_4G;
      break;
    case ISM330DLC_8g:
      *sensitivity = ( float )ISM330DLC_ACC_SENSITIVITY_FOR_FS_8G;
      break;
    case ISM330DLC_16g:
      *sensitivity = ( float )ISM330DLC_ACC_SENSITIVITY_FOR_FS_16G;
      break;
    default:
      *sensitivity = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Get the ISM330DLC accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr pointer where the output data rate is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Get_ODR( DrvContextTypeDef *handle, float *odr )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_odr_xl_t odr_low_level;

  if ( ism330dlc_xl_data_rate_get( &ctx, &odr_low_level ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  switch( odr_low_level )
  {
    case ISM330DLC_XL_ODR_OFF:
      *odr =     0.0f;
      break;
    case ISM330DLC_XL_ODR_1Hz6:
      *odr =     1.6f;
      break;
    case ISM330DLC_XL_ODR_12Hz5:
      *odr =    13.0f;
      break;
    case ISM330DLC_XL_ODR_26Hz:
      *odr =    26.0f;
      break;
    case ISM330DLC_XL_ODR_52Hz:
      *odr =    52.0f;
      break;
    case ISM330DLC_XL_ODR_104Hz:
      *odr =   104.0f;
      break;
    case ISM330DLC_XL_ODR_208Hz:
      *odr =   208.0f;
      break;
    case ISM330DLC_XL_ODR_416Hz:
      *odr =   416.0f;
      break;
    case ISM330DLC_XL_ODR_833Hz:
      *odr =   833.0f;
      break;
    case ISM330DLC_XL_ODR_1k66Hz:
      *odr =  1660.0f;
      break;
    case ISM330DLC_XL_ODR_3k33Hz:
      *odr =  3330.0f;
      break;
    case ISM330DLC_XL_ODR_6k66Hz:
      *odr =  6660.0f;
      break;
    default:
      *odr =    -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Set the ISM330DLC accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr )
{

  if(handle->isEnabled == 1)
  {
    if(ISM330DLC_X_Set_ODR_When_Enabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if(ISM330DLC_X_Set_ODR_When_Disabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}



/**
 * @brief Set the ISM330DLC accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_Value( DrvContextTypeDef *handle, float odr )
{

  if(handle->isEnabled == 1)
  {
    if(ISM330DLC_X_Set_ODR_Value_When_Enabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if(ISM330DLC_X_Set_ODR_Value_When_Disabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}



/**
 * @brief Get the ISM330DLC accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale pointer where the full scale is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Get_FS( DrvContextTypeDef *handle, float *fullScale )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_fs_xl_t fs_low_level;

  if ( ism330dlc_xl_full_scale_get( &ctx, &fs_low_level ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  switch( fs_low_level )
  {
    case ISM330DLC_2g:
      *fullScale =  2.0f;
      break;
    case ISM330DLC_4g:
      *fullScale =  4.0f;
      break;
    case ISM330DLC_8g:
      *fullScale =  8.0f;
      break;
    case ISM330DLC_16g:
      *fullScale = 16.0f;
      break;
    default:
      *fullScale = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Set the ISM330DLC accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the functional full scale to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_fs_xl_t new_fs;

  switch( fullScale )
  {
    case FS_LOW:
      new_fs = ISM330DLC_2g;
      break;
      
    case FS_MID_LOW:
    case FS_MID:
      new_fs = ISM330DLC_4g;
      break;
    
    case FS_MID_HIGH:
    case FS_HIGH:
      new_fs = ISM330DLC_8g;
      break;
    default:
      return COMPONENT_ERROR;
  }

  if ( ism330dlc_xl_full_scale_set( &ctx, new_fs ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Set the ISM330DLC accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the full scale value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Set_FS_Value( DrvContextTypeDef *handle, float fullScale )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_fs_xl_t new_fs;

  new_fs = ( fullScale <= 2.0f ) ? ISM330DLC_2g
         : ( fullScale <= 4.0f ) ? ISM330DLC_4g
         : ( fullScale <= 8.0f ) ? ISM330DLC_8g
         :                         ISM330DLC_16g;

  if ( ism330dlc_xl_full_scale_set( &ctx, new_fs ) == 1 )
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
static DrvStatusTypeDef ISM330DLC_X_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data )
{
  return ISM330DLC_Read_Reg( handle, reg, data );
}



/**
 * @brief Write the data to register
 * @param handle the device handle
 * @param reg register address
 * @param data register data
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data )
{
  return ISM330DLC_Write_Reg( handle, reg, data );
}



/**
 * @brief Get accelerometer data ready status
 * @param handle the device handle
 * @param status the data ready status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  if ( ism330dlc_xl_flag_data_ready_get( &ctx, status ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Initialize the ISM330DLC gyroscope sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Init( DrvContextTypeDef *handle )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  GYRO_Data_t *pData = ( GYRO_Data_t * )handle->pData;
  ISM330DLC_G_Data_t *pComponentData = ( ISM330DLC_G_Data_t * )pData->pComponentData;
  ISM330DLC_Combo_Data_t *comboData = pComponentData->comboData;

  if ( ISM330DLC_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Enable register address automatically incremented during a multiple byte
     access with a serial interface. */
  if ( ism330dlc_auto_increment_set( &ctx, PROPERTY_ENABLE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Enable BDU */
  if ( ism330dlc_block_data_update_set( &ctx, PROPERTY_ENABLE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* FIFO mode selection */
  if ( ism330dlc_fifo_mode_set( &ctx, ISM330DLC_BYPASS_MODE ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Select default output data rate. */
  pComponentData->Previous_ODR = 104.0f;

  /* Output data rate selection - power down */
  if ( ism330dlc_xl_data_rate_set( &ctx, ISM330DLC_XL_ODR_OFF ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Full scale selection. */
  if ( ISM330DLC_G_Set_FS( handle, FS_HIGH ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  comboData->isGyroInitialized = 1;

  handle->isInitialized = 1;

  return COMPONENT_OK;
}


/**
 * @brief Deinitialize the ISM330DLC gyroscope sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_DeInit( DrvContextTypeDef *handle )
{
  GYRO_Data_t *pData = ( GYRO_Data_t * )handle->pData;
  ISM330DLC_G_Data_t *pComponentData = ( ISM330DLC_G_Data_t * )pData->pComponentData;
  ISM330DLC_Combo_Data_t *comboData = pComponentData->comboData;

  if ( ISM330DLC_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Disable the component */
  if ( ISM330DLC_G_Sensor_Disable( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Reset output data rate. */
  pComponentData->Previous_ODR = 0.0f;

  comboData->isGyroInitialized = 0;

  handle->isInitialized = 0;

  return COMPONENT_OK;
}



/**
 * @brief Enable the ISM330DLC gyroscope sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Sensor_Enable( DrvContextTypeDef *handle )
{
  GYRO_Data_t *pData = ( GYRO_Data_t * )handle->pData;
  ISM330DLC_G_Data_t *pComponentData = ( ISM330DLC_G_Data_t * )pData->pComponentData;

  /* Check if the component is already enabled */
  if ( handle->isEnabled == 1 )
  {
    return COMPONENT_OK;
  }

  /* Output data rate selection. */
  if ( ISM330DLC_G_Set_ODR_Value_When_Enabled( handle, pComponentData->Previous_ODR ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 1;

  return COMPONENT_OK;
}



/**
 * @brief Disable the ISM330DLC gyroscope sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Sensor_Disable( DrvContextTypeDef *handle )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  GYRO_Data_t *pData = ( GYRO_Data_t * )handle->pData;
  ISM330DLC_G_Data_t *pComponentData = ( ISM330DLC_G_Data_t * )pData->pComponentData;

  /* Check if the component is already disabled */
  if ( handle->isEnabled == 0 )
  {
    return COMPONENT_OK;
  }

  /* Store actual output data rate. */
  if ( ISM330DLC_G_Get_ODR( handle, &( pComponentData->Previous_ODR ) ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Output data rate selection - power down */
  if ( ism330dlc_xl_data_rate_set( &ctx, ISM330DLC_XL_ODR_OFF ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 0;

  return COMPONENT_OK;
}


/**
 * @brief Get the WHO_AM_I ID of the ISM330DLC gyroscope sensor
 * @param handle the device handle
 * @param who_am_i pointer to the value of WHO_AM_I register
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i )
{

  return ISM330DLC_Get_WhoAmI(handle, who_am_i);
}


/**
 * @brief Check the WHO_AM_I ID of the ISM330DLC gyroscope sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Check_WhoAmI( DrvContextTypeDef *handle )
{

  return ISM330DLC_Check_WhoAmI(handle);
}


/**
 * @brief Get the ISM330DLC gyroscope sensor axes
 * @param handle the device handle
 * @param angular_velocity pointer where the values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *angular_velocity )
{

  int16_t dataRaw[3];
  float   sensitivity = 0;

  /* Read raw data from ISM330DLC output register. */
  if ( ISM330DLC_G_Get_Axes_Raw( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Get ISM330DLC actual sensitivity. */
  if ( ISM330DLC_G_Get_Sensitivity( handle, &sensitivity ) == COMPONENT_ERROR )
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
 * @brief Get the ISM330DLC gyroscope sensor raw axes
 * @param handle the device handle
 * @param value pointer where the raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value )
{

  int16_t dataRaw[3];

  /* Read raw data from ISM330DLC output register. */
  if ( ISM330DLC_G_Get_Axes_Raw( handle, dataRaw ) == COMPONENT_ERROR )
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
 * @brief Get the ISM330DLC gyroscope sensor sensitivity
 * @param handle the device handle
 * @param sensitivity pointer where the sensitivity value is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_fs_g_t fullScale;

  /* Read actual full scale selection from sensor. */
  if ( ism330dlc_gy_full_scale_get( &ctx, &fullScale ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Store the sensitivity based on actual full scale. */
  switch( fullScale )
  {
  case ISM330DLC_125dps:
    *sensitivity = ( float )ISM330DLC_GYRO_SENSITIVITY_FOR_FS_125DPS;
    break;
  case ISM330DLC_250dps:
    *sensitivity = ( float )ISM330DLC_GYRO_SENSITIVITY_FOR_FS_250DPS;
    break;
  case ISM330DLC_500dps:
    *sensitivity = ( float )ISM330DLC_GYRO_SENSITIVITY_FOR_FS_500DPS;
    break;
  case ISM330DLC_1000dps:
    *sensitivity = ( float )ISM330DLC_GYRO_SENSITIVITY_FOR_FS_1000DPS;
    break;
  case ISM330DLC_2000dps:
    *sensitivity = ( float )ISM330DLC_GYRO_SENSITIVITY_FOR_FS_2000DPS;
    break;
  default:
    *sensitivity = -1.0f;
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Get the ISM330DLC gyroscope sensor output data rate
 * @param handle the device handle
 * @param odr pointer where the output data rate is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Get_ODR( DrvContextTypeDef *handle, float *odr )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_odr_g_t odr_low_level;

  if ( ism330dlc_gy_data_rate_get( &ctx, &odr_low_level ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  switch( odr_low_level )
  {
    case ISM330DLC_GY_ODR_OFF:
      *odr =    0.0f;
      break;
    case ISM330DLC_GY_ODR_12Hz5:
      *odr =   13.0f;
      break;
    case ISM330DLC_GY_ODR_26Hz:
      *odr =   26.0f;
      break;
    case ISM330DLC_GY_ODR_52Hz:
      *odr =   52.0f;
      break;
    case ISM330DLC_GY_ODR_104Hz:
      *odr =  104.0f;
      break;
    case ISM330DLC_GY_ODR_208Hz:
      *odr =  208.0f;
      break;
    case ISM330DLC_GY_ODR_416Hz:
      *odr =  416.0f;
      break;
    case ISM330DLC_GY_ODR_833Hz:
      *odr =  833.0f;
      break;
    case ISM330DLC_GY_ODR_1k66Hz:
      *odr = 1660.0f;
      break;
    case ISM330DLC_GY_ODR_3k33Hz:
      *odr = 3330.0f;
      break;
    case ISM330DLC_GY_ODR_6k66Hz:
      *odr = 6660.0f;
      break;
    default:
      *odr =   -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Set the ISM330DLC gyroscope sensor output data rate
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr )
{

  if(handle->isEnabled == 1)
  {
    if(ISM330DLC_G_Set_ODR_When_Enabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if(ISM330DLC_G_Set_ODR_When_Disabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}



/**
 * @brief Set the ISM330DLC gyroscope sensor output data rate
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_Value( DrvContextTypeDef *handle, float odr )
{

  if(handle->isEnabled == 1)
  {
    if(ISM330DLC_G_Set_ODR_Value_When_Enabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if(ISM330DLC_G_Set_ODR_Value_When_Disabled(handle, odr) == COMPONENT_ERROR)
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}



/**
 * @brief Get the ISM330DLC gyroscope sensor full scale
 * @param handle the device handle
 * @param fullScale pointer where the full scale is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Get_FS( DrvContextTypeDef *handle, float *fullScale )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_fs_g_t fs_low_level;

  if ( ism330dlc_gy_full_scale_get( &ctx, &fs_low_level ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  switch( fs_low_level )
  {
  case ISM330DLC_125dps:
    *fullScale =  125.0f;
    break;
  case ISM330DLC_250dps:
    *fullScale =  250.0f;
    break;
  case ISM330DLC_500dps:
    *fullScale =  500.0f;
    break;
  case ISM330DLC_1000dps:
    *fullScale = 1000.0f;
    break;
  case ISM330DLC_2000dps:
    *fullScale = 2000.0f;
    break;
  default:
    *fullScale =   -1.0f;
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Set the ISM330DLC gyroscope sensor full scale
 * @param handle the device handle
 * @param fullScale the functional full scale to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_fs_g_t new_fs;

  switch( fullScale )
  {
    case FS_LOW:
      new_fs = ISM330DLC_250dps;
      break;
    
    case FS_MID_LOW:
    case FS_MID:
      new_fs = ISM330DLC_500dps;
      break;
      
    case FS_MID_HIGH:
    case FS_HIGH:
      new_fs = ISM330DLC_2000dps;
      break;
    default:
      return COMPONENT_ERROR;
  }

  if ( ism330dlc_gy_full_scale_set( &ctx, new_fs ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Set the ISM330DLC gyroscope sensor full scale
 * @param handle the device handle
 * @param fullScale the full scale value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Set_FS_Value( DrvContextTypeDef *handle, float fullScale )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_fs_g_t new_fs;

  new_fs = ( fullScale <=  125.0f ) ? ISM330DLC_125dps
         : ( fullScale <=  250.0f ) ? ISM330DLC_250dps
         : ( fullScale <=  500.0f ) ? ISM330DLC_500dps
         : ( fullScale <= 1000.0f ) ? ISM330DLC_1000dps
         :                            ISM330DLC_2000dps;

  if ( ism330dlc_gy_full_scale_set( &ctx, new_fs ) == 1 )
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
static DrvStatusTypeDef ISM330DLC_G_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data )
{

  if ( ISM330DLC_Read_Reg( handle, reg, data ) == COMPONENT_ERROR )
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
static DrvStatusTypeDef ISM330DLC_G_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data )
{

  if ( ISM330DLC_Write_Reg( handle, reg, data ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Get gyroscope data ready status
 * @param handle the device handle
 * @param status the data ready status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  if ( ism330dlc_gy_flag_data_ready_get( &ctx, status ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @}
 */

/** @addtogroup ISM330DLC_Private_Functions Private functions
 * @{
 */

/**
 * @brief Get the WHO_AM_I ID of the ISM330DLC sensor
 * @param handle the device handle
 * @param who_am_i pointer to the value of WHO_AM_I register
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i )
{
  /* Read WHO AM I register */
  return ISM330DLC_Read_Reg( handle, ISM330DLC_WHO_AM_I, who_am_i );
}


/**
 * @brief Check the WHO_AM_I ID of the ISM330DLC sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_Check_WhoAmI( DrvContextTypeDef *handle )
{

  uint8_t who_am_i = 0x00;

  if ( ISM330DLC_Get_WhoAmI( handle, &who_am_i ) == COMPONENT_ERROR )
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
 * @brief Read the data from register
 * @param handle the device handle
 * @param reg register address
 * @param data register data
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  return (DrvStatusTypeDef)ism330dlc_read_reg( &ctx, reg, data, 1 );
}

/**
 * @brief Write the data to register
 * @param handle the device handle
 * @param reg register address
 * @param data register data
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  return (DrvStatusTypeDef)ism330dlc_write_reg( &ctx, reg, &data, 1 );
}

/**
 * @brief Get the ISM330DLC accelerometer sensor raw axes
 * @param handle the device handle
 * @param pData pointer where the raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Get_Axes_Raw(DrvContextTypeDef *handle, int16_t *pData)
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  uint8_t regValue[6] = {0, 0, 0, 0, 0, 0};

  /* Read output registers from ISM330DLC_ACC_GYRO_OUTX_L_XL to ISM330DLC_ACC_GYRO_OUTZ_H_XL. */
  if ( ism330dlc_acceleration_raw_get( &ctx, ( uint8_t* )regValue ) == 1 )
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
 * @brief Set the ISM330DLC accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_odr_xl_t new_odr;

  switch( odr )
  {
    case ODR_LOW:
      new_odr = ISM330DLC_XL_ODR_12Hz5;
      break;
    case ODR_MID_LOW:
      new_odr = ISM330DLC_XL_ODR_12Hz5;
      break;
    case ODR_MID:
      new_odr = ISM330DLC_XL_ODR_26Hz;
      break;
    case ODR_MID_HIGH:
      new_odr = ISM330DLC_XL_ODR_52Hz;
      break;
    case ODR_HIGH:
      new_odr = ISM330DLC_XL_ODR_104Hz;
      break;
    default:
      return COMPONENT_ERROR;
  }

  if ( ism330dlc_xl_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM330DLC accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM330DLC_X_Data_t *pComponentData = ( ISM330DLC_X_Data_t * )pData->pComponentData;

  switch( odr )
  {
    case ODR_LOW:
      pComponentData->Previous_ODR = 12.5f;
      break;
    case ODR_MID_LOW:
      pComponentData->Previous_ODR = 12.5f;
      break;
    case ODR_MID:
      pComponentData->Previous_ODR = 26.0f;
      break;
    case ODR_MID_HIGH:
      pComponentData->Previous_ODR = 52.0f;
      break;
    case ODR_HIGH:
      pComponentData->Previous_ODR = 104.0f;
      break;
    default:
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM330DLC accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_odr_xl_t new_odr;

  new_odr = ( odr <=    1.6f ) ? ISM330DLC_XL_ODR_1Hz6
          : ( odr <=   13.0f ) ? ISM330DLC_XL_ODR_12Hz5
          : ( odr <=   26.0f ) ? ISM330DLC_XL_ODR_26Hz
          : ( odr <=   52.0f ) ? ISM330DLC_XL_ODR_52Hz
          : ( odr <=  104.0f ) ? ISM330DLC_XL_ODR_104Hz
          : ( odr <=  208.0f ) ? ISM330DLC_XL_ODR_208Hz
          : ( odr <=  416.0f ) ? ISM330DLC_XL_ODR_416Hz
          : ( odr <=  833.0f ) ? ISM330DLC_XL_ODR_833Hz
          : ( odr <= 1660.0f ) ? ISM330DLC_XL_ODR_1k66Hz
          : ( odr <= 3330.0f ) ? ISM330DLC_XL_ODR_3k33Hz
          :                      ISM330DLC_XL_ODR_6k66Hz;

  if ( ism330dlc_xl_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM330DLC accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_X_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr )
{

  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  ISM330DLC_X_Data_t *pComponentData = ( ISM330DLC_X_Data_t * )pData->pComponentData;

  pComponentData->Previous_ODR = ( odr <=    1.6f ) ? 1.6f
                               : ( odr <=   13.0f ) ? 13.0f
                               : ( odr <=   26.0f ) ? 26.0f
                               : ( odr <=   52.0f ) ? 52.0f
                               : ( odr <=  104.0f ) ? 104.0f
                               : ( odr <=  208.0f ) ? 208.0f
                               : ( odr <=  416.0f ) ? 416.0f
                               : ( odr <=  833.0f ) ? 833.0f
                               : ( odr <= 1660.0f ) ? 1660.0f
                               : ( odr <= 3330.0f ) ? 3330.0f
                               :                      6660.0f;

  return COMPONENT_OK;
}

/**
 * @brief Get the ISM330DLC gyroscope sensor raw axes
 * @param handle the device handle
 * @param pData pointer where the raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Get_Axes_Raw(DrvContextTypeDef *handle, int16_t *pData)
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  uint8_t regValue[6] = {0, 0, 0, 0, 0, 0};

  /* Read output registers from ISM330DLC_ACC_GYRO_OUTX_L_G to ISM330DLC_ACC_GYRO_OUTZ_H_G. */
  if ( ism330dlc_angular_rate_raw_get( &ctx, ( uint8_t* )regValue ) == 1 )
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
 * @brief Set the ISM330DLC gyroscope sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_odr_g_t new_odr;

  switch( odr )
  {
    case ODR_LOW:
      new_odr = ISM330DLC_GY_ODR_12Hz5;
      break;
    case ODR_MID_LOW:
      new_odr = ISM330DLC_GY_ODR_12Hz5;
      break;
    case ODR_MID:
      new_odr = ISM330DLC_GY_ODR_26Hz;
      break;
    case ODR_MID_HIGH:
      new_odr = ISM330DLC_GY_ODR_52Hz;
      break;
    case ODR_HIGH:
      new_odr = ISM330DLC_GY_ODR_104Hz;
      break;
    default:
      return COMPONENT_ERROR;
  }

  if ( ism330dlc_gy_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM330DLC gyroscope sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  GYRO_Data_t *pData = ( GYRO_Data_t * )handle->pData;
  ISM330DLC_G_Data_t *pComponentData = ( ISM330DLC_G_Data_t * )pData->pComponentData;

  switch( odr )
  {
    case ODR_LOW:
      pComponentData->Previous_ODR = 12.5f;
      break;
    case ODR_MID_LOW:
      pComponentData->Previous_ODR = 12.5f;
      break;
    case ODR_MID:
      pComponentData->Previous_ODR = 26.0f;
      break;
    case ODR_MID_HIGH:
      pComponentData->Previous_ODR = 52.0f;
      break;
    case ODR_HIGH:
      pComponentData->Previous_ODR = 104.0f;
      break;
    default:
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM330DLC gyroscope sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr )
{
  ism330dlc_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ism330dlc_odr_g_t new_odr;

  new_odr = ( odr <=  13.0f )  ? ISM330DLC_GY_ODR_12Hz5
          : ( odr <=  26.0f )  ? ISM330DLC_GY_ODR_26Hz
          : ( odr <=  52.0f )  ? ISM330DLC_GY_ODR_52Hz
          : ( odr <= 104.0f )  ? ISM330DLC_GY_ODR_104Hz
          : ( odr <= 208.0f )  ? ISM330DLC_GY_ODR_208Hz
          : ( odr <= 416.0f )  ? ISM330DLC_GY_ODR_416Hz
          : ( odr <= 833.0f )  ? ISM330DLC_GY_ODR_833Hz
          : ( odr <= 1660.0f ) ? ISM330DLC_GY_ODR_1k66Hz
          : ( odr <= 3330.0f ) ? ISM330DLC_GY_ODR_3k33Hz
          :                      ISM330DLC_GY_ODR_6k66Hz;

  if ( ism330dlc_gy_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the ISM330DLC gyroscope sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef ISM330DLC_G_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr )
{

  GYRO_Data_t *pData = ( GYRO_Data_t * )handle->pData;
  ISM330DLC_G_Data_t *pComponentData = ( ISM330DLC_G_Data_t * )pData->pComponentData;

  pComponentData->Previous_ODR = ( odr <=  13.0f )  ? 13.0f
                               : ( odr <=  26.0f )  ? 26.0f
                               : ( odr <=  52.0f )  ? 52.0f
                               : ( odr <= 104.0f )  ? 104.0f
                               : ( odr <= 208.0f )  ? 208.0f
                               : ( odr <= 416.0f )  ? 416.0f
                               : ( odr <= 833.0f )  ? 833.0f
                               : ( odr <= 1660.0f ) ? 1660.0f
                               : ( odr <= 3330.0f ) ? 3330.0f
                               :                      6660.0f;

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
