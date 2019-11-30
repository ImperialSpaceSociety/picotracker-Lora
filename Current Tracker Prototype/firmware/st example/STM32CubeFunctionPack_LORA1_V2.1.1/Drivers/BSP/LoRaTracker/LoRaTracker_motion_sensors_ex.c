/**
 ******************************************************************************
 * @file    LoRaTracker_motion_sensors_ex.c
 * @author  MEMS Software Solutions Team
 * @brief   This file provides a set of extended functions needed to manage the motion sensors
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "LoRaTracker_motion_sensors_ex.h"

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup LORATRACKER LORATRACKER
 * @{
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_EX LORATRACKER MOTION SENSOR EX
 * @brief   This module provides a set of extended functions needed to manage the motion sensors
 * @{
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_EX_Imported_Variables Imported Variables
 * @{
 */

extern void *MotionCompObj[LORA_TRACKER_MOTION_INSTANCES_NBR];

/**
 * @}
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_EX_Exported_Functions Exported Functions
 * @{
 */

/**
 * @brief  Enable 6D Orientation (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  IntPin the interrupt pin to be used
 * @note   This function sets the LSM6DSL accelerometer ODR to 416Hz and the LSM6DSL accelerometer full scale to 2g
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Enable_6D_Orientation(uint32_t Instance, LORA_TRACKER_MOTION_SENSOR_IntPin_t IntPin)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Enable_6D_Orientation(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif
      
#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Enable_6D_Orientation(MotionCompObj[Instance], (LSM6DSL_SensorIntPin_t)IntPin) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Disable 6D Orientation (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Disable_6D_Orientation(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Disable_6D_Orientation(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Disable_6D_Orientation(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Set the 6D orientation threshold (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  Threshold the threshold to be set
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Set_6D_Orientation_Threshold(uint32_t Instance, uint8_t Threshold)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Set_6D_Orientation_Threshold(MotionCompObj[Instance], Threshold) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Set_6D_Orientation_Threshold(MotionCompObj[Instance], Threshold) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}


/**
 * @brief  Enable the tilt detection (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  IntPin the interrupt pin to be used
 * @note   This function sets the LSM6DSL accelerometer ODR to 26Hz and the LSM6DSL accelerometer full scale to 2g
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Enable_Tilt_Detection(uint32_t Instance, LORA_TRACKER_MOTION_SENSOR_IntPin_t IntPin)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Enable_Tilt_Detection(MotionCompObj[Instance], (LSM6DSL_SensorIntPin_t)IntPin) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Disable the tilt detection (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Disable_Tilt_Detection(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Disable_Tilt_Detection(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Enable the wake up detection (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  IntPin the interrupt pin to be used
 * @note   This function sets the LSM6DSL accelerometer ODR to 416Hz and the LSM6DSL accelerometer full scale to 2g
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Enable_Wake_Up_Detection(uint32_t Instance, LORA_TRACKER_MOTION_SENSOR_IntPin_t IntPin)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Enable_Wake_Up_Detection(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Enable_Wake_Up_Detection(MotionCompObj[Instance], (LSM6DSL_SensorIntPin_t)IntPin) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Disable the wake up detection (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Disable_Wake_Up_Detection(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Disable_Wake_Up_Detection(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Disable_Wake_Up_Detection(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Set the wake up detection threshold (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  Threshold the threshold to be set
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Set_Wake_Up_Threshold(uint32_t Instance, uint8_t Threshold)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Set_Wake_Up_Threshold(MotionCompObj[Instance], Threshold) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Set_Wake_Up_Threshold(MotionCompObj[Instance], Threshold) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Set the wake up detection duration (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  Duration the duration to be set
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Set_Wake_Up_Duration(uint32_t Instance, uint8_t Duration)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Set_Wake_Up_Duration(MotionCompObj[Instance], Duration) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Set_Wake_Up_Duration(MotionCompObj[Instance], Duration) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}


/**
 * @brief  Enable the inactivity detection (available only for LIS2DW12 sensor)
 * @param  Instance the device instance
 * @param  IntPin the interrupt pin to be used
 * @note   This function sets the LIS2DW12 accelerometer ODR to 50Hz and the LIS2DW12 accelerometer full scale to 2g
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Enable_Inactivity_Detection(uint32_t Instance, LORA_TRACKER_MOTION_SENSOR_IntPin_t IntPin)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Enable_Inactivity_Detection(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Disable the inactivity detection (available only for LIS2DW12 sensor)
 * @param  Instance the device instance
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Disable_Inactivity_Detection(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_MOTION_SENSOR_LIS2DW12_0 == 1)
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Disable_Inactivity_Detection(MotionCompObj[Instance]) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}


/**
 * @brief  Set the sleep duration (available only for LIS2DW12 sensor)
 * @param  Instance the device instance
 * @param  Duration the duration to be set
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Set_Sleep_Duration(uint32_t Instance, uint8_t Duration)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Set_Sleep_Duration(MotionCompObj[Instance], Duration) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/*
 * @brief  Enable interrupt latch
 * @param  Instance the device instance
 * @param  Duration the duration to be set
 * @retval BSP status
*/
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Enable_Interrupt_Latch(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_Set_Interrupt_Latch(MotionCompObj[Instance], 1) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}


