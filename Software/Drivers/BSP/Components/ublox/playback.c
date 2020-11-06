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
 

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */

/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */



typedef struct
{
	uint32_t timestamp; // epoch time in seconds
	uint32_t latitude;  // Latitude
	uint32_t longitude; // Longitude
	
}time_pos_fix;


/* ==================================================================== */
/* ========================== private data ============================ */
/* ==================================================================== */

/* Definition of private datatypes go here */





/* ==================================================================== */
/* ====================== private functions =========================== */
/* ==================================================================== */

/* Function prototypes for private (static) functions go here */

void save_position(uint32_t timestamp, uint32_t latitude, uint32_t longitude);

/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

