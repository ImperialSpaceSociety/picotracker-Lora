/******************************************************************************
  * @file    main.c
  * @author  Central Labs
  * @version V2.1.0
  * @date    27-May-2019
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
   
/** @defgroup B-L072Z-LRWAN1 B-L072Z-LRWAN1
  * @{
  */  
   
/** @defgroup B-L072Z-LRWAN1_ASSET_TRACKER Asset Tracker
  * @{
  */    
    
/** @defgroup B-L072Z-LRWAN1_LoRaWAN LoRaWAN
  * @{
 */

/** @defgroup B-L072Z-LRWAN1_MAIN Main (B-L072Z-LRWAN1)
  * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include "hw.h"
#include "low_power_manager.h"
#include "lora.h"
#include "bsp.h"
#include "timeServer.h"
#include "vcom.h"
#include "version.h"
#include "command.h"
    
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
#include "iks01a2_motion_sensors.h"
#include "iks01a2_motion_sensors_ex.h"
#endif //LORA_SMART_TRACKER
#include "gnss_data.h"
#include "gnss_if.h"
//#include "log_manager.h"

/** @addtogroup B-L072Z-LRWAN1_MAIN_Definition Main Constant Definition
  * @{
 */

/** @addtogroup B-L072Z-LRWAN1_MAIN_Definition Main Constant Definition
  * @{
  */   
#define PRINTF_MAIN1(...)               PRINTF(__VA_ARGS__)
#define PRINTF_MAIN2(...)               PRINTF(__VA_ARGS__)
#define CHECK_LORA_JOIN()               (PlatformStatus.b.APP_LORA_JOINED == TRUE)
#define CHECK_OPERATIONS_PENDING()     ((LoraMacProcessRequest!=LORA_SET)      && \
                                         (AppProcessRequest!=LORA_SET)         && \
                                         (mems_int2_detected == 0)             && \
                                         (tx_timer_event == 0)                 && \
                                         (read_timer_event == 0)               && \
                                         (sleep_timer_event == 0)              && \
                                         (sensor_event == 0)                   && \
                                         (GetUserButtonPushed() == 0)          \
                                        )
/**
  * @}
  */

/** @addtogroup B-L072Z-LRWAN1_MAIN_CAYENNE_LPP myDevices CAYENNE Application server
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

#define TESEO_READ_TIMER                0
#define TEST_BATTERY                    0
#define USE_SHORTEN_JOIN_REQ_INTV       1   /* Enable skip sensor read to speedup first lora join requests when not joined. Allowed values: 0 disabled , 1 (default) enabled */
#define LOW_POWER_WITH_USB_CONNECTED    1   /* Low power allowed also with USB connected. Allowed values: 0 (default) disabled, 1 enabled */

/**
  * @}
  */

/** @addtogroup B-L072Z-LRWAN1_MAIN_SENSOR_THRSHLD Sensors thresholds
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

/** @addtogroup B-L072Z-LRWAN1_MAIN_TIME_INTERVAL Time intervals and timeout values
  * @{
  */
#define BATTERY_READ_INTERVAL           5000
#define SENSOR_POLL_INTERVAL            30000           // Must be higher than inactivity time

#define GNSS_CMD_DELAY                  (500)
#define WAIT_FOR_FIX_POLL_INTERVAL      (1000)
#define GNSS_NO_TIMEOUT                 (0)
#define GNSS_TIMEOUT_POLL               (2000)
#define GNSS_TIMEOUT_SEND               (60*1000)

/**
  * @}
  */


/** @addtogroup B-L072Z-LRWAN1_MAIN_DATA_RATE_SETTINGS Data trasmission settings
  * @ note Defines the application data transmission duty cycle. 5s, value in [ms].
  * @{
  */
#define SEND_INTERVAL_FIRST_TIME                        10000
#define JOIN_TX_DUTYCYCLE                               20000

#define TESEO_READ_DUTYCYCLE                            10000
#define SLEEP_TIMER_FIRST_TIME                          10000
#define SLEEP_TIMER_DUTYCYCLE                           20000
#define N_PACKETS_SENT_BEFORE_LOW_POWER                 2
#define MAX_TX_WITHOUT_LOW_POWER                        0
#define SEND_IDLE_INTERVAL                              10000
#define RESTART_MSG_INTERVAL                            10000

/**
  * @}
  */

#define STD_OUT_SAFE_ARRAY_LENGHT       (256)


/** @addtogroup B-L072Z-LRWAN1_MAIN_LoRaWAN_ADR LoRaWAN adaptive Data Rate
  * @ note Please note that when ADR is enabled the end-device should be static
  * @{
  */
#define LORAWAN_ADR_STATE                               LORAWAN_ADR_OFF
/**
  * @}
  */

/** @addtogroup B-L072Z-LRWAN1_MAIN_LoRaWAN_DDR LoRaWAN default Data Rate
  * @ note Please note that LORAWAN_DEFAULT_DATA_RATE is used only when ADR is disabled
  * @{
  */
#define LORAWAN_DEFAULT_DATA_RATE                       DR_4
/**
  * @}
  */

/** @addtogroup B-L072Z-LRWAN1_MAIN_LoRaWAN_APP_PORT LoRaWAN application port
  * @ note Do not use 224. It is reserved for certification
  * @{
 */
#define LORAWAN_APP_PORT                                2
/**
  * @}
  */ 

/** @addtogroup B-L072Z-LRWAN1_MAIN_LoRaWAN_ENDNODE_CLASS_PORT LoRaWAN default endNode class port
  * @{
 */
