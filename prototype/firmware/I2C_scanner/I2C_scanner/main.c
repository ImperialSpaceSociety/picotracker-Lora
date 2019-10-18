/* Discover devices on the I2C Bus */

#include <atmel_start.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Initialise UART for stdio*/
	
	
	usart_sync_enable(&TARGET_IO);
	stdio_io_init(&TARGET_IO.io);
	
	
	/* Write Header */
	printf("\r\nI2C Scanner\r\n\n");
	
	/* Initialise I2C */
	
	struct io_descriptor *I2C_io;
	struct _i2c_m_msg msg;
	uint8_t	 reg;

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_io);
	i2c_m_sync_enable(&I2C_0);
	
	msg.len    = 1;
	msg.flags  = I2C_M_STOP;
	msg.buffer = &reg;
	

	
	while (1) {
		uint8_t address;
		int16_t nDevices;
		int32_t error;

		printf("Scanning...\r\n");
		nDevices = 0;
		for(address = 8; address < 120; address++ )
		{
			msg.addr   = address;
			
			error = i2c_m_sync_transfer(&I2C_0, &msg);
			if (error == 0)
			{
				printf("I2C device found at 0x%x\r\n", address);
				

				nDevices++;
			}
			
		}
		if (nDevices == 0)
		printf("No devices found !\r\n");
		else
		printf("done\r\n\n");
	
		delay_ms(5000); // wait 5 seconds for next scan
		
		
	}
}
