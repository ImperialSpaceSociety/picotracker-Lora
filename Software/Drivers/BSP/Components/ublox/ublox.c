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

#include "ublox_ubx_messages.h"
#include "i2c_middleware.h"


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

static uint8_t UBLOX_verify_checksum(volatile uint8_t *buffer, uint8_t len);
static uint8_t UBLOX_send_message(uint8_t *message, uint8_t len);
static uint8_t UBLOX_receive_message(uint8_t *message, uint8_t len);
static uint8_t UBLOX_request_UBX(uint8_t *request, uint8_t len, uint8_t expectlen, uint8_t (*parse)(volatile uint8_t*));
static uint8_t UBLOX_receive_UBX(uint8_t *buffer, uint8_t len, uint32_t timeout);
static uint8_t UBLOX_parse_0624(volatile uint8_t *buffer);
static uint8_t UBLOX_parse_0107(volatile uint8_t *buffer);
static uint8_t UBLOX_parse_ACK(volatile uint8_t *buffer);
static uint8_t UBLOX_flush_I2C_buffer( uint16_t len);

/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */


/* 
 * GPS backup. 
 */
uint8_t Backup_GPS(){
  UBLOX_request_UBX(set_power_save_mode, sizeof(set_power_save_mode), 10, UBLOX_parse_ACK);				// switch GPS module to powersave mode. No response expected
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_RESET);    // force GPS backup mode by pulling GPS extint pin low		
	return 0;
}




/* 
 * sets up gps by putting in airbourne mode, setting to use GPS satellites only, turning off NMEA
 * Needs TO BE REFACTORED TO TIME OUT OR EXIT IF NO MESSAGED IS ReCEIVED BACK!
 */
uint8_t setup_GPS(){
	
	// wake up gps in case it is in Lower Power mode
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);    		      // pull GPS extint0 pin high to wake gps
	UBLOX_send_message(resetReceiver, sizeof(resetReceiver));				              // reset GPS module. cold start forced
	HAL_Delay(1000);                                                              // Wait for things to be setup	

	/* For running the self test part of the program */
	int ack_from_gps;
	ack_from_gps = UBLOX_request_UBX(setNMEAoff, sizeof(setNMEAoff), 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
  
	if (ack_from_gps)
		{
			PRINTF("SELFTEST: GPS responds. GPS OK...\r\n");
	}else
		{
			PRINTF("SELFTEST: GPS did not respond. GPS error...\r\n");
	}
	
	
	UBLOX_request_UBX(setNMEAoff, sizeof(setNMEAoff), 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
	
	UBLOX_request_UBX(setGPSonly, sizeof(setGPSonly), 10, UBLOX_parse_ACK);				// !! must verify if this is a good config: turn off all constellations except gps: UBX-CFG-GNSS 
	UBLOX_request_UBX(setNAVmode, sizeof(setNAVmode), 10, UBLOX_parse_ACK);				// set to airbourne mode
	UBLOX_request_UBX(powersave_config, sizeof(powersave_config) , 10, UBLOX_parse_ACK);	  // Save powersave config to ram. can be activated later.
	return 0;
}

/* Get the location fix */
uint8_t get_location_fix(){
	
	// wakeup gps
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);    		  // pull GPS extint0 pin high to wake gps	
	HAL_Delay(500);
	UBLOX_send_message(set_continueous_mode, sizeof(set_continueous_mode));	  // switch GPS module to continueous mode	
	
	// Check if we are in airbourne mode
	GPSnavigation = 0;
	
	UBLOX_request_UBX(request0624, 8, 44, UBLOX_parse_0624);
	
	if(GPSnavigation != 6)														// verify Dynamic Model: airborne with <1g acceleration
	{
		UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);					// if not, set it
	}

	fixAttemptCount = 0;

	while(1)				// poll UBX-NAV-PVT until the module has fix
	{

		GPSfix_type = 0;
		GPSfix_OK = 0;
		GPSsats = 0;

		
		#if !DUMMY_GPS_COORDS 
		UBLOX_request_UBX(request0107, 8, 100, UBLOX_parse_0107);                 // get fix info UBX-NAV-PVT
		
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

		if(GPSfix_OK == 1 && GPSfix_type == 3 && GPSsats >= SATS )           // check if we have a good fix
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
			UBLOX_send_message(resetReceiver, sizeof(resetReceiver));			              	// reset GPS module.
			HAL_Delay(1000);                                                              // wait for GPS module to be ready
			UBLOX_request_UBX(setNMEAoff, sizeof(setNMEAoff), 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
			UBLOX_request_UBX(setGPSonly, sizeof(setGPSonly), 10, UBLOX_parse_ACK);				// !! must verify if this is a good config: turn off all constellations except gps: UBX-CFG-GNSS 
			UBLOX_request_UBX(setNAVmode, sizeof(setNAVmode), 10, UBLOX_parse_ACK);				// set to airbourne mode
			UBLOX_request_UBX(powersave_config, sizeof(powersave_config) , 10, UBLOX_parse_ACK);	  // Save powersave config to ram. can be activated later.

			GPSfix_type = 0;
			GPSfix_OK = 0;
			GPSsats = 0;
			
			Backup_GPS();
			return 0;

		}
		
		HAL_Delay(1000);		
	}

}





