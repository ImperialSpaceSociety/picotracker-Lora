/**
 ******************************************************************************
 * @file    LoRaTracker_batterycharger.c
 * @author  SRA - System Lab - Sensing & Connectivity Application Team
 * @version V2.1.1
 * @date    10-Oct-2019
 * @brief   This file provides a set of functions needed to manage the battery charger module
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

#include "LoRaTracker_batterycharger.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup LORATRACKER
 * @{
 */

/** @addtogroup LORATRACKER_STBC02 LORATRACKER STBC02 
 * @{
 */

/** @addtogroup STBC02_BATTERY_CHARGER 
 * @{
 */

/** @addtogroup STBC02_BATTERY_CHARGER_Private_Constants
 * @{
 */

 /**
 * @brief STBC02 status name and related toggling frequency (in Hz) of the nCHG pin
 * @note  The sequence must respect the order of stbc02_ChgState_TypeDef
 */
const stbc02_ChgStateNameAndFreq_TypeDef stbc02_ChgStateNameAndFreq[10] = {
  {"Not Valid Input", 0.0},
  {"Valid Input", 0.0},
  {"Vbat Low", 0.0},
  {"End Of Charge", 4.1},
  {"Charging Phase", 6.2},
  {"Overcharge Fault", 8.2},
  {"Charging Timeout", 10.2},
  {"Battery Voltage Below Vpre", 12.8},
  {"Charging Thermal Limitation", 14.2},
  {"Battery Temp Fault (or not present)", 16.2},
};

/**
 * @}
 */

/** @addtogroup STBC02_BATTERY_CHARGER_Private_Variables
 * @{
 */

static stbc02_SwCmd_TypeDef stbc02_SwCmdSel;                    //!< The selected STBC02 SW Cmd
static stbc02_SwState_TypeDef stbc02_SwState = idle;            //!< The state during STBC02 SW Cmd sending
static stbc02_ChgState_TypeDef stbc02_ChgState = NotValidInput; //!< The state of the STBC02
static float stbc02_ChgPinFreq;                                 //!< The toggling frequency of the STBC02 nCHG pin
uint32_t stbc02_ChgPinToggledTime = 0;                          //!< SysTick value when STBC02 nCHG pin is toggling
TIM_HandleTypeDef hstbc02_UsedTim;                              //!< Handler of the used timer

/**
 * @}
 */

/* Private Function_Prototypes -----------------------------------------------*/
void BC_IO_Init(void);
void BC_ChgPinFreqGet(void);
void BC_ChgPinFreq2ChgSts(void);
void BC_TIMx_Init(void);

/** @addtogroup STBC02_BATTERY_CHARGER_Private_Functions
 * @{
 */

/**
  * @brief  Initializes the GPIO used for the Li-Ion Battery Charger
  * @retval None
  */
void BC_IO_Init(void)
{
  BC_IO_CHG_Init();
  BC_IO_SW_SEL_Init();
}

/**
  * @brief Measure the toggling frequency of the charging pin of the STBC02
  * @note This function works with 1 ms as time base
  * @retval None
  */
void BC_ChgPinFreqGet(void)
{
  static uint32_t tk_now = 0, tk_prev = 0, tk_delta = 0;

  tk_now = STBC02_GetTick();
  tk_delta = tk_now - tk_prev;
  tk_prev = tk_now;
  
  stbc02_ChgPinFreq = 1000.0/((float)tk_delta);
}

/**
  * @brief Get the status of the STBC02 checking the toggling frequency of the charging pin of the STBC02
  * @retval None
  */
void BC_ChgPinFreq2ChgSts(void)
{
  stbc02_ChgState_TypeDef ChgState = NotValidInput;
  
  if (stbc02_ChgPinFreq > 0.00)
  {
    for (ChgState =  EndOfCharge; ChgState < BatteryTemperatureFault; ChgState++)
    {
      if ( (stbc02_ChgPinFreq < ((stbc02_ChgStateNameAndFreq[ChgState].freq + stbc02_ChgStateNameAndFreq[ChgState+1].freq)/2)) )
      {
        stbc02_ChgState = ChgState;
        break;
      }
    }
    if ( (stbc02_ChgPinFreq > ((stbc02_ChgStateNameAndFreq[ChgState-1].freq + stbc02_ChgStateNameAndFreq[ChgState].freq)/2)) )
    {
      stbc02_ChgState = ChgState;
    }
  }
}

/**
  * @brief  Initializes the used timer
  * @retval None
  */
void BC_TIMx_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  
  hstbc02_UsedTim.Instance = STBC02_USED_TIM;
  hstbc02_UsedTim.Init.Prescaler = 0;
  hstbc02_UsedTim.Init.CounterMode = TIM_COUNTERMODE_UP;
  hstbc02_UsedTim.Init.Period = (uint32_t)(STBC02_USED_TIM_CLKFreq * STBC02_USED_TIM_PERIOD);
#if USE_TIM_AUTORELOAD_PRELOAD
  hstbc02_UsedTim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
