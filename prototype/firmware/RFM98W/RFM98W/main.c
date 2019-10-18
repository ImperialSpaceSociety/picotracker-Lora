#include <atmel_start.h>
#include "lora.h"


int main(void)

{
	
	uint8_t msg[50] = "$$$$RFM98W Sending Lots of data from Ricky\r\n";
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	
	printf("\r\n\r\nRFM98W Tests\r\n");
	
	if(lora_init() == 1) printf("\r\n LoRa Initialised\r\n");
	
	else printf("\r\n LoRa Initialise Failed\r\n");
	
	
	printf("\r\n Test FSK Mode\r\n");
	
	
	
	
	SendLoRaRTTY(msg, sizeof(msg));
	printf("\r\n Send FSK Message\r\n");
	
	
	
	while (1) {
	CheckFSKBuffers();	
	delay_us(1000);
	
	if(!RTTYSending())
	{
		delay_ms(10000);
		SendLoRaRTTY(msg, sizeof(msg));
	}
	
	}
	
}
