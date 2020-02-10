/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @brief   this is the main!
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
#include "hw.h"
#include "low_power_manager.h"
#include "lora.h"
#include "bsp.h"
#include "timeServer.h"
#include "vcom.h"
#include "version.h"
#include "ublox.h"
#include "geofence.h"
#include "ms5607.h"
#include "LoRaMac.h"
#include "main.h"
#include "stm32l0xx_hal_flash.h"
#include "stm32l0xx_hal_flash_ex.h"
#include "stm32l0xx_hal.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/*!
 * CAYENNE_LPP is myDevices Application server.
 */
#define CAYENNE_LPP
#define LPP_DATATYPE_DIGITAL_INPUT  0x0
#define LPP_DATATYPE_DIGITAL_OUTPUT 0x1
#define LPP_DATATYPE_ANALOG_INPUT   0x2
#define LPP_DATATYPE_HUMIDITY       0x68
#define LPP_DATATYPE_TEMPERATURE    0x67
#define LPP_DATATYPE_BAROMETER      0x73
#define LPP_DATATYPE_GPSLOCATION    0x88
#define LPP_DATATYPE_ACCELEROMETER  0x71
#define LPP_DATATYPE_GPSTIME        0x85
#define LPP_APP_PORT 99

// IMPT define switches in main.h to use or not use the GPS, sensor and radio and app duty cycle


/*!
 * LoRaWAN Adaptive Data Rate
 * @note Please note that when ADR is enabled the end-device should be static
 */
#define LORAWAN_ADR_STATE LORAWAN_ADR_OFF
/*!
 * LoRaWAN Default data Rate Data Rate
 * @note Please note that LORAWAN_DEFAULT_DATA_RATE is used only when ADR is disabled 
 */
#define LORAWAN_DEFAULT_DATA_RATE DR_0
/*!
 * LoRaWAN application port
 * @note do not use 224. It is reserved for certification
 */
#define LORAWAN_APP_PORT                            2
/*!
 * LoRaWAN default endNode class port
 */
#define LORAWAN_DEFAULT_CLASS                       CLASS_A
/*!
 * LoRaWAN default confirm state
 */
#define LORAWAN_DEFAULT_CONFIRM_MSG_STATE           LORAWAN_UNCONFIRMED_MSG
/*!
 * User application data buffer size
 */
#define LORAWAN_APP_DATA_BUFF_SIZE                           64
/*!
 * User application data
 */
static uint8_t AppDataBuff[LORAWAN_APP_DATA_BUFF_SIZE];

/*!
 * User application data structure
 */
//static lora_AppData_t AppData={ AppDataBuff,  0 ,0 };
lora_AppData_t AppData={ AppDataBuff,  0 ,0 };

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* call back when LoRa endNode has received a frame*/
static void LORA_RxData( lora_AppData_t *AppData);

/* call back when LoRa endNode has just joined*/
static void LORA_HasJoined( void );

/* call back when LoRa endNode has just switch the class*/
static void LORA_ConfirmClass ( DeviceClass_t Class );

/* call back when server needs endNode to send a frame*/
static void LORA_TxNeeded ( void );

/* LoRa endNode send request*/
static void Send( void* context );

/* start the tx process*/
static void LoraStartTx(TxEventType_t EventType);

/* tx timer callback function*/
static void OnTxTimerEvent( void* context );

/* tx timer callback function*/
static void LoraMacProcessNotify( void );

/* Private variables ---------------------------------------------------------*/
/* load Main call backs structure*/
static LoRaMainCallback_t LoRaMainCallbacks = { HW_GetBatteryLevel,
                                                HW_GetTemperatureLevel,
                                                HW_GetUniqueId,
                                                HW_GetRandomSeed,
                                                LORA_RxData,
                                                LORA_HasJoined,
                                                LORA_ConfirmClass,
                                                LORA_TxNeeded,
                                                LoraMacProcessNotify};
LoraFlagStatus LoraMacProcessRequest=LORA_RESET;
LoraFlagStatus AppProcessRequest=LORA_RESET;
/*!
 * Specifies the state of the application LED
 */
static uint8_t AppLedStateOn = RESET;
                                               
