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

#define LORAWAN_APP_DATA_BUFF_SIZE                           64
#define LPP_APP_PORT 99

//#define playback_testing

/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */



typedef struct
{
	uint32_t TOW;          // time of week in seconds
	uint32_t weeks;        // weeks since epoch
	uint32_t latitude;        // Latitude
	uint32_t longitude;       // Longitude
	uint32_t altitude;     // Altitude

}time_pos_fix;


/* Dummy values for testing */
time_pos_fix current_pos = {.TOW = 100, .weeks = 20, .latitude = 0x17CA1BA2/*399121314 == 399121314*/, .longitude = 0xD3123A77/*3541187191 == -753780105 */, .altitude = 9789};

uint8_t cayenne_no_load_voltage = 33;  // 18 - 43 (min 25 values)(5 bits)
uint8_t cayenne_load_voltage = 43;     // 18 - 43 (min 25 values)(5 bits)
int temperature = -23;                 // -50 to 30 in increments of 2 degrees celcius (min 40 values)(6 bits)
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


uint16_t current_index = 3;
uint16_t subset_size = 8;
uint16_t n_archived_positions = 200;


/* ==================================================================== */
/* ========================== private data ============================ */
/* ==================================================================== */

/* Definition of private datatypes go here */





/* ==================================================================== */
/* ====================== private functions =========================== */
/* ==================================================================== */

/* Function prototypes for private (static) functions go here */

void save_position(uint32_t timestamp, uint32_t latitude, uint32_t longitude);
time_pos_fix *pick_subset_of_time_pos_fix(uint16_t how_far_back);
int generate_random(int l, int r);
int mod(int a, int b);
uint8_t * prep_tx_str( void );


/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

#ifdef playback_testing
void main()
{
	for (int i = 0; i < subset_size; i++) 
	{
		int rand_n = generate_random(0, n_archived_positions);
		int abs_index = mod((current_index - rand_n),n_archived_positions);
		printf("abs index:%d\n",abs_index);
	}
	printf("\n");
	
	prep_tx_str();
	
}
#endif

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



uint8_t * prep_tx_str()
{
	  AppData.Port = LPP_APP_PORT;
	  
	  /* no load voltage(5 bits) and load voltage(3 bits) */
	  AppData.Buff[0] = ((cayenne_no_load_voltage - 18) & 0b00011111) << 3 | ((cayenne_load_voltage - 18) & 0b00011100) >> 2;
	  
	  /* load voltage(remaining 2 bits) and temperature(6 bits)*/
	  AppData.Buff[1] = ((cayenne_load_voltage - 18) & 0b00000011) << 6 | ((temperature + 50)/2) & 0b00111111;
	  
	  /* pressure(7 bits) and data received flag(1 bit)*/
	  AppData.Buff[2] = ((pressure/10) & 0b01111111) << 1 | (data_received & 0b00000001);
	  
	  /* Sats(5 bits) and reset count(3 bits)*/
	  AppData.Buff[3] = ((sats) & 0b00011111) << 3 | ((reset_count) & 0b00000111);
	  
	  /* current position. Use the most significant numbers */
	  /* latitude(16 bits) */
	  
	  int32_t temp_lat = ((int32_t)current_pos.latitude + 90*10000000)*65536/180*10000000;
	  int32_t temp_long = ((int32_t)current_pos.longitude + 180*10000000)*65536/360*10000000;
	  
	  /* latitude(16 bits) -90 to 90*/
	  AppData.Buff[4] = (uint8_t)(temp_lat >> 8) & 0xff;
	  AppData.Buff[5] = (uint8_t)(temp_lat >> 0) & 0xff;
	  /* longitude(16 bits) -180 to 180 */
	  AppData.Buff[6] = (uint8_t)(temp_long >> 8) & 0xff;
	  AppData.Buff[7] = (uint8_t)(temp_long >> 8) & 0xff;
	  /* altitude(16 bits) */
	  AppData.Buff[8] = (uint8_t)(current_pos.altitude) >> 8;
	  AppData.Buff[9] = (uint8_t)(current_pos.altitude) >> 0;
	  
	  for (int i = 0; i<10;i ++)
	  {
		  printf("%x ",AppData.Buff[i]);
	  }
		
		return AppData.Buff;
}
