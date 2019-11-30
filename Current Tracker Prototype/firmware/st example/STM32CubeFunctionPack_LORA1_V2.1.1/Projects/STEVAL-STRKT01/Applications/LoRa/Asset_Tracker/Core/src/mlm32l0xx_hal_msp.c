/**
  ****************************************************************************
  * @file    mlm32l0xx_hal_msp.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    10-July-2018
  * @brief   msp file for HAL
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
#include "hw.h"
#include "vcom.h"
#include "timeServer.h"
#include "config_bus.h"

/* when fast wake up is enabled, the mcu wakes up in ~20us  * and 
 * does not wait for the VREFINT to be settled. THis is ok for 
 * most of the case except when adc must be used in this case before 
 *starting the adc, you must make sure VREFINT is settled*/
#define ENABLE_FAST_WAKEUP

  
/** @addtogroup PROJECTS PROJECTS
  * @{
  */
   
/** @addtogroup STEVAL-STRKT01 STEVAL-STRKT01
  * @{
  */  
   
/** @addtogroup STEVAL-STRKT01_ASSET_TRACKER Asset Tracker
  * @{
  */    
    
/** @addtogroup STEVAL-STRKT01_Core Core
  * @{
 */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/** @addtogroup Core_Exported_Functions Core Exported Functions
  * @{
 */

/**
  * @brief This function configures the source of the time base.
  * @brief  don't enable systick
  * @param TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
   /* Return function status */
  return HAL_OK;
}

/**
  * @brief This function provides delay (in ms)
  * @param Delay: specifies the delay time length, in milliseconds.
  * @retval None
  */
void HAL_Delay(__IO uint32_t Delay)
{
  HW_RTC_DelayMs( Delay ); /* based on RTC */
}

/**
  * @brief Provides a tick value in millisecond.
  * @retval tick value
  */
uint32_t HAL_GetTick(void)
{
  return HW_RTC_GetTimerValue();
}

/**
  * @brief  Initializes the MSP.
  * @retval None
  */
void HAL_MspInit(void)
{
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* Disable the Power Voltage Detector */
  HAL_PWR_DisablePVD( ); 

  /* Enables the Ultra Low Power mode */
  HAL_PWREx_EnableUltraLowPower( );
  
  __HAL_FLASH_SLEEP_POWERDOWN_ENABLE();
  
  /*In debug mode, e.g. when DBGMCU is activated, Arm core has always clocks
   * And will not wait that the FLACH is ready to be read. It can miss in this 
   * case the first instruction. To overcome this issue, the flash remain clcoked during sleep mode
   */
  DBG( __HAL_FLASH_SLEEP_POWERDOWN_DISABLE(); );
  
#ifdef ENABLE_FAST_WAKEUP
  /*Enable fast wakeUp*/  
  HAL_PWREx_EnableFastWakeUp( );
#else  
  HAL_PWREx_DisableFastWakeUp( );
#endif

  HW_GpioInit( );
}

/**
  * @brief RTC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param hrtc: RTC handle pointer
  * @note  Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select 
  *        the RTC clock source; in this case the Backup domain will be reset in  
  *        order to modify the RTC Clock source, as consequence RTC registers (including 
  *        the backup registers) and RCC_CSR register are set to their reset values.  
  * @retval None
  */
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

  /*##-1- Configue the RTC clock soucre ######################################*/
  /* -a- Enable LSE Oscillator */
  RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* -b- Select LSE as RTC clock source */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  { 
    Error_Handler();
  }

  /*##-2- Enable the RTC peripheral Clock ####################################*/
  /* Enable RTC Clock */
  __HAL_RCC_RTC_ENABLE();
  
  /*##-3- Configure the NVIC for RTC Alarm ###################################*/
  HAL_NVIC_SetPriority(RTC_Alarm_IRQn, RTC_Alarm_IRQ_PP, RTC_Alarm_IRQ_SP);
  HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

/**
  * @brief RTC MSP De-Initialization 
  *        This function freeze the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc)
{
  /* Reset peripherals */
  __HAL_RCC_RTC_DISABLE();
}


/**
  * @brief  Alarm A callback.
  * @param  hrtc: RTC handle
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  TimerIrqHandler( );
}

/**
  * @brief  Gets IRQ number as a function of the GPIO_Pin.
  * @param  GPIO_Pin: Specifies the pins connected to the EXTI line.
  * @retval IRQ number
  */
IRQn_Type MSP_GetIRQn( uint16_t GPIO_Pin)
{
  switch( GPIO_Pin )
  {
    case GPIO_PIN_0:  
    case GPIO_PIN_1:  return EXTI0_1_IRQn;
    case GPIO_PIN_2: 
    case GPIO_PIN_3:  return EXTI2_3_IRQn;
    case GPIO_PIN_4:  
    case GPIO_PIN_5:  
    case GPIO_PIN_6:
    case GPIO_PIN_7:
    case GPIO_PIN_8:
    case GPIO_PIN_9:  
    case GPIO_PIN_10:
    case GPIO_PIN_11:
    case GPIO_PIN_12:
    case GPIO_PIN_13:
    case GPIO_PIN_14:
    case GPIO_PIN_15: 
    default: return EXTI4_15_IRQn;
  }
}

#if 1
#if defined(USE_AUX_UART_LOG)
DMA_HandleTypeDef hdma_usart2_tx;
#endif //defined(USE_AUX_UART_LOG)

