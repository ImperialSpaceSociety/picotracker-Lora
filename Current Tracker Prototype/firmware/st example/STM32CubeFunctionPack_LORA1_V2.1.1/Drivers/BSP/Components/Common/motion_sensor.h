/**
 ******************************************************************************
 * @file    motion_sensor.h
 * @author  MEMS Software Solutions Team
 * @brief   This header file contains definitions for motion sensors
 *          From motion_sensor.h, STM32CubeExpansion_MEMS1_V5.0.0 (preview release 18/07/18)
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif



/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup COMPONENTS COMPONENTS
 * @{
 */

/** @addtogroup COMMON COMMON
 * @{
 */

/** @addtogroup MOTION_SENSOR MOTION SENSOR
 * @{
 */

/** @addtogroup MOTION_SENSOR_Public_Types MOTION SENSOR Public types
 * @{
 */

/**
 * @brief  MOTION_SENSOR driver structure definition
 */
typedef struct
{
  int32_t (*Init)(void *);
  int32_t (*DeInit)(void *);
  int32_t (*ReadID)(void *, uint8_t *);
  int32_t (*GetCapabilities)(void *, void *);
} MOTION_SENSOR_CommonDrv_t;

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
} MOTION_SENSOR_FuncDrv_t;

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

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* MOTION_SENSOR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
