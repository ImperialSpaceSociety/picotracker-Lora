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
#include "stm32l0xx_hal_pwr.h"
#include "stm32l0xx.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//#define LOW_POWER_DISABLE
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
																		




uint8_t GPS_VOLTAGE_NOT_ABOVE_THRESHOLD = 1;

// Set up brown out reset voltage above the level of the GPS
void set_brownout_level( void );

// Configure the Power Voltage Detector (PVD)
void PVD_Config( void );
// PCD config type def
PWR_PVDTypeDef sConfigPVD;



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

	
	/* Set Brown out reset level voltage to 1.7V */
	set_brownout_level();
	
	
	/* Initialise serial debug interface */
	TraceInit( );

	
	PRINTF("\r\n\r\n");
	PRINTF("************************************ \r\n");
	PRINTF("* Picotracker Lora                 * \r\n");
	PRINTF("* Imperial College Space Society   * \r\n");
	PRINTF("************************************ \r\n\r\n");

	
  PRINTF("SELFTEST: Initialising Hardware\n\r");

	/* Configure the hardware*/
	HW_Init();
	
	/*Disbale Stand-by mode*/
	LPM_SetOffMode(LPM_APPLI_Id , LPM_Disable );


	#if GPS_ENABLED
	/* GET intial location fix to set LORA region 
	 * The program cannot go on to unless it gets a GPS fix. It is neccessary for it to try forever
	 * It needs a GPS fix to get the right LoRa params for the region
	 */
	PRINTF("SELFTEST: Attempting to get a GPS fix\n\r");
	while(!get_location_fix());

	#endif
	
	
	PRINTF("SELFTEST: Now the radio should transmit\n\r");
	

	/* Find out which region of world we are in and update region parm*/
	GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);
	
	
