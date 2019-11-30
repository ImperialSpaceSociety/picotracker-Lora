 /**
  ******************************************************************************
  * @file    bsp.c
  * @author  MCD Application Team
  * @version V1.1.5
  * @date    30-March-2018
  * @brief   This file includes interface functions among BSP and application levels
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

/** @addtogroup STEVAL-STRKT01_APP_BSP BSP App
  * @{
  */ 
   
  /* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "hw.h"
#include "timeServer.h"
#include "bsp.h"

#if LORA_SMART_TRACKER
#include "w752535.h"
#include "LoRaTracker_batterycharger.h"
#include "LoRaTracker_gnss.h"
#include "usb_device.h"
#endif // LORA_SMART_TRACKER


#if defined(LRWAN_NS1)
#include "lrwan_ns1_humidity.h"
#include "lrwan_ns1_pressure.h"
#include "lrwan_ns1_temperature.h"
#else  /* not LRWAN_NS1 */
#if defined(SENSOR_ENABLED)

#if LORA_SMART_TRACKER
#include "LoRaTracker_env_sensors.h"

#else // LORA_SMART_TRACKER
#if defined (X_NUCLEO_IKS01A1)
#warning "Do not forget to select X_NUCLEO_IKS01A1 files group instead of X_NUCLEO_IKS01A2"
#include "x_nucleo_iks01a1_humidity.h"
#include "x_nucleo_iks01a1_pressure.h"
#include "x_nucleo_iks01a1_temperature.h"
#else  /* not X_NUCLEO_IKS01A1 */
#include "x_nucleo_iks01a2_humidity.h"
#include "x_nucleo_iks01a2_pressure.h"
#include "x_nucleo_iks01a2_temperature.h"
#include "x_nucleo_iks01a2_accelero.h"
#endif  /* X_NUCLEO_IKS01A1 */

#endif // LORA_SMART_TRACKER
#endif  /* SENSOR_ENABLED */

#endif  /* LRWAN_NS1 */

/** @addtogroup STEVAL-STRKT01_APP_BSP_Private_TypesDefinitions BSP Private Types Definitions
  * @brief Private types definitions
  * @{
 */

