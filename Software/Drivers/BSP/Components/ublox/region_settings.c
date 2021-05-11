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
	.DevAddr = (uint32_t)0x0087628D,
};

#define COMMON_AU915_KEYS                                                                              \
	{                                                                                                  \
		0x63, 0xB1, 0xAA, 0xD8, 0x11, 0xF6, 0x69, 0x2A, 0x55, 0xEF, 0x4D, 0x88, 0x9B, 0xD5, 0x14, 0xCC \
	}
network_keys_t AU915_network_keys = {
	.FNwkSIntKey = COMMON_AU915_KEYS,
	.SNwkSIntKey = COMMON_AU915_KEYS,
	.NwkSEncKey = COMMON_AU915_KEYS,
	.AppSKey = {0xB1, 0x86, 0x74, 0x6B, 0xD5, 0xC0, 0x9F, 0x75, 0x9C, 0x8C, 0x74, 0x9B, 0x44, 0xC7, 0x2D, 0x1F},
	.DevAddr = (uint32_t)0x260B88E9,
};

#define COMMON_CN779_KEYS                                                                              \
	{                                                                                                  \
		0x63, 0xB1, 0xAA, 0xD8, 0x11, 0xF6, 0x69, 0x2A, 0x55, 0xEF, 0x4D, 0x88, 0x9B, 0xD5, 0x14, 0xCC \
	}
network_keys_t CN779_network_keys = {
	.FNwkSIntKey = COMMON_CN779_KEYS,
	.SNwkSIntKey = COMMON_CN779_KEYS,
	.NwkSEncKey = COMMON_CN779_KEYS,
	.AppSKey = {0xB1, 0x86, 0x74, 0x6B, 0xD5, 0xC0, 0x9F, 0x75, 0x9C, 0x8C, 0x74, 0x9B, 0x44, 0xC7, 0x2D, 0x1F},
	.DevAddr = (uint32_t)0x260B88E9,
};

#define COMMON_EU868_KEYS                                                                              \
	{                                                                                                  \
		0x63, 0xB1, 0xAA, 0xD8, 0x11, 0xF6, 0x69, 0x2A, 0x55, 0xEF, 0x4D, 0x88, 0x9B, 0xD5, 0x14, 0xCC \
	}
network_keys_t EU868_network_keys = {
	.FNwkSIntKey = COMMON_EU868_KEYS,
	.SNwkSIntKey = COMMON_EU868_KEYS,
	.NwkSEncKey = COMMON_EU868_KEYS,
	.AppSKey = {0xB1, 0x86, 0x74, 0x6B, 0xD5, 0xC0, 0x9F, 0x75, 0x9C, 0x8C, 0x74, 0x9B, 0x44, 0xC7, 0x2D, 0x1F},
	.DevAddr = (uint32_t)0x260B88E9,
};

#define COMMON_KR920_KEYS                                                                              \
	{                                                                                                  \
		0x63, 0xB1, 0xAA, 0xD8, 0x11, 0xF6, 0x69, 0x2A, 0x55, 0xEF, 0x4D, 0x88, 0x9B, 0xD5, 0x14, 0xCC \
	}
network_keys_t KR920_network_keys = {
	.FNwkSIntKey = COMMON_KR920_KEYS,
	.SNwkSIntKey = COMMON_KR920_KEYS,
	.NwkSEncKey = COMMON_KR920_KEYS,
	.AppSKey = {0xB1, 0x86, 0x74, 0x6B, 0xD5, 0xC0, 0x9F, 0x75, 0x9C, 0x8C, 0x74, 0x9B, 0x44, 0xC7, 0x2D, 0x1F},
	.DevAddr = (uint32_t)0x260B88E9,
};

#define COMMON_IN865_KEYS                                                                              \
	{                                                                                                  \
		0x63, 0xB1, 0xAA, 0xD8, 0x11, 0xF6, 0x69, 0x2A, 0x55, 0xEF, 0x4D, 0x88, 0x9B, 0xD5, 0x14, 0xCC \
	}
network_keys_t IN865_network_keys = {
	.FNwkSIntKey = COMMON_IN865_KEYS,
	.SNwkSIntKey = COMMON_IN865_KEYS,
	.NwkSEncKey = COMMON_IN865_KEYS,
	.AppSKey = {0xB1, 0x86, 0x74, 0x6B, 0xD5, 0xC0, 0x9F, 0x75, 0x9C, 0x8C, 0x74, 0x9B, 0x44, 0xC7, 0x2D, 0x1F},
	.DevAddr = (uint32_t)0x260B88E9,
};

#define COMMON_US915_KEYS                                                                              \
	{                                                                                                  \
		0x63, 0xB1, 0xAA, 0xD8, 0x11, 0xF6, 0x69, 0x2A, 0x55, 0xEF, 0x4D, 0x88, 0x9B, 0xD5, 0x14, 0xCC \
	}
network_keys_t US915_network_keys = {
	.FNwkSIntKey = COMMON_US915_KEYS,
	.SNwkSIntKey = COMMON_US915_KEYS,
	.NwkSEncKey = COMMON_US915_KEYS,
	.AppSKey = {0xB1, 0x86, 0x74, 0x6B, 0xD5, 0xC0, 0x9F, 0x75, 0x9C, 0x8C, 0x74, 0x9B, 0x44, 0xC7, 0x2D, 0x1F},
	.DevAddr = (uint32_t)0x260B88E9,
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
