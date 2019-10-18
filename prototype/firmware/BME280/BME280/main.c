/* Utility to read the BME Sensor */
/* Not fully tested !!! */

#include <atmel_start.h>
#include "BME280.h"



int main(void)
{
	
	
	
	/* Initializes MCU, drivers and middle ware */
	atmel_start_init();
	
	/* Initialize UART for stdio*/
		
	usart_sync_enable(&EDBG_UART);
	stdio_io_init(&EDBG_UART.io);
	
	
	/* Write Header */
	printf("\r\nBME280 Temperature, Pressure, and Humidity\r\n\n");
	
	int i;
	int T, P, H; // calibrated values
	float fP, fH;

	i = bme280Init(0x76);
	if (i != 0)
	{
	printf("\r\nBME280 sensor not found\r\n\n");
	}
	else
	{
		printf("BME280 device successfully opened.\n");
		delay_ms(100); // wait for data to settle for first read
	}
	while(1){
		
		bme280ReadValues(&T, &P, &H);
		T -= 150; // for some reason, the sensor reports temperatures too high
		fP = (float) P / 2.56;
		fH = (float) H / 10.24;
		printf("Calibrated temp. = %d.%d C, pres. = %d.%d Pa, hum. = %d.%d%%\n", T/100, T%100, (int)fP/100, (int) fP%100, (int)fH/100, (int) fH%100);
	
		
		delay_ms(5000);
	}
}
