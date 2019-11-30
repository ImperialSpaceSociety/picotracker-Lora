/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: contains all hardware driver

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
/**
  ******************************************************************************
  * @file    bsp.h
  * @author  MCD Application Team
  * @version V1.1.5
  * @date    30-March-2018
  * @brief   This file contains definitions and prototypes realted to interface
  *          functions among BSP and application levels
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

    
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_H__
#define __BSP_H__

#ifdef __cplusplus
 extern "C" {
#endif
    

/** @addtogroup PROJECTS PROJECTS
  * @{
  */
   
/** @addtogroup STEVAL-STRKT01 STEVAL-STRKT01
  * @{
  */  
   
/** @addtogroup STEVAL-STRKT01_ASSET_TRACKER Asset Tracker
  * @{
  */    
    
/** @addtogroup STEVAL-STRKT01_LoRaWAN LoRaWAN
  * @{
 */

/** @addtogroup STEVAL-STRKT01_BSP_INTERFACE BSP Interface
  * @{
 */

/** @defgroup STEVAL-STRKT01_APP_BSP BSP App
  * @brief Interface among BSP and application levels
  * @{
  */ 
   
/* Includes ------------------------------------------------------------------*/
#include "hw.h"
  
#ifdef LORA_SMART_TRACKER
#include "LoRaTracker_motion_sensors.h"
#include "LoRaTracker_motion_sensors_ex.h"
#include "LoRaTracker_batterycharger.h"
#endif //LORA_SMART_TRACKER

/** @defgroup STEVAL-STRKT01_APP_BSP_Exported_Types BSP Exported Types
  * @brief Exported types.
  * @{
  */  
   
/* Exported types ------------------------------------------------------------*/

typedef enum 
{
  STARTUP_AFTER_POWER_ON_RESET = 0x01,
  STARTUP_AFTER_SOFTWARE_RESET = 0x02,
  STARTUP_AFTER_PIN_RESET      = 0x03
} StartupMode_t;
   
typedef struct{
  float pressure;          /* in mbar */  
  float temperature;       /* in °C   */
  float humidity;          /* in %    */

  float latitude;
  float longitude ;
  float altitudeGps;       /* in m */

  int16_t altitudeBar ;    /* in m * 10 */
  
  int32_t acceleration_x;
  int32_t acceleration_y;
  int32_t acceleration_z;
  
  /**more may be added*/
} sensor_t;


typedef enum { 
  State_UltraLowPower,
  State_PrepareUltraLowPower,
  State_LowPower,
  State_PrepareLowPower,
  State_Run, 
  State_Read,
  State_ReadMems,
  State_ReadGnss,
  State_SaveData,
  State_Send,
  State_RetrieveData,
  State_SendData,
  State_IdleAfterSend,
  State_CheckAck,
  State_INVALID
} SystemState_t;


/**
 * @brief   Lora Tracker system status 
 * @details This variable stores the status of Lora Smart Tracker system
 */
typedef struct
{
  struct
  {
    uint8_t EEPROM_DATA_INITED          :       1;
    uint8_t RESTART_PENDING             :       1;
    StartupMode_t STARTUP_MODE          :       2;
    uint8_t LP_SLEEP_TIMER              :       1;
    uint8_t LP_SENSOR_EVENT             :       1;
    uint8_t LOG_MANAGER                 :       1;
    uint8_t SW1_OA                      :       1;
    uint8_t SW1_OB                      :       1;
    uint8_t SW2_OA                      :       1;
    uint8_t SW2_OB                      :       1;
    uint8_t USB_CONNECTED               :       1;
    uint8_t USB_DBG                     :       1;
    uint8_t USB_TRACE                   :       1;
    uint8_t GNSS_INITED                 :       1;
    uint8_t EEPROM_FORMATTED            :       1;
    uint8_t GNSS_WAIT_FIX               :       1;
    uint8_t GNSS_FIX_CHECK              :       1;
    uint8_t EEPROM_DATA_CAN_BE_CHANGED  :       1;
    uint8_t SEND_ON_WAKE_EVENT          :       1;
    uint8_t SEND_ON_SENSOR_EVENT        :       1;
    uint8_t RTC_UPDATED                 :       1;
    uint8_t GPSTIME_IN_LPP              :       1;
    uint8_t APP_LORA_JOINED             :       1;
    uint8_t SHORTEN_JOIN_REQ_INTV       :       1;
    uint8_t LORA_ACK_ENABLED            :       1;
    uint8_t WELCOME_MESSAGE_PENDING     :       1;
    uint8_t _Reserved_27_31             :       5;
  } b;
  
  struct
  {
    SystemState_t xCurrentState;
    SystemState_t xNextState;
    SystemState_t xPrevState;
    uint8_t GNSS_GEOFENCE_MASK;
    uint32_t GNSS_GEOFENCE_RADIUS;
    float GNSS_GEOFENCE_LAT;
    float GNSS_GEOFENCE_LON;
    int32_t RTC_TRIGGER_VALUE;
    uint32_t SEND_INTERVAL;
    uint8_t LORA_DR;
    uint8_t LORA_ADR;
    uint16_t lastReadIndex;
    uint16_t lastSavedIndex;
    uint8_t nErrorNoAck;
    uint8_t _Reserved8;
    uint32_t TX_TIMER_INTERVAL;
  } s;
  uint32_t nFwVersion;
} PlatformStatus_t;


