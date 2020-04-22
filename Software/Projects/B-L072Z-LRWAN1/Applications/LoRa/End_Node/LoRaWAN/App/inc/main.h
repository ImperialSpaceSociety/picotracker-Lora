/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

#define GPS_PPS_Pin GPIO_PIN_14
#define GPS_PPS_GPIO_Port GPIOB
#define GPS_INT_Pin GPIO_PIN_13
#define GPS_INT_GPIO_Port GPIOB

#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOA

#define BUTTON_Pin GPIO_PIN_3
#define BUTTON_GPIO_Port GPIOA


#define SENSOR_EN_PIN GPIO_PIN_7
#define SENSOR_EN_GPIO_Port GPIOB

#define GPS_EN_PIN GPIO_PIN_11
#define GPS_EN_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

#define GPS_I2C_ADDRESS 0x42



// PRELAUNCH IMPORTANT!
// Enable or disable sensor, Radio, GPS or LED
#define SENSOR_ENABLED   1         /* Enable ms5607 sensor. Init the sensor as well. Allowed values: 0 disabled , 1(default) enabled */
#define GPS_ENABLED      1         /* Enable Ublox GPS. Init the GPS as well. Allowed values: 0 disabled , 1(default) enabled */
#define RADIO_ENABLED    1         /* Enable Radio. WARNING: DISABLED OPTION NOT TESTED PROPERLY. Allowed values: 0 disabled , 1(default) enabled */
#define USE_LED          1         /* Enable LED blinky. Allowed values: 0 disabled , 1(default) enabled */


/* GPS RELATED DEFINES */
/* ----------------------------------------------------------------------------------- */

#define FIX				60		// attempts to poll UBX-NAV-PVT


/* GEOFENCE RELATED DEFINES */
/* ----------------------------------------------------------------------------------- */
/* For geofence testing */
#define DUMMY_GPS_COORDS  0        /* Bypass the GPS chip to return dummy GPS values . Allowed values: 0(default) disabled , 1 enabled */


/* LORAWAN RELATED DEFINES */
/* ----------------------------------------------------------------------------------- */

/*!
 * Defines the application data transmission duty cycle. 5 minutes, value in [ms].
 */

#define APP_TX_DUTYCYCLE                           10000
/*!
 * LoRaWAN Adaptive Data Rate
 * @note Please note that when ADR is enabled the end-device should be static
 */
#define LORAWAN_ADR_STATE LORAWAN_ADR_OFF
/*!
 * LoRaWAN Default data Rate Data Rate
 * @note Please note that LORAWAN_DEFAULT_DATA_RATE is used only when ADR is disabled 
 */
#define LORAWAN_DEFAULT_DATA_RATE DR_5



#define SAVE_FRAME_COUNTER_IN_INTERNAL_EEPROM           1   /* Storing frame counter in EEPROM. Allowed values: 0 disabled , 1 (default) enabled */


/* CALL SIGN */

//#define ICSPACE16
//#define ICSPACE17
//#define ICSPACE18
//#define ICSPACE19
#define ICSPACE20


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