/* Private typedef -----------------------------------------------------------*/

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_BSP_Private_Defines BSP Private Definitions
  * @brief Private definitions
  * @{
 */

/* Private define ------------------------------------------------------------*/
#define STBC02_CMD_TIMEOUT 200

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_BSP_Private_Macros BSP Private Macros
  * @brief Private macros
  * @{
 */

/* Private macro -------------------------------------------------------------*/

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_BSP_Private_Variables BSP Private Variables
  * @brief Private variables
  * @{
 */

/* Private variables ---------------------------------------------------------*/

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_BSP_Private_FunctionPrototypes BSP Private Function Prototypes
  * @brief Private function prototypes
  * @{
 */

/* Private function prototypes -----------------------------------------------*/
static void MSP_USB_InitStatus(FunctionalState status);
void SensorsRecovery(void);

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_BSP_Exported_Variables BSP Exported Variables
  * @brief Exported variables
  * @{
 */

/* Exported variables --------------------------------------------------------*/

#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)
extern volatile uint32_t SensorsEnabled; /* This "redundant" line is here to fulfil MISRA C-2012 rule 8.4 */
volatile uint32_t SensorsEnabled = 0; 
#endif

#ifdef LORA_SMART_TRACKER
void *M95M02_handle = NULL;
volatile uint8_t bWakeButtonPushed = 0;
extern uint8_t STUSB1600_int_detected;
extern uint8_t STBC02_nCHG_int_detected;
#endif

volatile uint8_t mems_int1_detected;
volatile uint8_t mems_int2_detected;
AccStatusTypeDef accActInact;
volatile uint8_t bUserButtonPushed = 0;

sensor_t sensor_data;
PlatformStatus_t PlatformStatus;

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_BSP_Public_Functions BSP Public Functions
  * @brief Public functions
  * @{
 */

/**
  * @brief Initialization of Platform status structure
  * @param none
  * @retval none
  */
void BSP_PlatformStatus_Init(void)
{
  memset(&PlatformStatus, 0x00, sizeof(PlatformStatus_t));
  BSP_LoadPlatformStatusFromEeprom();
  PlatformStatus.b.SW1_OA = DISABLE;
  PlatformStatus.b.SW1_OB = DISABLE;
  PlatformStatus.b.SW2_OA = DISABLE;
  PlatformStatus.b.SW2_OB = DISABLE;
  PlatformStatus.b.USB_CONNECTED = DISABLE;
  PlatformStatus.b.USB_DBG = DISABLE;
  PlatformStatus.b.USB_TRACE = ENABLE;
  PlatformStatus.b.RTC_UPDATED = RESET;
  PlatformStatus.s.xCurrentState = State_Run;
}

/**
  * @brief Check Platform status structure
  * @param none
  * @retval none
  */
void BSP_PlatformStatus_Check(PlatformStatus_t *default_values)
{
  if(PlatformStatus.b.EEPROM_DATA_INITED == 0 && default_values->b.EEPROM_DATA_CAN_BE_CHANGED==1 )
  {
    PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED = default_values->b.EEPROM_DATA_CAN_BE_CHANGED;
    PlatformStatus.b.LP_SLEEP_TIMER = default_values->b.LP_SLEEP_TIMER;
    PlatformStatus.b.LP_SENSOR_EVENT = default_values->b.LP_SENSOR_EVENT;
    PlatformStatus.b.LOG_MANAGER = default_values->b.LOG_MANAGER;
    PlatformStatus.b.GNSS_WAIT_FIX = default_values->b.GNSS_WAIT_FIX;
    PlatformStatus.b.GNSS_FIX_CHECK = default_values->b.GNSS_FIX_CHECK;
    PlatformStatus.b.SEND_ON_WAKE_EVENT = default_values->b.SEND_ON_WAKE_EVENT;
    PlatformStatus.b.SEND_ON_SENSOR_EVENT = default_values->b.SEND_ON_SENSOR_EVENT;
    PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED = default_values->b.EEPROM_DATA_CAN_BE_CHANGED;
    PlatformStatus.b.GPSTIME_IN_LPP = default_values->b.GPSTIME_IN_LPP;
    PlatformStatus.b.SHORTEN_JOIN_REQ_INTV = default_values->b.SHORTEN_JOIN_REQ_INTV;
    PlatformStatus.b.LORA_ACK_ENABLED = default_values->b.LORA_ACK_ENABLED;
    
    PlatformStatus.s.GNSS_GEOFENCE_MASK = default_values->s.GNSS_GEOFENCE_MASK;
    PlatformStatus.s.GNSS_GEOFENCE_RADIUS = default_values->s.GNSS_GEOFENCE_RADIUS;
    PlatformStatus.s.LORA_DR = default_values->s.LORA_DR;
    PlatformStatus.s.LORA_ADR = default_values->s.LORA_ADR;
    PlatformStatus.s.SEND_INTERVAL = default_values->s.SEND_INTERVAL;
    PlatformStatus.s.TX_TIMER_INTERVAL = default_values->s.TX_TIMER_INTERVAL;
    
    PlatformStatus.b.EEPROM_DATA_INITED = 1;
    PlatformStatus.nFwVersion = IOT_TRACKER_APP_VER;
    BSP_SavePlatformStatusToEeprom();
  }
}

/**
  * @brief Initialization of Platform status structure
  * @param none
  * @retval none
  */
void BSP_LoadPlatformStatusFromEeprom(void)
{
  PlatformStatus_t tempPlatformStatus;
  memset(&tempPlatformStatus, 0x00, sizeof(PlatformStatus_t));
#if SAVE_PLATFORM_STATUS_IN_INTERNAL_EEPROM
  memcpy((void*)&tempPlatformStatus, (void*)PLATFORM_STATUS_EEPROM_ADDRESS, PLATFORM_STATUS_EEPROM_LEN);
#endif //SAVE_PLATFORM_STATUS_IN_INTERNAL_EEPROM
  if(tempPlatformStatus.nFwVersion == IOT_TRACKER_APP_VER)
  {
  /* Copy the following items */
  PlatformStatus.nFwVersion = tempPlatformStatus.nFwVersion;
  
  PlatformStatus.b.LP_SLEEP_TIMER = tempPlatformStatus.b.LP_SLEEP_TIMER;
  PlatformStatus.b.LP_SENSOR_EVENT = tempPlatformStatus.b.LP_SENSOR_EVENT;
  PlatformStatus.b.LOG_MANAGER = tempPlatformStatus.b.LOG_MANAGER;
  PlatformStatus.b.GNSS_WAIT_FIX = tempPlatformStatus.b.GNSS_WAIT_FIX;
  PlatformStatus.b.GNSS_FIX_CHECK = tempPlatformStatus.b.GNSS_FIX_CHECK;
  PlatformStatus.b.EEPROM_FORMATTED = tempPlatformStatus.b.EEPROM_FORMATTED;
  PlatformStatus.b.SEND_ON_WAKE_EVENT = tempPlatformStatus.b.SEND_ON_WAKE_EVENT;
  PlatformStatus.b.SEND_ON_SENSOR_EVENT = tempPlatformStatus.b.SEND_ON_SENSOR_EVENT;
  PlatformStatus.b.GPSTIME_IN_LPP = tempPlatformStatus.b.GPSTIME_IN_LPP;
  PlatformStatus.b.SHORTEN_JOIN_REQ_INTV = tempPlatformStatus.b.SHORTEN_JOIN_REQ_INTV;
  PlatformStatus.b.LORA_ACK_ENABLED = tempPlatformStatus.b.LORA_ACK_ENABLED;
  PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED = tempPlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED;
  
  PlatformStatus.s.GNSS_GEOFENCE_MASK = tempPlatformStatus.s.GNSS_GEOFENCE_MASK;
  PlatformStatus.s.GNSS_GEOFENCE_RADIUS = tempPlatformStatus.s.GNSS_GEOFENCE_RADIUS;
  PlatformStatus.s.GNSS_GEOFENCE_LAT = tempPlatformStatus.s.GNSS_GEOFENCE_LAT;
  PlatformStatus.s.GNSS_GEOFENCE_LON = tempPlatformStatus.s.GNSS_GEOFENCE_LON;
  PlatformStatus.s.LORA_DR = tempPlatformStatus.s.LORA_DR;
  PlatformStatus.s.LORA_ADR = tempPlatformStatus.s.LORA_ADR;
  PlatformStatus.s.SEND_INTERVAL = tempPlatformStatus.s.SEND_INTERVAL;
  PlatformStatus.s.TX_TIMER_INTERVAL = tempPlatformStatus.s.TX_TIMER_INTERVAL;
  PlatformStatus.b.EEPROM_DATA_INITED = tempPlatformStatus.b.EEPROM_DATA_INITED;
  }
}

/**
  * @brief Initialization of Platform status structure
  * @param none
  * @retval none
  */
void BSP_SavePlatformStatusToEeprom(void)
{
#if SAVE_PLATFORM_STATUS_IN_INTERNAL_EEPROM
  WriteInternalEepromBuffer(PLATFORM_STATUS_EEPROM_ADDRESS, PLATFORM_STATUS_EEPROM_LEN, (void*)&PlatformStatus);
#endif //SAVE_PLATFORM_STATUS_IN_INTERNAL_EEPROM
}

/**
  * @brief Sensors reading function
  * @param pSensorData Pointer to sensor_t structure
  * @retval none
  */
void BSP_sensor_Read(sensor_t *pSensorData)
{
  int32_t retval = 0;
//  int32_t tmp_retval = 0;
  float HUMIDITY_Value = 0;
  float TEMPERATURE_Value = 0;
  float PRESSURE_Value = 0;
  LORA_TRACKER_MOTION_SENSOR_Axes_t AccValue = {0};
  
#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)

  if ((SensorsEnabled&HUMIDITY_SENSOR) == HUMIDITY_SENSOR)
  {
    tmp_retval|=LORA_TRACKER_ENV_SENSOR_GetValue(LORA_TRACKER_HTS221_0, ENV_HUMIDITY, &HUMIDITY_Value);
    if(tmp_retval)
    {
      PRINTF("Error disabling HTS221 humidity sensor");
    }
    retval |= tmp_retval;
  }
  if ((SensorsEnabled&TEMPERATURE_SENSOR) == TEMPERATURE_SENSOR)
  {
    tmp_retval|=LORA_TRACKER_ENV_SENSOR_GetValue(LORA_TRACKER_HTS221_0, ENV_TEMPERATURE, &TEMPERATURE_Value);
    if(tmp_retval)
    {
      PRINTF("Error disabling HTS221 temperature sensor");
    }
    retval |= tmp_retval;
  }
  if ((SensorsEnabled&PRESSURE_SENSOR) == PRESSURE_SENSOR)
  {
    tmp_retval|=LORA_TRACKER_ENV_SENSOR_GetValue(LORA_TRACKER_LPS22HB_0, ENV_PRESSURE, &PRESSURE_Value);
    if(tmp_retval)
    {
      PRINTF("Error disabling LPS22HB pressure sensor");
    }
    retval |= tmp_retval;
  }
  if ((SensorsEnabled&ACCELEROMETER_SENSOR) == ACCELEROMETER_SENSOR)
  {
    tmp_retval|=BSP_LORA_TRACKER_MOTION_SENSOR_GetAxes(LORA_TRACKER_LIS2DW12_0, MOTION_ACCELERO, &AccValue);
    if(tmp_retval)
    {
      PRINTF("Error disabling LPS22HB pressure sensor");
    }
    retval |= tmp_retval;
  }
#endif
  
  if (retval)
  {
    SensorsRecovery();
  }
  
  pSensorData->humidity    = HUMIDITY_Value;
  pSensorData->temperature = TEMPERATURE_Value;
  pSensorData->pressure    = PRESSURE_Value;
  
  pSensorData->acceleration_x = AccValue.x; 
  pSensorData->acceleration_y = AccValue.y;
  pSensorData->acceleration_z = AccValue.z;
}


/**
  * @brief  Facility to print startup mode enum
  * @param  s System status
  * @retval None
  */
void PrintStartupMode(StartupMode_t mode)
{
  switch(mode)
  {
  case STARTUP_AFTER_POWER_ON_RESET:
    PRINTF("STARTUP_AFTER_POWER_ON_RESET\r\n");
    break;
  case STARTUP_AFTER_SOFTWARE_RESET:
    PRINTF("STARTUP_AFTER_SOFTWARE_RESET\r\n");
    break;
  case STARTUP_AFTER_PIN_RESET:
    PRINTF("STARTUP_AFTER_PIN_RESET\r\n");
    break;
  default:
    PRINTF("STARTUP: unknown\r\n");
    break;
  }
}

/**
  * @brief  Facility to print charger status
  * @param  s charger status
  * @retval None
  */
void PrintChargerStatus(uint8_t s)
{
  PRINTF("Charger status %d\r\n", s);
  switch(s)
  {
  case NOT_VALID_INPUT:
    PRINTF("NOT_VALID_INPUT\r\n");
    break;
  case VALID_INPUT:
    PRINTF("VALID_INPUT\r\n");
    break;
  case VBAT_LOW:
    PRINTF("VBAT_LOW\r\n");
    break;
  case END_OF_CHARGING:
    PRINTF("END_OF_CHARGING\r\n");
    break;
  case CHARGING_PHASE:
    PRINTF("CHARGING_PHASE\r\n");
    break;
  case OVER_CHARGE_FAULT:
    PRINTF("OVER_CHARGE_FAULT\r\n");
    break;
  case CHARGING_TIMEOUT:
    PRINTF("CHARGING_TIMEOUT\r\n");
    break;
  case BATTERY_VOLTAGE_BELOW_VPRE:
    PRINTF("BATTERY_VOLTAGE_BELOW_VPRE\r\n");
    break;
  case CHARGING_THERMAL_LIMITATION:
    PRINTF("CHARGING_THERMAL_LIMITATION\r\n");
    break;
  case BATTERY_TEMPERATURE_FAULT:
    PRINTF("BATTERY_TEMP_FAULT_OR_NOT_PRESENT\r\n");
    break;
  case UNKNOWN:
    PRINTF("UNKNOWN\r\n");
    break;
  default:
    break;
  }
}

/**
  * @brief  State machine "PrintSystemState" facility
  * @param  s System status
  * @retval None
  */
void PrintSystemState(SystemState_t s)
{
  switch(s)
  {
  case State_PrepareLowPower:
    PRINTF("State_PrepareLowPower");
    break;
  case State_LowPower:
    PRINTF("State_LowPower");
    break;
  case State_PrepareUltraLowPower:
    PRINTF("State_PrepareUltraLowPower");
    break;
  case State_UltraLowPower:
    PRINTF("State_UltraLowPower");
    break;
  case State_Run:
    PRINTF("State_Run");
    break;
  case State_Read:
    PRINTF("State_Read");
    break;
  case State_ReadMems:
    PRINTF("State_ReadMems");
    break;
  case State_ReadGnss:
    PRINTF("State_ReadGnss");
    break;
  case State_SaveData:
    PRINTF("State_SaveData");
    break;
  case State_Send:
    PRINTF("State_Send");
    break;
  case State_RetrieveData:
    PRINTF("State_RetrieveData");
    break;
  case State_SendData:
    PRINTF("State_SendData");
    break;
  case State_IdleAfterSend:
    PRINTF("State_IdleAfterSend");
    break;
  case State_CheckAck:
    PRINTF("State_CheckAck");
    break;
  case State_INVALID:
    PRINTF("State_INVALID");
    break;
  default:
    PRINTF("ERROR - Status unknown");
  break;
  }
}


/** @brief Write in STM32 internal EEPROM 
  * @param dest_addr EEPROM address (range 0x08080000 - 0x080817FF)
  * @param num_bytes number of bytes to write
  * @param buffer_to_write pointer to input buffer
  * @retval none
  */
void WriteInternalEepromBuffer(uint32_t dest_addr, uint32_t num_bytes, uint8_t *buffer_to_write)
{
  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR );
  
  for(int address_offset=0; address_offset<num_bytes; address_offset += 4)
  {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, dest_addr+address_offset, *(uint32_t*)(buffer_to_write+address_offset));
  }
  
  HAL_FLASH_Lock();
}


/**
  * @brief It measures the battery voltage by returning the value in mV
  * @param none
  * @retval uint16_t The battery voltage value in mV
  */
uint16_t BSP_GetBatteryLevel16( void )
{
#ifdef LORA_SMART_TRACKER
  #define VDDA_VREFINT_CAL            ((uint32_t) 3000)        
  #define VREFINT_CAL       ((uint16_t*) ((uint32_t) 0x1FF80078))

  uint16_t batteryLevel = 0;
  uint16_t measuredLevel = 0;
  uint16_t nVrefIntLevel = 0;
  float batteryVoltage = 0;
  float nVddValue = 0;
  
  BSP_BC_CmdSend(BATMS_ON);
  HAL_Delay(200);
  
  measuredLevel = HW_AdcReadChannel( BATTERY_ADC_CHANNEL ); 

  BSP_BC_CmdSend(BATMS_OFF);
  HAL_Delay(200);
  
  nVrefIntLevel = HW_AdcReadChannel( ADC_CHANNEL_VREFINT ); 
  nVddValue = (( (uint32_t) VDDA_VREFINT_CAL * (*VREFINT_CAL ) )/ nVrefIntLevel);
  
  batteryVoltage =  ((( (float)(measuredLevel) * nVddValue/*3300*/) / 4096) * RESITOR_DIVIDER);
  
  batteryLevel = (uint16_t)(batteryVoltage / 1.0);
  
  return batteryLevel;
#else //LORA_SMART_TRACKER
  return HW_GetBatteryLevel();
#endif //LORA_SMART_TRACKER
}


/**
  * @brief It gets the battery voltage by returning the value in tenths of V
  * @param none
  * @retval uint8_t The battery voltage value in tenths of V
  */
uint8_t BSP_GetBatteryLevel( void )
{
  return (uint8_t)(BSP_GetBatteryLevel16() / 100);
}


#ifdef LORA_SMART_TRACKER

/**
  * @brief It calculates the battery charge percentage
  * @param BatteryLevelThe battery voltage in hundreds of mV
  * @retval uint8_t The battery charge percentage
  */
uint8_t BSP_BatteryChargePercentage(uint16_t BatteryLevel)
{
  uint8_t ret_percentage = 0;
  for (uint8_t i = 0; i< NUMBER_OF_BATTERY_PROFILE_SAMPLES; i++)
  {
    if ((BatteryLevel > a_battery_profile[i].voltage_min) && (BatteryLevel <= a_battery_profile[i].voltage_max))
    {
      if (a_battery_profile[i].voltage_m == 0)
      {
        ret_percentage = (uint8_t) a_battery_profile[i].voltage_q;
      }
      else
      {
        ret_percentage = (uint8_t) ((a_battery_profile[i].voltage_m * (BatteryLevel / 1000.0)) + a_battery_profile[i].voltage_q);
      }
    }
  }
  return ret_percentage;
}


/**
  * @brief It shuts down the board
  * @param none
  * @retval none
  */
void BSP_BoardShutdown( void )
{
  BSP_BC_CmdSend(SHIPPING_MODE_ON);
}


/**
  * @brief It gets the battery charging status
  * @param none
  * @retval BC_ChargeStatusTypeDef Battery charging status
  */
uint8_t BSP_GetChargerStatus( void )
{
  if (PlatformStatus.b.USB_CONNECTED)
  {
    stbc02_ChgState_TypeDef stbc02_ChgState = NotValidInput;
    BSP_BC_GetState(&stbc02_ChgState);
    return stbc02_ChgState;
  }
  else
    return NotValidInput;
}


/**
  * @brief Check LoRa Keys saved in EEPROM
  * @param none
  * @retval BC_ChargeStatusTypeDef Battery charging status
  */
uint8_t EepromLoraKeysValidation(void)
{
  uint8_t retval = 0;
  /* DevEui validation */
  if((*(uint64_t*)DEVICE_EUI_EEPROM_ADDRESS) == 0)
  {
    retval |= DEVICE_EUI_EEPROM_ID;
  }
  /* JoinEui validation */
  if((*(uint64_t*)JOIN_EUI_EEPROM_ADDRESS) == 0)
  {
    retval |= JOIN_EUI_EEPROM_ID;
  }
  /* AppKey validation */
  if ( ((*(uint64_t*)APP_KEY_EEPROM_ADDRESS) == 0) && ((*(uint64_t*)(APP_KEY_EEPROM_ADDRESS+8)) == 0) )
  {
    retval |= APP_KEY_EEPROM_ID;
  }
  /* NwkKey validation */
  if ( ((*(uint64_t*)NWK_KEY_EEPROM_ADDRESS) == 0) && ((*(uint64_t*)(NWK_KEY_EEPROM_ADDRESS+8)) == 0) )
  {
    retval |= NWK_KEY_EEPROM_ID;
  }
  return retval;
}

/**
  * @brief  Load Lora keys (DevEui, JoinEui, AppKey, NwkKey) from STM32 internal EEPROM
  * @param  None
  * @retval None
  */
void LoadLoraKeys()
{
#if SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
  extern uint8_t DevEui[];
  extern uint8_t JoinEui[];
  extern uint8_t AppKey[];
  extern uint8_t NwkKey[];
  
  if(EepromLoraKeysValidation() != 0)
  {
    return;
  }
  
  memcpy(DevEui, (void*)DEVICE_EUI_EEPROM_ADDRESS, DEVICE_EUI_EEPROM_LEN);
  memcpy(JoinEui, (void*)JOIN_EUI_EEPROM_ADDRESS, JOIN_EUI_EEPROM_LEN);
  memcpy(AppKey, (void*)APP_KEY_EEPROM_ADDRESS, APP_KEY_EEPROM_LEN);
  memcpy(NwkKey, (void*)NWK_KEY_EEPROM_ADDRESS, NWK_KEY_EEPROM_LEN);
#endif //SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
}


/**
  * @brief EEPROM initialization function
  * @param none
  * @retval none
  */
void BSP_memory_Init(void)
{
  PRINTF("BSP_EEPROM_Init()\r\n");
  BSP_EEPROM_Init(M95M02_DR_M_0, &M95M02_handle); 
  BSP_EEPROM_Module_Enable(M95M02_handle);
  
  uint8_t status = 0;
  if (BSP_EEPROM_IsInitialized(M95M02_handle, &status) == COMPONENT_OK && status == 1)
  { 
    PRINTF("BSP_EEPROM_Init() OK\r\n");
  }
  else
  {
    PRINTF("BSP_EEPROM_Init() FAILED\r\n");
  }
  
  int b = 0;//set to 1 for basic memory testing
  uint8_t dummywrite[4]={0x11, 0x22, 0xAA, 0xBB};
  while(b)
  {
    uint8_t dummyresp[4];
    uint8_t result = 0;
    
    if (BSP_EEPROM_IsInitialized(M95M02_handle, &status) == COMPONENT_OK && status == 1)
    { 
      PRINTF("BSP_EEPROM_Write()\r\n");
      if(COMPONENT_OK == BSP_EEPROM_Write( M95M02_handle, 0, dummywrite, 4))
      {
        result = 1;
        PRINTF("BSP_EEPROM_Write() OK\r\n");
        PRINTF("BSP_EEPROM_Read()\r\n");
        if(COMPONENT_OK == BSP_EEPROM_Read( M95M02_handle, 0, dummyresp, 4))
        {
          PRINTF("BSP_EEPROM_Read() OK\r\n");
          result = 2;
          PRINTF("Compare write/read buffers\r\n");
          for(uint8_t i = 0; i < 4; i ++)
          {
            if(dummyresp[i] != dummywrite[i])
            {
              result = 0;
            }
          }
          if(result == 2)
          {
            PRINTF("EEPROM write/read OK\r\n");
            for(uint8_t i = 0; i < 4; i ++)dummywrite[i]++; //edit buffer for next write
          }
          else
          {
            PRINTF("EEPROM write/read FAILED\r\n");
          }
        }
        else
        {
          PRINTF("BSP_EEPROM_Read() FAILED\r\n");
        }
      }
      else
      {
        PRINTF("BSP_EEPROM_Write() FAILED\r\n");
      }
    }
    else
    {
      PRINTF("BSP_EEPROM_IsInitialized() FAILED\r\n");
    }
  }
}


/**
  * @brief It initializes the power managment
  * @param none
  * @retval none
  */
void  BSP_power_Init( void )
{
  PRINTF("BC_IO_SW_SEL_Init()\r\n");
  BSP_BC_InitCommon();
  BC_IO_SW_SEL_Init();
  
  if (PlatformStatus.b.USB_CONNECTED)
  {
    PRINTF("BC_IO_CHG_Init()\r\n");
    BC_IO_CHG_Init();
  }
  else
  {
    PRINTF("BC_IO_CHG_Init()\r\n");
    BC_IO_CHG_Init();
  }
  
  BSP_PowerGNSS(DISABLE);
  BSP_PowerGNSS(ENABLE);
#ifdef MEMORY_ENABLED
  BSP_PowerEEPROM(ENABLE);
#else
  BSP_PowerEEPROM(DISABLE);
#endif  
  BSP_PowerTypeCCtrl(DISABLE);
  BSP_PowerSensors(ENABLE);
}
#endif //LORA_SMART_TRACKER


/**
  * @brief It deinitializes the embedded sensors
  * @param none
  * @retval none
  */
void  BSP_sensor_DeInit( void )
{
//  LORA_TRACKER_ENV_SENSOR_DeInit(LORA_TRACKER_HTS221_0);
//  LORA_TRACKER_ENV_SENSOR_DeInit(LORA_TRACKER_LPS22HB_0);
}

/**
  * @brief It initializes the embedded sensors
  * @param none
  * @retval none
  */
void  BSP_sensor_Init( void )
{
#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)
  /* Initialize sensors */
#ifdef LORA_SMART_TRACKER
  if (LORA_TRACKER_ENV_SENSOR_Init(LORA_TRACKER_HTS221_0, ENV_TEMPERATURE) == BSP_ERROR_NONE)
  {
    PRINTF("Temperature sensor HTS221_T_0 initialized\r\n");
  } 
  if (LORA_TRACKER_ENV_SENSOR_Init(LORA_TRACKER_HTS221_0, ENV_HUMIDITY) == BSP_ERROR_NONE)
  {
    PRINTF("Humidity sensor HTS221_H_0 initialized\r\n");
  } 
  if (LORA_TRACKER_ENV_SENSOR_Init(LORA_TRACKER_LPS22HB_0, ENV_PRESSURE) == BSP_ERROR_NONE) 
  {
    PRINTF("Pressure sensor LPS22HB_0 initialized\r\n");
  }
#else // LORA_SMART_TRACKER
  if ( IKS01A2_ENV_SENSOR_Init(IKS01A2_HTS221_0, ENV_TEMPERATURE | ENV_HUMIDITY) == BSP_ERROR_NONE )
  {
    PRINTF("Humidity & Temperature sensor HTS221_0 initialized\r\n");
  }
  if ( IKS01A2_ENV_SENSOR_Init(IKS01A2_LPS22HB_0, ENV_PRESSURE) == BSP_ERROR_NONE )
  {
    PRINTF("Pressure sensor LPS22HB_0 initialized\r\n");
  }
#endif //LORA_SMART_TRACKER
#endif // defined(SENSOR_ENABLED) || defined (LRWAN_NS1)
}


/**
  * @brief It enables the embedded sensors
  * @param none
  * @retval none
  */
void  BSP_sensor_Enable( void )
{
#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)
  /* Enable sensors */
#ifdef LORA_SMART_TRACKER
  if (LORA_TRACKER_ENV_SENSOR_Enable(LORA_TRACKER_HTS221_0, ENV_HUMIDITY) == BSP_ERROR_NONE)
  {
    if(0 == (SensorsEnabled & HUMIDITY_SENSOR))
    {
      PRINTF("Humidity sensor enabled\r\n");
    }
    SensorsEnabled |= HUMIDITY_SENSOR;
  }
  else
  {
    PRINTF("Humidity sensor NOT enabled (ERROR)\r\n");
    SensorsRecovery();
  }
  
  if (LORA_TRACKER_ENV_SENSOR_Enable(LORA_TRACKER_HTS221_0, ENV_TEMPERATURE) == BSP_ERROR_NONE)
  {
    if(0 == (SensorsEnabled & TEMPERATURE_SENSOR))
    {
    PRINTF("Temperature sensor enabled\r\n");  
    }
    SensorsEnabled |= TEMPERATURE_SENSOR;
  }
  else
  {
    PRINTF("Temperature sensor NOT enabled (ERROR)\r\n");
    SensorsRecovery();
  }
  
  if (LORA_TRACKER_ENV_SENSOR_Enable(LORA_TRACKER_LPS22HB_0, ENV_PRESSURE) == BSP_ERROR_NONE)
  {
    if(0 == (SensorsEnabled & PRESSURE_SENSOR))
    {
    PRINTF("Pressure sensor enabled\r\n");  
    }
    SensorsEnabled |= PRESSURE_SENSOR;
  }
  else
  {
    PRINTF("Pressure sensor NOT enabled\r\n");
    SensorsRecovery();
  }
#else  // LORA_SMART_TRACKER
  if ( IKS01A2_ENV_SENSOR_Enable(IKS01A2_HTS221_0, ENV_HUMIDITY | ENV_TEMPERATURE) == BSP_ERROR_NONE )
  {
    PRINTF("Humidity and temperature sensor enabled\r\n");
    SensorsEnabled |= HUMIDITY_SENSOR +TEMPERATURE_SENSOR;
  }
  else
  {
    PRINTF("Humidity and temperature sensor NOT enabled\r\n");
    Error_Handler();
  }

  if ( IKS01A2_ENV_SENSOR_Enable(IKS01A2_LPS22HB_0, ENV_PRESSURE) == BSP_ERROR_NONE )
  {
    PRINTF("Pressure sensor enabled\r\n");
    SensorsEnabled |= PRESSURE_SENSOR;
  }
  else
  {
    PRINTF("Pressure sensor NOT enabled\r\n");
    Error_Handler();
  }
#endif // LORA_SMART_TRACKER
#endif // defined(SENSOR_ENABLED) || defined (LRWAN_NS1)
}


/**
  * @brief It disables the embedded sensors
  * @param none
  * @retval none
  */
void  BSP_sensor_Disable( void )
{
#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)

  int32_t retval = 0;
  int32_t tmp_retval = 0;
  
  /* Disable all sensors */
#ifdef LORA_SMART_TRACKER 
  tmp_retval = LORA_TRACKER_ENV_SENSOR_Disable(LORA_TRACKER_LPS22HB_0, ENV_PRESSURE);
  if(tmp_retval)PRINTF("Error disabling LPS22HB pressure sensor");
  retval |= tmp_retval;
  tmp_retval = LORA_TRACKER_ENV_SENSOR_Disable(LORA_TRACKER_HTS221_0, ENV_TEMPERATURE);
  if(tmp_retval)PRINTF("Error disabling HTS221 temperature sensor");
  retval |= tmp_retval;
  tmp_retval = LORA_TRACKER_ENV_SENSOR_Disable(LORA_TRACKER_HTS221_0, ENV_HUMIDITY);
  if(tmp_retval)PRINTF("Error disabling HTS221 humidity sensor");
  retval |= tmp_retval;
#else //LORA_SMART_TRACKER
  retval |= IKS01A2_ENV_SENSOR_Disable(IKS01A2_HTS221_0, ENV_HUMIDITY );
  retval |= IKS01A2_ENV_SENSOR_Disable(IKS01A2_HTS221_0, ENV_TEMPERATURE);
  retval |= IKS01A2_ENV_SENSOR_Disable(IKS01A2_LPS22HB_0, ENV_PRESSURE);
#endif 
  SensorsEnabled &= ~PRESSURE_SENSOR;
  SensorsEnabled &= ~TEMPERATURE_SENSOR;
  SensorsEnabled &= ~HUMIDITY_SENSOR;
  
  if ( retval == BSP_ERROR_NONE )
    PRINTF("Environmental sensors disabled\r\n");
  else
  {
    PRINTF("Environmental sensors not working\r\n");
    SensorsRecovery();
  }
#endif /* #if defined(SENSOR_ENABLED) || defined (LRWAN_NS1) */ 
  
}

void SensorsRecovery(void)
{
    PRINTF("Sensors are initialized again\r\n");
    BSP_sensor_Read_I2C_Error();
    BSP_PowerSensors(DISABLE);
    BSP_PowerSensors(ENABLE);
    BSP_sensor_DeInit();
    BSP_sensor_Init();
    BSP_accelero_Init(false);
    BSP_LIS2DW12_IO_ITConfig(ENABLE); 
}

/**
  * @brief It initializes the accelerometer and prints the status
  * @param quiet The parameter is TRUE when the initailization status have to be printed otherwise it is FALSE  
  * @retval none
  */
void BSP_accelero_Init(bool quiet)
{
  #if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)

  /* --- Initialization --- */
  
#ifdef LORA_SMART_TRACKER
  if (BSP_LORA_TRACKER_MOTION_SENSOR_Init(LORA_TRACKER_LIS2DW12_0, MOTION_ACCELERO) == BSP_ERROR_NONE)
  {
    if (!quiet)
    {
      PRINTF("Accelerometer LIS2DW12 initialized\r\n");
    }
  }
#else //LORA_SMART_TRACKER
  if ( IKS01A2_MOTION_SENSOR_Init(IKS01A2_LSM6DSL_0, MOTION_ACCELERO ) == BSP_ERROR_NONE )
  {
    if (!quiet)
      PRINTF("Accelerometer LSM6DSL initialized\r\n");
  }
#endif //LORA_SMART_TRACKER
  else
  {
    PRINTF("Accelerometer NOT initialized\r\n");
    SensorsRecovery();
  }
  
  /* --- Set ODR = 12.5 Hz --- */
#ifdef LORA_SMART_TRACKER
  if (BSP_LORA_TRACKER_MOTION_SENSOR_SetOutputDataRate(LORA_TRACKER_LIS2DW12_0, MOTION_ACCELERO, 12.5) == BSP_ERROR_NONE)
  {
    if (!quiet)
    {
      PRINTF("Accelerometer LIS2DW12 ODR set to 12.5 Hz\r\n");
    }
  }
  else
  {
    PRINTF("Accelerometer LIS2DW12 ODR NOT set\r\n");
    SensorsRecovery();
  }
#endif
  
   /* --- Wake-Up and Inactivity Detection Enabling --- */
#ifdef LORA_SMART_TRACKER
  BSP_LORA_TRACKER_MOTION_SENSOR_Disable_Wake_Up_Detection(LORA_TRACKER_LIS2DW12_0);
  BSP_LORA_TRACKER_MOTION_SENSOR_Disable_Inactivity_Detection(LORA_TRACKER_LIS2DW12_0);
#else // LORA_SMART_TRACKER
  IKS01A2_MOTION_SENSOR_Disable_Wake_Up_Detection(IKS01A2_LSM6DSL_0);
  IKS01A2_MOTION_SENSOR_Disable_Inactivity_Detection(IKS01A2_LSM6DSL_0);
#endif // LORA_SMART_TRACKER
  
#ifdef LORA_SMART_TRACKER 
  if (BSP_LORA_TRACKER_MOTION_SENSOR_Enable_Inactivity_Detection(LORA_TRACKER_LIS2DW12_0, MOTION_SENSOR_INT2_PIN) == BSP_ERROR_NONE) 
  {
    if (!quiet)
      PRINTF("Inactivity detection enabled\r\n");
    accActInact = ACC_ACTIVITY;
  }
#else //LORA_SMART_TRACKER
  if ( IKS01A2_MOTION_SENSOR_Enable_Inactivity_Detection(IKS01A2_LSM6DSL_0, LSM6DSL_INT2_PIN)  == BSP_ERROR_NONE )
  {
    if (!quiet)
      PRINTF("Inactivity detection enabled\r\n");
    accActInact = ACC_ACTIVITY;
  }
#endif //LORA_SMART_TRACKER
  else
  {
    PRINTF("Inactivity detection NOT enabled\r\n");
    SensorsRecovery();
  }
  
#ifdef LORA_SMART_TRACKER
  // if(BSP_LORA_TRACKER_MOTION_SENSOR_Enable_Interrupt_Latch(LORA_TRACKER_LIS2DW12_0)==BSP_ERROR_NONE)
if(BSP_LORA_TRACKER_MOTION_SENSOR_Interrupt_Polarity_Low(LORA_TRACKER_LIS2DW12_0)==BSP_ERROR_NONE)
  {
    if (!quiet)
      PRINTF("Interrupt polarity: active low\r\n");
      //PRINTF("Interrupt latch enabled\r\n");
  }
  else
  {
    PRINTF("Interrupt NOT enabled\r\n");
    //PRINTF("Interrupt latch NOT enabled\r\n");
    SensorsRecovery();
  }
#endif
#ifdef LORA_SMART_TRACKER
  if ( BSP_LORA_TRACKER_MOTION_SENSOR_Set_Sleep_Duration(LORA_TRACKER_LIS2DW12_0, INACTIVITY_DURATION)  == BSP_ERROR_NONE ) /* SLEEP_DURATION definition has to be modified when not in testing mode */
  {
    if (!quiet)
      PRINTF("Inactivity duration set\r\n");
  }
#else //LORA_SMART_TRACKER
  if ( IKS01A2_MOTION_SENSOR_Set_Sleep_Duration(IKS01A2_LSM6DSL_0, 2)  == BSP_ERROR_NONE )
  {
    if (!quiet)
      PRINTF("Inactivity duration set\r\n");
  }
#endif // LORA_SMART_TRACKER
  else
  {
    PRINTF("Inactivity duration NOT set\r\n");
    SensorsRecovery();
  }
  
  /* --- Enabling --- */
#ifdef LORA_SMART_TRACKER
  LORA_TRACKER_MOTION_SENSOR_Event_Status_t status; 
  BSP_LORA_TRACKER_MOTION_SENSOR_Get_Event_Status(LORA_TRACKER_LIS2DW12_0, &status);
  
  if (BSP_LORA_TRACKER_MOTION_SENSOR_Enable(LORA_TRACKER_LIS2DW12_0, MOTION_ACCELERO) == BSP_ERROR_NONE)
  {
    SensorsEnabled |= ACCELEROMETER_SENSOR;
    if (!quiet)
      PRINTF("Accelerometer enabled\r\n");
  }
#else //LORA_SMART_TRACKER
  if ( IKS01A2_MOTION_SENSOR_Enable(IKS01A2_LSM6DSL_0, MOTION_ACCELERO) == BSP_ERROR_NONE )
  {
    SensorsEnabled |= ACCELEROMETER_SENSOR;
    if (!quiet)
      PRINTF("Accelerometer enabled\r\n");
  }
#endif //LORA_SMART_TRACKER
  else
  {
    PRINTF("Accelerometer NOT enabled\r\n");
    SensorsRecovery();
  }
  
  
  if (quiet)
    PRINTF("Accelerometer enabled\r\n");
  
#endif /* defined(SENSOR_ENABLED) || defined (LRWAN_NS1) */
}


/**
  * @brief It disables the accelerometer
  * @param none  
  * @retval none
  */
void BSP_accelero_Disable(void) 
{
#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)

#ifdef LORA_SMART_TRACKER
  BSP_LORA_TRACKER_MOTION_SENSOR_Disable_Wake_Up_Detection(LORA_TRACKER_LIS2DW12_0);
  BSP_LORA_TRACKER_MOTION_SENSOR_Disable_Inactivity_Detection(LORA_TRACKER_LIS2DW12_0);
  if (BSP_LORA_TRACKER_MOTION_SENSOR_Disable (LORA_TRACKER_LIS2DW12_0, MOTION_ACCELERO) == BSP_ERROR_NONE)
  {
    SensorsEnabled &= ~ACCELEROMETER_SENSOR;
    PRINTF("Accelerometer disabled\r\n");
  }
#else // LORA_SMART_TRACKER 
  IKS01A2_MOTION_SENSOR_Disable_Wake_Up_Detection(IKS01A2_LSM6DSL_0);
  IKS01A2_MOTION_SENSOR_Disable_Inactivity_Detection(IKS01A2_LSM6DSL_0);
  if ( IKS01A2_MOTION_SENSOR_Disable(IKS01A2_LSM6DSL_0, MOTION_ACCELERO) == BSP_ERROR_NONE )
  {
    SensorsEnabled &= ~ACCELEROMETER_SENSOR;
    PRINTF("Accelerometer disabled\r\n");
  }
#endif // LORA_SMART_TRACKER 
  else
  {
    PRINTF("Accelerometer NOT disabled\r\n");
    SensorsRecovery();
  }

#endif /* defined(SENSOR_ENABLED) || defined (LRWAN_NS1) */
}

/**
  * @brief It enables the accelerometer
  * @param none  
  * @retval none
  */
void BSP_accelero_Enable(void) 
{
#if defined(SENSOR_ENABLED) || defined (LRWAN_NS1)

#ifdef LORA_SMART_TRACKER
  if ((SensorsEnabled&ACCELEROMETER_SENSOR) != ACCELEROMETER_SENSOR)
  {
    BSP_accelero_Init(false);
  }
#endif // LORA_SMART_TRACKER 
#endif /* defined(SENSOR_ENABLED) || defined (LRWAN_NS1) */
}

/**
  * @brief It switches on or off the LIS2DW12 INT2 pin
  * @param status Allowed values are ENABLE or DISABLE
  * @retval none
  */
void BSP_LIS2DW12_IO_ITConfig(FunctionalState status)
{
  GPIO_InitTypeDef temp_gpio_init_struct = {0};
  
  if (status)
  {
    /* Interrupt pin configured as input with rising interrupt */
    temp_gpio_init_struct.Pin        = ((uint32_t)LIS2DW12_INT2_O_PIN);
//    temp_gpio_init_struct.Mode       = ((uint32_t)GPIO_MODE_IT_RISING);
    temp_gpio_init_struct.Mode       = ((uint32_t)GPIO_MODE_IT_FALLING);
    temp_gpio_init_struct.Pull       = ((uint32_t)GPIO_NOPULL);
    
    HAL_GPIO_Init(LIS2DW12_INT2_O_GPIO_PORT, &temp_gpio_init_struct);
    
    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(LIS2DW12_INT2_O_EXTI_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LIS2DW12_INT2_O_EXTI_IRQn);
  }
  else
  {
    
  }
}

/**
  * @brief It configures the Teseo boot pin for application
  * @param status Allowed values are: 0 for Teseo boot in application, 1 for Teseo boot mode, 2 for normal operation (UART mode), 3 during low power 
  * @retval none
  */
void BSP_GnssManageBootPins(uint8_t nBootMode)
{
  GPIO_InitTypeDef temp_gpio_init_struct = {0};
  switch(nBootMode)
  {
  case 0:
    /* UART pins configuration for TESEO BOOT in application mode: input pull down */
    temp_gpio_init_struct.Pin        = ((uint32_t)(GNSS_UART_TX | GNSS_UART_RX));
    temp_gpio_init_struct.Mode       = ((uint32_t)GPIO_MODE_INPUT);
    temp_gpio_init_struct.Pull       = ((uint32_t)GPIO_PULLDOWN);
    temp_gpio_init_struct.Speed      = ((uint32_t)GPIO_SPEED_FREQ_LOW);
    temp_gpio_init_struct.Alternate  = ((uint32_t)GNSS_UART_ALTERNATE);
    
    HAL_GPIO_Init(GNSS_UART_RXTX_PORT, &temp_gpio_init_struct);
    break;
  case 1:
    /* TODO: To be implemented */
    break;
  case 2:
    /* UART pins configuration restored in UART mode for normal operation */
    temp_gpio_init_struct.Pin        = ((uint32_t)(GNSS_UART_TX | GNSS_UART_RX));
    temp_gpio_init_struct.Mode       = ((uint32_t)GNSS_UART_PIN_MODE);
    temp_gpio_init_struct.Pull       = ((uint32_t)GNSS_UART_PULL);
    temp_gpio_init_struct.Speed      = ((uint32_t)GNSS_UART_SPEED);
    temp_gpio_init_struct.Alternate  = ((uint32_t)GNSS_UART_ALTERNATE);
    
    HAL_GPIO_Init(GNSS_UART_RXTX_PORT, &temp_gpio_init_struct);
    break;
  case 3:
    /* UART pins configuration in input pull up during standby for minimun current leakage */
    temp_gpio_init_struct.Pin        = ((uint32_t)(GNSS_UART_TX | GNSS_UART_RX));
    temp_gpio_init_struct.Mode       = ((uint32_t)GPIO_MODE_INPUT);
    temp_gpio_init_struct.Pull       = ((uint32_t)GPIO_PULLUP);
    temp_gpio_init_struct.Speed      = ((uint32_t)GPIO_SPEED_FREQ_LOW);
    temp_gpio_init_struct.Alternate  = ((uint32_t)GNSS_UART_ALTERNATE);
    
    HAL_GPIO_Init(GNSS_UART_RXTX_PORT, &temp_gpio_init_struct);
    break;
  default:
    PRINTF("INVALID PARAM\r\n");
    break;
  }
}

/**
  * @brief It wakes up the Teseo from standby
  * @param none
  * @retval none
  */
void BSP_GnssWakeup(FunctionalState status)
{
  GPIO_InitTypeDef temp_gpio_init_struct = {0};
  
  if(status)
  {
    /* UART pins configuration for TESEO BOOT in application mode: input pull down */
    BSP_GnssManageBootPins(0);
    
    temp_gpio_init_struct.Pin = GNSS_WAKEUP_PIN;
    temp_gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    temp_gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GNSS_WAKEUP_PORT, &temp_gpio_init_struct);
    
    HAL_Delay(100);
    
    /* GNSS feeding line is switched on */
    PRINTF("GNSS wake up from WAKEUP pin\r\n");
    
    GNSS_WAKEUP_SET();
    HAL_Delay(100);
    
    /* UART pins configuration is restored when GNSS feeding line is switched on */
    BSP_GnssManageBootPins(2);
  }
  else
  {
    GNSS_WAKEUP_RESET();
    temp_gpio_init_struct.Pin = GNSS_WAKEUP_PIN;
    temp_gpio_init_struct.Mode = GPIO_MODE_INPUT;
    temp_gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GNSS_WAKEUP_PORT, &temp_gpio_init_struct);
  }
}

/**
  * @brief It switches on or off the GNSS feeding line
  * @param status Allowed values are ENABLE or DISABLE
  * @retval none
  */
void BSP_PowerGNSS(FunctionalState status)
{
  if (status)
  {
    /* UART pins configuration for TESEO BOOT in application mode: input pull down */
    BSP_GnssManageBootPins(0);
    HAL_Delay(100);
    
    /* GNSS feeding line is switched on */
    PRINTF("BSP_BC_CmdSend(SW1_OA_ON) GNSS\r\n");
    BSP_BC_CmdSend(SW1_OA_ON);
    HAL_Delay(STBC02_CMD_TIMEOUT);
    
    /* UART pins configuration is restored when GNSS feeding line is switched on */
    BSP_GnssManageBootPins(2);
  }
  else
  {
    /* GNSS feeding line is switched off */
    PRINTF("BSP_BC_CmdSend(SW1_OA_OFF) GNSS\r\n");
    BSP_BC_CmdSend(SW1_OA_OFF);
    HAL_Delay(STBC02_CMD_TIMEOUT);
    
    /* UART pins are configured in order to isolate GNSS subcircuit when it is switched off */
    BSP_GnssManageBootPins(0);
    
    /* Wakeup pin configured in order to isolate GNSS subcircuit when it is switched off */
    BSP_GnssWakeup(DISABLE);
  }
  
  /* Platform status variable is updated */ 
  PlatformStatus.b.SW1_OA = status;
  
  HAL_Delay(100);
}  

  

/**
  * @brief It switches on or off the EEPROM feeding line
  * @param status Allowed values are ENABLE or DISABLE
  * @retval none
  */
void BSP_PowerEEPROM(FunctionalState status)
{
  GPIO_InitTypeDef temp_gpio_init_struct = {0};
  
  if (status)
  {
    PRINTF("BSP_BC_CmdSend(SW1_OB_ON) EEPROM\r\n");
    BSP_BC_CmdSend(SW1_OB_ON);
    
    /* SPI pins configuration is restored when EEPROM feeding line is switched on */
    
    /* Memory SPI MISO Init */  
    temp_gpio_init_struct.Pin       = M95M02_DR_SPI_MISO_PIN;
    temp_gpio_init_struct.Mode      = M95M02_DR_SPI_MISO_MODE;
    temp_gpio_init_struct.Pull      = M95M02_DR_SPI_MISO_PULL;
    temp_gpio_init_struct.Speed     = M95M02_DR_SPI_MISO_SPEED;
    temp_gpio_init_struct.Alternate = M95M02_DR_SPI_MISO_AF;
    HAL_GPIO_Init(M95M02_DR_SPI_MISO_GPIO_PORT, &temp_gpio_init_struct);
    
    /* Memory SPI MOSI Init */  
    temp_gpio_init_struct.Pin       = M95M02_DR_SPI_MOSI_PIN;
    temp_gpio_init_struct.Mode      = M95M02_DR_SPI_MOSI_MODE;
    temp_gpio_init_struct.Pull      = M95M02_DR_SPI_MOSI_PULL;
    temp_gpio_init_struct.Speed     = M95M02_DR_SPI_MOSI_SPEED;
    temp_gpio_init_struct.Alternate = M95M02_DR_SPI_MOSI_AF;
    HAL_GPIO_Init(M95M02_DR_SPI_MOSI_GPIO_PORT, &temp_gpio_init_struct);
    
    /* Memory SPI SCK Init */  
    temp_gpio_init_struct.Pin       = M95M02_DR_SPI_SCK_PIN;
    temp_gpio_init_struct.Mode      = M95M02_DR_SPI_SCK_MODE;
    temp_gpio_init_struct.Pull      = M95M02_DR_SPI_SCK_PULL;
    temp_gpio_init_struct.Speed     = M95M02_DR_SPI_SCK_SPEED;
    temp_gpio_init_struct.Alternate = M95M02_DR_SPI_SCK_AF;
    HAL_GPIO_Init(M95M02_DR_SPI_SCK_GPIO_PORT, &temp_gpio_init_struct);    
    
    /* Memory SPI NSS Init */  
    temp_gpio_init_struct.Pin       = M95M02_DR_S_PIN;
    temp_gpio_init_struct.Mode      = M95M02_DR_S_MODE;
    temp_gpio_init_struct.Pull      = M95M02_DR_S_PULL;
    temp_gpio_init_struct.Speed     = M95M02_DR_S_SPEED;
    HAL_GPIO_Init(M95M02_DR_S_GPIO_PORT, &temp_gpio_init_struct);       
  }
  else
  {
    PRINTF("BSP_BC_CmdSend(SW1_OB_OFF) EEPROM\r\n");
    BSP_BC_CmdSend(SW1_OB_OFF);
    
    /* SPI pins are configured as output and set to low level in order to isolate EEPROM subcircuit when it is switched off */
    temp_gpio_init_struct.Pin       = (M95M02_DR_SPI_MISO_PIN | M95M02_DR_SPI_MOSI_PIN | M95M02_DR_SPI_SCK_PIN | M95M02_DR_S_PIN);
    temp_gpio_init_struct.Mode      = GPIO_MODE_OUTPUT_PP;
    temp_gpio_init_struct.Pull      = GPIO_NOPULL;
    temp_gpio_init_struct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(M95M02_DR_SPI_GPIO_PORT, &temp_gpio_init_struct);     
    
    HAL_GPIO_WritePin(M95M02_DR_SPI_GPIO_PORT, (M95M02_DR_SPI_MISO_PIN | M95M02_DR_SPI_MOSI_PIN | M95M02_DR_SPI_SCK_PIN | M95M02_DR_S_PIN), GPIO_PIN_RESET);
  }
  
  /* Platform status variable is updated */ 
  PlatformStatus.b.SW1_OB = status;
  
  HAL_Delay(100);
}   

  
/**
  * @brief It switches on or off the Type-C Controller feeding line
  * @param status Allowed values are ENABLE or DISABLE
  * @retval none
  */
void BSP_PowerTypeCCtrl(FunctionalState status)
{
   GPIO_InitTypeDef temp_gpio_init_struct = {0};

  if (status)
  {
    PRINTF("BSP_BC_CmdSend(SW2_OA_ON) TYPE-C CTRL\r\n");
    BSP_BC_CmdSend(SW2_OA_ON);

    /* Wait STUSB1600 feeding line is switched on before enabling the interrupt on attach pin */
    
    /* Attach pin is configured as input with interrupt */  
    temp_gpio_init_struct.Pin       = STUSB1600_INT_PIN;
    temp_gpio_init_struct.Mode      = STUSB1600_INT_MODE;
    temp_gpio_init_struct.Pull      = STUSB1600_INT_PULL;
    HAL_GPIO_Init(STUSB1600_INT_GPIO_PORT, &temp_gpio_init_struct);    

    HAL_Delay(200);
    
    __HAL_GPIO_EXTI_CLEAR_IT(STUSB1600_INT_PIN);

    
    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(STUSB1600_INT_EXTI_IRQn, STUSB1600_INT_EXTI_IRQ_PP, STUSB1600_INT_EXTI_IRQ_SP);
    HAL_NVIC_EnableIRQ(STUSB1600_INT_EXTI_IRQn);
    
    /* I2C pins configuration is refreshed when STUSB1600 feeding line is switched on */
    
    /* SCL and SDA Init */  
    temp_gpio_init_struct.Pin       = (LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN);
    temp_gpio_init_struct.Mode      = LORA_TRAKER_I2C_SCL_SDA_MODE;
    temp_gpio_init_struct.Pull      = LORA_TRAKER_I2C_SCL_SDA_PULL;
    temp_gpio_init_struct.Speed     = LORA_TRAKER_I2C_SCL_SDA_SPEED;
    temp_gpio_init_struct.Alternate = LORA_TRAKER_I2C_SCL_SDA_AF;
    HAL_GPIO_Init(LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, &temp_gpio_init_struct);
  }
  else
  {
    /* EXTI interrupt is disabled*/
//    HAL_NVIC_DisableIRQ(STUSB1600_INT_EXTI_IRQn);    

    /* Attach pin is deinitialized */
    HAL_GPIO_DeInit(STUSB1600_INT_GPIO_PORT, STUSB1600_INT_PIN);

    PRINTF("BSP_BC_CmdSend(SW2_OA_OFF) TYPE-C CTRL\r\n");
    BSP_BC_CmdSend(SW2_OA_OFF);

    /* Attach pin is configured as output push pull */  
    temp_gpio_init_struct.Pin       = STUSB1600_INT_PIN;
    temp_gpio_init_struct.Mode      = GPIO_MODE_OUTPUT_PP;
    temp_gpio_init_struct.Pull      = GPIO_NOPULL;
    temp_gpio_init_struct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(STUSB1600_INT_GPIO_PORT, &temp_gpio_init_struct);    

    HAL_GPIO_WritePin(STUSB1600_INT_GPIO_PORT, STUSB1600_INT_PIN, GPIO_PIN_RESET);

    
    /* I2C pins are configured as output and set to low level waiting for STUSB1600 feeding line goes down */
    temp_gpio_init_struct.Pin       = (LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN);
    temp_gpio_init_struct.Mode      = GPIO_MODE_OUTPUT_PP;
    temp_gpio_init_struct.Pull      = GPIO_NOPULL;
    temp_gpio_init_struct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, &temp_gpio_init_struct);     
    
    HAL_GPIO_WritePin(LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, (LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN), GPIO_PIN_RESET);
    
    /* Wait voltages go down to zero */
    HAL_Delay(200);

    /* I2C pins configuration is restored */    
    
    /* SCL and SDA Init */  
    temp_gpio_init_struct.Pin       = (LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN);
    temp_gpio_init_struct.Mode      = LORA_TRAKER_I2C_SCL_SDA_MODE;
    temp_gpio_init_struct.Pull      = LORA_TRAKER_I2C_SCL_SDA_PULL;
    temp_gpio_init_struct.Speed     = LORA_TRAKER_I2C_SCL_SDA_SPEED;
    temp_gpio_init_struct.Alternate = LORA_TRAKER_I2C_SCL_SDA_AF;
    HAL_GPIO_Init(LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, &temp_gpio_init_struct);    
  }

  /* Platform status variable is updated */ 
  PlatformStatus.b.SW2_OA = status;  

  HAL_Delay(100);

}    


/**
  * @brief It switches on or off the sensors feeding line
  * @param status Allowed values are ENABLE or DISABLE
  * @retval none
  */
void BSP_PowerSensors(FunctionalState status)
{
  GPIO_InitTypeDef temp_gpio_init_struct = {0};

  if (status)
  {
    PRINTF("BSP_BC_CmdSend(SW2_OB_ON) SENSORS\r\n");
    BSP_BC_CmdSend(SW2_OB_ON);
    
    /* I2C pins configuration is refreshed when sensors feeding line is switched on */
    HAL_Delay(200);
    
    /* SCL and SDA Init */  
    temp_gpio_init_struct.Pin       = (LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN);
    temp_gpio_init_struct.Mode      = LORA_TRAKER_I2C_SCL_SDA_MODE;
    temp_gpio_init_struct.Pull      = LORA_TRAKER_I2C_SCL_SDA_PULL;
    temp_gpio_init_struct.Speed     = LORA_TRAKER_I2C_SCL_SDA_SPEED;
    temp_gpio_init_struct.Alternate = LORA_TRAKER_I2C_SCL_SDA_AF;
    HAL_GPIO_Init(LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, &temp_gpio_init_struct);
  }
  else
  {
    PRINTF("BSP_BC_CmdSend(SW2_OB_OFF) SENSORS\r\n");
    BSP_BC_CmdSend(SW2_OB_OFF);

    /* I2C pins are configured as output and set to low level waiting for sensors feeding line goes down */
    temp_gpio_init_struct.Pin       = (LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN);
    temp_gpio_init_struct.Mode      = GPIO_MODE_OUTPUT_PP;
    temp_gpio_init_struct.Pull      = GPIO_NOPULL;
    temp_gpio_init_struct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, &temp_gpio_init_struct);     
    
    HAL_GPIO_WritePin(LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, (LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN), GPIO_PIN_RESET);
    
    /* Wait voltages go down to zero */
    HAL_Delay(200);

    /* I2C pins configuration is restored */    
    
    /* SCL and SDA Init */  
    temp_gpio_init_struct.Pin       = (LORA_TRAKER_I2C_SCL_PIN | LORA_TRAKER_I2C_SDA_PIN);
    temp_gpio_init_struct.Mode      = LORA_TRAKER_I2C_SCL_SDA_MODE;
    temp_gpio_init_struct.Pull      = LORA_TRAKER_I2C_SCL_SDA_PULL;
    temp_gpio_init_struct.Speed     = LORA_TRAKER_I2C_SCL_SDA_SPEED;
    temp_gpio_init_struct.Alternate = LORA_TRAKER_I2C_SCL_SDA_AF;
    HAL_GPIO_Init(LORA_TRAKER_I2C_SCL_SDA_GPIO_PORT, &temp_gpio_init_struct);
  }
  
  /* Platform status variable is updated */ 
  PlatformStatus.b.SW2_OB = status;  
  
    HAL_Delay(100);

}   

