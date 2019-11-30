/**
 ******************************************************************************
 * @file    lis2dw12.h
 * @author  MEMS Software Solutions Team
 * @brief   LIS2DW12 header driver file
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
#ifndef LIS2DW12_H
#define LIS2DW12_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lis2dw12_reg.h"
#include <string.h>

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup Component Component
 * @{
 */

/** @addtogroup LIS2DW12 LIS2DW12
 * @{
 */

/** @defgroup LIS2DW12_Exported_Types LIS2DW12 Exported Types
 * @{
 */

typedef int32_t (*LIS2DW12_Init_Func)(void);
typedef int32_t (*LIS2DW12_DeInit_Func)(void);
typedef int32_t (*LIS2DW12_GetTick_Func)(void);
typedef int32_t (*LIS2DW12_WriteReg_Func)(uint16_t, uint16_t, uint8_t *, uint16_t);
typedef int32_t (*LIS2DW12_ReadReg_Func)(uint16_t, uint16_t, uint8_t *, uint16_t);

typedef enum
{
  LIS2DW12_INT1_PIN,
  LIS2DW12_INT2_PIN,
} LIS2DW12_SensorIntPin_t;

typedef struct
{
  LIS2DW12_Init_Func         Init;
  LIS2DW12_DeInit_Func       DeInit;
  uint32_t                   BusType; /*0 means I2C, 1 means SPI 4-Wires, 2 means SPI-3-Wires */
  uint8_t                    Address;
  LIS2DW12_WriteReg_Func     WriteReg;
  LIS2DW12_ReadReg_Func      ReadReg;
  LIS2DW12_GetTick_Func      GetTick;
} LIS2DW12_IO_t;


typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
} LIS2DW12_AxesRaw_t;

typedef struct
{
  int32_t x;
  int32_t y;
  int32_t z;
} LIS2DW12_Axes_t;

typedef struct
{
  unsigned int FreeFallStatus : 1;
  unsigned int TapStatus : 1;
  unsigned int DoubleTapStatus : 1;
  unsigned int WakeUpStatus : 1;
  unsigned int StepStatus : 1;
  unsigned int TiltStatus : 1;
  unsigned int D6DOrientationStatus : 1;
  unsigned int SleepStatus : 1;
} LIS2DW12_Event_Status_t;

typedef struct
{
  LIS2DW12_IO_t       IO;
  lis2dw12_ctx_t      Ctx;
  uint8_t             is_initialized;
  uint8_t             acc_is_enabled;
  float               acc_odr;
} LIS2DW12_Object_t;

typedef struct
{
  uint8_t   Acc;
  uint8_t   Gyro;
  uint8_t   Magneto;
  uint8_t   LowPower;
  uint32_t  GyroMaxFS;
  uint32_t  AccMaxFS;
  uint32_t  MagMaxFS;
  float     GyroMaxOdr;
  float     AccMaxOdr;
  float     MagMaxOdr;
} LIS2DW12_Capabilities_t;

typedef struct
{
  int32_t (*Init)(LIS2DW12_Object_t *);
  int32_t (*DeInit)(LIS2DW12_Object_t *);
  int32_t (*ReadID)(LIS2DW12_Object_t *, uint8_t *);
  int32_t (*GetCapabilities)(LIS2DW12_Object_t *, LIS2DW12_Capabilities_t *);
} LIS2DW12_CommonDrv_t;

typedef struct
{
  int32_t (*Enable)(LIS2DW12_Object_t *);
  int32_t (*Disable)(LIS2DW12_Object_t *);
  int32_t (*GetSensitivity)(LIS2DW12_Object_t *, float *);
  int32_t (*GetOutputDataRate)(LIS2DW12_Object_t *, float *);
  int32_t (*SetOutputDataRate)(LIS2DW12_Object_t *, float);
  int32_t (*GetFullScale)(LIS2DW12_Object_t *, int32_t *);
  int32_t (*SetFullScale)(LIS2DW12_Object_t *, int32_t);
  int32_t (*GetAxes)(LIS2DW12_Object_t *, LIS2DW12_Axes_t *);
  int32_t (*GetAxesRaw)(LIS2DW12_Object_t *, LIS2DW12_AxesRaw_t *);
} LIS2DW12_ACC_Drv_t;

/**
 * @}
 */

/** @defgroup LIS2DW12_Exported_Constants LIS2DW12 Exported Constants
 * @{
 */

#define LIS2DW12_OK                       0
#define LIS2DW12_ERROR                   -1

#define LIS2DW12_I2C_BUS                 0U
#define LIS2DW12_SPI_4WIRES_BUS          1U
#define LIS2DW12_SPI_3WIRES_BUS          2U

#define LIS2DW12_ACC_SENSITIVITY_FOR_FS_2G_LOPOW1_MODE   0.976f  /**< Sensitivity value for 2g full scale, Low-power1 mode [mg/LSB] */
#define LIS2DW12_ACC_SENSITIVITY_FOR_FS_2G_OTHER_MODES   0.244f  /**< Sensitivity value for 2g full scale, all other modes except Low-power1 [mg/LSB] */

#define LIS2DW12_ACC_SENSITIVITY_FOR_FS_4G_LOPOW1_MODE   1.952f  /**< Sensitivity value for 4g full scale, Low-power1 mode [mg/LSB] */
#define LIS2DW12_ACC_SENSITIVITY_FOR_FS_4G_OTHER_MODES   0.488f  /**< Sensitivity value for 4g full scale, all other modes except Low-power1 [mg/LSB] */

