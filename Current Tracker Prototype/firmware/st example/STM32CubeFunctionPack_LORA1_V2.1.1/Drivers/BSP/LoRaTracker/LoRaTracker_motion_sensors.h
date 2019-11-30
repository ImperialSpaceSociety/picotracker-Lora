/**
 ******************************************************************************
 * @file    LoRaTracker_motion_sensors.h
 * @author  MEMS Software Solutions Team
 * @brief   This file provides a set of functions needed to manage the motion sensors
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LORATRACKER_MOTION_SENSOR_H
#define LORATRACKER_MOTION_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "LoRaTracker_conf.h"
  

  
#ifndef USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0       
#define USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0         1
#endif

#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1)
#include "lis2dw12.h"
#endif
  
//#ifndef USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0
//#define USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0          1
//#endif
//
//#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
//#include "lsm6dsl.h"
//#endif

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup LORATRACKER LORATRACKER
 * @{
 */

/** @addtogroup LORATRACKER_MOTION_SENSOR LORATRACKER MOTION SENSOR
 * @{
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_Exported_Types Exported Types
 * @{
 */

typedef struct
{
  int32_t x;
  int32_t y;
  int32_t z;
} LORA_TRACKER_MOTION_SENSOR_Axes_t;

typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
} LORA_TRACKER_MOTION_SENSOR_AxesRaw_t;

/* Motion Sensor instance Info */
typedef struct
{
  uint8_t  Acc;
  uint8_t  Gyro;
  uint8_t  Magneto;
  uint8_t  LowPower;
  uint32_t GyroMaxFS;
  uint32_t AccMaxFS;
  uint32_t MagMaxFS;
  float    GyroMaxOdr;
  float    AccMaxOdr;
  float    MagMaxOdr;
} LORA_TRACKER_MOTION_SENSOR_Capabilities_t;

typedef struct
{
  uint32_t Functions;
} LORA_TRACKER_MOTION_SENSOR_Ctx_t;

/**
 * @brief  LORA_TRACKER_MOTION_SENSOR driver structure definition
 */
typedef struct
{
  int32_t (*Init)(void *);
  int32_t (*DeInit)(void *);
  int32_t (*ReadID)(void *, uint8_t *);
  int32_t (*GetCapabilities)(void *, void *);
} LORA_TRACKER_MOTION_SENSOR_CommonDrv_t;

typedef struct
{
  int32_t (*Enable)(void *);
  int32_t (*Disable)(void *);
  int32_t (*GetSensitivity)(void *, float *);
  int32_t (*GetOutputDataRate)(void *, float *);
  int32_t (*SetOutputDataRate)(void *, float);
  int32_t (*GetFullScale)(void *, int32_t *);
  int32_t (*SetFullScale)(void *, int32_t);
  int32_t (*GetAxes)(void *, void *);
  int32_t (*GetAxesRaw)(void *, void *);
} LORA_TRACKER_MOTION_SENSOR_FuncDrv_t;


/**
 * @}
 */

/** @defgroup LORATRACKER_MOTION_SENSOR_Exported_Constants Exported Constants
 * @{
 */

#if (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0 == 1) 
#define LORA_TRACKER_LIS2DW12_0 (0)
#endif

//#if (USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0 == 1)
//#define LORA_TRACKER_LSM6DSL_0 (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0)
//#endif



#ifndef MOTION_GYRO
#define MOTION_GYRO             1U
#endif
#ifndef MOTION_ACCELERO
#define MOTION_ACCELERO         2U
#endif
#ifndef MOTION_MAGNETO
#define MOTION_MAGNETO          4U
#endif

#define LORA_TRACKER_MOTION_FUNCTIONS_NBR    3U 
#define LORA_TRACKER_MOTION_INSTANCES_NBR    (USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0) //+ USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0)

#if (LORA_TRACKER_MOTION_INSTANCES_NBR == 0)
#error "No motion sensor instance has been selected" 
#endif

/**
 * @}
 */

/** @addtogroup LORATRACKER_MOTION_SENSOR_Exported_Functions Exported Functions
 * @{
 */

int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Init(uint32_t Instance, uint32_t Functions);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_DeInit(uint32_t Instance);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetCapabilities(uint32_t Instance, LORA_TRACKER_MOTION_SENSOR_Capabilities_t *Capabilities);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_ReadID(uint32_t Instance, uint8_t *Id);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Enable(uint32_t Instance, uint32_t Function);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_Disable(uint32_t Instance, uint32_t Function);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetAxes(uint32_t Instance, uint32_t Function, LORA_TRACKER_MOTION_SENSOR_Axes_t *Axes);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetAxesRaw(uint32_t Instance, uint32_t Function, LORA_TRACKER_MOTION_SENSOR_AxesRaw_t *Axes);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetSensitivity(uint32_t Instance, uint32_t Function, float *Sensitivity);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetOutputDataRate(uint32_t Instance, uint32_t Function, float *Odr);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_SetOutputDataRate(uint32_t Instance, uint32_t Function, float Odr);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_GetFullScale(uint32_t Instance, uint32_t Function, int32_t *Fullscale);
int32_t BSP_LORA_TRACKER_MOTION_SENSOR_SetFullScale(uint32_t Instance, uint32_t Function, int32_t Fullscale);

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

#ifdef __cplusplus
}
#endif

#endif /* LORATRACKER_MOTION_SENSOR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
