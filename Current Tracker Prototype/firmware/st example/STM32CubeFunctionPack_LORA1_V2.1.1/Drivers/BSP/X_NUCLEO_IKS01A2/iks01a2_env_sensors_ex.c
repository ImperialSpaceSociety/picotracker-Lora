/**
 ******************************************************************************
 * @file    iks01a2_env_sensors_ex.c
 * @author  MEMS Software Solutions Team
 * @brief   This file provides a set of extended functions needed to manage the environmental sensors
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
#include "iks01a2_env_sensors_ex.h"
#include "env_sensor.h"

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup IKS01A2 IKS01A2
 * @{
 */

/** @defgroup IKS01A2_ENV_SENSOR_EX IKS01A2 ENV SENSOR EX
 * @{
 */

/** @defgroup IKS01A2_ENV_SENSOR_EX_Imported_Variables IKS01A2 ENV SENSOR EX Imported Variables
 * @{
 */

extern void *EnvCompObj[IKS01A2_ENV_INSTANCES_NBR];

/**
 * @}
 */

/** @defgroup IKS01A2_ENV_SENSOR_EX_Exported_Functions IKS01A2 ENV SENSOR EX Exported Functions
 * @{
 */

/**
 * @brief  Get the data stored in FIFO (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  *Data Data
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Get_Data(uint32_t Instance, float *Press, float *Temp)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Get_Data(EnvCompObj[Instance], Press, Temp) != BSP_ERROR_NONE)
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
 * @brief  Get FIFO THR status (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  Status the pointer to the status
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Get_Fth_Status(uint32_t Instance, uint8_t *Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Get_FTh_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
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
 * @brief  Get FIFO Full status (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  Status the pointer to the status
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Get_Full_Status(uint32_t Instance, uint8_t *Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Get_Full_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
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
 * @brief  Get the number of unread samples in FIFO (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  *NumSamples Number of unread FIFO samples
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Get_Num_Samples(uint32_t Instance, uint8_t *NumSamples)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Get_Level(EnvCompObj[Instance], NumSamples) != BSP_ERROR_NONE)
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
 * @brief  Get FIFO OVR status (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  Status the pointer to the status
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Get_Ovr_Status(uint32_t Instance, uint8_t *Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Get_Ovr_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
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
 * @brief  Reset FIFO Interrupt (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  Interrupt FIFO interrupt. Could be: FTH, FULL or OVR
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Reset_Interrupt(uint32_t Instance, uint8_t Interrupt)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Reset_Interrupt(EnvCompObj[Instance], Interrupt) != BSP_ERROR_NONE)
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
 * @brief  Set FIFO Interrupt (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  Interrupt FIFO interrupt. Could be: FTH, FULL or OVR
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Set_Interrupt(uint32_t Instance, uint8_t Interrupt)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Set_Interrupt(EnvCompObj[Instance], Interrupt) != BSP_ERROR_NONE)
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
 * @brief  Set FIFO mode  (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  Mode FIFO mode
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Set_Mode(uint32_t Instance, uint8_t Mode)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Set_Mode(EnvCompObj[Instance], Mode) != BSP_ERROR_NONE)
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
 * @brief  Set FIFO watermark  (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  Watermark FIFO data level threshold
 * @param  Status the pointer to the status
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Set_Watermark_Level(uint32_t Instance, uint8_t Watermark)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Set_Watermark_Level(EnvCompObj[Instance], Watermark) != BSP_ERROR_NONE)
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
 * @brief  Enable FIFO usage (available only for LPS22HB sensor)
 * @param  Instance the device instance
 * @param  Interrupt FIFO interrupt
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_FIFO_Usage(uint32_t Instance, uint8_t Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      if (LPS22HB_FIFO_Usage(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_FIFO_Usage(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
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
 * @brief  Get the status of data ready bit (available only for HTS221, LPS22HB sensors)
 * @param  Instance the device instance
 * @param  Function Environmental sensor function. Could be:
 *         - ENV_HUMIDITY or ENV_TEMPERATURE for instance IKS01A2_HTS221_0
 *         - ENV_PRESSURE or ENV_TEMPERATURE for instance IKS01A2_LPS22HB_0
 * @param  Status the pointer to the status
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_Get_DRDY_Status(uint32_t Instance, uint32_t Function, uint8_t *Status)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      if ((Function & ENV_HUMIDITY) == ENV_HUMIDITY)
      {
        if (HTS221_HUM_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else if ((Function & ENV_TEMPERATURE) == ENV_TEMPERATURE)
      {
        if (HTS221_TEMP_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
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

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if ((Function & ENV_PRESSURE) == ENV_PRESSURE)
      {
        if (LPS22HB_PRESS_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
      }
      else if ((Function & ENV_TEMPERATURE) == ENV_TEMPERATURE)
      {
        if (LPS22HB_TEMP_Get_DRDY_Status(EnvCompObj[Instance], Status) != BSP_ERROR_NONE)
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

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  return ret;
}

/**
 * @brief  Get the register value (available only for HTS221, LPS22HB sensors)
 * @param  Instance the device instance
 * @param  Reg address to be read
 * @param  Data pointer where the value is written to
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_Read_Register(uint32_t Instance, uint8_t Reg, uint8_t *Data)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      if (HTS221_Read_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_Read_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
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
 * @brief  Set the register value (available only for HTS221, LPS22HB sensors)
 * @param  Instance the device instance
 * @param  Reg address to be read
 * @param  Data value to be written
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_Write_Register(uint32_t Instance, uint8_t Reg, uint8_t Data)
{
  int32_t ret;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      if (HTS221_Write_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_Write_Reg(EnvCompObj[Instance], Reg, Data) != BSP_ERROR_NONE)
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
