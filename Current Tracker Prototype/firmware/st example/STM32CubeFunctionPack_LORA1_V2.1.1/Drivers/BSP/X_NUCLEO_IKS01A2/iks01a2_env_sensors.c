/**
 ******************************************************************************
 * @file    iks01a2_env_sensors.c
 * @author  MEMS Software Solutions Team
 * @brief   This file provides a set of functions needed to manage the environmental sensors
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
#include "iks01a2_env_sensors.h"
#include "env_sensor.h"

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup IKS01A2 IKS01A2
 * @{
 */

/** @defgroup IKS01A2_ENV_SENSORS IKS01A2 ENV SENSORS
 * @{
 */

/** @defgroup IKS01A2_ENV_SENSORS_Exported_Variables IKS01A2 ENV SENSORS Exported Variables
 * @{
 */

extern void *EnvCompObj[IKS01A2_ENV_INSTANCES_NBR]; /* This "redundant" line is here to fulfil MISRA C-2012 rule 8.4 */
void *EnvCompObj[IKS01A2_ENV_INSTANCES_NBR];

/**
 * @}
 */

/** @defgroup IKS01A2_ENV_SENSORS_Private_Variables IKS01A2 ENV SENSORS Private Variables
 * @{
 */

/* We define a jump table in order to get the correct index from the desired function. */
/* This table should have a size equal to the maximum value of a function plus 1.      */
static uint32_t FunctionIndex[5] = {0, 0, 1, 1, 2};
static ENV_SENSOR_FuncDrv_t *EnvFuncDrv[IKS01A2_ENV_INSTANCES_NBR][IKS01A2_ENV_FUNCTIONS_NBR];
static ENV_SENSOR_CommonDrv_t *EnvDrv[IKS01A2_ENV_INSTANCES_NBR];
static IKS01A2_ENV_SENSOR_Ctx_t EnvCtx[IKS01A2_ENV_INSTANCES_NBR];

/**
 * @}
 */

/** @defgroup IKS01A2_ENV_SENSORS_Private_Function_Prototypes IKS01A2 ENV SENSORS Private Function Prototypes
 * @{
 */

#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
static int32_t HTS221_0_Probe(uint32_t Functions);
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
static int32_t LPS22HB_0_Probe(uint32_t Functions);
#endif

/**
 * @}
 */

/** @defgroup IKS01A2_ENV_SENSORS_Exported_Functions IKS01A2 ENV SENSOR Exported Functions
 * @{
 */

