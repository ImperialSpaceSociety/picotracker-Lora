/*
 * ublox.c
 * modified from TT7's ublox code: https://github.com/TomasTT7/TT7F-Float-Tracker/blob/99133b762c971b24040d007fff3f1a348941d788/Software/ARM_UBLOX.c
 * Author: Tomy2 
 * Author: Medad Newman 23/12/19
 *
 */ 

#include <stdlib.h>
#include "ublox.h"
#include <stdio.h>
#include "stm32l0xx_hal.h"
#include "main.h"
#include <string.h>
#include "hw.h"


extern uint8_t	buffer_0xB5[1];
extern uint8_t	buffer_0x62[1];
extern uint8_t buffer_ubx_packet_wo_header[150]; // this packet does not include the 0xb5 0x62 header

static uint8_t flush_buffer[500];


/* 
 * GPS backup. 
 */
uint8_t Backup_GPS(){
  UBLOX_request_UBX(set_power_save_mode, sizeof(set_power_save_mode), 10, UBLOX_parse_ACK);				// switch GPS module to powersave mode. No response expected
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_RESET);    // force GPS backup mode by pulling GPS extint pin low		
	return 0;
}


/* 
 * GPS Wake up. 
 */
uint8_t Wakeup_GPS(){
	
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);    		  // pull GPS extint0 pin high to wake gps	
	HAL_Delay(1000);                                                          // wait for things to be setup
	UBLOX_send_message(set_continueous_mode, sizeof(set_continueous_mode));	  // switch GPS module to continueous mode
	//UBLOX_request_UBX(saveConfiguration, sizeof(saveConfiguration), 10, UBLOX_parse_ACK);		// save current configuration	
	return 0;

}


/* 
 * sets up gps by putting in airbourne mode, setting to use GPS satellites only, turning off NMEA
 * Needs TO BE REFACTORED TO TIME OUT OR EXIT IF NO MESSAGED IS ReCEIVED BACK!
 */
uint8_t setup_GPS(){
	
	// wake up gps in case it is in Lower Power mode
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);    		      // pull GPS extint0 pin high to wake gps
	UBLOX_send_message(resetReceiver, sizeof(resetReceiver));				              // reset GPS module. warm start
	HAL_Delay(1000);                                                              // Wait for things to be setup	

	UBLOX_request_UBX(setNMEAoff, sizeof(setNMEAoff), 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
	UBLOX_request_UBX(setGPSonly, sizeof(setGPSonly), 10, UBLOX_parse_ACK);				// !! must verify if this is a good config: turn off all constellations except gps: UBX-CFG-GNSS 
	UBLOX_request_UBX(setNAVmode, sizeof(setNAVmode), 10, UBLOX_parse_ACK);				// set to airbourne mode
	UBLOX_request_UBX(powersave_config, sizeof(powersave_config) , 10, UBLOX_parse_ACK);	  // Save powersave config to ram. can be activated later.
	return 0;
}


uint8_t get_location_fix(){
	
	// GET GPS FIX

	// wakeup gps
	HAL_GPIO_WritePin(GPS_INT_GPIO_Port, GPS_INT_Pin, GPIO_PIN_SET);    		  // pull GPS extint0 pin high to wake gps	
	HAL_Delay(500);
	UBLOX_send_message(set_continueous_mode, sizeof(set_continueous_mode));	  // switch GPS module to continueous mode	
	
	// Check if we are in airbourne mode
	GPSnavigation = 0;
	
	UBLOX_request_UBX(request0624, 8, 44, UBLOX_parse_0624);
	
	if(GPSnavigation != 6)														// verify Dynamic Model: airborne with <1g acceleration
	{
		UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);					// if not, set it
	}

	fixAttemptCount = 0;

	while(1)				// poll UBX-NAV-PVT until the module has fix
	{

		GPSfix_type = 0;
		GPSfix_OK = 0;
		GPSsats = 0;


		UBLOX_request_UBX(request0107, 8, 100, UBLOX_parse_0107);           // get fix info UBX-NAV-PVT

		if(GPSfix_OK == 1 && GPSfix_type == 3 && GPSsats >= SATS )           // check if we have a good fix
		{ 
			Backup_GPS();
			
			if (GPSaltitude<1000)
			{
			  // indicate that fix has been found
				for(uint8_t i = 0; i < 20; i++)
				{
					HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_SET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_RESET);
					HAL_Delay(50);
				}
		  }

			
			return 1;
		}       

		fixAttemptCount++;
		
		// Indicator led to indicate that still searching
		if (GPSaltitude<1000){
			HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_SET);
			HAL_Delay(100);
			HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_RESET);
		}

		PRINTF("%d GPS SATS in FIX",GPSsats);
		PRINTF("\r\n"); 



		/* If fix taking too long, reset and re-initialize GPS module. 
		 * It does a forced hardware reset and recovers from a warm start
		 * Reset only after 70 tries
		 */
		if(fixAttemptCount > FIX)														
		{
			UBLOX_send_message(resetReceiver, sizeof(resetReceiver));				// reset GPS module. warm start
			UBLOX_request_UBX(setNMEAoff, sizeof(setNMEAoff), 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
			UBLOX_request_UBX(setGPSonly, sizeof(setGPSonly), 10, UBLOX_parse_ACK);				// !! must verify if this is a good config: turn off all constellations except gps: UBX-CFG-GNSS 
			UBLOX_request_UBX(setNAVmode, sizeof(setNAVmode), 10, UBLOX_parse_ACK);				// set to airbourne mode
			UBLOX_request_UBX(powersave_config, sizeof(powersave_config) , 10, UBLOX_parse_ACK);	  // Save powersave config to ram. can be activated later.

			// configure gps module again
			GPSfix_type = 0;
			GPSfix_OK = 0;
			GPSsats = 0;
			
			Backup_GPS();
			return 0;

		}
		
		HAL_Delay(500);		
	}

}




