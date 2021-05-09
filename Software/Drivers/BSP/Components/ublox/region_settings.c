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
	network_keys_t network_keys;

	switch (Loramac_region)
	{
	case LORAMAC_REGION_AS923:
		break;

	case LORAMAC_REGION_AU915:
		break;

	case LORAMAC_REGION_CN470:
		break;

	case LORAMAC_REGION_CN779:
		break;

	case LORAMAC_REGION_EU433:
		break;

	case LORAMAC_REGION_EU868:
		network_keys = eu868_network_keys;
		break;

	case LORAMAC_REGION_KR920:
		break;

	case LORAMAC_REGION_IN865:
		break;

	case LORAMAC_REGION_US915:
		break;

	case LORAMAC_REGION_RU864:
		break;

	default:
		network_keys = eu868_network_keys;
		break;
	}

	return network_keys;
}