/**
 * @brief  Initializes the environmental sensor
 * @param  Instance environmental sensor instance to be used
 * @param  Functions Environmental sensor functions. Could be :
 *         - ENV_TEMPERATURE and/or ENV_HUMIDITY for instance 0
 *         - ENV_TEMPERATURE and/or ENV_PRESSURE for instance 1
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_Init(uint32_t Instance, uint32_t Functions)
{
  int32_t ret = BSP_ERROR_NONE;
  uint32_t function = ENV_TEMPERATURE;
  uint32_t i;
  uint32_t component_functions = 0;
  IKS01A2_ENV_SENSOR_Capabilities_t cap;

  switch (Instance)
  {
#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
    case IKS01A2_HTS221_0:
      if (HTS221_0_Probe(Functions) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_NO_INIT;
      }
      if (EnvDrv[Instance]->GetCapabilities(EnvCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_UNKNOWN_COMPONENT;
      }
      if (cap.Temperature == 1U)
      {
        component_functions |= ENV_TEMPERATURE;
      }
      if (cap.Humidity == 1U)
      {
        component_functions |= ENV_HUMIDITY;
      }
      if (cap.Pressure == 1U)
      {
        component_functions |= ENV_PRESSURE;
      }
      break;
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
    case IKS01A2_LPS22HB_0:
      if (LPS22HB_0_Probe(Functions) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_NO_INIT;
      }
      if (EnvDrv[Instance]->GetCapabilities(EnvCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_UNKNOWN_COMPONENT;
      }
      if (cap.Temperature == 1U)
      {
        component_functions |= ENV_TEMPERATURE;
      }
      if (cap.Humidity == 1U)
      {
        component_functions |= ENV_HUMIDITY;
      }
      if (cap.Pressure == 1U)
      {
        component_functions |= ENV_PRESSURE;
      }
      break;
#endif

    default:
      ret = BSP_ERROR_WRONG_PARAM;
      break;
  }

  if (ret != BSP_ERROR_NONE)
  {
    return ret;
  }

  for (i = 0; i < IKS01A2_ENV_FUNCTIONS_NBR; i++)
  {
    if (((Functions & function) == function) && ((component_functions & function) == function))
    {
      if (EnvFuncDrv[Instance][FunctionIndex[function]]->Enable(EnvCompObj[Instance]) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_COMPONENT_FAILURE;
      }
    }
    function = function << 1;
  }

  return ret;
}

/**
 * @brief  Deinitialize environmental sensor sensor
 * @param  Instance environmental sensor instance to be used
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_DeInit(uint32_t Instance)
{
  int32_t ret;

  if (Instance >= IKS01A2_ENV_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (EnvDrv[Instance]->DeInit(EnvCompObj[Instance]) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Get environmental sensor instance capabilities
 * @param  Instance Environmental sensor instance
 * @param  Capabilities pointer to Environmental sensor capabilities
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_GetCapabilities(uint32_t Instance, IKS01A2_ENV_SENSOR_Capabilities_t *Capabilities)
{
  int32_t ret;

  if (Instance >= IKS01A2_ENV_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (EnvDrv[Instance]->GetCapabilities(EnvCompObj[Instance], Capabilities) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Get WHOAMI value
 * @param  Instance environmental sensor instance to be used
 * @param  Id WHOAMI value
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_ReadID(uint32_t Instance, uint8_t *Id)
{
  int32_t ret;

  if (Instance >= IKS01A2_ENV_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (EnvDrv[Instance]->ReadID(EnvCompObj[Instance], Id) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Enable environmental sensor sensor
 * @param  Instance environmental sensor instance to be used
 * @param  Function Environmental sensor function. Could be :
 *         - ENV_TEMPERATURE or ENV_HUMIDITY for instance 0
 *         - ENV_TEMPERATURE or ENV_PRESSURE for instance 1
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_Enable(uint32_t Instance, uint32_t Function)
{
  int32_t ret;

  if (Instance >= IKS01A2_ENV_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((EnvCtx[Instance].Functions & Function) == Function)
    {
      if (EnvFuncDrv[Instance][FunctionIndex[Function]]->Enable(EnvCompObj[Instance]) != BSP_ERROR_NONE)
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
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
 * @brief  Disable environmental sensor sensor
 * @param  Instance environmental sensor instance to be used
 * @param  Function Environmental sensor function. Could be :
 *         - ENV_TEMPERATURE or ENV_HUMIDITY for instance 0
 *         - ENV_TEMPERATURE or ENV_PRESSURE for instance 1
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_Disable(uint32_t Instance, uint32_t Function)
{
  int32_t ret;

  if (Instance >= IKS01A2_ENV_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((EnvCtx[Instance].Functions & Function) == Function)
    {
      if (EnvFuncDrv[Instance][FunctionIndex[Function]]->Disable(EnvCompObj[Instance]) != BSP_ERROR_NONE)
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
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
 * @brief  Get environmental sensor Output Data Rate
 * @param  Instance environmental sensor instance to be used
 * @param  Function Environmental sensor function. Could be :
 *         - ENV_TEMPERATURE or ENV_HUMIDITY for instance 0
 *         - ENV_TEMPERATURE or ENV_PRESSURE for instance 1
 * @param  Odr pointer to Output Data Rate read value
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_GetOutputDataRate(uint32_t Instance, uint32_t Function, float *Odr)
{
  int32_t ret;

  if (Instance >= IKS01A2_ENV_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((EnvCtx[Instance].Functions & Function) == Function)
    {
      if (EnvFuncDrv[Instance][FunctionIndex[Function]]->GetOutputDataRate(EnvCompObj[Instance], Odr) != BSP_ERROR_NONE)
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
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
 * @brief  Set environmental sensor Output Data Rate
 * @param  Instance environmental sensor instance to be used
 * @param  Function Environmental sensor function. Could be :
 *         - ENV_TEMPERATURE or ENV_HUMIDITY for instance 0
 *         - ENV_TEMPERATURE or ENV_PRESSURE for instance 1
 * @param  Odr Output Data Rate value to be set
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_SetOutputDataRate(uint32_t Instance, uint32_t Function, float Odr)
{
  int32_t ret;

  if (Instance >= IKS01A2_ENV_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((EnvCtx[Instance].Functions & Function) == Function)
    {
      if (EnvFuncDrv[Instance][FunctionIndex[Function]]->SetOutputDataRate(EnvCompObj[Instance], Odr) != BSP_ERROR_NONE)
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
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
 * @brief  Get environmental sensor value
 * @param  Instance environmental sensor instance to be used
 * @param  Function Environmental sensor function. Could be :
 *         - ENV_TEMPERATURE or ENV_HUMIDITY for instance 0
 *         - ENV_TEMPERATURE or ENV_PRESSURE for instance 1
 * @param  Value pointer to environmental sensor value
 * @retval BSP status
 */
