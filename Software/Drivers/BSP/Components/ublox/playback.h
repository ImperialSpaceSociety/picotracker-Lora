/**
  ******************************************************************************
  * @file           : playback.h
  * @brief          : manages playback of coordinates
  ******************************************************************************
  * Imperial College Space Society
	* Medad Newman, Richard Ibbotson
	* 2/11/2020
  *
  *
  ******************************************************************************
  */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef PLAYBACK_H
#define PLAYBACK_H


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of system and local header files goes here */
#include <stdint.h>
#include "bsp.h"

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */

typedef struct
{
	uint16_t n_positions_in_eeprom;            /* Number of positions held in the EEPROM */
	uint16_t n_positions_to_send;              /* Number of positions to send down in single transmission*/
	uint16_t n_positions_offset;               /* Send positions from n_positions_offset from current position. */
	uint16_t n_positions_to_select_from;       /* Define size of pool of positions to select from */
}playback_key_info_t;



/* ==================================================================== */
/* ========================== public data ============================= */
/* ==================================================================== */

/* Definition of public (external) data types go here */
void prepare_tx_buffer( void );
playback_key_info_t *get_playback_key_info( void );

typedef time_pos_fix_t (*retrieve_eeprom_time_pos_ptr_T)(uint16_t time_pos_index);

double corput(int n, int base);
uint8_t * get_tx_buffer( void );
uint16_t get_tx_buffer_len( void );
void init_playback(uint16_t n_positions_in_eeprom, sensor_t *sensor_data, time_pos_fix_t *current_pos , retrieve_eeprom_time_pos_ptr_T retrieve_eeprom_time_pos_ptr);

/* ==================================================================== */
/* ======================= public functions =========================== */
/* ==================================================================== */

/* Function prototypes for public (external) functions go here */


#endif
#ifdef __cplusplus
}
#endif







