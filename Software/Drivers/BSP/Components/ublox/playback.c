/*
 * playback.c 
 * Author: Medad Newman 2/11/2020
 * Imperial College Space Society ( Medad Newman, Richard Ibbotson)
 *
 * Manages the playback of coordinates over time.
 *
 */ 



/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of system and local header files goes here */
#include "playback.h"
#include "stdint.h"
#include <stdlib.h>
#include <stdio.h>
 

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */
#define MAX_SUBSET_SIZE 100U
#define MAX_N_ARCHIVED_POSITIONS 500UL

#define LORAWAN_APP_DATA_BUFF_SIZE                           242U
#define LPP_APP_PORT 99U

#define playback_testing
#define LONGITUDE_BYTES_LEN 2U
#define LATITUDE_BYTES_LEN 2U
#define ALTITUDE_BYTES_LEN 2U
#define HOURS_SINCE_EPOCH_BYTES_LEN 2U
#define POSITION_BYTES_LEN (LONGITUDE_BYTES_LEN + LATITUDE_BYTES_LEN + ALTITUDE_BYTES_LEN)


/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */



typedef struct
{
	uint16_t hours_since_epoch; // hours since Epoch
	uint16_t latitude;        // Latitude
	uint16_t longitude;       // Longitude
	uint16_t altitude;     // Altitude

}time_pos_fix;


/* Dummy values for testing */
time_pos_fix current_pos = {.hours_since_epoch = 200, .latitude = 0x17CA/*399121314 == 399121314*/, .longitude = 0xD312/*3541187191 == -753780105 */, .altitude = 0x0000F221};

uint8_t cayenne_no_load_voltage = 33;  // 18 - 43 (min 25 values)(5 bits)
uint8_t cayenne_load_voltage = 43;     // 18 - 43 (min 25 values)(5 bits)
int8_t temperature = -23;                 // -50 to 30 in increments of 2 degrees celcius (min 40 values)(6 bits)
uint16_t pressure = 400;               // 130 - 1030 (min 128 values, 10mbar per increment)(7 bits)
uint8_t data_received = 1;             // 0 or 1. indicates that message was received(1 bit)
uint8_t sats = 12;                     // 0 - 32. Number of sats. (4 bits)
uint8_t reset_count = 7;               // 0-8. Number of resets in (3 bits)

/*!
 * Application Data structure
 */
typedef struct
{
  /*point to the LoRa App data buffer*/
  uint8_t* Buff;
  /*LoRa App data buffer size*/
  uint8_t BuffSize;
  /*Port on which the LoRa App is data is sent/ received*/
  uint8_t Port;
  
} lora_AppData_t;

static uint8_t AppDataBuff[LORAWAN_APP_DATA_BUFF_SIZE];

lora_AppData_t AppData={ AppDataBuff,  0 ,0 };


time_pos_fix archived_positions[MAX_N_ARCHIVED_POSITIONS];
time_pos_fix subset_positions[MAX_SUBSET_SIZE];


uint16_t current_index = 3;             /* As we fill the archived positions buffer, 
                                         * we keep tracker of our current index in this buffer
									     */
uint16_t subset_size = 8;               /* Number of positions to send down */
uint16_t n_archived_positions = 200;    /* Number of positions held in the EEPROM */


/* ==================================================================== */
/* ========================== private data ============================ */
/* ==================================================================== */

/* Definition of private datatypes go here */





/* ==================================================================== */
/* ====================== private functions =========================== */
/* ==================================================================== */

/* Function prototypes for private (static) functions go here */

void save_position(uint16_t hours_since_epoch, uint16_t latitude, uint16_t longitude, uint16_t altitude);
time_pos_fix *pick_subset_of_time_pos_fix(uint16_t how_far_back);
int generate_random(int l, int r);
int mod(int a, int b);
uint8_t * prep_tx_str( void );
void fill_subset_positions_buffer(uint16_t subset_size);
void fill_tx_buffer_with_location(uint16_t start_point, uint8_t * buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude );
void fill_tx_buffer_with_location_and_time(uint16_t start_point, uint8_t * buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude, uint16_t hours_since_epoch );



/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

#ifdef playback_testing
void main()
{
	
	// Print out buffer for debug
	for (int i = 0; i<MAX_N_ARCHIVED_POSITIONS;i ++)
	{
		archived_positions[i].longitude = current_pos.longitude;
		archived_positions[i].latitude = current_pos.latitude;
		archived_positions[i].altitude = current_pos.altitude;
		archived_positions[i].hours_since_epoch = current_pos.hours_since_epoch;

	}
	
	fill_subset_positions_buffer(subset_size);
	printf("\n");
	
	prep_tx_str();
	
}
#endif

