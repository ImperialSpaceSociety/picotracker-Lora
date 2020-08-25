/**
  ******************************************************************************
  * @file           : i2c_middleware.c
  * @brief          : I2C middleware for this specific project, using HAL
	*										libraries
  ******************************************************************************
  * Imperial College Space Society
	* Medad Newman, Richard Ibbotson
  *
  *
  ******************************************************************************
  */


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of system and local header files goes here */

#include <i2c_middleware.h>
#include "hw_i2c.h"
#include "hw.h" // for PRINTF


/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */

/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */



/* ==================================================================== */
/* ========================== private data ============================ */
/* ==================================================================== */

/* Definition of private datatypes go here */




/* ==================================================================== */
/* ====================== private functions =========================== */
/* ==================================================================== */

/* Function prototypes for private (static) functions go here */


void I2C_PINS_GPIO_INIT(void);




/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

I2C_MIDDLEWARE_STATUS_t I2C_receive(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout )
{

		if(HAL_I2C_Master_Receive(hi2c, DevAddress, pData, Size,Timeout)!= HAL_OK)
		{
			/* Error_Handler() function is called when error occurs. */
		}




		if (HAL_I2C_GetError(hi2c) == HAL_I2C_ERROR_NONE){
				return I2C_SUCCSS;
		}
	
	return I2C_FAIL;
}	


/*
    Transmits a desired UBX message across I2C1.
*/
I2C_MIDDLEWARE_STATUS_t I2C_transmit(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout )
{

		if(HAL_I2C_Master_Transmit(hi2c, DevAddress, pData, Size,Timeout)!= HAL_OK)
		{
			/* Error_Handler() function is called when error occurs. */
		}



		if (HAL_I2C_GetError(hi2c) == HAL_I2C_ERROR_NONE){
				return I2C_SUCCSS;
		}

	
	return I2C_FAIL;
}



I2C_MIDDLEWARE_STATUS_t I2C_receive_mem(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout )
{


		if(HAL_I2C_Mem_Read(hi2c, DevAddress,MemAddress,I2C_MEMADD_SIZE_8BIT, pData, Size,Timeout) != HAL_OK)
		{
			
		}



		if (HAL_I2C_GetError(hi2c) == HAL_I2C_ERROR_NONE){
				return I2C_SUCCSS;
		}
	
	return I2C_FAIL;
}	


void I2C_PINS_GPIO_INIT(){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /*Configure GPIO pin : PB9 | PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}	
	
/* rapidly toggle the i2c lines to get it unstuck
 * Workaround to solve this mysterious problem where the sda line
 * appears to get stuck low.
 */
I2C_MIDDLEWARE_STATUS_t reinit_i2c(I2C_HandleTypeDef* hi2c)
{
	PRINTF("REINITALISING GPS. Powercycling first");

	/* disable power to GPS */
	HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPS_EN_PIN, GPIO_PIN_SET); 
	HAL_Delay(100);
  
  /* De-initialize the I2C comunication bus */
  HAL_I2C_MspDeInit(hi2c);
  
	/* Make I2C bus pins GPIO */
	I2C_PINS_GPIO_INIT();
	
	/* set i2c pins low to ensure it cannot power up the core of the GPS */
	HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPIO_PIN_9|GPIO_PIN_8, GPIO_PIN_RESET); 
	HAL_Delay(1000);
	
	/* Enable power to GPS */
	HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPS_EN_PIN, GPIO_PIN_RESET); 
	HAL_Delay(1000);
	
	/* send 9 clock pulses to the GPS ref: https://www.microchip.com/forums/FindPost/175578 */
	for (uint8_t i = 0; i < 9; i++)
	{
		HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPIO_PIN_8, GPIO_PIN_RESET); 
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPS_EN_GPIO_Port, GPIO_PIN_8, GPIO_PIN_SET); 
		HAL_Delay(1);

	}
	
	/* Re-Initiaize the I2C comunication bus */
	HAL_I2C_MspInit(hi2c);

	return I2C_SUCCSS;
}
