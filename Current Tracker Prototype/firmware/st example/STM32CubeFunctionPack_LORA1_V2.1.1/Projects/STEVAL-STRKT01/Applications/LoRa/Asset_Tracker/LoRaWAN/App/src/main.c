/**
  ******************************************************************************
  * @file    STEVAL-STRKT01/Applications/LoRa/Asset_Tracker/LoRaWAN/App/src/main.c
  * @author  SRA - System Lab - Sensing & Connectivity Application Team
  * @version V2.1.1
  * @date    10-Oct-2019
  * @brief   This is the main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


  

/** @addtogroup PROJECTS PROJECTS
  * @{
  */
   
/** @defgroup STEVAL-STRKT01 STEVAL-STRKT01
  * @brief   This module provides the STEVAL-STRKT01 application
  * @{
  */  
   
/** @defgroup STEVAL-STRKT01_ASSET_TRACKER Asset Tracker
  * @{
  */    
    
/** @defgroup STEVAL-STRKT01_LoRaWAN LoRaWAN
  * @{
 */

/** @defgroup STEVAL-STRKT01_MAIN Main (STEVAL_STRKT01)
  * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "hw.h"
#include "low_power_manager.h"
#include "lora.h"
#include "bsp.h"
#include "timeServer.h"
#include "vcom.h"
#include "version.h"

#include "gnss_app_cfg.h"
#if (configUSE_FEATURE == 1)
#include "gnss_feature_cfg_data.h"
#endif /* configUSE_FEATURE */
#include "gnss_fw_upgrade.h"
#include "config_bus.h"

#ifdef LORA_SMART_TRACKER
#include "LoRaTracker_gnss.h"
#include "usb_user.h"
#include "loratracker_bus.h"
#include "loratracker_errno.h"
#include "loratracker_motion_sensors.h"
#include "loratracker_motion_sensors_ex.h"
#else //LORA_SMART_TRACKER
#include "x_nucleo_gnss1a1.h"
#include "x_nucleo_iks01a2_accelero.h"
#endif //LORA_SMART_TRACKER
#include "gnss_data.h"
#include "gnss_if.h"
#include "log_manager.h"

/** @addtogroup STEVAL-STRKT01_MAIN_Definition Main Constant Definition
  * @{
 */



/** @addtogroup STEVAL-STRKT01_MAIN_PRINTF_Definition PRINTF definitions
  * @{
 */

#define PRINTF_MAIN1(...)                       PRINTF(__VA_ARGS__)
#define PRINTF_MAIN2(...)                       PRINTF(__VA_ARGS__)
#if( OVER_THE_AIR_ACTIVATION != 0 )
#define CHECK_LORA_JOIN()                       (PlatformStatus.b.APP_LORA_JOINED == TRUE)
#else //( OVER_THE_AIR_ACTIVATION != 0 )
#define CHECK_LORA_JOIN()                       (LORA_JoinStatus () == LORA_SET)
#endif //( OVER_THE_AIR_ACTIVATION != 0 )
#define CHECK_OPERATIONS_PENDING()              ((LoraMacProcessRequest!=LORA_SET)      && \
                                                  (AppProcessRequest!=LORA_SET)         && \
                                                  (mems_int2_detected == 0)             && \
                                                  (tx_timer_event == 0)                 && \
                                                  (read_timer_event == 0)               && \
                                                  (sleep_timer_event == 0)              && \
                                                  (sensor_event == 0)                   && \
                                                  (GetUserButtonPushed() == 0) )
                                                    
