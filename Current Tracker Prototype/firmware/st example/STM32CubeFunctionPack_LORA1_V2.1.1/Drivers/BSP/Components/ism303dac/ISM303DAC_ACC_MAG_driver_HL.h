/**
 ******************************************************************************
 * @file    ISM303DAC_ACC_MAG_driver_HL.h
 * @author  MEMS Application Team
 * @version V4.2.0
 * @date    01-February-2018
 * @brief   This file contains definitions for the ISM303DAC_ACC_MAG_driver_HL.c firmware driver
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
#ifndef __ISM303DAC_ACC_MAG_DRIVER_HL_H
#define __ISM303DAC_ACC_MAG_DRIVER_HL_H

#ifdef __cplusplus
extern "C" {
#endif



/* Includes ------------------------------------------------------------------*/

#include "accelerometer.h"
#include "magnetometer.h"

/* Include accelero sensor component drivers. */
#include "ISM303DAC_ACC_MAG_driver.h"



/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup COMPONENTS COMPONENTS
 * @{
 */

/** @addtogroup ISM303DAC ISM303DAC
 * @{
 */

/** @addtogroup ISM303DAC_Public_Constants Public constants
 * @{
 */

#define ISM303DAC_SENSORS_MAX_NUM  1     /**< ISM303DAC max number of instances */

/** @addtogroup ISM303DAC_ACC_SENSITIVITY Accelero sensitivity values based on selected full scale
 * @{
 */

#define ISM303DAC_ACC_SENSITIVITY_FOR_FS_2G   0.061  /**< Sensitivity value for 2 g full scale [mg/LSB] */
#define ISM303DAC_ACC_SENSITIVITY_FOR_FS_4G   0.122  /**< Sensitivity value for 4 g full scale [mg/LSB] */
#define ISM303DAC_ACC_SENSITIVITY_FOR_FS_8G   0.244  /**< Sensitivity value for 8 g full scale [mg/LSB] */
#define ISM303DAC_ACC_SENSITIVITY_FOR_FS_16G  0.488  /**< Sensitivity value for 16 g full scale [mg/LSB] */

/**
 * @}
 */

/** @addtogroup ISM303DAC_MAG_SENSITIVITY Mag sensitivity values based on selected full scale
 * @{
 */

#define ISM303DAC_MAG_SENSITIVITY_FOR_FS_50G  1.5  /**< Sensitivity value for 50 gauss full scale [mgauss/LSB] */

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup ISM303DAC_Public_Types ISM303DAC Public Types
 * @{
 */

/**
 * @brief ISM303DAC combo specific data internal structure definition
 */
typedef struct
{
  uint8_t isAccInitialized;
  uint8_t isMagInitialized;
} ISM303DAC_Combo_Data_t;

/**
 * @brief ISM330DLC accelero specific data internal structure definition
 */
typedef struct
{
  ISM303DAC_Combo_Data_t *comboData; /* Combo data to manage in software SPI 3-Wire initialization of the combo sensors */
  float Previous_ODR;
} ISM303DAC_X_Data_t;

/**
 * @brief ISM303DAC magneto specific data internal structure definition
 */
typedef struct
{
  ISM303DAC_Combo_Data_t *comboData; /* Combo data to manage in software SPI 3-Wire initialization of the combo sensors */
  float Previous_ODR;
} ISM303DAC_M_Data_t;

/**
 * @}
 */

/** @addtogroup ISM303DAC_Public_Variables Public variables
 * @{
 */

extern ACCELERO_Drv_t ISM303DAC_X_Drv;
extern MAGNETO_Drv_t ISM303DAC_M_Drv;
extern ISM303DAC_Combo_Data_t ISM303DAC_Combo_Data[ISM303DAC_SENSORS_MAX_NUM];

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

#endif /* __ISM303DAC_ACC_MAG_DRIVER_HL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
