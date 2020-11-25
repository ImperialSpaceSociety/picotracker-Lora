/**
  ******************************************************************************
  * @file           : ms5607.h
  * @brief          : Driver header file for MS5607.c
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

#ifndef MS5607_H
#define MS5607_H


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of system and local header files goes here */

#include <stdint.h>


/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */



/* ==================================================================== */
/* ========================== public data ============================= */
/* ==================================================================== */

/* Definition of public (external) data types go here */



extern double PRESSURE_Value; // compensated pressure value
extern double TEMPERATURE_Value; // compensated temperature value



/* ==================================================================== */
/* ======================= public functions =========================== */
/* ==================================================================== */

/* Function prototypes for public (external) functions go here */

uint8_t ms5607_Init(void);
void MS5607_get_temp_pressure(void);


#endif
#ifdef __cplusplus
}
#endif