#define GET_CONFIRM_MSG_STATE()                 ((PlatformStatus.b.LORA_ACK_ENABLED == 1)?LORAWAN_CONFIRMED_MSG:LORAWAN_UNCONFIRMED_MSG)

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_CAYENNE_LPP myDevices CAYENNE Application server
  * @{
 */

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

#define APPLICATION_READ_TIMER          1   /* Timer to periodically retrieve data from TESEO and sensors. Allowed values: 0 disabled, 1 (default) enabled */
#define TEST_BATTERY                    1   /* Enable periodical polling of battery voltage level. Allowed values: 0 (default) disabled, 1 enabled */
#define LOW_POWER_WITH_USB_CONNECTED    0   /* Low power allowed also with USB connected. Allowed values: 0 (default) disabled, 1 enabled */
#define TESEO_READ_TIMER                0   /* Timer to periodically poll TESEO for new data. Allowed values: 0 (default) disabled, 1 enabled */

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_SENSOR_THRSHLD Sensors thresholds
  * @{
 */

#define HUM_THRESH_HIGH  80
#define HUM_THRESH_LOW   20
#define TEMP_THRESH_HIGH 40
#define TEMP_THRESH_LOW  20
#define PRES_THRESH_HIGH 1100
#define PRES_THRESH_LOW  900

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_TIME_INTERVAL Time intervals and timeout values
  * @{
 */

#define BATTERY_READ_INTERVAL           5000
#define SENSOR_POLL_INTERVAL            10000

#define GNSS_CMD_DELAY                  (500)
#define GNSS_NUM_LOOPS_WITHOUT_DATA     (5)
#define WAIT_FOR_FIX_POLL_INTERVAL      (1000)
#define GNSS_NO_TIMEOUT                 (0)
#define GNSS_TIMEOUT_POLL               (2000)
#define GNSS_TIMEOUT_SEND               (60*1000)

/**
  * @}
  */

/** @addtogroup STEVAL-STRKT01_MAIN_DATA_RATE_SETTINGS Data trasmission settings
  * @ note Defines the application data transmission interval. 5s, value in [ms].
  * @{
 */
#define SEND_INTERVAL_FIRST_TIME                        10000

#define TESEO_READ_INTERVAL                             10000
#define SLEEP_TIMER_FIRST_TIME                          10000
#define SLEEP_TIMER_INTERVAL                            20000
#define N_PACKETS_SENT_BEFORE_LOW_POWER                 0       /* ToDo: 0 for power consumption tests. Original value: 2 */
#define MAX_TX_WITHOUT_LOW_POWER                        0
#define SEND_IDLE_INTERVAL                              10000
#define RESTART_MSG_INTERVAL                            10000

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_LoRaWAN_ADR LoRaWAN adaptive Data Rate
  * @ note Please note that when ADR is enabled the end-device should be static
  * @{
 */

#define LORAWAN_ADR_STATE                               LORAWAN_ADR_OFF

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_LoRaWAN_DDR LoRaWAN default Data Rate
  * @ note Please note that LORAWAN_DEFAULT_DATA_RATE is used only when ADR is disabled
  * @{
 */

#define LORAWAN_DEFAULT_DATA_RATE                       DR_4

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_LoRaWAN_APP_PORT LoRaWAN application port
  * @ note Do not use 224. It is reserved for certification
  * @{
 */

#define LORAWAN_APP_PORT                                2

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_LoRaWAN_ENDNODE_CLASS_PORT LoRaWAN default endNode class
  * @{
 */

#define LORAWAN_DEFAULT_CLASS                           CLASS_A

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_LoRaWAN_CONFIRM_STATE LoRaWAN default confirm state
  * @{
 */

#define LORAWAN_DEFAULT_CONFIRM_MSG_STATE               LORAWAN_UNCONFIRMED_MSG

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_LoRaWAN_DATA_BUFFER_SIZE LoRaWAN application data buffer size
  * @{
 */

#define LORAWAN_APP_DATA_BUFF_SIZE                      (64 + 4 + 2)  /*  Added bytes are: epochtime (4 bytes) + channel and datatype (2 bytes) */

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_MAIN_EEPROM_SETTINGS LoRaWAN Settings saved in internal EEPROM
  * @{
 */

#define USE_EEPROM_SETTINGS             1   /* Allowed values: 0 Application settings from code that are not changeble via USB, 1 (default) Application settings from EEPROM */ 

#define LOW_POWER_ON_SLEEP_TIMER_DEF    1   /* Low power on sleep timer expiration. Allowed values: 0 (default) disabled, 1 enabled */ 
#define LOW_POWER_ON_SENSOR_EVENT_DEF   1   /* Low power on accelerometer inactivity event. Allowed values: 0 disabled, 1 (default) enabled */
#define GNSS_WAIT_FIX_MODE_DEF          1   /* Allowed values: 0 GNSS_WAIT_FOR_DATA, 1 (default) GNSS_WAIT_FOR_FIX */
#define GNSS_FIX_CHECK_DEF              0   /* Allowed values: 0 (default) timeout, 1 infinite timeout */ 

#define SEND_ON_WAKE_EVENT_DEF          1   /* Trigger data sending on accelerometer wake-up event. Allowed values: 0 disabled, 1 (default) enabled */
#define SEND_ON_SENSOR_EVENT_DEF        1   /* Trigger data sending on environmental sensors threshold overshoot. Allowed values: 0 disabled, 1 (default) enabled */

#define GNSS_GEOFENCE_RADIUS_DEF        100 /* Geofence radius default value in meters */
#define GNSS_GEOFENCE_MASK_DEF          0   /* Mask to enable geofence demos: Allowe values: 0 (default) disabled, see ProcDbgSetGeoFence function for other values */

#define LOG_MANAGER_DEF                 0   /* Enable log manager. Allowed values: 0 (default) disabled, 1 enabled */
#define GPSTIME_IN_LPP_DEF              0   /* 'Include Epoch time' variable status. Allowed values: 0 (default) epoch time is not included and RTC is not updated, 1 epoch time is included and RTC is updated from gps time*/
   
#define LORA_DR_DEF                     LORAWAN_DEFAULT_DATA_RATE
#define LORA_ADR_DEF                    LORAWAN_ADR_STATE
#define SEND_INTERVAL_DEF               120000
#define TX_TIMER_INTERVAL_DEF           10000

#define SHORTEN_JOIN_REQ_INTV_DEF       1   /* Enable skip sensor read to speedup first LoRa join requests when not joined. Allowed values: 0 disabled, 1 (default) enabled */

#define LORA_ACK_ENABLED_DEF            LORAWAN_DEFAULT_CONFIRM_MSG_STATE

#define MAX_ERROR_NO_ACK                5

/**
  * @}
  */

/**
  * @}
  */ 



/** @addtogroup STEVAL-STRKT01_MAIN_Private_Variables Main Private Variables
  * @{
 */

/*!
 * User application data
 */
static uint8_t AppDataBuff[LORAWAN_APP_DATA_BUFF_SIZE];

static uint32_t lastSendTick = 0;
uint32_t last_mems_event,last_sensor_poll;
bool sensor_event = false;
uint32_t nStartSendTick = 0;
float gnss_latitude, gnss_longitude, gnss_altitude;
int32_t gnss_sats = 0;
uint8_t gnss_fix_validity = 0;
static uint8_t bSendCommandStore = 0;
static uint8_t bSendCommandGetpar = 0;
uint8_t bSendCommandGeofenceCfg = 0;
uint8_t bSendCommandGeofenceReq = 0;
uint8_t bSetRtcFirstTime = 0;

static const char geofenceCirclePosition[4][8] = {
  "Unknown",
  "Outside",
  "Boundary",
  "Inside"
};

static uint32_t nPacketsSent = 0;

static time_t nDeltaEpochTime = 0;

static uint8_t nTxWithoutLowPower = MAX_TX_WITHOUT_LOW_POWER;

bool read_timer_event, tx_timer_event, sleep_timer_event;

/*!
 * Specifies the state of the application LED
 */
static uint8_t AppLedStateOn = RESET;

/*!
 * Timer to handle the application Tx Led to toggle
 */
//static TimerEvent_t TxLedTimer;
static TimerEvent_t TxTimer;
static TimerEvent_t ReadTimer;
static TimerEvent_t SleepTimer;
#if defined(GNSS_ENABLED)
static TimerEvent_t TeseoReadTimer;
static uint8_t bTeseoRead = 0;
#endif //defined(GNSS_ENABLED)

/**
  * @}
  */ 

/** @addtogroup STEVAL-STRKT01_MAIN_Exported_Variables Main Exported Variables
  * @{
 */
/* Instance of GNSS Handler */
GNSS_HandleTypeDef pGNSS;
static GNSSParser_Data_t GNSSParser_Data;
uint8_t bGPGGA_Received = 0;
uint8_t bGPRMC_Received = 0;
uint8_t bPSTMVER_Received = 0;

#ifdef LORA_SMART_TRACKER
volatile uint8_t STUSB1600_int_detected    = 0;
volatile uint8_t STBC02_nCHG_int_detected  = 0;
extern LogData_t data_logged;
LogData_t data_logged;
#endif

uint8_t nLoraDR=0;
bool bLoraAck = FALSE;
bool bWaitAck = FALSE;

/**
  * @}
  */



/** @addtogroup STEVAL-STRKT01_MAIN_Private_function_prototypes Main Private function prototypes
  * @{
 */
static float convertCoord( float x, uint8_t sign );
static void LORA_RxData( lora_AppData_t *AppData);
static void LORA_HasJoined( void );
static void LORA_ConfirmClass ( DeviceClass_t Class );
static void LORA_TxNeeded ( void );
static uint8_t SendData( void );
static void Send( void* context );
static void LoraInitTxTimer( void );
static void OnTxTimerEvent( void*c );
static void LoraStartReadTimer(void);
static void ReloadReadTimer(void);
static void OnReadTimerEvent( void*c );
static void OnSleepTimerEvent( void*c );
static void InitSleepTimer( void );
static void ReloadSleepTimer(void);
void Board_GetDevEui( uint8_t *id );

/* tx timer callback function*/
static void LoraMacProcessNotify( void );

#if TESEO_READ_TIMER
static void OnTeseoReadTimerEvent( void );
static void TeseoReadTimerStart( void );
#endif//TESEO_READ_TIMER

#if defined(GNSS_ENABLED)
static void TeseoReadData( uint32_t nTimeout );
#endif

/* GNSS function prototypes */
static void GPIO_Config(void);
static void TeseoConsumerTask(void const * argument);

uint32_t App_GetTimeStamp(void);

/*!
 * Timer to handle the application Tx Led to toggle
 */
//static void OnTimerLedEvent( void*c );

void UserHwInit( void );
void UserProcess( void );

uint16_t GetFirstItemToSend( void );
uint8_t GetSingleItem(uint16_t nbitem);
void PushLogFlag(uint16_t nbitem);

void UserAuxFunction(void);
uint8_t CheckSensorsData(void);
void TeseoGeofenceCallback(uint8_t location, int32_t status);

/**
  * @}
  */ 

/** @addtogroup STEVAL-STRKT01_MAIN_Exported_Structures Main Exported Structures
  * @{
 */

/*!
 * User application data structure
 */
static lora_AppData_t AppData={ AppDataBuff,  0, 0 };

/* load Main call backs structure*/
static const LoRaMainCallback_t LoRaMainCallbacks = { BSP_GetBatteryLevel,
                                                HW_GetTemperatureLevel,
                                                Board_GetDevEui,
                                                HW_GetRandomSeed,
                                                LORA_RxData,
                                                LORA_HasJoined,
                                                LORA_ConfirmClass,
                                                LORA_TxNeeded,
                                                LoraMacProcessNotify};

LoraFlagStatus LoraMacProcessRequest=LORA_RESET;
LoraFlagStatus AppProcessRequest=LORA_RESET;

/* !
 *Initialises the Lora Parameters
 */
static  LoRaParam_t LoRaParamInit= {LORAWAN_ADR_STATE,
                                    LORAWAN_DEFAULT_DATA_RATE,  
                                    LORAWAN_PUBLIC_NETWORK};

/**
  * @}
  */

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
  
  PRINTF_MAIN1("SYSTEM STARTUP\r\n");
  
  /* Launch the auxiliary function */
  UserAuxFunction();
  
  /* Configure the hardware*/
  HW_Init();
  
  /* USER CODE BEGIN 1 */
  UserHwInit();
  /* USER CODE END 1 */
  
  /* Disable Stand-by mode*/
  LPM_SetOffMode(LPM_APPLI_Id, LPM_Disable );
  
  /* Configure the LoRa Stack*/
  LORA_Init( (void*)&LoRaMainCallbacks, &LoRaParamInit);
  
  PRINTF_MAIN1("VERSION: %X\r\n", VERSION);
  

	LORA_Join();
	
  
		
  PlatformStatus.s.xCurrentState = State_Run;
  lastSendTick = HAL_GetTick();
  
  LoraInitTxTimer( ) ;
  
#if APPLICATION_READ_TIMER
  LoraStartReadTimer( );
#endif //APPLICATION_READ_TIMER
  
  while( 1 )
  {
    if (AppProcessRequest==LORA_SET)
    {
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
    
    UserProcess();
  }
}

/** @addtogroup STEVAL-STRKT01_MAIN_Private_function Main Private functions
  * @{
 */

/**
  * @brief  LoraMacProcessNotify
  * @param  None
  * @retval None
  */
void LoraMacProcessNotify(void)
{
  LoraMacProcessRequest=LORA_SET;
}

/**
  * @brief  Get device EUI
  * @param  id Pointer to the ID
  * @retval None
  */
void Board_GetDevEui( uint8_t *id )
{
  HW_GetUniqueId(id);
  LoadLoraKeys();
}

/**
  * @brief  Teseo Console_Debug() implementation
  * @param  None
  * @retval None
  */
void TestLoraSmartTrackerTransmit(void)
{
  /* No console uart available on the tracker */
}

/**
  * @brief  User Auxiliary Function
  * @param  None
  * @retval None
  */
__weak void UserAuxFunction(void)
{
}

/**
  * @brief  User Auxiliary Function
  * @param  location: GEOFENCE_LECCE, GEOFENCE_CATANIA or GEOFENCE_CUR_COORDS
  * @retval None
  */
void TeseoGeofenceCallback(uint8_t location, int32_t status)
{
}

/**
  * @brief  Check sensors data to decide if return back to RUN state
  * @param  None
  * @retval 0: next state will be the previous state; 1: next state will be State_Run
  */
uint8_t CheckSensorsData()
{
  /* The user can add here a check on certain conditions to exit low power mode */
  return 0;
}

/**
  * @brief  Put Teseo in standby mode
  * @param  None
  * @retval None
  */
void TeseoStandby()
{
  if(GNSS_WAKEUP_GETSTATUS())
  {
    BSP_GnssWakeup(DISABLE);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMFORCESTANDBY,90000");
    BSP_GnssManageBootPins(3);
  }
}

/**
  * @brief  Wake up Teseo from standby mode using WAKEUP pin
  * @param  None
  * @retval None
  */
void TeseoWakeUp()
{
  if(GNSS_WAKEUP_GETSTATUS() == 0)
  {
    BSP_GnssWakeup(ENABLE);
  }
}

/**
  * @brief  Prepare hardware for low power mode
  * @param  None
  * @retval None
  */
void PrepareLowPower()
{
  ReloadSleepTimer();
#if GNSS_STANDBY_WAKEUP
  TeseoStandby();
#else//GNSS_STANDBY_WAKEUP
  BSP_PowerGNSS(DISABLE);
#endif //GNSS_STANDBY_WAKEUP
  BSP_sensor_Disable();
  LED_Off( LED_WHITE );
}

/**
  * @brief  Prepare hardware for ultra low power mode
  * @param  None
  * @retval None
  */
void PrepareUltraLowPower()
{
#if GNSS_STANDBY_WAKEUP
  TeseoStandby();
#else //GNSS_STANDBY_WAKEUP
  BSP_PowerGNSS(DISABLE);
#endif //GNSS_STANDBY_WAKEUP
  BSP_sensor_Disable();
  BSP_accelero_Disable();
  LED_Off( LED_WHITE );
}

/**
  * @brief  Led manager function
  * @param  None
  * @retval None
  */
void UserLedManager()
{
  static uint32_t nLedInterval = 500;
  static uint32_t nLastLedCheck = 0;
  if(PlatformStatus.s.xCurrentState == State_IdleAfterSend)
  {
    nLedInterval = 50;
  }
  else if ( CHECK_LORA_JOIN () )
  {
    nLedInterval = 100;
  }
  else
  {
    nLedInterval = 500;
  }
  if(HAL_GetTick() > nLedInterval + nLastLedCheck)
  {
    LED_Toggle( LED_WHITE );
    nLastLedCheck = HAL_GetTick();
  }
}

/**
  * @brief  Buttons manager function
  * @param  None
  * @retval None
  */
void UserButtonsManager()
{
  /* Buttons manager */

#ifdef LORA_SMART_TRACKER  
  /* USER button */
  if( GetUserButtonPushed() || BSP_PB_GetState( BUTTON_USER ) != 0)
  {
    PRINTF_MAIN1("USER BUTTON PUSHED\r\n");
    PRINTF_MAIN1("Keep pushed to shutdown\r\n");
    for(uint8_t i = 0; i < 10; i++)
    {
      LED_On( LED_WHITE );
      HAL_Delay(200);
      LED_Off( LED_WHITE );
      HAL_Delay(200);
      if(BSP_PB_GetState( BUTTON_USER ) == 0)break;
    }
    if(BSP_PB_GetState( BUTTON_USER ) != 0)
    {
      PRINTF_MAIN1("SENDING SHUTDOWN...\r\n");
      BSP_BoardShutdown();
      while(1)
      {
        PRINTF_MAIN1("Remove USB cable\r\n");
        LED_Toggle( LED_WHITE );
        HAL_Delay(2000);
      }
    }
    else
    {
      PRINTF_MAIN1("TRIGGER SEND DATA FROM BUTTON\r\n");
      PlatformStatus.s.xPrevState = PlatformStatus.s.xCurrentState;
      PlatformStatus.s.xNextState = State_Read;
      nTxWithoutLowPower = MAX_TX_WITHOUT_LOW_POWER;
    }
  }
  
  /* WAKE button */
  if( GetWakeButtonPushed() || BSP_PB_GetState( BUTTON_WAKE ) != 0)
  {
    PRINTF_MAIN1("WAKE BUTTON PUSHED, System Reset\r\n");
    for(uint8_t i = 0; i < 5; i++)
    {
      LED_On( LED_WHITE );
      HAL_Delay(200);
      LED_Off( LED_WHITE );
      HAL_Delay(200);
    }
    SystemResetHook();
  }
#else //LORA_SMART_TRACKER
  if( GetUserButtonPushed() )
  {
    PRINTF_MAIN1("USER BUTTON PUSHED\r\n");
    PRINTF_MAIN1("TRIGGER SEND DATA FROM BUTTON\r\n");
    PlatformStatus.s.xPrevState = PlatformStatus.s.xCurrentState;
    PlatformStatus.s.xNextState = State_Read;
    nTxWithoutLowPower = MAX_TX_WITHOUT_LOW_POWER;
  }
#endif //LORA_SMART_TRACKER
}

/**
  * @brief  Battery test
  * @param  None
  * @retval None
  */
void UserTestBattery()
{
#ifdef DEBUG
  uint8_t battery_charge_percentage = 0;
  float fBattLevel;
  uint8_t s;
  static uint32_t last_battery_read = 0;
  if ( HAL_GetTick() - last_battery_read > BATTERY_READ_INTERVAL )
  {
    last_battery_read = HAL_GetTick();
    /* Charger/battery management */
    s = BSP_GetChargerStatus();
    HAL_Delay(1000);
    s = BSP_GetChargerStatus();
    
    uint16_t battery_level16;
    battery_level16 = (uint16_t) BSP_GetBatteryLevel16();
    fBattLevel = (float)(battery_level16/1000.0);
    PRINTF_MAIN1("Battery voltage %.2f V\r\n", fBattLevel);
    battery_charge_percentage = BSP_BatteryChargePercentage(battery_level16);  
    PRINTF_MAIN1("Battery charge: %u%%\r\n", battery_charge_percentage);
    
    PrintChargerStatus(s);
  }
#endif //DEBUG
}

#if defined(GNSS_ENABLED)
/**
  * @brief  GNSS manager
  * @param  None
  * @retval None
*/
void UserGnssManager()
{
  if(bTeseoRead)
  {
    bTeseoRead = 0;
    TeseoReadData(GNSS_NO_TIMEOUT);
    TimerStart( &TeseoReadTimer);
  }
}
#endif //defined(GNSS_ENABLED)

/**
  * @brief  Mems interrupt manager 
  * @param  None
  * @retval bRetVal 
  */
uint8_t UserMemsInterruptManager()
{
  uint8_t bRetVal = 0;
  
#if !defined(LORA_SMART_TRACKER)
  
  //mems_int1_detected not managed in LORA_SMART_TRACKER
  if ((mems_int1_detected) && IS_STATE_NOT_LOCKED(PlatformStatus.s.xCurrentState))
  {
    /* WAKE UP DETECTION ON INT1 */
    bRetVal = 1;
    mems_int1_detected = 0;
    PRINTF_MAIN1(">> wake-up detected A\r\n");
    
#if 1
    if ( PlatformStatus.s.xCurrentState == State_Run ) 
      if (HAL_GetTick()-last_mems_event < 2000 )
      {
        PRINTF_MAIN2("%u\r\n",HAL_GetTick()-last_mems_event);
        mems_int1_detected = 0;
        return bRetVal;
      }
#endif
    LORA_TRACKER_MOTION_SENSOR_Event_Status_t status; 
    if (BSP_LORA_TRACKER_MOTION_SENSOR_Get_Event_Status(LORA_TRACKER_LIS2DW12_0, &status) == BSP_ERROR_NONE)
    {
      if (status.WakeUpStatus != 0)
      {
        PRINTF_MAIN1(">> wake-up detected B\r\n");
        last_mems_event = HAL_GetTick();
        if(PlatformStatus.b.SEND_ON_WAKE_EVENT)
        {
          PlatformStatus.s.xNextState = State_Read;
        }
      }
    }
  }
#endif //LORA_SMART_TRACKER
  
  if ((mems_int2_detected) && IS_STATE_NOT_LOCKED(PlatformStatus.s.xCurrentState))
  {
    /* ACTIVITY/INACTIVITY detection on INT2 */
    bRetVal = 1;
    mems_int2_detected = 0;
    PRINTF_MAIN1(">> accelerometer interrupt\r\n");
    
    if ( PlatformStatus.s.xCurrentState == State_Run )
    {
      if (HAL_GetTick()-last_mems_event < 2000U )
      {
        return bRetVal;
      }
    }
#if defined(SENSOR_ENABLED)
    LORA_TRACKER_MOTION_SENSOR_Event_Status_t status; 
    if(BSP_LORA_TRACKER_MOTION_SENSOR_Get_Event_Status(LORA_TRACKER_LIS2DW12_0, &status) == BSP_ERROR_NONE)
    {
      if  (status.SleepStatus!=0)
      {
        last_mems_event = HAL_GetTick();
        PRINTF_MAIN2("Accelerometer inactivity interrupt\r\n"); 
        accActInact = ACC_INACTIVITY;
        
        if(PlatformStatus.b.LP_SENSOR_EVENT)
        {
          if( LOW_POWER_WITH_USB_CONNECTED || PlatformStatus.b.USB_CONNECTED == 0 )
          {
            if ( PlatformStatus.s.xCurrentState == State_Run )
            {
              if(nTxWithoutLowPower==0)
              {
                PlatformStatus.s.xNextState = State_PrepareLowPower;
                PRINTF_MAIN1("--> Going low power (sensor event)...\r\n");
              }
            }
            else if ( PlatformStatus.s.xCurrentState == State_LowPower )
            {
              if(nTxWithoutLowPower==0)
              {
                PlatformStatus.s.xNextState = State_PrepareUltraLowPower;
                PRINTF_MAIN1("--> Going ultra low power (sensor event)...\r\n");
              }
            }
          }
        }
      }
      else
      {
        PRINTF_MAIN2("Accelerometer wake up interrupt\r\n"); 
        accActInact = ACC_ACTIVITY;
        PlatformStatus.s.xNextState = State_Run;
        if(PlatformStatus.b.SEND_ON_WAKE_EVENT)
        {
          PlatformStatus.s.xNextState = State_Read;
        }
      }
    }
#endif
  }
  return bRetVal;
}

/**
  * @brief  Read timer manager
  * @param  None
  * @retval None
  */
uint8_t UserReadTimerManager()
{
  uint8_t bRetVal = 0;
  
  if ((read_timer_event) && IS_STATE_NOT_LOCKED(PlatformStatus.s.xCurrentState))
  {
    
    bRetVal = 1;
    PRINTF_MAIN1(">> read_timer_event\r\n");
    read_timer_event = false;
    PlatformStatus.s.xPrevState = PlatformStatus.s.xCurrentState;
    PlatformStatus.s.xNextState = State_Read;
  }
  return bRetVal;
}

/**
  * @brief  Transmit timer manager
  * @param  None
  * @retval None
  */
uint8_t UserTxTimerManager()
{
  uint8_t bRetVal = 0;
  
  if ((tx_timer_event) && IS_STATE_NOT_LOCKED(PlatformStatus.s.xCurrentState))
  {
    bRetVal = 1;
    PRINTF_MAIN1(">> tx_timer_event\r\n");
    PlatformStatus.s.xPrevState = PlatformStatus.s.xCurrentState;
    PlatformStatus.s.xNextState = State_Send;
    tx_timer_event = false;
  }
  return bRetVal;
}

/**
  * @brief  Sleep timer manager
  * @param  None
  * @retval bRetVal 1 on sleep timer event, 0 otherwise
  */
uint8_t UserSleepTimerManager()
{
  uint8_t bRetVal = 0;
  if (sleep_timer_event)
  {
    bRetVal = 1;
    PRINTF_MAIN1(">> sleep_timer_event\r\n");
    sleep_timer_event = false;
    
    if( LOW_POWER_WITH_USB_CONNECTED || PlatformStatus.b.USB_CONNECTED == 0 )
    {
      if(PlatformStatus.b.LP_SLEEP_TIMER)
      {
        if ( PlatformStatus.s.xCurrentState == State_Run )
        {
          if(nTxWithoutLowPower==0)
          {
            ReloadSleepTimer();
            PlatformStatus.s.xNextState = State_PrepareLowPower;
            PRINTF_MAIN1("--> Going low power (timer event)...\r\n");
          }
        }
        else
        {
          if ( PlatformStatus.s.xCurrentState == State_LowPower )
          {
            if(nTxWithoutLowPower==0)
            {
              PlatformStatus.s.xNextState = State_PrepareUltraLowPower;
              PRINTF_MAIN1("--> Going ultra low power (timer event)...\r\n");
            }
          }
        }
      }
      else
      {
        PRINTF_MAIN1("PlatformStatus.b.LP_SLEEP_TIMER disabled\r\n");
      }
    }
  }
  return bRetVal;
}

/**
  * @brief  Environmental sensors manager
  * @param  None
  * @retval bRetVal
  */
uint8_t UserEnvSensorManager()
{
  uint8_t bRetVal = 0;
  if ((sensor_event) && IS_STATE_NOT_LOCKED(PlatformStatus.s.xCurrentState))
  {
    bRetVal = 1;
    PRINTF_MAIN1(">> sensor_event\r\n");
    sensor_event = 0;
    if(PlatformStatus.b.SEND_ON_SENSOR_EVENT)
    {
      PlatformStatus.s.xNextState = State_Read;
    }
  }
  return bRetVal;
}

/**
  * @brief  State machine process
  * @param  None
  * @retval None
  */
void UserStateMachine()
{
  if( (PlatformStatus.s.xCurrentState == State_LowPower ) || (PlatformStatus.s.xCurrentState == State_UltraLowPower ) )
  {
    if( PlatformStatus.b.USB_CONNECTED != 0 )
    {
      //wake up on usb connection
      if(!LOW_POWER_WITH_USB_CONNECTED)
      {
        PlatformStatus.s.xNextState = State_Run;
      }
    }
  }
  
  if(PlatformStatus.b.RESTART_PENDING)
  {
    static uint32_t last_restart_msg_tick = 0;
    if(HAL_GetTick() > last_restart_msg_tick + RESTART_MSG_INTERVAL)
    {
      last_restart_msg_tick = HAL_GetTick();
      PRINTF_MAIN1("* * * * * * * * * * * * * * * *\r\n");
      PRINTF_MAIN1("* * SYSTEM RESTART PENDING  * *\r\n");
      PRINTF_MAIN1("* * * * * * * * * * * * * * * *\r\n");
    }
  }
  
  if(PlatformStatus.s.xCurrentState != State_IdleAfterSend )
  {
    if( ( PlatformStatus.s.xCurrentState == State_CheckAck ) || ( PlatformStatus.s.xCurrentState == State_SaveData ) )
    {
      if( ( PlatformStatus.s.xPrevState == State_LowPower ) || (PlatformStatus.s.xPrevState == State_UltraLowPower ) )
      {
        if( LOW_POWER_WITH_USB_CONNECTED || PlatformStatus.b.USB_CONNECTED == 0 )
        {
          if(PlatformStatus.s.xPrevState == State_LowPower)
          {
            PlatformStatus.s.xNextState = State_PrepareLowPower;
          }
          if(PlatformStatus.s.xPrevState == State_UltraLowPower)
          {
            PlatformStatus.s.xNextState = State_PrepareUltraLowPower;
          }
        }
      }
      PlatformStatus.s.xPrevState = State_INVALID;
    }
    
    if( PlatformStatus.s.xNextState != State_INVALID && PlatformStatus.s.xCurrentState != PlatformStatus.s.xNextState)
    {
      PRINTF_MAIN1("State machine change: ");
      PrintSystemState(PlatformStatus.s.xNextState);
      PRINTF_MAIN1("\r\n");
      PlatformStatus.s.xCurrentState = PlatformStatus.s.xNextState;
    }
    PlatformStatus.s.xNextState = State_INVALID;
  }
  switch(PlatformStatus.s.xCurrentState)
  {
  case State_Read:
    nStartSendTick = HAL_GetTick();
#if APPLICATION_READ_TIMER
    ReloadReadTimer();
#endif //APPLICATION_READ_TIMER
  case State_ReadMems:
    {
      if( ( PlatformStatus.b.SHORTEN_JOIN_REQ_INTV==0 ) || ( CHECK_LORA_JOIN () || ( PlatformStatus.s.nErrorNoAck != 0 ) ) )
      {
#if defined(SENSOR_ENABLED)
        
        PRINTF_MAIN1("Enable and read sensors\r\n");
        PlatformStatus.s.xCurrentState = State_ReadMems;
        LED_On( LED_WHITE );
        BSP_sensor_Enable();
        BSP_accelero_Enable();
        
        BSP_sensor_Read( &sensor_data );
        PRINTF_MAIN1("Got sensor data: T: %.2f H: %.2f P: %.2f\r\n", sensor_data.temperature, sensor_data.humidity, sensor_data.pressure );
        PRINTF_MAIN1("Accelerometer: X: %d Y: %d Z: %d\r\n", sensor_data.acceleration_x, sensor_data.acceleration_y, sensor_data.acceleration_z );
#endif /* defined(SENSOR_ENABLED) */
      }
    }
    //no break, continue reading the other sensors
  case State_ReadGnss:
    {
      if( ( PlatformStatus.b.SHORTEN_JOIN_REQ_INTV==0 ) || ( CHECK_LORA_JOIN () || ( PlatformStatus.s.nErrorNoAck != 0 ) ) )
      {
#if defined(GNSS_ENABLED)
        PRINTF_MAIN2("Enable and read GNSS\r\n");
        PlatformStatus.s.xCurrentState = State_ReadGnss;
        TeseoReadData(GNSS_TIMEOUT_POLL);
        if( ( PlatformStatus.b.GNSS_WAIT_FIX ) && ( gnss_fix_validity == INVALID ) && ( HAL_GetTick() < ( nStartSendTick+GNSS_TIMEOUT_SEND )) )
        {
          PRINTF_MAIN1("Waiting for fix...\r\n");
          LED_Toggle( LED_WHITE );
          HAL_Delay(WAIT_FOR_FIX_POLL_INTERVAL);
          break;
        }
        if( ( PlatformStatus.b.GNSS_WAIT_FIX ) && ( gnss_fix_validity ) )
        {
          uint32_t elapsedtime = HAL_GetTick() - nStartSendTick;
          
          PRINTF_MAIN1("Waiting %dms for GPS fix\r\n", elapsedtime);
          PRINTF_MAIN1("Waiting %ds for GPS fix\r\n", elapsedtime/1000);
        }
#endif //defined(GNSS_ENABLED)
      }
    }
    //no break, continue saving the data
  case State_SaveData:
    {
      if( ( PlatformStatus.b.GNSS_FIX_CHECK && gnss_fix_validity != INVALID ) || PlatformStatus.b.GNSS_FIX_CHECK == 0)
      {
        if( ( PlatformStatus.b.SHORTEN_JOIN_REQ_INTV==0 ) || ( CHECK_LORA_JOIN () || ( PlatformStatus.s.nErrorNoAck != 0 ) ) )
        {
          PlatformStatus.s.xCurrentState = State_SaveData;
          data_logged.AccEnable = accActInact + 2*(gnss_fix_validity != INVALID);
          data_logged.temperature = ( int16_t )( sensor_data.temperature * 10 );      /* in °C * 10  */
          data_logged.pressure    = ( uint16_t )( sensor_data.pressure * 10 );        /* in hPa / 10 */
          data_logged.humidity    = ( uint16_t )( sensor_data.humidity * 2 );         /* in %*2      */
          
          data_logged.accelero_x  = ( int32_t )( sensor_data.acceleration_x );
          data_logged.accelero_y  = ( int32_t )( sensor_data.acceleration_y );
          data_logged.accelero_z  = ( int32_t )( sensor_data.acceleration_z );
          
          data_logged.latitude    = ( int32_t )( sensor_data.latitude * 10000 );
          data_logged.longitude   = ( int32_t )( sensor_data.longitude * 10000 );
          data_logged.altitudeGps = ( int32_t )( sensor_data.altitudeGps * 100 );
          
          data_logged.batteryLevel = (uint32_t) (BSP_GetBatteryLevel16()/10);
          data_logged.epoch_value = App_GetTimeStamp();
          data_logged.sentFlag = 0;
          
#ifdef MEMORY_ENABLED
          /* Sensors data and GNSS are store into EEPROM */
          if(PlatformStatus.b.LOG_MANAGER)
          {
            PRINTF_MAIN1("Save data...\r\n");
            LogEvent_Push_Printf(LOG_EV_NRM, "NRM_%c:%d:%d|%d|%d|%d|%d|%d|%d|%d", 'X', data_logged.sentFlag, data_logged.AccEnable, data_logged.temperature, data_logged.pressure, data_logged.humidity, data_logged.latitude, data_logged.longitude, data_logged.altitudeGps, data_logged.batteryLevel);
            PRINTF_MAIN1("\r\nTS:%d\r\n", App_GetTimeStamp());
            PlatformStatus.s.lastSavedIndex = LogEvent_GetCount(LOG_EV_NRM);
            PRINTF_MAIN1("Saved item %d\r\n", PlatformStatus.s.lastSavedIndex);
          }
#endif //MEMORY_ENABLED
        }
      }
    }
    if(tx_timer_event || TxTimer.IsStarted)
    {
      PlatformStatus.s.xNextState = State_Run;
      break;
    }
    if(CheckSensorsData())
    {
      PlatformStatus.s.xNextState = State_Run;
      break;
    }
    
  case State_Send: 
  case State_RetrieveData:
    {
#ifdef MEMORY_ENABLED
      /* Sensors data and GNSS are retrieved from EEPROM */
      if(PlatformStatus.b.LOG_MANAGER)
      {
        if(PlatformStatus.s.lastReadIndex == 0)
        {
          PlatformStatus.s.lastReadIndex = GetFirstItemToSend();
        }
        PRINTF_MAIN1("lastSavedIndex: %d - lastReadIndex: %d\r\n", PlatformStatus.s.lastSavedIndex, PlatformStatus.s.lastReadIndex);
        if(PlatformStatus.s.lastSavedIndex > PlatformStatus.s.lastReadIndex)
        {
          PRINTF_MAIN2("%d items to send\r\n", PlatformStatus.s.lastSavedIndex - PlatformStatus.s.lastReadIndex);
          PRINTF_MAIN1("Getting lastReadIndex: %d\r\n", PlatformStatus.s.lastReadIndex);
          GetSingleItem(PlatformStatus.s.lastReadIndex);
        }
        else
        {
          //nothing to send
          if ( CHECK_LORA_JOIN () )
          {
            PRINTF_MAIN2("No items to send\r\n");
            PlatformStatus.s.xNextState = State_Run;
            break;
          }
        }
      }
#endif //MEMORY_ENABLED
    }
  case State_SendData:
    {
      PlatformStatus.s.xCurrentState = State_SendData;
      LED_On( LED_WHITE );
      PRINTF_MAIN1("Send data...\r\n");
      lastSendTick = HAL_GetTick();
      bLoraAck = FALSE;
      if(SendData( ))
      {
        //send error
        PlatformStatus.s.xNextState = State_Run;
      }
      else
      {
        PlatformStatus.s.xNextState = State_IdleAfterSend;
        PlatformStatus.s.xCurrentState = State_IdleAfterSend;
      }
    }
    break;
  case State_CheckAck:
    {
      PlatformStatus.s.xNextState = State_Run;
      
      if ( CHECK_LORA_JOIN () )
      {
        if( (GET_CONFIRM_MSG_STATE() == LORAWAN_UNCONFIRMED_MSG) || (bWaitAck == 0) ||  (bLoraAck == 1) )
        {
          if(PlatformStatus.b.LOG_MANAGER)
          {
            if( (bLoraAck == 1) || ( GET_CONFIRM_MSG_STATE() == LORAWAN_UNCONFIRMED_MSG && bWaitAck != 0 ) )
            {
              /* LoRa Ack received, set flag in the saved item */
              PRINTF_MAIN1("LoRa ack received\r\n");
              PushLogFlag(PlatformStatus.s.lastReadIndex);
              PlatformStatus.s.nErrorNoAck=0;
              PlatformStatus.s.lastReadIndex++;
            }
            if(PlatformStatus.s.lastSavedIndex > PlatformStatus.s.lastReadIndex)
            {
              PRINTF_MAIN1("Set tx timer to flush data\r\n");
              TimerStop(&TxTimer);
              TimerSetValue(&TxTimer, PlatformStatus.s.TX_TIMER_INTERVAL);
              TimerStart(&TxTimer);
            }
          }
        }
        else
        {
          PRINTF_MAIN1("No LoRa ack, item will be resent\r\n");
          PRINTF_MAIN2("Set tx timer to flush data\r\n");
          TimerStop(&TxTimer);
          TimerSetValue(&TxTimer, PlatformStatus.s.TX_TIMER_INTERVAL);
          TimerStart(&TxTimer);
          if(PlatformStatus.s.nErrorNoAck < MAX_ERROR_NO_ACK)
          {
            PlatformStatus.s.nErrorNoAck++;
          }
          else
          {
            if(CHECK_LORA_JOIN())
            {
              PlatformStatus.b.APP_LORA_JOINED = FALSE;
              PRINTF_MAIN2("Network is down\r\n");
            }
          }
        }
        
        nPacketsSent++;
        if(nTxWithoutLowPower)nTxWithoutLowPower--;
      }
      
      ReloadSleepTimer();
    }
    break;
  case State_IdleAfterSend:
    if(HAL_GetTick() > lastSendTick + SEND_IDLE_INTERVAL)
    {
      PlatformStatus.s.xNextState = State_CheckAck;
      PlatformStatus.s.xCurrentState = State_INVALID;
    }
    break;
  case State_Run:
    {
      if ( HAL_GetTick() - last_sensor_poll > SENSOR_POLL_INTERVAL )
      {
        last_sensor_poll = HAL_GetTick();
        BSP_sensor_Enable();
        BSP_accelero_Enable();
        
        BSP_sensor_Read( &sensor_data );
        PRINTF_MAIN1("Got sensor data: T: %.2f H: %.2f P: %.2f\r\n", sensor_data.temperature, sensor_data.humidity, sensor_data.pressure );
        PRINTF_MAIN1("Accelerometer: X: %d Y: %d Z: %d\r\n", sensor_data.acceleration_x, sensor_data.acceleration_y, sensor_data.acceleration_z );
        if ( (sensor_data.humidity > HUM_THRESH_HIGH) || (sensor_data.humidity < HUM_THRESH_LOW) ||
            (sensor_data.temperature > TEMP_THRESH_HIGH) || (sensor_data.temperature < TEMP_THRESH_LOW) || 
              (sensor_data.pressure > PRES_THRESH_HIGH) || (sensor_data.pressure < PRES_THRESH_LOW) )
        {
          sensor_event = 1;
        }
        
        if(PlatformStatus.s.LORA_ADR)
        {
          PRINTF_MAIN2("LoRa ADR ON, DR %d, ack %d\r\n", nLoraDR, bLoraAck);
        }
        /* Uncomment following lines for debug purposes
        else
        {
        PRINTF_MAIN2("LoRa ADR OFF, DR %d, ack %d\r\n", nLoraDR, bLoraAck);
      }
        */
        
#if defined(GNSS_ENABLED)
        TeseoReadData(GNSS_NO_TIMEOUT);
#endif //defined(GNSS_ENABLED)
      }
    }
    break;
    
  case State_PrepareLowPower:
    {
      PrepareLowPower();
      PlatformStatus.s.xNextState = State_LowPower;
    }
    break;
  case State_LowPower:
    {
      HAL_Delay(500);
      LED_Off( LED_WHITE );
      
      LPM_SetOffMode(LPM_APPLI_Id, LPM_Disable );
      LPM_SetStopMode(LPM_APPLI_Id, LPM_Disable );
      /*If a flag is set at this point, mcu must not enter low power and must loop*/
    if( CHECK_OPERATIONS_PENDING() )
    {
      DISABLE_IRQ();
      SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk; /* Systick IRQ OFF */
      LPM_EnterLowPower();
      ENABLE_IRQ();
      SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; /* Systick IRQ ON */
    }
    }
    break;
    
  case State_PrepareUltraLowPower:
    {
      PrepareUltraLowPower();
      PlatformStatus.s.xNextState = State_UltraLowPower;
    }
    break;
  case State_UltraLowPower:
    {
      HAL_Delay(500);
      LED_Off( LED_WHITE );
      
      LPM_SetOffMode(LPM_APPLI_Id, LPM_Disable );
      LPM_SetStopMode(LPM_APPLI_Id, LPM_Enable );
      /*If a flag is set at this point, mcu must not enter low power and must loop*/
    if( CHECK_OPERATIONS_PENDING() )
    {
      DISABLE_IRQ();
      
      SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk; /* Systick IRQ OFF */
      LPM_EnterLowPower();
      ENABLE_IRQ();
      SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; /* Systick IRQ ON */
      
      
    }
    }
    break;
    
  default:
    {
      PlatformStatus.s.xNextState = State_Run;
      break;
    }
  }
}

/**
  * @brief  User hardware init
  * @param  None
  * @retval None
  */
void UserHwInit()
{
#if !defined(USE_AUX_UART_LOG)
  BSP_PB_Init( BUTTON_USER, BUTTON_MODE_EXTI );
#endif //!defined(USE_AUX_UART_LOG)
#ifdef LORA_SMART_TRACKER
  BSP_PB_Init( BUTTON_WAKE, BUTTON_MODE_EXTI );
#endif
  
#ifdef MEMORY_ENABLED
  if(PlatformStatus.b.EEPROM_FORMATTED)
  {
    LogEvent_Init(0);
  }
  if(PlatformStatus.b.LOG_MANAGER)
  {
    PlatformStatus.s.lastSavedIndex = LogEvent_GetCount(LOG_EV_NRM);
    PRINTF_MAIN1("Items in EEPROM: %d\r\n", PlatformStatus.s.lastSavedIndex);
    PlatformStatus.s.lastReadIndex = GetFirstItemToSend();
    PRINTF_MAIN1("Items sent: %d\r\n", PlatformStatus.s.lastReadIndex);
    PRINTF_MAIN1("Items to be sent: %d\r\n", PlatformStatus.s.lastSavedIndex - PlatformStatus.s.lastReadIndex);
  }
  
#endif //MEMORY_ENABLED
  
  PlatformStatus_t default_settings = {
    .nFwVersion = IOT_TRACKER_APP_VER,
    .b = {
      .LP_SLEEP_TIMER = LOW_POWER_ON_SLEEP_TIMER_DEF,
      .LP_SENSOR_EVENT = LOW_POWER_ON_SENSOR_EVENT_DEF,
      .LOG_MANAGER = LOG_MANAGER_DEF,
      .GNSS_WAIT_FIX = GNSS_WAIT_FIX_MODE_DEF,
      .GNSS_FIX_CHECK = GNSS_FIX_CHECK_DEF,
      .SEND_ON_WAKE_EVENT = SEND_ON_WAKE_EVENT_DEF,
      .SEND_ON_SENSOR_EVENT = SEND_ON_SENSOR_EVENT_DEF,
      .GPSTIME_IN_LPP = GPSTIME_IN_LPP_DEF,
      .SHORTEN_JOIN_REQ_INTV = SHORTEN_JOIN_REQ_INTV_DEF,
      .LORA_ACK_ENABLED = LORA_ACK_ENABLED_DEF,
      .EEPROM_DATA_CAN_BE_CHANGED = USE_EEPROM_SETTINGS
    },
    .s = {
      .GNSS_GEOFENCE_RADIUS = GNSS_GEOFENCE_RADIUS_DEF,
      .GNSS_GEOFENCE_MASK = GNSS_GEOFENCE_MASK_DEF,
      .LORA_DR = LORA_DR_DEF,
      .LORA_ADR = LORA_ADR_DEF,
      .SEND_INTERVAL = SEND_INTERVAL_DEF,
      .TX_TIMER_INTERVAL = TX_TIMER_INTERVAL_DEF
    },
  };

#if USE_EEPROM_SETTINGS
  /* Load default settings on eeprom if user button is pressed on startup */
  if(BSP_PB_GetState( BUTTON_USER ) != 0)
  {
    for(uint8_t i = 0; i < 20; i++)
    {
      LED_On( LED_WHITE );
      HAL_Delay(50);
      LED_Off( LED_WHITE );
      HAL_Delay(50);
      if(BSP_PB_GetState( BUTTON_USER ) == 0)break;
    }
    if(BSP_PB_GetState( BUTTON_USER ) != 0)
    {
      PRINTF_MAIN1("RESTORING DEFAULT EEPROM SETTINGS...\r\n");
      
      PlatformStatus.b.EEPROM_DATA_INITED = 0;
      
      for(uint8_t i = 0; i < 20; i++)
      {
        LED_On( LED_WHITE );
        HAL_Delay(50);
        LED_Off( LED_WHITE );
        HAL_Delay(50);
        if(BSP_PB_GetState( BUTTON_USER ) == 0)break;
      }
    }
  }
  
  /* Default platform status validation */
  BSP_PlatformStatus_Check(&default_settings);
  
  LoRaParamInit.AdrEnable = PlatformStatus.s.LORA_ADR;
  LoRaParamInit.TxDatarate = PlatformStatus.s.LORA_DR;
#else//USE_EEPROM_SETTINGS
  
  PlatformStatus.nFwVersion = IOT_TRACKER_APP_VER;
  
  PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED = default_settings.b.EEPROM_DATA_CAN_BE_CHANGED;
  PlatformStatus.b.LP_SLEEP_TIMER = default_settings.b.LP_SLEEP_TIMER;
  PlatformStatus.b.LP_SENSOR_EVENT = default_settings.b.LP_SENSOR_EVENT;
  PlatformStatus.b.LOG_MANAGER = default_settings.b.LOG_MANAGER;
  PlatformStatus.b.GNSS_WAIT_FIX = default_settings.b.GNSS_WAIT_FIX;
  PlatformStatus.b.GNSS_FIX_CHECK = default_settings.b.GNSS_FIX_CHECK;
  PlatformStatus.b.SEND_ON_WAKE_EVENT = default_settings.b.SEND_ON_WAKE_EVENT;
  PlatformStatus.b.SEND_ON_SENSOR_EVENT = default_settings.b.SEND_ON_SENSOR_EVENT;
  PlatformStatus.b.GPSTIME_IN_LPP = default_settings.b.GPSTIME_IN_LPP;
  PlatformStatus.b.SHORTEN_JOIN_REQ_INTV = default_settings.b.SHORTEN_JOIN_REQ_INTV;
  PlatformStatus.b.LORA_ACK_ENABLED = default_settings.b.LORA_ACK_ENABLED;
  
  PlatformStatus.s.GNSS_GEOFENCE_MASK = default_settings.s.GNSS_GEOFENCE_MASK;
  PlatformStatus.s.GNSS_GEOFENCE_RADIUS = default_settings.s.GNSS_GEOFENCE_RADIUS;
  PlatformStatus.s.LORA_DR = default_settings.s.LORA_DR;
  PlatformStatus.s.LORA_ADR = default_settings.s.LORA_ADR;
  PlatformStatus.s.SEND_INTERVAL = default_settings.s.SEND_INTERVAL;
  PlatformStatus.s.TX_TIMER_INTERVAL = default_settings.s.TX_TIMER_INTERVAL;
  
#endif //USE_EEPROM_SETTINGS
  
  PlatformStatus.s.xCurrentState = State_Run;
  PlatformStatus.s.xNextState = State_INVALID;
  PlatformStatus.s.xPrevState = State_INVALID;
  PlatformStatus.b.APP_LORA_JOINED = FALSE;
  PlatformStatus.s.nErrorNoAck = 0;

  GPIO_Config();
  
  /* Single instance for the GPS driver */
#if defined(GNSS_ENABLED)
#if (configUSE_I2C == 1)
  GNSS_I2C_Init();
  GNSS_Init(&pGNSS, GNSS_BUS_I2C);
#else
  GNSS_UART_Init(GNSS_UART_BAUD_RATE);
  GNSS_Init(&pGNSS, GNSS_BUS_UART);
#endif /* configUSE_I2C */
  
#ifdef LORA_SMART_TRACKER
  //no console huart for GNSS
#else //LORA_SMART_TRACKER
  IO_UART_Init();
#endif //LORA_SMART_TRACKER
#endif //defined(GNSS_ENABLED)

  InitSleepTimer();
  
#if TESEO_READ_TIMER
    TeseoReadTimerStart();
#endif //TESEO_READ_TIMER

  last_mems_event = last_sensor_poll = HAL_GetTick();
}

/**
  * @brief  Main loop process
  * @param  None
  * @retval None
  */
void UserProcess()
{
  UserLedManager();
  if( PlatformStatus.s.xCurrentState != State_IdleAfterSend )
  {
#ifdef USB_ENABLED
    FlushSafePrintf();
#endif //USB_ENABLED
    if( PlatformStatus.s.xCurrentState != State_INVALID )
    {
      //UserButtonsManager();
      
#if TEST_BATTERY
      UserTestBattery();
#endif //TEST_BATTERY
      
#if defined(GNSS_ENABLED)
      UserGnssManager();
#endif //defined(GNSS_ENABLED)
      
#if LORA_SMART_TRACKER
#ifdef USB_ENABLED
      ProcessTerminalString();
#endif /*USB_ENABLED*/
      SystemInterruptManager();
#endif
      
      if(UserMemsInterruptManager() == 0)
      {
        if(UserTxTimerManager() == 0)
        {
          if(UserReadTimerManager() == 0)
          {
            if(UserSleepTimerManager() == 0)
            {
              if(UserEnvSensorManager() == 0)
              {
              }
            }
          }
        }
      }
    }
  }
  
  UserStateMachine();
}

/**
  * @brief  Call back when LoRa endNode has just joined
  * @param  None
  * @retval None
  */
static void LORA_HasJoined( void )
{
#if( OVER_THE_AIR_ACTIVATION != 0 )
  PRINTF_SAFE("JOINED\r\n");
  PlatformStatus.b.APP_LORA_JOINED = TRUE;
  PlatformStatus.s.nErrorNoAck = 0;
#endif /* OVER_THE_AIR_ACTIVATION */
  LORA_RequestClass( LORAWAN_DEFAULT_CLASS );
}

/**
  * @brief  LoRa endNode send request
  * @param  None
  * @retval None
  */
static void Send( void* context )
{
  SendData();
}

/**
  * @brief  LoRa endNode send request
  * @param  None
  * @retval None
  */
static uint8_t SendData( void )
{
  uint16_t pressure = 0;
  int16_t temperature = 0;
  uint16_t humidity = 0;
  int32_t latitude=0, longitude = 0, altitudeGps=0;
  int32_t epoch_value =0;
  int32_t accelero_x, accelero_y, accelero_z; 
  uint16_t battery_level16;
  uint16_t battery_voltage;
  uint8_t battery_charge_percentage = 0;
  
  if ( CHECK_LORA_JOIN () != LORA_SET)
  {
    PRINTF_MAIN1("Not joined, sending join request\r\n");
    bWaitAck = FALSE;
    LORA_Join();
    return 0;
  }
  
  bWaitAck = TRUE;
  
  PRINTF_MAIN1("SEND REQUEST\r\n");
  
//  TimerInit( &TxLedTimer, OnTimerLedEvent );
  
//  TimerSetValue(  &TxLedTimer, 200);
  
  BSP_LED_On( LED_RED1 ) ; 
  
//  TimerStart( &TxLedTimer );  

  /* Evaluate battery level */
  battery_level16 = (uint16_t) BSP_GetBatteryLevel16();
  battery_charge_percentage = BSP_BatteryChargePercentage(battery_level16);  
  
  uint8_t cchannel=0;
  temperature = data_logged.temperature; 
  pressure    = data_logged.pressure; 
  humidity    = data_logged.humidity; 
  latitude    = data_logged.latitude; 
  longitude   = data_logged.longitude;;
  altitudeGps = data_logged.altitudeGps; 
  epoch_value = data_logged.epoch_value; 
  
  accelero_x =  ( int32_t )( data_logged.accelero_x );  
  accelero_y =  ( int32_t )( data_logged.accelero_y ); 
  accelero_z =  ( int32_t )( data_logged.accelero_z ); 
  
  battery_voltage = (uint16_t) (battery_level16/10);               /* Battery level expressed in hundreds of mV */
  
  uint32_t i = 0;

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

  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_ACCELEROMETER;
  AppData.Buff[i++] = ( accelero_x >> 8 ) & 0xFF;
  AppData.Buff[i++] = accelero_x & 0xFF;
  AppData.Buff[i++] = ( accelero_y >> 8 ) & 0xFF;
  AppData.Buff[i++] = accelero_y & 0xFF;
  AppData.Buff[i++] = ( accelero_z >> 8 ) & 0xFF;
  AppData.Buff[i++] = accelero_z & 0xFF;
  
#if defined( REGION_US915 ) || defined ( REGION_AU915 )
  if(PlatformStatus.s.LORA_DR > DR_3)
  {
#endif //defined( REGION_US915 ) || defined ( REGION_AU915 )
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_GPSLOCATION;
  AppData.Buff[i++] = ( latitude >> 16 ) & 0xFF;
  AppData.Buff[i++] = ( latitude >> 8 ) & 0xFF;
  AppData.Buff[i++] = latitude & 0xFF;
  AppData.Buff[i++] = ( longitude >> 16 ) & 0xFF;
  AppData.Buff[i++] = ( longitude >> 8 ) & 0xFF;
  AppData.Buff[i++] = longitude & 0xFF;
  AppData.Buff[i++] = ( altitudeGps >> 16 ) & 0xFF;
  AppData.Buff[i++] = ( altitudeGps >> 8 ) & 0xFF;
  AppData.Buff[i++] = altitudeGps & 0xFF;
#if defined( REGION_US915 ) || defined ( REGION_AU915 )
  }
#endif //defined( REGION_US915 ) || defined ( REGION_AU915 )
  
#if defined( REGION_US915 ) || defined ( REGION_AU915 )
  /* The maximum payload size does not allow to send more data for lowest DRs */
	UNUSED(battery_voltage);
#else
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_ANALOG_INPUT;
  AppData.Buff[i++] = ( battery_voltage >> 8 ) & 0xFF;
  AppData.Buff[i++] = battery_voltage & 0xFF;
  
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_DIGITAL_OUTPUT; 
  AppData.Buff[i++] = AppLedStateOn;
  
  if(PlatformStatus.b.GPSTIME_IN_LPP)
  {
    AppData.Buff[i++] = cchannel++;
    AppData.Buff[i++] = LPP_DATATYPE_GPSTIME;
    AppData.Buff[i++] = ((epoch_value>>24) & 0xFF);  // MSB value
    AppData.Buff[i++] = ((epoch_value>>16) & 0xFF);   
    AppData.Buff[i++] = ((epoch_value>>8) & 0xFF);   
    AppData.Buff[i++] = (epoch_value & 0xFF);        // LSB value
  }
#endif  /* REGION_XX915 */
  
  AppData.BuffSize = i;

  PRINTF_MAIN1("SENDING:\r\n");
  PRINTF_MAIN1("  Battery voltage: %.2fV\r\n", (float)battery_level16/1000.0);
  PRINTF_MAIN1("  Battery charge: %u%%\r\n", battery_charge_percentage);
  
  PRINTF_MAIN1("  T: %.2f H: %.2f P: %.2f\r\n", sensor_data.temperature, sensor_data.humidity, sensor_data.pressure );
  PRINTF_MAIN1("  Accelerometer: X: %d Y: %d Z: %d\r\n", sensor_data.acceleration_x, sensor_data.acceleration_y, sensor_data.acceleration_z );
  PRINTF_MAIN1("  LAT:%.4f LON:%.4f ALT:%.2f\r\n", sensor_data.latitude, sensor_data.longitude, sensor_data.altitudeGps );
  PRINTF_MAIN1("  epoch_value:%d \r\n", epoch_value);
 
  uint8_t RetVal = LORA_send( &AppData, GET_CONFIRM_MSG_STATE());
  if(RetVal)
  {
    PRINTF_SAFE("Send ERROR\r\n");
  }
  
  return RetVal;
}


/**
  * @brief  Call back when LoRa endNode has received a frame
  * @param  AppData, pointer to Application Data structure 
  * @retval None
  */
static void LORA_RxData( lora_AppData_t *AppData )
{
  PRINTF_MAIN1("PACKET RECEIVED ON PORT %d\r\n", AppData->Port);

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
        PRINTF_MAIN1("LED OFF\r\n");
        BSP_LED_Off( LED_BLUE ) ; 
      }
      else
      {
        PRINTF_MAIN1("LED ON\r\n");
        BSP_LED_On( LED_BLUE ) ; 
      }
    }
    break;
  case LPP_APP_PORT:
  {
    AppLedStateOn= (AppData->Buff[2] == 100) ?  0x01 : 0x00;
    if ( AppLedStateOn == RESET )
    {
      PRINTF_MAIN1("LED OFF\r\n");
      BSP_LED_Off( LED_BLUE ) ; 
      
    }
    else
    {
      PRINTF_MAIN1("LED ON\r\n");
      BSP_LED_On( LED_BLUE ) ; 
    }
    break;
  }
  default:
    break;
  }
}


/**
  * @brief  Tx timer callback function
  * @param  None
  * @retval None
  */
static void OnTxTimerEvent( void*c )
{
  tx_timer_event = true;
}


/**
  * @brief  Start the tx process
  * @param  None
  * @retval None
  */
static void LoraInitTxTimer( )
{
    /* send everytime timer elapses */
    TimerInit( &TxTimer, OnTxTimerEvent );
    TimerSetValue( &TxTimer, PlatformStatus.s.TX_TIMER_INTERVAL);
}

/**
  * @brief  Read timer callback function
  * @param  None
  * @retval None
  */
static void OnReadTimerEvent( void*c )
{
  read_timer_event  = true;
}

/**
  * @brief  Reload read timer
  * @param  None
  * @retval None
  */
static void ReloadReadTimer(void)
{
    TimerStop(&ReadTimer);
    TimerSetValue(&ReadTimer, PlatformStatus.s.SEND_INTERVAL);
    TimerStart(&ReadTimer);
}

/**
  * @brief  Start the sensors read process
  * @param  None
  * @retval None
  */
static void LoraStartReadTimer()
{
    /* send everytime timer elapses */
    TimerInit( &ReadTimer, OnReadTimerEvent );
    TimerSetValue( &ReadTimer,  SEND_INTERVAL_FIRST_TIME);
    OnReadTimerEvent(NULL);
}

/**
  * @brief  Call back when LoRa endNode has just switch the class
  * @param  None
  * @retval None
  */
static void LORA_ConfirmClass ( DeviceClass_t Class )
{
  PRINTF_MAIN1("switch to class %c done\r\n","ABC"[Class] );

  /*Optionnal*/
  /*informs the server that switch has occurred ASAP*/
  AppData.BuffSize = 0;
  AppData.Port = LORAWAN_APP_PORT;
  
  LORA_send( &AppData, LORAWAN_UNCONFIRMED_MSG);
}


/**
  * @brief  Call back when server needs endNode to send a frame
  * @param  None
  * @retval None
  */
static void LORA_TxNeeded ( void )
{
  AppData.BuffSize = 0;
  AppData.Port = LORAWAN_APP_PORT;
  
  LORA_send( &AppData, LORAWAN_UNCONFIRMED_MSG);
}

//static void OnTimerLedEvent( void*c )
//{
//#ifdef LORA_SMART_TRACKER
//  
//#else //LORA_SMART_TRACKER
//  PRINTF_MAIN1(">> led event\r\n");
//#endif //LORA_SMART_TRACKER
//}


/**
  * @brief  Config GPIO
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
#if GNSS_STANDBY_WAKEUP
   GPIO_InitTypeDef GPIO_InitStruct;
  
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
#if 0
  /* Configure GPIO pin Output Level */
  GNSS_RST_PIN_SET();
  
  /* Configure Reset */
  GPIO_InitStruct.Pin = GNSS_RST_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GNSS_RST_PORT, &GPIO_InitStruct);
#endif
  
  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GNSS_WAKEUP_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GNSS_WAKEUP_PORT, &GPIO_InitStruct);
#endif //GNSS_STANDBY_WAKEUP
}


/**
  * @brief  Send commands to configure the TESEO: get sw version, Set/get geofence status, configure NMEA message list
  * @param  None
  * @retval None
  */
uint8_t TeseoManageCommands()
{
  uint8_t nRetVal = 0;
  
  if(GNSSParser_Data.pstmver_data.pstmver_string[0] == 0)
  {
    PRINTF_MAIN1("TESEO GETVER\r\n");
//    $PSTMGETSWVER,<id><cr><lf>
//    Depending on the value of the <lib_id> parameter, the following version numbering is delivered by the command:
//    0 = GNSS Library Version
//    1 = OS20 Version
//    2 = SDK App Version
//    4 = WAAS Version
//    6 = Binary Image Version
//    7 = STA8088 HW version
//    254 = configuration data block
//    255 = all versions strings (as reported at the NMEA startup).
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETSWVER,6");
    HAL_Delay(1000);
    TeseoConsumerTask(NULL);
    nRetVal = 1;
    if(GNSSParser_Data.pstmver_data.pstmver_string[0] != 0)
    {
      PRINTF_MAIN1("GNSS FW version: ");
      PRINTF_MAIN1((char const*)GNSSParser_Data.pstmver_data.pstmver_string);
      PRINTF_MAIN1("\r\n");
    }
  }
  
  if(bSendCommandStore)
  {
    PRINTF_MAIN1("TESEO store params\r\n");
    bSendCommandStore = 0;
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1201,42");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1210,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1211,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1228,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1229,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1230,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSAVEPAR\r\n");
    TeseoConsumerTask(NULL);
    nRetVal = 1;
  }
  
  if(bSendCommandGetpar)
  {
    PRINTF_MAIN1("TESEO get params\r\n");
    bSendCommandGetpar = 0;
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1201"); //default 0x00980056
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1210"); //default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1211"); //default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1228"); //default 0x00020000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1229"); //default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1230"); //default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1268"); //default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    TeseoConsumerTask(NULL);
    nRetVal = 1;
  }
  
  if(bSendCommandGeofenceCfg)
  {
    //cfg5 use predefined coords on id 5
    GNSSGeofence_t Geofence_DataSTLecce = {
      .id = GEOFENCE_LECCE,
      .enabled = 0,
      .tolerance = 1,
      .lat = 40.336055,
      .lon = 18.120611,
      .radius = 200,
      .status = 0
    };
    Geofence_DataSTLecce.radius = PlatformStatus.s.GNSS_GEOFENCE_RADIUS;
    
    //cfg6 use predefined coords on id 6
    GNSSGeofence_t Geofence_DataSTCatania = {
      .id = GEOFENCE_CATANIA,
      .enabled = 0,
      .tolerance = 1,
      .lat = 37.4908266,
      .lon = 15.0073063,
      .radius = 200,
      .status = 0
    };
    Geofence_DataSTCatania.radius = PlatformStatus.s.GNSS_GEOFENCE_RADIUS;
    
    //cfg7, use current coords on id 7 if fix is valid
    GNSSGeofence_t Geofence_DataCur = {
      .id = GEOFENCE_CUR_COORDS,
      .enabled = 0,
      .tolerance = 1,
      .lat = 37.4908266,
      .lon = 15.0073063,
      .radius = 200,
      .status = 0
    };
    Geofence_DataCur.radius = PlatformStatus.s.GNSS_GEOFENCE_RADIUS;
    
    switch(bSendCommandGeofenceCfg)
    {
    case 1:
      {
        //disable geofence
        PRINTF_MAIN1("Config GeoFence OFF\r\n");
        GNSS_DATA_EnableGeofence(&pGNSS, 0);
        HAL_Delay(GNSS_CMD_DELAY);
        GNSS_DATA_SendCommand(&pGNSS, "$PSTMSAVEPAR\r\n");
        HAL_Delay(GNSS_CMD_DELAY);
        GNSS_DATA_ConfigGeofence(&pGNSS, &Geofence_DataSTLecce);
        HAL_Delay(GNSS_CMD_DELAY);
        GNSS_DATA_ConfigGeofence(&pGNSS, &Geofence_DataSTCatania);
        HAL_Delay(GNSS_CMD_DELAY);
        GNSS_DATA_ConfigGeofence(&pGNSS, &Geofence_DataCur);
        HAL_Delay(GNSS_CMD_DELAY);
        TeseoConsumerTask(NULL);
        nRetVal = 1;
        PlatformStatus.s.GNSS_GEOFENCE_MASK = 0;
        bSendCommandGeofenceCfg = 0;
        BSP_SavePlatformStatusToEeprom();
      }
      break;
    case GEOFENCE_LECCE:
    case GEOFENCE_CATANIA:
    case GEOFENCE_CUR_COORDS:
      {
        int gnss_feature = 0x0;
#if (configUSE_GEOFENCE == 1)
        gnss_feature |= GEOFENCE;
#endif /* configUSE_GEOFENCE */
        
        GNSS_DATA_EnableGeofence(&pGNSS, 1);
        HAL_Delay(GNSS_CMD_DELAY);
        GNSS_DATA_SendCommand(&pGNSS, "$PSTMSAVEPAR\r\n");
        HAL_Delay(GNSS_CMD_DELAY);
        GNSS_DATA_CfgMessageList(&pGNSS, 0x000000, gnss_feature);
        HAL_Delay(GNSS_CMD_DELAY);
        if(bSendCommandGeofenceCfg == GEOFENCE_LECCE)
        {
          PRINTF_MAIN1("ST Lecce (R=%d) coords: %f %c, %f %c\r\n", 
                            (int32_t)Geofence_DataSTLecce.radius, 
                            ABS(Geofence_DataSTLecce.lat), LAT_NORD_SUD(Geofence_DataSTLecce.lat), 
                            ABS(Geofence_DataSTLecce.lon), LON_EAST_WEST(Geofence_DataSTLecce.lon));
          Geofence_DataSTLecce.enabled = 1;
          GNSS_DATA_ConfigGeofence(&pGNSS, &Geofence_DataSTLecce);
          HAL_Delay(GNSS_CMD_DELAY);
          PlatformStatus.s.GNSS_GEOFENCE_MASK |= 1<<Geofence_DataSTLecce.id;
        }
        if(bSendCommandGeofenceCfg == GEOFENCE_CATANIA)
        {
          PRINTF_MAIN1("ST Catania (R=%d) coords: %f %c, %f %c\r\n", 
                            (int32_t)Geofence_DataSTCatania.radius, 
                            ABS(Geofence_DataSTCatania.lat), LAT_NORD_SUD(Geofence_DataSTCatania.lat), 
                            ABS(Geofence_DataSTCatania.lon), LON_EAST_WEST(Geofence_DataSTCatania.lon));
          Geofence_DataSTCatania.enabled = 1;
          GNSS_DATA_ConfigGeofence(&pGNSS, &Geofence_DataSTCatania);
          HAL_Delay(GNSS_CMD_DELAY);
          PlatformStatus.s.GNSS_GEOFENCE_MASK |= 1<<Geofence_DataSTCatania.id;
        }
        if(bSendCommandGeofenceCfg == GEOFENCE_CUR_COORDS)
        {
          PRINTF_MAIN1("Config GeoFence HERE\r\n");
          nRetVal = 1;
          Geofence_DataCur.lat = PlatformStatus.s.GNSS_GEOFENCE_LAT;
          Geofence_DataCur.lon = PlatformStatus.s.GNSS_GEOFENCE_LON;
          PRINTF_MAIN1("Geofence (R=%d) coords: %f %c, %f %c\r\n", 
                            (int32_t)Geofence_DataCur.radius, 
                            ABS(Geofence_DataCur.lat), LAT_NORD_SUD(Geofence_DataCur.lat), 
                            ABS(Geofence_DataCur.lon), LON_EAST_WEST(Geofence_DataCur.lon));
          Geofence_DataCur.enabled = 1;
          GNSS_DATA_ConfigGeofence(&pGNSS, &Geofence_DataCur);
          HAL_Delay(GNSS_CMD_DELAY);
          PlatformStatus.s.GNSS_GEOFENCE_MASK |= 1<<Geofence_DataCur.id;
        }

        TeseoConsumerTask(NULL);
        nRetVal = 1;
        BSP_SavePlatformStatusToEeprom();
        bSendCommandGeofenceCfg = 0;
      }
      break;
    default:
      bSendCommandGeofenceCfg = 0;
      break;
    }
  }
  
  if(bSendCommandGeofenceReq)
  {
    PRINTF_MAIN1("GET GEOFENCE STATUS\r\n");
    bSendCommandGeofenceReq = 0;
    
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGEOFENCEREQ\r\n");
    HAL_Delay(GNSS_CMD_DELAY);
    TeseoConsumerTask(NULL);
    nRetVal = 1;
  }
  
  if(!nRetVal)
  {
    TeseoConsumerTask(NULL);
  }
  
  return nRetVal;
}

/**
  * @brief  Convert date and time to epoch time
  * @param  None
  * @retval Epoch time
  */
uint32_t ConvertToEpochTime(RTC_TimeTypeDef *RTC_TimeStruct, RTC_DateTypeDef *RTC_DateStruct)
{
  struct tm t;
  
  t.tm_year = 2000+RTC_DateStruct->Year-1900;  // Year - 1900
  t.tm_mon = RTC_DateStruct->Month-1;           // Month, where 0 = jan
  t.tm_mday = RTC_DateStruct->Date;          // Day of the month
  t.tm_hour = RTC_TimeStruct->Hours;
  t.tm_min = RTC_TimeStruct->Minutes;
  t.tm_sec = RTC_TimeStruct->Seconds;
  t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
  uint32_t t_of_day = mktime(&t);
  return t_of_day;
}

/**
  * @brief  Get Timestamp
  * @param  None
  * @retval Timestamp
  */
uint32_t App_GetTimeStamp()
{
  RTC_TimeTypeDef RTC_TimeStruct;
  RTC_DateTypeDef RTC_DateStruct;
  time_t t_of_day;
  
  HW_RTC_GetTimeValue(&RTC_TimeStruct);
  HW_RTC_GetDateValue(&RTC_DateStruct);
  t_of_day = ConvertToEpochTime(&RTC_TimeStruct, &RTC_DateStruct);
  t_of_day = t_of_day + nDeltaEpochTime;
  return t_of_day;
}

/**
  * @brief  TeseoConsumerTask function
  * @param  const * argument
  * @retval None
  */
void TeseoConsumerTask(void const * argument)
{
  int gnss_feature = 0x0;
  GNSSParser_Status_t status, check;
  const GNSS_MsgTypeDef *gnssMsg;
  RTC_DateTypeDef rtc_date = {0};
  RTC_TimeTypeDef rtc_time = {0};
  
#if (configUSE_ODOMETER == 1)
  gnss_feature |= ODOMETER;
#endif /* configUSE_ODOMETER */

#if (configUSE_GEOFENCE == 1)
  gnss_feature |= GEOFENCE;
#endif /* configUSE_GEOFENCE */

#if (configUSE_DATALOG == 1)
  gnss_feature |= DATALOG;
#endif /* configUSE_DATALOG */

  if(PlatformStatus.s.GNSS_GEOFENCE_MASK != 0)
  {
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGEOFENCEREQ\r\n");
    HAL_Delay(GNSS_CMD_DELAY);
  }
  GNSS_DATA_SendCommand(&pGNSS, "$PSTMNMEAREQUEST,42,0");
  HAL_Delay(GNSS_CMD_DELAY);
  
  int concluded = 0;
  bGPGGA_Received = 0;
  bGPRMC_Received = 0;
  bPSTMVER_Received = 0;
  gnss_fix_validity = INVALID;
  memset(&GNSSParser_Data.gprmc_data.utc, 0x00, sizeof(GNSSParser_Data.gprmc_data.utc));
  memset(&GNSSParser_Data.gpgga_data.utc, 0x00, sizeof(GNSSParser_Data.gpgga_data.utc));
  GNSSParser_Data.gpgga_data.valid = INVALID;
  GNSSParser_Data.gpgga_data.sats = 0;
  
  while(!concluded)
  {    
    gnssMsg = GNSS_Get_Buffer(&pGNSS);
    if(gnssMsg == NULL)
    {
      break;
    }
    
    check = GNSS_PARSER_CheckSanity((uint8_t *)gnssMsg->buf, gnssMsg->len);

    if(check != GNSS_PARSER_ERROR){

      for(int m = 0; m < NMEA_MSGS_NUM; m++) 
      {

        status = GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)m, (uint8_t *)gnssMsg->buf);

        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == GPGGA)) {
          bGPGGA_Received += 1;
          gnss_latitude  = convertCoord( GNSSParser_Data.gpgga_data.xyz.lat, 
                                        GNSSParser_Data.gpgga_data.xyz.ns=='N' ? 0 : 1 );
          gnss_longitude = convertCoord( GNSSParser_Data.gpgga_data.xyz.lon, 
                                        GNSSParser_Data.gpgga_data.xyz.ew=='E' ? 0 : 1 );
          gnss_altitude = GNSSParser_Data.gpgga_data.xyz.alt;
          gnss_sats = GNSSParser_Data.gpgga_data.sats;
          gnss_fix_validity = GNSSParser_Data.gpgga_data.valid;
          
          PRINTF_MAIN1("Got coordinates: %f %c, %f %c, ALT:%f\r\n", 
                            ABS(gnss_latitude), LAT_NORD_SUD(gnss_latitude), 
                            ABS(gnss_longitude), LON_EAST_WEST(gnss_longitude),
                            gnss_altitude);
#if 0
          //print additional GNSS data
          PRINTF_MAIN1("Got coordinates %f %f %f\r\n",gnss_latitude,gnss_longitude,gnss_altitude);
          PRINTF_MAIN1("TIMEGGA (%d) %.2d:%.2d:%.2d\r\n",bGPGGA_Received,GNSSParser_Data.gpgga_data.utc.hh,GNSSParser_Data.gpgga_data.utc.mm,GNSSParser_Data.gpgga_data.utc.ss);
          PRINTF_MAIN1("DATERMC (%d) %.2d/%.2d/%.2d\r\n",bGPRMC_Received,GNSSParser_Data.gprmc_data.date/10000,(GNSSParser_Data.gprmc_data.date%10000)/100,GNSSParser_Data.gprmc_data.date%100);
          PRINTF_MAIN1("GNSSVER (-) %s\r\n",GNSSParser_Data.pstmver_data.pstmver_string);
#endif
          PRINTF_MAIN1("%.2d/%.2d/%.2d %.2d:%.2d:%.2d - %d sats - Fix %d\r\n",
                            GNSSParser_Data.gprmc_data.date/10000,(GNSSParser_Data.gprmc_data.date%10000)/100,GNSSParser_Data.gprmc_data.date%100,
                            GNSSParser_Data.gpgga_data.utc.hh,GNSSParser_Data.gpgga_data.utc.mm,GNSSParser_Data.gpgga_data.utc.ss, 
                            GNSSParser_Data.gpgga_data.sats, GNSSParser_Data.gpgga_data.valid);
          
          if(PlatformStatus.b.GPSTIME_IN_LPP)
          {
            /* RTC data are updated using information coming from GNSS */
            if ( (bSetRtcFirstTime) || ((gnss_fix_validity) && ((!PlatformStatus.b.RTC_UPDATED) || (PlatformStatus.s.RTC_TRIGGER_VALUE != GNSSParser_Data.gpgga_data.utc.hh))) )
            {
              if(gnss_fix_validity)
              {
                PRINTF_MAIN1("Update RTC with GPS fix\r\n");
              }
              else if(bSetRtcFirstTime)
              {
                PRINTF_MAIN1("Update RTC without GPS fix\r\n");
              }
              
              bSetRtcFirstTime = 0;
              
              rtc_time.Hours = (uint8_t) GNSSParser_Data.gpgga_data.utc.hh;
              rtc_time.Minutes = (uint8_t) GNSSParser_Data.gpgga_data.utc.mm;
              rtc_time.Seconds = (uint8_t) GNSSParser_Data.gpgga_data.utc.ss;
              
              /* Ready to set time */
              PRINTF_MAIN1("GPS time: %.2d:%.2d:%.2d (hh:mm:ss UTC time)\r\n", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds);      
              
              rtc_date.Date = GNSSParser_Data.gprmc_data.date/10000;
              rtc_date.Month = (GNSSParser_Data.gprmc_data.date%10000)/100;
              rtc_date.Year  = GNSSParser_Data.gprmc_data.date%100;
              
              /* Ready to set date */
              PRINTF_MAIN1("GPS date: %s %.2d-%s-%.2d \r\n", BSP_RTC_GetWeekDayName(rtc_date.WeekDay), rtc_date.Date, BSP_RTC_GetMonthName(rtc_date.Month),rtc_date.Year);
              
              RTC_TimeTypeDef RTC_TimeStruct;
              RTC_DateTypeDef RTC_DateStruct;
              time_t t_of_day, currentEpochTime;
              
              HW_RTC_GetTimeValue(&RTC_TimeStruct);
              HW_RTC_GetDateValue(&RTC_DateStruct);
              t_of_day = ConvertToEpochTime(&RTC_TimeStruct, &RTC_DateStruct);
              currentEpochTime = ConvertToEpochTime(&rtc_time, &rtc_date);
              
              nDeltaEpochTime = currentEpochTime - t_of_day;
              PRINTF_MAIN1("nDeltaEpochTime: %d\r\n", nDeltaEpochTime);
              
              PlatformStatus.s.RTC_TRIGGER_VALUE = GNSSParser_Data.gpgga_data.utc.hh;
              PlatformStatus.b.RTC_UPDATED = SET;
            }
          }
        }
        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == GPRMC))
        {
          bGPRMC_Received += 1;
        }
        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMVER))
        {
          bPSTMVER_Received += 1;
        }
        
        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMGEOFENCE)) {
          GNSS_DATA_GetGeofenceInfo(&pGNSS, &GNSSParser_Data);
          if(GNSSParser_Data.geofence_data.status[GEOFENCE_LECCE] != 0)
          {
            PRINTF_MAIN1("GEOFENCE_%d (ST LE): %d %s\r\n", GEOFENCE_LECCE, GNSSParser_Data.geofence_data.status[GEOFENCE_LECCE], geofenceCirclePosition[GNSSParser_Data.geofence_data.status[GEOFENCE_LECCE]]);
            TeseoGeofenceCallback(GEOFENCE_LECCE, GNSSParser_Data.geofence_data.status[GEOFENCE_LECCE]);
          }
          if(GNSSParser_Data.geofence_data.status[GEOFENCE_CATANIA] != 0)
          {
            PRINTF_MAIN1("GEOFENCE_%d (ST CT): %d %s\r\n", GEOFENCE_CATANIA, GNSSParser_Data.geofence_data.status[GEOFENCE_CATANIA], geofenceCirclePosition[GNSSParser_Data.geofence_data.status[GEOFENCE_CATANIA]]);
            TeseoGeofenceCallback(GEOFENCE_CATANIA, GNSSParser_Data.geofence_data.status[GEOFENCE_CATANIA]);
          }
          if(GNSSParser_Data.geofence_data.status[GEOFENCE_CUR_COORDS] != 0)
          {
            PRINTF_MAIN1("GEOFENCE_%d ( LOC ): %d %s\r\n", GEOFENCE_CUR_COORDS, GNSSParser_Data.geofence_data.status[GEOFENCE_CUR_COORDS], geofenceCirclePosition[GNSSParser_Data.geofence_data.status[GEOFENCE_CUR_COORDS]]);
            TeseoGeofenceCallback(GEOFENCE_CUR_COORDS, GNSSParser_Data.geofence_data.status[GEOFENCE_CUR_COORDS]);
          }
          UNUSED(geofenceCirclePosition);
        }
        if(status != GNSS_PARSER_ERROR)
        {
          break;
        }
        if(bGPRMC_Received && bGPGGA_Received)
        {
          concluded = 1;
          break;
        }
      }
    }
    
    gnssMsg->buf[8] = 0;

    GNSS_Release_Buffer(&pGNSS, gnssMsg);
    
  }
}


