/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include "ms5607.h"
#include "ublox.h"
#include "geofence.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SHORT_CYCLE			46		// value / 0.83 = ~duration of one main loop in seconds (Normal mode)
#define LONG_CYCLE			96		// value / 0.83 = ~duration of one main loop in seconds (Power Saving mode)
#define SOLAR				0		// mV
#define BATTERY				2500	// mV
#define BATTERY_ON			3.0		// mV
#define FIX					90		// attempts to poll UBX-NAV-PVT
#define SATS				4		// number of satellites required for positional solution

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

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

// Temperature Pressure variables
double Pressure; // compensated pressure value
double Temperature; // compensated temperature value


// GEOFENCE variables
uint32_t GEOFENCE_LoRa_frequency					= 0;
uint32_t GEOFENCE_no_tx										= 0;


//I2C related
uint8_t	i2c_buffer[2];
HAL_StatusTypeDef i2c_status;


// Battery/Solar voltage
uint32_t VCC_ADC												= 0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}


void check_ADC(void);

/* USER CODE END PFP */


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	


  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
	// keep checking if vcc voltage is high enough to carry on. NOT SURE IF NEEDED!. I think I should use inbuilt voltage measuremnt function
	
	
	HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_SET);

	
	// Setup pressure and temperature sensor
	ms5607_Init();

	// GPS SETUP
	setup_GPS();
	

	// GPS INITIAL BACKUP
	Backup_GPS();




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		MS5607_get_temp_pressure();
		
		printf("Temperature degrees C: "); 
		printf("%lf", Temperature); 
		printf("\r\n"); 
		printf("Pressure mBar: "); 
		printf("%lf", Pressure); 
		printf("\r\n");

		check_ADC(); // check solar voltage? not sure if accurate
		


		// GET GPS FIX
		fixAttemptCount = 0;
		
		while(1)				// poll UBX-NAV-PVT until the module has fix
		{
			
			GPSfix_type = 0;
			GPSfix_OK = 0;
			GPSsats = 0;
			
			Wakeup_GPS();

			UBLOX_request_UBX(request0107, 8, 100, UBLOX_parse_0107);                 // get fix info UBX-NAV-PVT

			if(GPSfix_type == 3 && GPSfix_OK == 1 && GPSsats >= SATS) break;          // check if we have a good fix
			
			fixAttemptCount++;
			HAL_Delay(1000);

			
			/* If fix taking too long, reset and re-initialize GPS module. 
			 * It does a forced hardware reset and recovers from a warm start
			 * Reset only after 70 tries
			 */
			if(fixAttemptCount > FIX)														
			{
				UBLOX_send_message(resetReceiver, sizeof(resetReceiver));				// reset GPS module. warm start
				setup_GPS();                                                    // configure gps module again
				GPSfix_type = 0;
				GPSfix_OK = 0;
				GPSsats = 0;
				break;
				
			}
		}
		
		// PUT GPS TO SLEEP
		Backup_GPS();


		
		// GEOFENCE
		GEOFENCE_position(GPS_UBX_latitude_Float, GPS_UBX_longitude_Float);		// choose the right LoRa frequency based on current location
		LoRa_tx_frequency = GEOFENCE_LoRa_frequency;

		if(GEOFENCE_no_tx){ 
			TXLoRa = 0;												                                  // disable LoRa transmission in NO AIRBORNE areas
		}
		
		// TRANSMIT DATA(TODO)
		
		// GO TO POWERSAVE MODE(TODO)
		
		
		// TODO: make the watchdog work
		// TODO: deinit I2C, uart etc to save power
		
		HAL_Delay(1000);
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void check_ADC(){
	
    HAL_ADC_Start(&hadc);
		if (HAL_ADC_PollForConversion(&hadc, 0xFF) == HAL_OK)
		{
				VCC_ADC = HAL_ADC_GetValue(&hadc);
		}
		HAL_ADC_Stop(&hadc);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
