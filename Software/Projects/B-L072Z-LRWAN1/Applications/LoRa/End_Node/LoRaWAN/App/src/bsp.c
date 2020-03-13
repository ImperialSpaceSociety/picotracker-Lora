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
  /* USER CODE BEGIN 5 */
	#if defined (SENSOR_ENABLED)
	MS5607_get_temp_pressure();
	#endif
  
	#if defined (GPS_ENABLED)
	get_location_fix();
	#endif
	

	
	
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
	
	 //#if defined (GPS_ENABLED)

	 //GPS SETUP
	 setup_GPS();

	 // GPS INITIAL BACKUP
	 Backup_GPS();
	//#endif

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