/**
  * @brief  Convert latitude/longitude coordinate from sexagesimal to decimal format
  * @param  float x coordinate
  * @param  uint8_t sign 1 for negative 0 for positive
  * @retval coordinate in decimal format
  */
static float convertCoord( float x, uint8_t sign )
{
  int degrees;
  float minutes;
  float ret;

  degrees = (int)(x / 100.0F);
  minutes = x - degrees*100.0F;
  ret = degrees + minutes / 60.0F;
  if (sign==1)
    ret = -ret;
  
  return ret;
}


/**
  * @brief  Read data from teseo
  * @param  None
  * @retval None
  */
void TeseoReadData( uint32_t nTimeout )
{
  static uint32_t nTeseoReset = 0;
  
  if(PlatformStatus.b.SW1_OA == 0)
  {
    PlatformStatus.b.GNSS_INITED = 0;
  }
  if (PlatformStatus.b.GNSS_INITED == 0)
  {
    BSP_PowerGNSS(DISABLE);
    GNSS_Bus_Reset(&pGNSS);
    
    PRINTF_MAIN2("GNSS_PARSER_Init()\r\n");
    GNSS_PARSER_Init(&GNSSParser_Data);
    
    BSP_PowerGNSS(ENABLE);
    PlatformStatus.b.GNSS_INITED = 1;
    HAL_Delay(1000);
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1201,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1210,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1211,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1228,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1229,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSETPAR,1230,0");
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_EnableGeofence(&pGNSS, 0);
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMSAVEPAR\r\n");
    HAL_Delay(GNSS_CMD_DELAY);
    
    if(PlatformStatus.s.GNSS_GEOFENCE_MASK)
    {
      if(PlatformStatus.s.GNSS_GEOFENCE_MASK & (1<<GEOFENCE_LECCE))
      {
        bSendCommandGeofenceCfg = GEOFENCE_LECCE;
        PlatformStatus.s.GNSS_GEOFENCE_MASK = (1<<GEOFENCE_LECCE);
      }
      if(PlatformStatus.s.GNSS_GEOFENCE_MASK & (1<<GEOFENCE_CATANIA))
      {
        bSendCommandGeofenceCfg = GEOFENCE_CATANIA;
        PlatformStatus.s.GNSS_GEOFENCE_MASK = (1<<GEOFENCE_CATANIA);
      }
      if(PlatformStatus.s.GNSS_GEOFENCE_MASK & (1<<GEOFENCE_CUR_COORDS))
      {
        bSendCommandGeofenceCfg = GEOFENCE_CUR_COORDS;
        PlatformStatus.s.GNSS_GEOFENCE_MASK = (1<<GEOFENCE_CUR_COORDS);
      }
    }
  }
  
#if GNSS_STANDBY_WAKEUP
  TeseoWakeUp();
#endif //GNSS_STANDBY_WAKEUP
  
  TeseoManageCommands();
  
  uint32_t nEndTick = HAL_GetTick() + nTimeout;
  
  while( (bGPGGA_Received == 0) || (bGPRMC_Received == 0) ) //retry if no rmc or gga 
  {
    if(bGPGGA_Received == 0 || bGPRMC_Received == 0)
    {
      nTeseoReset++;
      if(nTeseoReset > GNSS_NUM_LOOPS_WITHOUT_DATA)
      {
        nTeseoReset = 0;
        PlatformStatus.b.GNSS_INITED = 0;
      }
      PRINTF_MAIN1("Reset Teseo serial port\r\n");
      GNSS_Bus_Disable(&pGNSS);
      GNSS_Bus_Enable(&pGNSS);
    }
    TeseoConsumerTask(NULL);
    if( HAL_GetTick() > nEndTick )
    {
      break;
    }
  }
  
  if( (bGPGGA_Received != 0) && (bGPRMC_Received != 0) )
  {
    nTeseoReset = 0;
  }

  sensor_data.latitude  = gnss_latitude;
  sensor_data.longitude = gnss_longitude;
  sensor_data.altitudeGps  = gnss_altitude;
}