/*
    Verifies the checksum of received UBX messages.
*/
uint8_t UBLOX_verify_checksum(volatile uint8_t *buffer, uint8_t len)
{
    uint8_t CK_A_real = buffer[len-2];
    uint8_t CK_B_real = buffer[len-1];
    uint8_t CK_A_comp = 0;
    uint8_t CK_B_comp = 0;
    uint8_t ubloxCRC;

    for(uint8_t i = 2; i < len-2; i++)
    {
        CK_A_comp = CK_A_comp + buffer[i];
        CK_B_comp = CK_A_comp + CK_B_comp;
    }
    
    if(CK_A_real == CK_A_comp && CK_B_real == CK_B_comp) ubloxCRC = 1;
    else ubloxCRC = 0;

    return ubloxCRC;
}


/*
    Waits for the I2C1_RX_buffer[] to be filled with an expected number of bytes
    and then empties the buffer to a desired buffer for further processing.
*/
uint8_t UBLOX_receive_UBX(uint8_t *buffer, uint8_t len, uint32_t timeout)
{
		 /* Init tickstart for timeout management*/
		uint32_t tickstart_j = HAL_GetTick();

		/* set a time out for receiving a ubx message back from the GPS */
    while ((HAL_GetTick() - tickstart_j) < timeout)
		{
			/* listen for the first header char */
			UBLOX_receive_message(buffer_0xB5, 1);
			
			if (buffer_0xB5[0] == 0xb5){
				  /* now listen for the second header char */
					UBLOX_receive_message(buffer_0x62, 1);

				  if (buffer_0x62[0] == 0x62){
						
						/* now that the header has been received, parse the rest of message */
						UBLOX_receive_message(buffer_ubx_packet_wo_header, 120);

					  /* now fill GPS buffer with header+body of ubx message  */
						buffer[0] = 0xB5;
						buffer[1] = 0x62;
						for (uint8_t i=0; i<len-2; i++) {
								buffer[i+2]=buffer_ubx_packet_wo_header[i];
						}
					 
						return 1; // ubx message received and GPSbuffer filled with data

				}
			}
		}
		
		return 0; // no ubx message received
}




/*
    Transmits a desired UBX message across I2C1.
*/
uint8_t UBLOX_send_message(uint8_t *message, uint8_t len)
{
	I2C_MIDDLEWARE_STATUS_t status = I2C_transmit(&hi2c1, (uint16_t) GPS_I2C_ADDRESS << 1, message, len, GPS_I2C_TIMEOUT);
	
	if (status == I2C_SUCCSS)
	{
		return 1;
	}else
	{
		return 0;	
	}
}


/*
    Transmits a desired UBX message across I2C1.
*/
uint8_t UBLOX_receive_message(uint8_t *message, uint8_t len)
{
	I2C_MIDDLEWARE_STATUS_t status = I2C_receive( &hi2c1,(uint16_t) GPS_I2C_ADDRESS << 1, message, len, GPS_I2C_TIMEOUT);

	if (status == I2C_SUCCSS)
	{
		return 1;
	}else
	{
		return 0;	
	}
	
}



/*
 * Flush I2C buffer. Fill the flush buffer with number of bytes defined by len.
 * Return 0 for failure. 1 for success
*/
uint8_t UBLOX_flush_I2C_buffer( uint16_t len)
{
	
	I2C_MIDDLEWARE_STATUS_t status = I2C_receive(&hi2c1, (uint16_t) GPS_I2C_ADDRESS << 1, flush_buffer, len, GPS_I2C_TIMEOUT);
	
	if (status == I2C_SUCCSS)
	{
		return 1;
	}else
	{
		return 0;	
	}

}


/*
    Function polling desired GPS data. It first sends the set UBX request.
    Then waits for the data and calls the appropriate parsing function.
*/
uint8_t UBLOX_request_UBX(uint8_t *request, uint8_t len, uint8_t expectlen, uint8_t (*parse)(volatile uint8_t*))
{
		// Flush Ublox I2C buffer if it is unexpectedly filled with something else. Do not do anything with the data
    // TODO: maybe do something if there is an ubx message here. A GPS/MCU reset?
		UBLOX_flush_I2C_buffer(500);

		// Transmit the request
	  UBLOX_send_message(request, len);
			
		// Receive the request
		UBLOX_receive_UBX(GPSbuffer, expectlen, 1500);

		return  parse(GPSbuffer);          // parse the response to appropriate variables, 1 for successful parsing

}







/*
    UBX 06 24   NAVIGATION MODE
    
        GPSnavigation       0   portable
                            2   stationary
                            3   pedestrian
                            4   automotive
                            5   sea
                            6   airborne with <1g acceleration
                            7   airborne with <2g acceleration
                            8   airborne with <4g acceleration
                            9   wrist worn watch
    
    Checks the header and the checksum.
*/
uint8_t UBLOX_parse_0624(volatile uint8_t *buffer)
{
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x06 && buffer[3] == 0x24)
    {
        if(UBLOX_verify_checksum(buffer, 44))
        {
            GPSnavigation = buffer[8];
        }else{
            GPS_UBX_checksum_error++;
            
            GPSnavigation = 0;
        }
    }else{
        GPS_UBX_buffer_error++;
        
        GPSnavigation = 0;
    }
	  return 0;
}



