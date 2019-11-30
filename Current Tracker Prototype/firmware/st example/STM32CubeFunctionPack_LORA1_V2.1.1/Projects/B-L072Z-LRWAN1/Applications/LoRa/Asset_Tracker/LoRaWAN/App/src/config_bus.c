/**
  ******************************************************************************
  * @file    config_bus.c
  * @author  AST/CL
  * @version V2.0.0
  * @date    Apr-2018
  * @brief   This file contains definitions and prototypes for configuring the peripherals (UART/I2C)
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

/** @addtogroup PROJECTS PROJECTS
  * @{
  */
   
/** @addtogroup B-L072Z-LRWAN1 B-L072Z-LRWAN1
  * @{
  */  
   
/** @addtogroup B-L072Z-LRWAN1_ASSET_TRACKER Asset Tracker
  * @{
  */    
    
/** @addtogroup B-L072Z-LRWAN1_LoRaWAN LoRaWAN
  * @{
 */

/** @addtogroup B-L072Z-LRWAN1_BSP_INTERFACE BSP Interface
  * @{
 */  

/** @addtogroup B-L072Z-LRWAN1_SimOSGetPos SimOSGetPos
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "config_bus.h"
#include "gnss_app_cfg.h"
#ifdef LORA_SMART_TRACKER
#include "LoRaTracker_gnss.h"
#else //LORA_SMART_TRACKER
#include "x_nucleo_gnss1a1.h"
#endif //LORA_SMART_TRACKER

/* Global variables ----------------------------------------------------------*/
extern GNSS_HandleTypeDef pGNSS;
extern void Error_Handler(void);
extern __IO uint32_t uwTick;

I2C_HandleTypeDef  hi2c;
UART_HandleTypeDef huart;
UART_HandleTypeDef io_huart;

/* Exported functions --------------------------------------------------------*/

void GNSS_I2C_Init(void)
{
  hi2c.Instance = GNSS_I2C_INSTANCE;
#ifdef USE_STM32F4XX_NUCLEO  
  hi2c.Init.ClockSpeed = GNSS_I2C_CLK_SPEED;
  hi2c.Init.DutyCycle = GNSS_I2C_DUTY_CYCLE;
#endif /* USE_STM32F4XX_NUCLEO */

#ifdef USE_STM32L4XX_NUCLEO
  hi2c.Init.Timing = GNSS_I2C_CLK_SPEED;
#endif /* USE_STM32L4XX_NUCLEO */
  
#if (defined (USE_STM32L0XX_NUCLEO) || defined (USE_B_L072Z_LRWAN1) || defined (LORA_SMART_TRACKER))
  hi2c.Init.Timing = GNSS_I2C_CLK_SPEED;
#endif /* USE_STM32L0XX_NUCLEO */

  hi2c.Init.OwnAddress1 = GNSS_I2C_OWN_ADDRESS1;
  hi2c.Init.AddressingMode = GNSS_I2C_ADDRESSING_MODE;
  hi2c.Init.DualAddressMode = GNSS_I2C_DUAL_ADDRESS_MODE;
  hi2c.Init.OwnAddress2 = GNSS_I2C_OWN_ADDRESS2;
  hi2c.Init.GeneralCallMode = GNSS_I2C_GENERAL_CALL_MODE;
  hi2c.Init.NoStretchMode = GNSS_I2C_NO_STRETCH_MODE;
  if (HAL_I2C_Init(&hi2c) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
 * @brief  Wrapper to de-init UART peripheral.
 * @param  None
 * @retval None
 */
void GNSS_UART_DeInit(void)
{
  if (HAL_UART_DeInit(&huart) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
 * @brief  Wrapper to de-init I2C peripheral.
 * @param  None
 * @retval None
 */
void GNSS_I2C_DeInit(void)
{
  if (HAL_I2C_DeInit(&hi2c) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  Wrapper to init UART peripheral.
 * @param  BaudRate GNSS UART baud rate
 * @retval None
 */
void GNSS_UART_Init(uint32_t BaudRate)
{
  huart.Instance = GNSS_UART_INSTANCE;
  huart.Init.BaudRate = BaudRate;
  huart.Init.WordLength = GNSS_UART_WORD_LENGTH;
  huart.Init.StopBits = GNSS_UART_STOP_BITS;
  huart.Init.Parity = GNSS_UART_PARITY;
  huart.Init.Mode = GNSS_UART_MODE;
  huart.Init.HwFlowCtl = GNSS_UART_HW_FLOW_CTL;
  huart.Init.OverSampling = GNSS_UART_OVER_SAMPLING;
  if (HAL_UART_Init(&huart) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  Wrapper to de-init (console) UART peripheral.
 * @param  None
 * @retval None
 */
void IO_UART_Init(void)
{
  io_huart.Instance = IO_UART_INSTANCE;
  io_huart.Init.BaudRate = IO_UART_BAUD_RATE;
  io_huart.Init.WordLength = IO_UART_WORD_LENGTH;
  io_huart.Init.StopBits = IO_UART_STOP_BITS;
  io_huart.Init.Parity = IO_UART_PARITY;
  io_huart.Init.Mode = IO_UART_MODE;
  io_huart.Init.HwFlowCtl = IO_UART_HW_FLOW_CTL;
  io_huart.Init.OverSampling = IO_UART_OVER_SAMPLING;
  if (HAL_UART_Init(&io_huart) != HAL_OK)
  {
    Error_Handler();
  }
}

#if (configUSE_I2C == 1)

/**
  * @brief  Master Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  (void)hi2c;

  GNSS_Bus_RxCallback(&pGNSS);
}


/**
  * @brief  I2C error callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
  (void)hi2c;

  GNSS_Bus_ErrorCallback(&pGNSS);
}


/**
  * @brief  I2C abort callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c)
{
  (void)hi2c;

  GNSS_Bus_AbortCallback(&pGNSS);
}


/**
  * @brief This function is called to increment  a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in Systick ISR.
  * @retval None
  */
void HAL_IncTick(void)
{
  uwTick++;
  GNSS_Bus_BackgroundProcess(&pGNSS);
}

#else

#if 0
/**
  * @brief Rx Transfer completed callback.
  * @param huart: UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  (void)huart;

  GNSS_Bus_RxCallback(&pGNSS);
}
#endif

/**
  * @brief UART error callback.
  * @param huart: UART handle.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  (void)huart;

  GNSS_Bus_ErrorCallback(&pGNSS);
}

#endif /* configUSE_I2C */

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

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