static TimerEvent_t TxTimer;


/* !
 *Initialises the Lora Parameters
 */
static  LoRaParam_t LoRaParamInit= {LORAWAN_ADR_STATE,
                                    LORAWAN_DEFAULT_DATA_RATE,  
                                    LORAWAN_PUBLIC_NETWORK};	
																		


// UBLOX variables
uint8_t GPS_UBX_error_bitfield						= 0;

int32_t GPS_UBX_latitude									= 0;
int32_t GPS_UBX_longitude									= 0;
float GPS_UBX_latitude_Float							= 51.509865; // temp dummy for testing geofencing
float GPS_UBX_longitude_Float							= -0.118092;  // temp dummy for testing geofencing

int32_t GPSaltitude												= 0;

uint8_t GPShour														= 0;
uint8_t GPSminute													= 0;
uint8_t GPSsecond													= 0;
uint8_t GPSday														= 0;
uint8_t GPSmonth													= 0;
uint16_t GPSyear													= 0;

uint8_t GPSsats														= 0;
uint8_t GPSfix_type														= 0;
uint8_t GPSfix_OK												= 0;
uint8_t GPSvalidity												= 0;

uint8_t GPSnavigation											= 0;
uint8_t GPSpowermode											= 0;
uint8_t GPSpowersavemodestate							= 0;

int32_t GPSgroundspeed										= 0;
int32_t GPSheading												= 0;

uint16_t AD3data													= 0;
uint16_t AD9data													= 0;
uint16_t AD15data													= 0;
uint32_t telemCount												= 0;
uint32_t telemetry_len										= 0;

int32_t GPS_UBX_latitude_L								= 0;
int32_t GPS_UBX_longitude_L								= 0;
int32_t GPSaltitude_L											= 0;

uint32_t fixAttemptCount                  = 0;
uint8_t ack			                          = 0; // 1 is ack, 0 is nak



// Special message info
uint8_t message_counter                   = 0;
char special_message[] =
	{0x49 ,0x6e ,0x74 ,0x65 ,0x72 ,0x6e ,0x73 ,0x68 ,0x69 ,0x70 ,0x20 ,0x77 ,0x61 ,0x6e ,0x74 ,0x65 ,0x64 ,0x21 ,0x20 ,0x48 ,0x69 ,0x72 ,0x65 ,0x20 ,0x6d ,0x65 ,0x21 ,0x20 ,0x6d ,0x72 ,0x6e ,0x33 ,0x33 ,0x31 ,0x37 ,0x40 ,0x69 ,0x63 ,0x2e ,0x61 ,0x63 ,0x2e ,0x75 ,0x6b
};
	

// Internship wanted! Hire me! mrn3317@ic.ac.uk


// Temp pressure
double PRESSURE_Value; // compensated pressure value
double TEMPERATURE_Value; // compensated temperature value


// GEOFENCE variables
/* The world is split into polygons e.g. EU863870_4F_polygon. 
 * Multiple polygons can have the same LoRa region settings. E.g. LORAMAC_REGION_EU868.
 * Keeps track of which polygon the tracker is in, and if it changes to another polygon,
 * all LoRa settings are reinitialised.
 * 
 */
int REGIONAL_LORA_SETTINGS_CORRECT = 1; // Flag indicating if geofence settings are correct for region we are flying over. 1 if correct, 0 if incorrect

LoRaMacRegion_t Current_LoRa_Region_Settings   = LORAMAC_REGION_EU868;
LoRaMacRegion_t Previous_LoRa_Region_Settings  = LORAMAC_REGION_EU868;

Polygon_t current_polygon_region  = EU863870_4F_polygon;
Polygon_t previous_polygon_region = EU863870_4F_polygon;

uint32_t GEOFENCE_no_tx;


//I2C related
uint8_t	i2c_buffer[2];
HAL_StatusTypeDef i2c_status;

uint8_t	buffer_0xB5[1];
uint8_t	buffer_0x62[1];
uint8_t buffer_ubx_packet_wo_header[150]; // this packet does not include the 0xb5 0x62 header


// Battery/Solar voltage
uint32_t VCC_ADC												= 0;

// Set up brown out reset voltage above the level of the GPS
void set_brownout_level( void );