/**
 * @brief   Accelerometer Act_Inact status
 * @details This variable stores the status of accelemeter activity, inactivity
 */
typedef enum
{
  ACC_INACTIVITY = 0,
  ACC_ACTIVITY = 1
} AccStatusTypeDef;

/**
  * @}
  */


/** @defgroup STEVAL-STRKT01_APP_BSP_Exported_Constants BSP Exported Constants
  * @brief Exported constants
  * @{
  */  

/* Exported constants --------------------------------------------------------*/

/**
  * @}
  */


/** @defgroup STEVAL-STRKT01_APP_BSP_External_Variables BSP External Variables
  * @brief External variables
  * @{
  */ 

/* External variables --------------------------------------------------------*/

extern PlatformStatus_t PlatformStatus;
extern sensor_t sensor_data;
extern volatile uint8_t mems_int1_detected;
extern volatile uint8_t mems_int2_detected;
extern AccStatusTypeDef accActInact;

/**
  * @}
  */

/** @defgroup STEVAL-STRKT01_APP_BSP_Exported_Macros BSP Exported Macros
  * @brief Exported macros.
  * @{
  */

/* Exported macros -----------------------------------------------------------*/

#define IS_STATE_NOT_LOCKED(s)      ((s == State_UltraLowPower) \
                                  || (s == State_LowPower) \
                                  || (s == State_Run))


/**
  * @}
  */


/** @defgroup STEVAL-STRKT01_APP_BSP_Exported_Defines BSP Exported Definitions
  * @brief Exported definitions.
  * @{
  */

/* Exported defines ----------------------------------------------------------*/
#define NOT_VALID_INPUT                 0
#define VALID_INPUT                     1
#define VBAT_LOW                        2
#define END_OF_CHARGING                 3
#define CHARGING_PHASE                  4
#define OVER_CHARGE_FAULT               5
#define CHARGING_TIMEOUT                6
#define BATTERY_VOLTAGE_BELOW_VPRE      7
#define CHARGING_THERMAL_LIMITATION     8
#define BATTERY_TEMPERATURE_FAULT       9
#define UNKNOWN                         10

#define GEOFENCE_LECCE                  5
#define GEOFENCE_CATANIA                6
#define GEOFENCE_CUR_COORDS             7

#define ABS(F)                          ((F>=0)?(F):(-F))
#define LAT_NORD_SUD(L)                 ((L>=0)?('N'):('S'))
#define LON_EAST_WEST(L)                ((L>=0)?('E'):('W'))

/* Enable sensor masks */
#define PRESSURE_SENSOR                         0x00000001U
#define TEMPERATURE_SENSOR                      0x00000002U
#define HUMIDITY_SENSOR                         0x00000004U
//#define UV_SENSOR                               0x00000008U    /* Reserved for future use */
#define ACCELEROMETER_SENSOR                    0x00000010U
//#define GYROSCOPE_SENSOR                        0x00000020U    /* Reserved for future use */
//#define MAGNETIC_SENSOR                         0x00000040U    /* Reserved for future use */
#define INACTIVITY_DURATION                     1                /* The unit is worth approximately 40 seconds. Use 1 for test purposes. 7 as standard value (7*40 = 280s) */
#define RESITOR_DIVIDER_PROD                    ((56000.0+27000.0)/56000.0)
#define RESITOR_DIVIDER                         (float)(RESITOR_DIVIDER_PROD)

#define EEPROM_ADDR_START                       0x08080000       /* Start @ of STM32 internal EEPROM area */

