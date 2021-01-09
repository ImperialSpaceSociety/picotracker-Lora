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
#include <stdlib.h>
#include "hw.h"
#include "bsp.h"
#include "ms5607.h"
#include "ublox.h"
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

#define MINUTES_IN_DAY  1440UL
#define MINUTES_AGO_TO_SELECT_FROM (MINUTES_IN_DAY * PLAYBACK_DAYS)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t current_EEPROM_index = 0;
uint16_t n_playback_positions_saved = 0;

/* Dummy values for testing */

time_pos_fix_t current_position =
{
	.minutes_since_epoch = 0x0007342E,  /*472110 minutes */
	.latitude = 0x17CA                  /*399121314 == 399121314*/,
	.longitude = 0xD312                 /*3541187191 == -753780105 */,
	.altitude = 0x00F2                  /*0x0000F221 >>2 */
};


sensor_t sensor_data;
playback_key_info_t *playback_key_info_ptr;


/* Private function prototypes -----------------------------------------------*/
void save_current_position_info_to_EEPROM(time_pos_fix_t *currrent_position);
void fill_positions_to_send_buffer( void );
uint32_t unix_time_to_minutes_since_epoch(uint32_t unix_time);
int mod(int a, int b);
void print_stored_coordinates( void );
time_pos_fix_t get_oldest_pos_time( void );
time_pos_fix_t retrieve_eeprom_time_pos(uint16_t time_pos_index);

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
	PRINTF("GPS time: "); 
	PRINTF("%ld", gps_info.unix_time	); 
	PRINTF("\r\n");
	PRINTF("Solar voltage no load: "); 
	PRINTF("%ld", no_load_solar_voltage	); 
	PRINTF("\r\n");
	PRINTF("Solar voltage with GPS load: "); 
	PRINTF("%ld", load_solar_voltage); 
	PRINTF("\r\n");
	PRINTF("Reset Count: "); 
	PRINTF("%ld", sensor_data.reset_count); 
	PRINTF("\r\n");
	PRINTF("Data received from ground: "); 
	PRINTF("%ld", sensor_data.data_received); 
	PRINTF("\r\n");
	PRINTF("================================================================\r\n");


	
	



	current_position.altitude  = (gps_info.GPSaltitude >> 8) & 0xffff;
	current_position.latitude  = (gps_info.GPS_UBX_latitude >> 16) & 0xffff;
	current_position.longitude = (gps_info.GPS_UBX_longitude >> 16) & 0xffff;
	current_position.minutes_since_epoch = unix_time_to_minutes_since_epoch(gps_info.unix_time)&0x00ffffff;
	
	sensor_data.temperature = (int8_t)TEMPERATURE_Value;
	sensor_data.pressure    = (uint16_t)PRESSURE_Value;
	sensor_data.no_load_solar_voltage = (uint8_t)(no_load_solar_voltage/100);
	sensor_data.load_solar_voltage = (uint8_t)(load_solar_voltage/100);
	sensor_data.sats = (uint8_t)gps_info.GPSsats;
	
	time_pos_fix_t oldest = get_oldest_pos_time();
	sensor_data.days_of_playback = (uint8_t)((current_position.minutes_since_epoch - oldest.minutes_since_epoch)/MINUTES_IN_DAY);


	/* fill up the buffer to send down */
	fill_positions_to_send_buffer();
	/* now save all this data to non volatile memory */
	
	time_pos_fix_t most_recent = retrieve_eeprom_time_pos(0);

	if (gps_info.latest_gps_status == GPS_SUCCESS)
	{
		/* After the time between saving(HOW_OFTEN_TO_SAVE_POS_TIM_TO_EEPROM) has elapsed, then
		 * increment the counter such that it can save to the next location
		 */
		if (current_position.minutes_since_epoch - most_recent.minutes_since_epoch  > HOW_OFTEN_TO_SAVE_POS_TIM_TO_EEPROM)
		{
			playback_key_info_ptr->n_positions_saved_since_boot += 1;
		}
		
		/* Save position to eeprom, overwriting the latest position with every fix. */
		save_current_position_info_to_EEPROM(&current_position);
		

	}
}