/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main( void )
{
  /* STM32 HAL library initialization*/
  HAL_Init();
  
  /* Configure the system clock*/
  SystemClock_Config();
  
  /* Configure the debug mode*/
  DBG_Init();
	
	/* Set Brown out reset level voltage to 2.8V, above the 2.7V threshold of the GPS */
	set_brownout_level();
	

  /* Configure the hardware*/
  HW_Init();
	

	if (GPSaltitude<1000)
	{
		// Indicate that we are alive!
		for(uint8_t i = 0; i < 10; i++)
		{
			HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_SET);
			HAL_Delay(70); 
			HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_RESET);
			HAL_Delay(50);
		}
	}

	
	#if defined (GPS_ENABLED)
	/* GET intial location fix to set LORA region */
	get_location_fix();
	#endif
	
	/* Find out which region of world we are in */
	GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);
	
 
	PRINTF("My location polygon : %d\n\r", (int)current_polygon_region);  
	
  /*Disbale Stand-by mode*/
  LPM_SetOffMode(LPM_APPLI_Id , LPM_Disable );
  
  PRINTF("VERSION: %X\n\r", VERSION);
  
  /* Configure the Lora Stack*/
  LORA_Init( &LoRaMainCallbacks, &LoRaParamInit); // sets up LoRa settings depending on the location we are in.
  
	#if defined (RADIO_ENABLED)
  LORA_Join();
	#endif
  
  LoraStartTx( TX_ON_TIMER) ;
  
	
	// Infinite loop
  while( 1 )
  {
		

		
    if (AppProcessRequest==LORA_SET)
    {
			
			
      /*reset notification flag*/
      AppProcessRequest=LORA_RESET;
			


	    /*Send*/
      Send( NULL ); // Here lies the function to read sensor and GPS, parse and send it
			
			/* if the tracker moves into another region, break out of main loop and reinit everything including radio */
			if (!REGIONAL_LORA_SETTINGS_CORRECT){ 
				break;
			}
		
    }
		
		if (LoraMacProcessRequest==LORA_SET)
    {
      /*reset notification flag*/
      LoraMacProcessRequest=LORA_RESET;
      LoRaMacProcess( );
    }
		
    /*If a flag is set at this point, mcu must not enter low power and must loop*/
    DISABLE_IRQ( );
    
    /* if an interrupt has occurred after DISABLE_IRQ, it is kept pending 
     * and cortex will not enter low power anyway  */
    if ((LoraMacProcessRequest!=LORA_SET) && (AppProcessRequest!=LORA_SET))
    {
#ifndef LOW_POWER_DISABLE
      LPM_EnterLowPower( );
#endif
    }

    ENABLE_IRQ();
    
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */
  }
} // END main()


void LoraMacProcessNotify(void)
{
  LoraMacProcessRequest=LORA_SET;
}




static void LORA_HasJoined( void )
{
#if( OVER_THE_AIR_ACTIVATION != 0 )
  PRINTF("JOINED\n\r");
#endif
  LORA_RequestClass( LORAWAN_DEFAULT_CLASS );
}

