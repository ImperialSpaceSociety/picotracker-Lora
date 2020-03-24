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
#include "hw.h"

/* Exported types ------------------------------------------------------------*/

typedef struct{
  float pressure;    /* in mbar */  
  float temperature; /* in °C   */
  float humidity;    /* in %    */
  int32_t latitude;
  int32_t longitude ;
  int16_t  altitudeGps;       /* in m */
  int16_t altitudeBar ;       /* in m * 10 */
  /**more may be added*/
} sensor_t;




#define RESITOR_DIVIDER_PROD                    ((100000.0+100000.0)/100000.0)
#define RESITOR_DIVIDER                         (float)(RESITOR_DIVIDER_PROD)



// EEPROM related defines
#define EEPROM_ADDR_START                       0x08080000       /* Start @ of STM32 internal EEPROM area */

#define DEVICE_EUI_EEPROM_ID                    (1)
#define DEVICE_EUI_EEPROM_OFFSET                (0)
#define DEVICE_EUI_EEPROM_LEN                   (8)
#define DEVICE_EUI_EEPROM_ADDRESS               (uint32_t)(EEPROM_ADDR_START + DEVICE_EUI_EEPROM_OFFSET)

#define JOIN_EUI_EEPROM_ID                      (2)
#define JOIN_EUI_EEPROM_OFFSET                  (DEVICE_EUI_EEPROM_OFFSET + DEVICE_EUI_EEPROM_LEN)
#define JOIN_EUI_EEPROM_LEN                     (8)
#define JOIN_EUI_EEPROM_ADDRESS                 (uint32_t)(EEPROM_ADDR_START + JOIN_EUI_EEPROM_OFFSET)

#define APP_KEY_EEPROM_ID                       (4)
#define APP_KEY_EEPROM_OFFSET                   (DEVICE_EUI_EEPROM_OFFSET + DEVICE_EUI_EEPROM_LEN + JOIN_EUI_EEPROM_LEN)
#define APP_KEY_EEPROM_LEN                      (16)
#define APP_KEY_EEPROM_ADDRESS                  (uint32_t)(EEPROM_ADDR_START + APP_KEY_EEPROM_OFFSET)

#define NWK_KEY_EEPROM_ID                       (8)
#define NWK_KEY_EEPROM_OFFSET                   (DEVICE_EUI_EEPROM_OFFSET + DEVICE_EUI_EEPROM_LEN + JOIN_EUI_EEPROM_LEN + APP_KEY_EEPROM_LEN)
#define NWK_KEY_EEPROM_LEN                      (16)
#define NWK_KEY_EEPROM_ADDRESS                  (uint32_t)(EEPROM_ADDR_START + NWK_KEY_EEPROM_OFFSET)

#define PLATFORM_STATUS_EEPROM_OFFSET           (64)
#define PLATFORM_STATUS_EEPROM_ADDRESS          (EEPROM_ADDR_START + PLATFORM_STATUS_EEPROM_OFFSET)
#define PLATFORM_STATUS_EEPROM_LEN              sizeof(PlatformStatus_t)

   

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
void BSP_sensor_Read( sensor_t *sensor_data);



/**
  * @brief It measures the battery voltage by returning the value in mV
  * @param none
  * @retval uint16_t The battery voltage value in mV
  */
uint16_t BSP_GetBatteryLevel16( void );


void WriteInternalEepromBuffer(uint32_t dest_addr, uint32_t num_bytes, uint8_t *buffer_to_write);
uint8_t EepromLoraKeysValidation(void);
void LoadLoraKeys( void );

#ifdef __cplusplus
}
#endif

#endif /* __BSP_H__ */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
