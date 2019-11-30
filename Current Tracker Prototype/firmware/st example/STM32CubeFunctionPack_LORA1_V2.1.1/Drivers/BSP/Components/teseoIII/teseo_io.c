/**
  *******************************************************************************
  * @file    teseo_io.c
  * @author  APG/AST/CL
  * @version V2.0.0
  * @date    Feb-2018
  * @brief   Teseo III I/O manager.
  *******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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

/* Includes ------------------------------------------------------------------*/
#include "teseo_io.h"
#include "teseo_i2c.h"
#include "teseo_uart.h"

/* Private functions ---------------------------------------------------------*/
static GNSS_StatusTypeDef     Teseo_Bus_OnOff(GNSS_HandleTypeDef *pGNSS, uint8_t enable, int8_t nr_msg);
static GNSS_StatusTypeDef     Teseo_Bus_Enable(GNSS_HandleTypeDef *pGNSS);
static GNSS_StatusTypeDef     Teseo_Bus_Disable(GNSS_HandleTypeDef *pGNSS);
static const GNSS_MsgTypeDef *Teseo_Get_Buffer(GNSS_HandleTypeDef *pGNSS);
static GNSS_StatusTypeDef     Teseo_Release_Buffer(GNSS_HandleTypeDef *pGNSS, const GNSS_MsgTypeDef *pGNSS_Msg);

static GNSS_StatusTypeDef  Teseo_Bus_Write(GNSS_HandleTypeDef *pGNSS,
                                           uint8_t *pBuffer,
                                           uint16_t lenght,
                                           uint32_t timeout);

static void Teseo_Bus_RxCallback(GNSS_HandleTypeDef *pGNSS);
static void Teseo_Bus_ErrorCallback(GNSS_HandleTypeDef *pGNSS);
static void Teseo_Bus_AbortCallback(GNSS_HandleTypeDef *pGNSS);
static void Teseo_Bus_BackgroundProcess(const GNSS_HandleTypeDef *pGNSS);

/*
 * Definition of the GNSS driver function pointers struct
 */
GNSS_DrvTypeDef Teseo_Drv = {
  Teseo_Bus_OnOff,
  Teseo_Bus_Enable,
  Teseo_Bus_Disable,
  Teseo_Get_Buffer,
  Teseo_Release_Buffer,
  Teseo_Bus_Write,
  Teseo_Bus_RxCallback,
  Teseo_Bus_ErrorCallback,
  Teseo_Bus_AbortCallback,
  Teseo_Bus_BackgroundProcess
};

/*
 * Implements the API driver enabling or disabling the communication with TeseoIII.
 */
static GNSS_StatusTypeDef Teseo_Bus_OnOff(GNSS_HandleTypeDef *pGNSS, uint8_t enable, int8_t nr_msg)
{
  if(pGNSS->bus == GNSS_BUS_I2C)
  {
    teseo_i2c_onoff(pGNSS, enable, nr_msg);
  }
  else
  {
    teseo_uart_rx_onoff(pGNSS, enable);
  }

  return GNSS_OK;
}

/*
 * Implements the API driver enabling the communication with TeseoIII.
 */
static GNSS_StatusTypeDef Teseo_Bus_Enable(GNSS_HandleTypeDef *pGNSS)
{
  if(pGNSS->bus == GNSS_BUS_I2C)
  {
    teseo_i2c_enable(pGNSS);
  }
  else
  {
    teseo_uart_rx_enable(pGNSS);
  }

  return GNSS_OK;
}

/*
 * Implements the API driver enabling the communication with TeseoIII.
 */
static GNSS_StatusTypeDef Teseo_Bus_Disable(GNSS_HandleTypeDef *pGNSS)
{
  if(pGNSS->bus == GNSS_BUS_I2C)
  {
    teseo_i2c_disable(pGNSS);
  }
  else
  {
    teseo_uart_rx_disable(pGNSS);
  }

  return GNSS_OK;
}

/*
 * Implements the API driver retrieving the buffer containing a message from TeseoIII.
 */
static const GNSS_MsgTypeDef *Teseo_Get_Buffer(GNSS_HandleTypeDef *pGNSS)
{
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)pGNSS->pData;
  
  return teseo_queue_claim_rd_buffer(teseo_io_data->pQueue);
}

/*
 * Implements the API driver releasing resource for TeseoIII messages.
 */
static GNSS_StatusTypeDef Teseo_Release_Buffer(GNSS_HandleTypeDef *pGNSS, const GNSS_MsgTypeDef *pGNSS_Msg)
{
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)pGNSS->pData;
  
  teseo_queue_release_rd_buffer(teseo_io_data->pQueue, pGNSS_Msg);

  return GNSS_OK;
}

/*
 * Implements the API driver sending a command to TeseoIII.
 */
static GNSS_StatusTypeDef Teseo_Bus_Write(GNSS_HandleTypeDef *pGNSS, uint8_t *pBuffer, uint16_t lenght, uint32_t timeout)
{
  (void)timeout;

  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)pGNSS->pData;
  
  if(pGNSS->bus == GNSS_BUS_I2C)
  {
    return ((HAL_I2C_Master_Transmit_IT(teseo_io_data->hi2c, (uint16_t)(Teseo_I2C_7bits_Addr << 1), pBuffer, lenght) == HAL_OK) ? GNSS_OK : GNSS_ERROR);
  }
  return ((HAL_UART_Transmit/*_IT*/(teseo_io_data->huart, pBuffer, lenght, 0x100000) == HAL_OK) ? GNSS_OK : GNSS_ERROR);
}

/*
 * Implements the API driver for UART/I2C receive complete callback.
 */
static void Teseo_Bus_RxCallback(GNSS_HandleTypeDef *pGNSS)
{
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)pGNSS->pData;

  if(pGNSS->bus == GNSS_BUS_I2C)
  {
    teseo_i2c_rx_callback_ok(teseo_io_data->hi2c);
  }
  else
  {
    teseo_uart_rx_callback_ok(teseo_io_data->huart);
  }
}

/*
 * Implements the API driver for UART/I2C receive error callback.
 */
static void Teseo_Bus_ErrorCallback(GNSS_HandleTypeDef *pGNSS)
{
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)pGNSS->pData;

  if(pGNSS->bus == GNSS_BUS_I2C)
  {
    teseo_i2c_rx_callback_error(teseo_io_data->hi2c);
  }
  else
  {
    teseo_uart_rx_callback_error(teseo_io_data->huart);
  }
}

/*
 * Implements the API driver for I2C receive abort callback.
 */
static void Teseo_Bus_AbortCallback(GNSS_HandleTypeDef *pGNSS)
{
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)pGNSS->pData;

  if(pGNSS->bus == GNSS_BUS_I2C)
  {
    teseo_i2c_rx_callback_abort(teseo_io_data->hi2c);
  }
}

/*
 * Implements the API driver function to start (or resume after a given timeout) communication via I2C.
 */
static void Teseo_Bus_BackgroundProcess(const GNSS_HandleTypeDef *pGNSS)
{
  if(pGNSS->bus == GNSS_BUS_I2C)
  {
    teseo_i2c_background_process();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