#if TESEO_READ_TIMER
/**
  * @brief  Timer callback to periodically read data from TESEO
  * @param  None
  * @retval None
  */
static void OnTeseoReadTimerEvent( void )
{
  bTeseoRead = 1;
}


/**
  * @brief  Timer configuration to periodically read data from TESEO
  * @param  None
  * @retval None
  */
static void TeseoReadTimerStart(void)
{
#if defined(GNSS_ENABLED) 
  TimerInit( &TeseoReadTimer, OnTeseoReadTimerEvent );
  TimerSetValue( &TeseoReadTimer,  TESEO_READ_INTERVAL);
  OnTeseoReadTimerEvent();
#endif //defined(SENSOR_ENABLED) // || defined (LRWAN_NS1) 
}
#endif //TESEO_READ_TIMER


/**
  * @brief  Timer callback to go in low power
  * @param  None
  * @retval None
  */
static void OnSleepTimerEvent( void*c )
{
  sleep_timer_event = true;
}


/**
  * @brief  Timer configuration to go in low power
  * @param  None
  * @retval None
  */
static void InitSleepTimer(void)
{
  TimerInit( &SleepTimer, OnSleepTimerEvent );
  TimerSetValue( &SleepTimer,  SLEEP_TIMER_FIRST_TIME);
}


