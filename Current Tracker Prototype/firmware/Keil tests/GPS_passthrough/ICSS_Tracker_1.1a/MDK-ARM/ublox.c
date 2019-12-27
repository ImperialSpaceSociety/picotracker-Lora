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


extern I2C_HandleTypeDef hi2c1;
extern uint8_t	i2c_buffer[2];
extern HAL_StatusTypeDef i2c_status;

volatile uint8_t I2C1_RX_buffer[I2C1_BUFFER_SIZE];
volatile uint32_t I2C1_buffer_pointer;
volatile uint32_t UART1_temp;


volatile static uint8_t ack_error_counter = 0;
volatile static uint8_t buffer_error_counter = 0;
volatile static uint8_t receive_failure_counter = 0;


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
uint8_t UBLOX_receive_UBX(uint8_t *buffer, uint8_t len)
{

		i2c_status = HAL_I2C_Master_Receive(&hi2c1, (uint16_t)(GPS_I2C_ADDRESS << 1),  buffer, len, 0xFF);
		if (i2c_status == HAL_OK)
		{
			return 1;
		}else
		{
			return 0;
		}
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
    Function polling desired GPS data. It first sends the set UBX request.
    Then waits for the data and calls the appropriate parsing function.
*/
uint8_t UBLOX_request_UBX(uint8_t *request, uint8_t len, uint8_t expectlen, uint8_t (*parse)(volatile uint8_t*))
{
    i2c_status = HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1), request, len, 300);
		i2c_status = HAL_I2C_Master_Receive(&hi2c1, (uint16_t)(GPS_I2C_ADDRESS << 1), GPSbuffer, expectlen, 300); // copy the response from I2C1_RX_buffer to GPSbuffe
		
		if (i2c_status != HAL_OK)
		{
			receive_failure_counter++;
			return 0;
		}
	
    uint8_t success  = parse(GPSbuffer);          // parse the response to appropriate variables
    return success;
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
void UBLOX_parse_0102(volatile uint8_t *buffer)
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
}


/*
    UBX 01 21   TIME
        
        GPShour             9
        GPSminute           14
        GPSsecond           55
        
    Checks the header and the checksum.
*/
void UBLOX_parse_0121(volatile uint8_t *buffer)
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
}


/*
    UBX 01 06   SATS & FIX
        
        GPSsats             7
        GPSfix              0x00        No Fix
                            0x01        Dead Reckoning only
                            0x02        2D-Fix
                            0x03        3D-Fix
                            0x04        GPS + Dead Reckoning combined
                            0x05        Time only fix
        
    Checks the header and the checksum.
*/
void UBLOX_parse_0106(volatile uint8_t *buffer)
{
    if(buffer[0] == 0xB5 && buffer[1] == 0x62 && buffer[2] == 0x01 && buffer[3] == 0x06)
    {
        if(UBLOX_verify_checksum(buffer, 60))
        {
            GPSfix = buffer[16];
            GPSsats = buffer[53];
        }else{
            GPS_UBX_checksum_error++;
            
            GPSfix = 0;
            GPSsats = 0;
        }
    }else{
        GPS_UBX_buffer_error++;
        
        GPSfix = 0;
        GPSsats = 0;
    }
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
void UBLOX_parse_0624(volatile uint8_t *buffer)
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
}


/*
    UBX 06 11   POWER SAVE MODE
        
        GPSpowermode        0   Continuous Mode
                            1   Power Save Mode
                            4   Continuous Mode
    
    Checks the header and the checksum.
*/
void UBLOX_parse_0611(volatile uint8_t *buffer)
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
}


