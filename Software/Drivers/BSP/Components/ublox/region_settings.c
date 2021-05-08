/**
 * @file region_settings.c
 * @author Medad Rufus Newman (mailto@medadnewman.co.uk)
 * @brief 
 * @version 0.1
 * @date 2021-05-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

/* Inclusion of system and local header files goes here */
#include "region_setting.h"
#include "Commissioning.h"

/* ==================================================================== */
/* ============================ constants ============================= */
/* ==================================================================== */

/* #define and enum statements go here */

/* ==================================================================== */
/* ======================== global variables ========================== */
/* ==================================================================== */

/* Global variables definitions go here */

/* ==================================================================== */
/* ========================== private data ============================ */
/* ==================================================================== */

/* Definition of private datatypes go here */

network_keys_t eu868_network_keys = {
	.FNwkSIntKey = LORAWAN_F_NWK_S_INT_KEY,
	.AppSKey = LORAWAN_APP_S_KEY,
	.DevAddr = LORAWAN_DEVICE_ADDRESS,
};

network_keys_t eu868_network_keys = {
	.FNwkSIntKey = LORAWAN_F_NWK_S_INT_KEY,
	.AppSKey = LORAWAN_APP_S_KEY,
	.DevAddr = LORAWAN_DEVICE_ADDRESS,
};

network_keys_t *all_network_keys[] = {
	&eu868_network_keys,
};

/* ==================================================================== */
/* ====================== private functions =========================== */
/* ==================================================================== */

/* Function prototypes for private (static) functions go here */
network_keys_t get_network_keys(LoRaMacRegion_t Loramac_region);

/* ==================================================================== */
/* ===================== All functions by section ===================== */
/* ==================================================================== */

/* Functions definitions go here, organised into sections */

network_keys_t get_network_keys(LoRaMacRegion_t Loramac_region)
{
	return *all_network_keys[Loramac_region];
}