#define LORAWAN_DEFAULT_CLASS                           CLASS_A
/**
  * @}
  */ 

/** @addtogroup B-L072Z-LRWAN1_MAIN_LoRaWAN_CONFIRM_STATE LoRaWAN default confirm state
  * @{
  */
#define LORAWAN_DEFAULT_CONFIRM_MSG_STATE               LORAWAN_CONFIRMED_MSG
/**
  * @}
  */ 

/** @addtogroup B-L072Z-LRWAN1_MAIN_LoRaWAN_DATA_BUFFER_SIZE LoRaWAN application data buffer size
  * @{
  */
#define LORAWAN_APP_DATA_BUFF_SIZE                      (64 + 4 +2)  //adding 4 byte for epochtime + 2 byte channel and datatype)
/**
  * @}
  */ 

/** @addtogroup B-L072Z-LRWAN1_MAIN_EEPROM_SETTINGS LoRaWAN Settings saved in internal EEPROM
  * @{
 */
#define USE_EEPROM_SETTINGS             0

#define LOW_POWER_ON_SLEEP_TIMER_DEF    1   /* Low power on sleep timer expiration. Allowed values: 0 (default) disabled, 1 enabled */ 
#define LOW_POWER_ON_SENSOR_EVENT_DEF   1   /* Low power on accelerometer inactivity event. Allowed values: 0 disabled, 1 (default) enabled */
#define GNSS_SEND_WAIT_MODE_DEF         1   /* Allowed values: 0 GNSS_WAIT_FOR_DATA, 1 (default) GNSS_WAIT_FOR_FIX */
#define GNSS_POLL_WAIT_MODE_DEF         0   /* Allowed values: 0 GNSS_WAIT_FOR_DATA, 1 (default) GNSS_WAIT_FOR_FIX */

#define SEND_ON_WAKE_EVENT_DEF          1   /* Trigger data sending on accelerometer wake-up event. Allowed values: 0 disabled, 1 (default) enabled */
#define SEND_ON_SENSOR_EVENT_DEF        1   /* Trigger data sending on environmental sensors threshold overshoot. Allowed values: 0 disabled, 1 (default) enabled */

#define GNSS_GEOFENCE_RADIUS_DEF        100 /* Geofence radius value */
#define GNSS_GEOFENCE_MASK_DEF          0   /* Mask to enable geofence demos: Allowe values: 0 (default) disabled, see ProcDbgSetGeoFence function for other values */

#define LOG_MANAGER_DEF                 0
#define GPSTIME_IN_LPP_DEF              0   /* 'Include Epoch time' variable status. Allowed values: 0 (default) epoch time is not included and RTC is not updated, 1 epoch time is included and RTC is updated from gps time*/

#define LORA_DR_DEF                     LORAWAN_DEFAULT_DATA_RATE
#define LORA_ADR_DEF                    LORAWAN_ADR_STATE
#define SEND_INTERVAL_DEF               60000

#define MAX_ERROR_NO_ACK                5

/**
  * @}
  */

/**
  * @}
  */ 

/** @addtogroup B-L072Z-LRWAN1_MAIN_Private_Variables Main Private Variables
  * @{
 */

/*!
 * User application data
 */
#define MSGQUEUE_LEN 16

typedef struct 
{
    LogData_t array[MSGQUEUE_LEN];
    int head;
    int length;
} MsgQueue_t;

MsgQueue_t MsgQueue;
LogData_t data_logged;

static uint8_t AppDataBuff[LORAWAN_APP_DATA_BUFF_SIZE];
static char sStdOutSafeString[STD_OUT_SAFE_ARRAY_LENGHT+1] = { 0 }; //!< Buffer to store the custom printf output (safe)
uint32_t nCharsToPrint = 0;

static uint32_t lastSendTick = 0;
uint32_t last_mems_event,last_sensor_poll;
bool sensor_event = false;
uint32_t nStartSendTick = 0;
float gnss_latitude, gnss_longitude, gnss_altitude;
int32_t gnss_sats=0;
uint8_t gnss_fix_validity = 0;
static uint8_t bSendCommandStore = 0;
static uint8_t bSendCommandGetpar = 0;
uint8_t bSendCommandGeofenceCfg = 0;
uint8_t bSendCommandGeofenceReq = 0;

static const char *geofenceCirclePosition[] = {
  "Unknown",
  "Outside",
  "Boundary",
  "Inside"
};

uint8_t bUsbIsConnected = 0;
static uint32_t nPacketsSent = 0;

static uint8_t nTxWithoutLowPower = MAX_TX_WITHOUT_LOW_POWER;

bool read_timer_event, tx_timer_event, sleep_timer_event;

/*!
 * Specifies the state of the application LED
 */
static uint8_t AppLedStateOn = RESET;

#ifdef USE_B_L072Z_LRWAN1
/*!
 * Timer to handle the application Tx Led to toggle
 */
static TimerEvent_t TxLedTimer;
#endif
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

/** @addtogroup B-L072Z-LRWAN1_MAIN_Exported_Variables Main Exported Variables
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
#endif


#ifdef USE_B_L072Z_LRWAN1

uint8_t bUserButtonPushed = 0;

/*!
 * Timer to handle the application Tx Led to toggle
 */
static TimerEvent_t TxLedTimer;
#endif

uint8_t nLoraDR=0;
bool bLoraAck = FALSE;
bool bWaitAck = FALSE;

/**
  * @}
  */