/**
  * @brief  Reload sleep timer
  * @param  None
  * @retval None
  */
static void ReloadSleepTimer(void)
{
  if( ( PlatformStatus.b.LP_SLEEP_TIMER ) && (nPacketsSent > N_PACKETS_SENT_BEFORE_LOW_POWER ) )
  {
    TimerStop(&SleepTimer);
    TimerSetValue(&SleepTimer, SLEEP_TIMER_INTERVAL);
    TimerStart(&SleepTimer);
  }
}


/**
  * @brief  Get Teseo Data
  * @param  None
  * @retval None
  */
void GetTeseoData (int32_t* pnLatitude, int32_t* pnLongitude, int32_t* pnAltitudeGps, uint8_t *bFixValidity)
{
#if defined(GNSS_ENABLED)
  TeseoReadData(GNSS_TIMEOUT_POLL);
#endif //defined(GNSS_ENABLED)  
  *pnLatitude    = ( int32_t )( sensor_data.latitude * 10000 );
  *pnLongitude   = ( int32_t )( sensor_data.longitude * 10000 );
  *pnAltitudeGps = ( int32_t )( sensor_data.altitudeGps * 100 );
  *bFixValidity  = gnss_fix_validity;
}


/**
  * @brief  Send command to send cold start command to the TESEO
  * @param  None
  * @retval None
  */
