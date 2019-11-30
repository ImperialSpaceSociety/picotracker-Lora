/**
  ******************************************************************************
  * @file    eeprom.h
  * @author  SRA - System Lab - Sensing & Connectivity Application Team
  * @version V2.1.1
  * @date    10-Oct-2019
  * @brief   This header file contains the functions prototypes for the
  *          eeprom driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
#ifndef __EEPROM_H
#define __EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif



/* Includes ------------------------------------------------------------------*/
#include "sensor.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup COMMON COMMON
  * @{
  */

/** @addtogroup EEPROM EEPROM
  * @{
  */

/** @addtogroup EEPROM_Public_Types EEPROM Public types
  * @{
  */

/**
  * @brief  EEPROM driver structure definition
  */
typedef struct
{
  DrvStatusTypeDef ( *Init                   ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *DeInit                 ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *Eeprom_Enable          ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *Eeprom_Disable         ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *Eeprom_Hold            ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *Eeprom_NotHold         ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *Eeprom_WriteProtect    ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *Eeprom_NotWriteProtect ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *WriteEnable            ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *WriteDisable           ) ( DrvContextTypeDef* );
  DrvStatusTypeDef ( *ReadStatusRegister     ) ( DrvContextTypeDef*, uint8_t* );
  DrvStatusTypeDef ( *WriteStatusRegister    ) ( DrvContextTypeDef*, uint8_t* );
  DrvStatusTypeDef ( *Read                   ) ( DrvContextTypeDef*, uint32_t, uint8_t*, uint16_t );
  DrvStatusTypeDef ( *Write                  ) ( DrvContextTypeDef*, uint32_t, uint8_t*, uint16_t );
  DrvStatusTypeDef ( *WIP_Check              ) ( DrvContextTypeDef*, uint8_t* );
  DrvStatusTypeDef ( *Get_BP                 ) ( DrvContextTypeDef*, uint8_t* );
  DrvStatusTypeDef ( *Set_BP                 ) ( DrvContextTypeDef*, uint8_t );
} EEPROM_Drv_t;

/**
  * @brief  EEPROM data structure definition
  */
typedef struct
{
  void *pComponentData; /* Component specific data. */
  void *pExtData;       /* Other data. */
} EEPROM_Data_t;

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

#endif /* __EEPROM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
