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
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "bsp.h"
 

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */
#define MAX_N_ARCHIVED_POSITIONS 500UL

#define LORAWAN_APP_DATA_BUFF_SIZE                           242U
#define LPP_APP_PORT 99U

//#define playback_testing
#define LONGITUDE_BYTES_LEN 2U
#define LATITUDE_BYTES_LEN 2U
#define ALTITUDE_BYTES_LEN 2U
#define MINUTES_SINCE_EPOCH_BYTES_LEN 3U
#define POSITION_BYTES_LEN (LONGITUDE_BYTES_LEN + LATITUDE_BYTES_LEN + ALTITUDE_BYTES_LEN)


/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */






/* Dummy values for testing */
time_pos_fix_t current_pos = 
{
	.minutes_since_epoch = 0x00BBC8AA,  /*12306602 minutes */
	.latitude = 0x17CA                  /*399121314 == 399121314*/,
	.longitude = 0xD312                 /*3541187191 == -753780105 */,
	.altitude = 0x00F2                  /*0x0000F221 >>2 */
};


sensor_t current_sensor_data = 
{
	.no_load_solar_voltage = 33,  /* 18 - 43 (min 25 values)(5 bits) */
	.load_solar_voltage = 43,     /* 18 - 43 (min 25 values)(5 bits) */
	.temperature = -23,           /* -64 to 64 in increments of 2 degrees celcius (min 40 values)(6 bits) */
	.pressure = 400,              /* 130 - 1030 (min 128 values, 10mbar per increment)(7 bits) */
	.data_received = 1,           /* 0 or 1. indicates that message was received(1 bit) */
	.sats = 12,                   /* 0 - 32. Number of sats. (4 bits) */
	.reset_count = 7              /* 0-7. Number of resets in (3 bits) */
};


playback_key_info_t current_playback_key_info = 
{
	.n_positions_in_eeprom = 0,            /* Number of positions held in the EEPROM */
	.n_positions_to_send = 8,              /* Number of positions to send down in single transmission*/
	.n_positions_offset = 5,               /* Send positions from n_positions_offset from current position. */
	.n_positions_to_select_from = 300      /* Define size of pool of positions to select from */
};

static uint8_t tx_str_buffer[LORAWAN_APP_DATA_BUFF_SIZE];
static uint16_t tx_str_buffer_len = 0;

#ifdef playback_testing
time_pos_fix_t test_subset[MAX_SUBSET_SIZE];
time_pos_fix_t *subset_positions_ptr = test_subset;
sensor_t *sensor_data_ptr = &current_sensor_data;
time_pos_fix_t *current_pos_ptr = &current_pos;
#else
time_pos_fix_t *subset_positions_ptr;
sensor_t *sensor_data_ptr;
time_pos_fix_t *current_pos_ptr;
#endif

/* ==================================================================== */
/* ========================== private data ============================ */
/* ==================================================================== */

/* Definition of private datatypes go here */





/* ==================================================================== */
/* ====================== private functions =========================== */
/* ==================================================================== */

/* Function prototypes for private (static) functions go here */

void save_position(uint32_t minutes_since_epoch, uint16_t latitude, uint16_t longitude, uint16_t altitude);
time_pos_fix_t *pick_subset_of_time_pos_fix(uint16_t how_far_back);
int generate_random(int l, int r);
int mod(int a, int b);
void fill_subset_positions_buffer(uint16_t subset_size);
void fill_tx_buffer_with_location(uint16_t start_point, uint8_t * buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude );
void fill_tx_buffer_with_location_and_time(uint16_t start_point, uint8_t * buffer,
											uint16_t latitude, uint16_t longitude,
											uint16_t altitude, uint32_t minutes_since_epoch );



/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

#ifdef playback_testing
void main()
{
	
	// Print out buffer for debug
	for (int i = 0; i<current_playback_key_info.n_positions_to_send;i ++)
	{
		subset_positions_ptr[i].longitude = current_pos.longitude;
		subset_positions_ptr[i].latitude = current_pos.latitude;
		subset_positions_ptr[i].altitude = current_pos.altitude;
		subset_positions_ptr[i].minutes_since_epoch = current_pos.minutes_since_epoch;

	}
	
	printf("\n");
	
	prepare_tx_buffer();
	
}
#endif



/**
 * \brief Return pointer to current_playback_key_info
 * 
 * \param 
 * 
 * \return playback_key_info_t *
 */