/**
  * @brief  System reset function
  * @param  None
  * @retval None
  */
void SystemResetHook(void)
{
  HAL_NVIC_SystemReset();
}


/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected to the EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
#ifdef LORA_SMART_TRACKER
  case LIS2DW12_INT2_O_PIN: 
    mems_int2_detected = 1;
    break;
    
  case STUSB1600_INT_PIN:
    STUSB1600_int_detected = 1;
    break;
    
  case STBC02_CHG_PIN:
    BSP_BC_ChgPinHasToggled();
    STBC02_nCHG_int_detected++;
    break;
    
  case WAKE_BUTTON_PIN:
    SystemResetHook();
    bWakeButtonPushed = 1;
    break;

#else /* LORA_SMART_TRACKER */
    
  case   LSM6DSL_INT1_PIN:
    mems_int1_detected = 1;
    break;
    
  case   LSM6DSL_INT2_PIN:
    mems_int2_detected = 1;
    break;
#endif /* LORA_SMART_TRACKER */
    
  case USER_BUTTON_PIN:
    bUserButtonPushed = 1;
    break;
    
  default:
    HW_GPIO_IrqHandler( GPIO_Pin );
    break;
  }

}

#ifdef LORA_SMART_TRACKER
/**
  * @brief  Wake button interrupt 
  * @param  None
  * @retval 1 if wake button has been pushed, 0 otherwise
  */
