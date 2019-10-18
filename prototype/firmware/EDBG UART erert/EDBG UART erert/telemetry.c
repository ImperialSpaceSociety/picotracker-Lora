/*
* Telemetry strings and formatting
* 
* for Pico Balloon Tracker using HC12 radio module and GPS
* HC12 Module with STM8S003F3 processor and silabs Si4463 Radio
*  
* Derived Work Copyright (c) 2018 Imperial College Space Society
* From original work Copyright (C) 2014  Richard Meadows <richardeoin>
*
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

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "telemetry.h"
#include "string.h"
#include "fix.h"
#include "main.h"


/* A lot of work for the telemetry and gps communication is taken from 
* https://github.com/thasti/utrak
*/



extern volatile uint16_t tlm_tick;
extern uint16_t tx_buf_rdy;
extern uint16_t tx_buf_length;
extern char tx_buf[TX_BUF_MAX_LENGTH];
extern char telemetry_string[TX_BUF_MAX_LENGTH];
extern struct gps_fix current_fix;

/* calculated sentence ID length, used for variable length buffer */
uint16_t tlm_sent_id_length;
uint16_t tlm_alt_length;

/**
* TELEMETRY OUTPUT
* =============================================================================
*/

/**
* The type of telemetry we're currently outputting
*/
enum telemetry_t telemetry_type;
/**
* Current output
*/
int8_t telemetry_string_length = 0;
/**
* Where we are in the current output
*/
int8_t telemetry_index;
/**
* Is the radio currently on?
*/
uint8_t radio_on = 0;



/**
* CYCLIC REDUNDANCY CHECK (CRC)
* =============================================================================
*/

/**
* CRC Function for the XMODEM protocol.
* http://www.nongnu.org/avr-libc/user-manual/group__util__crc.html#gaca726c22a1900f9bad52594c8846115f
*/
uint16_t crc_xmodem_update(uint16_t crc, uint8_t data)
{
	int i;
	
	crc = crc ^ ((uint16_t)data << 8);
	for (i = 0; i < 8; i++) {
		if (crc & 0x8000) {
			crc = (crc << 1) ^ 0x1021;
		} else {
			crc <<= 1;
		}
	}
	
	return crc;
}

/**
* Calcuates the CRC checksum for a communications string
* See http://ukhas.org.uk/communication:protocol
*/
uint16_t calculate_txbuf_checksum(void)
{
	size_t i;
	uint16_t crc;
	crc = 0xFFFF;
	
	for (i = TX_BUF_CHECKSUM_BEGIN; i < TX_BUF_CHECKSUM_END; i++) {
		crc = crc_xmodem_update(crc, tx_buf[i]);
	}
	
	return crc;
}


