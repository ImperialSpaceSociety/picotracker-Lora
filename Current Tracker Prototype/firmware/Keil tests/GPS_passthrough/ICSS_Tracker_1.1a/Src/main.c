/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include "ms5607.h"
#include "ublox.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SHORT_CYCLE			46		// value / 0.83 = ~duration of one main loop in seconds (Normal mode)
#define LONG_CYCLE			96		// value / 0.83 = ~duration of one main loop in seconds (Power Saving mode)
#define SOLAR				0		// mV
#define BATTERY				2500	// mV
#define BATTERY_ON			0		// mV
#define FIX					90		// attempts to poll UBX-NAV-PVT
#define SATS				6		// number of satellites required for positional solution

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;



// UBLOX variables
// UBLOX -----------------------------------------------------------------------------------------------------------------
uint8_t GPS_UBX_error_bitfield								= 0;

uint16_t GPS_NMEA_latitude_int								= 0;
uint32_t GPS_NMEA_latitude_dec								= 0;
uint16_t GPS_NMEA_longitude_int								= 0;
uint32_t GPS_NMEA_longitude_dec								= 0;
uint8_t GPS_NMEA_NS											= 1;
uint8_t GPS_NMEA_EW											= 1;

int32_t GPS_UBX_latitude									= 0;
int32_t GPS_UBX_longitude									= 0;
float GPS_UBX_latitude_Float								= 0.0;
float GPS_UBX_longitude_Float								= 0.0;

int32_t GPSaltitude											= 0;

uint8_t GPShour												= 0;
uint8_t GPSminute											= 0;
uint8_t GPSsecond											= 0;
uint8_t GPSday												= 0;
uint8_t GPSmonth											= 0;
uint16_t GPSyear											= 0;

uint8_t GPSsats												= 0;
uint8_t GPSfix												= 0;
uint8_t GPSfix_0107											= 0;
uint8_t GPSvalidity											= 0;

uint8_t GPSnavigation										= 0;
uint8_t GPSpowermode										= 0;
uint8_t GPSpowersavemodestate								= 0;

int32_t GPSgroundspeed										= 0;
int32_t GPSheading											= 0;

uint16_t AD3data											= 0;
uint16_t AD9data											= 0;
uint16_t AD15data											= 0;
uint16_t Si4060Temp											= 0;
uint32_t telemCount											= 0;
uint32_t telemetry_len										= 0;

int32_t GPS_UBX_latitude_L									= 0;
int32_t GPS_UBX_longitude_L									= 0;
int32_t GPSaltitude_L										= 0;
uint8_t GPS_NMEA_NS_L										= 0;
uint8_t GPS_NMEA_EW_L										= 0;
uint16_t GPS_NMEA_latitude_int_L							= 0;
uint32_t GPS_NMEA_latitude_dec_L							= 0;
uint16_t GPS_NMEA_longitude_int_L							= 0;
uint32_t GPS_NMEA_longitude_dec_L							= 0;

uint32_t SSDVimages											= 0;
uint32_t SSDVstatus											= '0';



//I2C related
uint8_t	i2c_buffer[200];
HAL_StatusTypeDef i2c_status;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_I2C1_Init(void);
static void MX_RTC_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif



