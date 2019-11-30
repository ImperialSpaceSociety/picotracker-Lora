/**
  ******************************************************************************
  * @file    M95M02_DR_driver_HL.c
  * @author  SLAB Application Team (DM)
  * @version V0.1.0
  * @date    19-April-2018
  * @brief   This file provides a set of high-level functions needed to manage
  *          the M95M02_DR eeprom
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

/* Includes ------------------------------------------------------------------*/
#include "M95M02_DR_driver_HL.h"
#include <math.h>
#include <stdlib.h>

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

/* Callable private function prototypes ------------------------------------- */
static DrvStatusTypeDef M95M02_DR_M_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_DeInit( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_Eeprom_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_Eeprom_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_Eeprom_Hold( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_Eeprom_NotHold( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_Eeprom_WriteProtect( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_Eeprom_NotWriteProtect( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_wren( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_wrdi( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_M_rdsr( DrvContextTypeDef *handle, uint8_t *data );
static DrvStatusTypeDef M95M02_DR_M_wrsr( DrvContextTypeDef *handle, uint8_t *data );
static DrvStatusTypeDef M95M02_DR_M_read( DrvContextTypeDef *handle, uint32_t address, uint8_t *data, uint16_t datasize );
static DrvStatusTypeDef M95M02_DR_M_write( DrvContextTypeDef *handle, uint32_t address, uint8_t *data, uint16_t datasize );
static DrvStatusTypeDef M95M02_DR_M_wip_check( DrvContextTypeDef *handle, uint8_t *status );
static DrvStatusTypeDef M95M02_DR_M_Get_BP( DrvContextTypeDef *handle, uint8_t *bp );
static DrvStatusTypeDef M95M02_DR_M_Set_BP( DrvContextTypeDef *handle, uint8_t bp );


/* Private function prototypes ---------------------------------------------- */
static DrvStatusTypeDef M95M02_DR_Init( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_Eeprom_Enable( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_Eeprom_Disable( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_Eeprom_Hold( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_Eeprom_NotHold( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_Eeprom_WriteProtect( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_Eeprom_NotWriteProtect( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_wren( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_wrdi( DrvContextTypeDef *handle );
static DrvStatusTypeDef M95M02_DR_rdsr( DrvContextTypeDef *handle, uint8_t *data );
static DrvStatusTypeDef M95M02_DR_wrsr( DrvContextTypeDef *handle, uint8_t *data );
static DrvStatusTypeDef M95M02_DR_read( DrvContextTypeDef *handle, uint32_t address, uint8_t *data, uint16_t datasize );
static DrvStatusTypeDef M95M02_DR_write( DrvContextTypeDef *handle, uint32_t address, uint8_t *data, uint16_t datasize );
static DrvStatusTypeDef M95M02_DR_wip_check( DrvContextTypeDef *handle, uint8_t *wip );
static DrvStatusTypeDef M95M02_DR_Get_BP( DrvContextTypeDef *handle, uint8_t *bp );
static DrvStatusTypeDef M95M02_DR_Set_BP( DrvContextTypeDef *handle, uint8_t bp );

/** @addtogroup M95M02_DR_DRIVER_HL_Private_Variables M95M02_DR_DRIVER_HL Private variables
 * @{
 */

/**
  * @brief M95M02_DR temperature driver structure
  */
const EEPROM_Drv_t M95M02_DR_M_Drv =
{
  M95M02_DR_M_Init,
  M95M02_DR_M_DeInit,
  M95M02_DR_M_Eeprom_Enable,
  M95M02_DR_M_Eeprom_Disable,
  M95M02_DR_M_Eeprom_Hold,
  M95M02_DR_M_Eeprom_NotHold,
  M95M02_DR_M_Eeprom_WriteProtect,
  M95M02_DR_M_Eeprom_NotWriteProtect,
  M95M02_DR_M_wren,
  M95M02_DR_M_wrdi,
  M95M02_DR_M_rdsr,
  M95M02_DR_M_wrsr,
  M95M02_DR_M_read,
  M95M02_DR_M_write,
  M95M02_DR_M_wip_check,
  M95M02_DR_M_Get_BP,
  M95M02_DR_M_Set_BP
};

/**
  * @brief M95M02_DR data structure definition
  */
M95M02_DR_Data_t M95M02_DR_Data[M95M02_DR_MODULES_MAX_NUM];

/**
  * @}
  */

/** @addtogroup M95M02_DR_DRIVER_HL_Callable_Private_Functions M95M02_DR_DRIVER_HL Callable private functions
 * @{
 */

/**
  * @brief Initialize the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_Init( DrvContextTypeDef *handle )
{
  
  /* Call initialize function */
  if(M95M02_DR_Init(handle) == COMPONENT_ERROR)
  {
    return COMPONENT_ERROR;
  }
  
  ((M95M02_DR_M_Data_t *)(((EEPROM_Data_t *)(handle->pData))->pComponentData))->Data->isMemInitialized = 1;
  
  handle->isInitialized = 1;
  
  return COMPONENT_OK;
}

/**
  * @brief Deinitialize the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_DeInit( DrvContextTypeDef *handle )
{
  
  /* Call initialize function */
  if(M95M02_DR_M_Eeprom_Disable(handle) == COMPONENT_ERROR)
  {
    return COMPONENT_ERROR;
  }
  
  ((M95M02_DR_M_Data_t *)(((EEPROM_Data_t *)(handle->pData))->pComponentData))->Data->isMemInitialized = 0;
  
  handle->isInitialized = 0;
  
  return COMPONENT_OK;
}

/**
  * @brief Enable the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_Eeprom_Enable( DrvContextTypeDef *handle ) {

  /* Check if the component is already enabled */
  if ( handle->isEnabled == 1 )
  {
    return COMPONENT_OK;
  }
  
  /* Call enable function */
  if(M95M02_DR_Eeprom_Enable(handle) == COMPONENT_ERROR)
  {
    return COMPONENT_ERROR;
  }
  
  ((M95M02_DR_M_Data_t *)(((EEPROM_Data_t *)(handle->pData))->pComponentData))->Data->isMemEnabled = 1;
  
  handle->isEnabled = 1;
  
  return COMPONENT_OK;
}

/**
  * @brief Disable the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_Eeprom_Disable( DrvContextTypeDef *handle ) {

  /* Check if the component is already disabled */
  if ( handle->isEnabled == 0 )
  {
    return COMPONENT_OK;
  }
  
  /* Call disable function */
  if(M95M02_DR_Eeprom_Disable(handle) == COMPONENT_ERROR)
  {
    return COMPONENT_ERROR;
  }
  
  ((M95M02_DR_M_Data_t *)(((EEPROM_Data_t *)(handle->pData))->pComponentData))->Data->isMemEnabled = 0;
  
  handle->isEnabled = 0;
  
  return COMPONENT_OK;
}

/**
  * @brief Enable Hold condition for M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_Eeprom_Hold( DrvContextTypeDef *handle ) {

  /* Call HOLD function */
  if(M95M02_DR_Eeprom_Hold(handle) == COMPONENT_ERROR)
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Disable Hold condition for M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_Eeprom_NotHold( DrvContextTypeDef *handle ) {

  /* Call disable HOLD function */
  if(M95M02_DR_Eeprom_NotHold(handle) == COMPONENT_ERROR)
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Enable Write Protect for M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_Eeprom_WriteProtect( DrvContextTypeDef *handle ) {

  /* Call enable Write Protect function */
  if(M95M02_DR_Eeprom_WriteProtect(handle) == COMPONENT_ERROR)
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Disable Write Protect for M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_Eeprom_NotWriteProtect( DrvContextTypeDef *handle ) {

  /* Call disable Write Protect function */
  if(M95M02_DR_Eeprom_NotWriteProtect(handle) == COMPONENT_ERROR)
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Write Enable for the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_wren( DrvContextTypeDef *handle ) {

  if ( M95M02_DR_wren( handle ) == COMPONENT_ERROR ) {
    
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
static DrvStatusTypeDef M95M02_DR_M_wrdi( DrvContextTypeDef *handle ) {

  if ( M95M02_DR_wrdi( handle ) == COMPONENT_ERROR ) {
    
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
static DrvStatusTypeDef M95M02_DR_M_rdsr( DrvContextTypeDef *handle, uint8_t *data ) {

  if ( M95M02_DR_rdsr( handle, data ) == COMPONENT_ERROR ) {
    
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
static DrvStatusTypeDef M95M02_DR_M_wrsr( DrvContextTypeDef *handle, uint8_t *data ) {
  
  if ( M95M02_DR_wrsr( handle, data ) == COMPONENT_ERROR ) {
    
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Write to Eeprom Array of the M95M02_DR eeprom
  * @param handle the device handle
  * @param address the first eeprom address to be written
  * @param data the data that have been written
  * @param datasize the data size
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_M_write( DrvContextTypeDef *handle, uint32_t address, uint8_t *data, uint16_t datasize ) {

  if ( M95M02_DR_write( handle, address, data, datasize ) == COMPONENT_ERROR ) {
    
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
static DrvStatusTypeDef M95M02_DR_M_read( DrvContextTypeDef *handle, uint32_t address, uint8_t *data, uint16_t datasize ) {

  if ( M95M02_DR_read( handle, address, data, datasize ) == COMPONENT_ERROR ) {
    
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

static DrvStatusTypeDef M95M02_DR_M_wip_check( DrvContextTypeDef *handle, uint8_t *wip ) {

  if ( M95M02_DR_wip_check( handle, wip ) == COMPONENT_ERROR ) {
    
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
static DrvStatusTypeDef M95M02_DR_M_Get_BP( DrvContextTypeDef *handle, uint8_t *bp ) {

  if ( M95M02_DR_Get_BP( handle, bp ) == COMPONENT_ERROR ) {
    
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
static DrvStatusTypeDef M95M02_DR_M_Set_BP( DrvContextTypeDef *handle, uint8_t bp ) {

  if ( M95M02_DR_Set_BP( handle, bp ) == COMPONENT_ERROR ) {
    
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @}
  */

/** @addtogroup M95M02_DR_DRIVER_HL_Private_Functions M95M02_DR_DRIVER_HL Private functions
 * @{
 */

/**
  * @brief Initialize the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_Init( DrvContextTypeDef *handle ) {
  
  if ( M95M02_DR_DeActivate(handle) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  if ( M95M02_DR_NotHold(handle) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  if ( M95M02_DR_NotWriteProtect(handle) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Enable the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_Eeprom_Enable( DrvContextTypeDef *handle ) {
  
//  if ( M95M02_DR_Activate(handle) == M95M02_DR_ERROR )
//  {
//    return COMPONENT_ERROR;
//  }
  
  return COMPONENT_OK;
}

/**
  * @brief Disable the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_Eeprom_Disable( DrvContextTypeDef *handle ) {
  
  if ( M95M02_DR_DeActivate(handle) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  
  return COMPONENT_OK;
}

/**
  * @brief Enable Hold for M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_Eeprom_Hold( DrvContextTypeDef *handle ) {
  
  if ( M95M02_DR_Hold(handle) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Disable Hold for M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_Eeprom_NotHold( DrvContextTypeDef *handle ) {
  
  if ( M95M02_DR_NotHold(handle) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }

  return COMPONENT_OK;
}

/**
  * @brief Enable Write Protect for M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_Eeprom_WriteProtect( DrvContextTypeDef *handle ) {
  
  if ( M95M02_DR_WriteProtect(handle) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Disable Write Protect for M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_Eeprom_NotWriteProtect( DrvContextTypeDef *handle ) {
  
  if ( M95M02_DR_NotWriteProtect(handle) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Write Enable for the M95M02_DR eeprom
  * @param handle the device handle
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_wren( DrvContextTypeDef *handle ) {
  
  if ( M95M02_DR_WREN( (void *)handle ) == M95M02_DR_ERROR )
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
static DrvStatusTypeDef M95M02_DR_wrdi( DrvContextTypeDef *handle ) {
  
  if ( M95M02_DR_WRDI( (void *)handle ) == M95M02_DR_ERROR )
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
static DrvStatusTypeDef M95M02_DR_rdsr( DrvContextTypeDef *handle, uint8_t *data ) {
  
  if ( M95M02_DR_RDSR( (void *)handle, data ) == M95M02_DR_ERROR )
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
static DrvStatusTypeDef M95M02_DR_wrsr( DrvContextTypeDef *handle, uint8_t *data ) {
  
  if ( M95M02_DR_WRSR( (void *)handle, data ) == M95M02_DR_ERROR )
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
static DrvStatusTypeDef M95M02_DR_read( DrvContextTypeDef *handle, uint32_t address, uint8_t *data, uint16_t datasize ) {
  
  if ( M95M02_DR_READ( (void *)handle, address, data, datasize ) == M95M02_DR_ERROR )
  {
    return COMPONENT_ERROR;
  }
  
  return COMPONENT_OK;
}

/**
  * @brief Write to Eeprom Array of the M95M02_DR eeprom
  * @param handle the device handle
  * @param address the first eeprom address to be written
  * @param data the data that have been written
  * @param datasize the data size
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
  */
static DrvStatusTypeDef M95M02_DR_write( DrvContextTypeDef *handle, uint32_t address, uint8_t *data, uint16_t datasize ) {
  
  if ( M95M02_DR_WRITE( (void *)handle, address, data, datasize ) == M95M02_DR_ERROR )
    return COMPONENT_ERROR;
  
  return COMPONENT_OK;
}

static DrvStatusTypeDef M95M02_DR_wip_check( DrvContextTypeDef *handle, uint8_t *wip ) {
  
  if ( M95M02_DR_WIP_CHECK( (void *)handle, wip ) == M95M02_DR_ERROR )
    return COMPONENT_ERROR;
  
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
static DrvStatusTypeDef M95M02_DR_Get_BP( DrvContextTypeDef *handle, uint8_t *bp ) {

  if ( M95M02_DR_GET_BP( (void *)handle, bp ) == M95M02_DR_ERROR )
    return COMPONENT_ERROR;
  
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
static DrvStatusTypeDef M95M02_DR_Set_BP( DrvContextTypeDef *handle, uint8_t bp ) {
  
  if ( M95M02_DR_SET_BP( (void *)handle, bp ) == M95M02_DR_ERROR )
    return COMPONENT_ERROR;
  
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