void TeseoSendColdStart (void)
{
  GNSS_DATA_SendCommand(&pGNSS, "$PSTMCOLD,6\r\n");
  TeseoConsumerTask(NULL);
}  

/**
  * @brief  Get LoRa init params structure pointer
  * @param  None
  * @retval None
  */
void LoraGetInitParams(LoRaParam_t **LoRa_Param_Init)
{
  *LoRa_Param_Init = &LoRaParamInit;
}


/**
  * @brief  Set the sentFlag in the selected item 
  * @param  nbitem index of the selected item
  * @retval None
  */
void PushLogFlag(uint16_t nbitem)
{
  LogEvent_Item_t xLogItem = { 0 };
  LogEvent_Type_t xTypeR = LOG_EV_NRM;
  
  /* Get new item (for CRC computing) */ 
  if(SUCCESS == LogEvent_Get(&xLogItem, xTypeR, nbitem, 0))
  {
    PRINTF_MAIN1("#%d: %s\r\n", nbitem, xLogItem.Payload);
  }
  else
  {
    PRINTF_MAIN1("item not available\r\n");
  }
  
  /* Set sentFlag to EEPROM*/
  xLogItem.Payload[6] = '1';
  LogEvent_UpdateItem(&xLogItem);
  
  PRINTF_MAIN1("Type %s: %d items\r\n", LogEvent_GetTypeName(xTypeR), nbitem);
} 