#endif //USE_TIM_AUTORELOAD_PRELOAD
  if (HAL_TIM_Base_Init(&hstbc02_UsedTim) != HAL_OK)
  {
    while(1);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&hstbc02_UsedTim, &sMasterConfig) != HAL_OK)
  {
    while(1);
  }
}

/**
 * @}
 */

/** @addtogroup STBC02_BATTERY_CHARGER_Public_Functions
 * @{
 */

/**
  * @brief Initialize the STBC02
  * @retval None
  */
void BSP_BC_Init(void)
{
  BSP_BC_InitCommon();

  /* Init the related GPIOs */
  BC_IO_Init();
}

/**
  * @brief Initialize the STBC02
  * @retval None
  */
void BSP_BC_InitCommon(void)
{
  /* Init the stbc02_ChgPinFreq value */
  stbc02_ChgPinFreq = 0.0;
  
  /* Init the time base */
  BC_TIMx_Init();
}

/**
  * @brief  Initializes the nCHG GPIO used for the Li-Ion Battery Charger
  * @retval None
  */
void BC_IO_CHG_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  STBC02_CHG_GPIO_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = STBC02_CHG_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  HAL_GPIO_Init(STBC02_CHG_GPIO_PORT, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(STBC02_CHG_EXTI_IRQn, STBC02_CHG_EXTI_IRQ_PP, 0);
  HAL_NVIC_EnableIRQ(STBC02_CHG_EXTI_IRQn);
}

/**
  * @brief  De-Initializes the nCHG GPIO used for the Li-Ion Battery Charger
  * @retval None
  */
void BC_IO_CHG_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  STBC02_CHG_GPIO_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = STBC02_CHG_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  HAL_GPIO_Init(STBC02_CHG_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief  Initializes the SW_SEL GPIO used for the Li-Ion Battery Charger
  * @retval None
  */
void BC_IO_SW_SEL_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  STBC02_SW_SEL_GPIO_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = STBC02_SW_SEL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_WritePin(STBC02_SW_SEL_GPIO_PORT, STBC02_SW_SEL_PIN, GPIO_PIN_RESET);
  HAL_GPIO_Init(STBC02_SW_SEL_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief Send a single wire command to the STBC02
  * @param stbc02_SwCmd The command to be sent
  * @retval 0 in case of success
  * @retval 1 in case of failure
  */
uint8_t BSP_BC_CmdSend(stbc02_SwCmd_TypeDef stbc02_SwCmd)
{
  uint32_t tk = STBC02_GetTick();
  DEBUG_SW_PIN_RESET();
  
  stbc02_SwCmdSel = stbc02_SwCmd;
  stbc02_SwState = start;
  
  /* Start the time base */
  HAL_TIM_Base_Start_IT(&hstbc02_UsedTim);
  
  
  while(stbc02_SwState != idle)
  {
    if ( (STBC02_GetTick() - tk) > 10000 )
      return 1;
  }
  
  /* Stop the time base */
  HAL_TIM_Base_Stop_IT(&hstbc02_UsedTim);
  
  return 0;
}

/**
  * @brief Single wire command manager for the STBC02
  * @note This function have to be called every 5 us
  * @retval None
  */
void BSP_BC_CmdMng(void)
{
  static uint16_t TIMx_Pulse = 0;                           //! Actual timer pulse number
  static uint16_t TIMx_PulseTCS = 0;                        //! Timer pulse number to change state
  static stbc02_SwState_TypeDef stbc02_sw_state_prv = idle; //! Previous state
  static uint8_t CmdPulse = 0;                              //! Cmd pulse number

  TIMx_Pulse++;
  switch (stbc02_SwState)
  {
  case idle:
    break;
  case start:
    HAL_GPIO_WritePin(STBC02_SW_SEL_GPIO_PORT, STBC02_SW_SEL_PIN, GPIO_PIN_SET);
    DEBUG_SW_PIN_SET();
    TIMx_PulseTCS = TIMx_Pulse + (350/TIMER_CORRECTION) - 1;
    stbc02_sw_state_prv = stbc02_SwState;
    stbc02_SwState = wait;
    break;
  case pulse_l:
  case pulse_h:
  case stop_l:
    HAL_GPIO_TogglePin(STBC02_SW_SEL_GPIO_PORT, STBC02_SW_SEL_PIN);
    DEBUG_SW_PIN_TOGGLE();
    TIMx_PulseTCS = TIMx_Pulse + (100/TIMER_CORRECTION) - 1;
    stbc02_sw_state_prv = stbc02_SwState;
    stbc02_SwState = wait;
    break;
  case stop_h:
    HAL_GPIO_TogglePin(STBC02_SW_SEL_GPIO_PORT, STBC02_SW_SEL_PIN);
    DEBUG_SW_PIN_TOGGLE();
    TIMx_PulseTCS = TIMx_Pulse + (500/TIMER_CORRECTION) - 1;
    stbc02_sw_state_prv = stbc02_SwState;
    stbc02_SwState = wait;
    break;
  case wait:
    if ( TIMx_Pulse >= TIMx_PulseTCS )
    {
      if ( stbc02_sw_state_prv == stop_h )
      {
        CmdPulse = 0;
        stbc02_SwState = idle;
        HAL_GPIO_WritePin(STBC02_SW_SEL_GPIO_PORT, STBC02_SW_SEL_PIN, GPIO_PIN_RESET);
        DEBUG_SW_PIN_RESET();
      }
      else
      {
        if ( stbc02_sw_state_prv == pulse_h )
        {
          CmdPulse++;
          if ( CmdPulse < stbc02_SwCmdSel )
          {
            stbc02_sw_state_prv = start;
          }
          else
            __NOP();
        }
        stbc02_SwState = ++stbc02_sw_state_prv;
        __NOP();
      }
    }
    break;
  default:
    stbc02_SwState = idle;
    break;
  }
}

/**
  * @brief Call the function for measuring the toggling frequency of the charging pin of the STBC02
  * @note Must be called when the charging pin of the STBC02 has toggled
  * @retval None
  */
void BSP_BC_ChgPinHasToggled(void)
{
  BC_ChgPinFreqGet();
  stbc02_ChgPinToggledTime = STBC02_GetTick();
}

/**
  * @brief Check for STBC02 nCHG toggling
  * @note Must be called on SysTick IRQ
  * @retval 0 if not toggling
  * @retval 1 if toggling
  */
uint8_t BSP_BC_IsChgPinToggling(void)
{
  GPIO_PinState stbc02_ChgPinState;
  
  if ( (STBC02_GetTick() - stbc02_ChgPinToggledTime) > 500 )
  {
    stbc02_ChgPinFreq = 0.00;
    stbc02_ChgPinState = HAL_GPIO_ReadPin(STBC02_CHG_GPIO_PORT, STBC02_CHG_PIN);
    if (stbc02_ChgPinState == GPIO_PIN_SET)
    {
      stbc02_ChgState = NotValidInput;
    }
    else
    {
      stbc02_ChgState = ValidInput;
    }
    return 0;
  }
  return 1;
}

/**
  * @brief  Get the status of the STBC02
  * @param  pstbc02_ChgState To be filled with the new value
  * @retval None
  */
void BSP_BC_GetState(stbc02_ChgState_TypeDef *pstbc02_ChgState)
{
  /* Check for STBC02 nCHG toggling */
  if (BSP_BC_IsChgPinToggling())
  {
    /* Get the status of the STBC02 */
    BC_ChgPinFreq2ChgSts();
  }
  
  *pstbc02_ChgState = stbc02_ChgState;
}

/**
 * @}
 */

/** @addtogroup STBC02_BATTERY_CHARGER_MSP_Functions
 * @{
 */

/**
  * @brief  Initializes the TIM Base MSP.
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{

  if(htim->Instance==STBC02_USED_TIM)
  {
    /* STBC02_USED_TIM clock enable */
    STBC02_USED_TIM_CLK_ENABLE();

    /* STBC02_USED_TIM interrupt Init */
    HAL_NVIC_SetPriority(STBC02_USED_TIM_IRQn, STBC02_USED_TIM_IRQ_PP, STBC02_USED_TIM_IRQ_SP);
    HAL_NVIC_EnableIRQ(STBC02_USED_TIM_IRQn);
  }
}

