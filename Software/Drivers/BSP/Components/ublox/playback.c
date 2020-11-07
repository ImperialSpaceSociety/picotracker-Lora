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
#define SUBSET_SIZE 2U
#define N_ARCHIVED_POSITIONS 5UL

#define LORAWAN_APP_DATA_BUFF_SIZE                           64
#define LPP_APP_PORT 99



/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */



typedef struct
{
	uint32_t TOW; // time of week in seconds
	uint32_t weeks; // weeks since epoch
	uint32_t latitude;  // Latitude
	uint32_t longitude; // Longitude
	
}time_pos_fix;

time_pos_fix current_pos = {.TOW = 100, .weeks = 20, .latitude = 1234, .longitude = 5678};


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



time_pos_fix archived_positions[N_ARCHIVED_POSITIONS];
time_pos_fix subset_positions[SUBSET_SIZE];
int current_index = 3;


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

/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */


void main()
{
	for (int i = 0; i < SUBSET_SIZE; i++) 
	{
		int rand_n = generate_random(0, N_ARCHIVED_POSITIONS);
		int abs_index = mod((current_index - rand_n),N_ARCHIVED_POSITIONS);
		printf("abs index:%d\n",abs_index);
	}
	printf("\n");
	
}


int mod(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}

/**
 * \brief This will generate random number in range l and r, inclusive of both
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

char * prep_tx_str()
{
	  AppData.Port = LPP_APP_PORT;
	  
	  
	  AppData.Buff[0] = 5;
}