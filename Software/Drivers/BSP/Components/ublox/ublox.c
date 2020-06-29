/*
 * ublox.c 
 * Author: Medad Newman 23/12/19
 * Imperial College Space Society ( Medad Newman, Richard Ibbotson)
 *
 * modified from TT7's ublox code: 
 * https://github.com/TomasTT7/TT7F-Float-Tracker/blob/99133b762c971b24040d007fff3f1a348941d788/Software/ARM_UBLOX.c
 * Author: Tomy2
 *
 */ 



/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of system and local header files goes here */

#include <stdlib.h>
#include "ublox.h"
#include <stdio.h>
#include "stm32l0xx_hal.h"
#include "main.h"
#include <string.h>
#include "hw.h"

#include "SparkFun_Ublox_Arduino_Library.h"

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */


/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */


float GPS_UBX_latitude_Float							= 51.509865; // YY.YYYYYYY, in +/- DEGREES, temp dummy for testing geofencing
float GPS_UBX_longitude_Float							= -0.118092;  // XXX.XXXXXXX, in +/- DEGREES, temp dummy for testing geofencingstatic 
int32_t GPSaltitude												= 0;
uint8_t GPSsats														= 0;

gps_status_t latest_gps_status;


#if DUMMY_GPS_COORDS

uint16_t dummy_coord_counter  = 0;


/*dummy Coords ARRAYS (longitude, latitude) */
static float dummy_coords_array[] = { 
	126.9833,37.5500,  // South Korea
	126.9833,37.5500,  // South Korea
	126.9833,37.5500,  // South Korea
	126.9833,37.5500,  // South Korea
	13.4000,52.5167,  // Germany
	2.3333,48.8667,  // France
	13.4000,52.5167,  // Germany
	-4.4833,54.1500,  // Isle of Man
	13.4000,52.5167,  // Germany
	2.3333,48.8667,  // France
	24.7167,59.4333,  // Estonia
	25.9000,-24.6333,  // Botswana
	3.0500,36.7500,  // Algeria
	35.2333,31.7667,  // Palestine
	19.8167,41.3167,  // Albania
	-14.411667,-7.928611, // Georgetown, Ascension Island over the sea
	149.1333,-35.2667,  // Australia
	-88.7667,17.2500,  // Belize
	89.6333,27.4667,  // Bhutan
	104.9167,11.5500,  // Cambodia
	15.2833,-4.2500,  // Republic of Congo
	-5.2667,6.8167,  // Cote d'Ivoire
	-16.5667,13.4500,  // The Gambia
	44.8333,41.6833,  // Georgia
	-51.7500,64.1833,  // Greenland
	-61.7500,12.0500,  // Grenada
	-4.4833,54.1500,  // Isle of Man
	35.2333,31.7667,  // Israel
	12.4833,41.9000,  // Italy
	126.9833,37.5500,  // South Korea
	13.1667,32.8833,  // Libya
	101.7000,3.1667,  // Malaysia
	7.4167,43.7333,  // Monaco
};


const unsigned short dummy_coord_n = sizeof(dummy_coords_array) / (sizeof(float)* 2);

#endif




/* ==================================================================== */
/* ========================== private data ============================ */
/* ==================================================================== */

/* Definition of private datatypes go here */





/* ==================================================================== */
/* ====================== private functions =========================== */
/* ==================================================================== */

/* Function prototypes for private (static) functions go here */

gps_status_t get_location_fix(uint32_t timeout);
gps_status_t setup_GPS(void);
gps_status_t get_latest_gps_status(void);

/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

gps_status_t get_latest_gps_status(void)
{
	return latest_gps_status;
}

/* 
 * sets up gps by putting in airbourne mode, setting to use GPS satellites only, turning off NMEA
 * Needs TO BE REFACTORED TO TIME OUT OR EXIT IF NO MESSAGED IS ReCEIVED BACK!
 */
