/**
  *******************************************************************************
  * @file    config_bus.h
  * @author  AST/CL
  * @version V2.0.0
  * @date    Apr-2018
  * @brief   This file contains definitions and prototypes
  *	     for configuring the peripherals (UART/I2C)
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
#ifndef CONFIG_BUS_H
#define CONFIG_BUS_H

/* Includes ------------------------------------------------------------------*/
#ifdef USE_STM32F4XX_NUCLEO
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_i2c.h"
#endif /* USE_STM32F4XX_NUCLEO */

#ifdef USE_STM32L4XX_NUCLEO
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_uart.h"
#include "stm32l4xx_hal_i2c.h"
#endif /* USE_STM32L4XX_NUCLEO */

#if (defined (USE_STM32L0XX_NUCLEO) || defined (USE_B_L072Z_LRWAN1) || defined (LORA_SMART_TRACKER))
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_uart.h"
#include "stm32l0xx_hal_i2c.h"
#endif /* USE_STM32L0XX_NUCLEO */

#ifdef __cplusplus
extern "C" {
#endif

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

/** @addtogroup STEVAL-STRKT01_BSP_INTERFACE BSP Interface
  * @{
 */  
  
/** @addtogroup STEVAL-STRKT01_SimOSGetPos
 * @{
 */

/* Global variables ----------------------------------------------------------*/
/** @addtogroup STEVAL-STRKT01_SimOSGetPos_External_Variables External Variables
* @{
*/
extern I2C_HandleTypeDef  hi2c;
extern UART_HandleTypeDef huart;
extern UART_HandleTypeDef io_huart;
/**
 * @}
 */

/* Exported defines ----------------------------------------------------------*/
/** @addtogroup STEVAL-STRKT01_SimOSGetPos_Exported_Definitions Exported Definitions       
 * @{
 */

// I2C Instance
#define GNSS_I2C_INSTANCE          I2C1
#define GNSS_I2C_EV_IRQn           I2C1_EV_IRQn
#define GNSS_I2C_ER_IRQn           I2C1_ER_IRQn
#define GNSS_I2C_IRQn              I2C1_IRQn   

// I2C Conf
#define GNSS_I2C_CLK_SPEED         100000
#define GNSS_I2C_DUTY_CYCLE        I2C_DUTYCYCLE_2
#define GNSS_I2C_OWN_ADDRESS1      0
#define GNSS_I2C_ADDRESSING_MODE   I2C_ADDRESSINGMODE_7BIT
#define GNSS_I2C_DUAL_ADDRESS_MODE I2C_DUALADDRESS_DISABLE
#define GNSS_I2C_OWN_ADDRESS2      0
#define GNSS_I2C_GENERAL_CALL_MODE I2C_GENERALCALL_DISABLE
#define GNSS_I2C_NO_STRETCH_MODE   I2C_NOSTRETCH_DISABLE

// I2C Pins
#define GNSS_I2C_SCL            GPIO_PIN_8
#define GNSS_I2C_SDA            GPIO_PIN_9
#define GNSS_I22C_PORT          GPIOB
#define GNSS_I2C_CLK_ENABLE()   __HAL_RCC_I2C1_CLK_ENABLE()
#define GNSS_I2C_CLK_DISABLE()  __HAL_RCC_I2C1_CLK_DISABLE()
#define GNSS_I2C_PIN_MODE       GPIO_MODE_AF_OD
#define GNSS_I2C_PULL           GPIO_PULLUP
#define GNSS_I2C_SPEED          GPIO_SPEED_FREQ_VERY_HIGH
#define GNSS_I2C_ALTERNATE      GPIO_AF4_I2C1
   
// X-NUCLEO UART Instance
#define GNSS_UART_INSTANCE      USART1
#define GNSS_UART_IRQn          USART1_IRQn
#define GNSS_UART_IRQ_PP        0
#define GNSS_UART_IRQ_SP        0

// X-NUCLEO UART Conf
#define GNSS_UART_BAUD_RATE     9600
#define GNSS_UART_WORD_LENGTH   UART_WORDLENGTH_8B
#define GNSS_UART_STOP_BITS     UART_STOPBITS_1
#define GNSS_UART_PARITY        UART_PARITY_NONE
#define GNSS_UART_MODE          UART_MODE_TX_RX
#define GNSS_UART_HW_FLOW_CTL   UART_HWCONTROL_NONE
#define GNSS_UART_OVER_SAMPLING UART_OVERSAMPLING_16

// X-NUCLEO UART PINs
#define GNSS_UART_RX               GPIO_PIN_10
#define GNSS_UART_TX               GPIO_PIN_9
#define GNSS_UART_RXTX_PORT        GPIOA
#define GNSS_TX_GPIO_CLK_ENABLE()  __GPIOA_CLK_ENABLE()
#define GNSS_RX_GPIO_CLK_ENABLE()  __GPIOA_CLK_ENABLE()
#define GNSS_UART_CLK_ENABLE()     __HAL_RCC_USART1_CLK_ENABLE()
#define GNSS_UART_CLK_DISABLE()    __HAL_RCC_USART1_CLK_DISABLE()
#define GNSS_UART_PIN_MODE         GPIO_MODE_AF_PP
#define GNSS_UART_PULL             GPIO_NOPULL
#define GNSS_UART_SPEED            GPIO_SPEED_FREQ_VERY_HIGH
#if (defined (USE_STM32L0XX_NUCLEO) || defined (USE_B_L072Z_LRWAN1) || defined (LORA_SMART_TRACKER))
#define GNSS_UART_ALTERNATE        GPIO_AF4_USART1
#else   
#define GNSS_UART_ALTERNATE        GPIO_AF7_USART1
#endif /* USE_STM32L0XX_NUCLEO */

// I/O UART Instance
#define IO_UART_INSTANCE      USART2
#define IO_UART_IRQn          USART2_IRQn

// I/O UART Conf
#define IO_UART_BAUD_RATE     115200
#define IO_UART_WORD_LENGTH   UART_WORDLENGTH_8B
#define IO_UART_STOP_BITS     UART_STOPBITS_1
#define IO_UART_PARITY        UART_PARITY_NONE
#define IO_UART_MODE          UART_MODE_TX_RX
#define IO_UART_HW_FLOW_CTL   UART_HWCONTROL_NONE
#define IO_UART_OVER_SAMPLING UART_OVERSAMPLING_16

// I/O UART PINs
#define IO_UART_RX            GPIO_PIN_3
#define IO_UART_TX            GPIO_PIN_2
#define IO_UART_RXTX_PORT     GPIOA
#define IO_UART_CLK_ENABLE()  __HAL_RCC_USART2_CLK_ENABLE()
#define IO_UART_CLK_DISABLE() __HAL_RCC_USART2_CLK_DISABLE()
#define IO_UART_PIN_MODE      GPIO_MODE_AF_PP
#define IO_UART_PULL          GPIO_PULLUP//GPIO_NOPULL
#define IO_UART_SPEED         GPIO_SPEED_FREQ_VERY_HIGH//GPIO_SPEED_FREQ_LOW
#if (defined (USE_STM32L0XX_NUCLEO) || defined (USE_B_L072Z_LRWAN1) || defined (LORA_SMART_TRACKER))
#define IO_UART_ALTERNATE     GPIO_AF4_USART2
#else   
#define IO_UART_ALTERNATE     GPIO_AF7_USART2
#endif /* USE_STM32L0XX_NUCLEO */

// LED PIN
#define LOC_LED2            GPIO_PIN_10
#define LOC_LED2_PORT       GPIOB
#define LOC_LED2_SET()      HAL_GPIO_WritePin(LOC_LED2_PORT, LOC_LED2, GPIO_PIN_SET)
#define LOC_LED2_RESET()    HAL_GPIO_WritePin(LOC_LED2_PORT, LOC_LED2, GPIO_PIN_RESET)
/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup STEVAL-STRKT01_SimOSGetPos_Exported_Functions_Prototypes Exported Functions Prototypes
 * @{
 */
void GNSS_I2C_Init(void);
void GNSS_I2C_DeInit(void);
void GNSS_UART_Init(uint32_t BaudRate);
void GNSS_UART_DeInit(void);
void IO_UART_Init(void);

#ifdef __cplusplus
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

/**
 * @}
 */

/**
 * @}
 */

#endif /* CONFIG_BUS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