/*
    Converts GPS coordinates in Degrees and Decimal Minutes (4928.08702) to Decimal Degrees (49.4681170).
    
        PARAMETER       INPUT
        lat_INT         4 digits max
        lat_DEC         5 digits fixed
        lon_INT         5 digits max
        lon_DEC         5 digits fixed
        latNS           1/0
        lonEW           1/0
    
    The result is saved in global variables APRSLatitude and APRSLongitude.
*/
void Coords_DEGtoDEC(uint32_t lat_INT, uint32_t lat_DEC, uint32_t lon_INT, uint32_t lon_DEC, uint8_t latNS, uint8_t lonEW)
{
    /*
        lat_INT     4928    degrees, minutes
        lat_DEC     08702   minutes decimal value
        lon_INT     01805   degrees, minutes
        lon_DEC     46513   minutes decimal value
        latNS       0/1     S/N
        lonEW       0/1     W/E
    */
    
    float lat = 0.0;
    float lon = 0.0;
    
    uint32_t deg = lat_INT / 100;                               // 49
    uint32_t min = lat_INT % 100;                               // 28
    min = (min * 100000) + lat_DEC;                             // 2808702
    float minf = min / 100000.0;                                // 28.08702
    minf = minf * 100 / 60;                                     // 46.8117
    min = minf * 100000.0;                                      // 4681170
    lat = (deg * 10000000) + min;                               // 494681170
    
    deg = lon_INT / 100;                                        // 18
    min = lon_INT % 100;                                        // 05
    min = (min * 100000) + lon_DEC;                             // 546513
    minf = min / 100000.0;                                      // 5.46513
    minf = minf * 100 / 60;                                     // 9.10855
    min = minf * 100000.0;                                      // 910855
    lon = (deg * 10000000) + min;                               // 180910855
    
    
    if(!latNS) lat = lat * -1.0;
    if(!lonEW) lon = lon * -1.0;
    
    lon_DEC = (labs(lon) % 10000000) / 100;                     // just in case I wanted to save this format to a global variable as well
    lon_INT = abs(lon / 10000000);                              // just in case I wanted to save this format to a global variable as well
    lat_DEC = (labs(lat) % 10000000) / 100;                     // just in case I wanted to save this format to a global variable as well
    lat_INT = abs(lat / 10000000);                              // just in case I wanted to save this format to a global variable as well
    
    GPS_UBX_latitude_Float = (float)lat / 10000000.0;           // save to a global variable
    GPS_UBX_longitude_Float = (float)lon / 10000000.0;          // save to a global variable
}


/*
    Verifies the checksum of received UBX messages.
*/
uint8_t UBLOX_verify_checksum(volatile uint8_t *buffer, uint8_t len)
{
    uint8_t CK_A_real = buffer[len-2];
    uint8_t CK_B_real = buffer[len-1];
    uint8_t CK_A_comp = 0;
    uint8_t CK_B_comp = 0;
    uint8_t ubloxCRC;

    for(uint8_t i = 2; i < len-2; i++)
    {
        CK_A_comp = CK_A_comp + buffer[i];
        CK_B_comp = CK_A_comp + CK_B_comp;
    }
    
    if(CK_A_real == CK_A_comp && CK_B_real == CK_B_comp) ubloxCRC = 1;
    else ubloxCRC = 0;

    return ubloxCRC;
}


