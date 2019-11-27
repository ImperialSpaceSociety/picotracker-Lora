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
#define PA15_RESERVED_Pin GPIO_PIN_15
#define PA15_RESERVED_GPIO_Port GPIOA
#define PB3_RESERVED_Pin GPIO_PIN_3
#define PB3_RESERVED_GPIO_Port GPIOB
#define PA12_RESERVED_Pin GPIO_PIN_12
#define PA12_RESERVED_GPIO_Port GPIOA
#define PB4_RESERVED_Pin GPIO_PIN_4
#define PB4_RESERVED_GPIO_Port GPIOB
#define PB4_RESERVED_EXTI_IRQn EXTI4_15_IRQn
#define PC13_RESERVED_Pin GPIO_PIN_13
#define PC13_RESERVED_GPIO_Port GPIOC
#define PC13_RESERVED_EXTI_IRQn EXTI4_15_IRQn
#define PC1_RESERVED_Pin GPIO_PIN_1
#define PC1_RESERVED_GPIO_Port GPIOC
#define PC0_RESERVED_Pin GPIO_PIN_0
#define PC0_RESERVED_GPIO_Port GPIOC
#define PB1_RESERVED_Pin GPIO_PIN_1
#define PB1_RESERVED_GPIO_Port GPIOB
#define PB1_RESERVED_EXTI_IRQn EXTI0_1_IRQn
#define PA1_RESERVED_Pin GPIO_PIN_1
#define PA1_RESERVED_GPIO_Port GPIOA
#define PC2_RESERVED_Pin GPIO_PIN_2
#define PC2_RESERVED_GPIO_Port GPIOC
#define PA7_RESERVED_Pin GPIO_PIN_7
#define PA7_RESERVED_GPIO_Port GPIOA
#define PB0_RESERVED_Pin GPIO_PIN_0
#define PB0_RESERVED_GPIO_Port GPIOB
#define PB0_RESERVED_EXTI_IRQn EXTI0_1_IRQn
#define PA6_RESERVED_Pin GPIO_PIN_6
#define PA6_RESERVED_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
