/**
 ******************************************************************************
 * @file    hts221.h
 * @author  MEMS Software Solutions Team
 * @brief   HTS221 header driver file
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
#ifndef HTS221_H
#define HTS221_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hts221_reg.h"
#include <string.h>

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup Component Component
 * @{
 */

/** @addtogroup HTS221 HTS221
 * @{
 */

/** @defgroup HTS221_Exported_Types HTS221 Exported Types
 * @{
 */

typedef int32_t (*HTS221_Init_Func)(void);
typedef int32_t (*HTS221_DeInit_Func)(void);
typedef int32_t (*HTS221_GetTick_Func)(void);
typedef int32_t (*HTS221_WriteReg_Func)(uint16_t, uint16_t, uint8_t *, uint16_t);
typedef int32_t (*HTS221_ReadReg_Func)(uint16_t, uint16_t, uint8_t *, uint16_t);

typedef struct
{
  HTS221_Init_Func          Init;
  HTS221_DeInit_Func        DeInit;
  uint32_t                  BusType; /*0 means I2C, 1 means SPI-3-Wires */
  uint8_t                   Address;
  HTS221_WriteReg_Func      WriteReg;
  HTS221_ReadReg_Func       ReadReg;
  HTS221_GetTick_Func       GetTick;
} HTS221_IO_t;

typedef struct
{
  float x0;
  float y0;
  float x1;
  float y1;
} lin_t;

typedef struct
{
  HTS221_IO_t        IO;
  hts221_ctx_t       Ctx;
  uint8_t            is_initialized;
  uint8_t            hum_is_enabled;
  uint8_t            temp_is_enabled;
} HTS221_Object_t;

typedef struct
{
  uint8_t Temperature;
  uint8_t Pressure;
  uint8_t Humidity;
  uint8_t LowPower;
  float   HumMaxOdr;
  float   TempMaxOdr;
  float   PressMaxOdr;
} HTS221_Capabilities_t;

typedef struct
{
  int32_t (*Init)(HTS221_Object_t *);
  int32_t (*DeInit)(HTS221_Object_t *);
  int32_t (*ReadID)(HTS221_Object_t *, uint8_t *);
  int32_t (*GetCapabilities)(HTS221_Object_t *, HTS221_Capabilities_t *);
} HTS221_CommonDrv_t;

typedef struct
{
  int32_t (*Enable)(HTS221_Object_t *);
  int32_t (*Disable)(HTS221_Object_t *);
  int32_t (*GetOutputDataRate)(HTS221_Object_t *, float *);
  int32_t (*SetOutputDataRate)(HTS221_Object_t *, float);
  int32_t (*GetHumidity)(HTS221_Object_t *, float *);
} HTS221_HUM_Drv_t;

typedef struct
{
  int32_t (*Enable)(HTS221_Object_t *);
  int32_t (*Disable)(HTS221_Object_t *);
  int32_t (*GetOutputDataRate)(HTS221_Object_t *, float *);
  int32_t (*SetOutputDataRate)(HTS221_Object_t *, float);
  int32_t (*GetTemperature)(HTS221_Object_t *, float *);
} HTS221_TEMP_Drv_t;

/**
 * @}
 */

/** @defgroup HTS221_Exported_Constants HTS221 Exported Constants
 * @{
 */
#define HTS221_I2C_BUS           0U
#define HTS221_SPI_3WIRES_BUS    1U

/** HTS221 error codes  **/
#define HTS221_OK                 0
#define HTS221_ERROR             -1

/**
 * @}
 */

/** @addtogroup HTS221_Exported_Functions HTS221 Exported Functions
 * @{
 */

int32_t HTS221_RegisterBusIO(HTS221_Object_t *pObj, HTS221_IO_t *pIO);
int32_t HTS221_Init(HTS221_Object_t *pObj);
int32_t HTS221_DeInit(HTS221_Object_t *pObj);
int32_t HTS221_ReadID(HTS221_Object_t *pObj, uint8_t *Id);
int32_t HTS221_GetCapabilities(HTS221_Object_t *pObj, HTS221_Capabilities_t *Capabilities);
int32_t HTS221_Get_Init_Status(HTS221_Object_t *pObj, uint8_t *Status);

int32_t HTS221_HUM_Enable(HTS221_Object_t *pObj);
int32_t HTS221_HUM_Disable(HTS221_Object_t *pObj);
int32_t HTS221_HUM_GetOutputDataRate(HTS221_Object_t *pObj, float *Odr);
int32_t HTS221_HUM_SetOutputDataRate(HTS221_Object_t *pObj, float Odr);
int32_t HTS221_HUM_GetHumidity(HTS221_Object_t *pObj, float *Value);
int32_t HTS221_HUM_Get_DRDY_Status(HTS221_Object_t *pObj, uint8_t *Status);

int32_t HTS221_TEMP_Enable(HTS221_Object_t *pObj);
int32_t HTS221_TEMP_Disable(HTS221_Object_t *pObj);
int32_t HTS221_TEMP_GetOutputDataRate(HTS221_Object_t *pObj, float *Odr);
int32_t HTS221_TEMP_SetOutputDataRate(HTS221_Object_t *pObj, float Odr);
int32_t HTS221_TEMP_GetTemperature(HTS221_Object_t *pObj, float *Value);
int32_t HTS221_TEMP_Get_DRDY_Status(HTS221_Object_t *pObj, uint8_t *Status);

int32_t HTS221_Read_Reg(HTS221_Object_t *pObj, uint8_t Reg, uint8_t *Data);
int32_t HTS221_Write_Reg(HTS221_Object_t *pObj, uint8_t Reg, uint8_t Data);

/**
 * @}
 */

/** @addtogroup HTS221_Exported_Variables HTS221 Exported Variables
 * @{
 */

extern const HTS221_CommonDrv_t HTS221_COMMON_Driver;
extern const HTS221_HUM_Drv_t HTS221_HUM_Driver;
extern const HTS221_TEMP_Drv_t HTS221_TEMP_Driver;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
