/**
  ******************************************************************************
  * @file    debug.c
  * @author  MCD Application Team
  * @version V1.1.5
  * @date    30-March-2018
  * @brief   This file contains a set of debug functions
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef DEBUG
uint8_t bDebuggerConnected = 0;

/**
  * @brief It checks the debugger connection
  * @param None
  * @retval None
  */
void CheckDebuggerConnection()
{
  __IO uint32_t uwMyTick = 0;
  /* Enable the GPIO_A Clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  uint32_t endchecktick ;
  GPIO_PinState io_stat;
  
  io_stat = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13);
  endchecktick = 1000000 + uwMyTick;
  while(io_stat == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13))
  {
    if(uwMyTick++ > endchecktick)
    {
      return;
    }
  }

  io_stat = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13);
  endchecktick = 1000000 + uwMyTick;
  while(io_stat == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13))
  {
    if(uwMyTick++ > endchecktick)
    {
      return;
    }
  }

  io_stat = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13);
  endchecktick = 1000000 + uwMyTick;
  while(io_stat == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13))
  {
    if(uwMyTick++ > endchecktick)
    {
      return;
    }
  }
  
  bDebuggerConnected = 1;
}
#endif //DEBUG

/**
  * @brief Initializes the debug
  * @param None
  * @retval None
  */
void DBG_Init( void )
{
#ifdef DEBUG

  __HAL_RCC_DBGMCU_CLK_ENABLE( );

  HAL_DBGMCU_EnableDBGSleepMode( );
  HAL_DBGMCU_EnableDBGStopMode( );
  HAL_DBGMCU_EnableDBGStandbyMode( );
  
#if CHECK_DEBUGGER_CONNECTION
  CheckDebuggerConnection();
#endif //CHECK_DEBUGGER_CONNECTION

#else /* DEBUG */
  /* sw interface off*/
  GPIO_InitTypeDef GPIO_InitStructure ={0};
  
  GPIO_InitStructure.Mode   = GPIO_MODE_ANALOG;
  GPIO_InitStructure.Pull   = GPIO_NOPULL;
  GPIO_InitStructure.Pin    = (GPIO_PIN_13 | GPIO_PIN_14);
  __GPIOA_CLK_ENABLE() ;  
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
  __GPIOA_CLK_DISABLE() ;
  
  __HAL_RCC_DBGMCU_CLK_ENABLE( );
  HAL_DBGMCU_DisableDBGSleepMode( );
  HAL_DBGMCU_DisableDBGStopMode( );
  HAL_DBGMCU_DisableDBGStandbyMode( );
  __HAL_RCC_DBGMCU_CLK_DISABLE( );
#endif
}

/**
  * @brief Error_Handler
  * @param None
  * @retval None
  */
void Error_Handler(void)
{
#ifdef BLOCK_ON_ERROR
  uint8_t bBlockOnError = 1;
#else //BLOCK_ON_ERROR
  uint8_t bBlockOnError = 0;
#endif //BLOCK_ON_ERROR
  do
  {
    PRINTF("Error_Handler\n\r");
    HAL_Delay(1000);
  }
  while(bBlockOnError);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


