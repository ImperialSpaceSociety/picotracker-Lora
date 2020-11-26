/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: contains all hardware driver

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
/**
  ******************************************************************************
  * @file    bsp.h
  * @author  MCD Application Team
  * @brief   contains all hardware driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H__
#define __BSP_H__

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"


/* Exported types ------------------------------------------------------------*/

typedef struct{
  uint16_t pressure;    /* in mbar */  
  int8_t temperature; /* in °C   */
  int8_t humidity;    /* in %    */
  uint16_t latitude;
  uint16_t longitude ;
  uint16_t altitudeGps;       /* in m */
  uint8_t no_load_solar_voltage;
  uint8_t load_solar_voltage;
  uint8_t sats;                 /* satellites in fix */
  uint16_t reset_count;          /* Count number of resets */
  uint8_t data_received;
  /**more may be added*/
} sensor_t;

typedef struct
{
  uint32_t minutes_since_epoch; // minutes since Epoch
  uint16_t latitude;        // Latitude
  uint16_t longitude;       // Longitude
  uint16_t altitude;     // Altitude

}time_pos_fix_t;



#define RESITOR_DIVIDER_PROD                    ((100000.0+100000.0)/100000.0)
#define RESITOR_DIVIDER                         (float)(RESITOR_DIVIDER_PROD)



// EEPROM related defines


#define FRAME_COUNTER_EEPROM_ADDRESS               (0)
#define FRAME_COUNTER_EEPROM_LEN                   (4)

#define LORAMAC_REGION_EEPROM_ADDR                 (4)
#define LORAMAC_REGION_EEPROM_LEN                  (4)


#define RESET_COUNTER_ADDR                         (8)
#define RESET_COUNTER_LEN                          (2)


#define CURRENT_PLAYBACK_INDEX_IN_EEPROM_ADDR      (10)
#define CURRENT_PLAYBACK_INDEX_IN_EEPROM_LEN       (2)

#define N_PLAYBACK_POSITIONS_SAVED_IN_EEPROM_ADDR  (12)
#define N_PLAYBACK_POSITIONS_SAVED_IN_EEPROM_LEN   (2)

#define PLAYBACK_EEPROM_ADDR_START                 (14)
#define PLAYBACK_EEPROM_PACKET_SIZE                (9)
#define MAX_PLAYBACK_POSITIONS_SAVED_IN_EEPROM     (650)
#define PLAYBACK_EEPROM_SIZE                       (MAX_PLAYBACK_POSITIONS_SAVED_IN_EEPROM * PLAYBACK_EEPROM_PACKET_SIZE)

/* WARNING! Ensure this value is less than DATA_EEPROM_BANK2_END. Or else, it will overflow EEPROM */
#define NVM_GPS_EEPROM_ADDR_END                    (NVM_GPS_EEPROM_ADDR_START - 1 + PLAYBACK_EEPROM_SIZE)
																												


/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
/**
 * @brief  initialises the sensor
 *
 * @note
 * @retval None
 */
void  BSP_sensor_Init( void  );

/**
 * @brief  sensor  read. 
 *
 * @note none
 * @retval sensor_data
 */
void BSP_sensor_Read( void );



/**
  * @brief It measures the battery voltage by returning the value in mV
  * @param none
  * @retval uint16_t The battery voltage value in mV
  */
uint16_t BSP_GetSolarLevel16( void );


/*!
 * Writes the given buffer to the EEPROM at the specified address.
 *
 * \param[IN] addr EEPROM address to write to
 * \param[IN] buffer Pointer to the buffer to be written.
 * \param[IN] size Size of the buffer to be written.
 * \retval status [SUCCESS, FAIL]
 */
uint8_t EepromMcuWriteBuffer( uint16_t addr, uint8_t *buffer, uint16_t size );

/*!
 * Reads the EEPROM at the specified address to the given buffer.
 *
 * \param[IN] addr EEPROM address to read from
 * \param[OUT] buffer Pointer to the buffer to be written with read data.
 * \param[IN] size Size of the buffer to be read.
 * \retval status [SUCCESS, FAIL]
 */
uint8_t EepromMcuReadBuffer( uint16_t addr, uint8_t *buffer, uint16_t size );

uint16_t minute_from_epoch_to_time_pos_index(uint32_t minutes_from_epoch);
void manage_incoming_instruction(uint8_t *instructions);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_H__ */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