/*
    UBX UBX-NAV-PVT 0x01 0x07   EVERYTHING
    
        GPSyear                     2016
        GPSmonth                    10
        GPSday                      18
        GPShour                     9
        GPSminute                   14
        GPSsecond                   55
        GPSfix                      3
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
*/
void UBLOX_parse_0107(volatile uint8_t *buffer)
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
            GPSfix = buffer[26];
            GPSfix_0107 = buffer[27] & 0x01;
            GPSvalidity = buffer[17];
            
            // POWER SAVE MODE STATE
            GPSpowersavemodestate = (buffer[27] >> 2) & 0x07;
            
            // SATS
            GPSsats = buffer[29];
            
            // LONGITUDE, LATITUDE, ALTITUDE ABOVE MEAN SEA LEVEL
            GPS_UBX_longitude = (int32_t)buffer[30] | (int32_t)buffer[31] << 8 | (int32_t)buffer[32] << 16 | (int32_t)buffer[33] << 24;
            GPS_UBX_longitude_Float = (float)GPS_UBX_longitude / 10000000.0;
            
            GPS_UBX_latitude = (int32_t)buffer[34] | (int32_t)buffer[35] << 8 | (int32_t)buffer[36] << 16 | (int32_t)buffer[37] << 24;
            GPS_UBX_latitude_Float = (float)GPS_UBX_latitude / 10000000.0;
            
            GPSaltitude = (int32_t)buffer[42] | (int32_t)buffer[43] << 8 | (int32_t)buffer[44] << 16 | (int32_t)buffer[45] << 24;
            GPSaltitude /= 1000;
            
            // GROUND SPEED, HEADING
            GPSgroundspeed = (int32_t)buffer[66] | (int32_t)buffer[67] << 8 | (int32_t)buffer[68] << 16 | (int32_t)buffer[69] << 24;
            GPSheading = (int32_t)buffer[70] | (int32_t)buffer[71] << 8 | (int32_t)buffer[72] << 16 | (int32_t)buffer[73] << 24;;
            
            GPS_UBX_error_bitfield &= ~(1 << 2);
        }else{
            GPS_UBX_checksum_error++;
            
            GPSfix = 0;
            GPSsats = 0;
        }
    }else{
        GPS_UBX_buffer_error++;
        
        GPSfix = 0;
        GPSsats = 0;
    }
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
					  ack_error_counter++;
						return 0;
        }
				else
				{
					return 1;
				}
    }else{
        GPS_UBX_buffer_error++;
				buffer_error_counter++;
				return 0;
    }
}


/*
    Dummy parse function.
*/
void UBLOX_parse_empty(void)
{
    
}