/** @addtogroup B-L072Z-LRWAN1_MAIN_Private_function_prototypes Main Private function prototypes
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
static void OnReadTimerEvent( void*c );
static void OnSleepTimerEvent( void*c );
static void InitSleepTimer( void );
static void ReloadSleepTimer(void);
void Board_GetDevEui( uint8_t *id );
static void LoraMacProcessNotify( void );
void UserButtonCallback(void);

#if TESEO_READ_TIMER
static void OnTeseoReadTimerEvent( void*c );
static void TeseoReadTimerStart( void );
#endif//TESEO_READ_TIMER

#if defined(GNSS_ENABLED)
static void TeseoReadData( uint32_t nTimeout );
#endif

/* GNSS function prototypes */
static void GPIO_Config(void);
static void TeseoConsumerTask(void const * argument);

#ifdef USE_B_L072Z_LRWAN1
/*!
 * Timer to handle the application Tx Led to toggle
 */
static void OnTimerLedEvent( void*c );
#endif

void UserAuxFunction(void);
void UserHwInit( void );
void UserProcess( void );

static void MsgQueue_init(void);
static int MsgQueue_isempty(void);
static int MsgQueue_isfull(void);
static void MsgQueue_enqueue(void);
static void MsgQueue_dequeue(void);
static void MsgQueue_read(void);
static void MsgQueue_print(void);

/**
  * @}
  */ 

/** @addtogroup B-L072Z-LRWAN1_MAIN_Exported_Structures Main Exported Structures
  * @{
 */
/*!
 * User application data structure
 */
static lora_AppData_t AppData={ AppDataBuff,  0 ,0 };

/* load Main call backs structure*/
static LoRaMainCallback_t LoRaMainCallbacks = { BSP_GetBatteryLevel,
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

#ifdef USE_B_L072Z_LRWAN1
/*!
 * Timer to handle the application Tx Led to toggle
 */
static TimerEvent_t TxLedTimer;
static void OnTimerLedEvent( void*c );
#endif
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
  //DBG_Init();
  
  PRINTF_MAIN1("SYSTEM STARTUP\r\n");
  
  /* Launch the auxiliary function */
  UserAuxFunction();
    
  /* Configure the hardware*/
  HW_Init();
  
  /* USER CODE BEGIN 1 */
  UserHwInit();
  /* USER CODE END 1 */
  
  /* Configure the command mode*/
  CMD_Init();

  /* Disable Stand-by mode*/
  LPM_SetOffMode(LPM_APPLI_Id , LPM_Disable );
  
  /* Configure the Lora Stack*/
  LORA_Init( &LoRaMainCallbacks, &LoRaParamInit);
  
  PRINTF_MAIN1("VERSION: %X\r\n", VERSION);
  
  LORA_Join();
  
  PlatformStatus.s.xCurrentState = State_Run;
  PlatformStatus.s.xNextState = State_Run;
  lastSendTick = HAL_GetTick();

  LoraInitTxTimer( ) ;
  LoraStartReadTimer( );
  
  MsgQueue_init();
  
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
    
  /* USER CODE BEGIN 2 */
    UserProcess();
  /* USER CODE END 2 */
  }
}

void LoraMacProcessNotify(void)
{
  LoraMacProcessRequest=LORA_SET;
}

/** @addtogroup B-L072Z-LRWAN1_MAIN_Private_function Main Private functions
  * @{
 */

void Board_GetDevEui( uint8_t *id )
{
  HW_GetUniqueId(id);
  LoadLoraKeys();
}

/** @brief DBG_PRINTF_LOG_SAFE implementation
  * @param L reserved
  * @param sFormatString pointer to the string
  * @retval 0 -> OK, 1 -> FAIL 
  */
uint8_t DBG_PRINTF_LOG_SAFE(uint16_t L, const char* sFormatString, ...)
{
  uint8_t xRes = 0;
  if(nCharsToPrint < STD_OUT_SAFE_ARRAY_LENGHT)
  {
    va_list ap;
    va_start (ap, sFormatString);
    uint16_t nCharsToAdd = vsnprintf(sStdOutSafeString+nCharsToPrint, STD_OUT_SAFE_ARRAY_LENGHT-nCharsToPrint, sFormatString, ap);
    nCharsToPrint += nCharsToAdd;
//    PRINTF(sFormatString, ap);
    va_end (ap);
  }
  return xRes;
}

void UserButtonCallback(void)
{
  bUserButtonPushed = 1;
}

/** @brief Flush DBG_PRINTF_LOG_SAFE output 
  * @param  None
  * @retval None
  */
