/**
*******************************************************************************
* @file    gnss_if.h
* @author  AST/CL
* @version V2.0.0
* @date    Jun-2018
* @brief   Provides API to access Low Level Driver - LibGNSS module middleware
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
#ifndef GNSS_IF_H
#define GNSS_IF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup MIDDLEWARES
 *  @{
 */

/** @addtogroup ST
 *  @{
 */

/** @addtogroup STM32_GNSS
 *  @{
 */
 
/** @addtogroup LibGNSS
 *  @{
 */

/** @defgroup GNSS_DATA_FUNCTIONS GNSS DATA FUNCTIONS
 *  @brief Prototypes of the API allowing the application to interface the driver
 *  and interact with GNSS module (sending commands, retrieving parsed NMEA info, etc.).
 *  The implementation is up to the application according to specific needs.
 *  @{
 */

/**	
 * @brief  This function puts a string on the console (via UART).
 * @param  pBuffer The string that contains the data to be written on the console
 * @retval None
 */
void GNSS_IF_ConsoleWrite(uint8_t *pBuffer);

/**
 * @brief  This function puts a single character on the console (via UART).
 * @param  pCh Charatcer to be printed
 * @retval None
 */
void GNSS_IF_ConsoleWriteChar(uint8_t *pCh);

/**	
 * @brief  This function gets data from the console (via UART).
 * @param  pBuffer The buffer where the received data are stored
 * @retval None
 */
void GNSS_IF_ConsoleRead(uint8_t *pBuffer, uint16_t size, uint32_t timeout);

/**	
 * @brief  Check if the console status is readable or not and set its status
 * @param  None
 * @retval 1 if the the console status is readable, 0 otherwise
 */
int8_t GNSS_IF_ConsoleReadable(void);

/**
 * @brief  This function sends a command to the GNSS module.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  pBuffer The buffer containing the command to be sent
 * @param  lenght  The length of the command
 * @retval None
 */
void GNSS_IF_WriteCommand(void *pHandle, uint8_t *pBuffer, uint16_t lenght, uint32_t timeout);

/**
 * @brief  osDelay wrapper
 * @param  Delay delay in ms
 * @retval None
 */
void GNSS_IF_Delay(uint32_t Delay);
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

#endif /* GNSS_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
