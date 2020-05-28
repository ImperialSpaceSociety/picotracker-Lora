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






/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

I2C_MIDDLEWARE_STATUS_t I2C_receive(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout )
{
	/* Init tickstart for timeout management*/
	uint32_t tickstart = HAL_GetTick();
	while ((HAL_GetTick() - tickstart) < Timeout){

		if(HAL_I2C_Master_Receive_IT(hi2c, DevAddress, pData, Size)!= HAL_OK)
		{
			/* Error_Handler() function is called when error occurs. */
			Error_Handler();
		}

		/* wait until I2C comms is completed */
		while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY)
		{
			
		} 


		if (HAL_I2C_GetError(hi2c) == HAL_I2C_ERROR_NONE){
				return I2C_SUCCSS;
		}
	}
	
	return I2C_FAIL;
}	


/*
    Transmits a desired UBX message across I2C1.
*/
I2C_MIDDLEWARE_STATUS_t I2C_transmit(I2C_HandleTypeDef* hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout )
{
	/* Init tickstart for timeout management*/
	uint32_t tickstart = HAL_GetTick();
	while ((HAL_GetTick() - tickstart) < Timeout){

		if(HAL_I2C_Master_Transmit_IT(hi2c, DevAddress, pData, Size)!= HAL_OK)
		{
			/* Error_Handler() function is called when error occurs. */
			Error_Handler();
		}

		/* wait until I2C comms is completed */
		while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY)
		{
			
		} 


		if (HAL_I2C_GetError(hi2c) == HAL_I2C_ERROR_NONE){
				return I2C_SUCCSS;
		}
	}
	
	return I2C_FAIL;
}