void manage_incoming_instruction(uint8_t *instructions)
{
	uint32_t recent_time_min = extractLong_from_buff(0,instructions);
	uint16_t recent_timepos_index =  get_time_pos_index_older_than(recent_time_min);
	
	PRINTF("Received instruction recent. time(min):%d timepos index: %d\n",recent_time_min,recent_timepos_index);
	
	uint32_t older_time_min = extractLong_from_buff(4,instructions);
	uint16_t older_timepos_index =  get_time_pos_index_older_than(older_time_min);
	
	PRINTF("Received instruction older. time(min):%d timepos index: %d\n",older_time_min,older_timepos_index);

	process_playback_instructions(recent_timepos_index, older_timepos_index);
	
}



/**
 * \brief Intialise all the sensors and playback
 * 
 * \param 
 * 
 * \return void
 */
void  BSP_sensor_Init( void  )
{
	/* record number of resets to EEPROM, and also to send down */
	EepromMcuReadBuffer(RESET_COUNTER_ADDR,(void*)&sensor_data.reset_count,RESET_COUNTER_LEN);
	sensor_data.reset_count+=1;
	EepromMcuWriteBuffer(RESET_COUNTER_ADDR,(void*)&sensor_data.reset_count,RESET_COUNTER_LEN);


	
	#if defined( VARIANT_1V1B )  || defined ( VARIANT_1V2B )
	/* enable power to the sensors */
	SENSOR_EN_GPIO_Init();
	
	#endif
	
	#if defined( VARIANT_1V2A) || defined( VARIANT_1V3A)
	/* enable power to the GPS with mosfet */
	GPS_EN_GPIO_Init();
	#endif 
	
	
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
	
	/* We want to send positions from the last n days, defined by PLAYBACK_DAYS. Therefore, we need to calculate how 
	 * many saved eeprom position/times we should select from. We take the most recent timepos, then calculate back n days
	 * then calculate the index in eeprom of this timepos index.
	 */
	time_pos_fix_t most_recent_timepos_record = retrieve_eeprom_time_pos(0);
	uint16_t earliest_time_to_send = most_recent_timepos_record.minutes_since_epoch - MINUTES_AGO_TO_SELECT_FROM;
	
	/* if there is not timepos index older than the calculated earliest time to send, then select from all the 
	 * n_playback_positions_saved
	 */
	uint16_t earliest_timepos_index;
	uint16_t older_index = get_time_pos_index_older_than(earliest_time_to_send);
	
	if (older_index == 0)
	{
		earliest_timepos_index = n_playback_positions_saved;
	}
	else
	{
		earliest_timepos_index = older_index;
	}
		
	/* Initialise playback */
	init_playback(&n_playback_positions_saved, &sensor_data, &current_position,&retrieve_eeprom_time_pos, earliest_timepos_index);
	
	playback_key_info_ptr = get_playback_key_info_ptr();

	/* print out stored time/pos data for debugging */
	print_stored_coordinates();


}

/**
 * \brief Print out all the stored coordinates
 * 
 * 
 * \return void
 */
void print_stored_coordinates()
{
	/* test stored positoins */
	PRINTF("Printing Stored coordinates:\n");
	for (uint16_t i = 0; i < n_playback_positions_saved; i++)
	{
		time_pos_fix_t temp = retrieve_eeprom_time_pos(i);
		PRINTF("index: %d, long: %d, lat: %d, alt: %d, ts: %d\n",i,temp.longitude, temp.latitude, temp.altitude, temp.minutes_since_epoch);
	}
}


/**
 * \brief get postime oldest datapoint
 * 
 * 
 * \return time_pos_fix_t
 */
time_pos_fix_t get_oldest_pos_time()
{
	/* test stored positoins */
	PRINTF("Getting oldest position:\n");
	
	/* The index starts from 0. If 1 position is saved, it will have an index of 0.
	 * Generalising, if there are n positions, the nth position index will be n-1.
	 * The problem is, if there are 0 poitions saved, the index calculated will be -1.
	 * This will break the retrieve_eeprom_time_pos() because it reads only positive numbers.
	 * So if thats the case, then force the index to be 0.
	 * TODO: make it return a null value when n_playback_positions_saved == 0
	 */
	uint16_t index = (n_playback_positions_saved == 0)? 0 : n_playback_positions_saved - 1;
	
	time_pos_fix_t temp = retrieve_eeprom_time_pos(index);
	
	PRINTF("oldest postime :: pos_time index: %d, long: %d, lat: %d, alt: %d, ts: %d\n",index,temp.longitude, temp.latitude, temp.altitude, temp.minutes_since_epoch);
	
	return temp;
}

