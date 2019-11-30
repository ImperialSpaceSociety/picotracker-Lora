/**
 ******************************************************************************
 * @file    H3LIS331DL_ACC_driver_HL.c
 * @author  MEMS Application Team
 * @version V4.2.0
 * @date    01-February-2018
 * @brief   This file provides a set of high-level functions needed to manage
            the H3LIS331DL sensor
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

#include "H3LIS331DL_ACC_driver_HL.h"



/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup COMPONENTS COMPONENTS
 * @{
 */

/** @addtogroup H3LIS331DL H3LIS331DL
 * @{
 */

/** @addtogroup H3LIS331DL_Private_Function_Prototypes Private function prototypes
 * @{
 */

static DrvStatusTypeDef H3LIS331DL_Get_Axes_Raw_Data(DrvContextTypeDef *handle, int16_t *pData);
static DrvStatusTypeDef H3LIS331DL_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef H3LIS331DL_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef H3LIS331DL_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef H3LIS331DL_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr );

/**
 * @}
 */

/** @addtogroup H3LIS331DL_Callable_Private_Function_Prototypes Callable private function prototypes
 * @{
 */

static DrvStatusTypeDef H3LIS331DL_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef H3LIS331DL_DeInit( DrvContextTypeDef *handle );
static DrvStatusTypeDef H3LIS331DL_Sensor_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef H3LIS331DL_Sensor_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef H3LIS331DL_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i );
static DrvStatusTypeDef H3LIS331DL_Check_WhoAmI( DrvContextTypeDef *handle );
static DrvStatusTypeDef H3LIS331DL_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration );
static DrvStatusTypeDef H3LIS331DL_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value );
static DrvStatusTypeDef H3LIS331DL_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity );
static DrvStatusTypeDef H3LIS331DL_Get_ODR( DrvContextTypeDef *handle, float *odr );
static DrvStatusTypeDef H3LIS331DL_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef H3LIS331DL_Set_ODR_Value( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef H3LIS331DL_Get_FS( DrvContextTypeDef *handle, float *fullScale );
static DrvStatusTypeDef H3LIS331DL_Set_FS( DrvContextTypeDef *handle, SensorFs_t fs );
static DrvStatusTypeDef H3LIS331DL_Set_FS_Value( DrvContextTypeDef *handle, float fullScale );
static DrvStatusTypeDef H3LIS331DL_Get_Axes_Status( DrvContextTypeDef *handle, uint8_t *xyz_enabled );
static DrvStatusTypeDef H3LIS331DL_Set_Axes_Status( DrvContextTypeDef *handle, uint8_t *enable_xyz );
static DrvStatusTypeDef H3LIS331DL_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data );
static DrvStatusTypeDef H3LIS331DL_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data );
static DrvStatusTypeDef H3LIS331DL_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status );

/**
 * @}
 */

/** @addtogroup H3LIS331DL_Callable_Private_Function_Ext_Prototypes Callable private function for extended features prototypes
 * @{
 */

  /* _NOTE_: Possible to add the functions for extended features of the sensor here */

/**
 * @}
 */

/** @addtogroup H3LIS331DL_Public_Variables Public variables
 * @{
 */

#if 0 /* _NOTE_: Remove this line if you plan to use this structure below */
/**
 * @brief H3LIS331DL accelero extended features driver internal structure
 */
H3LIS331DL_ExtDrv_t H3LIS331DL_ExtDrv =
{
  /* _NOTE_: Possible to add the functions for extended features of the sensor here */
};
#endif /* _NOTE_: Remove this line if you plan to use this structure above */

/**
 * @brief H3LIS331DL accelero driver structure
 */
ACCELERO_Drv_t H3LIS331DL_Drv =
{
  H3LIS331DL_Init,
  H3LIS331DL_DeInit,
  H3LIS331DL_Sensor_Enable,
  H3LIS331DL_Sensor_Disable,
  H3LIS331DL_Get_WhoAmI,
  H3LIS331DL_Check_WhoAmI,
  H3LIS331DL_Get_Axes,
  H3LIS331DL_Get_AxesRaw,
  H3LIS331DL_Get_Sensitivity,
  H3LIS331DL_Get_ODR,
  H3LIS331DL_Set_ODR,
  H3LIS331DL_Set_ODR_Value,
  H3LIS331DL_Get_FS,
  H3LIS331DL_Set_FS,
  H3LIS331DL_Set_FS_Value,
  H3LIS331DL_Get_Axes_Status,
  H3LIS331DL_Set_Axes_Status,
  H3LIS331DL_Read_Reg,
  H3LIS331DL_Write_Reg,
  H3LIS331DL_Get_DRDY_Status
};

