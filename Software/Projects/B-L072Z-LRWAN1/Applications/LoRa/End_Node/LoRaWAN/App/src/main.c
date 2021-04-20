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
#include "main.h"
#include "reset_debug.h"
#include "playback.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//#define LOW_POWER_DISABLE

// IMPT define switches in main.h to use or not use the GPS, sensor and radio and app duty cycle
#define LPP_APP_PORT 99

#define WATCHDOG_PAT_INTERVAL 10000 // milliseconds

/*!
 * LoRaWAN application port
 * @note do not use 224. It is reserved for certification
 */
#define LORAWAN_APP_PORT 2
/*!
 * LoRaWAN default endNode class port
 */
#define LORAWAN_DEFAULT_CLASS CLASS_A
/*!
 * LoRaWAN default confirm state
 */
#define LORAWAN_DEFAULT_CONFIRM_MSG_STATE LORAWAN_UNCONFIRMED_MSG

/*!
 * User application data
 */
static uint8_t AppDataBuff[LORAWAN_APP_DATA_BUFF_SIZE];

/*!
 * User application data structure
 */
//static lora_AppData_t AppData={ AppDataBuff,  0 ,0 };
lora_AppData_t AppData = {AppDataBuff, 0, 0};

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* call back when LoRa endNode has received a frame*/
static void LORA_RxData(lora_AppData_t *AppData);

/* call back when LoRa endNode has just joined*/
static void LORA_HasJoined(void);

/* call back when LoRa endNode has just switch the class*/
static void LORA_ConfirmClass(DeviceClass_t Class);

/* call back when server needs endNode to send a frame*/
static void LORA_TxNeeded(void);

/* LoRa endNode send request*/
static void Send(void *context);

/* start the tx process*/
static void LoraStartTx(TxEventType_t EventType);

/* tx timer callback function*/
static void OnTxTimerEvent(void *context);

/* tx timer callback function*/
static void LoraMacProcessNotify(void);

/* calculate datarate depending on region */
int8_t datarate_calculator(LoRaMacRegion_t LoRaMacRegion);

/* Watchdog pat functions */
static void OnWatchdogPatEvent(void *context);
void watchdog_pat_timer_init(void);

/* Private variables ---------------------------------------------------------*/
/* load Main call backs structure*/
static LoRaMainCallback_t LoRaMainCallbacks = {HW_GetBatteryLevel,
											   HW_GetTemperatureLevel,
											   HW_GetUniqueId,
											   HW_GetRandomSeed,
											   LORA_RxData,
											   LORA_HasJoined,
											   LORA_ConfirmClass,
											   LORA_TxNeeded,
											   LoraMacProcessNotify};
LoraFlagStatus LoraMacProcessRequest = LORA_RESET;
LoraFlagStatus AppProcessRequest = LORA_RESET;
LoraFlagStatus WatchdogPatRequest = LORA_RESET;

static TimerEvent_t TxTimer;
static TimerEvent_t WatchdogPatTimer;