/* USER CODE BEGIN 0 */

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
	// keep checking if vcc voltage is high enough to carry on.
	while(1)
	{
		// WATCHDOG RESTART
		WATCHDOG_restart();
		
		ADC_start();
		AD9data = ADC_sample(9, 100);									// sample battery voltage
		ADC_stop();
		
		AD9 = ((uint32_t)AD9data * 6600) / 4096;
		if(AD9 >= BATTERY_ON) break;									// Battery minimum voltage limit (mV)
		
		RTT_init(1, 0x8000, 0);											// wake up every 1s
		PS_switch_MCK_to_FastRC(0, 0);
		PS_enter_Wait_Mode(1, 0, 0);									// enable wake up on RTT and enter wait mode
		RTT_off();
		PS_SystemInit(11, 3, 5);										// MCK: 2MHz PLL
	}

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
	// GPS INITIAL BACKUP
	UBLOX_send_message(dummyByte, 1);									// in case only MCU restarted while GPS stayed powered
	HAL_Delay(1000);												// wait for GPS module to be ready
	//UBLOX_send_message(setSwBackupMode, 16);							// low consumption at this point

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
	

	i2c_status = HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1), i2c_buffer, 1, 0xff);
	
	HAL_Delay(500);
	
	ms5607_Init();
	
	
	// GPS SETUP
	HAL_Delay(1000);											        // in case this follows immediately after the backup command
	UBLOX_send_message(dummyByte, 1);							// wake up GPS module
	HAL_Delay(1000);												      // wait for GPS module to be ready
	UBLOX_send_message(restore_default_config, sizeof(restore_default_config)); // reset GPS to default config
	while(!UBLOX_request_UBX(setNMEAoff, sizeof(setNMEAoff), 10, UBLOX_parse_ACK));				// turn off periodic NMEA output
	while(!UBLOX_request_UBX(setNAVmode, sizeof(setNAVmode), 10, UBLOX_parse_ACK));				// set Dynamic Model: airborne with <1g acceleration
	while(!UBLOX_request_UBX(setGPSonly, sizeof(setGPSonly), 10, UBLOX_parse_ACK));				// !! must verify if this is a good config: turn off all constellations except gps: UBX-CFG-GNSS 
	while(!UBLOX_request_UBX(setNAVmode, sizeof(setNAVmode), 10, UBLOX_parse_ACK));						// set to airbourne mode
	while(!UBLOX_request_UBX(saveConfiguration, sizeof(saveConfiguration), 10, UBLOX_parse_ACK));		// save current configuration


	// GPS INITIAL BACKUP
	//UART1_init(); // TODO: consider how to init and reinit i2c
	UBLOX_send_message(dummyByte, 1);									// in case only MCU restarted while GPS stayed powered
	HAL_Delay(1000);												// wait for GPS module to be ready
	UBLOX_send_message(setSwBackupMode, 16);							// low consumption at this point
	//UART1_deinit();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		MS5607_get_temp_pressure();
		HAL_Delay(1000);

		
