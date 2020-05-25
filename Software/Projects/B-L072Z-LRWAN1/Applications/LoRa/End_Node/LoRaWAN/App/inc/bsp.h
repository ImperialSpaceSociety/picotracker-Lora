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
  double pressure;    /* in mbar */  
  double temperature; /* in °C   */
  double humidity;    /* in %    */
  float latitude;
  float longitude ;
  uint32_t  altitudeGps;       /* in m */
	uint16_t battery_level16;
  /**more may be added*/
} sensor_t;


extern uint16_t battery_level16;
extern uint32_t VCC_ADC;


#define RESITOR_DIVIDER_PROD                    ((100000.0+100000.0)/100000.0)
#define RESITOR_DIVIDER                         (float)(RESITOR_DIVIDER_PROD)



// EEPROM related defines
#define EEPROM_ADDR_START                       0x08080000       /* Start @ of STM32 internal EEPROM area */

#define FRAME_COUNTER_EEPROM_ID                    (1)
#define FRAME_COUNTER_EEPROM_OFFSET                (0)
#define FRAME_COUNTER_EEPROM_LEN                   (8)
#define FRAME_COUNTER_EEPROM_ADDRESS               (uint32_t)(EEPROM_ADDR_START + FRAME_COUNTER_EEPROM_OFFSET)

   

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


void WriteInternalEepromBuffer(uint32_t dest_addr, uint32_t data);
uint8_t EepromLoraKeysValidation(void);
void LoadLoraKeys( void );
void LoadFrameCounter( uint32_t* fcnt );
uint8_t EepromFrameCounterValidation(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_H__ */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
