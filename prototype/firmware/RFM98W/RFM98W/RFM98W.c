/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#include <atmel_start.h>
#include "RFM98W.h"



struct io_descriptor *RFM98W_io;


/*
 * Drivers for RFM98W chip
 *
 * 
 */
#include "RFM98W.h"

/* set up the SPI Port and associated GPIO */
void RFM98W_Setup(void)
{
	/* Configure Reset */
	gpio_set_pin_direction(RFM98W_RESET_PIN, GPIO_DIRECTION_OUT);
	gpio_set_pin_level(RFM98W_RESET_PIN, true);
	
	/* Configure Chip Select */
	gpio_set_pin_direction(RFM98W_CS_PIN, GPIO_DIRECTION_OUT);
	gpio_set_pin_level(RFM98W_CS_PIN, true);
	
	/* Configure DIO */
	gpio_set_pin_direction(RFM98W_DIO0_PIN, GPIO_DIRECTION_IN);
	gpio_set_pin_pull_mode(RFM98W_DIO0_PIN,	GPIO_PULL_UP);
	
	gpio_set_pin_direction(RFM98W_DIO1_PIN, GPIO_DIRECTION_IN);
	gpio_set_pin_pull_mode(RFM98W_DIO1_PIN,	GPIO_PULL_UP);
	
	gpio_set_pin_direction(RFM98W_DIO2_PIN, GPIO_DIRECTION_IN);
	gpio_set_pin_pull_mode(RFM98W_DIO2_PIN,	GPIO_PULL_UP);
	
	gpio_set_pin_direction(RFM98W_DIO3_PIN, GPIO_DIRECTION_IN);
	gpio_set_pin_pull_mode(RFM98W_DIO3_PIN,	GPIO_PULL_UP);
	
	gpio_set_pin_direction(RFM98W_DIO4_PIN, GPIO_DIRECTION_IN);
	gpio_set_pin_pull_mode(RFM98W_DIO4_PIN,	GPIO_PULL_UP);
	
	gpio_set_pin_direction(RFM98W_DIO5_PIN, GPIO_DIRECTION_IN);
	gpio_set_pin_pull_mode(RFM98W_DIO5_PIN,	GPIO_PULL_UP);

	/* Configure SPI */
	spi_m_sync_get_io_descriptor(&SPI_0, &RFM98W_io);
	spi_m_sync_enable(&SPI_0);
}


void Set_RFM98W_CS(void)
{
	gpio_set_pin_level(RFM98W_CS_PIN, false);
}

void Clear_RFM98W_CS(void)
{
	gpio_set_pin_level(RFM98W_CS_PIN, true);
}


/* SPI Chip Reset 
 *  */
void reset_RFM98W(void)
{
	gpio_set_pin_level(RFM98W_RESET_PIN, false);
	delay_ms(1);
	gpio_set_pin_level(RFM98W_RESET_PIN, true);
	delay_ms(10);
}

/* Write to an RFM98W register */

void write_RFM98W_Register(uint8_t reg, uint8_t val)
{
	unsigned char data[2];
	
	data[0]= reg | 0x80;
	data[1] = val;

	Set_RFM98W_CS();
	
	io_write(RFM98W_io, data, 2);
	
	Clear_RFM98W_CS();
}

/* Read from an RFM98W Register */

uint8_t read_RFM98W_Register(uint8_t reg)
{
	
	uint8_t	data = reg & 0x7F;
	uint8_t val;

	Set_RFM98W_CS();

	io_write(RFM98W_io, &data, 1);
	io_read(RFM98W_io, &val, 1);

	Clear_RFM98W_CS();

	return val;
}


/* Write to RFM98W FIFO*/

void write_RFM98W_FIFO(uint8_t* data, uint8_t length)
{
	uint8_t reg = REG_FIFO | 0x80;
	Set_RFM98W_CS();
	
	io_write(RFM98W_io, &reg, 1);
	io_write(RFM98W_io, data, length);
	
	Clear_RFM98W_CS();
}

/* Read from RFM98W FIFO*/
void read_RFM98W_FIFO(uint8_t *data, uint8_t length)
{
	uint8_t reg = REG_FIFO;
	Set_RFM98W_CS();
	
	io_write(RFM98W_io, &reg, 1);
	io_read(RFM98W_io, data, length);
	
	Clear_RFM98W_CS();
}




/* Set value of DIO Pin */
void set_RFM98W_DIO(enum dio DIO, uint8_t value)
{
	switch (DIO)
	{
		case DIO0:
			gpio_set_pin_level(RFM98W_DIO0_PIN, value);
			break;
			
		case DIO1:
			gpio_set_pin_level(RFM98W_DIO1_PIN, value);
			break;
		
		case DIO2:
			gpio_set_pin_level(RFM98W_DIO2_PIN, value);
			break;
		
		case DIO3:
			gpio_set_pin_level(RFM98W_DIO3_PIN, value);
			break;
		
		case DIO4:
			gpio_set_pin_level(RFM98W_DIO4_PIN, value);
			break;
		
		case DIO5:
			gpio_set_pin_level(RFM98W_DIO5_PIN, value);
			break;	
			
			
	}
	
	
}

/* Get value of DIO Pin */
uint8_t get_RFM98W_DIO(enum dio DIO)
{
		
		uint8_t retval = 0;
		switch (DIO)
		{
			case DIO0:
			retval = gpio_get_pin_level(RFM98W_DIO0_PIN);
			break;
			
			case DIO1:
			retval = gpio_get_pin_level(RFM98W_DIO1_PIN);
			break;
			
			case DIO2:
			retval = gpio_get_pin_level(RFM98W_DIO2_PIN);
			break;
			
			case DIO3:
			retval = gpio_get_pin_level(RFM98W_DIO3_PIN);
			break;
			
			case DIO4:
			retval = gpio_get_pin_level(RFM98W_DIO4_PIN);
			break;
			
			case DIO5:
			retval = gpio_get_pin_level(RFM98W_DIO5_PIN);
			break;
			
			
		}
	
	return retval;
}

/* Configure mode of DIO Pin */

void configure_RFM98W_DIO(enum dio DIO,  enum gpio_direction direction,  enum gpio_pull_mode pullup)
{
	switch (DIO)
	{
		case DIO0:
		gpio_set_pin_direction(RFM98W_DIO0_PIN, direction);
		gpio_set_pin_pull_mode(RFM98W_DIO0_PIN,	pullup);
		break;
		
		case DIO1:
		gpio_set_pin_direction(RFM98W_DIO1_PIN, direction);
		gpio_set_pin_pull_mode(RFM98W_DIO1_PIN,	pullup);
		break;
		
		case DIO2:
		gpio_set_pin_direction(RFM98W_DIO2_PIN, direction);
		gpio_set_pin_pull_mode(RFM98W_DIO2_PIN,	pullup);
		break;
		
		case DIO3:
		gpio_set_pin_direction(RFM98W_DIO3_PIN, direction);
		gpio_set_pin_pull_mode(RFM98W_DIO3_PIN,	pullup);
		break;
		
		case DIO4:
		gpio_set_pin_direction(RFM98W_DIO4_PIN, direction);
		gpio_set_pin_pull_mode(RFM98W_DIO4_PIN,	pullup);
		break;
		
		case DIO5:
		gpio_set_pin_direction(RFM98W_DIO5_PIN, direction);
		gpio_set_pin_pull_mode(RFM98W_DIO5_PIN,	pullup);
		break;
		
		
	}
	
}