playback_key_info_t *get_playback_key_info( void )
{
	return &current_playback_key_info;
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

/**
 * \brief  Fill the tx buffer with location info only
 * 
 * \param start_point : index of start point in buffer to start filling
 * \param buffer : pointer to buffer
 * \param latitude 
 * \param longitude
 * \param altitude
 * 
 * \return void
 */
void fill_tx_buffer_with_location(uint16_t start_point, uint8_t * buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude )
{
	
	/* current position. Use the most significant numbers. Truncate to 16 bits.*/
	/* latitude(16 bits) -90 to 90*/
	tx_str_buffer[start_point + 0] = (latitude >> 0) & 0xff;
	tx_str_buffer[start_point + 1] = (latitude >> 8) & 0xff;
	/* longitude(16 bits) -180 to 180 */
	tx_str_buffer[start_point + 2] = (longitude >> 0) & 0xff;
	tx_str_buffer[start_point + 3] = (longitude >> 8) & 0xff;
	/* altitude(16 bits) */
	tx_str_buffer[start_point + 4] = (altitude >> 0) & 0xff;
	tx_str_buffer[start_point + 5] = (altitude >> 8) & 0xff;
		  
	
}


/**
 * \brief  Fill the tx buffer with location and time information
 * 
 * \param start_point : index of start point in buffer to start filling
 * \param buffer : pointer to buffer
 * \param latitude
 * \param longitude
 * \param altitude
 * \param minutes_since_epoch
 * 
 * \return void
 */
void fill_tx_buffer_with_location_and_time(uint16_t start_point, uint8_t * buffer, uint16_t latitude, uint16_t longitude, uint16_t altitude, uint32_t minutes_since_epoch )
{
	
	fill_tx_buffer_with_location(start_point, buffer, latitude, longitude, altitude );
	
	tx_str_buffer[start_point + POSITION_BYTES_LEN + 0] = (minutes_since_epoch >> 0) & 0xff;
	tx_str_buffer[start_point + POSITION_BYTES_LEN + 1] = (minutes_since_epoch >> 8) & 0xff;
	tx_str_buffer[start_point + POSITION_BYTES_LEN + 2] = (minutes_since_epoch >> 16) & 0xff;

}

/**
 * \brief Prepare Tx string, by filling the AppData.Buff[] with the 
 * data string to be sent down to gateways on the ground. 
 * 
 * \return none
 */
void prepare_tx_buffer(void)
{
	  
	  /* byte 0: no load voltage(5 bits) and load voltage(3 bits) */
	  tx_str_buffer[0] |= ((sensor_data_ptr->no_load_solar_voltage - 18) & 0x1F) << 3;
	  tx_str_buffer[0] |= ((sensor_data_ptr->load_solar_voltage - 18) & 0x1C) >> 2;
	  
	  /* byte1: load voltage(remaining 2 bits) and temperature(6 bits)*/
	  tx_str_buffer[1] |= ((sensor_data_ptr->load_solar_voltage - 18) & 0x03) << 6;
	  tx_str_buffer[1] |= (sensor_data_ptr->temperature >> 2 & 0x3F);
	  /* byte2: pressure(7 bits) and data received flag(1 bit)*/
	  tx_str_buffer[2] |= ((sensor_data_ptr->pressure/10) & 0x7F) << 1; // TODO: some minusing has to happen for pressure
	  tx_str_buffer[2] |=	(sensor_data_ptr->data_received & 0x01);
	  
	  /* byte3: Sats(5 bits) and reset count(3 bits)*/
	  tx_str_buffer[3] |= (sensor_data_ptr->sats & 0x1F) << 3;
	  tx_str_buffer[3] |= (sensor_data_ptr->reset_count & 0x07);

	  
	  fill_tx_buffer_with_location(4, tx_str_buffer, current_pos_ptr->latitude,current_pos_ptr->longitude,current_pos_ptr->altitude);

	  
	  for (int i = 0; i < current_playback_key_info.n_positions_to_send; i++)
	  {
		  time_pos_fix_t temp_pos = subset_positions_ptr[i];
		  fill_tx_buffer_with_location_and_time(4 + POSITION_BYTES_LEN + i * (POSITION_BYTES_LEN+MINUTES_SINCE_EPOCH_BYTES_LEN), 
												tx_str_buffer,
												temp_pos.latitude,
												temp_pos.longitude,
												temp_pos.altitude,
												temp_pos.minutes_since_epoch);
		  
	  }


	  tx_str_buffer_len = 4 + POSITION_BYTES_LEN + (POSITION_BYTES_LEN+MINUTES_SINCE_EPOCH_BYTES_LEN) * current_playback_key_info.n_positions_to_send;
	  
	  // Print out buffer for debug
	  for (int i = 0; i<tx_str_buffer_len;i ++)
	  {
		  printf("%02x",tx_str_buffer[i]);
	  }
	  
}


/**
 * \brief  return pointer to tx_str_buffer
 * 
 * 
 * \return uint8_t *
 */
uint8_t *get_tx_buffer()
{
	return tx_str_buffer;
}

/**
 * \brief return length of tx buffer
 * 
 * 
 * \return uint16_t
 */
uint16_t  get_tx_buffer_len()
{
	return tx_str_buffer_len;
}

/**
 * \brief Intialise the pointers with pointers to actual buffer locations
 *  Initialises this module
 * 
 * \param n_positions_in_eeprom
 * \param subset_positions
 * \param sensor_data
 * \param current_pos
 * 
 * \return void
 */
void init_playback(uint16_t n_positions_in_eeprom, time_pos_fix_t *subset_positions, sensor_t *sensor_data, time_pos_fix_t *current_pos )
{
	current_playback_key_info.n_positions_in_eeprom = n_positions_in_eeprom;
	subset_positions_ptr = subset_positions;
	sensor_data_ptr = sensor_data;
	current_pos_ptr = current_pos;

}