//	PRINTF("MY CURRENT LOCATION POLYGON : %d\n\r", (int)curr_poly_region);  
	PRINTF("APP DUTY CYCLE(TX INTERVAL maybe longer depending on message length and datarate) : %d\n\r", APP_TX_DUTYCYCLE);  


	while( 1 ){

		/* Configure the Lora Stack*/
		LORA_Init( &LoRaMainCallbacks, &LoRaParamInit); // sets up LoRa settings depending on the location we are in.
		
		/* update global variable that indicates that LoRa regional parameters are correct 
		 * TODO: clean up this implementation
		 * Call this update geofence
		 */
		geofence_init();


		/* Send a join request */
		#if RADIO_ENABLED
		LORA_Join();
		
		/* Init and start the tx interval timer */
		LoraStartTx( TX_ON_TIMER) ;

		#endif

		
	  /* Keep transmiting data packets every period defined by APP_TX_DUTYCYCLE */
		while( 1 )
		{
					
			if (AppProcessRequest==LORA_SET)
			{
				/*reset notification flag*/
				AppProcessRequest=LORA_RESET;

				/*Here lies the function to read sensor and GPS, parse and send it*/
				Send( NULL );
				/* if the tracker moves into another region, break out of main loop and 
				* reinit LoRa radio regional params
				*/
				if (!lora_settings_status){ 

					PRINTF("Breaking out of main loop to reinit LoRa regional settings\n\r");
					TimerStop( &TxTimer);
	
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
  uint16_t cayenne_pressure = 0;
  int16_t cayenne_temperature = 0;
  //uint16_t cayenne_humidity = 0;
  sensor_t sensor_data;
  int32_t cayenne_latitude = 0;
	int32_t cayenne_longitude = 0;
	int32_t cayenne_altitudeGps = 0;
  uint16_t cayenne_battery_voltage;
	uint8_t cayenne_GPS_sats;


  /* now join if not yet joined. */	
	#if RADIO_ENABLED
  if ( LORA_JoinStatus () != LORA_SET)
  {
    /* Go ahead and join */
    LORA_Join();
    return;
  }
	#endif
 
	/* Temporarily stop tx interval timer until GPS gets a lock */
	// TODO: this timerstop MUST be removed.
	TimerStop( &TxTimer);


	/* reading sensors and GPS */
  BSP_sensor_Read( &sensor_data );
	
	/* Restart tx interval timer */
	TimerStart( &TxTimer);



	/* Find out which region of world we are in */
	GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);
	
	/* reinit everything if it enters another LoRaWAN region. */
	if ((!lora_settings_status) ){
		TVL1(PRINTF("LoRa Regional settings incorrect. Data send terminated\n\r");)
		return;
	}
	
	/* Don't tx when over regions where we are not supposed to tx
   * There is currenly no region defined in geofence.h that prohibits tx.
   */
	if (GEOFENCE_no_tx){
		TVL1(PRINTF("Entered NO tx region. Data send terminated\n\r");)
		return;
	}
	
	
	

	
	/* Evaluate battery level */
  uint8_t cchannel=0;

  cayenne_temperature = ( int16_t )( sensor_data.temperature * 10 );     /* in °C * 10 */
  cayenne_pressure    = ( uint16_t )( sensor_data.pressure * 100 / 10 );  /* in hPa / 10 */
  //cayenne_humidity    = ( uint16_t )( sensor_data.humidity * 2 );        /* in %*2     */
  cayenne_battery_voltage = ( uint16_t )(sensor_data.battery_level16 / 10);    /* Battery level expressed in hundreds of mV */

	cayenne_altitudeGps = ( int32_t )( sensor_data.altitudeGps * 100 );
	cayenne_latitude = ( int32_t )( sensor_data.latitude * 10000 );
	cayenne_longitude = ( int32_t )( sensor_data.longitude * 10000 );
	cayenne_GPS_sats = ( uint8_t ) GPSsats;
	
	

	
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

	/* Using cayenne reference 
	 * https://github.com/MicrochipTech/Location-Tracking-using-SAMR34-and-UBLOX-GPS-Module/blob/master/src/CayenneLPP/lpp.c  
	 */
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
	
	#if RADIO_ENABLED
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
  /* Wait for next tx slot. 
	 * An interrupt service routine
	 * The timer, &TxTimer, calls this function after the elapsed time of length defined
	 * by APP_TX_DUTYCYCLE. Then this function tells the tracker that it is safe to transmit
   * now by setting AppProcessRequest.
	 * This function also restarts the timer so that it can get called again after
	 * the elapsed period.
	 */
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
{ /*  BOR Reset threshold levels for 1.7V - 1.8V VDD power supply */
	if ((FLASH_OB_GetBOR() & 0x0F) != OB_BOR_LEVEL1){
		HAL_FLASH_Unlock();
		/* Unlocks the option bytes block access */
		HAL_FLASH_OB_Unlock();
		/* Clears the FLASH pending flags */
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR |
		FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);
		/* Select The Desired V(BOR) Level------------------------*/
		FLASH_OB_BORConfig(OB_BOR_LEVEL1); 
		/* Launch the option byte loading and generate a System Reset */
		HAL_FLASH_OB_Launch();
		
		HAL_FLASH_Lock();
	}
}

/**
  * @brief  Configures the PVD resources.
  * @param  None
  * @retval None
  */
static void PVD_Config(void)
{
  /*##-1- Enable Power Clock #################################################*/
  __HAL_RCC_PWR_CLK_ENABLE();

  /*##-2- Configure the NVIC for PVD #########################################*/
  HAL_NVIC_SetPriority(PVD_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(PVD_IRQn);

  /* Configure the PVD Level to 5 and generate an interrupt on rising and falling
     edges(PVD detection level set to 2.9V) */
  sConfigPVD.PVDLevel = PWR_PVDLEVEL_5;  
  sConfigPVD.Mode = PWR_PVD_MODE_NORMAL;
  HAL_PWR_ConfigPVD(&sConfigPVD);

  /* Enable the PVD Output */
  HAL_PWR_EnablePVD();
}



/**
  * @brief  PWR PVD interrupt callback
  * @param  None
  * @retval None
  */
void HAL_PWR_PVDCallback(void)
{
  /* Toggle LED1 */
  BSP_LED_Toggle(LED1);
//	GPS_VOLTAGE_NOT_ABOVE_THRESHOLD = 1;
	
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
