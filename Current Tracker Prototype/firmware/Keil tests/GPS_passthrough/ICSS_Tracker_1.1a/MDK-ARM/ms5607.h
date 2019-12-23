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
#include <stdint.h>



uint16_t cmd_prom(uint8_t coef_num);
void cmd_reset(void);
uint8_t crc4(uint16_t n_prom[]); // n_prom defined as 8x unsigned int (n_prom[8])
unsigned long cmd_adc(char cmd);
HAL_StatusTypeDef ms5607_transmit(uint8_t *pBuffer, uint16_t Length);
HAL_StatusTypeDef ms5607_receive(uint8_t *pBuffer, uint16_t Length);
unsigned long cmd_adc(char cmd);
void MS5607_GET_TEMP_PRESSURE(void);
uint8_t ms5607_Init(void);


