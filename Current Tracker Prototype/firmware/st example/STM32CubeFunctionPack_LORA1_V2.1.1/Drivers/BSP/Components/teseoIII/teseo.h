/**
  *******************************************************************************
  * @file    teseo.h
  * @author  AST/CL
  * @version V2.0.0
  * @date    Feb-2018
  * @brief   This file provides set of driver functions to manage communication 
  * @brief   between MCU and Teseo
  *
  *******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        www.st.com/software_license_agreement_liberty_v2
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
  ********************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TESEO_H
#define TESEO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup DRIVERS
 * @{
 */
 
/** @addtogroup BSP
 * @{
 */

/** @addtogroup COMPONENTS
 * @{
 */

/** @addtogroup COMMON COMMON
 * @brief Defines the GNSS Driver object and related types.
 * @{
 */

/** @addtogroup COMMON_EXPORTED_DEFINES EXPORTED DEFINES
 * @{
 */

/* Exported defines ----------------------------------------------------------*/
/**
 * @brief Constant to identify the UART channel
 */
#define GNSS_BUS_UART (1U)

/**
 * @brief Constant to identify the I2C channel
 */
#define GNSS_BUS_I2C  (2U)

/**
 * @}
 */

/** @defgroup COMMON_EXPORTED_TYPES EXPORTED TYPES
 * @{
 */

/**
 * @brief Data structure for the GNSS message.
 */
typedef struct
{
  uint8_t *buf;
  uint32_t len;
} GNSS_MsgTypeDef;

/**
 * @brief GNSS Status enumerator definition.
 */
typedef enum
{
  GNSS_OK = 0,
  GNSS_ERROR,
  GNSS_TIMEOUT,
  GNSS_NOT_IMPLEMENTED
} GNSS_StatusTypeDef;

/**
 * @brief GNSS Context structure definition.
 */
typedef struct
{
  uint8_t bus;

  void *pData;   /**< Pointer to the effective data object */	
  void *pVTable; /**< Pointer to the Virtual Table Function. */
} GNSS_HandleTypeDef;

/**
 * @brief Data structure that contains the abstract method
 * to be implemented (and assigned) by the GNSS driver.
 */
typedef struct
{
  GNSS_StatusTypeDef    (*Bus_OnOff)(GNSS_HandleTypeDef *pGNSS, uint8_t enable, int8_t nr_msg); /**< Bus UART/I2C OnOff driver abstract method */
  GNSS_StatusTypeDef    (*Bus_Enable)(GNSS_HandleTypeDef *pGNSS); /**< Bus UART/I2C Enable driver abstract method */
  GNSS_StatusTypeDef    (*Bus_Disable)(GNSS_HandleTypeDef *pGNSS); /**< Bus I2C Disable driver abstract method */
  const GNSS_MsgTypeDef*(*Get_Buffer)(GNSS_HandleTypeDef *pGNSS); /**< Get Data Buffer driver abstract method */
  GNSS_StatusTypeDef    (*Release_Buffer)(GNSS_HandleTypeDef *pGNSS, const GNSS_MsgTypeDef *pGNSS_Msg); /**< Release Data Buffer driver abstract method */
  GNSS_StatusTypeDef    (*Bus_Write)(GNSS_HandleTypeDef *pHandle, uint8_t *pBuffer, uint16_t lenght, uint32_t timeout);
  void                  (*Bus_RxCallback)(GNSS_HandleTypeDef *pGNSS);
  void                  (*Bus_ErrorCallback)(GNSS_HandleTypeDef *pGNSS);
  void                  (*Bus_AbortCallback)(GNSS_HandleTypeDef *pGNSS);
  void                  (*Bus_BackgroundProcess)(const GNSS_HandleTypeDef *pGNSS);

} GNSS_DrvTypeDef;

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

#endif /* TESEO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
