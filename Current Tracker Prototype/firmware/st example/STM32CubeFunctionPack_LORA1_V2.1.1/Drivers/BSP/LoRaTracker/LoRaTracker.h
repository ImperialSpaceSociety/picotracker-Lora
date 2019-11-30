/**
  ******************************************************************************
  * @file    loratracker.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-November-2016
  * @brief   This file contains definitions for:
  *          LEDs and push-button available on LoRa tracker 
  *          from STMicroelectronics
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#ifndef __LORA_TRACKER_H
#define __LORA_TRACKER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stdlib.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup LORATRACKER LORATRACKER
  * @{
  */

/** @addtogroup LORATRACKER_LOWLEVEL LORATRACKER LOW LEVEL
  * @{
  */
      
/** @defgroup LORATRACKER_LOWLEVEL_Exported_Types       Exported Types
  * @{
  */ 
#ifdef LORA_SMART_TRACKER
typedef enum 
{
  LED1 = 0,
  LED_WHITE = LED1,
} Led_TypeDef;

#define LED2            LED1
#define LED3            LED1
#define LED4            LED1
#define LED_RED1        LED1
#define LED_BLUE        LED1
#define LED_RED2        LED1

#else //LORA_SMART_TRACKER
typedef enum 
{
  LED1 = 0,
  LED_GREEN = LED1,
  LED2 = 1,
  LED_RED1 =LED2,
  LED3 = 2,
  LED_BLUE =LED3,
  LED4 = 3,
  LED_RED2 =LED4
} Led_TypeDef;
#endif //LORA_SMART_TRACKER

typedef enum 
{  
  BUTTON_USER = 0,
  /* Alias */
#ifdef LORA_SMART_TRACKER
  BUTTON_KEY  = BUTTON_USER,
  BUTTON_WAKE = 1
#else //LORA_SMART_TRACKER
  BUTTON_KEY  = BUTTON_USER
#endif //LORA_SMART_TRACKER
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef; 

/**
  * @}
  */ 


/** @defgroup LORATRACKER_LOWLEVEL_Exported_Constants   Exported Constants 
  * @{
  */ 

/**
  * @}
  */ 


/** @addtogroup LORATRACKER_LOWLEVEL_LED        LED
  * @{
  */

#ifdef LORA_SMART_TRACKER

#define LEDn                               1
#define LED1_PIN                           GPIO_PIN_2
#define LED1_GPIO_PORT                     GPIOB
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

#else //LORA_SMART_TRACKER

#define LEDn                               4
#define LED1_PIN                           GPIO_PIN_5
#define LED1_GPIO_PORT                     GPIOB
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

#define LED2_PIN                           GPIO_PIN_5
#define LED2_GPIO_PORT                     GPIOA
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()  
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define LED3_PIN                           GPIO_PIN_6
#define LED3_GPIO_PORT                     GPIOB
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

#define LED4_PIN                           GPIO_PIN_7
#define LED4_GPIO_PORT                     GPIOB
#define LED4_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED4_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()
  
#endif //LORA_SMART_TRACKER

#ifdef LORA_SMART_TRACKER
#define LEDx_GPIO_CLK_ENABLE(__INDEX__)    do { \
                                                switch( __INDEX__ ) \
                                                {\
                                                  case LED1: \
                                                    LED1_GPIO_CLK_ENABLE();   \
                                                    break;\
                                                  default:\
                                                    break;\
                                                }\
                                              } while(0)
#else //LORA_SMART_TRACKER
#define LEDx_GPIO_CLK_ENABLE(__INDEX__)    do { \
                                                switch( __INDEX__ ) \
                                                {\
                                                  case LED1: \
                                                    LED1_GPIO_CLK_ENABLE();   \
                                                    break;\
                                                  case LED2: \
                                                    LED2_GPIO_CLK_ENABLE();   \
                                                    break;\
                                                  case LED3: \
                                                    LED3_GPIO_CLK_ENABLE();   \
                                                    break;\
                                                  case LED4: \
                                                    LED4_GPIO_CLK_ENABLE();   \
                                                    break;\
                                                  default:\
                                                    break;\
                                                }\
                                              } while(0)
#endif //LORA_SMART_TRACKER
                                                
#ifdef LORA_SMART_TRACKER
#define LEDx_GPIO_CLK_DISABLE(__INDEX__)   do { \
                                                switch( __INDEX__ ) \
                                                {\
                                                  case LED1: \
                                                    LED1_GPIO_CLK_DISABLE();   \
                                                    break;\
                                                default:\
                                                    break;\
                                                }\
                                              } while(0)
#else //LORA_SMART_TRACKER
#define LEDx_GPIO_CLK_DISABLE(__INDEX__)   do { \
                                                switch( __INDEX__ ) \
                                                {\
                                                  case LED1: \
                                                    LED1_GPIO_CLK_DISABLE();   \
                                                    break;\
                                                  case LED2: \
                                                    LED2_GPIO_CLK_DISABLE();   \
                                                    break;\
                                                  case LED3: \
                                                    LED3_GPIO_CLK_DISABLE();   \
                                                    break;\
                                                  case LED4: \
                                                    LED4_GPIO_CLK_DISABLE();   \
                                                    break;\
                                                  default:\
                                                    break;\
                                                }\
                                              } while(0)