/*
    Waits for the I2C1_RX_buffer[] to be filled with an expected number of bytes
    and then empties the buffer to a desired buffer for further processing.
*/
uint8_t UBLOX_receive_UBX(uint8_t *buffer, uint8_t len, uint32_t timeout)
{
		 /* Init tickstart for timeout management*/
		uint32_t tickstart_j = 0;
    tickstart_j = HAL_GetTick();


		/* set a time out for receiving a ubx message back from the GPS */
    while ((HAL_GetTick() - tickstart_j) < timeout)
		{
			/* listen for the first header char */
			HAL_I2C_Master_Receive(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1), buffer_0xB5, 1, 100);
			if (buffer_0xB5[0] == 0xb5){
				  /* now listen for the second header char */
					HAL_I2C_Master_Receive(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1), buffer_0x62, 1, 100);
					
				  if (buffer_0x62[0] == 0x62){
						
						/* now that the header has been received, parse the rest of message */
						HAL_I2C_Master_Receive(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1), buffer_ubx_packet_wo_header, 120, 100);
					
					  /* now fill GPS buffer with header+body of ubx message  */
						buffer[0] = 0xB5;
						buffer[1] = 0x62;
						for (uint8_t i=0; i<len-2; i++) {
								buffer[i+2]=buffer_ubx_packet_wo_header[i];
						}
					 
						return 1; // ubx message received and GPSbuffer filled with data

				}
			}
		}
		
		return 0; // no ubx message received
}




/*
    Transmits a desired UBX message across I2C1.
*/
uint8_t UBLOX_send_message(uint8_t *message, uint8_t len)
	
{
		i2c_status = HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1), message, len, 0xff);	
		
		if (i2c_status == HAL_OK)
		{
			return 1;
		}else
		{
			return 0;
		}	
}


/*
   Flush I2C buffer. Fill the flush buffer with number of bytes defined by len
*/
uint8_t UBLOX_flush_I2C_buffer( uint16_t len)
{
		HAL_I2C_Master_Receive(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1),flush_buffer , len, 100);
		
		if (i2c_status == HAL_OK)
		{
			return 1;
		}else
		{
			return 0;
		}	
}


/*
    Function polling desired GPS data. It first sends the set UBX request.
    Then waits for the data and calls the appropriate parsing function.
*/
uint8_t UBLOX_request_UBX(uint8_t *request, uint8_t len, uint8_t expectlen, uint8_t (*parse)(volatile uint8_t*))
{
		// Flush Ublox I2C buffer if it is unexpectedly filled with something else. Do not do anything with the data
    // TODO: maybe do something if there is an ubx message here. A GPS/MCU reset?
		UBLOX_flush_I2C_buffer(500);

		// Transmit the request
    HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1), request, len, 1000);
			
		memset(GPSbuffer, 0, sizeof(GPSbuffer)); // reset the buffer to all 0s. not sure if needed
		// Receive the request
		UBLOX_receive_UBX(GPSbuffer, expectlen, 5000);

		return  parse(GPSbuffer);          // parse the response to appropriate variables, 1 for successful parsing

}


/*
    UBX 01 02   POSITION
    
        GPS_UBX_longitude               494681170       +/-
        GPS_UBX_latitude                180910855       +/-
        GPS_UBX_longitude_Float         49.4681170      +/-
        GPS_UBX_latitude_Float          18.0910855      +/-
        GPSaltitude                     403             +/-
        
    Checks the header and the checksum.
*/
uint8_t UBLOX_parse_0102(volatile uint8_t *buffer)
{
    GPS_UBX_error_bitfield |= (1 << 2);
    
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x02)
    {
        if(UBLOX_verify_checksum(buffer, 36))
        {
            GPS_UBX_longitude = (int32_t)buffer[10] | (int32_t)buffer[11] << 8 | (int32_t)buffer[12] << 16 | (int32_t)buffer[13] << 24;
            GPS_UBX_longitude_Float = (float)GPS_UBX_longitude / 10000000.0;
            
            GPS_UBX_latitude = (int32_t)buffer[14] | (int32_t)buffer[15] << 8 | (int32_t)buffer[16] << 16 | (int32_t)buffer[17] << 24;
            GPS_UBX_latitude_Float = (float)GPS_UBX_latitude / 10000000.0;
            
            GPSaltitude = (int32_t)buffer[22] | (int32_t)buffer[23] << 8 | (int32_t)buffer[24] << 16 | (int32_t)buffer[25] << 24;
            GPSaltitude /= 1000;
            
            GPS_UBX_error_bitfield &= ~(1 << 2);
        }else{
            GPS_UBX_checksum_error++;
        }
    }else{
        GPS_UBX_buffer_error++;
    }
   
	  return 0;
}