/*
    UBX UBX-NAV-PVT 0x01 0x07   EVERYTHING
    
        GPSyear                     2016
        GPSmonth                    10
        GPSday                      18
        GPShour                     9
        GPSminute                   14
        GPSsecond                   55
        GPSfix_type                      1
																		0   no fix
																		1   dead reckoning only
																		2   2D-fix
																		3   3D-fix
																		4   GNSS + dead reckoning combined
																		5   time only fix
        GPSpowersavemodestate       0   PSM is not active
                                    1   Enabled (an intermediate state before Acquisition state)
                                    2   Acquisition
                                    3   Tracking
                                    4   Power Optimized Tracking
                                    5   Inactive
        GPSsats                     7
        GPS_UBX_latitude            494681170       +/-
        GPS_UBX_longitude           180910855       +/-
        GPS_UBX_longitude_Float     49.4681170      +/-
        GPS_UBX_latitude_Float      18.0910855      +/-
        GPSaltitude                 403             +/-
        GPSgroundspeed              10000           +/-
        GPSheading                  2545641         +/-
    
    Checks the header and the checksum.
    UBLOX 7 message is shorter then UBLOX 8 message. It must be reflected in the checksum verification.
		Comment Medad 27/12/19: looks like the pvt message is parsed according to the m8 spec. But not sure why it verifies checksum
		with 2 lengths(92 and 100 bytes). maybe flexible to accomodate the m7 spec.
*/
uint8_t UBLOX_parse_0107(volatile uint8_t *buffer)
{
    GPS_UBX_error_bitfield |= (1 << 2);
    
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x07)
    {
        if(UBLOX_verify_checksum(buffer, 92) || UBLOX_verify_checksum(buffer, 100))
        {
											
            // YEAR, MONTH, DAY
            //GPSyear = (uint16_t)buffer[10] | (uint16_t)buffer[11] << 8;
            //GPSmonth = buffer[12];
            //GPSday = buffer[13];
            
            // HOUR, MINUTE, SECONDS
            GPShour = buffer[14];
            GPSminute = buffer[15];
            GPSsecond = buffer[16];
            
            // FIX
            GPSfix_type = buffer[26];             // GNSSfix Type
					
					  GPSfix_OK = buffer[27] & 0x01; // Fix status flags: gnssFixOK
            //GPSvalidity = buffer[17];        // Validity flags
            
            // POWER SAVE MODE STATE
            //GPSpowersavemodestate = (buffer[27] >> 2) & 0x07; // Fix status flags: PSM state
            
            // SATS
            GPSsats = buffer[29];
            
            // LONGITUDE, LATITUDE, ALTITUDE ABOVE MEAN SEA LEVEL
            GPS_UBX_longitude = (int32_t)buffer[30] | (int32_t)buffer[31] << 8 | (int32_t)buffer[32] << 16 | (int32_t)buffer[33] << 24;
            GPS_UBX_longitude_Float = (float)GPS_UBX_longitude / 10000000.0;
            
            GPS_UBX_latitude = (int32_t)buffer[34] | (int32_t)buffer[35] << 8 | (int32_t)buffer[36] << 16 | (int32_t)buffer[37] << 24;
            GPS_UBX_latitude_Float = (float)GPS_UBX_latitude / 10000000.0;
            
            GPSaltitude = (int32_t)buffer[38] | (int32_t)buffer[39] << 8 | (int32_t)buffer[40] << 16 | (int32_t)buffer[41] << 24;
            GPSaltitude /= 1000;
            
            // GROUND SPEED, HEADING
            //GPSgroundspeed = (int32_t)buffer[66] | (int32_t)buffer[67] << 8 | (int32_t)buffer[68] << 16 | (int32_t)buffer[69] << 24;
            //GPSheading = (int32_t)buffer[70] | (int32_t)buffer[71] << 8 | (int32_t)buffer[72] << 16 | (int32_t)buffer[73] << 24;;
            
            GPS_UBX_error_bitfield &= ~(1 << 2);
						
        }else{
            GPS_UBX_checksum_error++;
            
            GPSfix_type = 0;
            GPSsats = 0;
        }
    }else{
        GPS_UBX_buffer_error++;
        
        GPSfix_type = 0;
        GPSsats = 0;
    }
		
		return 0;
}


/*
    UBX 05 01   ACK
    
    Checks the header and the checksum. returns 1 when an ack is received, returns 0 when a nak is received.
*/



uint8_t UBLOX_parse_ACK(volatile uint8_t *buffer)
{
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x05)
    {
        if(buffer[3] != 0x01)
        {
            GPS_UBX_ack_error++;
						return 0;
        }
				else
				{
					return 1;
				}
    }else{
        GPS_UBX_buffer_error++;
				return 0;
    }
		
}