/**
  * @brief  Get the selected item 
  * @param  nbitem index of the selected item
  * @retval retval 0 -> OK, 1 -> ERROR
  */
uint8_t GetSingleItem(uint16_t nbitem)
{
  uint8_t retval = 1;
  LogEvent_Item_t xLogItem = { 0 };
  if(SUCCESS == LogEvent_Get(&xLogItem, LOG_EV_NRM, nbitem, 0))
  {
    PRINTF_MAIN1("#%d: %s - ", nbitem, xLogItem.Payload);
    PRINTF_MAIN1("TS:%d\r\n", xLogItem.Header.TimeStamp);
    char* nQuoteIndex = strchr ((const char*)xLogItem.Payload, ':');
    if(nQuoteIndex != NULL)
    {
      uint32_t nScOut = 0;
      int tsentFlag, tAccEnable, ttemperature, tpressure, thumidity, tlatitude, tlongitude, taltitudeGps, tbatteryLevel;
      nScOut = sscanf(nQuoteIndex, ":%d:%d|%d|%d|%d|%d|%d|%d|%d", &tsentFlag,  &tAccEnable, &ttemperature, &tpressure, &thumidity, &tlatitude, &tlongitude, &taltitudeGps, &tbatteryLevel);
      if(nScOut == 9)
      {
        data_logged.sentFlag = (tsentFlag != 0);
        data_logged.AccEnable = tAccEnable;
        data_logged.temperature = ttemperature;
        data_logged.pressure = tpressure;
        data_logged.humidity = thumidity;
        data_logged.latitude = tlatitude;
        data_logged.longitude = tlongitude;
        data_logged.altitudeGps = taltitudeGps;
        data_logged.batteryLevel = tbatteryLevel;
        PRINTF_MAIN1("%d, %d, %d, %d, %d, %d, %d, %d, %d\r\n", data_logged.sentFlag, data_logged.AccEnable, data_logged.temperature, data_logged.pressure, data_logged.humidity, data_logged.latitude, data_logged.longitude, data_logged.altitudeGps, data_logged.batteryLevel);
        data_logged.epoch_value = xLogItem.Header.TimeStamp;
        retval = 0;
      }
      else
      {
        PRINTF_MAIN1("item corrupted\r\n");
      }
    }
    else
    {
      PRINTF_MAIN1("item format not valid\r\n");
    }
  }
  else
  {
    PRINTF_MAIN1("item not available\r\n");
  }
  return retval;
}

