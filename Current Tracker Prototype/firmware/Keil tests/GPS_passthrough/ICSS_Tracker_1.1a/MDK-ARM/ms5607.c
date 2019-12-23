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
#define I2cxTimeout   3000



#include <stdio.h>
#include <math.h>
#include "stm32l0xx_hal.h"
#include "ms5607.h"
 
 
extern I2C_HandleTypeDef hi2c1;
extern uint8_t	i2c_buffer[16];
extern HAL_StatusTypeDef i2c_status;



char buf0[26]={0,};
unsigned long D1; // ADC value of the pressure conversion
unsigned long D2; // ADC value of the temperature conversion
uint16_t C[8]; // calibration coefficients
double P; // compensated pressure value
double T; // compensated temperature value
double dT; // difference between actual and measured temperature
double OFF; // offset at actual temperature
double SENS; // sensitivity at actual temperature

uint8_t ms5607_Init(void)
{
    uint8_t i;
		uint8_t calculated_crc;
		uint8_t factory_crc;

    cmd_reset(); // reset IC

    for (i=0; i<8; i++) {
        C[i]=cmd_prom(i);   // read coefficients
    }
		
		factory_crc = 0x000F & (C[7]); // the factory calculated crc
		

		
    calculated_crc=crc4(C);
    
		if(calculated_crc==factory_crc)
        return 0;
    else
        return 1;

}

uint16_t cmd_prom(uint8_t coef_num){
    uint8_t  temp_date[2]= {0};
    unsigned int rC=0;
    uint8_t Buffer[2]={0};
    
		Buffer[0]=CMD_PROM_RD+coef_num*2;           

    ms5607_transmit(Buffer,1); // send PROM READ command
    ms5607_receive(temp_date,2);
    rC=256*temp_date[0]+temp_date[1];

    return rC;
}

void cmd_reset(void)
{
	uint8_t Buffer[2]={0};
	Buffer[0]=CMD_RESET;
	ms5607_transmit(Buffer,1);
}

uint8_t crc4(uint16_t n_prom[]) // n_prom defined as 8x unsigned int (n_prom[8])
{

	int cnt; // simple counter
	uint16_t  n_rem=0; // crc reminder
	uint8_t  n_bit;


	C[7]=(0xFF00 & (C[7]));  //CRC byte is replaced by 00 before calculating crc

	for (cnt = 0; cnt < 16; cnt++) // operation is performed on bytes
	{// choose LSB or MSB
		if (cnt%2==1)
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
    uint8_t  temp_date[3]= {0};

    unsigned long temp=0;

    uint8_t Buffer[2]={0};
    Buffer[0]=CMD_ADC_CONV+cmd;

    ms5607_transmit(Buffer,1); // send conversion command

    switch (cmd & 0x0f) // wait necessary conversion time
    {

    case CMD_ADC_256 :
        HAL_Delay(1);
        break;

    case CMD_ADC_512 :
        HAL_Delay(3);
        break;

    case CMD_ADC_1024:
        HAL_Delay(4);
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

    Buffer[0]=CMD_ADC_READ;

    ms5607_transmit(Buffer,1);
    ms5607_receive(temp_date,3);

    temp=65536*temp_date[0]+256*temp_date[1]+temp_date[2];
		
    return temp;
}

HAL_StatusTypeDef ms5607_transmit( uint8_t *pBuffer, uint16_t Length)
{
    HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)ADDR_W,  pBuffer, Length, 100);
    HAL_Delay(5);

    if(status != HAL_OK)
    {
        //I2C_Error();
    }
    return status;
}

HAL_StatusTypeDef ms5607_receive(uint8_t *pBuffer, uint16_t Length)
{
    HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Master_Receive(&hi2c1, (uint16_t)ADDR_R,  pBuffer, Length, 100);

    if(status != HAL_OK)
    {
			//I2C_Error();
    }
		
    return status;
}

void ms5607_Read_T(void)
{
    D2=cmd_adc(CMD_ADC_D2+CMD_ADC_256); // read D2
}

void ms5607_Read_P(void)
{
    D1=cmd_adc(CMD_ADC_D1+CMD_ADC_256); // read D1
}

void ms5607_Cal_T_P(void)
{
    // calculate 1st order pressure and temperature (MS5607 1st order algorithm)
    dT=D2-C[5]*pow(2,8);
    OFF=C[2]*pow(2,17)+dT*C[4]/pow(2,6);
    SENS=C[1]*pow(2,16)+dT*C[3]/pow(2,7);
    T =(2000+(dT*C[6])/pow(2,23))/100;
    P =(((D1*SENS)/pow(2,21)-OFF)/pow(2,15))/100;
	  
		printf("Temperature degrees C: "); 
		printf("%lf", T); 
		printf("\r\n"); 
		printf("Pressure mBar: "); 
		printf("%lf", P); 
		printf("\r\n"); 
	
	

}


void MS5607_GET_TEMP_PRESSURE(void)
{

	ms5607_Read_T();
	ms5607_Read_P();
	ms5607_Cal_T_P();
}
