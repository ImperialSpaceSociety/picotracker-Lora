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

#ifndef MS5607_H
#define MS5607_H

#include "stm32l0xx_hal.h"
#include <stdint.h>

/* Variables */



/* Function prototypes*/

HAL_StatusTypeDef ms5607_transmit(uint8_t *pBuffer, uint16_t Length);
HAL_StatusTypeDef ms5607_receive(uint8_t *pBuffer, uint16_t Length);

uint8_t ms5607_Init(void);
uint8_t crc4(uint16_t n_prom[]); // n_prom defined as 8x unsigned int (n_prom[8])
uint16_t cmd_prom(uint8_t coef_num);


unsigned long cmd_adc(char cmd);
unsigned long cmd_adc(char cmd);

void MS5607_get_temp_pressure(void);
void cmd_reset(void);


//extern I2C_HandleTypeDef hi2c1;
//extern uint8_t	i2c_buffer[2];
//extern HAL_StatusTypeDef i2c_status;

#endif // MS5607_H