/**
  * @brief  DeInitialize TIM Base MSP.
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{

  if(htim->Instance==STBC02_USED_TIM)
  {
    /* Peripheral clock disable */
    STBC02_USED_TIM_CLK_DISABLE();

    /* STBC02_USED_TIM interrupt Deinit */
    HAL_NVIC_DisableIRQ(STBC02_USED_TIM_IRQn);
  }
} 

/**
 * @}
 */

/** @addtogroup STBC02_BATTERY_CHARGER_Interrupt_Callback_Functions
 * @{
 */

#if USE_TIM_IRQ_CALLBACK
/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == STBC02_USED_TIM)
  {
//BSP_BC_CmdMng();
  }
}
#endif //USE_TIM_IRQ_CALLBACK

#if USE_GPIO_IRQ_CALLBACK
/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
	case (STBC02_CHG_PIN):
      /* Report that CHG pin has toggled */
      BSP_BC_ChgPinHasToggled();
      break;
    
  default:
      break;
  }
}
#endif //USE_GPIO_IRQ_CALLBACK

/**
 * @}
 */

/** @addtogroup STBC02_BATTERY_CHARGER_Interrupt_Service_Routines
 * @{
 */
#if USE_TIM_IRQ_HANDLER
/**
* @brief This function handles STBC02_USED_TIM global interrupt.
*/
void STBC02_USED_TIM_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&hstbc02_UsedTim);
}
#endif //USE_TIM_IRQ_HANDLER

#if USE_GPIO_IRQ_HANDLER
/**
  * @brief This function handles EXTI for STBC02_CHG_PIN interrupts.
  */
void STBC02_CHG_EXTI_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(STBC02_CHG_PIN);
}
#endif // USE_GPIO_IRQ_HANDLER

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
