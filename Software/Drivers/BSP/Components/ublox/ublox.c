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

#define GPS_I2C_ADDRESS 0x42
#define GPS_I2C_TIMEOUT 1000
#define GPSBUFFER_SIZE			125 // bigger than max size of ubx message
#define SATS				4		// number of satellites required for positional solution
#define UBX_TIMEOUT  5000 // in milliseconds


/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */



// UBLOX variables
static uint8_t GPS_UBX_error_bitfield						= 0;



static int32_t GPS_UBX_latitude                 = 0;								// YYYYYYYYY, +/-
static int32_t GPS_UBX_longitude                = 0 ;								// XXXXXXXXXX, +/-
				

static uint8_t GPShour													= 0;
static uint8_t GPSminute												= 0;
static uint8_t GPSsecond												= 0;
//static uint8_t GPSday														= 0;
//static uint8_t GPSmonth													= 0;
//static uint16_t GPSyear													= 0;

static uint8_t GPSfix_type											= 0;
static uint8_t GPSfix_OK												= 0;
//static uint8_t GPSvalidity											= 0;

static uint8_t GPSnavigation										= 0;
//static uint8_t GPSpowermode											= 0;
//static uint8_t GPSpowersavemodestate						= 0;
//static int32_t GPSgroundspeed										= 0;
//static int32_t GPSheading												= 0;

//static int32_t GPS_UBX_latitude_L               = 0;								// LAST valid value (in case of lost FIX)
//static int32_t GPS_UBX_longitude_L              = 0;								// LAST valid value (in case of lost FIX)
//static int32_t GPSaltitude_L                    = 0;									// LAST valid value (in case of lost FIX)

static uint32_t fixAttemptCount                 = 0;



float GPS_UBX_latitude_Float							= 51.509865; // YY.YYYYYYY, in +/- DEGREES, temp dummy for testing geofencing
float GPS_UBX_longitude_Float							= -0.118092;  // XXX.XXXXXXX, in +/- DEGREES, temp dummy for testing geofencingstatic 




int32_t GPSaltitude												= 0;
uint8_t GPSsats														= 0;


static  uint8_t GPSbuffer[GPSBUFFER_SIZE];


volatile static  uint8_t GPS_UBX_ack_error = 0;
volatile static  uint8_t GPS_UBX_checksum_error = 0;
volatile static  uint8_t GPS_UBX_buffer_error = 0;



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



/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */



/* 
 * sets up gps by putting in airbourne mode, setting to use GPS satellites only, turning off NMEA
 * Needs TO BE REFACTORED TO TIME OUT OR EXIT IF NO MESSAGED IS ReCEIVED BACK!
 */
uint8_t setup_GPS(){
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);   // pull GPS extint0 pin high to wake gps. Really important
	
	printf("Resetting gps\n");
	hardReset();
	
	HAL_Delay(defaultMaxWait);



	if (isConnected(defaultMaxWait) == false) //Connect to the Ublox module using Wire port
	{
			printf("Ublox GPS not detected at default I2C address. Please check wiring. Freezing.\n");
	}
	else
	{
			printf("Ublox GPS successfully detected. GPS OK...\n");
	}
	
	// set to using ubx only and via the DDC(I2C) port
	printf("Setting UBX only via I2C\n");
	setI2COutput(COM_TYPE_UBX,defaultMaxWait); //Set the I2C port to output UBX only (turn off NMEA noise)
	
	saveConfiguration(defaultMaxWait); //Save the current settings to flash and BBR


	// If we are going to change the dynamic platform model, let's do it here.
	// Possible values are:
	// PORTABLE, STATIONARY, PEDESTRIAN, AUTOMOTIVE, SEA, AIRBORNE1g, AIRBORNE2g, AIRBORNE4g, WRIST, BIKE

	if (setDynamicModel(DYN_MODEL_AIRBORNE1g,defaultMaxWait) == false) // Set the dynamic model to PORTABLE
	{
		printf("***!!! Warning: setDynamicModel failed !!!***\n");
	}
	else
	{
		printf("Dynamic platform model changed successfully!\n");
	}

	// Let's read the new dynamic model to see if it worked
	uint8_t newDynamicModel = getDynamicModel(defaultMaxWait);
	if (newDynamicModel == 255)
	{
		printf("***!!! Warning: getDynamicModel failed !!!***\n");
	}
	else
	{
		printf("The new dynamic model is: %d\n",newDynamicModel);
	}

	
	if (setGPS_constellation_only(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		printf("***!!! Warning: setGPS_constellation_only failed !!!***\n");
	}
	else
	{
		printf("set GPS constellation only carried out successfully!\n");
	}

	if (set_powersave_config(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		printf("***!!! Warning: set_powersave_config failed !!!***\n");
	}
	else
	{
		printf("set_powersave_config carried out successfully!\n");
	}

	// Printing protocol version
	printf("\nProtocol Version: ");
	uint8_t versionHigh = getProtocolVersionHigh(defaultMaxWait);
	printf("%d.",versionHigh);
	uint8_t versionLow = getProtocolVersionLow(defaultMaxWait);
	printf("%d\n",versionLow);
	
}

/* Get the location fix */
uint8_t get_location_fix(){

	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);   // pull GPS extint0 pin high to wake gps. Really important

	if (put_in_continueous_mode(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		printf("***!!! Warning: put_in_continueous_mode failed !!!***\n");
	}
	else
	{
		printf("put_in_continueous_mode carried out successfully!\n");
	}


	long latitude = getLatitude(defaultMaxWait);
	printf("Lat: ");
	printf("%ld",latitude);

	long longitude = getLongitude(defaultMaxWait);
	printf(" Long: ");
	printf("%ld",longitude);
	printf(" (degrees * 10^-7)");

	long altitude = getAltitude(defaultMaxWait);
	printf(" Alt: ");
	printf("%ld",altitude);
	printf(" (mm)");

	char SIV = getSIV(defaultMaxWait);
	printf(" SIV: ");
	printf("%d",SIV);


	char fixType = getFixType(defaultMaxWait);
	printf(" Fix: ");
	if(fixType == 0) printf("No fix");
	else if(fixType == 1) printf("Dead reckoning");
	else if(fixType == 2) printf("2D");
	else if(fixType == 3) printf("3D");
	else if(fixType == 4) printf("GNSS+Dead reckoning");


	printf("\n");
	printf("%d",getYear(defaultMaxWait));
	printf("-");
	printf("%d",getMonth(defaultMaxWait));
	printf("-");
	printf("%d",getDay(defaultMaxWait));
	printf(" ");
	printf("%d",getHour(defaultMaxWait));
	printf(":");
	printf("%d",getMinute(defaultMaxWait));
	printf(":");
	printf("%d",getSecond(defaultMaxWait));
	printf(".");
	
	//Pretty print leading zeros
	uint16_t mseconds = getMillisecond(defaultMaxWait);
	if (mseconds < 100)
		printf("0");
	if (mseconds < 10)
		printf("0");
	printf("%d",mseconds);

	printf(" nanoSeconds: ");
	printf("%d",getNanosecond(defaultMaxWait));


	printf("\n");



	if (put_in_power_save_mode(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		printf("***!!! Warning: put_in_power_save_mode failed !!!***\n");
	}
	else
	{
		printf("put_in_power_save_mode carried out successfully!\n");
	}	
	
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_RESET);   // pull GPS extint0 pin low to put gps to sleep. Really important


}





