/**
 ******************************************************************************
 * @file    LIS2DH12_ACC_driver_HL.c
 * @author  MEMS Application Team
 * @version V4.2.0
 * @date    01-February-2018
 * @brief   This file provides a set of high-level functions needed to manage
            the LIS2DH12 sensor
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

#include "LIS2DH12_ACC_driver_HL.h"



/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup COMPONENTS COMPONENTS
 * @{
 */

/** @addtogroup LIS2DH12 LIS2DH12
 * @{
 */

/** @addtogroup LIS2DH12_Private_Function_Prototypes Private function prototypes
 * @{
 */

static DrvStatusTypeDef LIS2DH12_Get_Axes_Raw_Data(DrvContextTypeDef *handle, int16_t *pData);
static DrvStatusTypeDef LIS2DH12_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef LIS2DH12_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef LIS2DH12_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef LIS2DH12_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr );

/**
 * @}
 */

/** @addtogroup LIS2DH12_Callable_Private_Function_Prototypes Callable private function prototypes
 * @{
 */

static DrvStatusTypeDef LIS2DH12_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef LIS2DH12_DeInit( DrvContextTypeDef *handle );
static DrvStatusTypeDef LIS2DH12_Sensor_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef LIS2DH12_Sensor_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef LIS2DH12_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i );
static DrvStatusTypeDef LIS2DH12_Check_WhoAmI( DrvContextTypeDef *handle );
static DrvStatusTypeDef LIS2DH12_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration );
static DrvStatusTypeDef LIS2DH12_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value );
static DrvStatusTypeDef LIS2DH12_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity );
static DrvStatusTypeDef LIS2DH12_Get_ODR( DrvContextTypeDef *handle, float *odr );
static DrvStatusTypeDef LIS2DH12_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr );
static DrvStatusTypeDef LIS2DH12_Set_ODR_Value( DrvContextTypeDef *handle, float odr );
static DrvStatusTypeDef LIS2DH12_Get_FS( DrvContextTypeDef *handle, float *fullScale );
static DrvStatusTypeDef LIS2DH12_Set_FS( DrvContextTypeDef *handle, SensorFs_t fs );
static DrvStatusTypeDef LIS2DH12_Set_FS_Value( DrvContextTypeDef *handle, float fullScale );
static DrvStatusTypeDef LIS2DH12_Get_Axes_Status( DrvContextTypeDef *handle, uint8_t *xyz_enabled );
static DrvStatusTypeDef LIS2DH12_Set_Axes_Status( DrvContextTypeDef *handle, uint8_t *enable_xyz );
static DrvStatusTypeDef LIS2DH12_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data );
static DrvStatusTypeDef LIS2DH12_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data );
static DrvStatusTypeDef LIS2DH12_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status );

/**
 * @}
 */

/** @addtogroup LIS2DH12_Callable_Private_Function_Ext_Prototypes Callable private function for extended features prototypes
 * @{
 */

static DrvStatusTypeDef LIS2DH12_FIFO_Get_Overrun_Status( DrvContextTypeDef *handle, uint8_t *status );
static DrvStatusTypeDef LIS2DH12_FIFO_Get_Num_Of_Samples( DrvContextTypeDef *handle, uint16_t *nSamples );
static DrvStatusTypeDef LIS2DH12_FIFO_Set_Mode( DrvContextTypeDef *handle, uint8_t mode );
static DrvStatusTypeDef LIS2DH12_FIFO_Set_INT1_FIFO_Overrun( DrvContextTypeDef *handle, uint8_t status );
static DrvStatusTypeDef LIS2DH12_Get_AxesSuperRaw( DrvContextTypeDef *handle, int16_t *pData, ACTIVE_AXIS_t axl_axis );
static DrvStatusTypeDef LIS2DH12_Get_OpMode( DrvContextTypeDef *handle, OP_MODE_t *axl_opMode );
static DrvStatusTypeDef LIS2DH12_Set_OpMode( DrvContextTypeDef *handle, OP_MODE_t axl_opMode );
static DrvStatusTypeDef LIS2DH12_Get_Active_Axis( DrvContextTypeDef *handle, ACTIVE_AXIS_t *axl_axis );
static DrvStatusTypeDef LIS2DH12_Set_Active_Axis( DrvContextTypeDef *handle, ACTIVE_AXIS_t axl_axis );
static DrvStatusTypeDef LIS2DH12_Enable_HP_Filter( DrvContextTypeDef *handle );
static DrvStatusTypeDef LIS2DH12_Disable_HP_Filter( DrvContextTypeDef *handle );
static DrvStatusTypeDef LIS2DH12_ClearDRDY( DrvContextTypeDef *handle, ACTIVE_AXIS_t axl_axis );
static DrvStatusTypeDef LIS2DH12_Set_INT1_DRDY( DrvContextTypeDef *handle, INT1_DRDY_CONFIG_t axl_drdyStatus );


/**
 * @}
 */

