/**
  ******************************************************************************
  * @file    loratracker_bus.h
  * @brief   header file for the BSP BUS IO driver
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.
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
#ifndef __LORATRACKER_BUS_H
#define __LORATRACKER_BUS_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include "stm32l0xx_hal.h"
#include "config_bus.h"
#include "sensor.h" 
#include "M95M02_DR_driver.h"
#include "LoRaTracker_eeprom.h"
#include <stdint.h>
  
 /** @addtogroup BSP
  * @{
  */


/** @addtogroup LORATRACKER
  * @{
  */

/** @addtogroup LORATRACKER_BUS
  * @{
  */ 

  
/** @addtogroup LORATRACKER_BUS_Private_Defines Private Defines
  * @{
  */
#define USE_HAL_SPI_REGISTER_CALLBACKS 0
#define USE_HAL_I2C_REGISTER_CALLBACKS 0
/**
* @}
*/

/** @addtogroup LORATRACKER_BUS_Private_Typedef Private Typedef 
  * @{
  */  
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
typedef struct
{
  pI2C_CallbackTypeDef  pMspI2cInitCb;
  pI2C_CallbackTypeDef  pMspI2cDeInitCb;
} BSP_I2C_Cb_t;
#endif /* (USE_HAL_I2C_REGISTER_CALLBACKS == 1) */

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
typedef struct
{
  pSPI_CallbackTypeDef  pMspSpiInitCb;
  pSPI_CallbackTypeDef  pMspSpiDeInitCb;
} BSP_SPI_Cb_t;
#endif /* (USE_HAL_SPI_REGISTER_CALLBACKS == 1) */

/**
* @}
*/

/** @addtogroup LORATRACKER_BUS_Exported_Functions_Typedef Exported Functions Typedef 
  * @{
  */ 

