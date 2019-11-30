/**
  ******************************************************************************
  * @file    M95M02_DR_Driver_HL.h
  * @author  SLAB Application Team (DM)
  * @version V0.1.0
  * @date    19-April-2018
  * @brief   This file contains definitions for the M95M02_DR_Driver_HL.c firmware driver
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
#ifndef __M95M02_DR_DRIVER_HL_H
#define __M95M02_DR_DRIVER_HL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "eeprom.h"

/* Include epprom component drivers. */
#include "M95M02_DR_Driver.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup M95M02_DR M95M02-DR
  * @{
  */

/** @addtogroup M95M02_DR_DRIVER_HL M95M02_DR_DRIVER_HL
  * @{
  */

/** @addtogroup M95M02_DR_DRIVER_HL_Public_Constants M95M02_DR_DRIVER_HL Public constants
 * @{
 */

#define M95M02_DR_MODULES_MAX_NUM  1     //!< M95M02_DR max number of instances

/**
  * @}
  */

/** @addtogroup M95M02_DR_DRIVER_HL_Public_Types M95M02_DR_DRIVER_HL Public Types
 * @{
 */

/**
 * @brief M95M02_DR specific data internal structure definition
  */
typedef struct
{
  uint8_t isMemInitialized;
  uint8_t isMemEnabled;
} M95M02_DR_Data_t;

/**
  * @brief M95M02_DR eeprom specific data internal structure definition
  */
typedef struct
{
  M95M02_DR_Data_t *Data;       /* Data to manage in software enable/disable of the epproms */
} M95M02_DR_M_Data_t;

/**
  * @}
  */

/** @addtogroup M95M02_DR_DRIVER_HL_Public_Variables M95M02_DR_DRIVER_HL Public variables
  * @{
  */

extern const EEPROM_Drv_t M95M02_DR_M_Drv;
extern M95M02_DR_Data_t M95M02_DR_Data[M95M02_DR_MODULES_MAX_NUM];

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

#endif /* __M95M02_DR_DRIVER_HL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
