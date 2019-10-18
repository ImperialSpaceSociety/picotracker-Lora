/*
 * BME280.h
 *
 * Created: 05/05/2019 15:27:04
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


#ifndef __BME280__
#define __BME280__

int bme280Init(int iAddr);
int bme280ReadValues(int *T, int *P, int *H);

#endif // __BME280__