#define LIS2DW12_ACC_SENSITIVITY_FOR_FS_8G_LOPOW1_MODE   3.904f  /**< Sensitivity value for 8g full scale, Low-power1 mode [mg/LSB] */
#define LIS2DW12_ACC_SENSITIVITY_FOR_FS_8G_OTHER_MODES   0.976f  /**< Sensitivity value for 8g full scale, all other modes except Low-power1 [mg/LSB] */

#define LIS2DW12_ACC_SENSITIVITY_FOR_FS_16G_LOPOW1_MODE  7.808f  /**< Sensitivity value for 16g full scale, Low-power1 mode [mg/LSB] */
#define LIS2DW12_ACC_SENSITIVITY_FOR_FS_16G_OTHER_MODES  1.952f  /**< Sensitivity value for 16g full scale, all other modes except Low-power1 [mg/LSB] */

/**
 * @}
 */

/** @addtogroup LIS2DW12_Exported_Functions LIS2DW12 Exported Functions
 * @{
 */

int32_t LIS2DW12_RegisterBusIO(LIS2DW12_Object_t *pObj, LIS2DW12_IO_t *pIO);
int32_t LIS2DW12_Init(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_DeInit(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ReadID(LIS2DW12_Object_t *pObj, uint8_t *Id);
int32_t LIS2DW12_GetCapabilities(LIS2DW12_Object_t *pObj, LIS2DW12_Capabilities_t *Capabilities);

int32_t LIS2DW12_ACC_Enable(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ACC_Disable(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ACC_GetSensitivity(LIS2DW12_Object_t *pObj, float *Sensitivity);
int32_t LIS2DW12_ACC_GetOutputDataRate(LIS2DW12_Object_t *pObj, float *Odr);
int32_t LIS2DW12_ACC_SetOutputDataRate(LIS2DW12_Object_t *pObj, float Odr);
int32_t LIS2DW12_ACC_GetFullScale(LIS2DW12_Object_t *pObj, int32_t *FullScale);
int32_t LIS2DW12_ACC_SetFullScale(LIS2DW12_Object_t *pObj, int32_t FullScale);
int32_t LIS2DW12_ACC_GetAxesRaw(LIS2DW12_Object_t *pObj, LIS2DW12_AxesRaw_t *Value);
int32_t LIS2DW12_ACC_GetAxes(LIS2DW12_Object_t *pObj, LIS2DW12_Axes_t *Acceleration);

int32_t LIS2DW12_Read_Reg(LIS2DW12_Object_t *pObj, uint8_t reg, uint8_t *Data);
int32_t LIS2DW12_Write_Reg(LIS2DW12_Object_t *pObj, uint8_t reg, uint8_t Data);
int32_t LIS2DW12_Set_Interrupt_Polarity(LIS2DW12_Object_t *pObj, uint8_t Status);
int32_t LIS2DW12_Set_Interrupt_Latch(LIS2DW12_Object_t *pObj, uint8_t Status);
int32_t LIS2DW12_Set_Interrupt_PinMode(LIS2DW12_Object_t *pObj, uint8_t Mode);

int32_t LIS2DW12_ACC_Enable_Wake_Up_Detection(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ACC_Disable_Wake_Up_Detection(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ACC_Set_Wake_Up_Threshold(LIS2DW12_Object_t *pObj, uint8_t Threshold);
int32_t LIS2DW12_ACC_Set_Wake_Up_Duration(LIS2DW12_Object_t *pObj, uint8_t Duration);

int32_t LIS2DW12_ACC_Enable_Inactivity_Detection(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ACC_Disable_Inactivity_Detection(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ACC_Set_Sleep_Duration(LIS2DW12_Object_t *pObj, uint8_t Duration);

int32_t LIS2DW12_ACC_Enable_6D_Orientation(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ACC_Disable_6D_Orientation(LIS2DW12_Object_t *pObj);
int32_t LIS2DW12_ACC_Set_6D_Orientation_Threshold(LIS2DW12_Object_t *pObj, uint8_t Threshold);
int32_t LIS2DW12_ACC_Get_6D_Orientation_XL(LIS2DW12_Object_t *pObj, uint8_t *XLow);
int32_t LIS2DW12_ACC_Get_6D_Orientation_XH(LIS2DW12_Object_t *pObj, uint8_t *XHigh);
int32_t LIS2DW12_ACC_Get_6D_Orientation_YL(LIS2DW12_Object_t *pObj, uint8_t *YLow);
int32_t LIS2DW12_ACC_Get_6D_Orientation_YH(LIS2DW12_Object_t *pObj, uint8_t *YHigh);
int32_t LIS2DW12_ACC_Get_6D_Orientation_ZL(LIS2DW12_Object_t *pObj, uint8_t *ZLow);
int32_t LIS2DW12_ACC_Get_6D_Orientation_ZH(LIS2DW12_Object_t *pObj, uint8_t *ZHigh);

int32_t LIS2DW12_ACC_Get_Event_Status(LIS2DW12_Object_t *pObj, LIS2DW12_Event_Status_t *Status);
int32_t LIS2DW12_ACC_Get_DRDY_Status(LIS2DW12_Object_t *pObj, uint8_t *Status);
int32_t LIS2DW12_ACC_Get_Init_Status(LIS2DW12_Object_t *pObj, uint8_t *Status);

int32_t LIS2DW12_FIFO_Get_Num_Samples(LIS2DW12_Object_t *pObj, uint16_t *NumSamples);
int32_t LIS2DW12_FIFO_Set_Mode(LIS2DW12_Object_t *pObj, uint8_t Mode);

/**
 * @}
 */

/** @addtogroup LIS2DW12_Exported_Variables LIS2DW12 Exported Variables
 * @{
 */

extern const LIS2DW12_CommonDrv_t LIS2DW12_COMMON_Driver;
extern const LIS2DW12_ACC_Drv_t LIS2DW12_ACC_Driver;

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
