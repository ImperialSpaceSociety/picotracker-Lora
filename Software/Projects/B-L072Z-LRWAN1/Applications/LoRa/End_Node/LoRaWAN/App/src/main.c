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


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* 
 *  GPS related defines
*/

#define SHORT_CYCLE			46		// value / 0.83 = ~duration of one main loop in seconds (Normal mode)
#define LONG_CYCLE			96		// value / 0.83 = ~duration of one main loop in seconds (Power Saving mode)
#define SOLAR				0		// mV
#define BATTERY				2500	// mV
#define BATTERY_ON			3.0		// mV
#define FIX					90		// attempts to poll UBX-NAV-PVT
#define SATS				4		// number of satellites required for positional solution

/*!
 * CAYENNE_LPP is myDevices Application server.
 */
#define CAYENNE_LPP
#define LPP_DATATYPE_DIGITAL_INPUT  0x0
#define LPP_DATATYPE_DIGITAL_OUTPUT 0x1
#define LPP_DATATYPE_HUMIDITY       0x68
#define LPP_DATATYPE_TEMPERATURE    0x67
#define LPP_DATATYPE_BAROMETER      0x73
#define LPP_APP_PORT 99
/*!
 * Defines the application data transmission duty cycle. 5s, value in [ms].
 */
#define APP_TX_DUTYCYCLE                            20000
/*!
 * LoRaWAN Adaptive Data Rate
 * @note Please note that when ADR is enabled the end-device should be static
 */
#define LORAWAN_ADR_STATE LORAWAN_ADR_ON
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
																		
// Radio variables
uint32_t LoRa_tx_frequency									= 144800000; // needs to be changed to Lora TX frequency. 
uint8_t TXLoRa                              = 1;

// UBLOX variables
uint8_t GPS_UBX_error_bitfield						= 0;

int32_t GPS_UBX_latitude									= 0;
int32_t GPS_UBX_longitude									= 0;
float GPS_UBX_latitude_Float							= 1.499827; // temp dummy for testing geofencing
float GPS_UBX_longitude_Float							= 103.813151;  // temp dummy for testing geofencing


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


// Temp pressure
double PRESSURE_Value; // compensated pressure value
double TEMPERATURE_Value; // compensated temperature value

// GEOFENCE variables
uint32_t GEOFENCE_LoRa_frequency					= 0;
uint32_t GEOFENCE_no_tx										= 0;



//I2C related
uint8_t	i2c_buffer[2];
HAL_StatusTypeDef i2c_status;