/**
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - NVIC configuration for UART interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_InitStruct;
    
  if(huart->Instance==GNSS_UART_INSTANCE)
  {
    /* Peripheral clock enable */
    GNSS_UART_CLK_ENABLE();
    GNSS_TX_GPIO_CLK_ENABLE();
    GNSS_RX_GPIO_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GNSS_UART_RX|GNSS_UART_TX;
    GPIO_InitStruct.Mode = GNSS_UART_PIN_MODE;
    GPIO_InitStruct.Pull = GNSS_UART_PULL;
    GPIO_InitStruct.Speed = GNSS_UART_SPEED;
    GPIO_InitStruct.Alternate = GNSS_UART_ALTERNATE;
    HAL_GPIO_Init(GNSS_UART_RXTX_PORT, &GPIO_InitStruct);

    /* Configure the NVIC for USART1 */
    HAL_NVIC_SetPriority(GNSS_UART_IRQn, GNSS_UART_IRQ_PP, GNSS_UART_IRQ_SP);
    HAL_NVIC_EnableIRQ(GNSS_UART_IRQn);

  }
  else
  {
#ifdef LORA_SMART_TRACKER
#if defined(USE_AUX_UART_LOG)
  __GPIOA_CLK_ENABLE(); 
  
  /**USART2 GPIO Configuration    
  PA2     ------> USART2_TX 
  */ 
  GPIO_InitStruct.Pin = GPIO_PIN_2; 
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; 
  GPIO_InitStruct.Pull = GPIO_NOPULL; 
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; 
  GPIO_InitStruct.Alternate = GPIO_AF4_USART2; 
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
  
  
    /* USART2 DMA Init */ 
  /* Enable USARTx clock */ 
    USARTx_CLK_ENABLE(); 
  
  /* USART2_TX Init */ 
    hdma_usart2_tx.Instance = DMA1_Channel4; 
    hdma_usart2_tx.Init.Request = DMA_REQUEST_4; 
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH; 
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE; 
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE; 
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE; 
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE; 
    hdma_usart2_tx.Init.Mode = DMA_NORMAL; 
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW; 
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK) 
    { 
      Error_Handler(); 
    } 
    __HAL_LINKDMA(huart,hdmatx,hdma_usart2_tx); 
    /* USART2 interrupt Init */ 
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0); 
    HAL_NVIC_EnableIRQ(USART2_IRQn);  
  
#else //defined(USE_AUX_UART_LOG)
    Error_Handler();
#endif //defined(USE_AUX_UART_LOG)
#else //LORA_SMART_TRACKER
    static DMA_HandleTypeDef hdma_tx;
    
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    USARTx_TX_GPIO_CLK_ENABLE();
    USARTx_RX_GPIO_CLK_ENABLE();
    
    /* Enable USARTx clock */
    USARTx_CLK_ENABLE();
    
    /* Enable DMA clock */
    DMAx_CLK_ENABLE();
    
    /*##-2- Configure peripheral GPIO ##########################################*/  
    /* UART  pin configuration  */
    vcom_IoInit();
    
    /*##-3- Configure the DMA ##################################################*/
    /* Configure the DMA handler for Transmission process */
    hdma_tx.Instance                 = USARTx_TX_DMA_CHANNEL;
    hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    hdma_tx.Init.Mode                = DMA_NORMAL;
    hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;
#ifndef STM32L152xE
    hdma_tx.Init.Request             = USARTx_TX_DMA_REQUEST;
#endif
    HAL_DMA_Init(&hdma_tx);
    
    /* Associate the initialized DMA handle to the UART handle */
    __HAL_LINKDMA(huart, hdmatx, hdma_tx);
    
    /*##-4- Configure the NVIC for DMA #########################################*/
    /* NVIC configuration for DMA transfer complete interrupt (USART1_TX) */
    HAL_NVIC_SetPriority(USARTx_DMA_TX_IRQn, USARTx_DMA_Priority, 1);
    HAL_NVIC_EnableIRQ(USARTx_DMA_TX_IRQn);
    
    /* NVIC for USART, to catch the TX complete */
    HAL_NVIC_SetPriority(USARTx_IRQn, USARTx_Priority, 1);
    HAL_NVIC_EnableIRQ(USARTx_IRQn);
#endif //LORA_SMART_TRACKER
  }
}

/**
  * @brief UART MSP DeInit
  * @param huart: uart handle
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  if(huart->Instance==GNSS_UART_INSTANCE)
  {
    /* Peripheral clock disable */
    GNSS_UART_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GNSS_UART_RXTX_PORT, GNSS_UART_TX|GNSS_UART_RX);

    GPIO_InitStruct.Pin = GNSS_UART_RX|GNSS_UART_TX;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GNSS_UART_RXTX_PORT, &GPIO_InitStruct);

    /* USART1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(GNSS_UART_IRQn);
  }
  else
  {
#ifdef LORA_SMART_TRACKER
    Error_Handler();
#else //LORA_SMART_TRACKER
    vcom_IoDeInit( );
    /*##-1- Reset peripherals ##################################################*/
    USARTx_FORCE_RESET();
    USARTx_RELEASE_RESET();
    
    /*##-3- Disable the DMA #####################################################*/
    /* De-Initialize the DMA channel associated to reception process */
    if(huart->hdmarx != 0)
    {
      HAL_DMA_DeInit(huart->hdmarx);
    }
    /* De-Initialize the DMA channel associated to transmission process */
    if(huart->hdmatx != 0)
    {
      HAL_DMA_DeInit(huart->hdmatx);
    }  
    
    /*##-4- Disable the NVIC for DMA ###########################################*/
    HAL_NVIC_DisableIRQ(USARTx_DMA_TX_IRQn);
#endif //LORA_SMART_TRACKER
  }
}
#endif


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