gps_status_t setup_GPS(){
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);   // pull GPS extint0 pin high to wake gps. Really important
	
	PRINTF("Resetting gps\n");
	hardReset();
	
	HAL_Delay(GPS_WAKEUP_TIMEOUT);



	if (isConnected(defaultMaxWait) == false) //Connect to the Ublox module using Wire port
	{
			PRINTF("Ublox GPS not detected at default I2C address. Please check wiring. Freezing.\n");
	}
	else
	{
			PRINTF("Ublox GPS successfully detected. GPS OK...\n");
	}
	
	// set to using ubx only and via the DDC(I2C) port
	PRINTF("Setting UBX only via I2C\n");
	setI2COutput(COM_TYPE_UBX,defaultMaxWait); //Set the I2C port to output UBX only (turn off NMEA noise)
	
	saveConfiguration(defaultMaxWait); //Save the current settings to flash and BBR


	// If we are going to change the dynamic platform model, let's do it here.
	// Possible values are:
	// PORTABLE, STATIONARY, PEDESTRIAN, AUTOMOTIVE, SEA, AIRBORNE1g, AIRBORNE2g, AIRBORNE4g, WRIST, BIKE

	if (setDynamicModel(DYN_MODEL_AIRBORNE1g,defaultMaxWait) == false) // Set the dynamic model to PORTABLE
	{
		PRINTF("***!!! Warning: setDynamicModel failed !!!***\n");
	}
	else
	{
		PRINTF("Dynamic platform model changed successfully!\n");
	}

	// Let's read the new dynamic model to see if it worked
	uint8_t newDynamicModel = getDynamicModel(defaultMaxWait);
	if (newDynamicModel == 255)
	{
		PRINTF("***!!! Warning: getDynamicModel failed !!!***\n");
	}
	else
	{
		PRINTF("The new dynamic model is: %d\n",newDynamicModel);
	}

	
	if (setGPS_constellation_only(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		PRINTF("***!!! Warning: setGPS_constellation_only failed !!!***\n");
	}
	else
	{
		PRINTF("set GPS constellation only carried out successfully!\n");
	}

	if (set_powersave_config(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		PRINTF("***!!! Warning: set_powersave_config failed !!!***\n");
	}
	else
	{
		PRINTF("set_powersave_config carried out successfully!\n");
	}

	// Printing protocol version
	PRINTF("\nProtocol Version: ");
	uint8_t versionHigh = getProtocolVersionHigh(defaultMaxWait);
	PRINTF("%d.",versionHigh);
	uint8_t versionLow = getProtocolVersionLow(defaultMaxWait);
	PRINTF("%d\n",versionLow);
	
	return GPS_SUCCESS;
}

/* Get the location fix */
gps_status_t get_location_fix(uint32_t timeout)
{

	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);   // pull GPS extint0 pin high to wake gps. Really important

	HAL_Delay(GPS_WAKEUP_TIMEOUT);

	if (put_in_continueous_mode(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		PRINTF("***!!! Warning: put_in_continueous_mode failed !!!***\n");
	}
	else
	{
		PRINTF("put_in_continueous_mode carried out successfully!\n");
	}

	unsigned long startTime = HAL_GetTick();
	while (HAL_GetTick() - startTime < timeout)
	{
		char fixType = getFixType(defaultMaxWait);
		PRINTF("Fix: ");
		if(fixType == 0) PRINTF("No fix");
		else if(fixType == 1) PRINTF("Dead reckoning");
		else if(fixType == 2) PRINTF("2D");
		else if(fixType == 3) PRINTF("3D");
		else if(fixType == 4) PRINTF("GNSS+Dead reckoning");
		
		
		char SIV = getSIV(defaultMaxWait);
		PRINTF(" SIV: ");
		PRINTF("%d",SIV);
		
	  PRINTF(" TIME: ");
		PRINTF("%d",getYear(defaultMaxWait));
		PRINTF("-");
		PRINTF("%d",getMonth(defaultMaxWait));
		PRINTF("-");
		PRINTF("%d",getDay(defaultMaxWait));
		PRINTF(" ");
		PRINTF("%d",getHour(defaultMaxWait));
		PRINTF(":");
		PRINTF("%d",getMinute(defaultMaxWait));
		PRINTF(":");
		PRINTF("%d",getSecond(defaultMaxWait));
		PRINTF("\n");

		if (fixType == 3 && SIV >= 5 )
		{
				PRINTF("GPS fix acquired in %d milliseconds\n",HAL_GetTick() - startTime);
			
				long latitude = getLatitude(defaultMaxWait);
				PRINTF("Lat: ");
				PRINTF("%ld",latitude);
			  GPS_UBX_latitude_Float = latitude/10000;

				long longitude = getLongitude(defaultMaxWait);
				PRINTF(" Long: ");
				PRINTF("%ld",longitude);
				PRINTF(" (degrees * 10^-7)");
				GPS_UBX_longitude_Float = longitude/10000;

				long altitude = getAltitude(defaultMaxWait);
				PRINTF(" Alt: ");
				PRINTF("%ld",altitude);
				PRINTF(" (mm)");
				GPSaltitude = altitude;

				GPSsats = SIV;

				PRINTF("\n");
			
			
				if (put_in_power_save_mode(defaultMaxWait) == false) // Set the constellation to use only GPS
				{
					PRINTF("***!!! Warning: put_in_power_save_mode failed !!!***\n");
				}
				else
				{
					PRINTF("put_in_power_save_mode carried out successfully!\n");
				}	

				HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_RESET);   // pull GPS extint0 pin low to put gps to sleep. Really important

				latest_gps_status = GPS_SUCCESS;
				return GPS_SUCCESS;
		}
	}
	
	PRINTF("GPS FIX TIMOUT\n");
	
	if (put_in_power_save_mode(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		PRINTF("***!!! Warning: put_in_power_save_mode failed !!!***\n");
	}
	else
	{
		PRINTF("put_in_power_save_mode carried out successfully!\n");
	}	
	
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_RESET);   // pull GPS extint0 pin low to put gps to sleep. Really important

	latest_gps_status = GPS_FAILURE;
	return GPS_FAILURE;

}
