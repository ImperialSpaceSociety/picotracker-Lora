/**
  *******************************************************************************
  * @file    teseo_io.h
  * @author  APG/AST/CL
  * @version V2.0.0
  * @date    Feb-2018
  * @brief   Teseo III I/O manager.
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
#ifndef TESEO_IO_H
#define TESEO_IO_H

#ifdef __cplusplus
extern "C" {
#endif

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

#if (defined (USE_STM32L0XX_NUCLEO)|| defined (USE_B_L072Z_LRWAN1) || defined (LORA_SMART_TRACKER))
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_uart.h"
#include "stm32l0xx_hal_i2c.h"
#endif /* USE_STM32L0XX_NUCLEO */

#include "gnss.h"
#include "teseo_queue.h"

/** @addtogroup DRIVERS
 * @{
 */
 
/** @addtogroup BSP
 * @{
 */

/** @addtogroup COMPONENTS
 * @{
 */

/** @addtogroup TESEOIII TESEOIII
 * @brief This module defines the GNSS IO Manager
 * and implements the GNSS driver API specific for both UART
 * and I2C communication.
 * @{
 */

/** @defgroup TESEOIII_EXPORTED_TYPES EXPORTED TYPES
 * @{
 */

/**
 * @brief Data structure for the TeseoIII IO Manager.
 */
#if defined ( __CC_ARM )
#pragma anon_unions 
#endif
typedef struct
{
  union
  {
    UART_HandleTypeDef *huart;
    I2C_HandleTypeDef  *hi2c;
  };
  Teseo_QueueTypeDef *pQueue;

} Teseo_IO_DataTypeDef;
/**
 * @}
 */

extern GNSS_DrvTypeDef Teseo_Drv;
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

#endif /* TESEO_IO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