void FlushSafePrintf()
{
  if(nCharsToPrint)
  {
    PRINTF_MAIN1(sStdOutSafeString);
    memset(sStdOutSafeString, 0x0, STD_OUT_SAFE_ARRAY_LENGHT);
    nCharsToPrint = 0;
  }
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
  * @brief  Prepare hardware for low power mode
  * @param  None
  * @retval None
  */
void PrepareLowPower()
{
  ReloadSleepTimer();
//  BSP_PowerGNSS(DISABLE);
  BSP_sensor_Disable();
  BSP_accelero_Init(true);   // restart the accelerometer otherwise we can't to UltraLowPower state
#ifdef LORA_SMART_TRACKER
    LED_Off( LED_WHITE );
#else
    LED_Off( LED2 );
#endif    
}

/**
  * @brief  Prepare hardware for ultra low power mode
  * @param  None
  * @retval None
  */
void PrepareUltraLowPower()
{
//  BSP_PowerGNSS(DISABLE);
  BSP_sensor_Disable();
  BSP_accelero_Disable();
#ifdef LORA_SMART_TRACKER
    LED_Off( LED_WHITE );
#else
    LED_Off( LED2 );
#endif    
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
#ifdef LORA_SMART_TRACKER
    LED_Toggle( LED_WHITE );
#else
    LED_Toggle( LED2 );
#endif    
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
      LED_On( LED_WHITE ) ; 
      HAL_Delay(200);
      LED_Off( LED_WHITE ) ; 
      HAL_Delay(200);
      if(BSP_PB_GetState( BUTTON_USER ) == 0)break;
    }
    if(BSP_PB_GetState( BUTTON_USER ) != 0)
    {
      PRINTF_MAIN1("SENDING SHUTDOWN...\r\n");
      BSP_BoardShutdown();
      while(1){LED_Toggle( LED_WHITE );HAL_Delay(2000);}
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
      LED_On( LED_WHITE ) ; 
      HAL_Delay(200);
      LED_Off( LED_WHITE ) ; 
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
#ifdef LORA_SMART_TRACKER
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
    PRINTF_MAIN1("  Battery charge: %u%%\r\n", battery_charge_percentage);
    
    PrintChargerStatus(s);
  }
#endif
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

#if 1
      if ( PlatformStatus.s.xCurrentState == State_Run ) //(MCV) controllare
      if (HAL_GetTick()-last_mems_event < 2000 )
      {
        mems_int1_detected = 0;
        return bRetVal;
      }
#endif

      IKS01A2_MOTION_SENSOR_Event_Status_t status;
      if (IKS01A2_MOTION_SENSOR_Get_Event_Status(IKS01A2_LSM6DSL_0, &status) == BSP_ERROR_NONE)
      {
        if (status.WakeUpStatus != 0)
        {
          PRINTF_MAIN1(">> wake-up detected\r\n");
          last_mems_event = HAL_GetTick();
          if(PlatformStatus.b.SEND_ON_WAKE_EVENT)
          {
            PlatformStatus.s.xNextState = State_Read;
          }
        }
      }
    }