static void Send( void* context )
{
  /* USER CODE BEGIN 3 */
	uint16_t battery_level16 = 0;
	uint16_t battery_level_vdd = 0;
  uint16_t cayenne_pressure = 0;
  int16_t cayenne_temperature = 0;
  //uint16_t cayenne_humidity = 0;
  sensor_t sensor_data;
  int32_t cayenne_latitude=0, cayenne_longitude = 0, cayenne_altitudeGps=0;
  //int32_t epoch_value =0;
  uint16_t cayenne_battery_voltage;
	uint8_t cayenne_GPS_sats;

#if defined (RADIO_ENABLED)
  if ( LORA_JoinStatus () != LORA_SET)
  {
    /*Not joined, try again later*/
    LORA_Join();
    return;
  }
#endif
  
  TVL1(PRINTF("SEND REQUEST\n\r");)
 
	
	/* The special message routine */
	#if defined( SPECIAL_MESSAGE)
	// we send down the special message every once is 2 messages
	
	// reset the message counter. 
	if (message_counter>=1)
	{
		message_counter = 0;

	}
	else
	{
		message_counter++;

		AppData.Port = LPP_APP_PORT;		
		AppData.BuffSize = sizeof(special_message); // make sure it does not count the /n
		
		for (uint8_t i=0; i<sizeof(special_message); i++) {
				AppData.Buff[i] = special_message[i];
		}
		
		#if defined (RADIO_ENABLED)
		LORA_send( &AppData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE);
		#endif

		return;
	}
	
	#endif


  BSP_sensor_Read( &sensor_data );

	/* Find out which region of world we are in */
	GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);
	
	/* reinit everything if it enters another LoRaWAN region. Dont tx when over regions where we are not supposed to tx */
	if ((!REGIONAL_LORA_SETTINGS_CORRECT) || (GEOFENCE_no_tx) ){
		return;
	}
	
	/* Evaluate battery level */
  uint8_t cchannel=0;
	battery_level16 = (uint16_t) BSP_GetBatteryLevel16();
	battery_level_vdd = (uint16_t)HW_GetBatteryLevelmV();

  cayenne_temperature = ( int16_t )( sensor_data.temperature * 10 );     /* in °C * 10 */
  cayenne_pressure    = ( uint16_t )( sensor_data.pressure * 100 / 10 );  /* in hPa / 10 */
  //cayenne_humidity    = ( uint16_t )( sensor_data.humidity * 2 );        /* in %*2     */
  cayenne_battery_voltage = ( uint16_t )battery_level16/10;               /* Battery level expressed in hundreds of mV */
	//cayenne_battery_voltage = ( uint16_t )battery_level_vdd*100;               /* Battery level expressed in hundreds of mV */

	cayenne_altitudeGps = GPSaltitude*100;
	cayenne_latitude = GPS_UBX_latitude_Float * 10000;
	cayenne_longitude = GPS_UBX_longitude_Float * 10000;
	cayenne_GPS_sats = GPSsats;
	
	
	
	PRINTF("Just read sensor values");
	PRINTF("\r\n"); 
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
	
	
	uint32_t i = 0;
  
  AppData.Port = LPP_APP_PORT;
  
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_BAROMETER;
  AppData.Buff[i++] = ( cayenne_pressure >> 8 ) & 0xFF;
  AppData.Buff[i++] = cayenne_pressure & 0xFF;
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_TEMPERATURE; 
  AppData.Buff[i++] = ( cayenne_temperature >> 8 ) & 0xFF;
  AppData.Buff[i++] = cayenne_temperature & 0xFF;
	
	// TO be uncommented if humidity value is recorded
//  AppData.Buff[i++] = cchannel++;
//  AppData.Buff[i++] = LPP_DATATYPE_HUMIDITY;
//  AppData.Buff[i++] = cayenne_humidity & 0xFF;

  /* The maximum payload size does not allow to send more data for lowest DRs.
	 * Problem solved by setting the min data rates for the two regions(AU915 and US915) greater
	 * than DR3
	 */

	// using reference https://github.com/MicrochipTech/Location-Tracking-using-SAMR34-and-UBLOX-GPS-Module/blob/master/src/CayenneLPP/lpp.c
	AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_GPSLOCATION;
  AppData.Buff[i++] = cayenne_latitude >> 16;
  AppData.Buff[i++] = cayenne_latitude >> 8;
  AppData.Buff[i++] = cayenne_latitude;
	
  AppData.Buff[i++] = cayenne_longitude >> 16;
  AppData.Buff[i++] = cayenne_longitude >> 8;
  AppData.Buff[i++] = cayenne_longitude;
	
	
  AppData.Buff[i++] = ( cayenne_altitudeGps >> 16 ) & 0xFF; 
  AppData.Buff[i++] = ( cayenne_altitudeGps >> 8 ) & 0xFF;
  AppData.Buff[i++] = cayenne_altitudeGps & 0xFF;
		
		
	AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_ANALOG_INPUT;
  AppData.Buff[i++] = ( cayenne_battery_voltage >> 8 ) & 0xFF; // TODO: read battery ADC
  AppData.Buff[i++] = cayenne_battery_voltage & 0xFF;
  
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_DIGITAL_OUTPUT; 
  AppData.Buff[i++] = cayenne_GPS_sats;
    


  AppData.BuffSize = i;
	
	#if defined (RADIO_ENABLED)
	LORA_send( &AppData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE);
	#endif
  
}


