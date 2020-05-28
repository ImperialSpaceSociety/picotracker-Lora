/**
  ******************************************************************************
  * @file           : ms5607.c
  * @brief          : Driver file for the ms5607 temperature pressure sensor
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

#include <stdio.h>
#include <math.h>
#include "stm32l0xx_hal.h"
#include "ms5607.h"
#include "main.h"
#include "hw.h"
#include "i2c_middleware.h"


/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */

#define ADDR_W        0xEE  // Module address write mode
#define ADDR_R        0xEF  // Module address read mode
#define CMD_RESET     0x1E  // ADC reset command
#define CMD_ADC_READ  0x00  // ADC read command
#define CMD_ADC_CONV  0x40  // ADC conversion command
#define CMD_ADC_D1    0x00  // ADC D1 conversion
#define CMD_ADC_D2    0x10  // ADC D2 conversion
#define CMD_ADC_256   0x00  // ADC OSR=256
#define CMD_ADC_512   0x02  // ADC OSR=512
#define CMD_ADC_1024  0x04  // ADC OSR=1024
#define CMD_ADC_2048  0x06  // ADC OSR=2048
#define CMD_ADC_4096  0x08  // ADC OSR=4096
#define CMD_ADC_8192  0x0a  //ADC OSR=8192
#define CMD_PROM_RD   0xA0  // Prom read command
#define MS5607_I2C_TIMEOUT 1000


/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */

static unsigned long D1; // ADC value of the pressure conversion
static unsigned long D2; // ADC value of the temperature conversion
static uint16_t C[8]; // calibration coefficients
static double dT; // difference between actual and measured temperature
static double OFF; // offset at actual temperature
static double SENS; // sensitivity at actual temperature



// Temp pressure
double PRESSURE_Value; // compensated pressure value
double TEMPERATURE_Value; // compensated temperature value


/* ==================================================================== */
/* ========================== private data ============================ */
/* ==================================================================== */

/* Definition of private datatypes go here */




/* ==================================================================== */
/* ====================== private functions =========================== */
/* ==================================================================== */

/* Function prototypes for private (static) functions go here */

static uint8_t ms5607_transmit(uint8_t *pBuffer, uint16_t Length);
static uint8_t ms5607_receive(uint8_t *pBuffer, uint16_t Length);
static void cmd_reset(void);
static uint8_t crc4(uint16_t n_prom[]); // n_prom defined as 8x unsigned int (n_prom[8])
static uint16_t cmd_prom(uint8_t coef_num);
static unsigned long cmd_adc(char cmd);

/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

uint8_t ms5607_Init(void)
{
    uint8_t i;
		uint8_t calculated_crc;
		uint8_t factory_crc;

    cmd_reset(); // reset IC
		HAL_Delay(20);

    for (i = 0; i<8; i++) {
        C[i] = cmd_prom(i);   // read coefficients
	//			PRINTF("c:%d\n\r",C[i]);

    }
				
		/* Check if the received values are all zero. if they are, communication error */
		if (!(C[0] && C[1] && C[2] && C[3] && C[4] && C[5] && C[6] && C[7])){
				PRINTF("SELFTEST: ms5607 not returning values. ms5607 NOT OK...\n\r");
        return 1;
		} 
		
		
		factory_crc = 0x000F & (C[7]); // the factory calculated crc
		//PRINTF("factory crc:%d\n\r",factory_crc);
				
    calculated_crc = crc4(C);
		
		//PRINTF("calculated crc:%d\n\r",calculated_crc);

    
		if(calculated_crc==factory_crc){
			  PRINTF("SELFTEST: ms5607 checksum matches. ms5607 OK...\n\r");

        return 0;
		}
    else{
			  PRINTF("SELFTEST: ms5607 checksum not matching. Device NOT OK...\n\r");
        return 1;
		}

}

uint16_t cmd_prom(uint8_t coef_num){
    uint8_t  temp_date[2] = {0};
    uint16_t rC = 0;
    uint8_t i2c_buffer[2] = {0};
    
		i2c_buffer[0] = CMD_PROM_RD+coef_num*2;           

    ms5607_transmit(i2c_buffer,1); // send PROM READ command
    ms5607_receive(temp_date,2);
    rC = 256*temp_date[0]+temp_date[1];

    return rC;
}