/**
 * @}
 */

/** @addtogroup H3LIS331DL_Callable_Private_Functions Callable private functions
 * @{
 */

/**
 * @brief Initialize the H3LIS331DL sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Init( DrvContextTypeDef *handle )
{
  uint8_t axes_status[] = { 1, 1, 1 };

  if ( H3LIS331DL_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Enable BDU. */
  if ( H3LIS331DL_SetBDU( ( void * )handle, H3LIS331DL_ENABLE ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Set power mode - power down. */
  if ( H3LIS331DL_SetMode( ( void * )handle, H3LIS331DL_POWER_DOWN ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Select default output data rate in normal mode. */
  if ( H3LIS331DL_Set_ODR_Value_When_Disabled( handle, 100.0f ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Full scale selection. */
  if ( H3LIS331DL_Set_FS( handle, FS_LOW ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Enable axes. */
  if ( H3LIS331DL_Set_Axes_Status( handle, axes_status ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isInitialized = 1;

  return COMPONENT_OK;
}

/**
 * @brief Deinitialize the H3LIS331DL sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_DeInit( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  H3LIS331DL_Data_t *pComponentData = ( H3LIS331DL_Data_t * )pData->pComponentData;

  if ( H3LIS331DL_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Disable the component */
  if( H3LIS331DL_Sensor_Disable( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Reset previous output data rate. */
  pComponentData->Previous_ODR = 0.0f;

  handle->isInitialized = 0;

  return COMPONENT_OK;
}

/**
 * @brief Enable the H3LIS331DL sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Sensor_Enable( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  H3LIS331DL_Data_t *pComponentData = ( H3LIS331DL_Data_t * )pData->pComponentData;

  /* Check if the component is already enabled */
  if ( handle->isEnabled == 1 )
  {
    return COMPONENT_OK;
  }

  /* Output data rate selection. */
  if ( H3LIS331DL_Set_ODR_Value_When_Enabled( handle, pComponentData->Previous_ODR ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 1;

  return COMPONENT_OK;
}

/**
 * @brief Disable the H3LIS331DL sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Sensor_Disable( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  H3LIS331DL_Data_t *pComponentData = ( H3LIS331DL_Data_t * )pData->pComponentData;

  /* Check if the component is already disabled */
  if ( handle->isEnabled == 0 )
  {
    return COMPONENT_OK;
  }

  /* Store actual output data rate. */
  if ( H3LIS331DL_Get_ODR( handle, &( pComponentData->Previous_ODR ) ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Set power down mode. */
  if ( H3LIS331DL_SetMode( ( void * )handle, H3LIS331DL_POWER_DOWN ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 0;

  return COMPONENT_OK;
}

/**
 * @brief Get the WHO_AM_I ID of the H3LIS331DL sensor
 * @param handle the device handle
 * @param who_am_i pointer to the value of WHO_AM_I register
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i )
{
  /* Read WHO AM I register */
  if ( H3LIS331DL_GetWHO_AM_I( ( void * )handle, ( uint8_t* )who_am_i ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Check the WHO_AM_I ID of the H3LIS331DL sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Check_WhoAmI( DrvContextTypeDef *handle )
{
  uint8_t who_am_i = 0x00;

  if ( H3LIS331DL_Get_WhoAmI( handle, &who_am_i ) == COMPONENT_ERROR )
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
 * @brief Get the H3LIS331DL accelerometer sensor axes
 * @param handle the device handle
 * @param acceleration pointer to where acceleration data write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration )
{
  int16_t dataRaw[3];
  float sensitivity = 0;

  /* Read raw data from H3LIS331DL output register. */
  if ( H3LIS331DL_Get_Axes_Raw_Data( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Get H3LIS331DL actual sensitivity. */
  if ( H3LIS331DL_Get_Sensitivity( handle, &sensitivity ) == COMPONENT_ERROR )
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
 * @brief Get the H3LIS331DL accelerometer sensor raw axes
 * @param handle the device handle
 * @param acceleration_raw pointer to where acceleration raw data write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value )
{
  int16_t dataRaw[3];

  /* Read raw data from H3LIS331DL output register. */
  if ( H3LIS331DL_Get_Axes_Raw_Data( handle, dataRaw ) == COMPONENT_ERROR )
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
 * @brief Get the H3LIS331DL accelerometer sensor sensitivity
 * @param handle the device handle
 * @param sensitivity pointer to where sensitivity write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity )
{
  H3LIS331DL_Fullscale_t fullScale;

  /* Read actual full scale selection from sensor. */
  if ( H3LIS331DL_GetFullScale( ( void * )handle, &fullScale ) == MEMS_ERROR )
  {
    *sensitivity = -1.0f;
    return COMPONENT_ERROR;
  }

  /* Store the sensitivity based on actual full scale. */
  switch ( fullScale )
  {

  case H3LIS331DL_FULLSCALE_2:
    *sensitivity = ( float )H3LIS331DL_ACC_SENSITIVITY_FOR_FS_100G;
    break;

  case H3LIS331DL_FULLSCALE_4:
    *sensitivity = ( float )H3LIS331DL_ACC_SENSITIVITY_FOR_FS_200G;
    break;

  case H3LIS331DL_FULLSCALE_8:
    *sensitivity = ( float )H3LIS331DL_ACC_SENSITIVITY_FOR_FS_400G;
    break;

  default:
    *sensitivity = -1.0f;
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the H3LIS331DL accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr pointer to where output data rate write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_ODR( DrvContextTypeDef *handle, float *odr )
{
  H3LIS331DL_Mode_t mode;
  H3LIS331DL_ODR_t odr_low_level;

  /* Read actual power mode selection from sensor. */
  if ( H3LIS331DL_GetMode( ( void * )handle, &mode ) == MEMS_ERROR )
  {
    *odr = -1.0f;
    return COMPONENT_ERROR;
  }

  switch ( mode )
  {

    case H3LIS331DL_POWER_DOWN:
      *odr = 0.0f;
      break;

    case H3LIS331DL_LOW_POWER_05:
      *odr = 0.5f;
      break;

    case H3LIS331DL_LOW_POWER_1:
      *odr = 1.0f;
      break;

    case H3LIS331DL_LOW_POWER_2:
      *odr = 2.0f;
      break;

    case H3LIS331DL_LOW_POWER_5:
      *odr = 5.0f;
      break;

    case H3LIS331DL_LOW_POWER_10:
      *odr = 10.0f;
      break;

    case H3LIS331DL_NORMAL:

      /* Read actual output data rate selection from sensor. */
      if ( H3LIS331DL_GetODR( ( void * )handle, &odr_low_level ) == MEMS_ERROR )
      {
        *odr = -1.0f;
        return COMPONENT_ERROR;
      }

      switch ( odr_low_level )
      {

        case H3LIS331DL_ODR_50Hz:
          *odr = 50.0f;
          break;

        case H3LIS331DL_ODR_100Hz:
          *odr = 100.0f;
          break;

        case H3LIS331DL_ODR_400Hz:
          *odr = 400.0f;
          break;

        case H3LIS331DL_ODR_1000Hz:
          *odr = 1000.0f;
          break;

        default:
          *odr = -1.0f;
          return COMPONENT_ERROR;
      }

    default:
      *odr = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  if ( handle->isEnabled == 1 )
  {
    if ( H3LIS331DL_Set_ODR_When_Enabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if ( H3LIS331DL_Set_ODR_When_Disabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_ODR_Value( DrvContextTypeDef *handle, float odr )
{
  if ( handle->isEnabled == 1 )
  {
    if( H3LIS331DL_Set_ODR_Value_When_Enabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if ( H3LIS331DL_Set_ODR_Value_When_Disabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the H3LIS331DL accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale pointer to where full scale write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_FS( DrvContextTypeDef *handle, float *fullScale )
{
  H3LIS331DL_Fullscale_t fs_low_level;

  if ( H3LIS331DL_GetFullScale( ( void* )handle, &fs_low_level ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  switch( fs_low_level )
  {
    case H3LIS331DL_FULLSCALE_2:
      *fullScale =  100.0f;
      break;
    case H3LIS331DL_FULLSCALE_4:
      *fullScale =  200.0f;
      break;
    case H3LIS331DL_FULLSCALE_8:
      *fullScale =  400.0f;
      break;
    default:
      *fullScale = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the functional full scale to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale )
{
  H3LIS331DL_Fullscale_t new_fs;

  switch( fullScale )
  {

  case FS_LOW:
  case FS_MID_LOW:
    new_fs = H3LIS331DL_FULLSCALE_2;
    break;

  case FS_MID:
    new_fs = H3LIS331DL_FULLSCALE_4;
    break;

  case FS_MID_HIGH:
  case FS_HIGH:
    new_fs = H3LIS331DL_FULLSCALE_8;
    break;

  default:
    return COMPONENT_ERROR;
  }

  if ( H3LIS331DL_SetFullScale( ( void* )handle, new_fs ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the full scale value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_FS_Value( DrvContextTypeDef *handle, float fullScale )
{
  H3LIS331DL_Fullscale_t new_fs;

  new_fs = ( fullScale <= 100.0f ) ?  H3LIS331DL_FULLSCALE_2
         : ( fullScale <= 200.0f ) ?  H3LIS331DL_FULLSCALE_4
         :                            H3LIS331DL_FULLSCALE_8;

  if ( H3LIS331DL_SetFullScale( ( void* )handle, new_fs ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the H3LIS331DL accelerometer sensor axes enabled/disabled status
 * @param handle the device handle
 * @param xyz_enabled pointer to where the vector of the axes enabled/disabled status write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_Axes_Status( DrvContextTypeDef *handle, uint8_t *xyz_enabled )
{
  H3LIS331DL_Axis_t axesEnabled;

  if ( H3LIS331DL_GetAxis( ( void * )handle, &axesEnabled ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  xyz_enabled[0] = ( axesEnabled & H3LIS331DL_X_ENABLE ) ? 1 : 0;
  xyz_enabled[1] = ( axesEnabled & H3LIS331DL_Y_ENABLE ) ? 1 : 0;
  xyz_enabled[2] = ( axesEnabled & H3LIS331DL_Z_ENABLE ) ? 1 : 0;

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor axes enabled/disabled
 * @param handle the device handle
 * @param enable_xyz vector of the axes enabled/disabled status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_Axes_Status( DrvContextTypeDef *handle, uint8_t *enable_xyz )
{
  H3LIS331DL_Axis_t axesEnable = 0x00;

  axesEnable |= ( enable_xyz[0] == 1 ) ? H3LIS331DL_X_ENABLE : H3LIS331DL_X_DISABLE;
  axesEnable |= ( enable_xyz[1] == 1 ) ? H3LIS331DL_Y_ENABLE : H3LIS331DL_Y_DISABLE;
  axesEnable |= ( enable_xyz[2] == 1 ) ? H3LIS331DL_Z_ENABLE : H3LIS331DL_Z_DISABLE;

  if ( H3LIS331DL_SetAxis( ( void * )handle, axesEnable ) == MEMS_ERROR )
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
static DrvStatusTypeDef H3LIS331DL_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data )
{

  if ( H3LIS331DL_ACC_ReadReg( (void *)handle, reg, data, 1 ) == MEMS_ERROR )
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
static DrvStatusTypeDef H3LIS331DL_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data )
{

  if ( H3LIS331DL_ACC_WriteReg( (void *)handle, reg, &data, 1 ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get data ready status
 * @param handle the device handle
 * @param status the data ready status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status )
{

  if ( H3LIS331DL_GetStatusBit( (void *)handle, H3LIS331DL_STATUS_REG_ZYXDA, status ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @}
 */

/** @addtogroup H3LIS331DL_Private_Functions Private functions
 * @{
 */

/**
 * @brief Get the H3LIS331DL accelerometer sensor raw axes data
 * @param handle the device handle
 * @param pData pointer to where the raw values of the axes write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Get_Axes_Raw_Data(DrvContextTypeDef *handle, int16_t *pData)
{
  H3LIS331DL_ACC_AxesRaw_t data_raw;

  /* Read output registers from H3LIS331DL_OUT_X_L to H3LIS331DL_OUT_Z_H. */
  if ( H3LIS331DL_GetAccAxesRaw( ( void* )handle, &data_raw ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  pData[0] = data_raw.AXIS_X;
  pData[1] = data_raw.AXIS_Y;
  pData[2] = data_raw.AXIS_Z;

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  float new_odr;

  switch( odr )
  {

  case ODR_LOW:
    new_odr = 0.5f;
    break;

  case ODR_MID_LOW:
    new_odr = 2.0f;
    break;

  case ODR_MID:
    new_odr = 10.0f;
    break;

  case ODR_MID_HIGH:
    new_odr = 100.0f;
    break;

  case ODR_HIGH:
    new_odr = 1000.0f;
    break;

  default:
    return COMPONENT_ERROR;
  }

  if ( H3LIS331DL_Set_ODR_Value_When_Enabled( ( void * )handle, new_odr ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  H3LIS331DL_Data_t *pComponentData = ( H3LIS331DL_Data_t * )pData->pComponentData;

  switch( odr )
  {

  case ODR_LOW:
    pComponentData->Previous_ODR = 0.5f;
    break;

  case ODR_MID_LOW:
    pComponentData->Previous_ODR = 2.0f;
    break;

  case ODR_MID:
    pComponentData->Previous_ODR = 10.0f;
    break;

  case ODR_MID_HIGH:
    pComponentData->Previous_ODR = 100.0f;
    break;

  case ODR_HIGH:
    pComponentData->Previous_ODR = 1000.0f;
    break;

  default:
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr )
{
  H3LIS331DL_Mode_t new_mode;
  H3LIS331DL_ODR_t new_odr;

  if ( odr < 50.0f )
  {
    new_mode = ( odr <= 0.5f ) ? H3LIS331DL_LOW_POWER_05
             : ( odr <= 1.0f ) ? H3LIS331DL_LOW_POWER_1
             : ( odr <= 2.0f ) ? H3LIS331DL_LOW_POWER_2
             : ( odr <= 5.0f ) ? H3LIS331DL_LOW_POWER_5
             :                   H3LIS331DL_LOW_POWER_10;

    /* Set power mode */
    if ( H3LIS331DL_SetMode( ( void * )handle, new_mode ) == MEMS_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }

  else
  {
    new_odr = ( odr <=  50.0f ) ? H3LIS331DL_ODR_50Hz
            : ( odr <= 100.0f ) ? H3LIS331DL_ODR_100Hz
            : ( odr <= 400.0f ) ? H3LIS331DL_ODR_400Hz
            :                     H3LIS331DL_ODR_1000Hz;

    /* Set Normal power mode */
    if ( H3LIS331DL_SetMode( ( void * )handle, H3LIS331DL_NORMAL ) == MEMS_ERROR )
    {
      return COMPONENT_ERROR;
    }

    /* Set ODR */
    if ( H3LIS331DL_SetODR( ( void* )handle, new_odr ) == MEMS_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the H3LIS331DL accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef H3LIS331DL_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  H3LIS331DL_Data_t *pComponentData = ( H3LIS331DL_Data_t * )pData->pComponentData;

  pComponentData->Previous_ODR = ( odr <=   0.5f ) ?    0.5f
                               : ( odr <=   1.0f ) ?    1.0f
                               : ( odr <=   2.0f ) ?    2.0f
                               : ( odr <=   5.0f ) ?    5.0f
                               : ( odr <=  10.0f ) ?   10.0f
                               : ( odr <=  50.0f ) ?   50.0f
                               : ( odr <= 100.0f ) ?  100.0f
                               : ( odr <= 400.0f ) ?  400.0f
                               :                     1000.0f;

  return COMPONENT_OK;
}

/**
 * @}
 */

/** @addtogroup H3LIS331DL_Callable_Private_Functions_Ext Callable private functions for extended features
 * @{
 */

  /* _NOTE_: Possible to add the functions for extended features of the sensor here */

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
