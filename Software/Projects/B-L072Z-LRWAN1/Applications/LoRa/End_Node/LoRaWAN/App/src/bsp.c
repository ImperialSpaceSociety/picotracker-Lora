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
#include "playback.h"








/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BATTERY_ADC_CHANNEL             ADC_CHANNEL_5
/*!
 * Generic definition
 */
#ifndef SUCCESS
#define SUCCESS                                     1
#endif

#ifndef FAIL
#define FAIL                                        0
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t current_EEPROM_index = 0;
uint16_t n_playback_positions_saved = 0;
time_pos_fix_t subset_positions[MAX_SUBSET_SIZE];
time_pos_fix_t current_position;
sensor_t sensor_data;
time_pos_fix_t read_eeprom_pos_time(uint16_t index);
void fill_positions_to_send_buffer( void );


/* Private function prototypes -----------------------------------------------*/
void save_current_position_info_to_EEPROM(void);

/* Exported functions ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


void BSP_sensor_Read(void)
{
	TVL1(PRINTF("READING SENSOR AND GPS\n\r");)

  /* USER CODE BEGIN 5 */
	#if SENSOR_ENABLED
	MS5607_get_temp_pressure();
	#endif
  
	#if GPS_ENABLED
	get_location_fix(GPS_LOCATION_FIX_TIMEOUT);
	#endif
	
	uint16_t no_load_solar_voltage = BSP_GetSolarLevel16();
	uint16_t load_solar_voltage = get_load_solar_voltage();


	
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
	PRINTF("%lf ", gps_info.GPS_UBX_longitude_Float); 
	PRINTF("Latitude: "); 
	PRINTF("%lf ", gps_info.GPS_UBX_latitude_Float); 
	PRINTF("altitude: "); 
	PRINTF("%ld", gps_info.GPSaltitude/1000	); 
	PRINTF("\r\n");
	PRINTF("Solar voltage no load: "); 
	PRINTF("%ld", no_load_solar_voltage	); 
	PRINTF("\r\n");
	PRINTF("Solar voltage with GPS load: "); 
	PRINTF("%ld", load_solar_voltage); 
	PRINTF("\r\n");
	PRINTF("================================================================\r\n");


	
	
  sensor_data->humidity    = 34; // hard coded dummy value
  sensor_data->temperature = TEMPERATURE_Value;
  sensor_data->pressure    = PRESSURE_Value;
	sensor_data->altitudeGps = gps_info.GPSaltitude/1000;
	sensor_data->latitude    = gps_info.GPS_UBX_latitude_Float;
	sensor_data->longitude   = gps_info.GPS_UBX_longitude_Float;
	sensor_data->no_load_solar_voltage = no_load_solar_voltage;
	sensor_data->load_solar_voltage = load_solar_voltage;

	/* fill up the buffer to send down */
	fill_positions_to_send_buffer();
	/* now save all this data to non volatile memory */
	save_current_position_info_to_EEPROM();
	
	
}


void fill_positions_to_send_buffer( void )
{
	
	playback_key_info_t current_playback_key_info = *get_playback_key_info();
	

	for (int i = 0; i < current_playback_key_info.n_positions_to_send; i++)
	{
		/* if the eeprom is not yet full, then only select the ones that are in there */
		int upper_val = MIN(current_playback_key_info.n_positions_to_select_from,
			                  current_playback_key_info.n_positions_in_eeprom);
		
		int lower_val = current_playback_key_info.n_positions_offset;
		
		
		int rand_time_pos_index = randr(lower_val, upper_val);
		
		time_pos_fix_t random_time_pos = read_eeprom_pos_time(rand_time_pos_index);
		
		
		subset_positions[i].altitude = random_time_pos.altitude;
		subset_positions[i].latitude = random_time_pos.latitude;
		subset_positions[i].longitude = random_time_pos.longitude;
		subset_positions[i].minutes_since_epoch = random_time_pos.minutes_since_epoch;
	}
}


time_pos_fix_t read_eeprom_pos_time(uint16_t index)
{
	
	time_pos_fix_t time_pos_fix;
	
	/* read Long, Lat, Altitude, minutes since epoch from EEPROM */
	uint16_t eeprom_location = current_EEPROM_index - ((index + 1) * PLAYBACK_EEPROM_PACKET_SIZE);
		
	EepromMcuWriteBuffer(eeprom_location + 0,(void*)&time_pos_fix.altitude,2); // todo: don't use numbers here. use #define
	EepromMcuWriteBuffer(eeprom_location + 2,(void*)&time_pos_fix.latitude,2);
	EepromMcuWriteBuffer(eeprom_location + 4,(void*)&time_pos_fix.longitude,2);
	EepromMcuWriteBuffer(eeprom_location + 6,(void*)&time_pos_fix.minutes_since_epoch,3); // todo: verify if works
	
	return time_pos_fix;
}