/*
* prepare_tx_buffer
*
* fills tx_buf with telemetry values. this depends on the
* GPS having a fix and telemetry being extracted before
*
* telemetry format:
* - callsign
* - sentence id
* - time
* - latitude
* - longitude
* - altitude
* - available satellites
* - voltage of the AAA cell(after boosting)
* - op status
* - temperature of radio

*/
void prepare_tx_buffer(void) {
	static uint16_t sent_id = 0;
	int i;
	uint16_t crc;
	
	sent_id++;
	tlm_sent_id_length = i16toav(sent_id, &tx_buf[TX_BUF_SENT_ID_START]);
	tx_buf[TX_BUF_SENT_ID_START + tlm_sent_id_length] = ',';
	
	i16toa(current_fix.hour, 2, &tx_buf[TX_BUF_TIME_START]);
	i16toa(current_fix.min, 2, &tx_buf[TX_BUF_TIME_START + 2]);
	i16toa(current_fix.sec, 2, &tx_buf[TX_BUF_TIME_START + 4]);
	tx_buf[TX_BUF_TIME_START + TIME_LENGTH] = ',';
	
	if (current_fix.lat > 0) {
		tx_buf[TX_BUF_LAT_START] = '+';
		i32toa(current_fix.lat, 9, &tx_buf[TX_BUF_LAT_START + 1]);
	} else {
		tx_buf[TX_BUF_LAT_START] = '-';
		i32toa(0 - current_fix.lat, 9, &tx_buf[TX_BUF_LAT_START + 1]);
	}
	/* copy fraction of degrees one character towards the end, insert dot */
	/* 012XXXXXX -> 012 XXXXXX */
	for (i = 8; i >= 3; i--) {
		tx_buf[TX_BUF_LAT_START + i + 1] = tx_buf[TX_BUF_LAT_START + i];	
	}
	tx_buf[TX_BUF_LAT_START + 3] = '.';
	tx_buf[TX_BUF_LAT_START + LAT_LENGTH + 1] = ',';
	
	if (current_fix.lon > 0) {
		tx_buf[TX_BUF_LON_START] = '+';
		i32toa(current_fix.lon, 10, &tx_buf[TX_BUF_LON_START + 1]);
	} else {
		tx_buf[TX_BUF_LON_START] = '-';
		i32toa(0 - current_fix.lon, 10, &tx_buf[TX_BUF_LON_START + 1]);
	}
	/* copy fraction of degrees one character towards the end, insert dot */
	/* 51XXXXXX -> 51 XXXXXX */
	for (i = 9; i >= 4; i--) {
		tx_buf[TX_BUF_LON_START + i + 1] = tx_buf[TX_BUF_LON_START + i];	
	}
	tx_buf[TX_BUF_LON_START + 4] = '.';
	tx_buf[TX_BUF_LON_START + LON_LENGTH + 1] = ',';
	
	tlm_alt_length = i16toav(current_fix.alt, &tx_buf[TX_BUF_ALT_START]);
	tx_buf[TX_BUF_ALT_START + tlm_alt_length] = ',';
	
	i16toa(current_fix.num_svs, SAT_LENGTH, &tx_buf[TX_BUF_SAT_START]);
	tx_buf[TX_BUF_SAT_START + SAT_LENGTH] = ',';
	
	i16toa(current_fix.voltage_radio, VOLT_LENGTH, &tx_buf[TX_BUF_VOLT_START]);
	tx_buf[TX_BUF_VOLT_START + VOLT_LENGTH] = ',';
	
	i16toa(current_fix.op_status, OP_STAT_LENGTH, &tx_buf[TX_BUF_OP_STAT_START]);
	tx_buf[TX_BUF_OP_STAT_START + OP_STAT_LENGTH] = ',';
	
	if (current_fix.temp_BME280 < 0) {
		tx_buf[TX_BUF_TEMP_START] = '-';
		i16toa(0 - current_fix.temp_BME280, TEMP_LENGTH, &tx_buf[TX_BUF_TEMP_START + 1]);
	} else {
		tx_buf[TX_BUF_TEMP_START] = '+';
		i16toa(current_fix.temp_BME280, TEMP_LENGTH, &tx_buf[TX_BUF_TEMP_START + 1]);
	}
	
	tx_buf[TX_BUF_TEMP_START + TEMP_LENGTH + 1] = '*';
	
	crc = calculate_txbuf_checksum();
	i16tox(crc, &tx_buf[TX_BUF_CHECKSUM_START]);
	
	for (i = 0; i < TX_BUF_POSTFIX_LENGTH; i++)
		tx_buf[TX_BUF_POSTFIX_START + i] = TX_BUF_POSTFIX[i];
	
	tx_buf_length = TX_BUF_FRAME_END;
	/* trigger transmission */
	tx_buf_rdy = 1;
}

void tlm_init(void) {
	tx_buf_rdy = 1;
}

/*
* init_tx_buffer
*
* helper routine to fill the TX buffer with "x"es - if any of those get transmitted,
* the field handling is not correct
*/
void init_tx_buffer(void) {
	uint16_t i;
	
	for (i = TX_BUF_START_OFFSET; i < TX_BUF_MAX_LENGTH; i++) {
		tx_buf[i] = 'x';
	}
}



