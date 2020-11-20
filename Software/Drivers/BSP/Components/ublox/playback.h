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

#define MAX_SUBSET_SIZE 100U


typedef struct
{
	uint16_t n_positions_in_eeprom;
	uint16_t current_index_in_eeprom;

}playback_key_info_t;



/* ==================================================================== */
/* ========================== public data ============================= */
/* ==================================================================== */

/* Definition of public (external) data types go here */
void prepare_tx_buffer( void );


uint8_t * get_tx_buffer( void );
uint16_t get_tx_buffer_len( void );
void  init_playback(uint16_t current_index_in_eeprom, uint16_t n_positions_in_eeprom, time_pos_fix_t *subset_positions );
/* ==================================================================== */
/* ======================= public functions =========================== */
/* ==================================================================== */

/* Function prototypes for public (external) functions go here */


#endif
#ifdef __cplusplus
}
#endif