/**
  * @brief  Get first item to send 
  * @param  none
  * @retval intem item index
  */
uint16_t GetFirstItemToSend( void )
{
  uint16_t item = 0;
  data_logged.sentFlag = 1;
  
  uint32_t lastSavedItem = LogEvent_GetCount(LOG_EV_NRM);
  uint32_t TotalItems = LogEvent_GetTotalCount(LOG_EV_NRM);
  
  /* backward search */
  item = lastSavedItem;
  
  if(item>1000)
  {
    do
    {
      item-=1000;
      if(GetSingleItem(item)==1)
      {
        //error
        break;
      }
      if( (lastSavedItem > TotalItems) && (item < lastSavedItem - TotalItems) )break;
    }while (data_logged.sentFlag == 0);
    item+=1000;
  }
  
  if(item>100)
  {
    do
    {
      item-=100;
      if(GetSingleItem(item)==1)
      {
        //error
        break;
      }
      if( (lastSavedItem > TotalItems) && (item < lastSavedItem - TotalItems) )break;
    }while (data_logged.sentFlag == 0);
    item+=100;
  }
  
  if(item>10)
  {
    do
    {
      item-=10;
      if(GetSingleItem(item)==1)
      {
        //error
        break;
      }
      if( (lastSavedItem > TotalItems) && (item < lastSavedItem - TotalItems) )break;
    }while (data_logged.sentFlag == 0);
    item+=10;
  }
  
  if(item>1)
  {
    do
    {
      item-=1;
      if(GetSingleItem(item)==1)
      {
        //error
        break;
      }
      if( (lastSavedItem > TotalItems) && (item < lastSavedItem - TotalItems) )break;
    }while (data_logged.sentFlag == 0);
  }
  
  if(item == 0xFFFF || item < lastSavedItem)
  {
    item++;
  }
  
  return (item);
}


/**
  * @brief  Set LoRa ack (from lora.c file)
  * @param  ack value
  * @retval None
  */
void LoraSetAck(bool ack)
{
  bLoraAck = ack;
}


/**
  * @brief  Set LoRa dr (from lora.c file)
  * @param  dr value
  * @retval None
  */
void LoraSetDR(uint8_t dr)
{
  if(PlatformStatus.s.LORA_ADR)
  {
    nLoraDR = dr;
  }
  else
  {
    nLoraDR = PlatformStatus.s.LORA_DR;
  }
}


/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
