/**
 * GPS_Passthrough
 *
 * Test Routine for UBlox GPS Test for pass through to uCenter
 * GPS is on SERCOM1 EXT 3 port
 * PC connection is on SERCOM3 EDBG USB CDC port
 *
 */

/* This seems a bit odd. Is this not the latest ASF version ? */

/* Modified the usart.c file so it does not wait for transmit complete ! */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

struct usart_module edbg_uart;
struct usart_module gps_uart;


void configure_edbg_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate    = 9600;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	while (usart_init(&edbg_uart,
	EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}
	usart_enable(&edbg_uart);
}
void configure_gps_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate    = 9600;
	config_usart.mux_setting = EXT3_UART_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EXT3_UART_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EXT3_UART_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EXT3_UART_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EXT3_UART_SERCOM_PINMUX_PAD3;
	while (usart_init(&gps_uart,
	EXT3_UART_MODULE, &config_usart) != STATUS_OK) {
	}
	usart_enable(&gps_uart);
}


int main (void)
{
	uint16_t temp;
	
	system_init();
	
	configure_edbg_usart();
	configure_gps_usart();
	
	
	while(1){
		
		if (usart_read_wait(&gps_uart, &temp) == STATUS_OK) {
			while (usart_write_wait(&edbg_uart, temp) != STATUS_OK) {
			}
		}
		
		if (usart_read_wait(&edbg_uart, &temp) == STATUS_OK) {
			while (usart_write_wait(&gps_uart, temp) != STATUS_OK) {
			}
		}
		
		
	}
}
	


