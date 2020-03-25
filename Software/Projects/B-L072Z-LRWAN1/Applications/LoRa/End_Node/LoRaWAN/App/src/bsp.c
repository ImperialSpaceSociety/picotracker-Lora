/**
  ******************************************************************************
  * @file    bsp.c
  * @author  MCD Application Team
  * @brief   manages the sensors on the application
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

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "hw.h"
#include "timeServer.h"
#include "bsp.h"
#include "ms5607.h"
#include "ublox.h"
#include "main.h"


extern uint16_t battery_level16;
extern uint32_t fCntUp_global;



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BATTERY_ADC_CHANNEL             ADC_CHANNEL_5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)
void *HUMIDITY_handle = NULL;
void *TEMPERATURE_handle = NULL;
void *PRESSURE_handle = NULL;
#endif

void BSP_sensor_Read( sensor_t *sensor_data)
{
	TVL1(PRINTF("READING SENSOR AND GPS\n\r");)

  /* USER CODE BEGIN 5 */
	#if defined (SENSOR_ENABLED)
	MS5607_get_temp_pressure();
	#endif
  
	#if defined (GPS_ENABLED)
	get_location_fix();
	#endif
	
	battery_level16 = (uint16_t) BSP_GetBatteryLevel16();

	
	PRINTF("================================================================\r\n");
	PRINTF("SENSOR AND GPS VALUES");
	PRINTF("\r\n"); 
	PRINTF("================================================================\r\n");

	PRINTF("Temperature degrees C: "); 
	PRINTF("%lf", TEMPERATURE_Value); 
	PRINTF("\r\n"); 
	PRINTF("Pressure mBar: "); 
	PRINTF("%lf", PRESSURE_Value); 
	PRINTF("\r\n");
	PRINTF("Longitude: "); 
	PRINTF("%lf", GPS_UBX_longitude_Float); 
	PRINTF("\r\n"); 
	PRINTF("Latitude: "); 
	PRINTF("%lf", GPS_UBX_latitude_Float); 
	PRINTF("\r\n");
	PRINTF("altitude: "); 
	PRINTF("%ld", GPSaltitude	); 
	PRINTF("\r\n");
	PRINTF("Solar voltage: "); 
	PRINTF("%ld", battery_level16	); 
	PRINTF("\r\n");
	PRINTF("================================================================\r\n");


	
	
  sensor_data->humidity    = 34; // hard coded dummy value
  sensor_data->temperature = TEMPERATURE_Value;
  sensor_data->pressure    = PRESSURE_Value;

  /* USER CODE END 5 */
}

void  BSP_sensor_Init( void  )
{
	#if defined (SENSOR_ENABLED)
  /* Initialize sensors */	
		ms5607_Init();
	#endif
	
	 #if defined (GPS_ENABLED)

	 //GPS SETUP
	 setup_GPS();

	 // GPS INITIAL BACKUP
	 Backup_GPS();
	#endif

}


/**
  * @brief It measures the battery voltage by returning the value in mV
  * @param none
  * @retval uint16_t The battery voltage value in mV
  */
uint16_t BSP_GetBatteryLevel16( void )
{

  uint16_t batteryLevel = 0;
  uint16_t measuredLevel = 0;
  uint16_t nVrefIntLevel = 0;
  float batteryVoltage = 0;
  float nVddValue = 0;
  

  measuredLevel = HW_AdcReadChannel( BATTERY_ADC_CHANNEL ); 
  nVrefIntLevel = HW_AdcReadChannel( ADC_CHANNEL_VREFINT ); 
	
	
  nVddValue = (( (uint32_t) VDDA_VREFINT_CAL * (*VREFINT_CAL ) )/ nVrefIntLevel);
  
  batteryVoltage =  ((( (float)(measuredLevel) * nVddValue/*3300*/) / 4096) * RESITOR_DIVIDER);
  
  batteryLevel = (uint16_t)(batteryVoltage / 1.0);
  
  return batteryLevel;
}

/** @brief Write in STM32 internal EEPROM 
  * @param dest_addr EEPROM address (range 0x08080000 - 0x080817FF)
  * @param data uint32_t data
  * @retval none
  */
void WriteInternalEepromBuffer(uint32_t dest_addr, uint32_t data)
{
  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR );
  

  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, dest_addr, data);
  
  HAL_FLASH_Lock();
}

///**
//  * @brief Check LoRa Keys saved in EEPROM
//  * @param none
//  * @retval BC_ChargeStatusTypeDef Battery charging status
//  */
//uint8_t EepromLoraKeysValidation(void)
//{
//  uint8_t retval = 0;
//  /* DevEui validation */
//  if((*(uint64_t*)DEVICE_EUI_EEPROM_ADDRESS) == 0)
//  {
//    retval |= DEVICE_EUI_EEPROM_ID;
//  }
//  return retval;
//}

/**
  * @brief Check Frame Counter value saved in EEPROM
  * @param none
  * @retval BC_ChargeStatusTypeDef Battery charging status
  */
uint8_t EepromFrameCounterValidation(void)
{
  uint8_t retval = 0;
  /* DevEui validation */
  if((*(uint64_t*)FRAME_COUNTER_EEPROM_ADDRESS) == 0)
  {
    retval |= FRAME_COUNTER_EEPROM_ID;
  }
  return retval;
}

///**
//  * @brief  Load Lora keys (DevEui, JoinEui, AppKey, NwkKey) from STM32 internal EEPROM
//  * @param  None
//  * @retval None
//  */
//void LoadLoraKeys()
//{
//#if SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
//  extern uint8_t DevEui[];
//  extern uint8_t JoinEui[];
//  extern uint8_t AppKey[];
//  extern uint8_t NwkKey[];
//  
//  if(EepromLoraKeysValidation() != 0)
//  {
//    return;
//  }
//  
//  memcpy(DevEui, (void*)DEVICE_EUI_EEPROM_ADDRESS, DEVICE_EUI_EEPROM_LEN);
//  memcpy(JoinEui, (void*)JOIN_EUI_EEPROM_ADDRESS, JOIN_EUI_EEPROM_LEN);
//  memcpy(AppKey, (void*)APP_KEY_EEPROM_ADDRESS, APP_KEY_EEPROM_LEN);
//  memcpy(NwkKey, (void*)NWK_KEY_EEPROM_ADDRESS, NWK_KEY_EEPROM_LEN);
//#endif //SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
//}


/**
  * @brief  Load Frame counter from STM32 internal EEPROM
  * @param  None
  * @retval None
  */
void LoadFrameCounter()
{
#if SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
  
  if(EepromFrameCounterValidation() != 0)
  {
    return;
  }
  
  memcpy(&fCntUp_global, (void*)FRAME_COUNTER_EEPROM_ADDRESS, FRAME_COUNTER_EEPROM_LEN);

#endif //SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
