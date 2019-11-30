/**
  ******************************************************************************
  * @file    LoRaTracker_eeprom.c
  * @author  SRA - System Lab - Sensing & Connectivity Application Team
  * @version V2.1.1
  * @date    10-Oct-2019
  * @brief   This file provides a set of functions needed to manage the
  *          eeprom module
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

/* Includes ------------------------------------------------------------------*/

#include "LoRaTracker_eeprom.h"

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
  * @brief   This module provides a set of functions needed to manage the eeprom 
  * @{
  */

/** @addtogroup LORATRACKER_EEPROM_Private_Variables    Private Variables
 * @{
 */

static DrvContextTypeDef EEPROM_ModuleHandle[ EEPROM_MODULES_MAX_NUM ];
static EEPROM_Data_t EEPROM_Data[ EEPROM_MODULES_MAX_NUM ]; // Accelerometer - all.
static M95M02_DR_M_Data_t M95M02_DR_M_0_Data; // Accelerometer - sensor 0.

/**
 * @}
 */

/** @addtogroup LORATRACKER_EEPROM_Private_Function_Prototype   Private Function Prototype
 * @{
 */

static DrvStatusTypeDef BSP_M95M02_DR_EEPROM_Init( void **handle );

/**
 * @}
 */

/** @addtogroup LORATRACKER_EEPROM_Imported_Functions   Imported Functions
 * @{
 */

extern DrvStatusTypeDef M95M02_DR_IO_Init( void );

/**
 * @}
 */

/** @addtogroup LORATRACKER_EEPROM_Private_Functions    Private Functions
 * @{
 */

/**
 * @brief Initialize an eeprom module
 * @param id the eeprom module identifier
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_Init( EEPROM_ID_t id, void **handle )
{
  *handle = NULL;
  
  switch(id)
  {
    default:
    case EEPROM_MODULES_AUTO:
    case M95M02_DR_M_0:
    {
      if( BSP_M95M02_DR_EEPROM_Init(handle) == COMPONENT_ERROR )
      {
        return COMPONENT_ERROR;
      }
      break;
    }
  }
  
  return COMPONENT_OK;
}

static DrvStatusTypeDef BSP_M95M02_DR_EEPROM_Init( void **handle ) {
  
  EEPROM_Drv_t *driver = NULL;
  
  if(EEPROM_ModuleHandle[M95M02_DR_M_0].isInitialized == 1)
  {
    /* We have reached the max num of instance for this component */
    return COMPONENT_ERROR;
  }
  
  if ( M95M02_DR_IO_Init() == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  /* Setup sensor handle. */
  EEPROM_ModuleHandle[ M95M02_DR_M_0 ].instance      = M95M02_DR_M_0;
  EEPROM_ModuleHandle[ M95M02_DR_M_0 ].isInitialized = 0;
  EEPROM_ModuleHandle[ M95M02_DR_M_0 ].isEnabled     = 0;
  EEPROM_ModuleHandle[ M95M02_DR_M_0 ].pData         = ( void * )&EEPROM_Data[ M95M02_DR_M_0 ];
  EEPROM_ModuleHandle[ M95M02_DR_M_0 ].pVTable       = ( void * )&M95M02_DR_M_Drv;
  EEPROM_ModuleHandle[ M95M02_DR_M_0 ].pExtVTable    = 0;
  
  M95M02_DR_M_0_Data.Data = &M95M02_DR_Data[0];
  EEPROM_Data[ M95M02_DR_M_0 ].pComponentData = ( void * )&M95M02_DR_M_0_Data;
  EEPROM_Data[ M95M02_DR_M_0 ].pExtData       = 0;
  
  *handle = (void *)&EEPROM_ModuleHandle[ M95M02_DR_M_0 ];
  
  driver = ( EEPROM_Drv_t * )((DrvContextTypeDef *)(*handle))->pVTable;
  
  if ( driver->Init == NULL )
  {
    memset((*handle), 0, sizeof(DrvContextTypeDef));
    *handle = NULL;
    return COMPONENT_ERROR;
  }
  
  if ( driver->Init( (DrvContextTypeDef *)(*handle) ) == COMPONENT_ERROR )
  {
    memset((*handle), 0, sizeof(DrvContextTypeDef));
    *handle = NULL;
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}
  
/**
 * @brief Deinitialize eeprom module
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_DeInit( void **handle ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)(*handle);
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if ( driver->DeInit == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->DeInit( ctx ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  memset(ctx, 0, sizeof(DrvContextTypeDef));
  
  *handle = NULL;
  
  return COMPONENT_OK;
}

/**
 * @brief Enable eeprom module
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_Module_Enable( void *handle ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if ( driver->Eeprom_Enable == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->Eeprom_Enable( ctx ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
 * @brief Disable eeprom module
 * @param handle the device handle
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_Module_Disable( void *handle ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if ( driver->Eeprom_Disable == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->Eeprom_Disable( ctx ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
 * @brief Check if the eeprom module is initialized
 * @param handle the device handle
 * @param status the pointer to the initialization status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_IsInitialized( void *handle, uint8_t *status ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  if ( status == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  *status = ctx->isInitialized;
  
  return COMPONENT_OK;
}

/**
 * @brief Check if the eeprom module is enabled
 * @param handle the device handle
 * @param status the pointer to the enable status
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_IsEnabled( void *handle, uint8_t *status ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  if ( status == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  *status = ctx->isEnabled;
  
  return COMPONENT_OK;
}

/**
 * @brief Get the eeprom module instance
 * @param handle the device handle
 * @param instance the pointer to the device instance
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_Get_Instance( void *handle, uint8_t *instance ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  if ( instance == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  *instance = ctx->instance;
  
  return COMPONENT_OK;
}

/**
  * @brief Write Enable for the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
DrvStatusTypeDef BSP_EEPROM_WriteEnable( void *handle ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if ( driver->WriteEnable == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->WriteEnable( ctx ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Write Disable for the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
DrvStatusTypeDef BSP_EEPROM_WriteDisable( void *handle ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if ( driver->WriteDisable == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->WriteDisable( ctx ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Read Status Register of the M95M02_DR eeprom
  * @param handle the device handle
  * @param data data to be read
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
DrvStatusTypeDef BSP_EEPROM_ReadStatusRegister( void *handle, uint8_t *data) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if(data == NULL)
  {  
    return COMPONENT_ERROR;
  }
  
  if ( driver->ReadStatusRegister == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->ReadStatusRegister( ctx, data ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Write Status Register of the M95M02_DR eeprom
  * @param handle the device handle
  * @param data data to be written
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
DrvStatusTypeDef BSP_EEPROM_WriteStatusRegister( void *handle, uint8_t *data) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if(data == NULL)
  {  
    return COMPONENT_ERROR;
  }
  
  if ( driver->WriteStatusRegister == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->WriteStatusRegister( ctx, data ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Read from Eeprom Array of the M95M02_DR eeprom
  * @param handle the device handle
  * @param address the first eeprom address to be read
  * @param data the data that have been read
  * @param datasize the data size
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
DrvStatusTypeDef BSP_EEPROM_Read( void *handle, uint32_t address, uint8_t *data, uint16_t datasize) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if(data == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->Read == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->Read( ctx, address, data, datasize ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

DrvStatusTypeDef BSP_EEPROM_Write( void *handle, uint32_t address, uint8_t *data, uint16_t datasize) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if(data == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->Write == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->Write( ctx, address, data, datasize ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

DrvStatusTypeDef BSP_EEPROM_WIP_Check( void *handle, uint8_t *status ) {
  
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if(status == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->WIP_Check == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->WIP_Check( ctx, status ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
 * @brief Get the block protect of the M95M02_DR eeprom
 * @details The block protect defines the size of the area to be software-protected against Write instructions
 * @param handle the device handle
 * @param bp pointer where the block protect is written
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_Get_BP( void *handle, M95M02_DR_ProtectedBlock_et *bp ) {

  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if(bp == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->Get_BP == NULL )
  {
    return COMPONENT_ERROR;
  }
  
  if ( driver->Get_BP( ctx, (uint8_t *)bp ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
 * @brief Set the block protect of the M95M02_DR eeprom
 * @details The block protect defines the size of the area to be software-protected against Write instructions
 * @param handle the device handle
 * @param bp The block protect to be set
 * @retval COMPONENT_OK in case of success
 * @retval COMPONENT_ERROR in case of failure
 */
DrvStatusTypeDef BSP_EEPROM_Set_BP( void *handle, M95M02_DR_ProtectedBlock_et bp ) {

  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  EEPROM_Drv_t *driver = NULL;
  
  if(ctx == NULL)
  {
    return COMPONENT_ERROR;
  }
  
  driver = ( EEPROM_Drv_t * )ctx->pVTable;
  
  if ( driver->Set_BP == NULL )
  {
    return COMPONENT_ERROR;
  }
  if ( driver->Set_BP( ctx, (uint8_t)bp ) == COMPONENT_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
