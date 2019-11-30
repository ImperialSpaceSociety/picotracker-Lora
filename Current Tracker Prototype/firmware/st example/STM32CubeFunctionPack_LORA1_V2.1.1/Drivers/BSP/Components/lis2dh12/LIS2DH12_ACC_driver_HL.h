/**
 ******************************************************************************
 * @file    LIS2DH12_ACC_driver_HL.h
 * @author  MEMS Application Team
 * @version V4.2.0
 * @date    01-February-2018
 * @brief   This file contains definitions for the LIS2DH12_ACC_driver_HL.c firmware driver
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
#ifndef __LIS2DH12_ACC_DRIVER_HL_H
#define __LIS2DH12_ACC_DRIVER_HL_H

#ifdef __cplusplus
extern "C" {
#endif



/* Includes ------------------------------------------------------------------*/

#include "accelerometer.h"

/* Include accelero sensor component drivers. */
#include "LIS2DH12_ACC_driver.h"



/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup COMPONENTS COMPONENTS
 * @{
 */

/** @addtogroup LIS2DH12 LIS2DH12
 * @{
 */

/** @addtogroup LIS2DH12_Public_Constants Public constants
 * @{
 */

/** @addtogroup LIS2DH12_ACC_SENSITIVITY Accelero sensitivity values based on selected full scale and power mode
 * @{
 */

#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_2G_NORMAL     4  /**< Sensitivity value for 2g full scale, Normal mode [mg/LSB] */
#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_2G_HI_RES     1  /**< Sensitivity value for 2g full scale, High-resolution mode [mg/LSB] */
#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_2G_LO_POW    16  /**< Sensitivity value for 2g full scale, Low-power [mg/LSB] */

#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_4G_NORMAL     8  /**< Sensitivity value for 4g full scale, Normal mode [mg/LSB] */
#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_4G_HI_RES     2  /**< Sensitivity value for 4g full scale, High-resolution mode [mg/LSB] */
#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_4G_LO_POW    32  /**< Sensitivity value for 4g full scale, Low-power [mg/LSB] */

#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_8G_NORMAL    16  /**< Sensitivity value for 8g full scale, Normal mode [mg/LSB] */
#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_8G_HI_RES     4  /**< Sensitivity value for 8g full scale, High-resolution mode [mg/LSB] */
#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_8G_LO_POW    64  /**< Sensitivity value for 8g full scale, Low-power [mg/LSB] */

#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_16G_NORMAL   48  /**< Sensitivity value for 16g full scale, Normal mode [mg/LSB] */
#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_16G_HI_RES   12  /**< Sensitivity value for 16g full scale, High-resolution mode [mg/LSB] */
#define LIS2DH12_ACC_SENSITIVITY_FOR_FS_16G_LO_POW  192  /**< Sensitivity value for 16g full scale, Low-power [mg/LSB] */

/**
 * @}
 */

/** @addtogroup LIS2DH12_ACT_THRESHOLD Sleep-to-wake, return-to-sleep activation threshold in low-power mode
 * @{
 */

#define LIS2DH12_ACT_THRESHOLD_LOW       0x01  /**< Lowest  value of threshold */
#define LIS2DH12_ACT_THRESHOLD_MID_LOW   0x0F
#define LIS2DH12_ACT_THRESHOLD_MID       0x1F
#define LIS2DH12_ACT_THRESHOLD_MID_HIGH  0x2F
#define LIS2DH12_ACT_THRESHOLD_HIGH      0x3F  /**< Highest value of threshold */

/**
 * @}
 */

/** @addtogroup LIS2DH12_ACT_DURATION Sleep-to-wake, return-to-sleep duration
 * @{
 */

#define LIS2DH12_ACT_DURATION_LOW       0x01  /**< Lowest  value of threshold */
#define LIS2DH12_ACT_DURATION_MID_LOW   0x0F
#define LIS2DH12_ACT_DURATION_MID       0x1F
#define LIS2DH12_ACT_DURATION_MID_HIGH  0x2F
#define LIS2DH12_ACT_DURATION_HIGH      0x3F  /**< Highest value of threshold */

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup LIS2DH12_Public_Types LIS2DH12 Public Types
 * @{
 */

/**
 * @brief LIS2DH12 accelero extended features driver internal structure definition
 */
typedef struct
{
  DrvStatusTypeDef ( *FIFO_Get_Overrun_Status    ) ( DrvContextTypeDef*, uint8_t* );
  DrvStatusTypeDef ( *FIFO_Get_Num_Of_Samples    ) ( DrvContextTypeDef*, uint16_t* );
  DrvStatusTypeDef ( *FIFO_Set_Mode              ) ( DrvContextTypeDef*, uint8_t );
  DrvStatusTypeDef ( *FIFO_Set_INT1_FIFO_Overrun ) ( DrvContextTypeDef*, uint8_t );
  DrvStatusTypeDef ( *Get_AxesSuperRaw           ) ( DrvContextTypeDef*, int16_t *, ACTIVE_AXIS_t );
  DrvStatusTypeDef ( *Get_OpMode                 ) ( DrvContextTypeDef*, OP_MODE_t * );
  DrvStatusTypeDef ( *Set_OpMode                 ) ( DrvContextTypeDef*, OP_MODE_t );
  DrvStatusTypeDef ( *Get_Active_Axis            ) ( DrvContextTypeDef*, ACTIVE_AXIS_t * );
  DrvStatusTypeDef ( *Set_Active_Axis            ) ( DrvContextTypeDef*, ACTIVE_AXIS_t );
  DrvStatusTypeDef ( *Enable_HP_Filter           ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *Disable_HP_Filter          ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *ClearDRDY                  ) ( DrvContextTypeDef*, ACTIVE_AXIS_t );
  DrvStatusTypeDef ( *Set_INT1_DRDY              ) ( DrvContextTypeDef*, INT1_DRDY_CONFIG_t );
} LIS2DH12_ExtDrv_t;

/**
 * @brief LIS2DH12 specific data internal structure definition
 */
typedef struct
{
  float Previous_ODR;
  LIS2DH12_Mode_t Previous_OpMode;
} LIS2DH12_Data_t;

/**
 * @}
 */

/** @addtogroup LIS2DH12_Public_Variables Public variables
 * @{
 */

extern ACCELERO_Drv_t LIS2DH12_Drv;
extern LIS2DH12_ExtDrv_t LIS2DH12_ExtDrv;

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

#endif /* __LIS2DH12_ACC_DRIVER_HL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