void  BSP_sensor_Init( void  )
{
	PRINTF("SELFTEST: Initialisng ms5607\n\r");
	#if SENSOR_ENABLED
  /* Initialize sensors */	
		ms5607_Init();
	#endif
	
	 #if GPS_ENABLED
	 PRINTF("SELFTEST: Initialising GPS\n\r");

	 //GPS SETUP
	 setup_GPS();
	#endif
	
	EepromMcuReadBuffer(CURRENT_PLAYBACK_INDEX_IN_EEPROM_ADDR,(void*)&current_EEPROM_index,sizeof(current_EEPROM_index));
	EepromMcuReadBuffer(N_PLAYBACK_POSITIONS_SAVED_IN_EEPROM_ADDR,(void*)&n_playback_positions_saved,sizeof(current_EEPROM_index));
	init_playback(n_playback_positions_saved, subset_positions, &sensor_data, &current_position);

}



/**
  * @brief Save all the position data and time to EEPROM
  * @param none
  * @retval none
  */
void save_current_position_info_to_EEPROM( void )
{
	
	/* save Long, Lat, Altitude, minutes since epoch to EEPROM */
	uint16_t truncated_altitude = (uint16_t)(gps_info.GPSaltitude >> 2) & 0xffffUL;
	uint16_t truncated_latitude = (uint16_t)(gps_info.GPS_UBX_latitude >> 4) & 0xffffUL;
	uint16_t truncated_longitude = (uint16_t)(gps_info.GPS_UBX_longitude >> 4) & 0xffffUL;
	uint32_t truncated_time_since_epoch = (uint32_t)(gps_info.minutes_since_epoch) & 0xffffffUL;

	
	EepromMcuWriteBuffer(current_EEPROM_index + 0,(void*)&truncated_altitude,2); // todo: don't use numbers here. use #define
	EepromMcuWriteBuffer(current_EEPROM_index + 2,(void*)&truncated_latitude,2);
	EepromMcuWriteBuffer(current_EEPROM_index + 4,(void*)&truncated_longitude,2);
	EepromMcuWriteBuffer(current_EEPROM_index + 6,(void*)&truncated_time_since_epoch,3); // todo: verify if works

	
	/* Now update the index in EEPROM */
	current_EEPROM_index+=PLAYBACK_EEPROM_PACKET_SIZE;
	n_playback_positions_saved+=1U;
	
	EepromMcuWriteBuffer(CURRENT_PLAYBACK_INDEX_IN_EEPROM_ADDR,(void*)&current_EEPROM_index,sizeof(current_EEPROM_index));
	EepromMcuWriteBuffer(N_PLAYBACK_POSITIONS_SAVED_IN_EEPROM_ADDR,(void*)&n_playback_positions_saved,sizeof(current_EEPROM_index)); // TODO: max it out at MAX_PLAYBACK_POSITIONS_SAVED_IN_EEPROM

	
}

/**
  * @brief It measures the solar voltage by returning the value in mV
  * @param none
  * @retval uint16_t The solar voltage value in mV
  */
uint16_t BSP_GetSolarLevel16( void )
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



uint8_t EepromMcuWriteBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    uint8_t status = FAIL;

    assert_param( ( DATA_EEPROM_BASE + addr ) >= DATA_EEPROM_BASE );
    assert_param( buffer != NULL );
    assert_param( size < ( DATA_EEPROM_BANK2_END - DATA_EEPROM_BASE ) );

    if( HAL_FLASHEx_DATAEEPROM_Unlock( ) == HAL_OK )
    {
        for( uint16_t i = 0; i < size; i++ )
        {
            if( HAL_FLASHEx_DATAEEPROM_Program( FLASH_TYPEPROGRAMDATA_BYTE,
                                                ( DATA_EEPROM_BASE + addr + i ),
                                                  buffer[i] ) != HAL_OK )
            {
                // Failed to write EEPROM
                break;
            }
        }
        status = SUCCESS;
    }

    HAL_FLASHEx_DATAEEPROM_Lock( );
    return status;
}

uint8_t EepromMcuReadBuffer( uint16_t addr, uint8_t *buffer, uint16_t size )
{
    assert_param( ( DATA_EEPROM_BASE + addr ) >= DATA_EEPROM_BASE );
    assert_param( buffer != NULL );
    assert_param( size < ( DATA_EEPROM_BANK2_END - DATA_EEPROM_BASE ) );

    memcpy1( buffer, ( uint8_t* )( DATA_EEPROM_BASE + addr ), size );
    return SUCCESS;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
