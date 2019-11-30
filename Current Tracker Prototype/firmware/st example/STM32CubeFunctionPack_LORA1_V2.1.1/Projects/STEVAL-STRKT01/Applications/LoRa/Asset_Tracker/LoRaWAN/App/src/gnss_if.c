/**
******************************************************************************
* @file       gnss_if.c
* @author     AST/CL
* @version    V1.0.0
* @date       Jul-2018
* @brief      Implements API to access Low Level Driver
******************************************************************************
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

/** @addtogroup PROJECTS PROJECTS
  * @{
  */
   
/** @addtogroup STEVAL-STRKT01 STEVAL-STRKT01
  * @{
  */  
   
/** @addtogroup STEVAL-STRKT01_ASSET_TRACKER Asset Tracker
  * @{
  */    
    
/** @addtogroup STEVAL-STRKT01_LoRaWAN LoRaWAN
  * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gnss_if.h"
#include "gnss_parser.h"
#include "x_nucleo_gnss1a1.h"

/* Private defines -----------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/* Puts a string to console */
void GNSS_IF_ConsoleWrite(uint8_t *pBuffer)
{
  GNSS_IO_Transmit(pBuffer);
}

/* Sends a command to the GNSS module. */
void GNSS_IF_WriteCommand(void *pHandle, uint8_t *pBuffer, uint16_t lenght, uint32_t timeout)
{
  if (GNSS_Bus_Write(pHandle, pBuffer, lenght, MAX_DURATION) != GNSS_OK)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"Error sending command\n\n");
  }  
}

void GNSS_IF_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
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
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
