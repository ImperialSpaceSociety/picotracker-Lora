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



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define STSOP_LATTITUDE ((float) 43.618622 )
#define STSOP_LONGITUDE ((float) 7.051415  )
#define MAX_GPS_POS ((int32_t) 8388607  ) // 2^23 - 1
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

	MS5607_get_temp_pressure();
	
	PRINTF("Temperature degrees C: "); 
	PRINTF("%lf", TEMPERATURE_Value); 
	PRINTF("\r\n"); 
	PRINTF("Pressure mBar: "); 
	PRINTF("%lf", PRESSURE_Value); 
	PRINTF("\r\n");
	
	
  sensor_data->humidity    = 34;
  sensor_data->temperature = TEMPERATURE_Value;
  sensor_data->pressure    = PRESSURE_Value;
  
  sensor_data->latitude  = (int32_t) ((STSOP_LATTITUDE  * MAX_GPS_POS) /90);
  sensor_data->longitude = (int32_t) ((STSOP_LONGITUDE  * MAX_GPS_POS )/180);
  /* USER CODE END 5 */
}

void  BSP_sensor_Init( void  )
{
  /* USER CODE BEGIN 6 */

#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)
  /* Initialize sensors */
//  BSP_HUMIDITY_Init( HTS221_H_0, &HUMIDITY_handle );
//  BSP_TEMPERATURE_Init( HTS221_T_0, &TEMPERATURE_handle );
//  BSP_PRESSURE_Init( PRESSURE_SENSORS_AUTO, &PRESSURE_handle );
//  
//  /* Enable sensors */
//  BSP_HUMIDITY_Sensor_Enable( HUMIDITY_handle );
//  BSP_TEMPERATURE_Sensor_Enable( TEMPERATURE_handle );
//  BSP_PRESSURE_Sensor_Enable( PRESSURE_handle );
	
	
		ms5607_Init();

#endif
    /* USER CODE END 6 */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
