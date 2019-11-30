/**
 ******************************************************************************
 * @file    LoRaTracker_batterycharger.h
 * @author  SRA - System Lab - Sensing & Connectivity Application Team
 * @version V2.1.1
 * @date    10-Oct-2019
 * @brief   This file contains definitions for LoRaTracker_batterycharger.c
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LORATRACKER_BATTERYCHARGER_H
#define __LORATRACKER_BATTERYCHARGER_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "hw.h"
#include <stdbool.h>

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STBC02 
 * @{
 */

/** @addtogroup STBC02_BATTERY_CHARGER 
 * @{
 */

/** @addtogroup STBC02_BATTERY_CHARGER_Public_Defines
 * @{
 */

#define STBC02_GetTick()                      HAL_GetTick()  //!< Get SysTick macro
   
/*! \name Timer Peripheral
*/
//@{
#define TIMER_CORRECTION                     50
#define STBC02_USED_TIM_PERIOD                50e-6 // s
#define USE_TIM_AUTORELOAD_PRELOAD              0 //set to 1 if the used timer has this feature
#define STBC02_USED_TIM                       TIM22
#define STBC02_USED_TIM_CLK_ENABLE()          __HAL_RCC_TIM22_CLK_ENABLE()
#define STBC02_USED_TIM_CLK_DISABLE()         __HAL_RCC_TIM22_CLK_DISABLE()
#define STBC02_USED_TIM_CLKFreq               (HAL_RCC_GetPCLK1Freq() * (((READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos) < 4) ? 1 : 2))
#define STBC02_USED_TIM_IRQn                  TIM22_IRQn
#define STBC02_USED_TIM_IRQ_PP                14
#define STBC02_USED_TIM_IRQ_SP                0
#define STBC02_USED_TIM_IRQHandler            TIM22_IRQHandler
#define USE_TIM_IRQ_HANDLER                   1  //set to 1 if you want to use the implemented irq handler, 0 to use the one in your own files
#define USE_TIM_IRQ_CALLBACK                  1  //set to 1 if you want to use the implemented irq callback, 0 to use the one in your own files
#define DEBUG_SW_PIN_SET()
#define DEBUG_SW_PIN_RESET()
#define DEBUG_SW_PIN_TOGGLE()

//@}
   
/*! \name GPIO for STBC02 Load switch selection input
*/
//@{
#define STBC02_SW_SEL_PIN                     GPIO_PIN_12
#define STBC02_SW_SEL_GPIO_PORT               GPIOB
#define STBC02_SW_SEL_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define STBC02_SW_SEL_GPIO_CLK_DISABLE()      __HAL_RCC_GPIOB_CLK_DISABLE()
//@}

/*! \name GPIO for STBC02 Charging/fault flag
*/
//@{
#define STBC02_CHG_PIN                        GPIO_PIN_3
#define STBC02_CHG_GPIO_PORT                  GPIOA
#define STBC02_CHG_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define STBC02_CHG_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()
#define STBC02_CHG_EXTI_IRQn                  EXTI2_3_IRQn
#define STBC02_CHG_EXTI_IRQ_PP                0
#define STBC02_CHG_EXTI_IRQ_SP                0
#define STBC02_CHG_EXTI_IRQHandler            EXTI2_3_IRQHandler
#define USE_GPIO_IRQ_HANDLER                  0  //set to 1 if you want to use the implemented irq handler, 0 to use the one in your own files
#define USE_GPIO_IRQ_CALLBACK                 0  //set to 1 if you want to use the implemented irq callback, 0 to use the one in your own files
//@}

/**
 * @}
 */
  
/** @addtogroup STBC02_BATTERY_CHARGER_Public_Types
 * @{
 */

/**
  * @brief Device state
  */
typedef enum
{
  NotValidInput = 0,
  ValidInput,
  VbatLow,
  EndOfCharge,
  ChargingPhase,
  OverchargeFault,
  ChargingTimeout,
  BatteryVoltageBelowVpre,
  ChargingThermalLimitation,
  BatteryTemperatureFault
} stbc02_ChgState_TypeDef;

/**
  * @brief SW selection pulse number
  */
typedef enum
{
  SW1_OA_OFF              = 1,
  SW1_OA_ON               = 2,
  SW1_OB_OFF              = 3,
  SW1_OB_ON               = 4,
  SW2_OA_OFF              = 5,
  SW2_OA_ON               = 6,
  SW2_OB_OFF              = 7,
  SW2_OB_ON               = 8,
  BATMS_OFF               = 9,
  BATMS_ON                = 10,
  IEND_OFF                = 11,
  IEND_5_PC_IFAST         = 12,
  IEND_2_5_PC_IFAST       = 13,
  IBAT_OCP_900_mA         = 14,
  IBAT_OCP_450_mA         = 15,
  IBAT_OCP_250_mA         = 16,
  IBAT_OCP_100_mA         = 17,
  VFLOAT_ADJ_OFF          = 18,
  VFLOAT_ADJ_PLUS_50_mV   = 19,
  VFLOAT_ADJ_PLUS_100_mV  = 20,
  VFLOAT_ADJ_PLUS_150_mV  = 21,
  VFLOAT_ADJ_PLUS_200_mV  = 22,
  SHIPPING_MODE_ON        = 23,
  AUTORECH_OFF            = 24,
  AUTORECH_ON             = 25,
  WATCHDOG_OFF            = 26,
  WATCHDOG_ON             = 27,
  IFAST_IPRE_50_PC_OFF    = 28,
  IFAST_IPRE_50_PC_ON     = 29
} stbc02_SwCmd_TypeDef;

/**
  * @brief SW pulse state
  */
typedef enum
{
  idle=0,
  start=1,
  pulse_l=2,
  pulse_h=3,
  stop_l=4,
  stop_h=5,
  wait=6
} stbc02_SwState_TypeDef;

/**
  * @brief Device state structure as name and nominal frequency
  */
typedef struct
{
  char *name;
  float freq;
} stbc02_ChgStateNameAndFreq_TypeDef;

/**
 * @}
 */

/** @addtogroup STBC02_BATTERY_CHARGER_Public_Variables
 * @{
 */

extern TIM_HandleTypeDef hstbc02_UsedTim;

/**
 * @}
 */

/* Public Function_Prototypes -----------------------------------------------*/
void BSP_BC_Init(void);
void BSP_BC_InitCommon(void);
void BC_IO_CHG_Init(void);
void BC_IO_CHG_DeInit(void);
void BC_IO_SW_SEL_Init(void);
uint8_t BSP_BC_CmdSend(stbc02_SwCmd_TypeDef stbc02_SwCmd);
void BSP_BC_CmdMng(void);
void BSP_BC_ChgPinHasToggled(void);
uint8_t BSP_BC_IsChgPinToggling(void);
void BSP_BC_GetState(stbc02_ChgState_TypeDef *pstbc02_ChgState);
 
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
#endif /* __LORATRACKER_BATTERYCHARGER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
