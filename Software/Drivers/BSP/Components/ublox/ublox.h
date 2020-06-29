/**
  ******************************************************************************
  * @file           : ublox.h
  * @brief          : Driver header file for ublox.c
  ******************************************************************************
  * Imperial College Space Society
	* Medad Newman, Richard Ibbotson
  *
  *
  ******************************************************************************
  */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef UBLOX_H
#define UBLOX_H


/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of system and local header files goes here */

#include "stm32l0xx_hal.h"
#include <stdint.h>

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */

typedef enum
{
	GPS_SUCCESS = 0,
	GPS_FAILURE
} gps_status_t;


/* ==================================================================== */
/* ========================== public data ============================= */
/* ==================================================================== */

/* Definition of public (external) data types go here */


extern float GPS_UBX_latitude_Float;							// YY.YYYYYYY, in +/- DEGREES (?), also used as output of Coords_DEGtoDEC()
extern float GPS_UBX_longitude_Float;							// XXX.XXXXXXX, in +/- DEGREES (?), also used as output of Coords_DEGtoDEC()

extern int32_t GPSaltitude;										// for both UBX and NMEA, in +/- meters (m)
extern uint8_t GPSsats;											// for both UBX and NMEA

/* ==================================================================== */
/* ======================= public functions =========================== */
/* ==================================================================== */

/* Function prototypes for public (external) functions go here */

extern gps_status_t get_location_fix(uint32_t timeout);
extern gps_status_t setup_GPS(void);
extern gps_status_t get_latest_gps_status(void);


#endif
#ifdef __cplusplus
}
#endif