/*
    UBX 01 21   TIME
        
        GPShour             9
        GPSminute           14
        GPSsecond           55
        
    Checks the header and the checksum.
*/
uint8_t UBLOX_parse_0121(volatile uint8_t *buffer)
{
    GPS_UBX_error_bitfield |= (1 << 3);
    
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x21)
    {
        if(UBLOX_verify_checksum(buffer, 28))
        {
            GPShour = buffer[22];
            GPSminute = buffer[23];
            GPSsecond = buffer[24];
            
            GPS_UBX_error_bitfield &= ~(1 << 3);
        }else{
            GPS_UBX_checksum_error++;
        }
    }else{
        GPS_UBX_buffer_error++;
    }
   
	 return 0;
}


/*
    UBX 01 06   SATS & FIX
        
        GPSsats             7
        GPSfix_type              0x00        No Fix
                            0x01        Dead Reckoning only
                            0x02        2D-Fix
                            0x03        3D-Fix
                            0x04        GPS + Dead Reckoning combined
                            0x05        Time only fix
        
    Checks the header and the checksum.
*/
uint8_t UBLOX_parse_0106(volatile uint8_t *buffer)
{
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x06)
    {
        if(UBLOX_verify_checksum(buffer, 60))
        {
            GPSfix_type = buffer[16];
            GPSsats = buffer[53];
        }else{
            GPS_UBX_checksum_error++;
            
            GPSfix_type = 0;
            GPSsats = 0;
        }
    }else{
        GPS_UBX_buffer_error++;
        
        GPSfix_type = 0;
        GPSsats = 0;
    }
		return 0;
}


/*
    UBX 06 24   NAVIGATION MODE
    
        GPSnavigation       0   portable
                            2   stationary
                            3   pedestrian
                            4   automotive
                            5   sea
                            6   airborne with <1g acceleration
                            7   airborne with <2g acceleration
                            8   airborne with <4g acceleration
                            9   wrist worn watch
    
    Checks the header and the checksum.
*/
uint8_t UBLOX_parse_0624(volatile uint8_t *buffer)
{
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x06 && buffer[3] == 0x24)
    {
        if(UBLOX_verify_checksum(buffer, 44))
        {
            GPSnavigation = buffer[8];
        }else{
            GPS_UBX_checksum_error++;
            
            GPSnavigation = 0;
        }
    }else{
        GPS_UBX_buffer_error++;
        
        GPSnavigation = 0;
    }
	  return 0;
}


/*
    UBX 06 11   POWER SAVE MODE
        
        GPSpowermode        0   Continuous Mode
                            1   Power Save Mode
                            4   Continuous Mode
    
    Checks the header and the checksum.
*/
uint8_t UBLOX_parse_0611(volatile uint8_t *buffer)
{
    GPS_UBX_error_bitfield |= (1 << 4);
    
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x06 && buffer[3] == 0x11)
    {
        if(UBLOX_verify_checksum(buffer, 10))
        {
            GPSpowermode = buffer[7];
            
            GPS_UBX_error_bitfield &= ~(1 << 4);
        }else{
            GPS_UBX_checksum_error++;
            
            GPSpowermode = 0;
        }
    }else{
        GPS_UBX_buffer_error++;
        
        GPSpowermode = 0;
    }
		
		return 0;

}