void cmd_reset(void)
{
	HAL_Delay(20); // may have to give it a short time to start up if it had been previously powered off
	uint8_t i2c_buffer[2] = {0};
	i2c_buffer[0] = CMD_RESET;
	ms5607_transmit(i2c_buffer,1);
}

uint8_t crc4(uint16_t n_prom[]) // n_prom defined as 8x unsigned int (n_prom[8])
{

	uint8_t cnt; // simple counter
	uint16_t  n_rem = 0; // crc reminder
	uint8_t  n_bit;


	C[7] = (0xFF00 & (C[7]));  //CRC byte is replaced by 00 before calculating crc

	for (cnt = 0; cnt < 16; cnt++) // operation is performed on bytes
	{// choose LSB or MSB
		if (cnt % 2 == 1)
		{ 
			n_rem ^= (unsigned short) ((n_prom[cnt>>1]) & 0x00FF);
		}
		else 
		{
			n_rem ^= (unsigned short) (n_prom[cnt>>1]>>8);
		}

		for (n_bit = 8; n_bit > 0; n_bit--)
		{
			if (n_rem & (0x8000))
			{
				n_rem = (n_rem << 1) ^ 0x3000;
			}
			else
			{
				n_rem = (n_rem << 1);
			}
		}
	}
	

	n_rem = ((n_rem >> 12) & 0x000F); // final 4-bit reminder is CRC code
	return (n_rem ^ 0x00);

}

unsigned long cmd_adc(char cmd)
{
    uint8_t temp_date[3] = {0};

    uint32_t temp = 0;

    uint8_t i2c_buffer[2] = {0};
    i2c_buffer[0] = CMD_ADC_CONV+cmd;

    ms5607_transmit(i2c_buffer,1); // send conversion command

    switch (cmd & 0x0f) // wait necessary conversion time
    {

    case CMD_ADC_256 :
        HAL_Delay(1);
        break;

    case CMD_ADC_512 :
        HAL_Delay(3);
        break;

    case CMD_ADC_1024:
        HAL_Delay(10);
        break;

    case CMD_ADC_2048:
        HAL_Delay(6);
        break;

    case CMD_ADC_4096:
        HAL_Delay(10);
        break;

    case CMD_ADC_8192:
        HAL_Delay(20);
        break;

    }

    i2c_buffer[0] = CMD_ADC_READ;

    ms5607_transmit(i2c_buffer,1);
    ms5607_receive(temp_date,3);

    temp = 65536*temp_date[0]+256*temp_date[1]+temp_date[2];
		
    return temp;
}

uint8_t ms5607_transmit( uint8_t *message, uint16_t len)
{
	
		I2C_MIDDLEWARE_STATUS_t status = I2C_transmit(&hi2c1, (uint16_t)ADDR_W, message, len, MS5607_I2C_TIMEOUT);
		
		if (status == I2C_SUCCSS)
		{
			return 1;
		}else
		{
			return 0;	
		}

}

uint8_t ms5607_receive(uint8_t *message, uint16_t len)
{
	

	I2C_MIDDLEWARE_STATUS_t status = I2C_receive(&hi2c1, (uint16_t)ADDR_R, message, len, MS5607_I2C_TIMEOUT);
	
	if (status == I2C_SUCCSS)
	{
		return 1;
	}else
	{
		return 0;	
	}

}

void ms5607_Read_T(void)
{
    D2 = cmd_adc(CMD_ADC_D2+CMD_ADC_1024); // read D2
}

void ms5607_Read_P(void)
{
    D1 = cmd_adc(CMD_ADC_D1+CMD_ADC_1024); // read D1
}

void ms5607_Cal_T_P(void)
{
    // calculate 1st order pressure and temperature (MS5607 1st order algorithm)
    dT = D2-C[5]*pow(2,8);
    OFF = C[2]*pow(2,17)+dT*C[4]/pow(2,6);
    SENS = C[1]*pow(2,16)+dT*C[3]/pow(2,7);
    TEMPERATURE_Value = (2000+(dT*C[6])/pow(2,23))/100;
	  PRESSURE_Value = (((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100;
}


void MS5607_get_temp_pressure(void)
{
	ms5607_Read_T();
	ms5607_Read_P();
	ms5607_Cal_T_P();
}
