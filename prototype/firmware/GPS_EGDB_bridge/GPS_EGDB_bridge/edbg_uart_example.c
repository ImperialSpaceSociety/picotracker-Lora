/**
* \file
*
* \brief Application implement
*
* Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
*
* \asf_license_start
*
* \page License
*
* Subject to your compliance with these terms, you may use Microchip
* software and any derivatives exclusively with Microchip products.
* It is your responsibility to comply with third party license terms applicable
* to your use of third party software (including open source software) that
* may accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
* INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
* AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
* LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
* LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
* SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
* ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
* RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*
* \asf_license_stop
*
*/
/*
* Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
*/

#include "atmel_start.h"
#include "atmel_start_pins.h"
#include <string.h>


//static uint8_t example_hello_world[12] = "Hello World!";

volatile static uint32_t data_from_GPS_arrived = 0;
volatile static uint32_t data_from_MCU_arrived = 0;

uint8_t recv_char_from_GPS;
uint8_t recv_char_from_MCU;


static void tx_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
	gpio_toggle_pin_level(LED0);
}

static void rx_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* Receive completed */
	data_from_MCU_arrived = 1;
}

static void tx_cb_USART(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
	gpio_toggle_pin_level(LED0);
}

static void rx_cb_USART(const struct usart_async_descriptor *const io_descr)
{
	/* Receive completed */
	data_from_GPS_arrived = 1;
}



static void bridge_gps_to_com_port(){
	
	// read data from GPS and send it on to MCU
	if (data_from_GPS_arrived == 1) {
		while (io_read(&USART_0.io, &recv_char_from_GPS, 1) == 1) {
			while (io_write(&EDBG_COM.io, &recv_char_from_GPS, 1) != 1) {
			}
		}
		data_from_GPS_arrived = 0;
	}
			
	// read data from MCU and send it on to GPS
	if (data_from_MCU_arrived == 1) {
		while (io_read(&EDBG_COM.io, &recv_char_from_MCU, 1) == 1) {
			while (io_write(&USART_0.io, &recv_char_from_MCU, 1) != 1) {
			}
		}
		data_from_MCU_arrived = 0;
	}
	
}





int main(void)
{


	atmel_start_init();

	/* setup usart from GPS to comp port */
	usart_async_register_callback(&EDBG_COM, USART_ASYNC_TXC_CB, tx_cb_EDBG_COM);
	usart_async_register_callback(&EDBG_COM, USART_ASYNC_RXC_CB, rx_cb_EDBG_COM);
	
	usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, tx_cb_USART);
	usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, rx_cb_USART);
	
	usart_async_enable(&EDBG_COM);
	usart_async_enable(&USART_0);
	

	


	// main loop
	while (1) {
		bridge_gps_to_com_port();	
		
		
		

	}
	
}