/*
    UBX UBX-NAV-PVT 0x01 0x07   EVERYTHING
    
        GPSyear                     2016
        GPSmonth                    10
        GPSday                      18
        GPShour                     9
        GPSminute                   14
        GPSsecond                   55
        GPSfix_type                      1
																		0   no fix
																		1   dead reckoning only
																		2   2D-fix
																		3   3D-fix
																		4   GNSS + dead reckoning combined
																		5   time only fix
        GPSpowersavemodestate       0   PSM is not active
                                    1   Enabled (an intermediate state before Acquisition state)
                                    2   Acquisition
                                    3   Tracking
                                    4   Power Optimized Tracking
                                    5   Inactive
        GPSsats                     7
        GPS_UBX_latitude            494681170       +/-
        GPS_UBX_longitude           180910855       +/-
        GPS_UBX_longitude_Float     49.4681170      +/-
        GPS_UBX_latitude_Float      18.0910855      +/-
        GPSaltitude                 403             +/-
        GPSgroundspeed              10000           +/-
        GPSheading                  2545641         +/-
    
    Checks the header and the checksum.
    UBLOX 7 message is shorter then UBLOX 8 message. It must be reflected in the checksum verification.
		Comment Medad 27/12/19: looks like the pvt message is parsed according to the m8 spec. But not sure why it verifies checksum
		with 2 lengths(92 and 100 bytes). maybe flexible to accomodate the m7 spec.
*/
uint8_t UBLOX_parse_0107(volatile uint8_t *buffer)
{
    GPS_UBX_error_bitfield |= (1 << 2);
    
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x07)
    {
        if(UBLOX_verify_checksum(buffer, 92) || UBLOX_verify_checksum(buffer, 100))
        {
											
            // YEAR, MONTH, DAY
            GPSyear = (uint16_t)buffer[10] | (uint16_t)buffer[11] << 8;
            GPSmonth = buffer[12];
            GPSday = buffer[13];
            
            // HOUR, MINUTE, SECONDS
            GPShour = buffer[14];
            GPSminute = buffer[15];
            GPSsecond = buffer[16];
            
            // FIX
            GPSfix_type = buffer[26];             // GNSSfix Type
					
					  GPSfix_OK = buffer[27] & 0x01; // Fix status flags: gnssFixOK
            GPSvalidity = buffer[17];        // Validity flags
            
            // POWER SAVE MODE STATE
            GPSpowersavemodestate = (buffer[27] >> 2) & 0x07; // Fix status flags: PSM state
            
            // SATS
            GPSsats = buffer[29];
            
            // LONGITUDE, LATITUDE, ALTITUDE ABOVE MEAN SEA LEVEL
            GPS_UBX_longitude = (int32_t)buffer[30] | (int32_t)buffer[31] << 8 | (int32_t)buffer[32] << 16 | (int32_t)buffer[33] << 24;
            GPS_UBX_longitude_Float = (float)GPS_UBX_longitude / 10000000.0;
            
            GPS_UBX_latitude = (int32_t)buffer[34] | (int32_t)buffer[35] << 8 | (int32_t)buffer[36] << 16 | (int32_t)buffer[37] << 24;
            GPS_UBX_latitude_Float = (float)GPS_UBX_latitude / 10000000.0;
            
            GPSaltitude = (int32_t)buffer[38] | (int32_t)buffer[39] << 8 | (int32_t)buffer[40] << 16 | (int32_t)buffer[41] << 24;
            GPSaltitude /= 1000;
            
            // GROUND SPEED, HEADING
            GPSgroundspeed = (int32_t)buffer[66] | (int32_t)buffer[67] << 8 | (int32_t)buffer[68] << 16 | (int32_t)buffer[69] << 24;
            GPSheading = (int32_t)buffer[70] | (int32_t)buffer[71] << 8 | (int32_t)buffer[72] << 16 | (int32_t)buffer[73] << 24;;
            
            GPS_UBX_error_bitfield &= ~(1 << 2);
        }else{
            GPS_UBX_checksum_error++;
            
            GPSfix_type = 0;
            GPSsats = 0;
        }
    }else{
        GPS_UBX_buffer_error++;
        
        GPSfix_type = 0;
        GPSsats = 0;
    }
		
		return 0;
}


/*
    UBX 05 01   ACK
    
    Checks the header and the checksum. returns 1 when an ack is received, returns 0 when a nak is received.
*/



uint8_t UBLOX_parse_ACK(volatile uint8_t *buffer)
{
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x05)
    {
        if(buffer[3] != 0x01)
        {
            GPS_UBX_ack_error++;
						return 0;
        }
				else
				{
					return 1;
				}
    }else{
        GPS_UBX_buffer_error++;
				return 0;
    }
		
}


/*
    Dummy parse function.
*/
uint8_t UBLOX_parse_empty(void)
{
   return 0;
}



/*
    Function to prepare the module and enter the chosen POWER SAVING mode.
    First it turns off periodic messages, then it turns of GLONASS (required for POWER SAVE mode), sets up the desired mode
    and a wake up period and switches to the POWER SAVE mode.
*/
void UBLOX_powersave_mode_init(uint8_t * mode)
{
    GPS_UBX_ack_error = 0;
    UBLOX_request_UBX(setNMEAoff, 28, 10, UBLOX_parse_ACK);                             // turn off the periodic output
    UBLOX_request_UBX(setGPSonly, 28, 10, UBLOX_parse_ACK);                             // turn off GLONASS (needs to be done for POWERSAVE mode)
    UBLOX_request_UBX(mode, 52, 10, UBLOX_parse_ACK);                                   // set up the desired UBX-CFG-PM2 (0x06 0x3B) settings
    UBLOX_request_UBX(setPowerSaveMode, 10, 10, UBLOX_parse_ACK);                       // switch to POWERSAVE mode
}

