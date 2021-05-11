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

#define COMMON_AS923_KEYS                                                                              \
	{                                                                                                  \
		0xD8, 0x48, 0x86, 0x98, 0xE9, 0x1D, 0x24, 0xEC, 0x9C, 0x80, 0xB7, 0x3B, 0x40, 0x37, 0x68, 0xDE \
	}
network_keys_t AS923_network_keys = {
	.FNwkSIntKey = COMMON_AS923_KEYS,
	.SNwkSIntKey = COMMON_AS923_KEYS,
	.NwkSEncKey = COMMON_AS923_KEYS,
	.AppSKey = {0xED, 0x62, 0xBB, 0x87, 0x43, 0xBF, 0xEF, 0x4C, 0x46, 0x92, 0x80, 0x6B, 0xF4, 0xBF, 0xA6, 0x49},
	.DevAddr = (uint32_t)0x260B67E7,
};

#define COMMON_AU915_KEYS                                                                              \
	{                                                                                                  \
		0xEE, 0x1B, 0xE3, 0x41, 0xD1, 0x29, 0xC6, 0x79, 0xBC, 0x76, 0xE6, 0xF7, 0x62, 0xAB, 0x55, 0xBC \
	}
network_keys_t AU915_network_keys = {
	.FNwkSIntKey = COMMON_AU915_KEYS,
	.SNwkSIntKey = COMMON_AU915_KEYS,
	.NwkSEncKey = COMMON_AU915_KEYS,
	.AppSKey = {0x6B, 0x53, 0x2A, 0x66, 0x28, 0x48, 0xD0, 0x56, 0x54, 0x70, 0xAF, 0xC9, 0x19, 0xA8, 0x86, 0x96},
	.DevAddr = (uint32_t)0x260B8026,
};

#define COMMON_CN779_KEYS                                                                              \
	{                                                                                                  \
		0x63, 0xB1, 0xAA, 0xD8, 0x11, 0xF6, 0x69, 0x2A, 0x55, 0xEF, 0x4D, 0x88, 0x9B, 0xD5, 0x14, 0xCC \
	}
network_keys_t CN779_network_keys = {
	.FNwkSIntKey = COMMON_CN779_KEYS,
	.SNwkSIntKey = COMMON_CN779_KEYS,
	.NwkSEncKey = COMMON_CN779_KEYS,
	.AppSKey = {0x09, 0xA0, 0x74, 0x4F, 0x22, 0x7C, 0x43, 0xD1, 0xDC, 0x2A, 0x48, 0x2E, 0xAB, 0xCE, 0x92, 0x41},
	.DevAddr = (uint32_t)0x260B9E90,
};

#define COMMON_EU868_KEYS                                                                              \
	{                                                                                                  \
		0x8B, 0xD4, 0xD7, 0x56, 0xF2, 0x9D, 0x94, 0xA7, 0xE8, 0x66, 0xF3, 0xCA, 0x70, 0x31, 0xD6, 0xD5 \
	}
network_keys_t EU868_network_keys = {
	.FNwkSIntKey = COMMON_EU868_KEYS,
	.SNwkSIntKey = COMMON_EU868_KEYS,
	.NwkSEncKey = COMMON_EU868_KEYS,
	.AppSKey = {0x33, 0x9C, 0x79, 0xC3, 0xB1, 0x69, 0x2E, 0xA7, 0x79, 0xD3, 0xCD, 0xD8, 0x89, 0x0C, 0x7F, 0x36},
	.DevAddr = (uint32_t)0x260B7827,
};

#define COMMON_KR920_KEYS                                                                              \
	{                                                                                                  \
		0xD1, 0xD1, 0xEC, 0x3E, 0xC1, 0xF6, 0x48, 0x14, 0xAB, 0x60, 0x96, 0x4F, 0x59, 0xF1, 0x50, 0xA7 \
	}
