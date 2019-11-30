/**
  ******************************************************************************
  * @file    loratracker_bus.c
  * @brief   Source file for the BSP BUS IO driver
  ******************************************************************************
  * @attention
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

/* Includes ------------------------------------------------------------------*/
#include "loratracker_bus.h"
#include "loratracker_errno.h"
#include "stm32l0xx_hal.h"
#include "debug.h"


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

/** @defgroup STEVAL-STRKT01_LORATRACKER_BUS LORATRACKER BUS
  * @brief This module provides set of firmware functions to manage BSP BUS
  * @{
  */

/** @addtogroup STEVAL-STRKT01_LORATRACKER_BUS_Private_Defines Private Defines
  * @{
  */
#define TIMEOUT_DURATION 1000

/* Definitions for STBC02 Single Wire protocol */
#define 	STBC02_CMD_START_DURATION			((uint32_t) 375)  /* Start Command duration in useconds */
#define 	STBC02_CMD_CMD_DURATION				((uint32_t) 110)	/* Pulse Command duration in useconds */
#define 	STBC02_CMD_STOP_DURATION			((uint32_t) 550)	/* Stop Command duration in useconds */
#define 	STBC02_CMD_IDLE_DURATION			((uint32_t) 550)	/* Idle Command duration in useconds */

/**
  * @}
  */



/** @defgroup STEVAL-STRKT01_LORATRACKER_Private_Variables     Private Variables
  * @{
  */
I2C_HandleTypeDef hbusi2c1;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
static uint32_t IsI2C1MspCbValid = 0;
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */


SPI_HandleTypeDef hM95M02_DR_Spi;
DMA_HandleTypeDef hdma_M95M02_DR_Spi_rx;
DMA_HandleTypeDef hdma_M95M02_DR_Spi_tx;
static uint8_t SPI_TxBuffer[SPIx_BUFFERSIZE];
static uint8_t SPI_RxBuffer[SPIx_BUFFERSIZE];
/**
  * @}
  */


/** @defgroup STEVAL-STRKT01_LORATRACKER_Private_FunctionPrototypes  Private Function Prototypes
  * @{
  */
HAL_StatusTypeDef I2C1_Init(I2C_HandleTypeDef *hi2c);

static void I2C1_MspInit(I2C_HandleTypeDef *i2cHandle);
static void I2C1_MspDeInit(I2C_HandleTypeDef *i2cHandle);
static void SPIx_MspInit(SPI_HandleTypeDef* spiHandle);
static void SPIx_Error(SPI_HandleTypeDef* spiHandle);
static uint8_t SPIx_GetBaudRatePrescaler(uint32_t APB_Clock, uint32_t SPI_maxClock, uint32_t *pBaudRatePrescaler);
static uint8_t M95M02_DR_SPI_Init(void);

/**
  * @}
  */


/** @defgroup STEVAL-STRKT01_LORATRACKER_BUS_Exported_Functions Exported Functions
  * @{
  */
/* BUS IO driver over I2C Peripheral */
/*******************************************************************************
                            BUS OPERATIONS OVER I2C
*******************************************************************************/

/**
  * @brief Sensor read I2C error
  * @param None
  * @retval None
  */
void BSP_sensor_Read_I2C_Error(void)
{
  uint32_t temp;
  
  /* De-initialize the I2C comunication bus */
  //  HAL_I2C_DeInit(&PWR_I2C_Handle);
  BSP_I2C1_DeInit();
  
  /* I2C SDA is tied low */
  temp = GPIOB->MODER;
  
  /* PB8 (I2C CLK) is configured as general purpose output mode */
  CLEAR_BIT(temp, 3 << (8 * 2));
  SET_BIT(temp, 1 << (8 * 2));
  GPIOB->MODER = temp;
  
  /* Safe delay */
  uint32_t n= 100;
  n = n * HAL_RCC_GetHCLKFreq()/1000;
  n/=10;
  while(n--);
  
  /* PB8 (I2C CLK) is configured as alternate function mode */
  CLEAR_BIT(temp, 3 << (8 * 2));
  SET_BIT(temp, 2 << (8 * 2));
  GPIOB->MODER = temp;
  
  /* Re-Initiaize the I2C comunication bus */
  //  PWR_I2C_Init();
  BSP_I2C1_Init();
}

