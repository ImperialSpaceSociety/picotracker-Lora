#ifdef __cplusplus
extern "C"
{
#endif

#ifndef UBLOX_UBX_MESSAGES_H
#define UBLOX_UBX_MESSAGES_H


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




/* ==================================================================== */
/* ========================== public data ============================= */
/* ==================================================================== */

/* Definition of public (external) data types go here */


extern uint8_t setGPSonly[68];	
extern uint8_t setNMEAoff[28];
extern uint8_t setNMEAon[28];
extern uint8_t setNAVmode[44];
extern uint8_t restore_default_config[21];
extern uint8_t set_continueous_mode[10];
extern uint8_t set_power_save_mode[10];

	/*
	REQUESTS.
	Response to these messages is message specific.
*/
	
/* NAVIGATION ENGINE					response 44 bytes */
extern uint8_t request0624[8];

/* GNSS configuration					response 52 bytes */
extern uint8_t request063E[8];
	
/* POSITION DATA						response 36 bytes */
extern uint8_t request0102[8];

/* FIX, SATS							response 60 bytes */
extern uint8_t request0106[8];

/* TIME, DATE							response 28 bytes */
extern uint8_t request0121[8];

/* EVERYTHING							response 100 bytes (UBLOX 8), 92 bytes (UBLOX 7) */
extern uint8_t request0107[8];
/* VERSION								response 48 + 30 * N bytes */
extern uint8_t request0A04[8];

/* HARDWARE RESET Reset Options: Forced(Watchdog)  Startup Option: Coldstart     no response */
extern uint8_t resetReceiver[12];


/* SAVE CURRENT CONFIGURATION CFG-CFG			no response */
extern uint8_t saveConfiguration[21];



/*
	POWER SAVING.
	Response to these UBX messages is ACK/NACK - 10 bytes.
*/



/* Switches to the continuous mode. */
extern uint8_t setContinuousMode[10];

/* Switches to the selected power saving configuration. */
extern uint8_t setPowerSaveMode[10];

/* Backup mode for infinite duration. */
extern uint8_t setBackupMode[16];
	
/* Software backup mode. DEPRECIATED! */
extern uint8_t setSwBackupMode[16];

	
extern uint8_t powersave_config[56];
	

/* ==================================================================== */
/* ======================= public functions =========================== */
/* ==================================================================== */

/* Function prototypes for public (external) functions go here */


#endif // UBLOX_UBX_MESSAGES_H
#ifdef __cplusplus
}
#endif
