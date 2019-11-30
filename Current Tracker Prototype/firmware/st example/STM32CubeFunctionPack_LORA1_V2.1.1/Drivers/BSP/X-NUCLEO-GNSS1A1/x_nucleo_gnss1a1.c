/**
  ******************************************************************************
  * @file    x_nucleo_gnss1a1.c
  * @author  AST / Central Lab
  * @version V2.0.0
  * @date    Feb-2018
  * @brief   This file contains prototypes for the GNSS
  *	     expansion board driver specific functions
  *          defined in x_nucleo_gnss1a1.h
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include <string.h>

#include "x_nucleo_gnss1a1.h"

/* Global variables ----------------------------------------------------------*/
extern I2C_HandleTypeDef  hi2c;
extern UART_HandleTypeDef huart;
extern UART_HandleTypeDef io_huart;

extern void GNSS_I2C_Init(void);
extern void GNSS_I2C_DeInit(void);
extern void GNSS_UART_Init(uint32_t BaudRate);
extern void GNSS_UART_DeInit(void);

/* Private functions ---------------------------------------------------------*/

/*
 * Returns the static instance of a GNSS object.
 */
static Teseo_IO_DataTypeDef *Teseo_IO_static_alloc(void)
{
  static Teseo_IO_DataTypeDef Teseo_IO_Data;
  return &Teseo_IO_Data;
}

/* Exported functions --------------------------------------------------------*/

GNSS_StatusTypeDef GNSS_Init(GNSS_HandleTypeDef *pGNSS, uint8_t bus)
{
  Teseo_IO_DataTypeDef *pData = Teseo_IO_static_alloc();

  /* Check the GNSS handle allocation */
  if(pGNSS == NULL)
  {
    return GNSS_ERROR;
  }
  
  if (bus == GNSS_BUS_I2C)
  {
    pData->hi2c = &hi2c;
  }
  else
  {
    pData->huart = &huart;
  }

  pGNSS->bus = bus;
  pGNSS->pData = (void *)pData;
  pGNSS->pVTable = (void *)&Teseo_Drv;
  
  return GNSS_OK;
}

GNSS_StatusTypeDef GNSS_IO_Transmit(uint8_t *pBuffer)
{
  if (HAL_UART_Transmit(&io_huart, pBuffer, (uint16_t)strlen((char *)pBuffer), 1000) != HAL_OK)
  {
    return GNSS_ERROR;
  }

  return GNSS_OK;
}

GNSS_StatusTypeDef GNSS_IO_TransmitChar(uint8_t *pCh)
{
  if (HAL_UART_Transmit(&io_huart, pCh, 1, 1000) != HAL_OK)
  {
    return GNSS_ERROR;
  }

  return GNSS_OK;
}

GNSS_StatusTypeDef GNSS_IO_Receive(uint8_t *pBuffer, uint16_t size, uint32_t timeout)
{
  if (HAL_UART_Receive(&io_huart, pBuffer, size, timeout) != HAL_OK)
  {
    return GNSS_ERROR;
  }

  return GNSS_OK;
}

GNSS_StatusTypeDef GNSS_IO_Readable(void)
{
  /*  To avoid a target blocking case, let's check for
  *  possible OVERRUN error and discard it
  */
  if(__HAL_UART_GET_FLAG(&io_huart, UART_FLAG_ORE)) {
    __HAL_UART_CLEAR_OREFLAG(&io_huart);
  }
  // Check if data is received
  return (__HAL_UART_GET_FLAG(&io_huart, UART_FLAG_RXNE) != RESET) ? GNSS_ERROR : GNSS_OK;
}


void GNSS_Reset(void)
{
  GNSS_RST_PIN_RESET();
  HAL_Delay(10);
  GNSS_RST_PIN_SET();
  HAL_Delay(150);
}

GNSS_StatusTypeDef GNSS_Bus_Reset(GNSS_HandleTypeDef *pGNSS)
{
  if (pGNSS == NULL)
  {
    return GNSS_ERROR;
  }
  
  if (GNSS_Bus_Disable(pGNSS) == GNSS_ERROR)
  {
    return GNSS_ERROR;
  }
  
  GNSS_Reset();

  if (GNSS_Bus_Enable(pGNSS) == GNSS_ERROR)
  {
    return GNSS_ERROR;
  }
  
  return GNSS_OK;
}

GNSS_StatusTypeDef GNSS_Bus_OnOff(GNSS_HandleTypeDef *pGNSS, uint8_t enable, int8_t nr_msg)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return GNSS_ERROR;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;

  if (pDrv->Bus_OnOff == NULL)
  {
    return GNSS_ERROR;
  }
 
  if (pDrv->Bus_OnOff(pGNSS, enable, nr_msg) == GNSS_ERROR)
  {
    return GNSS_ERROR;
  }
  
  return GNSS_OK;
}

