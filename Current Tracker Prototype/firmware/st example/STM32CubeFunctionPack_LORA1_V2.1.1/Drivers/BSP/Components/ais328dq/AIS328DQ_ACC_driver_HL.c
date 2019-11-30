/**
 ******************************************************************************
 * @file    AIS328DQ_ACC_driver_HL.c
 * @author  MEMS Application Team
 * @version V4.2.0
 * @date    01-February-2018
 * @brief   This file provides a set of high-level functions needed to manage
            the AIS328DQ sensor
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

#include "AIS328DQ_ACC_driver_HL.h"
#include <math.h>



/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup COMPONENTS COMPONENTS
 * @{
 */

/** @addtogroup AIS328DQ AIS328DQ
 * @{
 */

/* Link function for sensor peripheral */
extern uint8_t Sensor_IO_Write( void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite );
extern uint8_t Sensor_IO_Read( void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead );

/** @addtogroup AIS328DQ_Private_Function_Prototypes Private function prototypes
 * @{
 */

static DrvStatusTypeDef AIS328DQ_Get_Axes_Raw_Data(DrvContextTypeDef *handle, int16_t *pData);
static DrvStatusTypeDef AIS328DQ_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef AIS328DQ_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef AIS328DQ_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef AIS328DQ_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr );

/**
 * @}
 */

/** @addtogroup AIS328DQ_Callable_Private_Function_Prototypes Callable private function prototypes
 * @{
 */

static DrvStatusTypeDef AIS328DQ_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef AIS328DQ_DeInit( DrvContextTypeDef *handle );
static DrvStatusTypeDef AIS328DQ_Sensor_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef AIS328DQ_Sensor_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef AIS328DQ_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i );
static DrvStatusTypeDef AIS328DQ_Check_WhoAmI( DrvContextTypeDef *handle );
static DrvStatusTypeDef AIS328DQ_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration );
static DrvStatusTypeDef AIS328DQ_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value );
static DrvStatusTypeDef AIS328DQ_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity );
static DrvStatusTypeDef AIS328DQ_Get_ODR( DrvContextTypeDef *handle, float *odr );
static DrvStatusTypeDef AIS328DQ_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef AIS328DQ_Set_ODR_Value( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef AIS328DQ_Get_FS( DrvContextTypeDef *handle, float *fullScale );
static DrvStatusTypeDef AIS328DQ_Set_FS( DrvContextTypeDef *handle, SensorFs_t fs );
static DrvStatusTypeDef AIS328DQ_Set_FS_Value( DrvContextTypeDef *handle, float fullScale );
static DrvStatusTypeDef AIS328DQ_Get_Axes_Status( DrvContextTypeDef *handle, uint8_t *xyz_enabled );
static DrvStatusTypeDef AIS328DQ_Set_Axes_Status( DrvContextTypeDef *handle, uint8_t *enable_xyz );
static DrvStatusTypeDef AIS328DQ_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data );
static DrvStatusTypeDef AIS328DQ_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data );
static DrvStatusTypeDef AIS328DQ_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status );

/**
 * @}
 */

/** @addtogroup AIS328DQ_Callable_Private_Function_Ext_Prototypes Callable private function for extended features prototypes
 * @{
 */

  /* _NOTE_: Possible to add the functions for extended features of the sensor here */

/**
 * @}
 */

/** @addtogroup AIS328DQ_Public_Variables Public variables
 * @{
 */

#if 0 /* _NOTE_: Remove this line if you plan to use this structure below */
/**
 * @brief AIS328DQ accelero extended features driver internal structure
 */
AIS328DQ_ExtDrv_t AIS328DQ_ExtDrv =
{
  /* _NOTE_: Possible to add the functions for extended features of the sensor here */
};
#endif /* _NOTE_: Remove this line if you plan to use this structure above */

/**
 * @brief AIS328DQ accelero driver structure
 */
ACCELERO_Drv_t AIS328DQ_Drv =
{
  AIS328DQ_Init,
  AIS328DQ_DeInit,
  AIS328DQ_Sensor_Enable,
  AIS328DQ_Sensor_Disable,
  AIS328DQ_Get_WhoAmI,
  AIS328DQ_Check_WhoAmI,
  AIS328DQ_Get_Axes,
  AIS328DQ_Get_AxesRaw,
  AIS328DQ_Get_Sensitivity,
  AIS328DQ_Get_ODR,
  AIS328DQ_Set_ODR,
  AIS328DQ_Set_ODR_Value,
  AIS328DQ_Get_FS,
  AIS328DQ_Set_FS,
  AIS328DQ_Set_FS_Value,
  AIS328DQ_Get_Axes_Status,
  AIS328DQ_Set_Axes_Status,
  AIS328DQ_Read_Reg,
  AIS328DQ_Write_Reg,
  AIS328DQ_Get_DRDY_Status
};

