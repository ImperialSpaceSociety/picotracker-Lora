/*
 * gps.h
 *
 * Created: 10 May 2019 21:05:36
 *  Author: Medad Newman
 */ 


/*
 * Functions for the UBLOX 8 GPS
 *  
 * Derived Work Copyright (c) 2018 Imperial College Space Society
 * From original work Copyright (C) 2014  Richard Meadows <richardeoin>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GPS_H
#define GPS_H

#include <stdint.h>
#include "fix.h"



#define UART_RX_BUFFER_LENGTH   120
#define UBX_CFG_RETRIES         3
#define UBX_CFG_TIMEOUT         60000     // timeout 
#define UBX_POLL_RETRIES        3       
#define UBX_POLL_TIMEOUT        1000000l     // timeout

#define RX_TIMEOUT_MS           1920
#define UART_BAUDRATE           96
//#define test_period             1920

void UART_send_buffer(char *cmd, uint8_t length);

uint8_t gps_set_gps_only(void);
uint8_t gps_disable_nmea_output(void);
uint8_t gps_set_airborne_model(void);
uint8_t gps_set_power_save(void);
uint8_t gps_power_save(int on);
uint8_t gps_save_settings(void);
uint8_t gps_get_fix(struct gps_fix *fix);
uint8_t gps_wake_up(void);
uint8_t gps_cfg_reset(void);

void gps_startup_delay(void);


uint8_t SERCOM_USART_read_byte(uint32_t * timeout);






#endif /* GPS_H */