/*
    Processes and parses an NMEA GGA message located in the input buffer.
    Accepts both GPGGA and GNGGA messages.
        
        GPShour                     15
        GPSminute                   30
        GPSsecond                   43
        GPS_NMEA_latitude_int       4928
        GPS_NMEA_latitude_dec       00456
        GPS_NMEA_longitude_int      01815
        GPS_NMEA_longitude_dec      58561
        GPS_NMEA_NS                 1/0
        GPS_NMEA_EW                 1/0
        GPSfix                      3
        GPSsats                     11
        GPSaltitude                 403
        
        GPS_NMEA_checksum_toverify
        GPS_NMEA_checksum_calculated
        
    Checks the header, saves the checksum and calculates a control checksum.
*/
void UBLOX_process_GGA(uint8_t *buffer)
{
    if(buffer[1] == 'G' && (buffer[2] == 'N' || buffer[2] == 'P') && buffer[3] == 'G' && buffer[4] == 'G' && buffer[5] == 'A')
    {
        uint8_t i, j, IntegerPart;
        uint8_t GPSaltitudeNeg = 0;
        
        GPShour = 0;
        GPSminute = 0;
        GPSsecond = 0;
        GPS_NMEA_latitude_int = 0;
        GPS_NMEA_latitude_dec = 0;
        GPS_NMEA_longitude_int = 0;
        GPS_NMEA_longitude_dec = 0;
        GPS_NMEA_NS = 1;
        GPS_NMEA_EW = 1;
        GPSfix = 0;
        GPSsats = 0;
        GPSaltitude = 0;
        GPS_NMEA_checksum_calculated = 0;
        GPS_NMEA_checksum_toverify = 0;
        IntegerPart = 1;
        
        i = 1;
        while(buffer[i] != '*')
        {
            GPS_NMEA_checksum_calculated ^= buffer[i];
            i++;
        }
        
        for(i = 6, j = 0; i < GPSBUFFER_SIZE && (j < 15); i++)
        {
            if(buffer[i] == ',')
            {
                j++;
                IntegerPart = 1;
            }else{
                switch(j)
                {
                    case 1:                                                             // TIME
                        if((buffer[i] >= '0') && (buffer[i] <= '9'))
                        {
                            if(i == 7 || i == 8)
                            {
                                GPShour = GPShour * 10;
                                GPShour += (buffer[i] - '0');
                            }
                            if(i == 9 || i == 10)
                            {
                                GPSminute = GPSminute * 10;
                                GPSminute += (buffer[i] - '0');
                            }
                            if(i == 11 || i == 12)
                            {
                                GPSsecond = GPSsecond * 10;
                                GPSsecond += (buffer[i] - '0');
                            }
                        }
                        break;
                    
                    case 2:                                                             // LATITUDE
                        if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
                        {
                            GPS_NMEA_latitude_int = GPS_NMEA_latitude_int * 10;
                            GPS_NMEA_latitude_int += (uint16_t)(buffer[i] - '0');
                        }
                        if(buffer[i] == '.') IntegerPart = 0;
                        if((buffer[i] >= '0') && (buffer[i] <= '9') && !IntegerPart)
                        {
                            GPS_NMEA_latitude_dec = GPS_NMEA_latitude_dec * 10;
                            GPS_NMEA_latitude_dec += (uint32_t)(buffer[i] - '0');
                        }
                        break;
                    
                    case 3:                                                             // NORTH/SOUTH
                        if(buffer[i] == 'N')
                        {
                            GPS_NMEA_NS = 1;
                        }
                        else if(buffer[i] == 'S')
                        {
                            GPS_NMEA_NS = 0;
                        }
                        break;
                    
                    case 4:                                                             // LONGITUDE
                        if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
                        {
                            GPS_NMEA_longitude_int = GPS_NMEA_longitude_int * 10;
                            GPS_NMEA_longitude_int += (uint16_t)(buffer[i] - '0');
                        }
                        if(buffer[i] == '.') IntegerPart = 0;
                        if((buffer[i] >= '0') && (buffer[i] <= '9') && !IntegerPart)
                        {
                            GPS_NMEA_longitude_dec = GPS_NMEA_longitude_dec * 10;
                            GPS_NMEA_longitude_dec += (uint32_t)(buffer[i] - '0');
                        }
                        break;
                    
                    case 5:                                                             // EAST/WEST
                        if(buffer[i] == 'E')
                        {
                            GPS_NMEA_EW = 1;
                        }
                        else if(buffer[i] == 'W')
                        {
                            GPS_NMEA_EW = 0;
                        }
                        break;
                    
                    case 6:                                                             // FIX
                        GPSfix = buffer[i] - '0';
                        break;
                    
                    case 7:                                                             // SATELLITES
                        if((buffer[i] >= '0') && (buffer[i] <= '9'))
                        {
                            GPSsats = GPSsats * 10;
                            GPSsats += (uint8_t)(buffer[i] - '0');
                        }
                        break;
                    
                    case 9:                                                             // ALTITUDE
                        if(buffer[i] == '-') GPSaltitudeNeg = 1;
                        if((buffer[i] >= '0') && (buffer[i] <= '9') && IntegerPart)
                        {
                            GPSaltitude = GPSaltitude * 10;
                            GPSaltitude += (int32_t)(buffer[i] - '0');
                        }
                        if(buffer[i] == '.') IntegerPart = 0;
                        break;
                    
                    case 14:                                                            // CHECKSUM (XOR of $ ... * bytes)
                        if(IntegerPart == 3)
                        {
                            if((buffer[i] >= '0') && (buffer[i] <= '9')) GPS_NMEA_checksum_toverify += (buffer[i] - '0');
                            else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPS_NMEA_checksum_toverify += (buffer[i] - '7');
                            IntegerPart++;
                        }
                        if(IntegerPart == 2)
                        {
                            if((buffer[i] >= '0') && (buffer[i] <= '9')) GPS_NMEA_checksum_toverify = ((buffer[i] - '0') << 4);
                            else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPS_NMEA_checksum_toverify = ((buffer[i] - '7') << 4);
                            IntegerPart++;
                        }
                        if(buffer[i] == '*') IntegerPart = 2;
                        break;
                    
                    default:
                        break;
                }
            }
        }
        
        if(GPSaltitudeNeg) GPSaltitude *= -1;                                           // adjust the altitude value if negative
        
        if(GPS_NMEA_checksum_calculated != GPS_NMEA_checksum_toverify)
                                             GPS_NMEA_error_bitfield |= (1 << 2);       // GGA checksum error
        
    }else{
        GPS_NMEA_error_bitfield |= (1 << 1);                                            // GGA buffer error
    }
}