// Set up brown out reset voltage as low as possible
void set_brownout_level(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	reset_cause_t reset_cause = reset_cause_get();

	/* STM32 HAL library initialization*/
	HAL_Init();

	/* Configure the system clock*/
	SystemClock_Config();

	/* Configure the debug mode*/
	DBG_Init();

	/* Set Brown out reset level voltage to 1.7V */
	set_brownout_level();

	/* Initialise serial debug interface */
	TraceInit();
	PRINTF("\n\nThe system reset cause is \"%s\"\n", reset_cause_get_name(reset_cause));

	PRINTF("\r\n\r\n");
	PRINTF("************************************ \r\n");
	PRINTF("* Picotracker Lora                 * \r\n");
	PRINTF("* Imperial College Space Society   * \r\n");
	PRINTF("************************************ \r\n\r\n");

	PRINTF("SELFTEST: Initialising Hardware\n\r");

	/* Configure the hardware*/
	HW_Init();

	HAL_IWDG_Refresh(&hiwdg);

	/*Disbale Stand-by mode*/
	LPM_SetOffMode(LPM_APPLI_Id, LPM_Disable);

	HAL_IWDG_Refresh(&hiwdg);

#if GPS_ENABLED
	/* GET intial location fix to set LORA region 
	 * The program cannot go on to unless it gets a GPS fix. It is neccessary for it to try forever
	 * It needs a GPS fix to get the right LoRa params for the region
	 */
	PRINTF("SELFTEST: Attempting to get a GPS fix\n\r");
	get_location_fix(GPS_LOCATION_FIX_TIMEOUT);

	HAL_IWDG_Refresh(&hiwdg);

	if (get_latest_gps_status() == GPS_SUCCESS)
	{
		/* Find out which region of world we are in and update region parm*/
		update_geofence_position(gps_info.GPS_UBX_latitude_Float, gps_info.GPS_UBX_longitude_Float);

		HAL_IWDG_Refresh(&hiwdg);

		/* Save current polygon to eeprom only if gps fix was valid */
		EepromMcuWriteBuffer(LORAMAC_REGION_EEPROM_ADDR, (void *)&current_loramac_region, sizeof(LoRaMacRegion_t));

		HAL_IWDG_Refresh(&hiwdg);
	}
	else
	{
/* read the eeprom value instead */
// TODO: must ensure that eeprom is not filled with garbage. i.e. when the eeprom has never been programed
#if USE_NVM_STORED_LORAWAN_REGION
		EepromMcuReadBuffer(LORAMAC_REGION_EEPROM_ADDR, (void *)&current_loramac_region, sizeof(LoRaMacRegion_t));
#endif

		HAL_IWDG_Refresh(&hiwdg);
	}

#endif

	PRINTF("SELFTEST: Now the radio should transmit\n\r");

	PRINTF("APP DUTY CYCLE(TX INTERVAL maybe longer depending on message length and datarate) : %d\n\r", APP_TX_DUTYCYCLE);

	while (1)
	{

		/* select data rate depending on region of the world. */
		int8_t dr = datarate_calculator(current_loramac_region);

		LoRaParam_t LoRaParamInit = {LORAWAN_ADR_STATE, dr, LORAWAN_PUBLIC_NETWORK};

		/* Configure the Lora Stack*/
		LORA_Init(&LoRaMainCallbacks, &LoRaParamInit); // sets up LoRa settings depending on the location we are in.

		HAL_IWDG_Refresh(&hiwdg);

		PRINTF("RANDTEST:%d\n", randr(1, 100));

/* Send a join request */
#if RADIO_ENABLED
		LORA_Join();

		HAL_IWDG_Refresh(&hiwdg);

		/* Init and start the tx interval timer */
		LoraStartTx(TX_ON_TIMER);

		HAL_IWDG_Refresh(&hiwdg);

#endif

		/* Keep transmiting data packets every period defined by APP_TX_DUTYCYCLE */
		while (1)
		{

			if (AppProcessRequest == LORA_SET)
			{
				/*reset notification flag*/
				AppProcessRequest = LORA_RESET;

				/*Here lies the function to read sensor and GPS, parse and send it*/
				Send(NULL);
				/* if the tracker moves into another region, break out of main loop and 
				* reinit LoRa radio regional params
				*/
				if (lora_settings_status == INCORRECT)
				{

					PRINTF("Breaking out of main loop to reinit LoRa regional settings\n\r");
					TimerStop(&TxTimer);

					break;
				}
			}

			if (LoraMacProcessRequest == LORA_SET)
			{
				/*reset notification flag*/
				LoraMacProcessRequest = LORA_RESET;
				LoRaMacProcess();
			}

			if (WatchdogPatRequest == LORA_SET)
			{
				/*Pat the watchdog*/
				WatchdogPatRequest = LORA_RESET;
				HAL_IWDG_Refresh(&hiwdg);
			}

			/*If a flag is set at this point, mcu must not enter low power and must loop*/
			DISABLE_IRQ();

			/* if an interrupt has occurred after DISABLE_IRQ, it is kept pending 
			 * and cortex will not enter low power anyway  */
			if ((LoraMacProcessRequest != LORA_SET) && (AppProcessRequest != LORA_SET) && (WatchdogPatRequest != LORA_SET))
			{
#ifndef LOW_POWER_DISABLE
				LPM_EnterLowPower();
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
	LoraMacProcessRequest = LORA_SET;
}

static void LORA_HasJoined(void)
{
#if (OVER_THE_AIR_ACTIVATION != 0)
	PRINTF("JOINED\n\r");
#endif
	LORA_RequestClass(LORAWAN_DEFAULT_CLASS);
}

static void Send(void *context)
{
	HAL_IWDG_Refresh(&hiwdg);

	/* now join if not yet joined. */
#if RADIO_ENABLED
	if (LORA_JoinStatus() != LORA_SET)
	{
		/* Go ahead and join */
		LORA_Join();

		HAL_IWDG_Refresh(&hiwdg);

		return;
	}
#endif

	/* Temporarily stop tx interval timer until GPS gets a lock */
	// TODO: this timerstop MUST be removed.
	TimerStop(&TxTimer);

	HAL_IWDG_Refresh(&hiwdg);

	/* reading sensors and GPS */
	BSP_sensor_Read();

	HAL_IWDG_Refresh(&hiwdg);

	/* Restart tx interval timer */
	TimerStart(&TxTimer);

	if (get_latest_gps_status() == GPS_SUCCESS)
	{
		/* Find out which region of world we are in and update region parm*/
		update_geofence_position(gps_info.GPS_UBX_latitude_Float, gps_info.GPS_UBX_longitude_Float);

		/* Save current polygon to eeprom only if gps fix was valid */
		EepromMcuWriteBuffer(LORAMAC_REGION_EEPROM_ADDR, (void *)&current_loramac_region, sizeof(LoRaMacRegion_t));

		HAL_IWDG_Refresh(&hiwdg);
	}

	/* reinit everything if it enters another LoRaWAN region. */
	if (lora_settings_status == INCORRECT)
	{
		PRINTF("LoRa Regional settings incorrect. Data send terminated\n\r");

		HAL_IWDG_Refresh(&hiwdg);

		return;
	}

	/* Don't tx when over regions where we are not supposed to tx
   * There is currenly no region defined in geofence.h that prohibits tx.
   */
	if (tx_permission == TX_NOT_OK)
	{
		TVL1(PRINTF("Entered NO tx region. Data send terminated\n\r");)

		HAL_IWDG_Refresh(&hiwdg);

		return;
	}

	prepare_tx_buffer();

	HAL_IWDG_Refresh(&hiwdg);

	AppData.Port = LPP_APP_PORT;
	AppData.Buff = get_tx_buffer();
	AppData.BuffSize = get_tx_buffer_len();

	// Print out buffer for debug
	PRINTF("Buffer to tx:\n", AppData.BuffSize);

	for (int i = 0; i < AppData.BuffSize; i++)
	{
		PRINTF("%02x", AppData.Buff[i]);
	}
	PRINTF("\n");
	PRINTF("tx_str_buffer_len: %d\n\n", AppData.BuffSize);

#if RADIO_ENABLED
	LORA_send(&AppData, LORAWAN_DEFAULT_CONFIRM_MSG_STATE);
#endif

	HAL_IWDG_Refresh(&hiwdg);
}

static void LORA_RxData(lora_AppData_t *AppData)
{
	/* USER CODE BEGIN 4 */
	PRINTF("PACKET RECEIVED ON PORT %d\n\r", AppData->Port);

	switch (AppData->Port)
	{
	case 3:
		/*this port switches the class*/
		if (AppData->BuffSize == 1)
		{
			switch (AppData->Buff[0])
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
		break;

	case LPP_APP_PORT:
		break;

	case DOWNLINK_CONFIG_PORT:

		PRINTF("Received data: ");

		for (int i = 0; i < AppData->BuffSize; i++)
		{
			PRINTF("%02x", AppData->Buff[i]);
		}
		PRINTF("\n\n");

		manage_incoming_instruction(AppData->Buff);

		break;

	default:
		break;
	}
	/* USER CODE END 4 */
}

static void OnWatchdogPatEvent(void *context)
{
	TimerStart(&WatchdogPatTimer);
	WatchdogPatRequest = LORA_SET;
}

void watchdog_pat_timer_init()
{
	/* send everytime timer elapses */
	TimerInit(&WatchdogPatTimer, OnWatchdogPatEvent);
	TimerSetValue(&WatchdogPatTimer, WATCHDOG_PAT_INTERVAL);
	OnWatchdogPatEvent(NULL);
}

static void OnTxTimerEvent(void *context)
{
	/* Wait for next tx slot. 
	 * An interrupt service routine
	 * The timer, &TxTimer, calls this function after the elapsed time of length defined
	 * by APP_TX_DUTYCYCLE. Then this function tells the tracker that it is safe to transmit
   * now by setting AppProcessRequest.
	 * This function also restarts the timer so that it can get called again after
	 * the elapsed period.
	 */
	TimerStart(&TxTimer);

	AppProcessRequest = LORA_SET;
}

static void LoraStartTx(TxEventType_t EventType)
{
	if (EventType == TX_ON_TIMER)
	{
		/* send everytime timer elapses */
		TimerInit(&TxTimer, OnTxTimerEvent);
		TimerSetValue(&TxTimer, APP_TX_DUTYCYCLE);
		OnTxTimerEvent(NULL);
	}
	else
	{
		/* send everytime button is pushed */
		GPIO_InitTypeDef initStruct = {0};

		initStruct.Mode = GPIO_MODE_IT_RISING;
		initStruct.Pull = GPIO_PULLUP;
		initStruct.Speed = GPIO_SPEED_HIGH;

		HW_GPIO_Init(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, &initStruct);
		HW_GPIO_SetIrq(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, 0, Send);
	}
}

static void LORA_ConfirmClass(DeviceClass_t Class)
{
	PRINTF("switch to class %c done\n\r", "ABC"[Class]);

	/*Optionnal*/
	/*informs the server that switch has occurred ASAP*/
	AppData.BuffSize = 0;
	AppData.Port = LORAWAN_APP_PORT;

	LORA_send(&AppData, LORAWAN_UNCONFIRMED_MSG);
}

static void LORA_TxNeeded(void)
{
	AppData.BuffSize = 0;
	AppData.Port = LORAWAN_APP_PORT;

	LORA_send(&AppData, LORAWAN_UNCONFIRMED_MSG);
}

void set_brownout_level(void)
{ /*  BOR Reset threshold levels for 1.7V - 1.8V VDD power supply */
	if ((FLASH_OB_GetBOR() & 0x0F) != OB_BOR_LEVEL1)
	{
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
* Use datarate of DR_5 over the EU but DR_4 over rest of the world
*/
int8_t datarate_calculator(LoRaMacRegion_t LoRaMacRegion)
{
	int8_t dr = 0;

	switch (LoRaMacRegion)
	{
	case LORAMAC_REGION_EU868:
		dr = DR_5;
		break;

	default:
		dr = DR_4;
		break;
	}

	return dr;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
