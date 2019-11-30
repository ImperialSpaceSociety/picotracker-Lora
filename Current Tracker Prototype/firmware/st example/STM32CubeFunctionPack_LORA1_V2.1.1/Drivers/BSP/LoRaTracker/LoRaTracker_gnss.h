/**
 ******************************************************************************
 * @file    LoRaTracker_gnss.h
 * @author  SRA - System Lab - Sensing & Connectivity Application Team
 * @version V2.1.1
 * @date    10-Oct-2019
 * @brief   This file contains definitions for LoRaTracker_gnss.c
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
#ifndef __LORATRACKER_GNSS_H
#define __LORATRACKER_GNSS_H

#ifdef __cplusplus
extern "C" {
#endif



/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "teseo_io.h"
#include "gnss.h"

/** @addtogroup DRIVERS DRIVERS
  * @{
  */
  
/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup LORATRACKER LORATRACKER
  * @{
  */

/** @addtogroup LORATRACKER_GNSS LORATRACKER_GNSS
  * @brief Implements the GNSS Driver API
  * @{
  */
  
/** @addtogroup LORATRACKER_GNSS_EXPORTED_DEFINES       Exported Defines
 * @{
 */

/* Exported defines ----------------------------------------------------------*/
/**
 * @brief Default GNSS UART BaudRate
 */
#define DEFAULT_UART_BAUD_RATE 9600

/**
 * @brief GNSS UART BaudRate (used for FW Upgrade)
 */
#define FAST_UART_BAUD_RATE    115200
   
// Reset PIN
/**
 * @brief GNSS Reset Pin
 */
#define GNSS_RST_PIN         GPIO_PIN_4

/**
 * @brief GNSS Reset Pin Port
 */
#define GNSS_RST_PORT        GPIOA

/**
 * @brief GNSS Reset Pin set macro
 */
#define GNSS_RST_PIN_SET()   HAL_GPIO_WritePin(GNSS_RST_PORT, GNSS_RST_PIN, GPIO_PIN_SET)

/**
 * @brief GNSS Reset Pin reset macro
 */
#define GNSS_RST_PIN_RESET() HAL_GPIO_WritePin(GNSS_RST_PORT, GNSS_RST_PIN, GPIO_PIN_RESET)

// WAKEUP PIN
/**
 * @brief GNSS Wakeup Pin
 */
#define GNSS_WAKEUP_PIN         GPIO_PIN_8

/**
 * @brief GNSS Wakeup Pin Port
 */
#define GNSS_WAKEUP_PORT        GPIOA

/**
 * @brief GNSS Wakeup Pin set macro
 */
#define GNSS_WAKEUP_SET()       HAL_GPIO_WritePin(GNSS_WAKEUP_PORT, GNSS_WAKEUP_PIN, GPIO_PIN_SET)

/**
 * @brief GNSS Wakeup Pin reset macro
 */
#define GNSS_WAKEUP_RESET()     HAL_GPIO_WritePin(GNSS_WAKEUP_PORT, GNSS_WAKEUP_PIN, GPIO_PIN_RESET)

/**
 * @brief GNSS Wakeup Pin read status macro
 */
#define GNSS_WAKEUP_GETSTATUS() HAL_GPIO_ReadPin(GNSS_WAKEUP_PORT, GNSS_WAKEUP_PIN)
/**
 * @}
 */

/** @addtogroup LORATRACKER_GNSS_EXPORTED_FUNCTIONS     Exported Functions
 * @{
 */

/**
 * @brief  This function initializes the GNSS_HandleTypeDef object.
 * @param  pGNSS Instance of a GNSS_HandleTypeDef object to be initialized by the application
 * @param  bus	 Indicates the channel for communicating with the GNSS module (UART or I2C)
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef     GNSS_Init(GNSS_HandleTypeDef *pGNSS, uint8_t bus);

/**
 * @brief  This function resets the GNSS
 * @param  None
 * @retval None
 */
void                   GNSS_Reset(void);

/**
 * @brief  This function de-initializes the channel (UART or I2C respectively),
 * resets the GNSS and initializes the channel (UART or I2C respectively).
 * @param  pGNSS Pointer to the GNSS handler
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef     GNSS_Bus_Reset(GNSS_HandleTypeDef *pGNSS);

/**
 * @brief  This function enables or disables the communication with the GNSS module.
 * @param  pGNSS  Pointer to the GNSS handler
 * @param  enable Flag to enable/disable the communication
 * @param  nr_msg Number of complete messages we want to receive from the GNSS module
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef     GNSS_Bus_OnOff(GNSS_HandleTypeDef *pGNSS, uint8_t enable, int8_t nr_msg);

/**
 * @brief  This function enables the communication with the GNSS module.
 * @param  pGNSS Pointer to the GNSS handler
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef     GNSS_Bus_Enable(GNSS_HandleTypeDef *pGNSS);

/**
 * @brief  This function disables the communication with the GNSS module.
 * @param  pGNSS Pointer to the GNSS handler
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef     GNSS_Bus_Disable(GNSS_HandleTypeDef *pGNSS);

/**
 * @brief  This function sends a command to the GNSS module.
 * @param  pGNSS   Pointer to the GNSS handler
 * @param  pBuffer The buffer containing the command to be sent
 * @param  lenght  The length of the command
 * @param  timeout Sending timeout
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef     GNSS_Bus_Write(GNSS_HandleTypeDef *pGNSS, uint8_t *pBuffer, uint16_t lenght, uint32_t timeout);

/**
 * @brief  This function retrieves the buffer containing a message from the GNSS module.
 * @param  pGNSS Pointer to the GNSS handler
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
const GNSS_MsgTypeDef *GNSS_Get_Buffer(GNSS_HandleTypeDef *pGNSS);

/**
 * @brief  This function releases the buffer resource for GNSS messages.
 * @param  pGNSS     Pointer to the GNSS handler
 * @param  pGNSS_Msg The buffer to be releases
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef     GNSS_Release_Buffer(GNSS_HandleTypeDef *pGNSS, const GNSS_MsgTypeDef *pGNSS_Msg);

/**
 * @brief  This function reads the GNSS wakeup status.
 * @param  pGNSS  Pointer to the GNSS handler
 * @param  status The status just read
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef     GNSS_Wakeup_Status(const GNSS_HandleTypeDef *pGNSS, uint8_t *status);

/**
 * @brief  Helper function sending a string to the console UART.
 * @param  pBuffer The string buffer to be sent
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef  GNSS_IO_Transmit(uint8_t *pBuffer);

/**
 * @brief  Helper function sending a single character to the console UART.
 * @param  pCh The character to be sent
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef  GNSS_IO_TransmitChar(uint8_t *pCh);

/**
 * @brief  Helper function receiving a string from the console UART.
 * @param  pBuffer The string buffer to be received
 * @param  size    The string size
 * @param  timeout Receiving timeout
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef  GNSS_IO_Receive(uint8_t *pBuffer, uint16_t size, uint32_t timeout);

/**
 * @brief  Helper function reading the status of the console UART.
 * @param  None
 * @retval GNSS_OK on success GNSS_ERROR otherwise
 */
GNSS_StatusTypeDef  GNSS_IO_Readable(void);

/**
 * @brief  Callback handler for UART/I2C receive complete.
 * @param  pGNSS Pointer to the GNSS handler
 * @retval None
 */
void GNSS_Bus_RxCallback(GNSS_HandleTypeDef *pGNSS);

/**
 * @brief  Callback handler for UART/I2C error on reveive.
 * @param  pGNSS Pointer to the GNSS handler
 * @retval None
 */
void GNSS_Bus_ErrorCallback(GNSS_HandleTypeDef *pGNSS);

/**
 * @brief  Callback handler for UART/I2C reveive abort.
 * @param  pGNSS  Instance of a GNSS_HandleTypeDef object to be initialized by the application
 * @retval None
 */
void GNSS_Bus_AbortCallback(GNSS_HandleTypeDef *pGNSS);

/**
 * @brief  Helper function to start (or resume after a given timeout) communication via I2C.
 * @param  pGNSS Pointer to the GNSS handler
 * @retval None
 */
void GNSS_Bus_BackgroundProcess(GNSS_HandleTypeDef *pGNSS);
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

#endif /* __LORATRACKER_GNSS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
