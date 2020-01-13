/**
  ******************************************************************************
  * @file           : ms5607.h
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

static char buf0[26]={0,};
static unsigned long D1; // ADC value of the pressure conversion
static unsigned long D2; // ADC value of the temperature conversion
static uint16_t C[8]; // calibration coefficients
static double dT; // difference between actual and measured temperature
static double OFF; // offset at actual temperature
static double SENS; // sensitivity at actual temperature
extern double Pressure; // compensated pressure value
extern double Temperature; // compensated temperature value

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