/**
 * \brief look through eeprom to find the time/pos entry older than 
 * the given minute_from_epoch
 * 
 * 
 * \return index of time pos. If there is no time/pos older in eeprom, then return 0
 */
uint16_t get_time_pos_index_older_than(uint32_t minutes_from_epoch)
{
	uint16_t res_index = 0;
	for (uint16_t i = 0; i < n_playback_positions_saved; i++)
	{
		time_pos_fix_t temp = retrieve_eeprom_time_pos(i);
		if (temp.minutes_since_epoch < minutes_from_epoch)
		{
			return i;
		}
		
	}
	
	return res_index;
	
}

/**
  * @brief Save all the position data and time to EEPROM
  * @param none
  * @retval none
  */
void save_current_position_info_to_EEPROM(time_pos_fix_t *currrent_position)
{
	
	/* save Long, Lat, Altitude, minutes since epoch to EEPROM */
	
	uint16_t location_to_write = PLAYBACK_EEPROM_ADDR_START + current_EEPROM_index;
	EepromMcuWriteBuffer(location_to_write + 0,(void*)&current_position.altitude,ALTITUDE_BYTES_LEN);
	EepromMcuWriteBuffer(location_to_write + 2,(void*)&current_position.latitude,LATITUDE_BYTES_LEN);
	EepromMcuWriteBuffer(location_to_write + 4,(void*)&current_position.longitude,LONGITUDE_BYTES_LEN);
	EepromMcuWriteBuffer(location_to_write + 6,(void*)&current_position.minutes_since_epoch,MINUTES_SINCE_EPOCH_BYTES_LEN);

	
	/* Now update the index in EEPROM */
	current_EEPROM_index = mod(current_EEPROM_index + PLAYBACK_EEPROM_PACKET_SIZE, PLAYBACK_EEPROM_SIZE);
	n_playback_positions_saved= MIN(n_playback_positions_saved + 1,MAX_PLAYBACK_POSITIONS_SAVED_IN_EEPROM);
	
	EepromMcuWriteBuffer(CURRENT_PLAYBACK_INDEX_IN_EEPROM_ADDR,(void*)&current_EEPROM_index,sizeof(current_EEPROM_index));
	EepromMcuWriteBuffer(N_PLAYBACK_POSITIONS_SAVED_IN_EEPROM_ADDR,(void*)&n_playback_positions_saved,sizeof(current_EEPROM_index));

	
}


/**
 * \brief Read the eeprom for a position and time and a certain index.
 * 
 * \param index. index 0 is the most recent timepos stored in eeprom.
 * 
 * \return time_pos_fix_t position time fix
 */
time_pos_fix_t retrieve_eeprom_time_pos(uint16_t time_pos_index)
{
	
	time_pos_fix_t time_pos_fix;
	
	/* read Long, Lat, Altitude, minutes since epoch from EEPROM */
	uint16_t location_to_read = PLAYBACK_EEPROM_ADDR_START + mod(current_EEPROM_index - (time_pos_index + 1) * PLAYBACK_EEPROM_PACKET_SIZE,PLAYBACK_EEPROM_SIZE);	
	EepromMcuReadBuffer(location_to_read + 0,(void*)&time_pos_fix.altitude, ALTITUDE_BYTES_LEN);
	EepromMcuReadBuffer(location_to_read + 2,(void*)&time_pos_fix.latitude, LATITUDE_BYTES_LEN);
	EepromMcuReadBuffer(location_to_read + 4,(void*)&time_pos_fix.longitude, LONGITUDE_BYTES_LEN);
	EepromMcuReadBuffer(location_to_read + 6,(void*)&time_pos_fix.minutes_since_epoch, MINUTES_SINCE_EPOCH_BYTES_LEN);
	
	return time_pos_fix;
}

/*
 * \brief Mathematical mod operation. a mod b.
 * 
 * \param a
 * \param b
 * 
 * \return int
 */
int mod(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}



/**
  * @brief Calculate minutes since epoch. Based on GPS time.
	* Epoch is set to 1 Jan 2020 01:01:01H( unix time: 1577840461)
  * @param none
  * @retval none
  */
uint32_t unix_time_to_minutes_since_epoch(uint32_t unix_time)
{
	return (unix_time - 1577840461)/60;
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