/**
 * @}
 */

/** @addtogroup AIS328DQ_Callable_Private_Functions Callable private functions
 * @{
 */

/**
 * @brief Initialize the AIS328DQ sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Init( DrvContextTypeDef *handle )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  uint8_t axes_status[] = { 1, 1, 1 };

  if ( AIS328DQ_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Enable BDU. */
  if ( ais328dq_block_data_update_set( &ctx, PROPERTY_ENABLE ) == 1)
  {
    return COMPONENT_ERROR;
  }

  /* Select default output data rate in normal mode. */
  if ( AIS328DQ_Set_ODR_Value_When_Disabled( handle, 100.0f ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Full scale selection. */
  if ( AIS328DQ_Set_FS( handle, FS_LOW ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Enable axes. */
  if ( AIS328DQ_Set_Axes_Status( handle, axes_status ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isInitialized = 1;

  return COMPONENT_OK;
}

/**
 * @brief Deinitialize the AIS328DQ sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_DeInit( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  AIS328DQ_Data_t *pComponentData = ( AIS328DQ_Data_t * )pData->pComponentData;

  if ( AIS328DQ_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Disable the component */
  if( AIS328DQ_Sensor_Disable( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Reset previous output data rate. */
  pComponentData->Previous_ODR = 0.0f;

  handle->isInitialized = 0;

  return COMPONENT_OK;
}

/**
 * @brief Enable the AIS328DQ sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Sensor_Enable( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  AIS328DQ_Data_t *pComponentData = ( AIS328DQ_Data_t * )pData->pComponentData;

  /* Check if the component is already enabled */
  if ( handle->isEnabled == 1 )
  {
    return COMPONENT_OK;
  }

  /* Output data rate selection. */
  if ( AIS328DQ_Set_ODR_Value_When_Enabled( handle, pComponentData->Previous_ODR ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 1;

  return COMPONENT_OK;
}

/**
 * @brief Disable the AIS328DQ sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Sensor_Disable( DrvContextTypeDef *handle )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  AIS328DQ_Data_t *pComponentData = ( AIS328DQ_Data_t * )pData->pComponentData;

  /* Check if the component is already disabled */
  if ( handle->isEnabled == 0 )
  {
    return COMPONENT_OK;
  }

  /* Store actual output data rate. */
  if ( AIS328DQ_Get_ODR( handle, &( pComponentData->Previous_ODR ) ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Output data rate selection - power down */
  if ( ais328dq_data_rate_set( &ctx, AIS328DQ_ODR_OFF ) == 1 )
  {
    return COMPONENT_ERROR;
  }
  
  handle->isEnabled = 0;

  return COMPONENT_OK;
}

/**
 * @brief Get the WHO_AM_I ID of the AIS328DQ sensor
 * @param handle the device handle
 * @param who_am_i pointer to the value of WHO_AM_I register
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  /* Read WHO AM I register */
  if ( ais328dq_device_id_get( &ctx, ( uint8_t* )who_am_i ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Check the WHO_AM_I ID of the AIS328DQ sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Check_WhoAmI( DrvContextTypeDef *handle )
{
  uint8_t who_am_i = 0x00;

  if ( AIS328DQ_Get_WhoAmI( handle, &who_am_i ) == COMPONENT_ERROR )
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
 * @brief Get the AIS328DQ accelerometer sensor axes
 * @param handle the device handle
 * @param acceleration pointer to where acceleration data write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration )
{
  int16_t dataRaw[3];
  float sensitivity = 0;

  /* Read raw data from AIS328DQ output register. */
  if ( AIS328DQ_Get_Axes_Raw_Data( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Get AIS328DQ actual sensitivity. */
  if ( AIS328DQ_Get_Sensitivity( handle, &sensitivity ) == COMPONENT_ERROR )
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
 * @brief Get the AIS328DQ accelerometer sensor raw axes
 * @param handle the device handle
 * @param acceleration_raw pointer to where acceleration raw data write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value )
{
  int16_t dataRaw[3];

  /* Read raw data from AIS328DQ output register. */
  if ( AIS328DQ_Get_Axes_Raw_Data( handle, dataRaw ) == COMPONENT_ERROR )
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
 * @brief Get the AIS328DQ accelerometer sensor sensitivity
 * @param handle the device handle
 * @param sensitivity pointer to where sensitivity write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ais328dq_fs_t fullScale;

  /* Read actual full scale selection from sensor. */
  if ( ais328dq_full_scale_get( &ctx, &fullScale ) == 1 )
  {
    *sensitivity = -1.0f;
    return COMPONENT_ERROR;
  }

  /* Store the sensitivity based on actual full scale. */
  switch ( fullScale )
  {
  case AIS328DQ_2g:
    *sensitivity = ( float )AIS328DQ_ACC_SENSITIVITY_FOR_FS_2G;
    break;

  case AIS328DQ_4g:
    *sensitivity = ( float )AIS328DQ_ACC_SENSITIVITY_FOR_FS_4G;
    break;

  case AIS328DQ_8g:
    *sensitivity = ( float )AIS328DQ_ACC_SENSITIVITY_FOR_FS_8G;
    break;

  default:
    *sensitivity = -1.0f;
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the AIS328DQ accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr pointer to where output data rate write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Get_ODR( DrvContextTypeDef *handle, float *odr )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ais328dq_dr_t odr_low_level;
  
  /* Read actual power mode selection from sensor. */
  if ( ais328dq_data_rate_get( &ctx, &odr_low_level ) == 1 )
  {
    *odr = -1.0f;
    return COMPONENT_ERROR;
  }

  switch ( odr_low_level )
  {
    case AIS328DQ_ODR_OFF:
      *odr = 0.0f;
      break;

    case AIS328DQ_ODR_Hz5:
      *odr = 0.5f;
      break;

    case AIS328DQ_ODR_1Hz:
      *odr = 1.0f;
      break;

    case AIS328DQ_ODR_2Hz:
      *odr = 2.0f;
      break;

    case AIS328DQ_ODR_5Hz:
      *odr = 5.0f;
      break;

    case AIS328DQ_ODR_10Hz:
      *odr = 10.0f;
      break;

    case AIS328DQ_ODR_50Hz:
      *odr = 50.0f;
      break;

    case AIS328DQ_ODR_100Hz:
      *odr = 100.0f;
      break;

    case AIS328DQ_ODR_400Hz:
      *odr = 400.0f;
      break;

    case AIS328DQ_ODR_1kHz:
      *odr = 1000.0f;
      break;

    default:
      *odr = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the AIS328DQ accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  if ( handle->isEnabled == 1 )
  {
    if ( AIS328DQ_Set_ODR_When_Enabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if ( AIS328DQ_Set_ODR_When_Disabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the AIS328DQ accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_ODR_Value( DrvContextTypeDef *handle, float odr )
{
  if ( handle->isEnabled == 1 )
  {
    if( AIS328DQ_Set_ODR_Value_When_Enabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if ( AIS328DQ_Set_ODR_Value_When_Disabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the AIS328DQ accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale pointer to where full scale write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Get_FS( DrvContextTypeDef *handle, float *fullScale )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ais328dq_fs_t fs;

  if ( ais328dq_full_scale_get( &ctx, &fs ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  switch( fs )
  {
    case AIS328DQ_2g:
      *fullScale =  2.0f;
      break;
      
    case AIS328DQ_4g:
      *fullScale =  4.0f;
      break;
      
    case AIS328DQ_8g:
      *fullScale =  8.0f;
      break;
      
    default:
      *fullScale = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the AIS328DQ accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the functional full scale to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ais328dq_fs_t new_fs;

  switch( fullScale )
  {
    case FS_LOW:
    case FS_MID_LOW:
      new_fs = AIS328DQ_2g;
      break;
      
    case FS_MID:
      new_fs = AIS328DQ_4g;
      break;
      
    case FS_MID_HIGH:
    case FS_HIGH:
      new_fs = AIS328DQ_8g;
      break;
      
    default:
      return COMPONENT_ERROR;
  }

  if ( ais328dq_full_scale_set( &ctx, new_fs ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the AIS328DQ accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the full scale value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_FS_Value( DrvContextTypeDef *handle, float fullScale )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ais328dq_fs_t new_fs;

  new_fs = ( fullScale <=  2.0f ) ? AIS328DQ_2g
         : ( fullScale <= 4.0f ) ?  AIS328DQ_4g
         :                          AIS328DQ_8g;

  if ( ais328dq_full_scale_set( &ctx, new_fs ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the AIS328DQ accelerometer sensor axes enabled/disabled status
 * @param handle the device handle
 * @param xyz_enabled pointer to where the vector of the axes enabled/disabled status write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Get_Axes_Status( DrvContextTypeDef *handle, uint8_t *xyz_enabled )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  uint8_t x_en = 0;
  uint8_t y_en = 0;
  uint8_t z_en = 0;

  if ( ais328dq_axis_x_data_get( &ctx, &x_en ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  if ( ais328dq_axis_y_data_get( &ctx, &y_en ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  if ( ais328dq_axis_z_data_get( &ctx, &z_en ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  xyz_enabled[0] = x_en;
  xyz_enabled[1] = y_en;
  xyz_enabled[2] = z_en;

  return COMPONENT_OK;
}

/**
 * @brief Set the AIS328DQ accelerometer sensor axes enabled/disabled
 * @param handle the device handle
 * @param enable_xyz vector of the axes enabled/disabled status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_Axes_Status( DrvContextTypeDef *handle, uint8_t *enable_xyz )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  uint8_t x_en = 0;
  uint8_t y_en = 0;
  uint8_t z_en = 0;

  x_en = ( enable_xyz[0] == 1 ) ? 1 : 0;
  y_en = ( enable_xyz[1] == 1 ) ? 1 : 0;
  z_en = ( enable_xyz[2] == 1 ) ? 1 : 0;

  if ( ais328dq_axis_x_data_set( &ctx, x_en ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  if ( ais328dq_axis_y_data_set( &ctx, y_en ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  if ( ais328dq_axis_z_data_set( &ctx, z_en ) == 1 )
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
static DrvStatusTypeDef AIS328DQ_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  
  if ( ais328dq_read_reg( &ctx, reg, data, 1 ) == 1 )
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
static DrvStatusTypeDef AIS328DQ_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  
  if ( ais328dq_write_reg( &ctx, reg, &data, 1 ) == 1 )
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
static DrvStatusTypeDef AIS328DQ_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};

  if ( ais328dq_flag_data_ready_get( &ctx, status ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @}
 */

/** @addtogroup AIS328DQ_Private_Functions Private functions
 * @{
 */

/**
 * @brief Get the AIS328DQ accelerometer sensor raw axes data
 * @param handle the device handle
 * @param pData pointer to where the raw values of the axes write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Get_Axes_Raw_Data(DrvContextTypeDef *handle, int16_t *pData)
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  uint8_t regValue[6] = {0, 0, 0, 0, 0, 0};
  
  /* Read output registers from AIS328DQ_OUT_X_L to AIS328DQ_OUT_Z_H. */
  if ( ais328dq_acceleration_raw_get( &ctx, ( uint8_t* )regValue ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  /* Format the data. */
  pData[0] = ( ( ( ( int16_t )regValue[1] ) << 8 ) + ( int16_t )regValue[0] );
  pData[1] = ( ( ( ( int16_t )regValue[3] ) << 8 ) + ( int16_t )regValue[2] );
  pData[2] = ( ( ( ( int16_t )regValue[5] ) << 8 ) + ( int16_t )regValue[4] );
  
  pData[0] >>= 4;
  pData[1] >>= 4;
  pData[2] >>= 4;
  
  return COMPONENT_OK;
}

/**
 * @brief Set the AIS328DQ accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr )
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

  if ( AIS328DQ_Set_ODR_Value_When_Enabled( ( void * )handle, new_odr ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the AIS328DQ accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  AIS328DQ_Data_t *pComponentData = ( AIS328DQ_Data_t * )pData->pComponentData;

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
 * @brief Set the AIS328DQ accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr )
{
  ais328dq_ctx_t ctx = {.write_reg = Sensor_IO_Write, .read_reg = Sensor_IO_Read, .handle = (void *)handle};
  ais328dq_dr_t new_odr;

  new_odr = ( odr <=   0.5f ) ? AIS328DQ_ODR_Hz5
          : ( odr <=   1.0f ) ? AIS328DQ_ODR_1Hz
          : ( odr <=   2.0f ) ? AIS328DQ_ODR_2Hz
          : ( odr <=   5.0f ) ? AIS328DQ_ODR_5Hz
          : ( odr <=  10.0f ) ? AIS328DQ_ODR_10Hz
          : ( odr <=  50.0f ) ? AIS328DQ_ODR_50Hz
          : ( odr <= 100.0f ) ? AIS328DQ_ODR_100Hz
          : ( odr <= 400.0f ) ? AIS328DQ_ODR_400Hz
          :                     AIS328DQ_ODR_1kHz;

  /* Set ODR */
  if ( ais328dq_data_rate_set( &ctx, new_odr ) == 1 )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the AIS328DQ accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef AIS328DQ_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  AIS328DQ_Data_t *pComponentData = ( AIS328DQ_Data_t * )pData->pComponentData;

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

/** @addtogroup AIS328DQ_Callable_Private_Functions_Ext Callable private functions for extended features
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