/** @addtogroup LIS2DH12_Public_Variables Public variables
 * @{
 */

/**
 * @brief LIS2DH12 accelero extended features driver internal structure
 */
LIS2DH12_ExtDrv_t LIS2DH12_ExtDrv =
{
  LIS2DH12_FIFO_Get_Overrun_Status,
  LIS2DH12_FIFO_Get_Num_Of_Samples,
  LIS2DH12_FIFO_Set_Mode,
  LIS2DH12_FIFO_Set_INT1_FIFO_Overrun,
  LIS2DH12_Get_AxesSuperRaw,
  LIS2DH12_Get_OpMode,
  LIS2DH12_Set_OpMode,
  LIS2DH12_Get_Active_Axis,
  LIS2DH12_Set_Active_Axis,
  LIS2DH12_Enable_HP_Filter,
  LIS2DH12_Disable_HP_Filter,
  LIS2DH12_ClearDRDY,
  LIS2DH12_Set_INT1_DRDY
};

/**
 * @brief LIS2DH12 accelero driver structure
 */
ACCELERO_Drv_t LIS2DH12_Drv =
{
  LIS2DH12_Init,
  LIS2DH12_DeInit,
  LIS2DH12_Sensor_Enable,
  LIS2DH12_Sensor_Disable,
  LIS2DH12_Get_WhoAmI,
  LIS2DH12_Check_WhoAmI,
  LIS2DH12_Get_Axes,
  LIS2DH12_Get_AxesRaw,
  LIS2DH12_Get_Sensitivity,
  LIS2DH12_Get_ODR,
  LIS2DH12_Set_ODR,
  LIS2DH12_Set_ODR_Value,
  LIS2DH12_Get_FS,
  LIS2DH12_Set_FS,
  LIS2DH12_Set_FS_Value,
  LIS2DH12_Get_Axes_Status,
  LIS2DH12_Set_Axes_Status,
  LIS2DH12_Read_Reg,
  LIS2DH12_Write_Reg,
  LIS2DH12_Get_DRDY_Status
};

/**
 * @}
 */

/** @addtogroup LIS2DH12_Callable_Private_Functions Callable private functions
 * @{
 */