/*
 * @brief  Interrupt active high
 * @param  Instance the device instance
 * @retval BSP status
*/
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Interrupt_Polarity_High(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_Set_Interrupt_Polarity(MotionCompObj[Instance], 0) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}


/*
 * @brief  Interrupt active low
 * @param  Instance the device instance
 * @retval BSP status
*/
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Interrupt_Polarity_Low(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_Set_Interrupt_Polarity(MotionCompObj[Instance], 1) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}




/*
 * @brief  Interrupt pin mode Push Pull
 * @param  Instance the device instance
 * @retval BSP status
*/
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Interrupt_Pin_Mode_PP(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_Set_Interrupt_PinMode(MotionCompObj[Instance], 0) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}


/*
 * @brief  Interrupt pin mode Open Drain
 * @param  Instance the device instance
 * @retval BSP status
*/
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Interrupt_Pin_Mode_OD(uint32_t Instance)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_Set_Interrupt_PinMode(MotionCompObj[Instance], 1) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}




/**
 * @brief  Get the status of all hardware events (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  Status the pointer to the status of all hardware events
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_Event_Status(uint32_t Instance, LORA_TRACKER_MOTION_SENSOR_Event_Status_t *Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      /* The second cast (void *) is added to bypass Misra R11.3 rule */
      if (LIS2DW12_ACC_Get_Event_Status(MotionCompObj[Instance], (LIS2DW12_Event_Status_t *)(void *)Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      /* The second cast (void *) is added to bypass Misra R11.3 rule */
      if (LSM6DSL_ACC_Get_Event_Status(MotionCompObj[Instance], (LSM6DSL_Event_Status_t *)(void *)Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get the status of data ready bit (available only for LSM6DSL, LSM303AGR sensors)
 * @param  Instance the device instance
 * @param  Function Motion sensor function. Could be:
 *         - MOTION_ACCELERO or MOTION_GYRO for instance LORA_TRACKER_LSM6DSL_0
 *         - MOTION_ACCELERO for instance LORA_TRACKER_LSM303AGR_ACC_0
 *         - MOTION_MAGNETO for instance LORA_TRACKER_LSM303AGR_MAG_0
 * @param  Status the pointer to the status
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_DRDY_Status(uint32_t Instance, uint32_t Function, uint8_t *Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if ((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
      {
        if (LIS2DW12_ACC_Get_DRDY_Status(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      break;
#endif
    
#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if ((Function & MOTION_ACCELERO) == MOTION_ACCELERO)
      {
        if (LSM6DSL_ACC_Get_DRDY_Status(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else if ((Function & MOTION_GYRO) == MOTION_GYRO)
      {
        if (LSM6DSL_GYRO_Get_DRDY_Status(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      if (LSM303AGR_ACC_Get_DRDY_Status(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      if (LSM303AGR_MAG_Get_DRDY_Status(MotionCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get 6D Orientation XL (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  xl the pointer to the 6D orientation XL axis
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_6D_Orientation_XL(uint32_t Instance, uint8_t *xl)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Get_6D_Orientation_XL(MotionCompObj[Instance], xl) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Get_6D_Orientation_XL(MotionCompObj[Instance], xl) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get 6D Orientation XH (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  xh the pointer to the 6D orientation XH axis
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_6D_Orientation_XH(uint32_t Instance, uint8_t *xh)
{
  int32_t ret;

  switch (Instance)
  { 
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Get_6D_Orientation_XH(MotionCompObj[Instance], xh) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Get_6D_Orientation_XH(MotionCompObj[Instance], xh) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get 6D Orientation YL (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  yl the pointer to the 6D orientation YL axis
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_6D_Orientation_YL(uint32_t Instance, uint8_t *yl)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Get_6D_Orientation_YL(MotionCompObj[Instance], yl) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Get_6D_Orientation_YL(MotionCompObj[Instance], yl) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get 6D Orientation YH (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  yh the pointer to the 6D orientation YH axis
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_6D_Orientation_YH(uint32_t Instance, uint8_t *yh)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Get_6D_Orientation_YH(MotionCompObj[Instance], yh) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Get_6D_Orientation_YH(MotionCompObj[Instance], yh) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get 6D Orientation ZL (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  zl the pointer to the 6D orientation ZL axis
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_6D_Orientation_ZL(uint32_t Instance, uint8_t *zl)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Get_6D_Orientation_ZL(MotionCompObj[Instance], zl) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Get_6D_Orientation_ZL(MotionCompObj[Instance], zl) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get 6D Orientation ZH (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  zh the pointer to the 6D orientation ZH axis
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_6D_Orientation_ZH(uint32_t Instance, uint8_t *zh)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_ACC_Get_6D_Orientation_ZH(MotionCompObj[Instance], zh) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Get_6D_Orientation_ZH(MotionCompObj[Instance], zh) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get step count (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  StepCount number of steps
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Get_Step_Count(uint32_t Instance, uint16_t *StepCount)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_ACC_Get_Step_Count(MotionCompObj[Instance], StepCount) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get the register value (available only for LSM6DSL, LSM303AGR sensors)
 * @param  Instance the device instance
 * @param  Reg address to be read
 * @param  Data pointer where the value is written to
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Read_Register(uint32_t Instance, uint8_t Reg, uint8_t *Data)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_Read_Reg(MotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_Read_Reg(MotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      if (LSM303AGR_ACC_Read_Reg(MotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      if (LSM303AGR_MAG_Read_Reg(MotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Set the register value (available only for LSM6DSL, LSM303AGR sensors)
 * @param  Instance the device instance
 * @param  Reg address to be read
 * @param  Data value to be written
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Write_Register(uint32_t Instance, uint8_t Reg, uint8_t Data)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_Write_Reg(MotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_Write_Reg(MotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      if (LSM303AGR_ACC_Write_Reg(MotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      if (LSM303AGR_MAG_Write_Reg(MotionCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get number of unread FIFO samples (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  NumSamples number of unread FIFO samples
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_FIFO_Get_Num_Samples(uint32_t Instance, uint16_t *NumSamples)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_FIFO_Get_Num_Samples(MotionCompObj[Instance], NumSamples) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_FIFO_Get_Num_Samples(MotionCompObj[Instance], NumSamples) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}


/**
 * @brief  Set FIFO mode (available only for LSM6DSL sensor)
 * @param  Instance the device instance
 * @param  Mode FIFO mode
 * @retval BSP status
 */
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_FIFO_Set_Mode(uint32_t Instance, uint8_t Mode)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)    /* LORA_TRACKER CUSTOMIZATION*/
    case LORA_TRACKER_LIS2DW12_0:
      if (LIS2DW12_FIFO_Set_Mode(MotionCompObj[Instance], Mode) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
    case LORA_TRACKER_LSM6DSL_0:
      if (LSM6DSL_FIFO_Set_Mode(MotionCompObj[Instance], Mode) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0 == 1)
    case LORA_TRACKER_LSM303AGR_ACC_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0 == 1)
    case LORA_TRACKER_LSM303AGR_MAG_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
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
