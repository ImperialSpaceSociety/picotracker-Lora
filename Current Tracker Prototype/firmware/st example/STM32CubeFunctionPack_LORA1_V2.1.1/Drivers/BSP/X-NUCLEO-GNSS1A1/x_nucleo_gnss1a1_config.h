/**
  *******************************************************************************
  * @file    x_nucleo_gnss1a1_config.h
  * @author  ADG ADD Application Software
  * @version V1.0.0
  * @date    20-Ago-2016
  * @brief   This file contains definitions of the constants and macros used by 
  *          the driver
  *
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

#ifndef X_NUCLEO_GNSS1A1_CONFIG_H
#define X_NUCLEO_GNSS1A1_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup DRIVERS
  * @{
  */
  
/** @addtogroup BSP
 * @{
 */

/** @addtogroup X_NUCLEO_GNSS1A1
  * @{
  */

/** @defgroup X_NUCLEO_GNSS1A1_CONFIG X_NUCLEO_GNSS1A1_CONFIG
  * @{
  */
  
/** @defgroup PRIVATE_DEFINES PRIVATE DEFINES
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
#define GNSS_I2C_SCL           GPIO_PIN_8
#define GNSS_I2C_SDA           GPIO_PIN_9
#define GNSS_I22C_PORT         GPIOB
#define GNSS_I2C_CLK_ENABLE()  __HAL_RCC_I2C1_CLK_ENABLE()
#define GNSS_I2C_CLK_DISABLE() __HAL_RCC_I2C1_CLK_DISABLE()
#define GNSS_I2C_PIN_MODE      GPIO_MODE_AF_OD
#define GNSS_I2C_PULL          GPIO_PULLUP
#define GNSS_I2C_SPEED         GPIO_SPEED_FREQ_VERY_HIGH
#define GNSS_I2C_ALTERNATE     GPIO_AF4_I2C1
   
// X-NUCLEO UART Instance
#define GNSS_UART_INSTANCE      USART1
#define GNSS_UART_IRQn          USART1_IRQn

// X-NUCLEO UART Conf
#define GNSS_UART_BAUD_RATE     9600
#define GNSS_UART_WORD_LENGTH   UART_WORDLENGTH_8B
#define GNSS_UART_STOP_BITS     UART_STOPBITS_1
#define GNSS_UART_PARITY        UART_PARITY_NONE
#define GNSS_UART_MODE          UART_MODE_TX_RX
#define GNSS_UART_HW_FLOW_CTL   UART_HWCONTROL_NONE
#define GNSS_UART_OVER_SAMPLING UART_OVERSAMPLING_16

 // X-NUCLEO UART PINs
#define GNSS_UART_RX            GPIO_PIN_10
#define GNSS_UART_TX            GPIO_PIN_9
#define GNSS_UART_RXTX_PORT     GPIOA
#define GNSS_UART_CLK_ENABLE()  __HAL_RCC_USART1_CLK_ENABLE()
#define GNSS_UART_CLK_DISABLE() __HAL_RCC_USART1_CLK_DISABLE()
#define GNSS_UART_PIN_MODE      GPIO_MODE_AF_PP
#define GNSS_UART_PULL          GPIO_PULLUP
#define GNSS_UART_SPEED         GPIO_SPEED_FREQ_VERY_HIGH
#ifdef USE_STM32L0XX_NUCLEO   
#define GNSS_UART_ALTERNATE     GPIO_AF4_USART1
#elif defined(USE_B_L072Z_LRWAN1)
#define GNSS_UART_ALTERNATE     GPIO_AF4_USART1
#else   
#define GNSS_UART_ALTERNATE     GPIO_AF7_USART1
#endif /* USE_STM32L0XX_NUCLEO */

// I/O UART Instance
#define GNSS_IO_UART_INSTANCE      USART2
#define GNSS_IO_UART_IRQn          USART2_IRQn

// I/O UART Conf
#define GNSS_IO_UART_BAUD_RATE     115200
#define GNSS_IO_UART_WORD_LENGTH   UART_WORDLENGTH_8B
#define GNSS_IO_UART_STOP_BITS     UART_STOPBITS_1
#define GNSS_IO_UART_PARITY        UART_PARITY_NONE
#define GNSS_IO_UART_MODE          UART_MODE_TX_RX
#define GNSS_IO_UART_HW_FLOW_CTL   UART_HWCONTROL_NONE
#define GNSS_IO_UART_OVER_SAMPLING UART_OVERSAMPLING_16

// I/O UART PINs
#define GNSS_IO_UART_RX            GPIO_PIN_3
#define GNSS_IO_UART_TX            GPIO_PIN_2
#define GNSS_IO_UART_RXTX_PORT     GPIOA
#define GNSS_IO_UART_CLK_ENABLE()  __HAL_RCC_USART2_CLK_ENABLE()
#define GNSS_IO_UART_CLK_DISABLE() __HAL_RCC_USART2_CLK_DISABLE()
#define GNSS_IO_UART_PIN_MODE      GPIO_MODE_AF_PP
#define GNSS_IO_UART_PULL          GPIO_PULLUP//GPIO_NOPULL
#define GNSS_IO_UART_SPEED         GPIO_SPEED_FREQ_VERY_HIGH//GPIO_SPEED_FREQ_LOW
#ifdef USE_STM32L0XX_NUCLEO   
#define GNSS_IO_UART_ALTERNATE     GPIO_AF4_USART2
#elif defined(USE_B_L072Z_LRWAN1)
#define GNSS_IO_UART_ALTERNATE     GPIO_AF4_USART2
#else   
#define GNSS_IO_UART_ALTERNATE     GPIO_AF7_USART2
#endif /* USE_STM32L0XX_NUCLEO */

// Reset PIN    
#define GNSS_RST_PIN         GPIO_PIN_4
#define GNSS_RST_PORT        GPIOA
#define GNSS_RST_PIN_SET()   HAL_GPIO_WritePin(GNSS_RST_PORT, GNSS_RST_PIN, GPIO_PIN_SET)
#define GNSS_RST_PIN_RESET() HAL_GPIO_WritePin(GNSS_RST_PORT, GNSS_RST_PIN, GPIO_PIN_RESET)

// WAKEUP PIN
#define GNSS_WAKEUP_PIN         GPIO_PIN_8
#define GNSS_WAKEUP_PORT        GPIOA
#define GNSS_WAKEUP_SET()       HAL_GPIO_WritePin(GNSS_WAKEUP_PORT, GNSS_WAKEUP_PIN, GPIO_PIN_SET)
#define GNSS_WAKEUP_RESET()     HAL_GPIO_WritePin(GNSS_WAKEUP_PORT, GNSS_WAKEUP_PIN, GPIO_PIN_RESET)
#define GNSS_WAKEUP_GETSTATUS() HAL_GPIO_ReadPin(GNSS_WAKEUP_PORT, GNSS_WAKEUP_PIN)

// LED PIN
#define LOC_LED2            GPIO_PIN_10
#define LOC_LED2_PORT       GPIOB
#define LOC_LED2_SET()      HAL_GPIO_WritePin(LOC_LED2_PORT, LOC_LED2, GPIO_PIN_SET)
#define LOC_LED2_RESET()    HAL_GPIO_WritePin(LOC_LED2_PORT, LOC_LED2, GPIO_PIN_RESET)
   
   
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

#ifdef __cplusplus
}
#endif

#endif /* X_NUCLEO_GNSS1A1_CONFIG_H */