#endif //!LORA_SMART_TRACKER
    
    if ((mems_int2_detected) && IS_STATE_NOT_LOCKED(PlatformStatus.s.xCurrentState))
    {
      /* ACTIVITY/INACTIVITY DETECTION ON INT2 */
      bRetVal = 1;
      mems_int2_detected = 0;
      
      if ( PlatformStatus.s.xCurrentState == State_Run )
      {
        if (HAL_GetTick()-last_mems_event < 2000U )
        {
          return bRetVal;
        }
      }

#if defined(SENSOR_ENABLED)
#ifdef LORA_SMART_TRACKER
      LORA_TRACKER_MOTION_SENSOR_Event_Status_t status; 
      if(BSP_LORA_TRACKER_MOTION_SENSOR_Get_Event_Status(LORA_TRACKER_LIS2DW12_0, &status) == BSP_ERROR_NONE)
#else
      IKS01A2_MOTION_SENSOR_Event_Status_t status;
      if (IKS01A2_MOTION_SENSOR_Get_Event_Status(IKS01A2_LSM6DSL_0, &status) == BSP_ERROR_NONE)
#endif
      {
        if  (status.SleepStatus!=0)
        {
          last_mems_event = HAL_GetTick();
          PRINTF_MAIN1("Accelerometer inactivity interrupt\r\n"); 
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
#endif // defined(SENSOR_ENABLED)
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
    
    if(PlatformStatus.s.xNextState != State_INVALID && PlatformStatus.s.xCurrentState != PlatformStatus.s.xNextState)
    {
//      PRINTF("State: from ");
//      PrintSystemState(PlatformStatus.s.xCurrentState);
//      PRINTF(" to ");
      PRINTF("State machine change: ");
      PrintSystemState(PlatformStatus.s.xNextState);
      PRINTF("\r\n");
      PlatformStatus.s.xPrevState = PlatformStatus.s.xCurrentState;     // was missing
      PlatformStatus.s.xCurrentState = PlatformStatus.s.xNextState;
    }
    PlatformStatus.s.xNextState = State_INVALID;
  }
  
  switch(PlatformStatus.s.xCurrentState)
  {

  case State_Read:
    nStartSendTick = HAL_GetTick();
    TimerStop(&ReadTimer);
    TimerSetValue(&ReadTimer, PlatformStatus.s.SEND_INTERVAL);
    TimerStart(&ReadTimer);
    
  case State_ReadMems:
    {
#if USE_SHORTEN_JOIN_REQ_INTV
     if ( CHECK_LORA_JOIN () || ( PlatformStatus.s.nErrorNoAck != 0 ) )
#endif //USE_SHORTEN_JOIN_REQ_INTV
      {
#if defined(SENSOR_ENABLED)
        PRINTF_MAIN1("Enable and read sensors\r\n");
        PlatformStatus.s.xCurrentState = State_ReadMems;
#ifdef LORA_SMART_TRACKER
        LED_On( LED_WHITE );
#else
        LED_On( LED2 );
#endif    
        BSP_sensor_Enable();
        BSP_accelero_Enable();
        
        BSP_sensor_Read( &sensor_data );
        PRINTF_MAIN1("Got sensor data: T: %.2f H: %.2f P: %.2f\r\n", sensor_data.temperature, sensor_data.humidity, sensor_data.pressure );
        PRINTF_MAIN1("Accelerometer: X: %d Y: %d Z: %d\r\n", sensor_data.acceleration_x, sensor_data.acceleration_y, sensor_data.acceleration_z );
#endif //defined(SENSOR_ENABLED)
      }
    }
    //no break, continue reading the other sensors
  case State_ReadGnss:
    {
#if USE_SHORTEN_JOIN_REQ_INTV
      if ( CHECK_LORA_JOIN () || ( PlatformStatus.s.nErrorNoAck != 0 ) )
#endif //USE_SHORTEN_JOIN_REQ_INTV
      {
#if defined(GNSS_ENABLED)        
        PRINTF_MAIN2("Enable and read GNSS\r\n");
        PlatformStatus.s.xCurrentState = State_ReadGnss;
        TeseoReadData(GNSS_TIMEOUT_POLL);
        if( ( PlatformStatus.b.GNSS_SEND_WAIT ) && ( gnss_fix_validity == INVALID ) && ( HAL_GetTick() < ( nStartSendTick+GNSS_TIMEOUT_SEND )) )
        {
          PRINTF_MAIN1("Waiting for fix...\r\n");
#ifdef LORA_SMART_TRACKER
          LED_Toggle( LED_WHITE );
#else
          LED_Toggle( LED2 );
#endif    
          HAL_Delay(WAIT_FOR_FIX_POLL_INTERVAL);
          break;
        }
#endif //defined(GNSS_ENABLED)        
      }
    }
    //no break, continue sending the data
  case State_SaveData:
    {
      PlatformStatus.s.xCurrentState = State_SaveData;
      PRINTF_MAIN1("Save data\r\n");
      MsgQueue_enqueue();
      MsgQueue_print();
      if(tx_timer_event || TxTimer.IsStarted)
      {
        PlatformStatus.s.xNextState = State_Run;
        break;
      }
    }
    
  case State_Send:
    
  case State_RetrieveData:
    {
      PlatformStatus.s.xCurrentState = State_RetrieveData;
      PRINTF_MAIN1("Retrieve data\r\n");
      MsgQueue_read();
    }
    
  case State_SendData:
    {
      PlatformStatus.s.xCurrentState = State_SendData;
#ifdef LORA_SMART_TRACKER
        LED_On( LED_WHITE );
#else
        LED_On( LED2 );
#endif    
      PRINTF_MAIN1("Send data...\r\n");
      lastSendTick = HAL_GetTick();
      bLoraAck=false;
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
#if (LORAWAN_DEFAULT_CONFIRM_MSG_STATE == LORAWAN_CONFIRMED_MSG)
      if ( CHECK_LORA_JOIN () && bLoraAck )
      {
        PRINTF_MAIN1("ACK received -> item dequeued\r\n");
        MsgQueue_dequeue();
        if ( MsgQueue_isempty() )
          PlatformStatus.s.xNextState = State_Run;
        else
          PlatformStatus.s.xNextState = State_RetrieveData;
        
        nPacketsSent++;
        if(nTxWithoutLowPower)nTxWithoutLowPower--;
      }
      else
      {
        PRINTF_MAIN1("ACK not received -> item remains in queue\r\n");
        PlatformStatus.s.xNextState = State_Run;
      }
#else
      if ( CHECK_LORA_JOIN () )
      {
        MsgQueue_dequeue();
        PlatformStatus.s.xNextState = State_Run;
        
        nPacketsSent++;
        if(nTxWithoutLowPower)nTxWithoutLowPower--;
      }
#endif      
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
        BSP_sensor_Enable( );
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
#if defined(GNSS_ENABLED)
      TeseoReadData(GNSS_NO_TIMEOUT);
#endif //GNSS_ENABLED
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
      PRINTF("Sleep mode ON\r\n");
      HAL_Delay(500);

      LPM_SetOffMode(LPM_APPLI_Id , LPM_Disable );
      LPM_SetStopMode(LPM_APPLI_Id , LPM_Disable );
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
      PRINTF("Stop mode ON\r\n");
      HAL_Delay(500);

      LPM_SetOffMode(LPM_APPLI_Id , LPM_Disable );
      LPM_SetStopMode(LPM_APPLI_Id , LPM_Enable );
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
  BSP_PB_Init( BUTTON_USER, BUTTON_MODE_EXTI );
  
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
      .GNSS_SEND_WAIT = GNSS_SEND_WAIT_MODE_DEF,
      .GNSS_POLL_WAIT = GNSS_POLL_WAIT_MODE_DEF,
      .SEND_ON_WAKE_EVENT = SEND_ON_WAKE_EVENT_DEF,
      .SEND_ON_SENSOR_EVENT = SEND_ON_SENSOR_EVENT_DEF,
      .GPSTIME_IN_LPP = GPSTIME_IN_LPP_DEF,
      .EEPROM_DATA_CAN_BE_CHANGED = USE_EEPROM_SETTINGS
    },
    .s = {
      .GNSS_GEOFENCE_RADIUS = GNSS_GEOFENCE_RADIUS_DEF,
      .GNSS_GEOFENCE_MASK = GNSS_GEOFENCE_MASK_DEF,
      .LORA_DR = LORA_DR_DEF,
      .LORA_ADR = LORA_ADR_DEF,
      .SEND_INTERVAL = SEND_INTERVAL_DEF
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
  PlatformStatus.b.GNSS_SEND_WAIT = default_settings.b.GNSS_SEND_WAIT;
  PlatformStatus.b.GNSS_POLL_WAIT = default_settings.b.GNSS_POLL_WAIT;
  PlatformStatus.b.SEND_ON_WAKE_EVENT = default_settings.b.SEND_ON_WAKE_EVENT;
  PlatformStatus.b.SEND_ON_SENSOR_EVENT = default_settings.b.SEND_ON_SENSOR_EVENT;
  PlatformStatus.b.GPSTIME_IN_LPP = default_settings.b.GPSTIME_IN_LPP;
  
  PlatformStatus.s.GNSS_GEOFENCE_MASK = default_settings.s.GNSS_GEOFENCE_MASK;
  PlatformStatus.s.GNSS_GEOFENCE_RADIUS = default_settings.s.GNSS_GEOFENCE_RADIUS;
  PlatformStatus.s.LORA_DR = default_settings.s.LORA_DR;
  PlatformStatus.s.LORA_ADR = default_settings.s.LORA_ADR;
  PlatformStatus.s.SEND_INTERVAL = default_settings.s.SEND_INTERVAL;
  
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
  //no console huart
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
  CMD_Process();

  UserLedManager();
  if(PlatformStatus.s.xCurrentState != State_IdleAfterSend)
  {
    FlushSafePrintf();
    if( PlatformStatus.s.xCurrentState != State_INVALID )
    {
      UserButtonsManager();
    
#if TEST_BATTERY
      UserTestBattery();
#endif //TEST_BATTERY
      
#if defined(GNSS_ENABLED)
      UserGnssManager();
#endif //GNSS_ENABLED
      
#ifdef USB_ENABLED 
      ProcessTerminalString();
#endif /*USB_ENABLED*/
#if LORA_SMART_TRACKER
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
  int32_t latitude=0, longitude=0, altitudeGps=0, epoch_value=0;
  int32_t accelero_x, accelero_y, accelero_z;
  uint16_t battery_level16;
  uint16_t battery_voltage;
  //uint8_t battery_charge_percentage = 100;
  
  if ( CHECK_LORA_JOIN () != LORA_SET)
  {
    PRINTF_MAIN1("Not joined, sending join request\r\n");
    bWaitAck = FALSE;
    LORA_Join();
    return 0;
  }
  
  PRINTF_MAIN1("SEND REQUEST\r\n");
  
#ifdef USE_B_L072Z_LRWAN1
  TimerInit( &TxLedTimer, OnTimerLedEvent );
  
  TimerSetValue(  &TxLedTimer, 200);
  
  BSP_LED_On( LED_RED1 ) ; 
  
  TimerStart( &TxLedTimer );  
#endif

  battery_level16 = (uint16_t)(BSP_GetBatteryLevel16()/10);
  battery_voltage = (uint16_t) (battery_level16/10);               /* Battery level expressed in in hundreds of mV */
  //battery_charge_percentage = 100; //BSP_BatteryChargePercentage(battery_level16);  TBD

  uint8_t cchannel=0;
  temperature = data_logged.temperature; 
  pressure    = data_logged.pressure; 
  humidity    = data_logged.humidity; 
  latitude    = data_logged.latitude; 
  longitude   = data_logged.longitude; 
  altitudeGps = data_logged.altitudeGps; 
  epoch_value = data_logged.epoch_value; 
  
  accelero_x =  ( int32_t )( data_logged.accelero_x ); 
  accelero_y =  ( int32_t )( data_logged.accelero_y );
  accelero_z =  ( int32_t )( data_logged.accelero_z );

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
  
  AppData.Buff[i++] = cchannel++;
  AppData.Buff[i++] = LPP_DATATYPE_ACCELEROMETER;
  AppData.Buff[i++] = ( accelero_x >> 8 ) & 0xFF;
  AppData.Buff[i++] = accelero_x & 0xFF;
  AppData.Buff[i++] = ( accelero_y >> 8 ) & 0xFF;
  AppData.Buff[i++] = accelero_y & 0xFF;
  AppData.Buff[i++] = ( accelero_z >> 8 ) & 0xFF;
  AppData.Buff[i++] = accelero_z & 0xFF;

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
    AppData.Buff[i++] = (epoch_value & 0xFF);  // LSB value
  }
#endif  /* REGION_XX915 */
      
  AppData.BuffSize = i;
  
  PRINTF_MAIN1("SENDING:\r\n");
  PRINTF_MAIN1("  T: %.2f H: %.2f P:%.2f\r\n", sensor_data.temperature, sensor_data.humidity, sensor_data.pressure );
  PRINTF_MAIN1("  AccX:%d AccY:%d AccZ:%d\r\n", sensor_data.acceleration_x, sensor_data.acceleration_y, sensor_data.acceleration_z );
  PRINTF_MAIN1("  LAT:%.4f LON:%.4f ALT:%.2f\r\n", sensor_data.latitude, sensor_data.longitude, sensor_data.altitudeGps );
  PRINTF_MAIN1("  Batt: %.2fV\r\n", (float)battery_level16/100.0);
  PRINTF_MAIN1("  Epoch: %d\r\n", epoch_value);

  uint8_t RetVal = LORA_send( &AppData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE);
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
  /* USER CODE END 4 */
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
    TimerSetValue( &TxTimer,  SEND_INTERVAL_FIRST_TIME);
}

/**
  * @brief  Read timer callback function
  * @param  None
  * @retval None
  */
static void OnReadTimerEvent( void*c )
{
  read_timer_event = true;
}

/**
  * @brief  Start the tx process
  * @param  None
  * @retval None
  */
static void LoraStartReadTimer()
{
    /* send everytime timer elapses */
    TimerInit( &ReadTimer, OnReadTimerEvent );
    TimerSetValue( &ReadTimer,  SEND_INTERVAL_FIRST_TIME);
    //OnReadTimerEvent(NULL);
    TimerStart( &ReadTimer );
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

#ifdef USE_B_L072Z_LRWAN1
static void OnTimerLedEvent( void*c )
{
#ifdef LORA_SMART_TRACKER
  
#else //LORA_SMART_TRACKER
  LED_Off( LED_RED1 ) ; 
  PRINTF_MAIN1(">> led event\r\n");
#endif //LORA_SMART_TRACKER
}
#endif

/**
  * @brief  Config GPIO
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStruct;
  
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  /* Configure GPIO pin Output Level */
  GNSS_RST_PIN_SET();
  
  /* Configure Reset */
  GPIO_InitStruct.Pin = GNSS_RST_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GNSS_RST_PORT, &GPIO_InitStruct);
  
  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GNSS_WAKEUP_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GNSS_WAKEUP_PORT, &GPIO_InitStruct);
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
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1201");//default 0x00980056
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1210");//default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1211");//default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1228");//default 0x00020000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1229");//default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1230");//default 0x00000000
    HAL_Delay(GNSS_CMD_DELAY);
    GNSS_DATA_SendCommand(&pGNSS, "$PSTMGETPAR,1268");//default 0x00000000
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
  * @brief  TeseoConsumerTask function
  * @param  const * argument
  * @retval None
  */
void TeseoConsumerTask(void const * argument)
{
#if (configUSE_ODOMETER == 1) || (configUSE_GEOFENCE == 1) || (configUSE_DATALOG == 1)
  int gnss_feature = 0x0;
#endif
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
  
  //PRINTF_MAIN1("Teseo Consumer Task running\r\n");
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

    //PRINTF_MAIN1("got ");
    //(check == GNSS_PARSER_OK) ? PRINTF_MAIN1("Good sentence: ") : PRINTF_MAIN1("!!!Bad sentence: ");
    //PRINTF_MAIN1((uint8_t *)gnssMsg->buf);
    //PRINTF_MAIN1("\r\n");


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
            PRINTF_MAIN1("%.2d/%.2d/%.2d %.2d:%.2d:%.2d - %d sats - Fix %d\r\n",
                              GNSSParser_Data.gprmc_data.date/10000,(GNSSParser_Data.gprmc_data.date%10000)/100,GNSSParser_Data.gprmc_data.date%100,
                              GNSSParser_Data.gpgga_data.utc.hh,GNSSParser_Data.gpgga_data.utc.mm,GNSSParser_Data.gpgga_data.utc.ss, 
                              GNSSParser_Data.gpgga_data.sats, GNSSParser_Data.gpgga_data.valid);

        if(PlatformStatus.b.GPSTIME_IN_LPP)
          {
            /* RTC data are updated using information coming from GNSS */
            if ((gnss_fix_validity) && ((!PlatformStatus.b.RTC_UPDATED) || (PlatformStatus.s.RTC_TRIGGER_VALUE != GNSSParser_Data.gpgga_data.utc.hh)))
            {
              rtc_time.Hours = (uint8_t) GNSSParser_Data.gpgga_data.utc.hh;
              rtc_time.Minutes = (uint8_t) GNSSParser_Data.gpgga_data.utc.mm;
              rtc_time.Seconds = (uint8_t) GNSSParser_Data.gpgga_data.utc.ss;
              
              /* Ready to set date */
              HW_RTC_SetTimeValue(&rtc_time);
              
              /* Get the RTC date */
              HW_RTC_GetTimeValue(&rtc_time);
              
              PRINTF_MAIN1("\r\nRTC time set to: %.2d:%.2d:%.2d (hh:mm:ss UTC time)\r\n", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds);      
              
              rtc_date.Date = GNSSParser_Data.gprmc_data.date/10000;
              rtc_date.Month = (GNSSParser_Data.gprmc_data.date%10000)/100;
              rtc_date.Year  = GNSSParser_Data.gprmc_data.date%100;
              
              /* Ready to set date */
              HW_RTC_SetDateValue(&rtc_date);
              
              /* Get the RTC date */
              HW_RTC_GetDateValue(&rtc_date);
              
              PRINTF_MAIN1("\r\nRTC date set to: %s %.2d-%s-%.2d \r\n", BSP_RTC_GetWeekDayName(rtc_date.WeekDay), rtc_date.Date, BSP_RTC_GetMonthName(rtc_date.Month),rtc_date.Year);
              
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
          }
          if(GNSSParser_Data.geofence_data.status[GEOFENCE_CATANIA] != 0)
          {
            PRINTF_MAIN1("GEOFENCE_%d (ST CT): %d %s\r\n", GEOFENCE_CATANIA, GNSSParser_Data.geofence_data.status[GEOFENCE_CATANIA], geofenceCirclePosition[GNSSParser_Data.geofence_data.status[GEOFENCE_CATANIA]]);
          }
          if(GNSSParser_Data.geofence_data.status[GEOFENCE_CUR_COORDS] != 0)
          {
            PRINTF_MAIN1("GEOFENCE_%d ( LOC ): %d %s\r\n", GEOFENCE_CUR_COORDS, GNSSParser_Data.geofence_data.status[GEOFENCE_CUR_COORDS], geofenceCirclePosition[GNSSParser_Data.geofence_data.status[GEOFENCE_CUR_COORDS]]);
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
  if(PlatformStatus.b.SW1_OA == 0)
  {
    PlatformStatus.b.GNSS_INITED = 0;
  }
  if (PlatformStatus.b.GNSS_INITED == 0)
  {
//    BSP_PowerGNSS(DISABLE);
    GNSS_Bus_Reset(&pGNSS);
    
    PRINTF_MAIN2("\r\nGNSS_PARSER_Init()\r\n");
    GNSS_PARSER_Init(&GNSSParser_Data);
    
//    BSP_PowerGNSS(ENABLE);
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
  
  TeseoManageCommands();
  
  uint32_t nEndTick = HAL_GetTick() + nTimeout;
  //while(bGPGGA_Received == 0 || bGPRMC_Received == 0) //retry if no rmc or gga DANALF TBD
  if(bGPGGA_Received == 0 || bGPRMC_Received == 0) //retry if no rmc or gga
  {
    if(bGPGGA_Received == 0 || bGPRMC_Received == 0)
    {
      PRINTF_MAIN1("\r\nReset Teseo serial port\r\n");
      static uint32_t nTeseoReset = 0;
      if(nTeseoReset++ > 5/*NUM_GNSS_LOOPS_WITHOUT_DATA*/)
      {
        nTeseoReset = 0;
        PlatformStatus.b.GNSS_INITED = 0;
      }
      GNSS_Bus_Disable(&pGNSS);
      GNSS_Bus_Enable(&pGNSS);
    }

    TeseoConsumerTask(NULL);
    if( HAL_GetTick() > nEndTick )
    {
      //break;  DANALF TBD
    }
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
  TimerSetValue( &TeseoReadTimer,  TESEO_READ_DUTYCYCLE);
  OnTeseoReadTimerEvent();
#endif //defined(SENSOR_ENABLED)
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
  TimerStart( &SleepTimer );
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
    TimerSetValue(&SleepTimer, SLEEP_TIMER_DUTYCYCLE);
    TimerStart(&SleepTimer);
  }
}

/**
  * @brief  Get Teseo Data
  * @param  None
  * @retval None
  */
void GetTeseoData (int32_t* pnLatitude, int32_t* pnLongitude , int32_t* pnAltitudeGps, uint8_t *bFixValidity)
{
#if defined(GNSS_ENABLED)
  TeseoReadData(GNSS_TIMEOUT_POLL);
#endif //GNSS_ENABLED  
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
  if(LORAWAN_DEFAULT_CONFIRM_MSG_STATE==LORAWAN_CONFIRMED_MSG)
  {
    nLoraDR = dr;
  }
  else
  {
    nLoraDR = true;
  }
}

/* Queue management functions */

static void MsgQueue_init(void)
{
  MsgQueue.head = 0;
  MsgQueue.length = 0;
}

static int MsgQueue_isempty(void)
{
  return (MsgQueue.length==0);
}

static int MsgQueue_isfull(void)
{
  return (MsgQueue.length==MSGQUEUE_LEN);
}

static void MsgQueue_enqueue(void)
{
  LogData_t e;
  uint16_t mSeconds;
    
  e.AccEnable = accActInact;
  e.temperature = (  int16_t )( sensor_data.temperature * 10 );     /* in °C * 10 */
  e.pressure    = ( uint16_t )( sensor_data.pressure * 10 );        /* in hPa / 10 */
  e.humidity    = ( uint16_t )( sensor_data.humidity * 2 );         /* in %*2     */

  e.accelero_x  = ( int32_t )( sensor_data.acceleration_x );
  e.accelero_y  = ( int32_t )( sensor_data.acceleration_y );
  e.accelero_z  = ( int32_t )( sensor_data.acceleration_z );
  
  e.latitude    = ( int32_t )( sensor_data.latitude * 10000 );
  e.longitude   = ( int32_t )( sensor_data.longitude * 10000 );
  e.altitudeGps = ( int32_t )( sensor_data.altitudeGps * 100 );
  
  e.batteryLevel = (uint32_t) (BSP_GetBatteryLevel16()/10);
  e.epoch_value = HW_RTC_GetCalendarTime(&mSeconds);
  e.sentFlag = 0;

  if ( MsgQueue_isfull() )
  {
    PRINTF_MAIN1("Can't enqueue -- MsgQueue is full\r\n");
    return;
  }
  MsgQueue.array[(MsgQueue.head + MsgQueue.length) % MSGQUEUE_LEN] = e;
  MsgQueue.length++;

  PRINTF_MAIN1("[ Saved msg with epoch %d ]\r\n",e.epoch_value);
}

static void MsgQueue_dequeue(void)
{
  if (!MsgQueue_isempty())
  {
    PRINTF_MAIN1("[ Dequque msg with epoch %d ]\r\n",MsgQueue.array[MsgQueue.head].epoch_value);
    MsgQueue.head = (MsgQueue.head + 1) % MSGQUEUE_LEN;
    MsgQueue.length--;
  }
  else
    PRINTF_MAIN1("Queue is empty\r\n");
}

static void MsgQueue_read(void)
{
  if (!MsgQueue_isempty())
  {
    PRINTF_MAIN1("[ Read msg with epoch %d ]\r\n",MsgQueue.array[MsgQueue.head].epoch_value);
    data_logged = MsgQueue.array[MsgQueue.head];
  }
  else
    PRINTF_MAIN1("Can't read -- Queue is empty\r\n");
}

static void MsgQueue_print(void)
{
  int i;
  
  PRINTF_MAIN1("[ MsgQueue H=%d L=%d ][ ",MsgQueue.head,MsgQueue.length);
  for (i=0;i<MsgQueue.length;i++)
    PRINTF_MAIN1("%d ",MsgQueue.array[(MsgQueue.head+i)%MSGQUEUE_LEN].epoch_value);
  PRINTF_MAIN1("]\r\n");
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
