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
#define RA_NSS_Pin GPIO_PIN_15
#define RA_NSS_GPIO_Port GPIOA
#define RA_SCK_Pin GPIO_PIN_3
#define RA_SCK_GPIO_Port GPIOB
#define TCXO_EN_Pin GPIO_PIN_12
#define TCXO_EN_GPIO_Port GPIOA
#define RA_DIO0_Pin GPIO_PIN_4
#define RA_DIO0_GPIO_Port GPIOB
#define RA_DIO0_EXTI_IRQn EXTI4_15_IRQn
#define RA_DIO3_Pin GPIO_PIN_13
#define RA_DIO3_GPIO_Port GPIOC
#define RA_DIO3_EXTI_IRQn EXTI4_15_IRQn
#define UART_RX_Pin GPIO_PIN_10
#define UART_RX_GPIO_Port GPIOA
#define ANT_BST_Pin GPIO_PIN_1
#define ANT_BST_GPIO_Port GPIOC
#define RA_RES_Pin GPIO_PIN_0
#define RA_RES_GPIO_Port GPIOC
#define RA_DIO1_Pin GPIO_PIN_1
#define RA_DIO1_GPIO_Port GPIOB
#define RA_DIO1_EXTI_IRQn EXTI0_1_IRQn
#define UART_TX_Pin GPIO_PIN_9
#define UART_TX_GPIO_Port GPIOA
#define ANT_RX_Pin GPIO_PIN_1
#define ANT_RX_GPIO_Port GPIOA
#define ANT_TX_Pin GPIO_PIN_2
#define ANT_TX_GPIO_Port GPIOC
#define GPS_PPS_Pin GPIO_PIN_14
#define GPS_PPS_GPIO_Port GPIOB
#define GPS_INT_Pin GPIO_PIN_13
#define GPS_INT_GPIO_Port GPIOB
#define RA_MOSI_Pin GPIO_PIN_7
#define RA_MOSI_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOA
#define RA_DIO2_Pin GPIO_PIN_0
#define RA_DIO2_GPIO_Port GPIOB
#define RA_DIO2_EXTI_IRQn EXTI0_1_IRQn
#define RA_MISO_Pin GPIO_PIN_6
#define RA_MISO_GPIO_Port GPIOA
#define BUTTON_Pin GPIO_PIN_3
#define BUTTON_GPIO_Port GPIOA


#define SENSOR_EN_PIN GPIO_PIN_7
#define SENSOR_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define GPS_I2C_ADDRESS 0x42


// comment out these defines to disable sensor or GPS
#define SENSOR_ENABLED
#define GPS_ENABLED
#define RADIO_ENABLED
//#define SPECIAL_MESSAGE

/*!
 * Defines the application data transmission duty cycle. 5 minutes, value in [ms].
 */

#define APP_TX_DUTYCYCLE                           300000

#define ICSPACE16
//#define ICSPACE17

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