#define DEVICE_EUI_EEPROM_ID                    (1)
#define DEVICE_EUI_EEPROM_OFFSET                (0)
#define DEVICE_EUI_EEPROM_LEN                   (8)
#define DEVICE_EUI_EEPROM_ADDRESS               (uint32_t)(EEPROM_ADDR_START + DEVICE_EUI_EEPROM_OFFSET)

#define JOIN_EUI_EEPROM_ID                      (2)
#define JOIN_EUI_EEPROM_OFFSET                  (DEVICE_EUI_EEPROM_OFFSET + DEVICE_EUI_EEPROM_LEN)
#define JOIN_EUI_EEPROM_LEN                     (8)
#define JOIN_EUI_EEPROM_ADDRESS                 (uint32_t)(EEPROM_ADDR_START + JOIN_EUI_EEPROM_OFFSET)

#define APP_KEY_EEPROM_ID                       (4)
#define APP_KEY_EEPROM_OFFSET                   (DEVICE_EUI_EEPROM_OFFSET + DEVICE_EUI_EEPROM_LEN + JOIN_EUI_EEPROM_LEN)
#define APP_KEY_EEPROM_LEN                      (16)
#define APP_KEY_EEPROM_ADDRESS                  (uint32_t)(EEPROM_ADDR_START + APP_KEY_EEPROM_OFFSET)

#define NWK_KEY_EEPROM_ID                       (8)
#define NWK_KEY_EEPROM_OFFSET                   (DEVICE_EUI_EEPROM_OFFSET + DEVICE_EUI_EEPROM_LEN + JOIN_EUI_EEPROM_LEN + APP_KEY_EEPROM_LEN)
#define NWK_KEY_EEPROM_LEN                      (16)
#define NWK_KEY_EEPROM_ADDRESS                  (uint32_t)(EEPROM_ADDR_START + NWK_KEY_EEPROM_OFFSET)

#define PLATFORM_STATUS_EEPROM_OFFSET           (64)
#define PLATFORM_STATUS_EEPROM_ADDRESS          (EEPROM_ADDR_START + PLATFORM_STATUS_EEPROM_OFFSET)
#define PLATFORM_STATUS_EEPROM_LEN              sizeof(PlatformStatus_t)

    
    
/**
  * @}
  */




/** @defgroup STEVAL-STRKT01_BSP_INTERFACE_BSP_Exported_FunctionsPrototype BSP Exported Functions Prototypes
  * @brief Exported functions prototypes.
  * @{
  */


/* Exported functions ------------------------------------------------------- */ 

void  BSP_sensor_Init( void  );
void  BSP_sensor_DeInit( void );
uint8_t BSP_GetBatteryLevel( void );
uint8_t BSP_BatteryChargePercentage(uint16_t BatteryLevel);
void WriteInternalEepromBuffer(uint32_t dest_addr, uint32_t num_bytes, uint8_t *buffer_to_write);
uint8_t EepromLoraKeysValidation(void);

#ifdef LORA_SMART_TRACKER
void LoadLoraKeys( void );
void BSP_memory_Init( void );
void BSP_power_Init( void  );
void BSP_BoardShutdown( void );
uint8_t BSP_GetChargerStatus( void );
void BSP_GnssManageBootPins(uint8_t bBootMode);
void BSP_GnssWakeup(FunctionalState status);
void BSP_PowerGNSS(FunctionalState status);
void BSP_PowerEEPROM(FunctionalState status);
void BSP_PowerTypeCCtrl(FunctionalState status);
void BSP_PowerSensors(FunctionalState status);
void BSP_LIS2DW12_IO_ITConfig(FunctionalState status);
uint8_t GetWakeButtonPushed(void);
#endif //LORA_SMART_TRACKER
uint8_t GetUserButtonPushed(void);

void PrintChargerStatus(uint8_t s);
void PrintSystemState(SystemState_t s);
void PrintStartupMode(StartupMode_t mode);
void BSP_PlatformStatus_Init(void);
void BSP_PlatformStatus_Check(PlatformStatus_t *default_values);
void BSP_LoadPlatformStatusFromEeprom(void);
void BSP_SavePlatformStatusToEeprom(void);
uint16_t BSP_GetBatteryLevel16(void);
void SystemInterruptManager (void);
void SystemResetHook(void);  


void BSP_sensor_Enable( void );
void BSP_sensor_Disable( void );
void BSP_sensor_Read( sensor_t *pSensorData );
void BSP_accelero_Init( bool quiet );
void BSP_accelero_Enable( void );
void BSP_accelero_Disable( void );


/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __BSP_H__ */


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