// Battery/Solar voltage
uint32_t VCC_ADC												= 0;



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
  
  /* Configure the hardware*/
  HW_Init();
  
  /* USER CODE BEGIN 1 */
	
	
	// set LED pin high
	HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_SET);

	
	// Setup pressure and temperature sensor
	//ms5607_Init(); // Now initialised in bsp.c . Need to verify if it works

	// GPS SETUP
	setup_GPS();
	

	// GPS INITIAL BACKUP
	Backup_GPS();

	
  /* USER CODE END 1 */
  
  /*Disbale Stand-by mode*/
  LPM_SetOffMode(LPM_APPLI_Id , LPM_Disable );
  
  PRINTF("VERSION: %X\n\r", VERSION);
  
  /* Configure the Lora Stack*/
  LORA_Init( &LoRaMainCallbacks, &LoRaParamInit);
  
  LORA_Join();
  
  LoraStartTx( TX_ON_TIMER) ;
  
	
	// Infinite loop
  while( 1 )
  {
    if (AppProcessRequest==LORA_SET)
    {
			
			// MEDAD: It looks like it transmits after entering here
			
      /*reset notification flag*/
      AppProcessRequest=LORA_RESET;
			

	    /*Send*/
      Send( NULL );
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
  uint16_t pressure = 0;
  int16_t temperature = 0;
  uint16_t humidity = 0;
  uint8_t batteryLevel;
  sensor_t sensor_data;
  
  if ( LORA_JoinStatus () != LORA_SET)
  {
    /*Not joined, try again later*/
    LORA_Join();
    return;
  }
  
  TVL1(PRINTF("SEND REQUEST\n\r");)
#ifndef CAYENNE_LPP
  int32_t latitude, longitude = 0;
  uint16_t altitudeGps = 0;
#endif
  


  BSP_sensor_Read( &sensor_data );

#ifdef CAYENNE_LPP
  uint8_t cchannel=0;
  temperature = ( int16_t )( sensor_data.temperature * 10 );     /* in °C * 10 */
  pressure    = ( uint16_t )( sensor_data.pressure * 100 / 10 );  /* in hPa / 10 */
  humidity    = ( uint16_t )( sensor_data.humidity * 2 );        /* in %*2     */
  uint32_t i = 0;

  batteryLevel = HW_GetBatteryLevel( );                     /* 1 (very low) to 254 (fully charged) */

  AppData.Port = LPP_APP_PORT;

  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_BAROMETER;
  AppData.Buff[i++] = ( pressure >> 8 ) & 0xFF;
  AppData.Buff[i++] = pressure & 0xFF;
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_TEMPERATURE; 
  AppData.Buff[i++] = ( temperature >> 8 ) & 0xFF;
  AppData.Buff[i++] = temperature & 0xFF;
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_HUMIDITY;
  AppData.Buff[i++] = humidity & 0xFF;
#if defined( REGION_US915 ) || defined ( REGION_AU915 )
  /* The maximum payload size does not allow to send more data for lowest DRs */
#else
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_DIGITAL_INPUT; 
  AppData.Buff[i++] = batteryLevel*100/254;
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_DIGITAL_OUTPUT; 
  AppData.Buff[i++] = AppLedStateOn;
#endif  /* REGION_XX915 */
#else  /* not CAYENNE_LPP */

  temperature = ( int16_t )( sensor_data.temperature * 100 );     /* in °C * 100 */
  pressure    = ( uint16_t )( sensor_data.pressure * 100 / 10 );  /* in hPa / 10 */
  humidity    = ( uint16_t )( sensor_data.humidity * 10 );        /* in %*10     */
  latitude = sensor_data.latitude;
  longitude= sensor_data.longitude;
  uint32_t i = 0;

  batteryLevel = HW_GetBatteryLevel( );                     /* 1 (very low) to 254 (fully charged) */

  AppData.Port = LORAWAN_APP_PORT;

#if defined( REGION_US915 ) || defined ( REGION_AU915 )
  AppData.Buff[i++] = AppLedStateOn;
  AppData.Buff[i++] = ( pressure >> 8 ) & 0xFF;
  AppData.Buff[i++] = pressure & 0xFF;
  AppData.Buff[i++] = ( temperature >> 8 ) & 0xFF;
  AppData.Buff[i++] = temperature & 0xFF;
  AppData.Buff[i++] = ( humidity >> 8 ) & 0xFF;
  AppData.Buff[i++] = humidity & 0xFF;
  AppData.Buff[i++] = batteryLevel;
  AppData.Buff[i++] = 0;
  AppData.Buff[i++] = 0;
  AppData.Buff[i++] = 0;
#else  /* not REGION_XX915 */
  AppData.Buff[i++] = AppLedStateOn;
  AppData.Buff[i++] = ( pressure >> 8 ) & 0xFF;
  AppData.Buff[i++] = pressure & 0xFF;
  AppData.Buff[i++] = ( temperature >> 8 ) & 0xFF;
  AppData.Buff[i++] = temperature & 0xFF;
  AppData.Buff[i++] = ( humidity >> 8 ) & 0xFF;
  AppData.Buff[i++] = humidity & 0xFF;
  AppData.Buff[i++] = batteryLevel;
  AppData.Buff[i++] = ( latitude >> 16 ) & 0xFF;
  AppData.Buff[i++] = ( latitude >> 8 ) & 0xFF;
  AppData.Buff[i++] = latitude & 0xFF;
  AppData.Buff[i++] = ( longitude >> 16 ) & 0xFF;
  AppData.Buff[i++] = ( longitude >> 8 ) & 0xFF;
  AppData.Buff[i++] = longitude & 0xFF;
  AppData.Buff[i++] = ( altitudeGps >> 8 ) & 0xFF;
  AppData.Buff[i++] = altitudeGps & 0xFF;
#endif  /* REGION_XX915 */
#endif  /* CAYENNE_LPP */
  AppData.BuffSize = i;
  
  LORA_send( &AppData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE);
  
  /* USER CODE END 3 */
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