/**
 * @brief Initialize the LIS2DH12 sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Init( DrvContextTypeDef *handle )
{
  uint8_t axes_status[] = { 1, 1, 1 };

  if ( LIS2DH12_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Enable BDU. */
  if ( LIS2DH12_SetBDU( ( void * )handle, LIS2DH12_ENABLE ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* FIFO mode selection - FIFO disable. */
  if ( LIS2DH12_FIFOModeEnable( ( void * )handle, LIS2DH12_FIFO_DISABLE ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Output data rate selection - power down. */
  if ( LIS2DH12_SetODR( ( void* )handle, LIS2DH12_ODR_POWER_DOWN ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Set default power mode - High resolution. */
  if ( LIS2DH12_SetMode( ( void * )handle, LIS2DH12_HIGH_RES ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Select default output data rate. */
  if ( LIS2DH12_Set_ODR_When_Disabled( handle, ODR_MID_HIGH ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Full scale selection. */
  if ( LIS2DH12_Set_FS( handle, FS_LOW ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Enable axes. */
  if ( LIS2DH12_Set_Axes_Status( handle, axes_status ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isInitialized = 1;

  return COMPONENT_OK;
}

/**
 * @brief Deinitialize the LIS2DH12 sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_DeInit( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  LIS2DH12_Data_t *pComponentData = ( LIS2DH12_Data_t * )pData->pComponentData;

  if ( LIS2DH12_Check_WhoAmI( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Disable the component */
  if( LIS2DH12_Sensor_Disable( handle ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Reset previous output data rate. */
  pComponentData->Previous_ODR = 0.0f;

  handle->isInitialized = 0;

  return COMPONENT_OK;
}

/**
 * @brief Enable the LIS2DH12 sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Sensor_Enable( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  LIS2DH12_Data_t *pComponentData = ( LIS2DH12_Data_t * )pData->pComponentData;

  /* Check if the component is already enabled */
  if ( handle->isEnabled == 1 )
  {
    return COMPONENT_OK;
  }

  /* Output data rate selection. */
  if ( LIS2DH12_Set_ODR_Value_When_Enabled( handle, pComponentData->Previous_ODR ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 1;

  return COMPONENT_OK;
}

/**
 * @brief Disable the LIS2DH12 sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Sensor_Disable( DrvContextTypeDef *handle )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  LIS2DH12_Data_t *pComponentData = ( LIS2DH12_Data_t * )pData->pComponentData;

  /* Check if the component is already disabled */
  if ( handle->isEnabled == 0 )
  {
    return COMPONENT_OK;
  }

  /* Store actual output data rate. */
  if ( LIS2DH12_Get_ODR( handle, &( pComponentData->Previous_ODR ) ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Output data rate selection - power down. */
  if ( LIS2DH12_SetODR( ( void* )handle, LIS2DH12_ODR_POWER_DOWN ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  handle->isEnabled = 0;

  return COMPONENT_OK;
}

/**
 * @brief Get the WHO_AM_I ID of the LIS2DH12 sensor
 * @param handle the device handle
 * @param who_am_i pointer to the value of WHO_AM_I register
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_WhoAmI( DrvContextTypeDef *handle, uint8_t *who_am_i )
{
  /* Read WHO AM I register */
  if ( LIS2DH12_GetWHO_AM_I( ( void * )handle, ( uint8_t* )who_am_i ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Check the WHO_AM_I ID of the LIS2DH12 sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Check_WhoAmI( DrvContextTypeDef *handle )
{
  uint8_t who_am_i = 0x00;

  if ( LIS2DH12_Get_WhoAmI( handle, &who_am_i ) == COMPONENT_ERROR )
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
 * @brief Get the LIS2DH12 accelerometer sensor axes
 * @param handle the device handle
 * @param acceleration pointer to where acceleration data write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_Axes( DrvContextTypeDef *handle, SensorAxes_t *acceleration )
{
  int16_t dataRaw[3];
  float sensitivity = 0;

  /* Read raw data from LIS2DH12 output register. */
  if ( LIS2DH12_Get_Axes_Raw_Data( handle, dataRaw ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Get LIS2DH12 actual sensitivity. */
  if ( LIS2DH12_Get_Sensitivity( handle, &sensitivity ) == COMPONENT_ERROR )
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
 * @brief Get the LIS2DH12 accelerometer sensor raw axes
 * @param handle the device handle
 * @param acceleration_raw pointer to where acceleration raw data write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_AxesRaw( DrvContextTypeDef *handle, SensorAxesRaw_t *value )
{
  int16_t dataRaw[3];

  /* Read raw data from LIS2DH12 output register. */
  if ( LIS2DH12_Get_Axes_Raw_Data( handle, dataRaw ) == COMPONENT_ERROR )
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
 * @brief Get the LIS2DH12 accelerometer sensor sensitivity
 * @param handle the device handle
 * @param sensitivity pointer to where sensitivity write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_Sensitivity( DrvContextTypeDef *handle, float *sensitivity )
{
  LIS2DH12_Mode_t mode;
  LIS2DH12_Fullscale_t fullScale;

  /* Read actual power mode selection from sensor. */
  if ( LIS2DH12_GetMode( ( void * )handle, &mode ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Read actual full scale selection from sensor. */
  if ( LIS2DH12_GetFullScale( ( void * )handle, &fullScale ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Store the sensitivity based on actual operating mode and full scale. */
  switch ( mode )
  {

  case LIS2DH12_HIGH_RES:
    switch ( fullScale )
    {

    case LIS2DH12_FULLSCALE_2:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_2G_HI_RES;
      break;

    case LIS2DH12_FULLSCALE_4:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_4G_HI_RES;
      break;

    case LIS2DH12_FULLSCALE_8:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_8G_HI_RES;
      break;

    case LIS2DH12_FULLSCALE_16:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_16G_HI_RES;
      break;

    default:
      *sensitivity = -1.0f;
      return COMPONENT_ERROR;
    }

    break;

  case LIS2DH12_NORMAL:
    switch ( fullScale )
    {

    case LIS2DH12_FULLSCALE_2:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_2G_NORMAL;
      break;

    case LIS2DH12_FULLSCALE_4:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_4G_NORMAL;
      break;

    case LIS2DH12_FULLSCALE_8:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_8G_NORMAL;
      break;

    case LIS2DH12_FULLSCALE_16:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_16G_NORMAL;
      break;

    default:
      *sensitivity = -1.0f;
      return COMPONENT_ERROR;
    }

    break;

  case LIS2DH12_LOW_POWER:
    switch ( fullScale )
    {

    case LIS2DH12_FULLSCALE_2:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_2G_LO_POW;
      break;

    case LIS2DH12_FULLSCALE_4:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_4G_LO_POW;
      break;

    case LIS2DH12_FULLSCALE_8:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_8G_LO_POW;
      break;

    case LIS2DH12_FULLSCALE_16:
      *sensitivity = ( float )LIS2DH12_ACC_SENSITIVITY_FOR_FS_16G_LO_POW;
      break;

    default:
      *sensitivity = -1.0f;
      return COMPONENT_ERROR;
    }

    break;

  default:
    *sensitivity = -1.0f;
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the LIS2DH12 accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr pointer to where output data rate write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_ODR( DrvContextTypeDef *handle, float *odr )
{
  LIS2DH12_Mode_t mode;
  LIS2DH12_ODR_t odr_low_level;

  /* Read actual power mode selection from sensor. */
  if ( LIS2DH12_GetMode( ( void * )handle, &mode ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Read actual output data rate selection from sensor. */
  if ( LIS2DH12_GetODR( ( void * )handle, &odr_low_level ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  switch ( odr_low_level )
  {

  case LIS2DH12_ODR_POWER_DOWN:
    *odr =      0.0f;
    break;

  case LIS2DH12_ODR_1Hz:
    *odr =      1.0f;
    break;

  case LIS2DH12_ODR_10Hz:
    *odr =     10.0f;
    break;

  case LIS2DH12_ODR_25Hz:
    *odr =     25.0f;
    break;

  case LIS2DH12_ODR_50Hz:
    *odr =     50.0f;
    break;

  case LIS2DH12_ODR_100Hz:
    *odr =    100.0f;
    break;

  case LIS2DH12_ODR_200Hz:
    *odr =    200.0f;
    break;

  case LIS2DH12_ODR_400Hz:
    *odr =    400.0f;
    break;

  case LIS2DH12_ODR_1620Hz_LP:
    switch ( mode )
    {

    case LIS2DH12_LOW_POWER:
      *odr = 1620.0f;
      break;

    default:
      *odr =   -1.0f;
      return COMPONENT_ERROR;
    }

  case LIS2DH12_ODR_1344Hz_NP_5367HZ_LP:
    switch ( mode )
    {

    case LIS2DH12_NORMAL:
    case LIS2DH12_HIGH_RES:
      *odr = 1344.0f;
      break;

    case LIS2DH12_LOW_POWER:
      *odr = 5376.0f;
      break;

    default:
      *odr =   -1.0f;
      return COMPONENT_ERROR;
    }

  default:
    *odr =     -1.0f;
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the LIS2DH12 accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_ODR( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  if ( handle->isEnabled == 1 )
  {
    if ( LIS2DH12_Set_ODR_When_Enabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if ( LIS2DH12_Set_ODR_When_Disabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the LIS2DH12 accelerometer sensor output data rate
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_ODR_Value( DrvContextTypeDef *handle, float odr )
{
  if ( handle->isEnabled == 1 )
  {
    if( LIS2DH12_Set_ODR_Value_When_Enabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }
  else
  {
    if ( LIS2DH12_Set_ODR_Value_When_Disabled( handle, odr ) == COMPONENT_ERROR )
    {
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the LIS2DH12 accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale pointer to where full scale write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_FS( DrvContextTypeDef *handle, float *fullScale )
{
  LIS2DH12_Fullscale_t fs_low_level;

  if ( LIS2DH12_GetFullScale( ( void* )handle, &fs_low_level ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  switch( fs_low_level )
  {
    case LIS2DH12_FULLSCALE_2:
      *fullScale =  2.0f;
      break;
    case LIS2DH12_FULLSCALE_4:
      *fullScale =  4.0f;
      break;
    case LIS2DH12_FULLSCALE_8:
      *fullScale =  8.0f;
      break;
    case LIS2DH12_FULLSCALE_16:
      *fullScale = 16.0f;
      break;
    default:
      *fullScale = -1.0f;
      return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the LIS2DH12 accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the functional full scale to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_FS( DrvContextTypeDef *handle, SensorFs_t fullScale )
{
  LIS2DH12_Fullscale_t new_fs;

  switch( fullScale )
  {

  case FS_LOW:
    new_fs = LIS2DH12_FULLSCALE_2;
    break;

  case FS_MID_LOW:
  case FS_MID:
    new_fs = LIS2DH12_FULLSCALE_4;
    break;

  case FS_MID_HIGH:
    new_fs = LIS2DH12_FULLSCALE_8;
    break;

  case FS_HIGH:
    new_fs = LIS2DH12_FULLSCALE_16;
    break;

  default:
    return COMPONENT_ERROR;
  }

  if ( LIS2DH12_SetFullScale( ( void* )handle, new_fs ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the LIS2DH12 accelerometer sensor full scale
 * @param handle the device handle
 * @param fullScale the full scale value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_FS_Value( DrvContextTypeDef *handle, float fullScale )
{
  LIS2DH12_Fullscale_t new_fs;

  new_fs = ( fullScale <= 2.0f ) ?  LIS2DH12_FULLSCALE_2
         : ( fullScale <= 4.0f ) ?  LIS2DH12_FULLSCALE_4
         : ( fullScale <= 8.0f ) ?  LIS2DH12_FULLSCALE_8
         :                          LIS2DH12_FULLSCALE_16;

  if ( LIS2DH12_SetFullScale( ( void* )handle, new_fs ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Get the LIS2DH12 accelerometer sensor axes enabled/disabled status
 * @param handle the device handle
 * @param xyz_enabled pointer to where the vector of the axes enabled/disabled status write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_Axes_Status( DrvContextTypeDef *handle, uint8_t *xyz_enabled )
{
  LIS2DH12_AxesEnabled_t axesEnabled;

  if ( LIS2DH12_GetAxesEnabled( ( void * )handle, &axesEnabled ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  xyz_enabled[0] = ( axesEnabled & LIS2DH12_X_ENABLE ) ? 1 : 0;
  xyz_enabled[1] = ( axesEnabled & LIS2DH12_Y_ENABLE ) ? 1 : 0;
  xyz_enabled[2] = ( axesEnabled & LIS2DH12_Z_ENABLE ) ? 1 : 0;

  return COMPONENT_OK;
}

/**
 * @brief Set the LIS2DH12 accelerometer sensor axes enabled/disabled
 * @param handle the device handle
 * @param enable_xyz vector of the axes enabled/disabled status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_Axes_Status( DrvContextTypeDef *handle, uint8_t *enable_xyz )
{
  LIS2DH12_AxesEnabled_t axesEnable = 0x00;

  axesEnable |= ( enable_xyz[0] == 1 ) ? LIS2DH12_X_ENABLE : LIS2DH12_X_DISABLE;
  axesEnable |= ( enable_xyz[1] == 1 ) ? LIS2DH12_Y_ENABLE : LIS2DH12_Y_DISABLE;
  axesEnable |= ( enable_xyz[2] == 1 ) ? LIS2DH12_Z_ENABLE : LIS2DH12_Z_DISABLE;

  if ( LIS2DH12_SetAxesEnabled( ( void * )handle, axesEnable ) == MEMS_ERROR )
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
static DrvStatusTypeDef LIS2DH12_Read_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t *data )
{

  if ( LIS2DH12_ACC_ReadReg( (void *)handle, reg, data, 1 ) == MEMS_ERROR )
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
static DrvStatusTypeDef LIS2DH12_Write_Reg( DrvContextTypeDef *handle, uint8_t reg, uint8_t data )
{

  if ( LIS2DH12_ACC_WriteReg( (void *)handle, reg, &data, 1 ) == MEMS_ERROR )
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
static DrvStatusTypeDef LIS2DH12_Get_DRDY_Status( DrvContextTypeDef *handle, uint8_t *status )
{

  if ( LIS2DH12_GetStatusBit( (void *)handle, LIS2DH12_STATUS_REG_ZYXDA, status ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @}
 */

/** @addtogroup LIS2DH12_Private_Functions Private functions
 * @{
 */

/**
 * @brief Get the LIS2DH12 accelerometer sensor raw axes data
 * @param handle the device handle
 * @param pData pointer to where the raw values of the axes write to
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_Axes_Raw_Data(DrvContextTypeDef *handle, int16_t *pData)
{
  uint8_t regValue[6] = { 0, 0, 0, 0, 0, 0 };
  LIS2DH12_Mode_t mode;

  /* Read output registers from LIS2DH12_OUT_X_L to LIS2DH12_OUT_Z_H. */
  if ( LIS2DH12_GetAccAxesRaw( ( void* )handle, ( u8_t* )regValue ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  pData[0] = ( ( ( ( int16_t )regValue[1] ) << 8 ) + ( int16_t )regValue[0] );
  pData[1] = ( ( ( ( int16_t )regValue[3] ) << 8 ) + ( int16_t )regValue[2] );
  pData[2] = ( ( ( ( int16_t )regValue[5] ) << 8 ) + ( int16_t )regValue[4] );

  /* Read actual power mode selection from sensor. */
  if ( LIS2DH12_GetMode( ( void * )handle, &mode ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Select raw data format according to power mode selected. */
  switch ( mode )
  {

  case LIS2DH12_HIGH_RES:   /* 12 bits left justified */
    pData[0] >>= 4;
    pData[1] >>= 4;
    pData[2] >>= 4;
    break;

  case LIS2DH12_NORMAL:     /* 10 bits left justified */
    pData[0] >>= 6;
    pData[1] >>= 6;
    pData[2] >>= 6;
    break;

  case LIS2DH12_LOW_POWER:  /*  8 bits left justified */
    pData[0] >>= 8;
    pData[1] >>= 8;
    pData[2] >>= 8;
    break;

  default:
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the LIS2DH12 accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_ODR_When_Enabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  LIS2DH12_ODR_t new_odr;

  switch( odr )
  {

  case ODR_LOW:
    new_odr = LIS2DH12_ODR_10Hz;
    break;

  case ODR_MID_LOW:
    new_odr = LIS2DH12_ODR_25Hz;
    break;

  case ODR_MID:
    new_odr = LIS2DH12_ODR_50Hz;
    break;

  case ODR_MID_HIGH:
    new_odr = LIS2DH12_ODR_100Hz;
    break;

  case ODR_HIGH:
    new_odr = LIS2DH12_ODR_200Hz;
    break;

  default:
    return COMPONENT_ERROR;
  }

  if ( LIS2DH12_SetODR( ( void * )handle, new_odr ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the LIS2DH12 accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the functional output data rate to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_ODR_When_Disabled( DrvContextTypeDef *handle, SensorOdr_t odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  LIS2DH12_Data_t *pComponentData = ( LIS2DH12_Data_t * )pData->pComponentData;

  switch( odr )
  {

  case ODR_LOW:
    pComponentData->Previous_ODR =  10.0f;
    break;

  case ODR_MID_LOW:
    pComponentData->Previous_ODR =  25.0f;
    break;

  case ODR_MID:
    pComponentData->Previous_ODR =  50.0f;
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
 * @brief Set the LIS2DH12 accelerometer sensor output data rate when enabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_ODR_Value_When_Enabled( DrvContextTypeDef *handle, float odr )
{
  LIS2DH12_Mode_t mode;
  LIS2DH12_ODR_t new_odr;

  /* Read actual power mode selection from sensor. */
  if ( LIS2DH12_GetMode( ( void * )handle, &mode ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  if ( odr <= 400.0f )
  {
    new_odr = ( odr <=   1.0f ) ? LIS2DH12_ODR_1Hz
            : ( odr <=  10.0f ) ? LIS2DH12_ODR_10Hz
            : ( odr <=  25.0f ) ? LIS2DH12_ODR_25Hz
            : ( odr <=  50.0f ) ? LIS2DH12_ODR_50Hz
            : ( odr <= 100.0f ) ? LIS2DH12_ODR_100Hz
            : ( odr <= 200.0f ) ? LIS2DH12_ODR_200Hz
            :                     LIS2DH12_ODR_400Hz;
  }

  else
  {
    switch ( mode )
    {

    case LIS2DH12_LOW_POWER:
      new_odr = ( odr <= 1620.0f ) ? LIS2DH12_ODR_1620Hz_LP : LIS2DH12_ODR_1344Hz_NP_5367HZ_LP;
      break;

    case LIS2DH12_NORMAL:
    case LIS2DH12_HIGH_RES:
      new_odr = LIS2DH12_ODR_1344Hz_NP_5367HZ_LP;
      break;

    default:
      return COMPONENT_ERROR;
    }
  }

  if ( LIS2DH12_SetODR( ( void* )handle, new_odr ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
 * @brief Set the LIS2DH12 accelerometer sensor output data rate when disabled
 * @param handle the device handle
 * @param odr the output data rate value to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_ODR_Value_When_Disabled( DrvContextTypeDef *handle, float odr )
{
  ACCELERO_Data_t *pData = ( ACCELERO_Data_t * )handle->pData;
  LIS2DH12_Data_t *pComponentData = ( LIS2DH12_Data_t * )pData->pComponentData;
  LIS2DH12_Mode_t mode;

  /* Read actual power mode selection from sensor. */
  if ( LIS2DH12_GetMode( ( void * )handle, &mode ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  if ( odr <= 400.0f )
  {
    pComponentData->Previous_ODR = ( odr <=   1.0f ) ?   1.0f
                                 : ( odr <=  10.0f ) ?  10.0f
                                 : ( odr <=  25.0f ) ?  25.0f
                                 : ( odr <=  50.0f ) ?  50.0f
                                 : ( odr <= 100.0f ) ? 100.0f
                                 : ( odr <= 200.0f ) ? 200.0f
                                 :                     400.0f;
  }

  else
  {
    switch ( mode )
    {

    case LIS2DH12_LOW_POWER:
      pComponentData->Previous_ODR = ( odr <= 1620.0f ) ? 1620.0f : 5376.0f;
      break;

    case LIS2DH12_NORMAL:
    case LIS2DH12_HIGH_RES:
      pComponentData->Previous_ODR = 1344.0f;
      break;

    default:
      return COMPONENT_ERROR;
    }
  }

  return COMPONENT_OK;
}

/**
 * @}
 */

/** @addtogroup LIS2DH12_Callable_Private_Functions_Ext Callable private functions for extended features
 * @{
 */

/**
 * @brief Get status of FIFO_OVR flag
 * @param handle the device handle
 * @param *status The pointer where the status of FIFO is stored
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
*/
static DrvStatusTypeDef LIS2DH12_FIFO_Get_Overrun_Status( DrvContextTypeDef *handle, uint8_t *status )
{

  if ( LIS2DH12_GetFifoSourceBit( handle, LIS2DH12_FIFO_SRC_OVRUN, status ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Get number of unread FIFO samples
 * @param handle the device handle
 * @param *nSamples Number of unread FIFO samples
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
*/
static DrvStatusTypeDef LIS2DH12_FIFO_Get_Num_Of_Samples( DrvContextTypeDef *handle, uint16_t *nSamples )
{

  uint8_t nSamplesRaw = 0;

  if ( LIS2DH12_GetFifoSourceFSS( handle, &nSamplesRaw ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  *nSamples = (uint16_t)nSamplesRaw;

  return COMPONENT_OK;
}



/**
 * @brief Set FIFO mode
 * @param handle the device handle
 * @param mode FIFO mode
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
*/
static DrvStatusTypeDef LIS2DH12_FIFO_Set_Mode( DrvContextTypeDef *handle, uint8_t mode )
{

  /* Verify that the passed parameter contains one of the valid values */
  switch ( ( LIS2DH12_FifoMode_t )mode )
  {
  case LIS2DH12_FIFO_DISABLE:       /* Disable FIFO */
  case LIS2DH12_FIFO_BYPASS_MODE:   /* Bypass mode */
  case LIS2DH12_FIFO_MODE:          /* FIFO mode */
  case LIS2DH12_FIFO_STREAM_MODE:   /* Stream mode */
  case LIS2DH12_FIFO_TRIGGER_MODE:  /* Stream to FIFO mode */
    break;
  default:
    return COMPONENT_ERROR;
  }

  if ( LIS2DH12_FIFOModeEnable( handle, ( LIS2DH12_FifoMode_t )mode ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}



/**
 * @brief Set FIFO_OVR interrupt on INT1 pin
 * @param handle the device handle
 * @param status FIFO_OVR interrupt on INT1 pin enable/disable
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
*/
static DrvStatusTypeDef LIS2DH12_FIFO_Set_INT1_FIFO_Overrun( DrvContextTypeDef *handle, uint8_t status )
{

  LIS2DH12_IntPinConf_t value = 0;

  /* Read current status of register */
  if ( LIS2DH12_ACC_ReadReg( handle, LIS2DH12_CTRL_REG3, &value, 1 ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  /* Set / reset the desired bit */
  if ( ( LIS2DH12_ACC_State_t )status == LIS2DH12_ENABLE )
  {
    value |= LIS2DH12_INT1_OVERRUN_ENABLE;
  }
  else if ( ( LIS2DH12_ACC_State_t )status == LIS2DH12_DISABLE )
  {
    value &= ~LIS2DH12_INT1_OVERRUN_ENABLE;
  }
  else
  {
    return COMPONENT_ERROR;
  }

  /* Set new register value */
  if ( LIS2DH12_SetInt1Pin( handle, value ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}


/**
 * @brief Get the LIS2DH12 accelerometer sensor super raw axes
 * @param handle the device handle
 * @param pData pointer where the super raw values of the axes are written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_AxesSuperRaw( DrvContextTypeDef *handle, int16_t *pData, ACTIVE_AXIS_t axl_axis )
{  
  uint8_t regValue[2] = {0, 0};
  
  switch( axl_axis )
  {
  case X_AXIS:
    if( LIS2DH12_ACC_ReadReg(handle, LIS2DH12_OUT_X_L, regValue, 2) == MEMS_ERROR)
    {
      return COMPONENT_ERROR;
    }
    break;
  case Y_AXIS:
    if( LIS2DH12_ACC_ReadReg(handle, LIS2DH12_OUT_Y_L, regValue, 2) == MEMS_ERROR)
    {
      return COMPONENT_ERROR;
    }
    break;
  case Z_AXIS:
    if( LIS2DH12_ACC_ReadReg(handle, LIS2DH12_OUT_Z_L, regValue, 2) == MEMS_ERROR)
    {
      return COMPONENT_ERROR;
    }
    break;
  default:
    return COMPONENT_ERROR;    
  }
  
  *pData = ((((int16_t)regValue[1]) << 8) + ((int16_t)regValue[0]));
  
  return COMPONENT_OK;
  
}

/**
 * @brief Get the Operating Mode of the LIS2DH12 sensor
 * @param handle the device handle
 * @param opMode pointer to the value of Operating mode
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_OpMode( DrvContextTypeDef *handle, OP_MODE_t *axl_opMode )
{  
  LIS2DH12_Mode_t opMode;
    
  if ( LIS2DH12_GetMode( (void *)handle, &opMode ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  switch( opMode )
  {
  case LIS2DH12_NORMAL:
    *axl_opMode = NORMAL_MODE;
    break;
  case LIS2DH12_HIGH_RES:
    *axl_opMode = HIGH_RES_MODE;
    break;
  case LIS2DH12_LOW_POWER:
    *axl_opMode = LOW_PWR_MODE;
    break;
  default:
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
 * @brief Set the Operating Mode of the LIS2DH12 sensor
 * @param handle the device handle
 * @param opMode the operating mode to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_OpMode( DrvContextTypeDef *handle, OP_MODE_t axl_opMode )
{  
  LIS2DH12_Mode_t opMode;
  
  switch( axl_opMode )
  {
  case NORMAL_MODE:
    opMode = LIS2DH12_NORMAL;
    break;
  case HIGH_RES_MODE:
    opMode = LIS2DH12_HIGH_RES;
    break;
  case LOW_PWR_MODE:
    opMode = LIS2DH12_LOW_POWER;
    break;
  default:
    return COMPONENT_ERROR;    
  }
  
  if ( LIS2DH12_SetMode( (void *)handle, opMode ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}


/**
 * @brief Get the active axis of the LIS2DH12 sensor
 * @param handle the device handle
 * @param axis pointer to the value of active axis
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Get_Active_Axis( DrvContextTypeDef *handle, ACTIVE_AXIS_t *axl_axis )
{  
  LIS2DH12_AxesEnabled_t axis;
   
  if ( LIS2DH12_GetAxesEnabled( (void *)handle, &axis ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  switch( axis )
  {
  case LIS2DH12_X_ENABLE:
    *axl_axis = X_AXIS;
    break;
  case LIS2DH12_Y_ENABLE:
    *axl_axis = Y_AXIS;
    break;
  case LIS2DH12_Z_ENABLE:
    *axl_axis = Z_AXIS;
    break;
  case (LIS2DH12_X_ENABLE|LIS2DH12_Y_ENABLE|LIS2DH12_Z_ENABLE):
    *axl_axis = ALL_ACTIVE;
    break;
  default:
    return COMPONENT_ERROR;    
  }
  
  return COMPONENT_OK;
}

/**
 * @brief Set the active axis of the LIS2DH12 sensor
 * @param handle the device handle
 * @param axis the active axis to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_Active_Axis( DrvContextTypeDef *handle, ACTIVE_AXIS_t axl_axis )
{  
  LIS2DH12_AxesEnabled_t axis;
  
  switch( axl_axis )
  {
  case X_AXIS:
    axis = LIS2DH12_X_ENABLE;
    break;
  case Y_AXIS:
    axis = LIS2DH12_Y_ENABLE;
    break;
  case Z_AXIS:
    axis = LIS2DH12_Z_ENABLE;
    break;
  case ALL_ACTIVE:
    axis = (LIS2DH12_X_ENABLE|LIS2DH12_Y_ENABLE|LIS2DH12_Z_ENABLE);
    break;
  default:
    return COMPONENT_ERROR;    
  }
  
  if ( LIS2DH12_SetAxesEnabled( (void *)handle, axis ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}


/**
 * @brief Enable the HP Filter of the LIS2DH12 sensor
 * @param handle the device handle
 * @param mode the HP Filter mode to be set
 * @param cutoff the HP Filter cutoff frequency to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Enable_HP_Filter( DrvContextTypeDef *handle )
{
  if ( LIS2DH12_SetHPFMode( (void *)handle, LIS2DH12_HPM_NORMAL_MODE ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  if ( LIS2DH12_SetHPFCutOFF( (void *)handle, LIS2DH12_HPFCF_1 ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  if ( LIS2DH12_SetFilterDataSel( (void *)handle, LIS2DH12_ENABLE ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}


/**
 * @brief Disable the HP Filter of the LIS2DH12 sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Disable_HP_Filter( DrvContextTypeDef *handle )
{      
  if ( LIS2DH12_SetFilterDataSel( (void *)handle, LIS2DH12_DISABLE ) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}


/**
 * @brief Clear DRDY of the LIS2DH12 sensor
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_ClearDRDY( DrvContextTypeDef *handle, ACTIVE_AXIS_t axl_axis )
{ 
  uint8_t regValue[6];
  
  switch( axl_axis )
  {
  case X_AXIS:
    if( LIS2DH12_ACC_ReadReg(handle, LIS2DH12_OUT_X_L, regValue, 2) == MEMS_ERROR)
    {
      return COMPONENT_ERROR;
    }
    break;
  case Y_AXIS:
    if( LIS2DH12_ACC_ReadReg(handle, LIS2DH12_OUT_Y_L, regValue, 2) == MEMS_ERROR)
    {
      return COMPONENT_ERROR;
    }
    break;
  case Z_AXIS:
    if( LIS2DH12_ACC_ReadReg(handle, LIS2DH12_OUT_Z_L, regValue, 2) == MEMS_ERROR)
    {
      return COMPONENT_ERROR;
    }
    break;
  case ALL_ACTIVE:
    if( LIS2DH12_ACC_ReadReg(handle, LIS2DH12_OUT_X_L, regValue, 6) == MEMS_ERROR)
    {
      return COMPONENT_ERROR;
    }
    break;
  default:
    return COMPONENT_ERROR;    
  }
    
  return COMPONENT_OK;
}

  

/**
 * @brief Set DRDY enable/disable of the LIS2DH12 sensor on INT1 
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
static DrvStatusTypeDef LIS2DH12_Set_INT1_DRDY( DrvContextTypeDef *handle, INT1_DRDY_CONFIG_t axl_drdyStatus )
{  
  LIS2DH12_IntPinConf_t pinConf;
  
  switch( axl_drdyStatus )
  {
  case INT1_DRDY_DISABLED:
    pinConf = LIS2DH12_I1_DRDY1_ON_INT1_DISABLE;
    break;
  case INT1_DRDY_ENABLED:
    pinConf = LIS2DH12_I1_DRDY1_ON_INT1_ENABLE;
    break;
  default:
    return COMPONENT_ERROR;    
  }
  
  if ( LIS2DH12_SetInt1Pin((void *)handle, pinConf) == MEMS_ERROR )
  {
    return COMPONENT_ERROR;
  }
      
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
