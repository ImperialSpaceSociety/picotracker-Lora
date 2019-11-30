/**
  ******************************************************************************
  * @file    LoRaTracker_eeprom.h
  * @author  SRA - System Lab - Sensing & Connectivity Application Team
  * @version V2.1.1
  * @date    10-Oct-2019
  * @brief   This file contains definitions for the LoRaTracker_eeprom.c
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
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
#ifndef __LORATRACKER_EEPROM_H
#define __LORATRACKER_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "M95M02_DR_Driver_HL.h"
  
/** @addtogroup DRIVERS DRIVERS
  * @{
  */
  
/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup LORATRACKER 
  * @{
  */

/** @addtogroup LORATRACKER_EEPROM LORATRACKER_EEPROM
  * @{
  */

/** @addtogroup LORATRACKER_EEPROM_Exported_Types       Exported Types
  * @{
  */

typedef enum
{
  EEPROM_MODULES_AUTO = -1,     /* Always first element and equal to -1 */
  M95M02_DR_M_0       =  0      /* Default on board. */
} EEPROM_ID_t;

/**
 * @}
 */

/** @addtogroup LORATRACKER_EEPROM_Exported_Defines     Exported Defines
  * @{
  */

#define EEPROM_MODULES_MAX_NUM  1

/**
 * @}
 */

/** @addtogroup LORATRACKER_EEPROM_Exported_Functions   Exported Functions
 * @{
 */

/* Eeprom Configuration Functions */
DrvStatusTypeDef BSP_EEPROM_Init( EEPROM_ID_t id, void **handle );
DrvStatusTypeDef BSP_EEPROM_DeInit( void **handle );
DrvStatusTypeDef BSP_EEPROM_Module_Enable( void *handle );
DrvStatusTypeDef BSP_EEPROM_Module_Disable( void *handle );
DrvStatusTypeDef BSP_EEPROM_IsInitialized( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_EEPROM_IsEnabled( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_EEPROM_Get_Instance( void *handle, uint8_t *instance );
DrvStatusTypeDef BSP_EEPROM_WriteEnable( void *handle );
DrvStatusTypeDef BSP_EEPROM_WriteDisable( void *handle );
DrvStatusTypeDef BSP_EEPROM_ReadStatusRegister( void *handle, uint8_t *data);
DrvStatusTypeDef BSP_EEPROM_WriteStatusRegister( void *handle, uint8_t *data);
DrvStatusTypeDef BSP_EEPROM_Read( void *handle, uint32_t address, uint8_t *data, uint16_t datasize);
DrvStatusTypeDef BSP_EEPROM_Write( void *handle, uint32_t address, uint8_t *data, uint16_t datasize);
DrvStatusTypeDef BSP_EEPROM_WIP_Check( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_EEPROM_Get_BP( void *handle, M95M02_DR_ProtectedBlock_et *bp );
DrvStatusTypeDef BSP_EEPROM_Set_BP( void *handle, M95M02_DR_ProtectedBlock_et bp );

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

#endif /* __LORATRACKER_EEPROM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
