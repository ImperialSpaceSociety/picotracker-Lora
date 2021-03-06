/**
  ******************************************************************************
  * @file           : i2c_middleware.h
  * @brief          : I2C middleware for this specific project, using HAL
	*										libraries. The header file
  ******************************************************************************
  * Imperial College Space Society
	* Medad Newman, Richard Ibbotson
  *
  *
  ******************************************************************************
  */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef I2C_MIDDLEWARE_H
#define I2C_MIDDLEWARE_H


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of system and local header files goes here */

#include <stdlib.h>
#include "stm32l0xx_hal.h"
#include "debug.h"

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */



/* ==================================================================== */
/* ========================== public data ============================= */
/* ==================================================================== */

/* Definition of public (external) data types go here */


/**
 * I2C status
 */
typedef enum
{
  I2C_SUCCSS = 0,
	I2C_FAIL
} I2C_MIDDLEWARE_STATUS_t;



/* ==================================================================== */
/* ======================= public functions =========================== */
/* ==================================================================== */

/* Function prototypes for public (external) functions go here */

I2C_MIDDLEWARE_STATUS_t I2C_receive(I2C_HandleTypeDef* hi2c,
																		uint16_t DevAddress,
																		uint8_t *pData, 
																		uint16_t Size, 
																		uint32_t Timeout );
																		
I2C_MIDDLEWARE_STATUS_t I2C_transmit(I2C_HandleTypeDef* hi2c,
																		 uint16_t DevAddress, 
																		 uint8_t *pData, 
																		 uint16_t Size, 
																		 uint32_t Timeout );


I2C_MIDDLEWARE_STATUS_t I2C_receive_mem(I2C_HandleTypeDef* hi2c,
																				uint16_t DevAddress,
																				uint16_t MemAddress,
																				uint8_t *pData,
																				uint16_t Size,
																				uint32_t Timeout );


I2C_MIDDLEWARE_STATUS_t reinit_i2c(I2C_HandleTypeDef* hi2c);


#endif // I2C_MIDDLEWARE_H
#ifdef __cplusplus
}
#endif