/* BUS IO driver over I2C Peripheral */
int32_t BSP_I2C1_Init(void);
int32_t BSP_I2C1_DeInit(void);
int32_t BSP_I2C1_IsReady(void);
int32_t BSP_I2C1_WriteReg(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
int32_t BSP_I2C1_ReadReg(uint16_t Addr, uint16_t Reg, uint8_t *pData, uint16_t len);
void BSP_sensor_Read_I2C_Error(void);

int32_t BSP_GetTick(void); 

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
int32_t BSP_BUS_RegisterDefaultMspCallbacks(void);
int32_t BSP_BUS_RegisterMspCallbacks(BSP_BUS_Cb_t *Callbacks);
#endif /* ((USE_HAL_I2C_REGISTER_CALLBACKS == 1) || (USE_HAL_SPI_REGISTER_CALLBACKS == 1)) */

/**
* @}
*/

/* Timing samples for L0 with SYSCLK 32MHz set in SystemClock_Config() */
#define LORA_TRAKER_I2C                            I2C1
#define LORA_TRAKER_I2C_CLK_ENABLE()               __I2C1_CLK_ENABLE()
#define LORA_TRAKER_I2C_SCL_SDA_GPIO_CLK_ENABLE()  __GPIOB_CLK_ENABLE()
#define LORA_TRAKER_I2C_SCL_SDA_AF                 GPIO_AF4_I2C1
#define LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT          GPIOB
#define LORA_TRAKER_I2C_SCL_PIN                    GPIO_PIN_8
#define LORA_TRAKER_I2C_SDA_PIN                    GPIO_PIN_9
#define LORA_TRAKER_I2C_SCL_SDA_MODE               GPIO_MODE_AF_OD
#define LORA_TRAKER_I2C_SCL_SDA_PULL               GPIO_NOPULL

#if ((defined (USE_STM32F4XX_LORA_TRAKER)) || (defined (USE_STM32L0XX_LORA_TRAKER)) || (defined (USE_STM32L4XX_LORA_TRAKER))|| (defined (USE_B_L072Z_LRWAN1)) || (defined (LORA_SMART_TRACKER)))
#define LORA_TRAKER_I2C_SCL_SDA_SPEED              GPIO_SPEED_FAST;
#elif (defined (USE_STM32L1XX_LORA_TRAKER))
#define LORA_TRAKER_I2C_SCL_SDA_SPEED              GPIO_SPEED_MEDIUM;
#endif

#define LORA_TRAKER_I2C_FORCE_RESET()              __I2C1_FORCE_RESET()
#define LORA_TRAKER_I2C_RELEASE_RESET()            __I2C1_RELEASE_RESET()

/* I2C interrupt requests */
#define LORA_TRAKER_I2C_EV_IRQn                    I2C1_IRQn

#define LORA_TRAKER_I2C_TIMING_100KHZ       0x10A13E56 /* Analog Filter ON, Rise Time 400ns, Fall Time 100ns */
#define LORA_TRAKER_I2C_TIMING_400KHZ       0x00B1112E /* Analog Filter ON, Rise Time 250ns, Fall Time 100ns */

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define LORA_TRAKER_I2C_TIMEOUT_MAX    0x1000 /*<! The value of the maximal timeout for BUS waiting loops */

#define BATTERY_ADC_CHANNEL             ADC_CHANNEL_5


/* Battery charger status */
typedef enum 
{
  BC_OK       = 0x00,
  BC_ERROR    = 0x01,
  BC_READY    = 0x02,
  BC_BUSY     = 0x03
} BC_StatusTypeDef;



#define M95M02_DR_SPI_MAX_CLOCK                 10000000 /* in Hz */
#define M95M02_DR_SPI_BUS_CLOCK                 HAL_RCC_GetPCLK2Freq()
#define M95M02_DR_SPI                           SPI2 
#define M95M02_DR_SPI_CLK_ENABLE()              __HAL_RCC_SPI2_CLK_ENABLE() 
#define M95M02_DR_SPI_CLK_DISABLE()             __HAL_RCC_SPI2_CLK_DISABLE()
#define M95M02_DR_SPI_MISO_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE() 
#define M95M02_DR_SPI_MOSI_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE() 
#define M95M02_DR_SPI_SCK_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

#define M95M02_DR_SPI_GPIO_PORT                 GPIOB 

#define M95M02_DR_SPI_MISO_GPIO_PORT            GPIOB 
#define M95M02_DR_SPI_MISO_PIN                  GPIO_PIN_14
#define M95M02_DR_SPI_MISO_MODE                 GPIO_MODE_AF_PP
#define M95M02_DR_SPI_MISO_PULL                 GPIO_NOPULL
#define M95M02_DR_SPI_MISO_SPEED                GPIO_SPEED_FREQ_VERY_HIGH
#define M95M02_DR_SPI_MISO_AF                   GPIO_AF0_SPI2 

#define M95M02_DR_SPI_MOSI_GPIO_PORT            GPIOB 
#define M95M02_DR_SPI_MOSI_PIN                  GPIO_PIN_15
#define M95M02_DR_SPI_MOSI_MODE                 GPIO_MODE_AF_PP
#define M95M02_DR_SPI_MOSI_PULL                 GPIO_NOPULL
#define M95M02_DR_SPI_MOSI_SPEED                GPIO_SPEED_FREQ_VERY_HIGH
#define M95M02_DR_SPI_MOSI_AF                   GPIO_AF0_SPI2 

#define M95M02_DR_SPI_SCK_GPIO_PORT             GPIOB 
#define M95M02_DR_SPI_SCK_PIN                   GPIO_PIN_13
#define M95M02_DR_SPI_SCK_MODE                  GPIO_MODE_AF_PP
#define M95M02_DR_SPI_SCK_PULL                  GPIO_NOPULL
#define M95M02_DR_SPI_SCK_SPEED                 GPIO_SPEED_FREQ_VERY_HIGH
#define M95M02_DR_SPI_SCK_AF                    GPIO_AF0_SPI2 

#define M95M02_DR_SPI_FORCE_RESET()             __HAL_RCC_SPI2_FORCE_RESET() 
#define M95M02_DR_SPI_RELEASE_RESET()           __HAL_RCC_SPI2_RELEASE_RESET()
#define M95M02_DR_SPI_IRQn                      SPI2_IRQn 
#define M95M02_DR_SPI_IRQ_PP                    7 
#define M95M02_DR_SPI_IRQ_SP                    0
#define M95M02_DR_SPI_IRQHandler                SPI2_IRQHandler

//Da modificare
#define M95M02_DR_SPI_RX_DMA                    DMA1_Channel4 
#define M95M02_DR_SPI_RX_DMA_CH                 DMA_REQUEST_2 
#define M95M02_DR_SPI_TX_DMA                    DMA1_Channel5 
#define M95M02_DR_SPI_TX_DMA_CH                 DMA_REQUEST_2 
#define M95M02_DR_SPI_DMA_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE();

#define M95M02_DR_SPI_TX_RX_DMA_IRQn            DMA1_Channel4_5_6_7_IRQn 
#define M95M02_DR_SPI_TX_RX_DMA_IRQ_PP          7
#define M95M02_DR_SPI_TX_RX_DMA_IRQ_SP          0
#define M95M02_DR_SPI_DMA_IRQHandler            DMA1_Channel4_5_6_7_IRQHandler 

#define M95M02_DR_S_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define M95M02_DR_S_GPIO_CLK_DISABLE()          __GPIOB_CLK_DISABLE()
#define M95M02_DR_S_GPIO_PORT                   GPIOB
#define M95M02_DR_S_PIN                         GPIO_PIN_12
#define M95M02_DR_S_MODE                        GPIO_MODE_OUTPUT_PP
#define M95M02_DR_S_PULL                        GPIO_NOPULL
#define M95M02_DR_S_SPEED                       GPIO_SPEED_HIGH

#define SPIx_TIMEOUT_MAX                        1000 /*<! Maximum timeout value for BUS waiting loops */
#define SPIx_BUFFERSIZE                         264

///* ################ IO Memory ############################################# */ 

#define LIS2DW12_INT2_O_GPIO_PORT           GPIOA
#define LIS2DW12_INT2_O_GPIO_CLK_ENABLE()   __GPIOA_CLK_ENABLE()
#define LIS2DW12_INT2_O_GPIO_CLK_DISABLE()  __GPIOA_CLK_DISABLE()
#define LIS2DW12_INT2_O_PIN                 GPIO_PIN_0
#define LIS2DW12_INT2_O_EXTI_IRQn           EXTI0_1_IRQn


#define M95M02_DR_HOLD_GPIO_PORT                GPIOI
#define M95M02_DR_HOLD_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOI_CLK_ENABLE()
#define M95M02_DR_HOLD_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOI_CLK_DISABLE()
#define M95M02_DR_HOLD_PIN                      GPIO_PIN_5
#define M95M02_DR_W_GPIO_PORT                   GPIOI
#define M95M02_DR_W_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOI_CLK_ENABLE()
#define M95M02_DR_W_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOI_CLK_DISABLE()
#define M95M02_DR_W_PIN    


extern DMA_HandleTypeDef hdma_M95M02_DR_Spi_rx;
extern DMA_HandleTypeDef hdma_M95M02_DR_Spi_tx;
extern UART_HandleTypeDef hSrvUart;
extern DMA_HandleTypeDef hdma_SrvUart_tx;
extern DMA_HandleTypeDef hdma_SrvUart_rx;
extern UART_HandleTypeDef hIoLinkUart;
extern DMA_HandleTypeDef hdma_IoLinkUart_tx;
extern DMA_HandleTypeDef hdma_IoLinkUart_rx;

/** @addtogroup LORATRACKER_BUS_Exported_Functions_Typedef Exported Functions Typedef 
  * @{
  */  
DrvStatusTypeDef M95M02_DR_IO_Init( void ) ;
uint8_t EEPROM_PIN_Read( void *handle, M95M02_DR_PinName_et PinName, uint8_t *State );
uint8_t EEPROM_PIN_Write( void *handle, M95M02_DR_PinName_et PinName, uint8_t State );
uint8_t EEPROM_Send_Instruction( void *handle, uint32_t Instruction, uint8_t *Data, uint16_t DataSize );
/**
  * @}
  */

/* ################ STUSB1600 (USB Type-C controller) ####################### */
#define STUSB1600_RST_GPIO_PORT                 GPIOA
#define STUSB1600_RST_PIN                       GPIO_PIN_4
#define STUSB1600_RST_MODE                      GPIO_MODE_OUTPUT_PP
#define STUSB1600_RST_PULL                      GPIO_NOPULL
#define STUSB1600_RST_SPEED                     GPIO_SPEED_HIGH

#define STUSB1600_INT_GPIO_PORT                 GPIOB
#define STUSB1600_INT_PIN                       GPIO_PIN_6
#define STUSB1600_INT_MODE                      GPIO_MODE_IT_RISING
#define STUSB1600_INT_PULL                      GPIO_NOPULL
#define STUSB1600_INT_EXTI_IRQn                 EXTI4_15_IRQn
#define STUSB1600_INT_EXTI_IRQ_PP               3
#define STUSB1600_INT_EXTI_IRQ_SP               0

#ifdef __cplusplus
}
#endif

#endif /* __LORATRACKER_BUS_H */

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
