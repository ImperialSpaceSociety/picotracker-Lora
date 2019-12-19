/**
  ******************************************************************************
  * @file           : ms5697.h
  * @brief          : Driver header file for MS5607.c
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */


#include "stm32l0xx_hal.h"


void MS5607_init(void);
void MS5607_get_pressure(uint16_t* pressure, int16_t* temperature);
void MS5607_get_cal(uint32_t* data);


