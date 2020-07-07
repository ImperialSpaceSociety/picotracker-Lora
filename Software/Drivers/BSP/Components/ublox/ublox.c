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
#define FIX				                        2		  // attempts to poll UBX-NAV-PVT

/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */


float GPS_UBX_latitude_Float							= 51.509865; // YY.YYYYYYY, in +/- DEGREES, temp dummy for testing geofencing
float GPS_UBX_longitude_Float							= -0.118092;  // XXX.XXXXXXX, in +/- DEGREES, temp dummy for testing geofencingstatic 
int32_t GPSaltitude												= 0;
uint8_t GPSsats														= 0;

gps_status_t latest_gps_status;


#ifdef DUMMY_GPS_COORDS

uint16_t dummy_coord_counter  = 0;


/*dummy Coords ARRAYS (longitude, latitude) */
static float dummy_coords_array[] = { 
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


static uint8_t	buffer_0xB5[1];
static uint8_t	buffer_0x62[1];
static uint8_t buffer_ubx_packet_wo_header[150]; // this packet does not include the 0xb5 0x62 header
static uint8_t flush_buffer[500];


// UBLOX variables
static uint8_t GPS_UBX_error_bitfield						= 0;



static int32_t GPS_UBX_latitude                 = 0;								// YYYYYYYYY, +/-
static int32_t GPS_UBX_longitude                = 0 ;								// XXXXXXXXXX, +/-
				

static uint8_t GPShour													= 0;
static uint8_t GPSminute												= 0;
static uint8_t GPSsecond												= 0;
static uint8_t GPSday														= 0;
static uint8_t GPSmonth													= 0;
static uint16_t GPSyear													= 0;

static uint8_t GPSfix_type											= 0;
static uint8_t GPSfix_OK												= 0;
//static uint8_t GPSvalidity											= 0;

static uint8_t GPSnavigation										= 0;
static uint32_t fixAttemptCount                 = 0;




static  uint8_t GPSbuffer[GPSBUFFER_SIZE];


volatile static  uint8_t GPS_UBX_ack_error = 0;
volatile static  uint8_t GPS_UBX_checksum_error = 0;
volatile static  uint8_t GPS_UBX_buffer_error = 0;

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
gps_status_t Backup_GPS();

void make_dummy_coordinates(void);


/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

gps_status_t get_latest_gps_status(void)
{
	return latest_gps_status;
}


/* 
 * GPS backup. 
 */
gps_status_t Backup_GPS(){
	if (put_in_power_save_mode(defaultMaxWait) == false)
	{
		PRINTF("***!!! Warning: put_in_power_save_mode failed !!!***\n");
	}
	else
	{
		PRINTF("put_in_power_save_mode carried out successfully!\n");
	}
	//HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_RESET);    // force GPS backup mode by pulling GPS extint pin low		
	return 0;
}




/* 
 * sets up gps by putting in airbourne mode, setting to use GPS satellites only, turning off NMEA
 * Needs TO BE REFACTORED TO TIME OUT OR EXIT IF NO MESSAGED IS ReCEIVED BACK!
 */
gps_status_t setup_GPS(){
	
	// wake up gps in case it is in Lower Power mode
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);    		      // pull GPS extint0 pin high to wake gps
	ihardReset();	
	HAL_Delay(1000);                                                              // Wait for things to be setup	

	/* Set the I2C port to output UBX only (turn off NMEA noise) */
	if (setI2COutput(COM_TYPE_UBX,defaultMaxWait) == false) //Set the I2C port to output UBX only (turn off NMEA noise)
	{
		PRINTF("***!!! Warning: setI2COutput failed !!!***\n");
	}
	else
	{
		PRINTF("set setI2COutput carried out successfully!\n");
	}
	
	/* For running the self test part of the program */
	if (isConnected(defaultMaxWait) == false) //Connect to the Ublox module using Wire port
	{
			PRINTF("SELFTEST: GPS did not respond. GPS error...\r\n");
	}
	else
	{
			PRINTF("SELFTEST: GPS responds. GPS OK...\r\n");
	}
  
	if (setGPS_constellation_only(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		PRINTF("***!!! Warning: setGPS_constellation_only failed !!!***\n");
	}
	else
	{
		PRINTF("set GPS constellation only carried out successfully!\n");
	}

	if (setDynamicModel(DYN_MODEL_AIRBORNE1g,defaultMaxWait) == false) // set to airbourne mode
	{
		PRINTF("***!!! Warning: setDynamicModel failed !!!***\n");
	}
	else
	{
		PRINTF("Dynamic platform model changed successfully!\n");
	}
	
	if (set_powersave_config(defaultMaxWait) == false)           // Save powersave config to ram. can be activated later.
	{
		PRINTF("***!!! Warning: set_powersave_config failed !!!***\n");
	}
	else
	{
		PRINTF("set_powersave_config carried out successfully!\n");
	}
	
	return 0;
}

/* Get the location fix */
gps_status_t get_location_fix(uint32_t timeout){
	
	// wakeup gps
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);    		  // pull GPS extint0 pin high to wake gps	
	HAL_Delay(500);
	
	if (put_in_continueous_mode(defaultMaxWait) == false) // Set the constellation to use only GPS
	{
		PRINTF("***!!! Warning: put_in_continueous_mode failed !!!***\n");
	}
	else
	{
		PRINTF("put_in_continueous_mode carried out successfully!\n");
	}

	
	/* Set the I2C port to output UBX only (turn off NMEA noise) */
	if (setI2COutput(COM_TYPE_UBX,defaultMaxWait) == false) //Set the I2C port to output UBX only (turn off NMEA noise)
	{
		PRINTF("***!!! Warning: setI2COutput failed !!!***\n");
	}
	else
	{
		PRINTF("set setI2COutput carried out successfully!\n");
	}
	
	
	/* Check if we are in airbourne mode. check if dynamic mode is correct */
	
	uint8_t newDynamicModel = getDynamicModel(defaultMaxWait);
	if (newDynamicModel == 255)
	{
		PRINTF("***!!! Warning: getDynamicModel failed !!!***\n");
	}
	else if (newDynamicModel != 6)
	{
		PRINTF("The current dynamic model is INCORRECT. The current dynamic model is: %d\n",newDynamicModel);
	}
	else
	{
		PRINTF("The current dynamic model is: %d\n",newDynamicModel);
	}

	
	if (newDynamicModel != DYN_MODEL_AIRBORNE1g){
		
		if (setDynamicModel(DYN_MODEL_AIRBORNE1g,defaultMaxWait) == false) // Set the dynamic model to PORTABLE
		{
			PRINTF("***!!! Warning: setDynamicModel failed !!!***\n");
		}
		else
		{
			PRINTF("Dynamic platform model changed successfully!\n");
		}
	}
	
	
	
	fixAttemptCount = 0;

	while(1)				// poll UBX-NAV-PVT until the module has fix
	{

		GPSfix_type = 0;
		GPSfix_OK = 0;
		GPSsats = 0;

		
		#if !DUMMY_GPS_COORDS 
		
		char fixType = getFixType(defaultMaxWait);
		char SIV = getSIV(defaultMaxWait);
		GPSyear =  getYear(defaultMaxWait);
		GPSmonth = getMonth(defaultMaxWait);
		GPSday = getDay(defaultMaxWait);
		GPShour = getHour(defaultMaxWait);
		GPSminute = getMinute(defaultMaxWait);
		GPSsecond = getSecond(defaultMaxWait);
		
		long latitude = getLatitude(defaultMaxWait);
		GPS_UBX_latitude_Float = latitude/10000;

		long longitude = getLongitude(defaultMaxWait);
		GPS_UBX_longitude_Float = longitude/10000;

		long altitude = getAltitude(defaultMaxWait);
		GPSaltitude = altitude;

		GPSsats = SIV;
		
		#else
		
		/* Strictly for testing if the geofencing works when GPS gives dummy values.
		 * It returns a dummy GPS coordinate instead of the one the actual ublox GPS returns.
		 */
		GPSsats = 6;     // dummy GPS sats
		GPSfix_type = 3; // dummy GNSSfix Type
		GPSfix_OK = 1;   // dummy Fix status flags: gnssFixOK
		
		GPS_UBX_longitude_Float = dummy_coords_array[dummy_coord_counter * 2];    // dummy longitude
		GPS_UBX_latitude_Float = dummy_coords_array[dummy_coord_counter * 2 + 1]; // dummy latitude
		
		if (dummy_coord_counter < dummy_coord_n-1){
			dummy_coord_counter++;
		}else{
			dummy_coord_counter = 0;
		}
		#endif

		if(GPSfix_type == 3 && GPSsats >= SATS )           // check if we have a good fix
		{ 
			Backup_GPS();
			
			#if USE_LED
			// indicate that fix has been found
			for(uint8_t i = 0; i < 20; i++)
			{
				HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_SET);
				HAL_Delay(50);
				HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_RESET);
				HAL_Delay(50);
			}
		 #endif

			
			return 1;
		}       

		fixAttemptCount++;
		
		#if USE_LED
		
		// Indicator led to indicate that still searching
		HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_RESET);
	
		#endif
		PRINTNOW();
		PRINTF("GPS Fix Attempt count : %d (%dh:%dm:%ds is GPS time)\r\n",fixAttemptCount,GPShour,GPSminute,GPSsecond);


		/* If fix taking too long, reset and re-initialize GPS module. 
		 * It does a forced hardware reset and recovers from a cold start
		 * Reset only after 250 tries, defined by FIX
		 */
		if(fixAttemptCount > FIX)														
		{
			// configure gps module again
			//ihardReset();	                                    	                         	// reset GPS module.
			HAL_Delay(1000);                                                              // wait for GPS module to be ready

			 
			if (setI2COutput(COM_TYPE_UBX,defaultMaxWait) == false) //Set the I2C port to output UBX only (turn off NMEA noise)
			{
				PRINTF("***!!! Warning: setI2COutput failed !!!***\n");
			}
			else
			{
				PRINTF("set setI2COutput carried out successfully!\n");
			}
			
			
			if (setGPS_constellation_only(defaultMaxWait) == false) // Set the constellation to use only GPS
			{
				PRINTF("***!!! Warning: setGPS_constellation_only failed !!!***\n");
			}
			else
			{
				PRINTF("set GPS constellation only carried out successfully!\n");
			}

			if (setDynamicModel(DYN_MODEL_AIRBORNE1g,defaultMaxWait) == false) // set to airbourne mode
			{
				PRINTF("***!!! Warning: setDynamicModel failed !!!***\n");
			}
			else
			{
				PRINTF("Dynamic platform model changed successfully!\n");
			}

			if (set_powersave_config(defaultMaxWait) == false)           // Save powersave config to ram. can be activated later.
			{
				PRINTF("***!!! Warning: set_powersave_config failed !!!***\n");
			}
			else
			{
				PRINTF("set_powersave_config carried out successfully!\n");
			}
						
			
			GPSfix_type = 0;
			GPSfix_OK = 0;
			GPSsats = 0;
			
			Backup_GPS();
			return 0;

		}
		
		HAL_Delay(1000);		
	}

}