int32_t IKS01A2_ENV_SENSOR_GetValue(uint32_t Instance, uint32_t Function, float *Value)
{
  int32_t ret;

  if (Instance >= IKS01A2_ENV_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((EnvCtx[Instance].Functions & Function) == Function)
    {
      if (EnvFuncDrv[Instance][FunctionIndex[Function]]->GetValue(EnvCompObj[Instance], Value) != BSP_ERROR_NONE)
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
      ret = BSP_ERROR_WRONG_PARAM;
    }
  }

  return ret;
}

/**
 * @}
 */

/** @defgroup IKS01A2_ENV_SENSORS_Private_Functions IKS01A2 ENV SENSORS Private Functions
 * @{
 */

#if (USE_IKS01A2_ENV_SENSOR_HTS221_0 == 1)
/**
 * @brief  Register Bus IOs for instance 0 if HTS221 ID is OK
 * @param  Functions Environmental sensor functions. Could be :
 *         - ENV_TEMPERATURE and/or ENV_HUMIDITY
 * @retval BSP status
 */
static int32_t HTS221_0_Probe(uint32_t Functions)
{
  HTS221_IO_t            io_ctx;
  uint8_t                id;
  int32_t                ret = BSP_ERROR_NONE;
  static HTS221_Object_t hts221_obj_0;
  HTS221_Capabilities_t  cap;

  /* Configure the environmental sensor driver */
  io_ctx.BusType     = HTS221_I2C_BUS; /* I2C */
  io_ctx.Address     = HTS221_I2C_ADDRESS;
  io_ctx.Init        = IKS01A2_I2C_Init;
  io_ctx.DeInit      = IKS01A2_I2C_DeInit;
  io_ctx.ReadReg     = IKS01A2_I2C_ReadReg;
  io_ctx.WriteReg    = IKS01A2_I2C_WriteReg;
  io_ctx.GetTick     = IKS01A2_GetTick;

  if (HTS221_RegisterBusIO(&hts221_obj_0, &io_ctx) != HTS221_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (HTS221_ReadID(&hts221_obj_0, &id) != HTS221_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (id != HTS221_ID)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    (void)HTS221_GetCapabilities(&hts221_obj_0, &cap);
    EnvCtx[IKS01A2_HTS221_0].Functions = ((uint32_t)cap.Temperature) | ((uint32_t)cap.Pressure << 1) | ((
                                           uint32_t)cap.Humidity << 2);

    EnvCompObj[IKS01A2_HTS221_0] = &hts221_obj_0;
    /* The second cast (void *) is added to bypass Misra R11.3 rule */
    EnvDrv[IKS01A2_HTS221_0] = (ENV_SENSOR_CommonDrv_t *)(void *)&HTS221_COMMON_Driver;

    if (((Functions & ENV_TEMPERATURE) == ENV_TEMPERATURE) && (cap.Temperature == 1U))
    {
      /* The second cast (void *) is added to bypass Misra R11.3 rule */
      EnvFuncDrv[IKS01A2_HTS221_0][FunctionIndex[ENV_TEMPERATURE]] = (ENV_SENSOR_FuncDrv_t *)(void *)&HTS221_TEMP_Driver;

      if (EnvDrv[IKS01A2_HTS221_0]->Init(EnvCompObj[IKS01A2_HTS221_0]) != HTS221_OK)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    if (((Functions & ENV_HUMIDITY) == ENV_HUMIDITY) && (cap.Humidity == 1U))
    {
      /* The second cast (void *) is added to bypass Misra R11.3 rule */
      EnvFuncDrv[IKS01A2_HTS221_0][FunctionIndex[ENV_HUMIDITY]] = (ENV_SENSOR_FuncDrv_t *)(void *)&HTS221_HUM_Driver;

      if (EnvDrv[IKS01A2_HTS221_0]->Init(EnvCompObj[IKS01A2_HTS221_0]) != HTS221_OK)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
  }

  return ret;
}
#endif

#if (USE_IKS01A2_ENV_SENSOR_LPS22HB_0 == 1)
/**
 * @brief  Register Bus IOs for instance 1 if LPS22HB ID is OK
 * @param  Functions Environmental sensor functions. Could be :
 *         - ENV_TEMPERATURE and/or ENV_PRESSURE
 * @retval BSP status
 */
static int32_t LPS22HB_0_Probe(uint32_t Functions)
{
  LPS22HB_IO_t            io_ctx;
  uint8_t                 id;
  int32_t                 ret = BSP_ERROR_NONE;
  static LPS22HB_Object_t lps22hb_obj_0;
  LPS22HB_Capabilities_t  cap;

  /* Configure the pressure driver */
  io_ctx.BusType     = LPS22HB_I2C_BUS; /* I2C */
  io_ctx.Address     = LPS22HB_I2C_ADD_H;
  io_ctx.Init        = IKS01A2_I2C_Init;
  io_ctx.DeInit      = IKS01A2_I2C_DeInit;
  io_ctx.ReadReg     = IKS01A2_I2C_ReadReg;
  io_ctx.WriteReg    = IKS01A2_I2C_WriteReg;
  io_ctx.GetTick     = IKS01A2_GetTick;

  if (LPS22HB_RegisterBusIO(&lps22hb_obj_0, &io_ctx) != LPS22HB_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (LPS22HB_ReadID(&lps22hb_obj_0, &id) != LPS22HB_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (id != LPS22HB_ID)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    (void)LPS22HB_GetCapabilities(&lps22hb_obj_0, &cap);

    EnvCtx[IKS01A2_LPS22HB_0].Functions = ((uint32_t)cap.Temperature) | ((uint32_t)cap.Pressure << 1) | ((
                                            uint32_t)cap.Humidity << 2);

    EnvCompObj[IKS01A2_LPS22HB_0] = &lps22hb_obj_0;
    /* The second cast (void *) is added to bypass Misra R11.3 rule */
    EnvDrv[IKS01A2_LPS22HB_0] = (ENV_SENSOR_CommonDrv_t *)(void *)&LPS22HB_COMMON_Driver;

    if (((Functions & ENV_TEMPERATURE) == ENV_TEMPERATURE) && (cap.Temperature == 1U))
    {
      /* The second cast (void *) is added to bypass Misra R11.3 rule */
      EnvFuncDrv[IKS01A2_LPS22HB_0][FunctionIndex[ENV_TEMPERATURE]] = (ENV_SENSOR_FuncDrv_t *)(void *)&LPS22HB_TEMP_Driver;

      if (EnvDrv[IKS01A2_LPS22HB_0]->Init(EnvCompObj[IKS01A2_LPS22HB_0]) != LPS22HB_OK)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
    if (((Functions & ENV_PRESSURE) == ENV_PRESSURE) && (cap.Pressure == 1U))
    {
      /* The second cast (void *) is added to bypass Misra R11.3 rule */
      EnvFuncDrv[IKS01A2_LPS22HB_0][FunctionIndex[ENV_PRESSURE]] = (ENV_SENSOR_FuncDrv_t *)(void *)&LPS22HB_PRESS_Driver;

      if (EnvDrv[IKS01A2_LPS22HB_0]->Init(EnvCompObj[IKS01A2_LPS22HB_0]) != LPS22HB_OK)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
  }
  return ret;
}
#endif

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