/**
  * @brief  Initialize a bus
  * @param None
  * @retval BSP status
  */
int32_t BSP_I2C1_Init(void)
{

  int32_t ret = BSP_ERROR_NONE;

  hbusi2c1.Instance  = I2C1;

  if (HAL_I2C_GetState(&hbusi2c1) == HAL_I2C_STATE_RESET)
  {
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 0)
    /* Init the I2C Msp */
    I2C1_MspInit(&hbusi2c1);
#else
    if (IsI2C1MspCbValid == 0U)
    {
      if (BSP_I2C1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif

    /* Init the I2C */
    if (I2C1_Init(&hbusi2c1) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
    else if (HAL_I2CEx_ConfigAnalogFilter(&hbusi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
  * @brief  DeInitialize a bus
  * @param None
  * @retval BSP status
  */
int32_t BSP_I2C1_DeInit(void)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 0)
  /* DeInit the I2C */
  I2C1_MspDeInit(&hbusi2c1);
#endif

  if (HAL_I2C_DeInit(&hbusi2c1) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Return the status of the Bus
  * @retval bool
  */
int32_t BSP_I2C1_IsReady(void)
{
  return (HAL_I2C_GetState(&hbusi2c1) == HAL_I2C_STATE_READY);
}

/**
  * @brief  Write registers through bus (8 bits)
  * @param  Addr: Device address on Bus.
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written
  * @retval BSP status
  */
int32_t BSP_I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Mem_Write(&hbusi2c1, (uint8_t)DevAddr,
                        (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT,
                        (uint8_t *)pData, len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Read registers through a bus (8 bits)
  * @param  DevAddr: Device address on BUS
  * @param  Reg: The target register address to read
  * @retval BSP status
  */
int32_t  BSP_I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Mem_Read(&hbusi2c1, DevAddr, (uint16_t)Reg,
                       I2C_MEMADD_SIZE_8BIT, pData,
                       len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = HAL_OK;
  }

  return ret;
}

/**
  * @brief  Receive an amount of data through a bus (Simplex)
  * @param  DevAddr: Device address on Bus.
  * @param  pData: Data pointer
  * @param  Length: Data length
  * @retval BSP status
  */
int32_t BSP_I2C1_Recv(uint16_t DevAddr, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Master_Receive(&hbusi2c1, DevAddr, pData, len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = len;
  }

  return ret;
}

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
/**
  * @brief BSP I2C1 Bus Msp Callback registering
  * @param Callbacks     pointer to I2C1 MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_I2C1_RegisterMspCallbacks(BSP_I2C_Cb_t *Callbacks)
{
  /* Prevent unused argument(s) compilation warning */
  __HAL_I2C_RESET_HANDLE_STATE(&hbusi2c1);

  /* Register MspInit Callback */
  if (HAL_I2C_RegisterCallback(&hbusi2c1, HAL_I2C_MSPINIT_CB_ID, Callbacks->pMspI2cInitCb)  != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if (HAL_I2C_RegisterCallback(&hbusi2c1, HAL_I2C_MSPDEINIT_CB_ID, Callbacks->pMspI2cDeInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsI2C1MspCbValid = 1;

  return BSP_ERROR_NONE;
}
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

/**
  * @brief  Return system tick in ms
  * @param  None
  * @retval Current HAL time base time stamp
  */
int32_t BSP_GetTick(void)
{
  return HAL_GetTick();
}

/**
  * @brief  I2C1 init function
  * @param  hi2c I2C handle pointer
  * @retval A HAL Status value
  */
HAL_StatusTypeDef I2C1_Init(I2C_HandleTypeDef *hi2c)
{
  HAL_StatusTypeDef ret = HAL_OK;
  hi2c->Instance = I2C1;
  hi2c->Init.Timing = 0x00200C28;
  hi2c->Init.OwnAddress1 = 0;
  hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c->Init.OwnAddress2 = 0;
  hi2c->Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(hi2c) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  if (HAL_I2CEx_ConfigAnalogFilter(hi2c, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  if (HAL_I2CEx_ConfigDigitalFilter(hi2c, 0) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  return ret;
}

/**
* @brief I2C MSP Initialization
* This function configures the used hardware resources
* @param hi2c I2C handle pointer
* @retval None
*/
static void I2C1_MspInit(I2C_HandleTypeDef *i2cHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* I2C1 GPIO Configuration
  PB8     ------> I2C1_SCL
  PB9     ------> I2C1_SDA
  */
  
  GPIO_InitStruct.Pin        = LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN;
  GPIO_InitStruct.Mode       = LORA_TRAKER_I2C_SCL_SDA_MODE;
  GPIO_InitStruct.Speed      = LORA_TRAKER_I2C_SCL_SDA_SPEED;
  GPIO_InitStruct.Pull       = LORA_TRAKER_I2C_SCL_SDA_PULL;
  GPIO_InitStruct.Alternate  = LORA_TRAKER_I2C_SCL_SDA_AF;

  HAL_GPIO_Init( LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, &GPIO_InitStruct );


  /* Enable the I2C peripheral clock */
  LORA_TRAKER_I2C_CLK_ENABLE();
  /* Enable I2C GPIO clocks */
  LORA_TRAKER_I2C_SCL_SDA_GPIO_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */
  
  /* Force the I2C peripheral clock reset */
  LORA_TRAKER_I2C_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  LORA_TRAKER_I2C_RELEASE_RESET();

  /* Enable and set I2C Interrupt to the highest priority */
  HAL_NVIC_SetPriority(LORA_TRAKER_I2C_EV_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(LORA_TRAKER_I2C_EV_IRQn);

#if ((defined (USE_STM32F4XX_LORA_TRAKER)) || (defined (USE_STM32L1XX_LORA_TRAKER)) || (defined (USE_STM32L4XX_LORA_TRAKER)))
  /* Enable and set I2C Interrupt to the highest priority */
  HAL_NVIC_SetPriority(LORA_TRAKER_I2C_ER_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(LORA_TRAKER_I2C_ER_IRQn);
#endif

}


/**
* @brief I2C MSP Deinitialization
* This function releases the I2C hardware resources
* @param hi2c I2C handle pointer
* @retval None
*/
static void I2C1_MspDeInit(I2C_HandleTypeDef *i2cHandle)
{

  /* Peripheral clock disable */
  __HAL_RCC_I2C1_CLK_DISABLE();

  /* I2C1 GPIO Configuration
  PB8     ------> I2C1_SCL
  PB9     ------> I2C1_SDA
  */
  
  HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);
}

/*-------------------------- Memory Functions --------------------------------*/


/**
  * @brief  Configures SPI interface for Memory.
  * @param  None
  * @retval 0 in case of success
  * @retval 1 in case of failure
  */
static uint8_t M95M02_DR_SPI_Init(void)
{
  uint32_t spiBaudRatePrescaler = 0;
  
  if (SPIx_GetBaudRatePrescaler(M95M02_DR_SPI_BUS_CLOCK, M95M02_DR_SPI_MAX_CLOCK, &spiBaudRatePrescaler))
    return 1;
  
  /* DMA controller clock enable */
  M95M02_DR_SPI_DMA_CLK_ENABLE(); 
  
  /* Memory SPI DMA Stream IRQ interrupt configuration for TX and RX */
  HAL_NVIC_SetPriority(M95M02_DR_SPI_TX_RX_DMA_IRQn, M95M02_DR_SPI_TX_RX_DMA_IRQ_PP, M95M02_DR_SPI_TX_RX_DMA_IRQ_SP);
  HAL_NVIC_EnableIRQ(M95M02_DR_SPI_TX_RX_DMA_IRQn); 
  
  hM95M02_DR_Spi.Instance = M95M02_DR_SPI; // SPI2
  hM95M02_DR_Spi.Init.Mode = SPI_MODE_MASTER;
  hM95M02_DR_Spi.Init.Direction = SPI_DIRECTION_2LINES;
  hM95M02_DR_Spi.Init.DataSize = SPI_DATASIZE_8BIT;
  hM95M02_DR_Spi.Init.CLKPolarity = SPI_POLARITY_LOW;
  hM95M02_DR_Spi.Init.CLKPhase = SPI_PHASE_1EDGE;
  hM95M02_DR_Spi.Init.NSS = SPI_NSS_SOFT;
  hM95M02_DR_Spi.Init.BaudRatePrescaler = spiBaudRatePrescaler;
  hM95M02_DR_Spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hM95M02_DR_Spi.Init.TIMode = SPI_TIMODE_DISABLE;
  hM95M02_DR_Spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hM95M02_DR_Spi.Init.CRCPolynomial = 7; //10;
  
  SPIx_MspInit(&hM95M02_DR_Spi);
  
  if (HAL_SPI_Init(&hM95M02_DR_Spi) != HAL_OK)
  {
    Error_Handler();
  }
  
  if( HAL_SPI_GetState( &hM95M02_DR_Spi) == HAL_SPI_STATE_READY )
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


/**
* @brief SPI MSP Initialization
* This function configures the used hardware resources
* @param spiHandle SPI handle pointer
* @retval None
*/
static void SPIx_MspInit(SPI_HandleTypeDef* spiHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  if(spiHandle->Instance==M95M02_DR_SPI) {
    
    /* Peripheral GPIO clock enable */
    M95M02_DR_SPI_MISO_GPIO_CLK_ENABLE();
    M95M02_DR_SPI_MOSI_GPIO_CLK_ENABLE();
    M95M02_DR_SPI_SCK_GPIO_CLK_ENABLE();
    /* SPI Peripheral clock enable */
    M95M02_DR_SPI_CLK_ENABLE(); 
    
    /* Memory SPI GPIO Configuration */
    
    /* Memory SPI MISO Init */  
    GPIO_InitStruct.Pin = M95M02_DR_SPI_MISO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = M95M02_DR_SPI_MISO_AF;
    HAL_GPIO_Init(M95M02_DR_SPI_MISO_GPIO_PORT, &GPIO_InitStruct);
    
    /* Memory SPI MOSI Init */ 
    GPIO_InitStruct.Pin = M95M02_DR_SPI_MOSI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = M95M02_DR_SPI_MOSI_AF;
    HAL_GPIO_Init(M95M02_DR_SPI_MOSI_GPIO_PORT, &GPIO_InitStruct);
    
    /* Memory SPI SCK Init */ 
    GPIO_InitStruct.Pin = M95M02_DR_SPI_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = M95M02_DR_SPI_SCK_AF;
    HAL_GPIO_Init(M95M02_DR_SPI_SCK_GPIO_PORT, &GPIO_InitStruct);
    
    /* Memory SPI DMA Init */
    
    /* Memory SPI RX Init */
    hdma_M95M02_DR_Spi_rx.Instance = M95M02_DR_SPI_RX_DMA;
    hdma_M95M02_DR_Spi_rx.Init.Request = M95M02_DR_SPI_RX_DMA_CH;
    hdma_M95M02_DR_Spi_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_M95M02_DR_Spi_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_M95M02_DR_Spi_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_M95M02_DR_Spi_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_M95M02_DR_Spi_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_M95M02_DR_Spi_rx.Init.Mode = DMA_NORMAL;
    hdma_M95M02_DR_Spi_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_M95M02_DR_Spi_rx) != HAL_OK) {
      Error_Handler();
    }
    
    __HAL_LINKDMA(spiHandle,hdmarx,hdma_M95M02_DR_Spi_rx);
    
    /* Memory SPI TX Init */
    hdma_M95M02_DR_Spi_tx.Instance = M95M02_DR_SPI_TX_DMA; 
    hdma_M95M02_DR_Spi_tx.Init.Request = M95M02_DR_SPI_TX_DMA_CH; 
    hdma_M95M02_DR_Spi_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_M95M02_DR_Spi_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_M95M02_DR_Spi_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_M95M02_DR_Spi_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_M95M02_DR_Spi_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_M95M02_DR_Spi_tx.Init.Mode = DMA_NORMAL;
    hdma_M95M02_DR_Spi_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_M95M02_DR_Spi_tx) != HAL_OK) {
      Error_Handler();
    }
    
    __HAL_LINKDMA(spiHandle,hdmatx,hdma_M95M02_DR_Spi_tx);
  }
}


/**
  * @brief  Manages error callback by re-initializing SPI
  * @param spiHandle SPI handle pointer
  * @retval None
  */
void SPIx_Error(SPI_HandleTypeDef* spiHandle)
{
   /* De-initialize the SPI comunication bus */
  HAL_SPI_DeInit(spiHandle);
  
  /* Wait a while in order to have SPI that works fine after deinit */
  HAL_Delay(1);
}


/**
  * @brief It generates the SPI baud rate prescaler
  * @param APB_Clock 
  * @param SPI_maxClock 
  * @param pBaudRatePrescaler Pointer to baud rate prescaler 
  * @retval A number that indicates if the function has been performed correctly
  */
static uint8_t SPIx_GetBaudRatePrescaler(uint32_t APB_Clock, uint32_t SPI_maxClock, uint32_t *pBaudRatePrescaler) {
  
  uint32_t clockDivider = 0;
  
  clockDivider = M95M02_DR_SPI_BUS_CLOCK / M95M02_DR_SPI_MAX_CLOCK;
  
  if (clockDivider <= 2)
    *pBaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  else
    if (clockDivider <= 4)
      *pBaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    else
      if (clockDivider <= 8)
        *pBaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
      else
        if (clockDivider <= 16)
          *pBaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
        else
          if (clockDivider <= 32)
            *pBaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
          else
            if (clockDivider <= 64)
              *pBaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
            else
              if (clockDivider <= 128)
                *pBaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
              else
                if (clockDivider <= 256)
                  *pBaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
                else
                  return 1;
                
  return 0;
                
}

/**
  * @brief  Configures the I/Os for the M95M02_DR EEPROM module.
  * @param  None
  * @retval COMPONENT_OK in case of success
  * @retval COMPONENT_ERROR in case of failure
*/
DrvStatusTypeDef M95M02_DR_IO_Init( void ) {
  
  GPIO_InitTypeDef GPIO_InitStruct;
  uint8_t status;
  
  status = M95M02_DR_SPI_Init();
  
  if (status == COMPONENT_OK) {
    /* Configure M95M02_DR CS GPIO pin ****************************** */
    M95M02_DR_S_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin = M95M02_DR_S_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(M95M02_DR_S_GPIO_PORT, &GPIO_InitStruct);

  }
  
  return (DrvStatusTypeDef)status;
}


/**
  * @brief  Writes the pin state of the eeprom
  * @param  *handle Instance handle
  * @param  PinName The M95M02-DR pin to be written
  * @param  State The new pin state
  * @retval 0 in case of success
  * @retval 1 in case of failure
  */
uint8_t EEPROM_PIN_Write( void *handle, M95M02_DR_PinName_et PinName, uint8_t PinState ) {
  
	uint8_t retval = 1;
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  GPIO_TypeDef* GPIOx;
  uint16_t GPIO_Pin_x;
  
  switch (ctx->instance) {
    
  case M95M02_DR_M_0:
    switch (PinName) {
      
    case S:
      GPIOx = M95M02_DR_S_GPIO_PORT;
      GPIO_Pin_x = M95M02_DR_S_PIN;
      HAL_GPIO_WritePin(GPIOx, GPIO_Pin_x, (GPIO_PinState)PinState);
      break;
    default:
      retval = 1;
    }
    break;
    
  default:
    retval = 1; 
  }
  
  retval = 0;
	
	return retval;
}

/**
  * @brief  Reads the pin state of the eeprom
  * @param  *handle Instance handle
  * @param  PinName The M95M02-DR pin to be read
  * @param  *State The actual pin state
  * @retval 0 in case of success
  * @retval 1 in case of failure
  */
uint8_t EEPROM_PIN_Read( void *handle, M95M02_DR_PinName_et PinName, uint8_t *PinState ) {
  
	uint8_t retval = 1;
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  GPIO_TypeDef* GPIOx;
  uint16_t GPIO_Pin_x;
  
  switch (ctx->instance) {
    
  case M95M02_DR_M_0:
    switch (PinName) {
      
    case S:
      GPIOx = M95M02_DR_S_GPIO_PORT;
      GPIO_Pin_x = M95M02_DR_S_PIN;
      break;
    default:
      retval = 1;
    }
    break;
    
    default:
      retval = 1; 
  }
    
  /* call GPIO read pin function */
  *PinState = (uint8_t)HAL_GPIO_ReadPin(GPIOx, GPIO_Pin_x);
  retval = 0;
  
	return retval;
}

/**
  * @brief  Send an instruction to the eeprom
  * @param  *handle Instance handle
  * @param  Instruction The instruction plus address to be sent
  * @param  *Data Data to be read/written
  * @param  DataSize The size of the data
  * @details Instruction must be coded as Instruction (MSB) and 24-bit Address (LSB)
  * @retval 0 in case of success
  * @retval 1 in case of failure
  */
uint8_t EEPROM_Send_Instruction( void *handle, uint32_t Instruction, uint8_t *Data, uint16_t DataSize ) {
  
  uint8_t retValue = 1;
  HAL_StatusTypeDef status = HAL_ERROR;
  DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
  GPIO_TypeDef* GPIOx;
  uint16_t GPIO_Pin_x;
  M95M02_DR_Instructions_et InstructionOnly;
  uint32_t Address;
  uint16_t iTxBuffer;
  uint8_t DataOffset;
  
  switch (ctx->instance) {
    
  case M95M02_DR_M_0:
    GPIOx = M95M02_DR_S_GPIO_PORT;
    GPIO_Pin_x = M95M02_DR_S_PIN;
    
    /* Reset the TX buffer */
    memset(SPI_TxBuffer, 0x00, SPIx_BUFFERSIZE);
    /* Reset the RX buffer */
    memset(SPI_RxBuffer, 0x00, SPIx_BUFFERSIZE);
    
    InstructionOnly = (M95M02_DR_Instructions_et)(Instruction>>24);
    Address = Instruction & 0x00FFFFFF;
    
    iTxBuffer = 0;

    SPI_TxBuffer[iTxBuffer++] = InstructionOnly;
    
    if ((InstructionOnly == READ) || (InstructionOnly == WRITE)) {
      
      for (uint8_t iAddress=0; iAddress<3; iAddress++) {
        
        SPI_TxBuffer[iTxBuffer++] = (uint8_t)((Address>>((2-iAddress)*8))&(0x000000FF));
      }
    }
    
    DataOffset = iTxBuffer;
    
    if ((InstructionOnly == WRSR) || (InstructionOnly == WRITE)) {
      
      for (uint16_t iDataSize=0; iDataSize<DataSize; iDataSize++) {
        
        SPI_TxBuffer[iTxBuffer++] = Data[iDataSize];
      }
    }
    
    /* Select the device */
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin_x, GPIO_PIN_RESET);
    status = HAL_SPI_TransmitReceive( &hM95M02_DR_Spi, SPI_TxBuffer, SPI_RxBuffer, DataOffset+DataSize, 0xFFFFFFFF );
    
    /* Check the communication status */
    if( status != HAL_OK ) {
      
      /* Execute user timeout callback */
      SPIx_Error( &hM95M02_DR_Spi );
      retValue = 1;
    }
    else {
      
      while(HAL_SPI_GetState(&hM95M02_DR_Spi) != HAL_SPI_STATE_READY);
      
      if ((InstructionOnly == RDSR) || (InstructionOnly == READ)) {
        
        for (uint16_t iDataSize=0; iDataSize<DataSize; iDataSize++) {
          
          *(Data+iDataSize) = SPI_RxBuffer[DataOffset+iDataSize];
        }
      }
      
      retValue = 0;
    }
    /* Deselect the device */
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin_x, GPIO_PIN_SET);
    break;
    
  default:
    retValue = 1;
  }
  
  return retValue;
}


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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