/*
    Processes and parses an NMEA ZDA message located in the input buffer.
    Accepts both GPZDA and GNZDA messages.
    
        GPShour                     15
        GPSminute                   30
        GPSsecond                   43
        GPSday                      18
        GPSmonth                    10
        GPSyear                     2016
        
        GPS_NMEA_checksum_toverify
        GPS_NMEA_checksum_calculated
        
    Checks the header, saves the checksum and calculates a control checksum.
*/
void UBLOX_process_ZDA(uint8_t *buffer)
{
    if(buffer[1] == 'G' && (buffer[2] == 'N' || buffer[2] == 'P') && buffer[3] == 'Z' && buffer[4] == 'D' && buffer[5] == 'A')
    {
        uint8_t i, j, IntegerPart;
        
        GPShour = 0;
        GPSminute = 0;
        GPSsecond = 0;
        GPSday = 0;
        GPSmonth = 0;
        GPSyear = 0;
        GPS_NMEA_checksum_calculated = 0;
        GPS_NMEA_checksum_toverify = 0;
        IntegerPart = 1;
        
        i = 1;
        while(buffer[i] != '*')
        {
            GPS_NMEA_checksum_calculated ^= buffer[i];
            i++;
        }
        
        for(i = 6, j = 0; i < GPSBUFFER_SIZE && (j < 7); i++)
        {
            if(buffer[i] == ',')
            {
                j++;
                IntegerPart = 1;
            }else{
                switch(j)
                {
                    case 1:                                                             // TIME
                        if((buffer[i] >= '0') && (buffer[i] <= '9'))
                        {
                            if(i == 7 || i == 8)
                            {
                                GPShour = GPShour * 10;
                                GPShour += (buffer[i] - '0');
                            }
                            if(i == 9 || i == 10)
                            {
                                GPSminute = GPSminute * 10;
                                GPSminute += (buffer[i] - '0');
                            }
                            if(i == 11 || i == 12)
                            {
                                GPSsecond = GPSsecond * 10;
                                GPSsecond += (buffer[i] - '0');
                            }
                        }
                        break;
                    
                    case 2:                                                             // DAY
                        if((buffer[i] >= '0') && (buffer[i] <= '9'))
                        {
                            GPSday = GPSday * 10;
                            GPSday += (uint8_t)(buffer[i] - '0');
                        }
                        break;
                    
                    case 3:                                                             // MONTH
                        if((buffer[i] >= '0') && (buffer[i] <= '9'))
                        {
                            GPSmonth = GPSmonth * 10;
                            GPSmonth += (uint8_t)(buffer[i] - '0');
                        }
                        break;
                    
                    case 4:                                                             // YEAR
                        if((buffer[i] >= '0') && (buffer[i] <= '9'))
                        {
                            GPSyear = GPSyear * 10;
                            GPSyear += (uint8_t)(buffer[i] - '0');
                        }
                        break;
                    
                    case 7:                                                             // CHECKSUM (XOR of $ ... * bytes)
                        if(IntegerPart == 3)
                        {
                            if((buffer[i] >= '0') && (buffer[i] <= '9')) GPS_NMEA_checksum_toverify += (buffer[i] - '0');
                            else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPS_NMEA_checksum_toverify += (buffer[i] - '7');
                            IntegerPart++;
                        }
                        if(IntegerPart == 2)
                        {
                            if((buffer[i] >= '0') && (buffer[i] <= '9')) GPS_NMEA_checksum_toverify = ((buffer[i] - '0') << 4);
                            else if((buffer[i] >= 'A') && (buffer[i] <= 'F')) GPS_NMEA_checksum_toverify = ((buffer[i] - '7') << 4);
                            IntegerPart++;
                        }
                        if(buffer[i] == '*') IntegerPart = 2;
                        break;
                    
                    default:
                        break;
                }
            }
        }
    }
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


/*
    Fills a buffer with ASCII characters returned after polling UBX-MON-VER. Individual bits of information are 0x00 delimited.
*/
uint32_t UBLOX_get_version(uint8_t *buffer)
{
    UBLOX_send_message(request0A04, 8);                                                 // request UBX-MON-VER
    
    I2C1_buffer_pointer = 0;                                                           // reset UART1 RX buffer pointer
    UBLOX_receive_UBX(GPSbuffer, 104);                                              // copy the response from I2C1_RX_buffer to GPSbuffer
    
    if(GPSbuffer[0] == 0xB5 && GPSbuffer[1] == 0x62 && GPSbuffer[2] == 0x0A && GPSbuffer[3] == 0x04)
    {
        uint8_t sequence = 0;
        uint8_t zeroFlag = 0;
        uint32_t msglen = (GPSbuffer[5] << 8) | GPSbuffer[4];
        msglen -= 4;
        
        for(uint32_t i = 0; i < msglen; i++)
        {
            if(GPSbuffer[6 + i] != 0)
            {
                buffer[sequence++] = (GPSbuffer[6 + i]);
                zeroFlag = 0;
            }else{
                if(!zeroFlag)
                {
                    buffer[sequence++] = 0;
                    zeroFlag = 1;
                }
            }
        }
        
        return sequence;
    }else{
        return 0;
    }
}