//		i2c_status = HAL_I2C_Master_Receive(&hi2c1, (uint16_t) (GPS_I2C_ADDRESS << 1), i2c_buffer, 1, 0xff);
//		if((i2c_status == HAL_I2C_ERROR_NONE) && (i2c_buffer[0] != 0xff))
//		HAL_UART_Transmit(&huart1 , i2c_buffer, 1, 0xFFFF);

	
		// WATCHDOG RESTART
		WATCHDOG_restart();
		
		ADC_start();
		AD9data = ADC_sample(9, 100);									// sample battery voltage
		ADC_stop();
		
		AD9 = ((uint32_t)AD9data * 6600) / 4096;
		if(AD9 >= BATTERY_ON) break;									// Battery minimum voltage limit (mV)
		

	}
	
	// GPS SETUP
	UART1_init();
	SysTick_delay_ms(1000);												// in case this follows immediately after the backup command
	UBLOX_send_message(dummyByte, 1);									// wake up GPS module
	SysTick_delay_ms(1000);												// wait for GPS module to be ready
	UBLOX_request_UBX(setNMEAoff, 28, 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
	UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);				// set Dynamic Model: airborne with <1g acceleration
	UBLOX_request_UBX(setGPSonly, 28, 10, UBLOX_parse_ACK);				// turn off GLONASS
	UBLOX_request_UBX(saveConfiguration, 21, 10, UBLOX_parse_ACK);		// save current configuration	
	UART1_deinit();
	
	uint32_t cycleCount = 0;
	
	// MAIN LOOP
    while(1) 
    {
        // STATUS LED
        LED_PB5_blink(5);															// signal start of loop
		cycleCount++;
		
		// GPS FIX
		uint32_t fixCount = 0;
		uint8_t TXaprs = 0;
		uint8_t TXrtty = 0;
		uint8_t TXssdv = 0;
		
		UART1_init();
		UBLOX_send_message(dummyByte, 1);											// wake up GPS module
		HAL_delay(1000);														// wait for GPS module to be ready
		
		GPSnavigation = 0;
		UBLOX_request_UBX(request0624, 8, 44, UBLOX_parse_0624);
		
		if(GPSnavigation != 6)														// verify Dynamic Model: airborne with <1g acceleration
		{
			UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);					// if not, set it
		}
		
		while(1)																	// poll UBX-NAV-PVT until the module has fix (limited)
		{
			// WATCHDOG RESTART
			WATCHDOG_restart();
			
			GPSfix = 0;
			GPSfix_0107 = 0;
			GPSsats = 0;
			
			UBLOX_request_UBX(request0107, 8, 100, UBLOX_parse_0107); // UBX-NAV-PVT
			if(GPSfix == 3 && GPSfix_0107 == 1 && GPSsats >= SATS) break;
			
			fixCount++;
			
			if(fixCount > FIX)														// if taking too long reset and re-initialize GPS module
			{
				LED_PB5_blink(5);													// signal GPS module reset
				SysTick_delay_ms(100);
				LED_PB5_blink(5);
				
				UBLOX_send_message(resetReceiver, 12);								// reset GPS module
				SysTick_delay_ms(1000);												// wait for GPS module to be ready
				UBLOX_request_UBX(setNMEAoff, 28, 10, UBLOX_parse_ACK);				// turn off periodic NMEA output
				UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);				// set Dynamic Model: airborne with <1g acceleration
				UBLOX_request_UBX(setGPSonly, 28, 10, UBLOX_parse_ACK);				// turn off GLONASS
				UBLOX_request_UBX(saveConfiguration, 21, 10, UBLOX_parse_ACK);		// save current configuration
				
				GPSfix = 0;
				GPSfix_0107 = 0;
				GPSsats = 0;
				break;
			}
		}
		
		UBLOX_send_message(setSwBackupMode, 16);									// switch GPS module to software backup mode
		UART1_deinit();
		
		if(GPSfix == 3 && GPSfix_0107 == 1) {TXaprs = 1; TXrtty = 1; TXssdv = 1;}	// enable APRS, RTTY and SSDV transmissions
		else {TXaprs = 1; TXrtty = 0; TXssdv = 0;}									// disable RTTY and SSDV transmissions
		
		// Si4060/Si4463 TEMPERATURE
		SPI_init();
		SI4060_init();
		Si4060Temp = SI4060_get_temperature();										// SPI and Si4060 need to be initialized first to get the temperature
		SI4060_deinit();
		SPI_deinit();
		
		// ADC READINGS
		ADC_start();
		AD3data = ADC_sample(3, 100);												// SOLAR PANEL voltage
		AD9data = ADC_sample(9, 100);												// BATTERY voltage
		AD15data = ADC_sample_temperature(100);										// ATSAM3S8B's internal temperature
		ADC_stop();
		
		// SOLAR & BATTERY LIMITS
		uint32_t AD9 = ((uint32_t)AD9data * 6600) / 4096;
		
		if(AD9 >= BATTERY)														// solar panel and battery minimum voltage limit (mV)
		{
			WaitModeSeconds = SHORT_CYCLE;											// short cycle, transmit APRS, RTTY and SSDV
		}else{
			WaitModeSeconds = LONG_CYCLE;											// longer cycle
			TXrtty = 0;																// transmit only APRS
			TXssdv = 0;
		}
		
		// RTTY LIMIT
		if(TXrtty)
		{
			if((cycleCount % 2) == 1) TXrtty = 1;									// transmit RTTY only every other APRS cycle
			else TXrtty = 0;
		}
		
		// SSDV LIMIT
		if(TXssdv)
		{
			if(GPSminute == 0 || GPSminute == 1 || GPSminute == 30 || GPSminute == 31)
			{
				TXssdv = 1;															// if it is the top of the hour or on the half hour, transmit SSDV
			}else{
				TXssdv = 0;															// if not, disable it
			}
		}
		
		// CONSTRUCT RTTY TELEMETRY
		uint32_t telemLen = 0;
		
		if(TXrtty)
		{
			telemCount++;
			telemLen = UBLOX_construct_telemetry_UBX(TXbuffer, 0);					// store the telemetry string in TXbuffer
		}
		
		// WATCHDOG RESTART
		WATCHDOG_restart();
		
		// CONSTRUCT APRS PACKET
		APRShour						= GPShour;
		APRSminute						= GPSminute;
		APRSsecond						= GPSsecond;
		APRSyear						= GPSyear;
		APRSmonth						= GPSmonth;
		APRSday							= GPSday;
		APRSlatitude					= GPS_UBX_latitude_Float;
		APRSlongitude					= GPS_UBX_longitude_Float;
		APRSaltitude					= GPSaltitude;
		APRSsequence					= cycleCount;
		APRSvalue1						= AD3data;
		APRSvalue2						= AD9data;
		APRSvalue3						= AD15data;
		APRSvalue4						= Si4060Temp;
		APRSvalue5						= GPSsats;
		APRSbitfield					= 0;
		if(GPSnavigation == 6)					APRSbitfield |= (1 << 0);			// Nav bit (Airborne mode)
		if(GPSfix == 3)							APRSbitfield |= (1 << 1);			// Fix bit (GPS fix ok)
		if(WaitModeSeconds == LONG_CYCLE)		APRSbitfield |= (1 << 3);			// PSM bit (power save mode active)
		
		TC_rtty_gfsk_lookup				= 1;										// RTTY_INTERRUPT - 0; GFSK_SYNC - 1; - - 2; LOOKUP - 3
		APRS_send_path					= 2;										// send WIDE2-1 path (2)
		
		if(GPSfix)	APRS_packet_mode	= 1;										// full packet
		else		APRS_packet_mode	= 7;										// no position packet, just backlog and ADC readings
		
		APRS_packet_construct(APRSpacket);											// store the packet in APRSpacket
		
		// BACKLOG
		if((cycleCount % 30) == 0 && GPSfix == 3) APRS_store_backlog();				// save a new backlog to flash memory every x telemetry strings
		
		// GEOFENCE
		GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);			// choose the right APRS frequency based on current location
		APRS_tx_frequency = GEOFENCE_APRS_frequency;
		if(GEOFENCE_no_tx) TXaprs = 0;												// disable APRS transmission in NO AIRBORNE areas
		
		// STATUS LED
		LED_PA0_blink(5);															// signal start of transmissions
		
		// FAST MCK
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_SystemInit(11, 3, 2);													// MCK: 16MHz PLL
		
		// APRS TX
		if(TXaprs)
		{
			SI4060_TX_power = 0x5A;													// TT7F5 (144MHz) 0x5A -> 15.23dBm at 46.36mA
			
			SPI_init();
			SI4060_init();
			SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
			SI4060_frequency_offset(0);
			SI4060_PA_mode(2, 0);													// Si4463/64: higher maximum power, Class-E or Square Wave match
			SI4060_tx_APRS_GFSK_sync();												// transmit the packet using GFSK modulation
			SI4060_deinit();
			SPI_deinit();
		}
		
		// SLOW MCK
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_SystemInit(11, 3, 5);													// MCK: 2MHz PLL
		
		// RTTY TX
		if(TXrtty)
		{
			SI4060_TX_power = 0x1E;													// TT7F5 (434MHz) 0x1E -> 9.69dBm at 58.9mA
			
			SPI_init();
			SI4060_init();
			SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
			SI4060_frequency_offset(0);
			SI4060_PA_mode(2, 0);													// Si4463/64: higher maximum power, Class-E or Square Wave match
			SI4060_frequency(FREQUENCY_RTTY);
			SI4060_frequency_deviation(TX_DEVIATION_RTTY);
			SI4060_power_level(SI4060_TX_power);
			SI4060_tx_OOK_blips(5, 250, 1000);										// first transmit several blips to announce RTTY transmission
			
			// WATCHDOG RESTART
			WATCHDOG_restart();
			
			SI4060_modulation(2, 1);												// FSK, asynchronous
			SI4060_change_state(0x07);												// TX state
			TC0_init_RTTY_NORMAL();													// start TimerCounter0 to time baud rate
			
			uint8_t Sync[] = {0, 0, 0, 0, 0};
			SI4060_tx_RTTY_string_TC0(Sync, 5);										// transmit five 0x00 bytes to help receiver synchronize
			SI4060_tx_RTTY_string_TC0(TXbuffer, telemLen);							// then transmit the telemetry string
			
			TC0_stop();
			SI4060_deinit();
			SPI_deinit();
		}
		
		// WATCHDOG RESTART
		WATCHDOG_restart();
		
		// MT9D111 GET IMAGE
		uint8_t imageOK = 0;
		uint32_t JPEGlength = 0;
		uint16_t JPEGstatus = 0;
		
		if(TXssdv)
		{
			SSDVstatus = '0';
			
			// MAX MCK																// all following delays must be multiplied by 32 (2MHz -> 64MHz) 
			PS_switch_MCK_to_FastRC(0, 0);											// MCK: 4MHz internal FastRC
			PS_SystemInit(23, 3, 1);												// MCK: 64MHz PLL
			
			// CAMERA INIT & CHECK
			TWI_init_master();														// camera communicates via TWI interface, initialized to 100kHz
			PWM_init(6, 3);															// provide camera with 10.7MHz clock signal
			SysTick_delay_ms(32);													// restart clock 24 clock cycles before de-asserting standby
			
			if(MT9D111_exit_standby())												// if camera reacts, continue
			{
				MT9D111_reset();													// reset the camera
				
				if(MT9D111_get_version() == 0x15190020)								// check the camera responds
				{
					// TAKE JPEG IMAGE
					uint32_t camTimeout = 0;
					
					for(uint8_t i = 0; i < 4; i++)									// allow a few attempts in case of failure
					{
						// WATCHDOG RESTART
						WATCHDOG_restart();
						
						LED_PA0_blink(160);											// signal camera will try get an image
						SysTick_delay_ms(3200);
						LED_PA0_blink(160);
						SysTick_delay_ms(3200);
						LED_PA0_blink(160);
						
						SSDVstatus = i + '1';										// count attempts
						
						uint32_t len = CreateJpegHeader(JPEGbuffer, res_x, res_y, JPEG_COLOR_FORMAT, JPEG_RESTART_INTERVAL, qscale_1);
						
						// JPEG MODE INIT
						camTimeout = MT9D111_wait_for_state(3);						// wait for the camera's PREVIEW state
						if(!camTimeout) {SSDVstatus = 'P'; continue;}				// next attempt if timed out
						
						// WATCHDOG RESTART
						WATCHDOG_restart();
						
						camTimeout = MT9D111_mode_1();								// set up camera to take one JPEG
						if(!camTimeout) {SSDVstatus = 'C'; continue;}				// next attempt if timed out
						
						// WATCHDOG RESTART
						WATCHDOG_restart();
						
						// IMAGE SAMPLING
						camTimeout = 16000000;
						while((PIOA->PIO_PDSR & (1 << 15)) && camTimeout) camTimeout--;		// wait for the end of the current frame (VSYNC HIGH->LOW)
						if(!camTimeout) {SSDVstatus = 'D'; continue;}						// next attempt if timed out
						
						PDC_transfer(JPEGbuffer + len, MT9D111_BUFFER_SIZE - len);	// initialize the PDC (there is not enough time after VSYNC goes HIGH)
						
						// WATCHDOG RESTART
						WATCHDOG_restart();
						
						camTimeout = 16000000;
						while(!(PIOA->PIO_PDSR & (1 << 15)) && camTimeout) camTimeout--;	// wait for the start of a new frame (VSYNC LOW->HIGH)
						if(!camTimeout) {SSDVstatus = 'D'; continue;}						// next attempt if timed out
						
						camTimeout = 16000000;
						while(PIOA->PIO_PDSR & (1 << 15) && camTimeout) camTimeout--;		// wait for the end of the sampled frame (VSYNC HIGH->LOW)
						if(!camTimeout) {SSDVstatus = 'D'; continue;}						// next attempt if timed out
						
						// ANALYZE RECEIVED DATA
						MT9D111_register_write(WRITE_PAGE, 1);
						uint16_t da5 = MT9D111_variable_read(9, 15, 1);				// last JPEG length [23:16]
						uint16_t da6 = MT9D111_variable_read(9, 16, 0);				// last JPEG length [15:0]
						
						MT9D111_register_write(WRITE_PAGE, 2);
						JPEGstatus = MT9D111_register_read(0x02);					// JPEG status (interested in Transfer done status flag)
						
						JPEGlength = ((uint32_t)da5 << 16) | da6;					// size of the current JPG image (camera produced bytes)
						JPEGlength += len;											// size including the header
						
						if(JPEGlength <= (MT9D111_BUFFER_SIZE - 2) && (JPEGstatus & 0x01) && JPEGlength > (len + 500))
						{
							JPEGbuffer[JPEGlength++] = 0xFF;						// finish the image with an EOI marker
							JPEGbuffer[JPEGlength++] = 0xD9;
							imageOK = 1;											// MCU has JPEG image of length JPEGlength
							break;
						}
						else
						{
							for(uint32_t i = 0; i < MT9D111_BUFFER_SIZE; i++) JPEGbuffer[i] = 0;	// else clear the buffer
							JPEGlength = 0;
							JPEGstatus = 0;
							imageOK = 0;
							SSDVstatus = 'L';										// sampled image exceeded buffer size
						}
					}
					
					// WATCHDOG RESTART
					WATCHDOG_restart();
					
					// CAMERA STANDBY
					MT9D111_wait_for_state(3);										// wait for the camera's PREVIEW state
					camTimeout = MT9D111_standby();									// prepare camera for low power state, enter standby mode
					if(!camTimeout) SSDVstatus = 'E';								// failed to enter standby on exit
					SysTick_delay_ms(32);											// after asserting standby, wait 10 clock cycles before stopping CLK
					PWM_deinit();													// turn clock signal off
					TWI_deinit();													// de-initialize TWI
				}
				else																// camera didn't respond to command or wrong version
				{
					SSDVstatus = 'V';												// failed communication/wrong version
					PWM_deinit();													// turn clock signal off
					TWI_deinit();													// de-initialize TWI
					imageOK = 0;
				}
			}
			else																	// camera didn't transition to PREVIEW mode (disconnected?)
			{
				SSDVstatus = 'S';													// failed to communicate/exit standby
				PWM_deinit();														// turn clock signal off
				TWI_deinit();														// de-initialize TWI
				imageOK = 0;
			}
			
			// SLOW MCK
			PS_switch_MCK_to_FastRC(0, 0);											// MCK: 4MHz internal FastRC
			PS_SystemInit(11, 3, 5);												// MCK: 2MHz PLL
		}
			
		// SSDV TX
		if(TXssdv & imageOK)
		{
			SSDVimages++;
			SI4060_TX_power = 0x1E;													// TT7F5 (434MHz) 0x1E -> 9.69dBm at 58.9mA
			
			// RADIO INIT & SYNC
			SPI_init();
			SI4060_init();
			SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
			SI4060_frequency_offset(0);
			SI4060_PA_mode(2, 0);													// Si4463/64: higher maximum power, Class-E or Square Wave match
			SI4060_frequency(FREQUENCY_RTTY);
			SI4060_frequency_deviation(TX_DEVIATION_RTTY);
			SI4060_power_level(SI4060_TX_power);
			SI4060_tx_OOK_blips(5, 250, 250);										// first transmit several blips to announce SSDV transmission
			SI4060_modulation(2, 1);												// FSK, asynchronous
			SI4060_change_state(0x07);												// TX state
			TC0_init_RTTY_NORMAL();													// start TimerCounter0 to time baud rate
			
			uint8_t Sync[] = {0, 0, 0, 0, 0};
			SI4060_tx_RTTY_string_TC0(Sync, 5);										// transmit five 0x00 bytes to help receiver synchronize
			
			// SSDV PROCESS
			uint8_t *_JPEGbufferP = JPEGbuffer;
			ssdv_t ssdv;
			
			ssdv_enc_init(&ssdv, SSDV_TYPE_NORMAL, SSDV_CALLSIGN, img_id++, 4);
			ssdv_enc_set_buffer(&ssdv, pkt);
			
			uint8_t c = 0;
			uint32_t packetCount = 0;
			
			while(1)
			{	
				// WATCHDOG RESTART
				WATCHDOG_restart();
				
				// INTERLEAVED APRS & RTTY
				if(packetCount % packetsPerTelem == 0 && packetCount != 0)			// every x packets transmit APRS packet and RTTY telemetry
				{
					TC0_stop();														// stop transmission until GPS fix is obtained
					SI4060_deinit();
					SPI_deinit();
					
					// GPS FIX
					uint32_t fixCount = 0;
					uint8_t interleavedTXrtty = 0;
					uint8_t interleavedTXaprs = 1;
					
					UART1_init();
					UBLOX_send_message(dummyByte, 1);								// wake up GPS module
					SysTick_delay_ms(1000);											// wait for GPS module to be ready
					
					GPSnavigation = 0;
					UBLOX_request_UBX(request0624, 8, 44, UBLOX_parse_0624);
					
					if(GPSnavigation != 6)											// verify Dynamic Model: airborne with <1g acceleration
					{
						UBLOX_request_UBX(setNAVmode, 44, 10, UBLOX_parse_ACK);		// if not, set it
					}
					
					while(1)														// poll UBX-NAV-PVT until the module has fix (limited)
					{
						// WATCHDOG RESTART
						WATCHDOG_restart();
						
						GPSfix = 0;
						GPSfix_0107 = 0;
						GPSsats = 0;
						
						UBLOX_request_UBX(request0107, 8, 100, UBLOX_parse_0107);
						if(GPSfix == 3 && GPSfix_0107 == 1 && GPSsats >= SATS) break;
						
						fixCount++;
						
						if(fixCount > 15)											// if taking too long stop trying (decreased limit to normal operation)
						{
							GPSfix = 0;
							GPSfix_0107 = 0;
							GPSsats = 0;
							break;
						}
					}
					
					UBLOX_send_message(setSwBackupMode, 16);						// switch GPS module to software backup mode
					UART1_deinit();
					
					// Si4060/Si4463 TEMPERATURE
					SPI_init();
					SI4060_init();
					Si4060Temp = SI4060_get_temperature();							// SPI and Si4060 need to be initialized first to get the temperature
					SI4060_deinit();
					SPI_deinit();
					
					// ADC READINGS
					ADC_start();
					AD3data = ADC_sample(3, 100);									// SOLAR PANEL voltage
					AD9data = ADC_sample(9, 100);									// BATTERY voltage
					AD15data = ADC_sample_temperature(100);							// ATSAM3S8B's internal temperature
					ADC_stop();
					
					// TX LIMITS
					if(GPSfix == 3 && GPSfix_0107 == 1) interleavedTXrtty = 1;		// enable RTTY
					
					// CONSTRUCT RTTY TELEMETRY
					if(interleavedTXrtty)
					{
						telemCount++;
						telemLen = UBLOX_construct_telemetry_UBX(TXbuffer, 0);
					}
					
					// WATCHDOG RESTART
					WATCHDOG_restart();
					
					// CONSTRUCT APRS PACKET
					cycleCount++;
					
					APRShour						= GPShour;
					APRSminute						= GPSminute;
					APRSsecond						= GPSsecond;
					APRSyear						= GPSyear;
					APRSmonth						= GPSmonth;
					APRSday							= GPSday;
					APRSlatitude					= GPS_UBX_latitude_Float;
					APRSlongitude					= GPS_UBX_longitude_Float;
					APRSaltitude					= GPSaltitude;
					APRSsequence					= cycleCount;
					APRSvalue1						= AD3data;
					APRSvalue2						= AD9data;
					APRSvalue3						= AD15data;
					APRSvalue4						= Si4060Temp;
					APRSvalue5						= GPSsats;
					APRSbitfield					= 0;
					if(GPSnavigation == 6)			APRSbitfield |= (1 << 0);		// Nav bit (Airborne mode)
					if(GPSfix == 3)					APRSbitfield |= (1 << 1);		// Fix bit (GPS fix ok)
					if(TXssdv == 1)					APRSbitfield |= (1 << 2);		// Img bit (currently transmitting SSDV image)
					
					TC_rtty_gfsk_lookup				= 1;							// RTTY_INTERRUPT - 0; GFSK_SYNC - 1; - - 2; LOOKUP - 3
					APRS_send_path					= 2;							// send WIDE2-1 path (2)
					
					if(GPSfix)	APRS_packet_mode	= 1;							// full packet
					else		APRS_packet_mode	= 7;							// no position packet, just backlog and ADC readings
					
					APRS_packet_construct(APRSpacket);								// store the packet in APRSpacket
					
					// BACKLOG
					if((cycleCount % 30) == 0 && GPSfix == 3) APRS_store_backlog();	// save a new backlog to flash memory every x telemetry strings
					
					// GEOFENCE
					GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);	// choose the right APRS frequency based on current location
					APRS_tx_frequency = GEOFENCE_APRS_frequency;
					if(GEOFENCE_no_tx) interleavedTXaprs = 0;						// disable APRS transmission in NO AIRBORNE areas
					
					// STATUS LED
					LED_PB5_blink(5);												// signal interleaved transmission
					SysTick_delay_ms(50);
					LED_PB5_blink(5);
					
					// APRS TX
					if(interleavedTXaprs)
					{
						SI4060_TX_power = 0x5A;										// TT7F5 (144MHz) 0x5A -> 15.23dBm at 46.36mA
						
						// FAST MCK
						PS_switch_MCK_to_FastRC(0, 0);								// MCK: 4MHz internal FastRC
						PS_SystemInit(11, 3, 2);									// MCK: 16MHz PLL
						
						SPI_init();
						SI4060_init();
						SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
						SI4060_frequency_offset(0);
						SI4060_PA_mode(2, 0);										// Si4463/64: higher maximum power, Class-E or Square Wave match
						SI4060_tx_APRS_GFSK_sync();									// transmit the packet using GFSK modulation
						SI4060_deinit();
						SPI_deinit();
						
						// SLOW MCK
						PS_switch_MCK_to_FastRC(0, 0);								// MCK: 4MHz internal FastRC
						PS_SystemInit(11, 3, 5);									// MCK: 2MHz PLL
					}
					
					// RTTY TX
					SI4060_TX_power = 0x1E;											// TT7F5 (434MHz) 0x1E -> 9.69dBm at 58.9mA
					
					SPI_init();
					SI4060_init();
					SI4060_setup_pins(0x02, 0x04, 0x02, 0x02, 0x00, 0x00);
					SI4060_frequency_offset(0);
					SI4060_PA_mode(2, 0);											// Si4463/64: higher maximum power, Class-E or Square Wave match
					SI4060_frequency(FREQUENCY_RTTY);
					SI4060_frequency_deviation(TX_DEVIATION_RTTY);
					SI4060_power_level(SI4060_TX_power);
					SI4060_tx_OOK_blips(5, 250, 250);								// first transmit several blips to announce transmission
					
					// WATCHDOG RESTART
					WATCHDOG_restart();
					
					SI4060_modulation(2, 1);										// FSK, asynchronous
					SI4060_change_state(0x07);										// TX state
					TC0_init_RTTY_NORMAL();											// start TimerCounter0 to time baud rate
					
					uint8_t Sync[] = {0, 0, 0, 0, 0};
					SI4060_tx_RTTY_string_TC0(Sync, 5);								// transmit five 0x00 bytes to help receiver synchronize
					
					if(interleavedTXrtty)											// if not allowed, continue to next SSDV packet
					{
						SI4060_tx_RTTY_string_TC0(TXbuffer, telemLen);
						
						// WATCHDOG RESTART
						WATCHDOG_restart();
					}
				}
				
				// SSDV PACKET
				packetCount++;
				
				while((c = ssdv_enc_get_packet(&ssdv)) == SSDV_FEED_ME)
				{
					size_t r = 0;
					
					for(uint8_t i = 0; i < 64; i++)
					{
						if(_JPEGbufferP > JPEGbuffer + JPEGlength) continue;
						img[i] = *_JPEGbufferP++;
						r++;
					}
					
					if(r == 0) break;
					ssdv_enc_feed(&ssdv, img, r);
				}
				
				if(c == SSDV_EOI)
				{
					break;
				}
				
				else if(c != SSDV_OK)
				{
					break;
				}
				
				SI4060_tx_RTTY_string_TC0(pkt, 256);
			}
			
			TC0_stop();
			SI4060_deinit();
			SPI_deinit();
		}
		
		// LOW POWER CYCLE
		RTT_init(WaitModeSeconds, 0x8000, 0);										// Wait mode period in RC oscillator's seconds
		PS_switch_MCK_to_FastRC(0, 0);												// MCK: 4MHz internal FastRC
		PS_enter_Wait_Mode(1, 0, 0);												// enable wake up on RTT and enter wait mode
		RTT_off();																	// clear pending flag after wake-up
		PS_SystemInit(11, 3, 5);													// MCK: 2MHz PLL
    }
		
		
  /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 31;
  hrtc.Init.SynchPrediv = 1023;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
    
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 1;
  sDate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the Alarm A 
  */
  sAlarm.AlarmTime.Hours = 0;
  sAlarm.AlarmTime.Minutes = 0;
  sAlarm.AlarmTime.Seconds = 0;
  sAlarm.AlarmTime.SubSeconds = 0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RA_NSS_Pin|TCXO_EN_Pin|ANT_RX_Pin|LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ANT_BST_Pin|RA_RES_Pin|ANT_TX_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RA_NSS_Pin TCXO_EN_Pin ANT_RX_Pin */
  GPIO_InitStruct.Pin = RA_NSS_Pin|TCXO_EN_Pin|ANT_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RA_DIO0_Pin RA_DIO1_Pin RA_DIO2_Pin */
  GPIO_InitStruct.Pin = RA_DIO0_Pin|RA_DIO1_Pin|RA_DIO2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : RA_DIO3_Pin */
  GPIO_InitStruct.Pin = RA_DIO3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(RA_DIO3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ANT_BST_Pin RA_RES_Pin ANT_TX_Pin */
  GPIO_InitStruct.Pin = ANT_BST_Pin|RA_RES_Pin|ANT_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : GPS_PPS_Pin GPS_INT_Pin */
  GPIO_InitStruct.Pin = GPS_PPS_Pin|GPS_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
