/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAML21 has 9 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8

/* GPIO Pins */
#define PA15 GPIO(GPIO_PORTA, 15)
#define PA16 GPIO(GPIO_PORTA, 16)
#define PB00 GPIO(GPIO_PORTB, 00)
#define PB01 GPIO(GPIO_PORTB, 01)
#define PB10 GPIO(GPIO_PORTB, 10)
#define PB11 GPIO(GPIO_PORTB, 11)
#define PB17 GPIO(GPIO_PORTB, 17)
#define PB30 GPIO(GPIO_PORTB, 30)



#define PA22 GPIO(GPIO_PORTA, 22) // EDBG TXD
#define PA23 GPIO(GPIO_PORTA, 23) // EDBG RXD
#define PB16 GPIO(GPIO_PORTB, 16) // SPI MISO
#define PB22 GPIO(GPIO_PORTB, 22) // SPI MOSI
#define PB23 GPIO(GPIO_PORTB, 23) // SPI SCK

#endif // ATMEL_START_PINS_H_INCLUDED