GNSS_StatusTypeDef GNSS_Bus_Enable(GNSS_HandleTypeDef *pGNSS)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return GNSS_ERROR;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;

  if (pDrv->Bus_Enable == NULL)
  {
    return GNSS_ERROR;
  }

  if (pGNSS->bus == GNSS_BUS_I2C)
  {
    GNSS_I2C_Init();
  }
  else
  {
    GNSS_UART_Init(DEFAULT_UART_BAUD_RATE);
  }
  
  if (pDrv->Bus_Enable(pGNSS) == GNSS_ERROR)
  {
    return GNSS_ERROR;
  }
  
  return GNSS_OK;
}

GNSS_StatusTypeDef GNSS_Bus_Disable(GNSS_HandleTypeDef *pGNSS)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return GNSS_ERROR;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;

  if (pDrv->Bus_Disable == NULL)
  {
    return GNSS_ERROR;
  }
  
  if (pDrv->Bus_Disable(pGNSS) == GNSS_ERROR)
  {
    return GNSS_ERROR;
  }
  
  if (pGNSS->bus == GNSS_BUS_I2C)
  {
    GNSS_I2C_DeInit();
  }
  else
  {
    GNSS_UART_DeInit();
  }
  
  return GNSS_OK;
}

const GNSS_MsgTypeDef *GNSS_Get_Buffer(GNSS_HandleTypeDef *pGNSS)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return NULL;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;
  
  if (pDrv->Get_Buffer == NULL)
  {
    return NULL;
  }
  
  return (pDrv->Get_Buffer(pGNSS));
}

GNSS_StatusTypeDef GNSS_Release_Buffer(GNSS_HandleTypeDef *pGNSS, const GNSS_MsgTypeDef *pGNSS_Msg)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return GNSS_ERROR;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;
  
  if (pDrv->Release_Buffer == NULL)
  {
    return GNSS_ERROR;
  }
  
  if (pDrv->Release_Buffer(pGNSS, pGNSS_Msg) == GNSS_ERROR)
  {
    return GNSS_ERROR;
  }

  return GNSS_OK;
}


GNSS_StatusTypeDef GNSS_Bus_Write(GNSS_HandleTypeDef *pGNSS, uint8_t *pBuffer, uint16_t lenght, uint32_t timeout)
{
  GNSS_StatusTypeDef status;
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return GNSS_ERROR;
  }

  if (pBuffer == NULL)
  {
    return GNSS_ERROR;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;
  
  if (pDrv->Bus_Write == NULL)
  {
    return GNSS_ERROR;
  }

  status = pDrv->Bus_Write(pGNSS, pBuffer, lenght, timeout);
  if (status == GNSS_ERROR)
  {
    return GNSS_ERROR;
  }

  return GNSS_OK;
}

GNSS_StatusTypeDef GNSS_Wakeup_Status(const GNSS_HandleTypeDef *pGNSS, uint8_t *status)
{
  (void)pGNSS;

  (GNSS_WAKEUP_GETSTATUS() == GPIO_PIN_RESET) ? (*status = 0) : (*status = 1);
  
  return GNSS_OK;
}

void GNSS_Bus_RxCallback(GNSS_HandleTypeDef *pGNSS)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;

  if (pDrv->Bus_RxCallback == NULL)
  {
    return;
  }
  
  pDrv->Bus_RxCallback(pGNSS);
}

void GNSS_Bus_ErrorCallback(GNSS_HandleTypeDef *pGNSS)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;

  if (pDrv->Bus_ErrorCallback == NULL)
  {
    return;
  }
  
  pDrv->Bus_ErrorCallback(pGNSS);
}

void GNSS_Bus_AbortCallback(GNSS_HandleTypeDef *pGNSS)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;

  if (pDrv->Bus_AbortCallback == NULL)
  {
    return;
  }
  
  pDrv->Bus_AbortCallback(pGNSS);
}

void GNSS_Bus_BackgroundProcess(GNSS_HandleTypeDef *pGNSS)
{
  const GNSS_DrvTypeDef *pDrv;

  if (pGNSS == NULL)
  {
    return;
  }

  pDrv = (GNSS_DrvTypeDef *)pGNSS->pVTable;

  if (pDrv->Bus_BackgroundProcess == NULL)
  {
    return;
  }
  
  pDrv->Bus_BackgroundProcess(pGNSS);
}

__weak void GNSS_ConsoleDbg(uint8_t *pData)
{
  HAL_UART_Transmit(&io_huart, pData, strlen((char *)pData), 1000);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