uint8_t GetWakeButtonPushed(void)
{
  uint8_t nRetVal = bWakeButtonPushed;
  
  bWakeButtonPushed = 0;
  
  return nRetVal;
}
#endif //LORA_SMART_TRACKER

/**
  * @brief  User button interrupt 
  * @param  None
  * @retval 1 if user button has been pushed, 0 otherwise
  */
uint8_t GetUserButtonPushed(void)
{
  uint8_t nRetVal = bUserButtonPushed;
  
  bUserButtonPushed = 0;
  
  return nRetVal;
}

/**
  * @brief  Interrupt management
  * @param  None
  * @retval None
  */
void SystemInterruptManager (void)
{
  /* STUSB1600_INT interrupt management */
  if (STUSB1600_int_detected)
  {
    if (HAL_GPIO_ReadPin(STUSB1600_INT_GPIO_PORT, STUSB1600_INT_PIN) && PlatformStatus.b.USB_CONNECTED)
    {
      PRINTF("USB type-C is detached\r\n");
      MSP_USB_InitStatus(DISABLE);
      
      BSP_PowerTypeCCtrl(DISABLE);
      
      PRINTF("BC_IO_CHG_Init()\r\n");
      BC_IO_CHG_DeInit();
      BC_IO_CHG_Init();
    }
    
    /* Interrupt flag is cleared */
    STUSB1600_int_detected = 0;
    STBC02_nCHG_int_detected = 0;
  }
  
  /* STBC02_nCHG interrupt management */
  if (STBC02_nCHG_int_detected >=3)
  {
    if(PlatformStatus.b.USB_CONNECTED != 1)
    {
      MSP_USB_InitStatus(ENABLE);
      
      BC_IO_CHG_DeInit();
      BC_IO_CHG_Init();
      
      BSP_PowerTypeCCtrl(ENABLE);
      PRINTF("USB type-C is attached\r\n");
      PlatformStatus.b.WELCOME_MESSAGE_PENDING = 1;
    }
    
    /* Interrupt flag is cleared */
    STBC02_nCHG_int_detected = 0;
  }
  
}


/**
  * @brief USB initalization status
  * @param status: ENABLE/DISABLE
  * @retval None
  */
static void MSP_USB_InitStatus(FunctionalState status)
{
#ifdef USB_ENABLED
  if (status)
  {
    HW_USB_DEVICE_Init();
  }
  else
  {
    HW_USB_DEVICE_DeInit();
    
    /* Disable USB DP Pull-up */
    __HAL_RCC_USB_CLK_ENABLE();
    HAL_PCD_DevDisconnect(hUsbDeviceFS.pData);
    __HAL_RCC_USB_CLK_DISABLE();
  }
#endif //USB_ENABLED
  
  /* Platform status variable is updated */ 
  PlatformStatus.b.USB_CONNECTED = status;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
