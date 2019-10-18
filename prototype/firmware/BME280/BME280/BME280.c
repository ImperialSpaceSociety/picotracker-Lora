/*
 * BME280.c
 *
 * Created: 05/05/2019 15:30:16
 *  Author: richard
 */ 
// Derived Work from:
// BME280 temperature/pressure/humidity sensor
// prototyping code to read and calculate calibrated values
// from the I2C bus
//
// Written by Larry Bank - 2/1/2017
// Copyright (c) 2017 BitBank Software, Inc.
// bitbank@pobox.com
//

#include <stdio.h>
#include <stdint.h>
#include "driver_init.h"

struct io_descriptor *I2C_0_io;


// Sensor calibration data
static int calT1,calT2,calT3;
static int calP1, calP2, calP3, calP4, calP5, calP6, calP7, calP8, calP9;
static int calH1, calH2, calH3, calH4, calH5, calH6;

//
// Opens a file system handle to the I2C device
// reads the calibration data and sets the device
// into auto sensing mode
//
int bme280Init(int iAddr)
{
	int i, rc;
	uint8_t ucTemp[32];
	unsigned char ucCal[36];

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, iAddr, I2C_M_SEVEN);

	ucTemp[0] = 0xd0; // get ID
	rc = io_write(I2C_0_io, ucTemp, 1);
	
	i = io_read(I2C_0_io, ucTemp, 1);
	
	if (rc < 0 || i != 1 || ucTemp[0] != 0x60)
	{
		printf("Error, ID doesn't match 0x60; wrong device?\n");
		return -1;
	}
	// Read 24 bytes of calibration data
	ucTemp[0] = 0x88; // starting 4from register 0x88
	rc = io_write(I2C_0_io, ucTemp, 1);
	i = io_read(I2C_0_io, ucCal, 24);
	if (rc < 0 || i != 24)
	{
		printf("calibration data not read correctly\n");
		return -1;
	}
	ucTemp[0] = 0xa1; // get humidity calibration byte
	rc = io_write(I2C_0_io, ucTemp, 1);
	i = io_read(I2C_0_io, &ucCal[24], 1);
	ucTemp[0] = 0xe1; // get 7 more humidity calibration bytes
	rc = io_write(I2C_0_io, ucTemp, 1);
	i = io_read(I2C_0_io, &ucCal[25], 7);
	if (rc < 0 || i < 0) // something went wrong
	{}
	// Prepare temperature calibration data
	calT1 = ucCal[0] + (ucCal[1] << 8);
	calT2 = ucCal[2] + (ucCal[3] << 8);
	if (calT2 > 32767) calT2 -= 65536; // negative value
	calT3 = ucCal[4] + (ucCal[5] << 8);
	if (calT3 > 32767) calT3 -= 65536;
	
	// Prepare pressure calibration data
	calP1 = ucCal[6] + (ucCal[7] << 8);
	calP2 = ucCal[8] + (ucCal[9] << 8);
	if (calP2 > 32767) calP2 -= 65536; // signed short
	calP3 = ucCal[10] + (ucCal[11] << 8);
	if (calP3 > 32767) calP3 -= 65536;
	calP4 = ucCal[12] + (ucCal[13] << 8);
	if (calP4 > 32767) calP4 -= 65536;
	calP5 = ucCal[14] + (ucCal[15] << 8);
	if (calP5 > 32767) calP5 -= 65536;
	calP6 = ucCal[16] + (ucCal[17] << 8);
	if (calP6 > 32767) calP6 -= 65536;
	calP7 = ucCal[18] + (ucCal[19] << 8);
	if (calP7 > 32767) calP7 -= 65536;
	calP8 = ucCal[20] + (ucCal[21] << 8);
	if (calP8 > 32767) calP8 -= 65536;
	calP9 = ucCal[22] + (ucCal[23] << 8);
	if (calP9 > 32767) calP9 -= 65536;

	// Prepare humidity calibration data
	calH1 = ucCal[24];
	calH2 = ucCal[25] + (ucCal[26] << 8);
	if (calH2 > 32767) calH2 -= 65536;
	calH3 = ucCal[27];
	calH4 = (ucCal[28] << 4) + (ucCal[29] & 0xf);
	if (calH4 > 2047) calH4 -= 4096; // signed 12-bit
	calH5 = (ucCal[30] << 4) + (ucCal[29] >> 4);
	if (calH5 > 2047) calH5 -= 4096;
	calH6 = ucCal[31];
	if (calH6 > 127) calH6 -= 256; // signed char

	ucTemp[0] = 0xf2; // control humidity register
	ucTemp[1] = 0x01; // humidity over sampling rate = 1
	rc = io_write(I2C_0_io, ucTemp, 2);

	ucTemp[0] = 0xf4; // control measurement register
	ucTemp[1] = 0x27; // normal mode, temp and pressure over sampling rate=1
	rc = io_write(I2C_0_io, ucTemp, 2);

	ucTemp[0] = 0xf5; // CONFIG
	ucTemp[1] = 0xa0; // set stand by time to 1 second
	rc = io_write(I2C_0_io, ucTemp, 2);
	if (rc < 0) {} // suppress warning

	return 0;

	} /* bme280Init() */

	//
	// Read the sensor register values
	// and translate them into calibrated readings
	// using the previously loaded calibration data
	// Temperature is expressed in Celsius degrees as T * 100 (for 2 decimal places)
	// Pressure is <future>
	// Humidity is express as H * 1024 (10 bit fraction)
	//
	int bme280ReadValues(int *T, int *P, int *H)
	{
		unsigned char ucTemp[16];
		int i,rc;
		int t, p, h; // raw sensor values
		int var1,var2,t_fine;
		int64_t P_64;
		int64_t var1_64, var2_64;

		ucTemp[0] = 0xf7; // start of data registers we want
		rc = io_write(I2C_0_io, ucTemp, 1); // write address of register to read
		i = io_read(I2C_0_io, ucTemp, 8);
		if (rc < 0 || i != 8)
		{
			return -1; // something went wrong
		}
		p = (ucTemp[0] << 12) + (ucTemp[1] << 4) + (ucTemp[2] >> 4);
		t = (ucTemp[3] << 12) + (ucTemp[4] << 4) + (ucTemp[5] >> 4);
		h = (ucTemp[6] << 8) + ucTemp[7];
		//	printf("raw values: p = %d, t = %d, h = %d\n", p, t, h);
		// Calculate calibrated temperature value
		// the value is 100x C (e.g. 2601 = 26.01C)
		var1 = ((((t >> 3) - (calT1 <<1))) * (calT2)) >> 11;
		var2 = (((((t >> 4) - (calT1)) * ((t>>4) - (calT1))) >> 12) * (calT3)) >> 14;
		t_fine = var1 + var2;
		*T = (t_fine * 5 + 128) >> 8;

		// Calculate calibrated pressure value
		var1_64 = t_fine - 128000;
		var2_64 = var1_64 * var1_64 * (int64_t)calP6;
		var2_64 = var2_64 + ((var1_64 * (int64_t)calP5) << 17);
		var2_64 = var2_64 + (((int64_t)calP4) << 35);
		var1_64 = ((var1_64 * var1_64 * (int64_t)calP3)>>8) + ((var1_64 * (int64_t)calP2)<<12);
		var1_64 = (((((int64_t)1)<<47)+var1_64))*((int64_t)calP1)>>33;
		if (var1_64 == 0)
		{
			*P = 0;
		}
		else
		{
			P_64 = 1048576 - p;
			P_64 = (((P_64<<31)-var2_64)*3125)/var1_64;
			var1_64 = (((int64_t)calP9) * (P_64>>13) * (P_64>>13)) >> 25;
			var2_64 = (((int64_t)calP8) * P_64) >> 19;
			P_64 = ((P_64 + var1_64 + var2_64) >> 8) + (((int64_t)calP7)<<4);
			*P = (int)P_64 / 100;
		}
		// Calculate calibrated humidity value
		var1 = (t_fine - 76800);
		var1 = (((((h << 14) - ((calH4) << 20) - ((calH5) * var1)) +
		(16384)) >> 15) * (((((((var1 * (calH6)) >> 10) * (((var1 * (calH3)) >> 11) + (32768))) >> 10) + (2097152)) * (calH2) + 8192) >> 14));
		var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) * (calH1)) >> 4));
		var1 = (var1 < 0? 0 : var1);
		var1 = (var1 > 419430400 ? 419430400 : var1);
		*H = var1 >> 12;
		return 0;

		} /* bme280ReadValues() */