#endif //LORA_SMART_TRACKER
                                                
/**
  * @}
  */ 
  
                                                
/** @addtogroup LORATRACKER_LOWLEVEL_BUTTON     BUTTON
  * @{
  */  
#ifdef LORA_SMART_TRACKER
#define BUTTONn                            2
#else //LORA_SMART_TRACKER
#define BUTTONn                            1
#endif //LORA_SMART_TRACKER

/**
  * @brief Key push-button
  */
#ifdef LORA_SMART_TRACKER
#define USER_BUTTON_PIN                         GPIO_PIN_2
#define USER_BUTTON_GPIO_PORT                   GPIOA
#define USER_BUTTON_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()   
#define USER_BUTTON_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()  
#define USER_BUTTON_EXTI_LINE                   GPIO_PIN_2
#define USER_BUTTON_EXTI_IRQn                   EXTI2_3_IRQn
#define USER_BUTTON_RISING_FALLING              GPIO_MODE_IT_FALLING
#define USER_BUTTON_LEVEL_ACTIVE                GPIO_PIN_RESET

#define WAKE_BUTTON_PIN                         GPIO_PIN_7
#define WAKE_BUTTON_GPIO_PORT                   GPIOB
#define WAKE_BUTTON_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()   
#define WAKE_BUTTON_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()  
#define WAKE_BUTTON_EXTI_LINE                   GPIO_PIN_7
#define WAKE_BUTTON_EXTI_IRQn                   EXTI4_15_IRQn
#define WAKE_BUTTON_RISING_FALLING              GPIO_MODE_IT_RISING
#define WAKE_BUTTON_LEVEL_ACTIVE                GPIO_PIN_SET
#else //LORA_SMART_TRACKER
#define USER_BUTTON_PIN                         GPIO_PIN_2
#define USER_BUTTON_GPIO_PORT                   GPIOB
#define USER_BUTTON_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()   
#define USER_BUTTON_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()  
#define USER_BUTTON_EXTI_LINE                   GPIO_PIN_2
#define USER_BUTTON_EXTI_IRQn                   EXTI2_3_IRQn
#define USER_BUTTON_RISING_FALLING              GPIO_MODE_IT_FALLING
#define USER_BUTTON_LEVEL_ACTIVE                GPIO_PIN_RESET
#endif //LORA_SMART_TRACKER

/* Aliases */
#define KEY_BUTTON_PIN                          USER_BUTTON_PIN
#define KEY_BUTTON_GPIO_PORT                    USER_BUTTON_GPIO_PORT
#define KEY_BUTTON_GPIO_CLK_ENABLE()            USER_BUTTON_GPIO_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()           USER_BUTTON_GPIO_CLK_DISABLE()
#define KEY_BUTTON_EXTI_LINE                    USER_BUTTON_EXTI_LINE
#define KEY_BUTTON_EXTI_IRQn                    USER_BUTTON_EXTI_IRQn

#ifdef LORA_SMART_TRACKER
#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)     do { \
                                                switch( __INDEX__ ) \
                                                  {\
                                                  case BUTTON_USER: \
                                                    USER_BUTTON_GPIO_CLK_ENABLE();   \
                                                    break;\
                                                  case BUTTON_WAKE: \
                                                    WAKE_BUTTON_GPIO_CLK_ENABLE();   \
                                                    break;\
                                                  default:\
                                                    break;\
                                                  }\
 } while(0)

#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)     do { \
                                                switch( __INDEX__ ) \
                                                  {\
                                                  case BUTTON_USER: \
                                                    USER_BUTTON_GPIO_CLK_DISABLE();   \
                                                    break;\
                                                  case BUTTON_WAKE: \
                                                    WAKE_BUTTON_GPIO_CLK_DISABLE();   \
                                                    break;\
                                                  default:\
                                                    break;\
                                                  }\
 } while(0)
   
#else //LORA_SMART_TRACKER

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)     do {KEY_BUTTON_GPIO_CLK_ENABLE();  } while(0)
#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)    do {KEY_BUTTON__GPIO_CLK_DISABLE();} while(0)

#endif //LORA_SMART_TRACKER
   
/**
  * @}
  */ 




/** @defgroup LORATRACKER_LOWLEVEL_Exported_Functions   Exported Functions
  * @{
  */
uint32_t         BSP_GetVersion(void);  
void             BSP_LED_Init(Led_TypeDef Led);
void             BSP_LED_On(Led_TypeDef Led);
void             BSP_LED_Off(Led_TypeDef Led);
void             BSP_LED_Toggle(Led_TypeDef Led);                 
void             BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
uint32_t         BSP_PB_GetState(Button_TypeDef Button);                

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

#endif /* __LORA_TRACKER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