static void LORA_RxData( lora_AppData_t *AppData )
{
  /* USER CODE BEGIN 4 */
  PRINTF("PACKET RECEIVED ON PORT %d\n\r", AppData->Port);

  switch (AppData->Port)
  {
    case 3:
    /*this port switches the class*/
    if( AppData->BuffSize == 1 )
    {
      switch (  AppData->Buff[0] )
      {
        case 0:
        {
          LORA_RequestClass(CLASS_A);
          break;
        }
        case 1:
        {
          LORA_RequestClass(CLASS_B);
          break;
        }
        case 2:
        {
          LORA_RequestClass(CLASS_C);
          break;
        }
        default:
          break;
      }
    }
    break;
    case LORAWAN_APP_PORT:
    if( AppData->BuffSize == 1 )
    {
      AppLedStateOn = AppData->Buff[0] & 0x01;
      if ( AppLedStateOn == RESET )
      {
        PRINTF("LED OFF\n\r");
        LED_Off( LED1 ) ; 
      }
      else
      {
        PRINTF("LED ON\n\r");
        LED_On( LED1 ) ; 
      }
    }
    break;
  case LPP_APP_PORT:
  {
    AppLedStateOn= (AppData->Buff[2] == 100) ?  0x01 : 0x00;
    if ( AppLedStateOn == RESET )
    {
      PRINTF("LED OFF\n\r");
      LED_Off( LED1 ) ; 
      
    }
    else
    {
      PRINTF("LED ON\n\r");
      LED_On( LED1 ) ; 
    }
    break;
  }
  default:
    break;
  }
  /* USER CODE END 4 */
}

static void OnTxTimerEvent( void* context )
{
  /*Wait for next tx slot*/
  TimerStart( &TxTimer);
  
  AppProcessRequest=LORA_SET;
}

static void LoraStartTx(TxEventType_t EventType)
{
  if (EventType == TX_ON_TIMER)
  {
    /* send everytime timer elapses */
    TimerInit( &TxTimer, OnTxTimerEvent );
    TimerSetValue( &TxTimer,  APP_TX_DUTYCYCLE); 
    OnTxTimerEvent( NULL );
  }
  else
  {
    /* send everytime button is pushed */
    GPIO_InitTypeDef initStruct={0};
  
    initStruct.Mode =GPIO_MODE_IT_RISING;
    initStruct.Pull = GPIO_PULLUP;
    initStruct.Speed = GPIO_SPEED_HIGH;

    HW_GPIO_Init( USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, &initStruct );
    HW_GPIO_SetIrq( USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, 0, Send );
  }
}

static void LORA_ConfirmClass ( DeviceClass_t Class )
{
  PRINTF("switch to class %c done\n\r","ABC"[Class] );

  /*Optionnal*/
  /*informs the server that switch has occurred ASAP*/
  AppData.BuffSize = 0;
  AppData.Port = LORAWAN_APP_PORT;
  
  LORA_send( &AppData, LORAWAN_UNCONFIRMED_MSG);
}

static void LORA_TxNeeded ( void )
{
  AppData.BuffSize = 0;
  AppData.Port = LORAWAN_APP_PORT;
  
  LORA_send( &AppData, LORAWAN_UNCONFIRMED_MSG);
}

void set_brownout_level( void )
{ /*!< BOR Reset threshold levels for 2.8V - 2.9V VDD power supply    */
	if ((FLASH_OB_GetBOR() & 0x0F) != OB_BOR_LEVEL5){
		HAL_FLASH_Unlock();
		/* Unlocks the option bytes block access */
		HAL_FLASH_OB_Unlock();
		/* Clears the FLASH pending flags */
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR |
		FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);
		/* Select The Desired V(BOR) Level------------------------*/
		FLASH_OB_BORConfig(OB_BOR_LEVEL5);
		/* Launch the option byte loading and generate a System Reset */
		HAL_FLASH_OB_Launch();
		
		HAL_FLASH_Lock();
	}
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