/**
 * \brief Fill the subset_positions[] buffer with a randomly selected subset of archived positions.
 * 
 * 
 * \return void
 */
void fill_subset_positions_buffer(uint16_t subset_size)
{
	for (int i = 0; i < subset_size; i++)
	{
		int rand_n = generate_random(0, n_archived_positions);
		/* Our archived positions have a certain length, which overwrites once it reaches the end.
		 * Take this into account 
		 */
		int abs_index = mod((current_index - rand_n),n_archived_positions);
		
		/* Add the randomly selected position to the subset of positions */
		subset_positions[i] = archived_positions[abs_index];
		printf("abs index:%d\n",abs_index);

	}
}



/**
 * \brief Mathematical mod operation. a mod b.
 * 
 * \param a
 * \param b
 * 
 * \return int
 */
int mod(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}

/**
 * \brief This will generate random number in range l and r, inclusive of both(TODO: verify if this works)
 * 
 * \param l: lower bound
 * \param r: upper bound
 * 
 * \return int random number
 */
int generate_random(int l, int r) { 
	int rand_num = (rand() % (r - l + 1)) + l;
	return rand_num;
}


void fill_tx_buffer_with_location(uint16_t start_point, uint8_t * buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude )
{
	
	/* current position. Use the most significant numbers. Truncate to 16 bits.*/
	/* latitude(16 bits) -90 to 90*/
	AppData.Buff[start_point + 0] = (latitude >> 8) & 0xff;
	AppData.Buff[start_point + 1] = (latitude >> 0) & 0xff;
	/* longitude(16 bits) -180 to 180 */
	AppData.Buff[start_point + 2] = (longitude >> 8) & 0xff;
	AppData.Buff[start_point + 3] = (longitude >> 0) & 0xff;
	/* altitude(16 bits) */
	AppData.Buff[start_point + 4] = (altitude >> 8) & 0xff;
	AppData.Buff[start_point + 5] = (altitude >> 0) & 0xff;
		  
	
}


void fill_tx_buffer_with_location_and_time(uint16_t start_point, uint8_t * buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude, uint16_t hours_since_epoch )
{
	
	fill_tx_buffer_with_location(start_point, buffer, latitude, longitude, altitude );
	
	AppData.Buff[start_point + POSITION_BYTES_LEN + 0] = (hours_since_epoch >> 8) & 0xff;
	AppData.Buff[start_point + POSITION_BYTES_LEN + 1] = (hours_since_epoch >> 0) & 0xff;
}

/**
 * \brief Prepare Tx string, by filling the AppData.Buff[] with the 
 * data string to be sent down to gateways on the ground. 
 * 
 * \return uint8_t *
 */
uint8_t * prep_tx_str()
{
	  AppData.Port = LPP_APP_PORT;
	  
	  /* no load voltage(5 bits) and load voltage(3 bits) */
	  AppData.Buff[0] = ((cayenne_no_load_voltage - 18) & 0b00011111) << 3 | ((cayenne_load_voltage - 18) & 0b00011100) >> 2;
	  
	  /* load voltage(remaining 2 bits) and temperature(6 bits)*/
	  AppData.Buff[1] = ((cayenne_load_voltage - 18) & 0b00000011) << 6 | temperature>>2 & 0b00111111;
	  
	  /* pressure(7 bits) and data received flag(1 bit)*/
	  AppData.Buff[2] = ((pressure/10) & 0b01111111) << 1 | (data_received & 0b00000001);
	  
	  /* Sats(5 bits) and reset count(3 bits)*/
	  AppData.Buff[3] = ((sats) & 0b00011111) << 3 | ((reset_count) & 0b00000111);
	  
	  
	  fill_tx_buffer_with_location(4, AppData.Buff, current_pos.latitude,current_pos.longitude,current_pos.altitude);

	  
	  for (int i = 0; i < subset_size; i++)
	  {
		  time_pos_fix temp_pos = subset_positions[i];
		  fill_tx_buffer_with_location_and_time(10 + i * (POSITION_BYTES_LEN+HOURS_SINCE_EPOCH_BYTES_LEN), 
												AppData.Buff,
												temp_pos.latitude,
												temp_pos.longitude,
												temp_pos.altitude,
												temp_pos.hours_since_epoch);
		  
	  }


	  
	  
	  // Print out buffer for debug
	  for (int i = 0; i<LORAWAN_APP_DATA_BUFF_SIZE;i ++)
	  {
		  printf("%02x",AppData.Buff[i]);
	  }
		
		return AppData.Buff;
}
