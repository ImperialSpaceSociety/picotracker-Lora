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
#include "main.h"


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


void I2C_pins_GPIO_OUTPUT_init(void);
void I2C_pins_GPIO_INPUT_init(void);




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

void I2C_pins_GPIO_INPUT_init(){
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Configure SDA,SCL pin as input */
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}

void I2C_pins_GPIO_OUTPUT_init(){

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
  
	PRINTF("I2C ERROR!");	

	/* Re-Initiaize the I2C comunication bus */	
	HAL_StatusTypeDef status = HAL_I2C_DeInit(hi2c);
	
	
	switch(status) {
		
		case HAL_ERROR:
		PRINTF("HAL_ERROR deinit i2c error\n");	
		break; 

		case HAL_OK:
		PRINTF("HAL_OK deinit\n");	
		break; 

		/* you can have any number of case statements */
		default: 
		PRINTF("unknown deinit i2c error\n");	
	}
	
	HAL_Delay(20);
	
	
	status = HAL_I2C_Init(hi2c);
	
	switch(status) {
		
		case HAL_ERROR:
		PRINTF("HAL_ERROR init i2c error\n");	
		break; 

		case HAL_OK:
		PRINTF("HAL_OK init\n");	
		break; 

		/* you can have any number of case statements */
		default: 
		PRINTF("unknown init i2c error\n");	
	}
	
	HAL_IWDG_Refresh(&hiwdg);

	return I2C_SUCCSS;
}