network_keys_t KR920_network_keys = {
	.FNwkSIntKey = COMMON_KR920_KEYS,
	.SNwkSIntKey = COMMON_KR920_KEYS,
	.NwkSEncKey = COMMON_KR920_KEYS,
	.AppSKey = {0xDE, 0xA8, 0xE3, 0x40, 0x29, 0xE4, 0xFE, 0xFE, 0x60, 0xB7, 0x1C, 0xC8, 0xBF, 0xF6, 0xA1, 0x29},
	.DevAddr = (uint32_t)0x260B8E92,
};

#define COMMON_IN865_KEYS                                                                              \
	{                                                                                                  \
		0xB0, 0xFD, 0x52, 0x2C, 0xC9, 0xC8, 0x02, 0xE9, 0x7A, 0x9D, 0x74, 0x4E, 0xE6, 0x88, 0xBB, 0x61 \
	}
network_keys_t IN865_network_keys = {
	.FNwkSIntKey = COMMON_IN865_KEYS,
	.SNwkSIntKey = COMMON_IN865_KEYS,
	.NwkSEncKey = COMMON_IN865_KEYS,
	.AppSKey = {0xF6, 0x31, 0x53, 0xC1, 0xE8, 0x94, 0x81, 0x86, 0x3A, 0x7D, 0x1D, 0x3C, 0x2C, 0xF7, 0x93, 0x87},
	.DevAddr = (uint32_t)0x260B52E9,
};

#define COMMON_US915_KEYS                                                                              \
	{                                                                                                  \
		0x05, 0x55, 0x91, 0x59, 0xA2, 0x6E, 0x53, 0xD0, 0x6F, 0x2F, 0x96, 0x6C, 0x20, 0x03, 0x76, 0xD7 \
	}
network_keys_t US915_network_keys = {
	.FNwkSIntKey = COMMON_US915_KEYS,
	.SNwkSIntKey = COMMON_US915_KEYS,
	.NwkSEncKey = COMMON_US915_KEYS,
	.AppSKey = {0xC2, 0xB0, 0x92, 0x96, 0x18, 0x99, 0x00, 0x9F, 0x82, 0x6A, 0x76, 0xB1, 0xEA, 0x29, 0xCB, 0xA0},
	.DevAddr = (uint32_t)0x260BDD73,
};

#define COMMON_RU864_KEYS                                                                              \
	{                                                                                                  \
		0x63, 0xB1, 0xAA, 0xD8, 0x11, 0xF6, 0x69, 0x2A, 0x55, 0xEF, 0x4D, 0x88, 0x9B, 0xD5, 0x14, 0xCC \
	}
network_keys_t RU864_network_keys = {
	.FNwkSIntKey = COMMON_RU864_KEYS,
	.SNwkSIntKey = COMMON_RU864_KEYS,
	.NwkSEncKey = COMMON_RU864_KEYS,
	.AppSKey = {0xB1, 0x86, 0x74, 0x6B, 0xD5, 0xC0, 0x9F, 0x75, 0x9C, 0x8C, 0x74, 0x9B, 0x44, 0xC7, 0x2D, 0x1F},
	.DevAddr = (uint32_t)0x260B88E9,
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

	/**
	 * @brief return network keys for each region. Don't bother with
	 * LORAMAC_REGION_CN470 or LORAMAC_REGION_EU433 because we
	 * don't use them
	 */
	switch (Loramac_region)
	{
	case LORAMAC_REGION_AS923:
		network_keys = AS923_network_keys;
		break;

	case LORAMAC_REGION_AU915:
		network_keys = AU915_network_keys;
		break;

	case LORAMAC_REGION_CN779:
		network_keys = CN779_network_keys;
		break;

	case LORAMAC_REGION_EU868:
		network_keys = EU868_network_keys;
		break;

	case LORAMAC_REGION_KR920:
		network_keys = KR920_network_keys;
		break;

	case LORAMAC_REGION_IN865:
		network_keys = IN865_network_keys;
		break;

	case LORAMAC_REGION_US915:
		network_keys = US915_network_keys;
		break;

	case LORAMAC_REGION_RU864:
		network_keys = RU864_network_keys;
		break;

	default:
		network_keys = EU868_network_keys;
		break;
	}

	return network_keys;
}
