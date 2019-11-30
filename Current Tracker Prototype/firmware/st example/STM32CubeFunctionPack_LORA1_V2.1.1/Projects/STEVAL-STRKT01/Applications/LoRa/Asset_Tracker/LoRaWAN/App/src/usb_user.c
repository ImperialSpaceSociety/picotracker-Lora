/**
  **************************************************************************************************
  * @file    usb_user.c
  * @author  SRA - System Lab - Sensing & Connectivity Application Team
  * @version V2.1.1
  * @date    10-Oct-2019
  * @brief   This file provides a set of user functions to manage USB peripheral
  **************************************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistributions of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of its contributors
  *    may be used to endorse or promote products derived from this software
  *    without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  **************************************************************************************************
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

/** @addtogroup STEVAL-STRKT01_APP_USB USB
  * @{
  */ 

/** @addtogroup STEVAL-STRKT01_APP_USB_USER USB USER
  * @{
  */    
   
/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "lora.h"
#include "log_manager.h"

#include "usb_user.h"
#include "version.h"

/** @addtogroup STEVAL-STRKT01_APP_USB_USER_Private_TypesDefinitions USB USER Private Types Definitions
  * @brief Private types definitions
  * @{
 */

/* Private typedef -----------------------------------------------------------*/

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_USB_USER_Private_Defines USB USER Private Definitions
  * @brief Private definitions
  * @{
 */

/* Private define ------------------------------------------------------------*/
#define USB_USER_RX_BUFFER_SIZE                       100        /* See APP_RX_DATA_SIZE definition in usb_cdc_if.c file */
#define DELAY_PRINTF                                    2

#define COMMAND_OFFSET                                  0
#define TERMINAL_DEBUG_SEVERITY                         0
#define STD_OUT_ARRAY_LENGHT                            100      
#define USB_SEND_TIMEOUT_LOG                            0x100000
#define USB_SEND_TIMEOUT_TERMINAL                       0x100000

#define         ID1                                 ( 0x1FF80050 )
#define         ID2                                 ( 0x1FF80054 )
#define         ID3                                 ( 0x1FF80064 )

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_USB_USER_Private_Macros USB USER Private Macros
  * @brief Private macros
  * @{
 */

/* Private macro -------------------------------------------------------------*/
#define HEX16(X)  X[0],X[1], X[2], X[3], X[4], X[5], X[6],X[7],X[8],X[9], X[10],X[11], X[12], X[13], X[14], X[15]
#define HEX8(X)   X[0],X[1], X[2], X[3], X[4], X[5], X[6],X[7]

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_USB_USER_Private_FunctionPrototypes USB USER Private Function Prototypes
  * @brief Private function prototypes
  * @{
 */

/* Private function prototypes -----------------------------------------------*/
static uint8_t DBG_PRINTF_TERMINAL(uint16_t L, const char* sFormatString, ...);

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_USB_USER_Private_Variables USB USER Private Variables
  * @brief Private variables
  * @{
 */

/* Private variables ---------------------------------------------------------*/
#ifdef USB_ENABLED
static uint8_t pcUSBUserRxBuffer[USB_USER_RX_BUFFER_SIZE + 1] = { 0 };
static uint32_t nUsbBytesReceived = 0;
#endif //USB_ENABLED
#if defined(USE_AUX_UART_LOG) || defined(USB_ENABLED)
static char sStdOutString[STD_OUT_ARRAY_LENGHT+1];                              //!< Buffer to store the custom printf output
static uint32_t nCharsToPrint=0;
#endif //defined(USE_AUX_UART_LOG)

const uint8_t WelcomeMessage[]="ST Microelectronics\r\nLoRa Smart Tracker firmware\r\n";

/**
  * @brief Console command descriptors array
  */
const xCmdStruct_t xCmdStructVect[] = {
  { "?fwversion",         "View fw info",                                 ProcDbgGetFwVersion,            0 },
  { "?mcuid",             "View MCU ID",                                  ProcDbgGetMcuId,                0 },
  { "!sysreset",          "System reset",                                 ProcDbgSysReset,                0 },
  { "!shutdown",          "System shutdown",                              ProcDbgSysShutdown,             0 },
  { "?welcomemsg",        "Welcome message",                              ProcDbgWelcomeMessage,          0 },
  { "?platformstatus",    "Get the platform settings",                    ProcDbgGetPlatformStatus,       0 },
  { "!defaultsettings",   "Restore EEPROM default settings",              ProcDbgRestoreSettings,         0 },
  { "!lpsensorevent",     "Set Low P on sensor event on/off",             ProcDbgSetLpSensorEvent,        0 },
  { "!lpsleeptimer",      "Set Low P on sleep timer on/off",              ProcDbgSetLpSleepTimer,         0 },
  { "!sendonwake",        "Send data on sensor wakeup (on/off)",          ProcDbgSetSendOnWake,           0 },
  { "!sendonthreshold",   "Send data on sensor threshold (on/off)",       ProcDbgSetSendOnThreshold,      0 },
  { "!loraadronoff",      "Set LoRa ADR on/off",                          ProcDbgSetLoraADR,              0 },
  { "!loradr",            "Set LoRa Data Rate",                           ProcDbgSetLoraDR,               0 },
  { "!lorainterval",      "Set LoRa send interval",                       ProcDbgSetSendInterval,         0 },
  { "?loraack",           "Get LoRa ack variable status",                 ProcDbgGetLoraAckEnabled,       0 },
  { "!loraack",           "Set LoRa ack variable status",                 ProcDbgSetLoraAckEnabled,       0 },
  { "!txtimerintv",       "Set tx timer interval",                        ProcDbgSetTxTimerInterval,      0 },
  { "!format",            "Format EEPROM - Will lose data",               ProcDbgFormateeprom,            0 },
  { "!pushlog",           "Push current data to EEPROM",                  ProcDbgPushLog,                 0 }, 
  { "?getsingleitem",     "Get 1 item from EEPROM",                       ProcDbgGetSingleItem,           0 },
  { "?getlogs",           "Get all items from EEPROM",                    ProcDbgGetLogs,                 0 },
  { "?getunsentlogs",     "Get items not sent from EEPROM",               ProcDbgGetUnsentLogs,           0 },
  { "?logmanager",        "Get EEPROM datalog status",                    ProcDbgGetLogmanager,           0 },
  { "!logmanager",        "Set EEPROM datalog ON/OFF",                    ProcDbgSetLogmanager,           0 },
  { "?gnssappconf",       "GNSS get app config data",                     ProcDbgGetGnssAppConfig,        0 },
  { "!gnssappconf",       "GNSS set app config data",                     ProcDbgSetGnssAppConfig,        0 },
  { "!powergnss",         "GNSS VDD is switched on or off",               ProcDbgPowerGNSS,               0 },
  { "!powereeprom",       "EEPROM VDD is switched on or off",             ProcDbgPowerEEPROM,             0 },
  { "!powertcctrl",       "Type-C controller VDD is switched on or off",  ProcDbgPowerTCCtrl,             0 },
  { "!powersens",         "Sensors VDD is switched on or off",            ProcDbgPowerSens,               0 },
  { "?debugmode",         "Get the debug mode",                           ProcDbgGetDebugMode,            0 },
  { "!debugmode",         "Set the debug mode",                           ProcDbgSetDebugMode,            0 },
  { "?devicejoinstatus",  "Get the LoRa device join status",              ProcDbgGetDeviceStatus,         0 },
  { "?devicejoinparam",   "Get the LoRa join parameters",                 ProcDbgGetLoRaJoinParameters,   0 },
  { "!deviceeui",         "Set the LoRa device EUI",                      ProcDbgSetDeviceEUI,            0 },
  { "!joineui",           "Set the LoRa join EUI",                        ProcDbgSetJoinEUI,              0 },
  { "!appkey",            "Set the application key",                      ProcDbgSetApplicationKey,       0 },
  { "!ntwkkey",           "Set the network key",                          ProcDbgSetNetworkKey,           0 },
  { "!eraselorakeys",     "Erase LoRa keys in EEPROM",                    ProcDbgEraseLoraKeys,           0 },
  { "!triggerlora",       "Trigger a lora sending",                       ProcDbgTriggerLoRaSending,      0 },
  { "?includeepochtime",  "Get 'Include Epoch time' variable status",     ProcDbgGetIncludeEpochTime,     0 },
  { "!includeepochtime",  "Set 'Include Epoch time' variable status",     ProcDbgSetIncludeEpochTime,     0 },
  { "?joinreqintvshort",  "Get 'Shorten join req intv' variable status",  ProcDbgGetShortenJoinReqIntv,   0 },
  { "!joinreqintvshort",  "Set 'Shorten join req intv' variable status",  ProcDbgSetShortenJoinReqIntv,   0 },
  { "!sysrun",            "Set system state to run",                      ProcDbgSystemStateRun,          0 },
  { "!syslp",             "Set system state to low power",                ProcDbgSystemStateLowPower,     0 },
  { "!sysulp",            "Set system state to ultra low power",          ProcDbgSystemStateUltraLowPower,0 },
  { "!gpscoldstart",      "GPS cold start",                               ProcDbgSetColdStart,            0 },
  { "?gpsgetposition",    "Get GPS position",                             ProcDbgGetGPSPosition,          0 },
  { "!geofence",          "Config geofence",                              ProcDbgSetGeoFence,             0 },
  { "?geofence",          "Get geofence status",                          ProcDbgGetGeoFence,             0 },
  { "?sensordata",        "Get sensors data",                             ProcDbgGetSensorData,           0 },
  { "?",                  "View help",                                    ProcDbgHelp,                    0 },
};

/**
  * @}
  */

#ifdef USB_ENABLED

/** @addtogroup STEVAL-STRKT01_APP_USB_USER_Public_Functions USB USER Public Functions
  * @brief Public functions
  * @{
 */

/** @brief DBG_PRINTF_LOG_SAFE implementation
  * @param L reserved
  * @param sFormatString pointer to the string
  * @retval 0 -> OK, 1 -> FAIL 
  */
uint8_t DBG_PRINTF_LOG_SAFE(uint16_t L, const char* sFormatString, ...)
{
  uint8_t xRes = 0;
  return xRes;
}


/** @brief Flush DBG_PRINTF_LOG_SAFE output 
  * @param  None
  * @retval None
  */
void FlushSafePrintf(void)
{
  if(nCharsToPrint)
  {
    USB_User_SendMessage((uint8_t*)sStdOutString, /*strlen(sStdOutString)*/nCharsToPrint, USB_SEND_TIMEOUT_LOG);
    memset(sStdOutString, 0x0, STD_OUT_ARRAY_LENGHT);
    nCharsToPrint = 0;
  }
}

/** @brief DBG_PRINTF_LOG implementation
  * @param L reserved
  * @param sFormatString pointer to the string
  * @retval 0 -> OK, 1 -> FAIL (or trace disabled)
  */
uint8_t DBG_PRINTF_LOG(uint8_t Q, uint16_t L, const char* sFormatString, ...)
{
  uint8_t xRes = 1;
  va_list ap;
  if (PlatformStatus.b.USB_TRACE && (nCharsToPrint < STD_OUT_ARRAY_LENGHT) )
  {
    va_start (ap, sFormatString);
    uint16_t nCharsToAdd = vsnprintf(sStdOutString+nCharsToPrint, STD_OUT_ARRAY_LENGHT-nCharsToPrint, sFormatString, ap);
    nCharsToPrint += nCharsToAdd;
    va_end (ap);
    if(!Q)
    {
      xRes = (USBD_OK != USB_User_SendMessage((uint8_t*)sStdOutString, /*strlen(sStdOutString)*/nCharsToPrint, USB_SEND_TIMEOUT_LOG));
      
      memset(sStdOutString, 0x0, STD_OUT_ARRAY_LENGHT);
      nCharsToPrint = 0;
    }
  }
  return xRes;
}


/** @brief Processing of received terminal string
  * @param none
  * @retval none
  */
void ProcessTerminalString(void)
{
#ifdef COMMAND_INTERPRETER_H
  char OutputStr[100];
  BaseType_t xReturned;
  xReturned = FreeRTOS_CLIProcessCommand( att_data, OutputStr, 80 );
  
#else //COMMAND_INTERPRETER_H
  /* search cmd in cmds list */
  pCmdHandlerFunc_t pHandle = NULL;
  uint8_t index;
  
  if(PlatformStatus.b.WELCOME_MESSAGE_PENDING)
  {
    HAL_Delay(200);
    if(USB_User_SendMessage((void*)"\r\n\r\n", 4, 1) == USBD_OK)
    {
      PlatformStatus.b.WELCOME_MESSAGE_PENDING = 0;
      ProcDbgWelcomeMessage("");
      ProcDbgGetFwVersion("");
    }
  }
  
  if (pcUSBUserRxBuffer[0] == 0)
  {
    return;
  }
  
  if( (pcUSBUserRxBuffer[nUsbBytesReceived - 1] != '\r') && (pcUSBUserRxBuffer[nUsbBytesReceived - 1] != '\n') )
  {
    return;
  }
  else
  {
    index = 0;
    do
    {
      index++ ;
    } while ((pcUSBUserRxBuffer[nUsbBytesReceived - index] == '\r') || (pcUSBUserRxBuffer[nUsbBytesReceived - index] == '\n'));
    pcUSBUserRxBuffer[nUsbBytesReceived - index + 1] = 0;
  }
  
  for(uint32_t i=0;i<countof(xCmdStructVect);i++)
  {
    if(0==strncmp(xCmdStructVect[i].cCmdString, (char*)(pcUSBUserRxBuffer+COMMAND_OFFSET),strlen(xCmdStructVect[i].cCmdString)-COMMAND_OFFSET))
    {
      pHandle = xCmdStructVect[i].pCmdHandlerFunc;
      break;
    }
  }
  
  PlatformStatus.b.USB_TRACE = ENABLE;
  if(pHandle)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nProcessing command: %s\r\n",pcUSBUserRxBuffer+COMMAND_OFFSET);
    pHandle((char*)(pcUSBUserRxBuffer+COMMAND_OFFSET));
    
#if !UART_MINIMAL_ECHO
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Command complete\r\n");
#endif
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nCommand\r\n%s\r\n",pcUSBUserRxBuffer+COMMAND_OFFSET);
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "not found, '?' for HELP\r\n");
  }
  
  memset(pcUSBUserRxBuffer, 0x00, USB_USER_RX_BUFFER_SIZE);
  nUsbBytesReceived = 0;
#endif //COMMAND_INTERPRETER_H
}


/** @brief 
  * @param pBuf pointer to received string
  * @param Len received string lenght
  * @retval None
  */
void USB_User_StoreCommand(uint8_t* pBuf, uint32_t *Len)
{
  if (*Len > USB_USER_RX_BUFFER_SIZE)
  {
    memcpy((char*)pcUSBUserRxBuffer, (char*)pBuf, USB_USER_RX_BUFFER_SIZE);
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "USB Rx buffer size exceeded\r\n");
  }
  else
  {
    if (*Len > USB_USER_RX_BUFFER_SIZE - nUsbBytesReceived)
    {
      memcpy((char*)(pcUSBUserRxBuffer+nUsbBytesReceived), (char*)pBuf, (USB_USER_RX_BUFFER_SIZE - nUsbBytesReceived));
      nUsbBytesReceived = USB_USER_RX_BUFFER_SIZE;
    }
    else
    {
      memcpy((char*)(pcUSBUserRxBuffer+nUsbBytesReceived), (char*)pBuf, (*Len));
      nUsbBytesReceived += (*Len);
    }
  }
  
  if (PlatformStatus.b.USB_DBG == DISABLE)
  {
    PlatformStatus.b.USB_TRACE = DISABLE;
  }
}

/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_APP_USB_USER_Private_Function USB USER Private Function
  * @brief Private functions
  * @{
 */

/* Private functions ---------------------------------------------------------*/

/** @brief DBG_PRINTF_TERMINAL implementation
  * @param L the string lenght
  * @param sFormatString pointer to the string
  * @retval descriptor index, 0xFFFFFFFF not found
  */
uint8_t DBG_PRINTF_TERMINAL(uint16_t L, const char* sFormatString, ...)
{
  uint8_t xRes = 0;
  va_list ap;
  if (CDC_CheckVCP() == USBD_OK)
  {
    va_start (ap, sFormatString);
    vsnprintf(sStdOutString, STD_OUT_ARRAY_LENGHT, sFormatString, ap);
    va_end (ap);
    USB_User_SendMessage((uint8_t*)sStdOutString, strlen(sStdOutString), USB_SEND_TIMEOUT_TERMINAL);
  }
  return xRes;
}


/** @brief Interpreter command line
  * @param none
  * @retval none
  */
void InitCommandLine(void)
{
#ifdef COMMAND_INTERPRETER_H
  for(uint32_t i=0;i<countof(xCmdStructVect);i++)
  {
    FreeRTOS_CLIRegisterCommand( &xCmdStructVect[i] );
  }
#endif /* COMMAND_INTERPRETER_H */
}


/** @brief Get command descriptor index
  * @param pCmd pointer to the command string
  * @retval descriptor index, 0xFFFFFFFF not found
  */
uint32_t GetDescriptorIndex(char* pCmd)
{
#ifdef COMMAND_INTERPRETER_H
  
#else /* COMMAND_INTERPRETER_H */
  for(uint32_t i=0;i<countof(xCmdStructVect);i++)
  {
    if(0==strncmp(xCmdStructVect[i].cCmdString,pCmd,strlen(xCmdStructVect[i].cCmdString)))
    {
      return i;
    }
  }
#endif /* COMMAND_INTERPRETER_H */
  return 0xFFFFFFFF;
}


/**
  * @brief  Send a message over USB.
  * @param  None
  * @retval None
  */
USBD_StatusTypeDef USB_User_SendMessage(uint8_t* pBuf, uint16_t Lenght, uint32_t AttemptsNumber)
{
  USBD_StatusTypeDef temp_usbd_status = USBD_BUSY;
  
  if (CDC_CheckVCP() == USBD_OK)
  {
    if (AttemptsNumber != 0xFFFFFFFF)
    {
      while ((temp_usbd_status == USBD_BUSY) && (AttemptsNumber > 0)) 
      {
        temp_usbd_status = (USBD_StatusTypeDef) CDC_Transmit_FS(pBuf, Lenght);
        AttemptsNumber--;
      }
    }
    else
    {
      while (temp_usbd_status == USBD_BUSY) 
      {
        temp_usbd_status = (USBD_StatusTypeDef) CDC_Transmit_FS(pBuf, Lenght);
      }
    }
  }
  
#if defined(USE_AUX_UART_LOG)
    extern UART_HandleTypeDef dbghuart;
//        HAL_UART_Transmit_DMA(&dbghuart, (uint8_t*)pBuf, /*strlen(pBuf)*/Lenght);
    HAL_UART_Transmit(&dbghuart, (uint8_t*)pBuf, /*strlen(pBuf)*/Lenght, 0x100000);
#endif //defined(USE_AUX_UART_LOG)
  
  return temp_usbd_status;
}


/**
  * @brief  Send a welcome message over USB.
  * @param  None
  * @retval None
*/
USBD_StatusTypeDef USB_User_SendWelcomeMessage(void)
{
  return (USBD_StatusTypeDef) CDC_Transmit_FS((void*)WelcomeMessage, strlen((char const*)WelcomeMessage));
}
#else /* USB_ENABLED */

/** @brief DBG_PRINTF_TERMINAL implementation
  * @param L the string lenght
  * @param sFormatString pointer to the string
  * @retval descriptor index, 0xFFFFFFFF not found
  */
uint8_t DBG_PRINTF_TERMINAL(uint16_t L, const char* sFormatString, ...)
{
  uint8_t xRes = 0;
#if defined(USE_AUX_UART_LOG)
  va_list ap;
//  if (CDC_CheckVCP() == USBD_OK)
  {
    va_start (ap, sFormatString);
    vsnprintf(sStdOutString, STD_OUT_ARRAY_LENGHT, sFormatString, ap);
    va_end (ap);
    
      extern UART_HandleTypeDef dbghuart;
      //        HAL_UART_Transmit_DMA(&dbghuart, (uint8_t*)pBuf, /*strlen(pBuf)*/Lenght);
      HAL_UART_Transmit(&dbghuart, (uint8_t*)sStdOutString, strlen(sStdOutString), 0x100000);
  }
#endif //(USE_AUX_UART_LOG)
  return xRes;
}

/** @brief DBG_PRINTF_LOG implementation
  * @param L reserved
  * @param sFormatString pointer to the string
  * @retval 0 -> OK, 1 -> FAIL (or trace disabled)
  */
uint8_t DBG_PRINTF_LOG(uint8_t Q, uint16_t L, const char* sFormatString, ...)
{
  uint8_t xRes = 1;
#if defined(USE_AUX_UART_LOG)
  va_list ap;
  if (PlatformStatus.b.USB_TRACE && (nCharsToPrint < STD_OUT_ARRAY_LENGHT) )
  {
    va_start (ap, sFormatString);
    uint16_t nCharsToAdd = vsnprintf(sStdOutString+nCharsToPrint, STD_OUT_ARRAY_LENGHT-nCharsToPrint, sFormatString, ap);
    nCharsToPrint += nCharsToAdd;
    va_end (ap);
    if(!Q)
    {
      extern UART_HandleTypeDef dbghuart;
      //        HAL_UART_Transmit_DMA(&dbghuart, (uint8_t*)pBuf, /*strlen(pBuf)*/Lenght);
      HAL_UART_Transmit(&dbghuart, (uint8_t*)sStdOutString, /*strlen(pBuf)*/nCharsToPrint, 0x100000);
      
      memset(sStdOutString, 0x0, STD_OUT_ARRAY_LENGHT);
      nCharsToPrint = 0;
    }
  }
#endif //defined(USE_AUX_UART_LOG)
  return xRes;
}
#endif /* USB_ENABLED */

/** @brief Get firmware version
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetFwVersion)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Current Fw version: %X\r\n", VERSION);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LoRa IOT tracker app version: %d.%d.%d\r\n", (IOT_TRACKER_APP_VER&0xF000)>>12, (IOT_TRACKER_APP_VER&0xF00)>>8, (IOT_TRACKER_APP_VER&0xFF));
  return RET_VAL_CLI;
}


/** @brief Get MCU factory ID
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetMcuId)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nMCU ID: ");
  uint8_t *pnStartMcuIdAddr;
  pnStartMcuIdAddr = (uint8_t *)ID1;
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "%.2X%.2X%.2X%.2X", *(pnStartMcuIdAddr+0), *(pnStartMcuIdAddr+1), *(pnStartMcuIdAddr+2), *(pnStartMcuIdAddr+3));
  pnStartMcuIdAddr = (uint8_t *)ID2;
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "%.2X%.2X%.2X%.2X", *(pnStartMcuIdAddr+0), *(pnStartMcuIdAddr+1), *(pnStartMcuIdAddr+2), *(pnStartMcuIdAddr+3));
  pnStartMcuIdAddr = (uint8_t *)ID3;
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "%.2X%.2X%.2X%.2X\r\n", *(pnStartMcuIdAddr+0), *(pnStartMcuIdAddr+1), *(pnStartMcuIdAddr+2), *(pnStartMcuIdAddr+3));
  
  return RET_VAL_CLI;
}

/** @brief Print a message waiting for USB disconnection
  * @param None
  * @retval None
  */
void PrintShutdownMessage()
{
  while(1)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "DISCONNECT USB cable to shutdown\r\n");
    HAL_Delay(1000);
    LED_Toggle( LED_WHITE );
  }
}


/** @brief System shutdown
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSysShutdown)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "---    SYSTEM SHUTDOWN    ---\r\n");
  
  for(uint8_t n=5; n>0; n--)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "---    SYSTEM SHUTDOWN %d  ---\r\n", n);
    HAL_Delay(1000);
  }
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Sending shipping mode command to STBC02\r\n");
  HAL_Delay(1000);
  BSP_BoardShutdown();
  
  PrintShutdownMessage();
  
  return RET_VAL_CLI;
}


/** @brief System reset
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSysReset)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "---    SYSTEM RESET    ---\r\n");
  
  for(uint8_t n=5; n>0; n--)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "---    SYSTEM RESET %d  ---\r\n", n);
    HAL_Delay(1000);
  }
  SystemResetHook();
  
  return RET_VAL_CLI;
}


/** @brief Show help
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgHelp)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nTerminal HELP:\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\n");
  for(uint32_t i=0;i<countof(xCmdStructVect);i++)
  {
#ifdef COMMAND_INTERPRETER_H
    
#else //COMMAND_INTERPRETER_H
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, xCmdStructVect[i].cCmdString);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "  - ");
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, xCmdStructVect[i].cCmdHelp);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\n");
    }
#endif //COMMAND_INTERPRETER_H
  }
  
  return RET_VAL_CLI;
}

/**
  * @brief Get plaftorm settings
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgRestoreSettings)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Restore EEPROM default settings\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Changes will take effect after restart\r\n");
  PlatformStatus.b.EEPROM_DATA_INITED = 0;
  PlatformStatus.b.RESTART_PENDING = 1;
  BSP_SavePlatformStatusToEeprom();
  if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
  }
}


/**
  * @brief Get platform settings
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetPlatformStatus)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Get Platform settings\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM_DATA_CAN_BE_CHANGED: %d\r\n", PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM_DATA_INITED: %d\r\n", PlatformStatus.b.EEPROM_DATA_INITED );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "RESTART_PENDING: %d\r\n", PlatformStatus.b.RESTART_PENDING );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "STARTUP_MODE: %d\r\n", PlatformStatus.b.STARTUP_MODE );
  PrintStartupMode(PlatformStatus.b.STARTUP_MODE);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "SW1_OA: %d\r\n", PlatformStatus.b.SW1_OA );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "SW1_OB: %d\r\n", PlatformStatus.b.SW1_OB );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "SW2_OA: %d\r\n", PlatformStatus.b.SW2_OA );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "SW2_OB: %d\r\n", PlatformStatus.b.SW2_OB );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "USB_CONNECTED: %d\r\n", PlatformStatus.b.USB_CONNECTED );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "USB_DBG: %d\r\n", PlatformStatus.b.USB_DBG );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "USB_TRACE: %d\r\n", PlatformStatus.b.USB_TRACE );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LP_SLEEP_TIMER: %d\r\n", PlatformStatus.b.LP_SLEEP_TIMER );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LP_SENSOR_EVENT: %d\r\n", PlatformStatus.b.LP_SENSOR_EVENT );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "SEND_ON_WAKE_EVENT: %d\r\n", PlatformStatus.b.SEND_ON_WAKE_EVENT );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "SEND_ON_SENSOR_EVENT: %d\r\n", PlatformStatus.b.SEND_ON_SENSOR_EVENT );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM_FORMATTED: %d\r\n", PlatformStatus.b.EEPROM_FORMATTED );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LOG_MANAGER: %d\r\n", PlatformStatus.b.LOG_MANAGER );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "GNSS_WAIT_FIX: %d\r\n", PlatformStatus.b.GNSS_WAIT_FIX );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "GNSS_FIX_CHECK: %d\r\n", PlatformStatus.b.GNSS_FIX_CHECK );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "RTC_UPDATED: %d\r\n", PlatformStatus.b.RTC_UPDATED );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "GPSTIME_IN_LPP: %d\r\n", PlatformStatus.b.GPSTIME_IN_LPP );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "SHORTEN_JOIN_REQ_INTV: %d\r\n", PlatformStatus.b.SHORTEN_JOIN_REQ_INTV );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LORA_ACK_ENABLED: %d\r\n", PlatformStatus.b.LORA_ACK_ENABLED );
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "xPrevState: %d\r\n", PlatformStatus.s.xPrevState );
  PrintSystemState(PlatformStatus.s.xPrevState);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nxCurrentState: %d\r\n", PlatformStatus.s.xCurrentState );
  PrintSystemState(PlatformStatus.s.xCurrentState);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nxNextState: %d\r\n", PlatformStatus.s.xNextState );
  PrintSystemState(PlatformStatus.s.xNextState);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGNSS_GEOFENCE_MASK: %d\r\n", PlatformStatus.s.GNSS_GEOFENCE_MASK );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "GNSS_GEOFENCE_RADIUS: %d\r\n", PlatformStatus.s.GNSS_GEOFENCE_RADIUS );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LORA_DR: %d\r\n", PlatformStatus.s.LORA_DR );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LORA_ADR: %d\r\n", PlatformStatus.s.LORA_ADR );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "SEND_INTERVAL: %dms\r\n", PlatformStatus.s.SEND_INTERVAL );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "TX_TIMER_INTERVAL: %dms\r\n", PlatformStatus.s.TX_TIMER_INTERVAL );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "APP_LORA_JOINED: %d\r\n", PlatformStatus.b.APP_LORA_JOINED );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "nErrorNoAck: %d\r\n", PlatformStatus.s.nErrorNoAck );
  
  uint16_t batt_level = BSP_GetBatteryLevel16();
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Battery voltage: %dmV\r\n", batt_level );
  uint8_t battery_charge_percentage = BSP_BatteryChargePercentage(batt_level);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Battery charge: %u%%\r\n", battery_charge_percentage);
  
  uint8_t s = BSP_GetChargerStatus();
  PrintChargerStatus(s);
  
#if( OVER_THE_AIR_ACTIVATION != 0 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Application uses the Over-the-Air activation procedure.\r\n");
#else //( OVER_THE_AIR_ACTIVATION != 0 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Application uses the Personalization activation procedure\r\n");
#endif //( OVER_THE_AIR_ACTIVATION != 0 )
  
#if defined( REGION_AS923 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_AS923\r\n");
#elif defined( REGION_AU915 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_AU915\r\n");
#elif defined( REGION_CN470 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_CN470\r\n");
#elif defined( REGION_CN779 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_CN779\r\n");
#elif defined( REGION_EU433 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_EU433\r\n");
#elif defined( REGION_IN865 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_IN865\r\n");
#elif defined( REGION_EU868 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_EU868\r\n");
#elif defined( REGION_KR920 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_KR920\r\n");
#elif defined( REGION_US915 )
  #if defined( HYBRID )
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_US915 (HYBRID)\r\n");
  #else //defined( HYBRID )
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_US915\r\n");
  #endif //defined( HYBRID )
#elif defined( REGION_RU864 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "REGION: REGION_RU864\r\n");
#else
  #error "Please define a region in the compiler options."
#endif
  return RET_VAL_CLI;
}


/**
  * @brief Send welcome message
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgWelcomeMessage)
{
  HAL_Delay(1);
  
#ifdef USB_ENABLED
  USB_User_SendWelcomeMessage();
#endif //USB_ENABLED

  return RET_VAL_CLI;
}

static void FormatEeprom()
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nFormatting the EEPROM\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nThis may take a while\r\n");
  /* ErrorStatus res = LogEvent_Format(NULL); */
  LogEvent_Init(1);
  PlatformStatus.b.EEPROM_FORMATTED = 1;
  BSP_SavePlatformStatusToEeprom();
  if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
  }
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nEEPROM format complete\r\n");
}

/**
  * @brief Format EEPROM to use with logmanager
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI (ProcDbgFormateeprom)
{
  static uint8_t nFnCallTimes = 0;
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nFormat EEPROM for logs saving\r\n");
  if(nFnCallTimes==0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nYou  will loose all data saved in EEPROM\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nTO PROCEED, ISSUE THE COMMAND AGAIN\r\n");
    nFnCallTimes++;
  }
  else
  {
    FormatEeprom();
    PlatformStatus.s.lastReadIndex = 0;
    PlatformStatus.s.lastSavedIndex = 0;
    nFnCallTimes = 0;
  }
}


/**
  * @brief Push current data to EEPROM ( Acc_Act_Inact, T, P, H, Lat, Long, Alt, Batt Lev\r\n")
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgPushLog)
{
  uint32_t n;

  LogEvent_Push_Printf(LOG_EV_NRM, "NRM_%c:%d:%d|%d|%d|%d|%d|%d|%d|%d", 'X', 0, accActInact , 
                       ( int16_t )( sensor_data.temperature * 100 ), ( uint16_t )( sensor_data.pressure * 10 ),
                       ( uint16_t )( sensor_data.humidity * 10 ), 
                       ( int32_t )( sensor_data.latitude * 10000 ), ( int32_t )( sensor_data.longitude * 10000 ), ( int32_t )( sensor_data.altitudeGps * 100 ),
                       (uint32_t) (BSP_GetBatteryLevel16()/10));
  n = LogEvent_GetCount(LOG_EV_NRM);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nType %s #%d: %d items\r\n", LogEvent_GetTypeName(LOG_EV_NRM), LOG_EV_NRM, n);
  
  return RET_VAL_CLI;
}                                   
                                        
/**
  * @brief Get all items from EEPROM
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetLogs)
{ 
  uint32_t n;
  LogEvent_Type_t xTypeR = LOG_EV_NRM;
  LogEvent_Item_t xLogItem = { 0 };
  
  if (xTypeR == LOG_EV_NRM)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nRetreiving NRM type items\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items formatted as: Sent: Acc Act/Inact | T (x10) | P (x10) | H (x2) | Lat | Long | Alt | Batt Lev\r\n"); 
  }
  n = LogEvent_GetCount(xTypeR);
  if (n >0)
  {
    for(uint32_t i=0;i<n;i++) 
    {
      if(SUCCESS == LogEvent_Get(&xLogItem, xTypeR, i, 0))
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\n");
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "#%d: TS: %d\r\n", i, xLogItem.Header.TimeStamp);
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "#%d: %s\r\n", i, xLogItem.Payload);
        char* nQuoteIndex = strchr ((const char*)xLogItem.Payload, ':');
        if(nQuoteIndex != NULL)
        {
          uint32_t nScOut = 0;
          LogData_t data_logged;
          int tsentFlag, tAccEnable, ttemperature, tpressure, thumidity, tlatitude, tlongitude, taltitudeGps, tbatteryLevel;
          nScOut = sscanf(nQuoteIndex, ":%d:%d|%d|%d|%d|%d|%d|%d|%d", &tsentFlag,  &tAccEnable , &ttemperature, &tpressure, &thumidity, &tlatitude, &tlongitude, &taltitudeGps, &tbatteryLevel);
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
            data_logged.epoch_value = xLogItem.Header.TimeStamp;
            DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "%d: %d, %d, %d, %d, %d, %d, %d, %d\r\n", data_logged.sentFlag, data_logged.AccEnable , data_logged.temperature, data_logged.pressure, data_logged.humidity, data_logged.latitude, data_logged.longitude, data_logged.altitudeGps, data_logged.batteryLevel);
          }
          else
          {
            PRINTF("item corrupted\r\n");
          }
        }
        else
        {
          PRINTF("item format not valid\r\n");
        }
      }
      else
      {
        PRINTF("item not available\r\n");
      } 
    } 
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "No item stored\r\n"); 
  }
  
  return RET_VAL_CLI;
}

/**
  * @brief Get items not sent from EEPROM
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetUnsentLogs)
{ 
  uint32_t n;
  LogEvent_Type_t xTypeR = LOG_EV_NRM;
  LogEvent_Item_t xLogItem = { 0 };
  
  if (xTypeR == LOG_EV_NRM)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nRetreiving NRM type items (only unsent items)\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items formatted as: Sent: Acc Act/Inact | T (x10) | P (x10) | H (x2) | Lat | Long | Alt | Batt Lev\r\n"); 
  }
  n = LogEvent_GetCount(xTypeR);
  if (n >0)
  {
    for(uint32_t i=0;i<n;i++) 
    {
      if(SUCCESS == LogEvent_Get(&xLogItem, xTypeR, i, 0))
      {
        char* nQuoteIndex = strchr ((const char*)xLogItem.Payload, ':');
        if(nQuoteIndex != NULL)
        {
          uint32_t nScOut = 0;
          LogData_t data_logged;
          int tsentFlag, tAccEnable, ttemperature, tpressure, thumidity, tlatitude, tlongitude, taltitudeGps, tbatteryLevel;
          nScOut = sscanf(nQuoteIndex, ":%d:%d|%d|%d|%d|%d|%d|%d|%d", &tsentFlag,  &tAccEnable , &ttemperature, &tpressure, &thumidity, &tlatitude, &tlongitude, &taltitudeGps, &tbatteryLevel);
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
            data_logged.epoch_value = xLogItem.Header.TimeStamp;
            if(data_logged.sentFlag == 0)
            {
              DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\n");
              DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "#%d: TS: %d\r\n", i, xLogItem.Header.TimeStamp);
              DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "#%d: %s\r\n", i, xLogItem.Payload);
              DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "%d: %d, %d, %d, %d, %d, %d, %d, %d\r\n", data_logged.sentFlag, data_logged.AccEnable , data_logged.temperature, data_logged.pressure, data_logged.humidity, data_logged.latitude, data_logged.longitude, data_logged.altitudeGps, data_logged.batteryLevel);
            }
          }
          else
          {
            PRINTF("item corrupted\r\n");
          }
        }
        else
        {
          PRINTF("item format not valid\r\n");
        }
      }
      else
      {
        PRINTF("item not available\r\n");
      } 
    } 
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "No item stored\r\n"); 
  }
  
  return RET_VAL_CLI;
}

/**
  * @brief Get one single item from EEPROM
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetSingleItem)
{
  LogEvent_Item_t xLogItem = { 0 };
  char * p_char_identifier = 0;
  int nbitem;
  uint32_t n, nScOut;
  LogEvent_Type_t xTypeR = LOG_EV_NRM;
  
  n = LogEvent_GetCount(xTypeR); 
  p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    nScOut = 0;
    nScOut = sscanf(p_char_identifier, "-%d",  &nbitem);
    if( (nScOut==1) && (nbitem < n) )
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items formatted as: Sent: Acc Act/Inact | T (x10) | P (x10) | H (x2) | Lat | Long | Alt | Batt Lev\r\n"); 
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "#%d: TS: %d\r\n", nbitem, xLogItem.Header.TimeStamp);
      
      if(SUCCESS == LogEvent_Get(&xLogItem, xTypeR, nbitem, 0))
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "#%d: %s\r\n", nbitem, xLogItem.Payload);
        
        char* nQuoteIndex = strchr ((const char*)xLogItem.Payload, ':');
        if(nQuoteIndex != NULL)
        {
          nScOut = 0;
          LogData_t data_logged;
          int tsentFlag, tAccEnable, ttemperature, tpressure, thumidity, tlatitude, tlongitude, taltitudeGps, tbatteryLevel;
          nScOut = sscanf(nQuoteIndex, ":%d:%d|%d|%d|%d|%d|%d|%d|%d", &tsentFlag,  &tAccEnable , &ttemperature, &tpressure, &thumidity, &tlatitude, &tlongitude, &taltitudeGps, &tbatteryLevel);
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
            data_logged.epoch_value = xLogItem.Header.TimeStamp;
            DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "%d, %d, %d, %d, %d, %d, %d, %d, %d\r\n", data_logged.sentFlag, data_logged.AccEnable , data_logged.temperature, data_logged.pressure, data_logged.humidity, data_logged.latitude, data_logged.longitude, data_logged.altitudeGps, data_logged.batteryLevel);
          }
          else
          {
            PRINTF("item corrupted\r\n");
          }
        }
        else
        {
          PRINTF("item format not valid\r\n");
        }
      }
      else
      {
        PRINTF("item not available\r\n");
      }
    }
    else
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\n Item %d not stored\r\n", nbitem);  
    }
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: ?getsingleitem-NNN to get a single item\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "where NNN is the item number\r\n");
  }
  return RET_VAL_CLI;
}


/**
  * @brief Get EEPROM Datalog status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetLogmanager)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Get Logmanager status\r\n");
  if(PlatformStatus.b.EEPROM_FORMATTED)
  {
    if(PlatformStatus.b.LOG_MANAGER)
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Logmanager: running\r\n");
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items in EEPROM: %d\r\n", PlatformStatus.s.lastSavedIndex);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items sent: %d\r\n", PlatformStatus.s.lastReadIndex);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items to be sent: %d\r\n", PlatformStatus.s.lastSavedIndex - PlatformStatus.s.lastReadIndex);
    }
    else
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Logmanager: not running\r\n");
    }
    
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items count NRM: %d (total %d)\r\n", LogEvent_GetCount(LOG_EV_NRM), LogEvent_GetTotalCount(LOG_EV_NRM));
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items count SYS: %d (total %d)\r\n", LogEvent_GetCount(LOG_EV_SYS), LogEvent_GetTotalCount(LOG_EV_SYS));
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Items count CRT: %d (total %d)\r\n", LogEvent_GetCount(LOG_EV_CRT), LogEvent_GetTotalCount(LOG_EV_CRT));
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM need to be formatted, issue '!format' first\r\n");
  }
  
  return RET_VAL_CLI;
}


/**
  * @brief Set the system to start log manager upon lora sending
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetLogmanager)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set Logmanager status\r\n");
  uint8_t param_valid = 0;
  if(PlatformStatus.b.EEPROM_FORMATTED)
  {
    char *p_char_identifier = strstr(pcInStr, "-");
    if (p_char_identifier)
    {
      p_char_identifier++;
      if(*p_char_identifier == '1')
      {
        param_valid = 1;
        PlatformStatus.b.LOG_MANAGER = 1;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Logmanager: running\r\n");
      }
      else if(*p_char_identifier == '0')
      {
        param_valid = 1;
        PlatformStatus.b.LOG_MANAGER = 0;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Logmanager: not running\r\n");
      }
    }
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM need to be formatted, issue '!format' first\r\n");
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !logmanager-1 to start the logmanager\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !logmanager-0 to stop the logmanager\r\n");
  }
  return RET_VAL_CLI;
}

/**
  * @brief Get "Include Epoch time" variable status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetIncludeEpochTime)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Get 'Include Epoch time' variable status\r\n");
  if(PlatformStatus.b.GPSTIME_IN_LPP)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Epoch time is included in payload\r\n");
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Epoch time is NOT included in payload\r\n");
  }
  
  return RET_VAL_CLI;
}

/**
  * @brief Set "Include Epoch time" variable
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetIncludeEpochTime)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set 'Include Epoch time' variable status\r\n");
  uint8_t param_valid = 0;
    char *p_char_identifier = strstr(pcInStr, "-");
    if (p_char_identifier)
    {
      p_char_identifier++;
      if(*p_char_identifier == '1')
      {
        param_valid = 1;
        PlatformStatus.b.GPSTIME_IN_LPP = 1;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Epoch time is included in payload\r\n");
      }
      else if(*p_char_identifier == '0')
      {
        param_valid = 1;
        PlatformStatus.b.GPSTIME_IN_LPP = 0;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Epoch time is NOT included in payload\r\n");
      }
    }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !includeepochtime-1 to include Epoch time\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !includeepochtime-0 to disable Epoch time inclusion\r\n");
  }
  return RET_VAL_CLI;
}

/**
  * @brief Get "Shorten join req intv" variable status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetShortenJoinReqIntv)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Get 'Shorten join req intv' variable status\r\n");
  if(PlatformStatus.b.SHORTEN_JOIN_REQ_INTV)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Parameter=1\r\n");
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Parameter=0\r\n");
  }
  
  return RET_VAL_CLI;
}

/**
  * @brief Set "Shorten join req intv" variable
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetShortenJoinReqIntv)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set 'Shorten join req intv' variable status\r\n");
  uint8_t param_valid = 0;
    char *p_char_identifier = strstr(pcInStr, "-");
    if (p_char_identifier)
    {
      p_char_identifier++;
      if(*p_char_identifier == '1')
      {
        param_valid = 1;
        PlatformStatus.b.SHORTEN_JOIN_REQ_INTV = 1;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Join request interval is shorten\r\n");
      }
      else if(*p_char_identifier == '0')
      {
        param_valid = 1;
        PlatformStatus.b.SHORTEN_JOIN_REQ_INTV = 0;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Join request interval is NOT shorten\r\n");
      }
    }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !joinreqintvshort-1 to shorten join req intv\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !joinreqintvshort-0 to disable 'shorten join req intv' param\r\n");
  }
  return RET_VAL_CLI;
}

/**
  * @brief Get LoRa ack variable status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetLoraAckEnabled)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Get LoRa ack variable status\r\n");
  if(PlatformStatus.b.LORA_ACK_ENABLED)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Parameter=1\r\n");
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Parameter=0\r\n");
  }
  
  return RET_VAL_CLI;
}

/**
  * @brief Set LoRa ack variable status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetLoraAckEnabled)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LoRa ack variable status\r\n");
  uint8_t param_valid = 0;
    char *p_char_identifier = strstr(pcInStr, "-");
    if (p_char_identifier)
    {
      p_char_identifier++;
      if(*p_char_identifier == '1')
      {
        param_valid = 1;
        PlatformStatus.b.LORA_ACK_ENABLED = 1;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LoRa ack variable is set\r\n");
      }
      else if(*p_char_identifier == '0')
      {
        param_valid = 1;
        PlatformStatus.b.LORA_ACK_ENABLED = 0;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LoRa ack variable is NOT set\r\n");
      }
    }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !loraack-1 to set LoRa ack variable\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !loraack-0 to unset LoRa ack variable\r\n");
  }
  return RET_VAL_CLI;
}

/**
  * @brief Get GnssAppConfig status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetGnssAppConfig)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Get GnssAppConfig status\r\n");
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "GnssAppConfig: GNSS_WAIT_FIX %d\r\n", PlatformStatus.b.GNSS_WAIT_FIX);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "GnssAppConfig: GNSS_FIX_CHECK %d\r\n", PlatformStatus.b.GNSS_FIX_CHECK);
  
  return RET_VAL_CLI;
}

/**
  * @brief Set GnssAppConfig status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetGnssAppConfig)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set GnssAppConfig status\r\n");
  
  uint8_t param1_valid = 0;
  uint8_t param2_valid = 0;
  uint8_t param1_value = 0;
  uint8_t param2_value = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param1_valid = 1;
      param1_value = 1;
    }
    else if(*p_char_identifier == '0')
    {
      param1_valid = 1;
      param1_value = 0;
    }
  }
  
  p_char_identifier = strstr(p_char_identifier+1, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param2_valid = 1;
      param2_value = 1;
    }
    else if(*p_char_identifier == '0')
    {
      param2_valid = 1;
      param2_value = 0;
    }
  }
  
  if(param1_valid == 1 && param2_valid == 1)
  {
    PlatformStatus.b.GNSS_WAIT_FIX = param1_value;
    PlatformStatus.b.GNSS_FIX_CHECK = param2_value;
    BSP_SavePlatformStatusToEeprom();
    if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
    }
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Params updated\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "GnssAppConfig: GNSS_WAIT_FIX %d (timeout)\r\n", PlatformStatus.b.GNSS_WAIT_FIX);
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "GnssAppConfig: GNSS_FIX_CHECK %d (infinite timeout)\r\n", PlatformStatus.b.GNSS_FIX_CHECK);
  }
  
  if(param1_valid == 0 || param2_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !gnssappconf-X-Y to config the gnss app layer\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "where X is the activation for WAIT FOR FIX (timeout)\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "and Y is the activation for WAIT FOR FIX (infinite timeout)\r\n");
  }
  return RET_VAL_CLI;
}


/**
  * @brief Set the system to go in low power on timer 
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetLpSleepTimer)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LpSleepTimer status\r\n");
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      PlatformStatus.b.LP_SLEEP_TIMER = 1;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LpSleepTimer: ON\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      PlatformStatus.b.LP_SLEEP_TIMER = 0;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LpSleepTimer: OFF\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !lpsleeptimer-1 to start the LpSleepTimer\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !lpsleeptimer-0 to stop the LpSleepTimer\r\n");
  }
  return RET_VAL_CLI;
}


/**
  * @brief Set the system to go in low power on sensor event (LIS2DW12 inactivity)
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetLpSensorEvent)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LpSensorEvent status\r\n");
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      PlatformStatus.b.LP_SENSOR_EVENT = 1;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LpSensorEvent: ON\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      PlatformStatus.b.LP_SENSOR_EVENT = 0;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LpSensorEvent: OFF\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !lpsensorevent-1 to activate the LpSensorEvent\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !lpsensorevent-0 to deactivate the LpSensorEvent\r\n");
  }
  return RET_VAL_CLI;
}


/**
  * @brief It enables/disables sending data after a the accelerometer wake-up 
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetSendOnWake)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set trigger to send data on sensor wakeup (on/off)\r\n");
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      PlatformStatus.b.SEND_ON_WAKE_EVENT = 1;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Trigger on wake: ON\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      PlatformStatus.b.SEND_ON_WAKE_EVENT = 0;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Trigger on wake: OFF\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !sendonwake-1 to set the trigger on wake\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !sendonwake-0 to unset the trigger on wake\r\n");
  }
  return RET_VAL_CLI;
}


/**
  * @brief It enables/disables sending data after a sensor threshold event
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetSendOnThreshold)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set trigger to send data on sensor threshold (on/off)\r\n");
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      PlatformStatus.b.SEND_ON_SENSOR_EVENT = 1;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Trigger on threshold: ON\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      PlatformStatus.b.SEND_ON_SENSOR_EVENT = 0;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Trigger on threshold: OFF\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !sendonthreshold-1 to set the trigger on threshold\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !sendonthreshold-0 to unset the trigger on threshold\r\n");
  }
  return RET_VAL_CLI;
}


/**
* @brief Set the system setting for LoRa ADR
* @param pcInStr pointer to input string
                                         * @retval None
*/
PROTO_FUNCTION_CLI(ProcDbgSetLoraADR)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LoRa ADR status\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Changes will take effect after restart\r\n");
  
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      PlatformStatus.s.LORA_ADR = 1;
      PlatformStatus.b.RESTART_PENDING = 1;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "ADR: ON\r\n");
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nRestart the device to activate news settings\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      PlatformStatus.s.LORA_ADR = 0;
      PlatformStatus.b.RESTART_PENDING = 1;
      BSP_SavePlatformStatusToEeprom();
      if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
      }
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "ADR: OFF\r\n");
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nRestart the device to activate news settings\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !loraadronoff-1 to set the ADR ON\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !loraadronoff-0 to set the ADR OFF\r\n");
  }
  return RET_VAL_CLI;
}


/**
  * @brief Set the system setting for lora send interval
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetSendInterval)
{
  char * p_char_identifier = 0;
  uint32_t nScOut;
  int nSendInterval;
  
  p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    nScOut = 0;
    nScOut = sscanf(p_char_identifier, "-%d",  &nSendInterval);
    if(nScOut==1)
    {
      if(nSendInterval > 10)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Send interval set to: %dms\r\n", nSendInterval);
        PlatformStatus.s.SEND_INTERVAL = nSendInterval;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
      }
      else
      {
        PRINTF("Send interval must be >%d\r\n", 10);
      }
    }
    else
    {
      PRINTF("Wrong command string format\r\n");
    }
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !lorainterval-NNN to set the LoRa send interval in ms\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "where NNN is the interval\r\n");
  }
}


/**
  * @brief Set the system setting for tx timer interval
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetTxTimerInterval)
{
  char * p_char_identifier = 0;
  uint32_t nScOut;
  int nTxTimerInterval;
  
  p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    nScOut = 0;
    nScOut = sscanf(p_char_identifier, "-%d",  &nTxTimerInterval);
    if(nScOut==1)
    {
      if(nTxTimerInterval > 10)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Tx timer interval set to: %dms\r\n", nTxTimerInterval);
        PlatformStatus.s.TX_TIMER_INTERVAL = nTxTimerInterval;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
      }
      else
      {
        PRINTF("Tx timer interval must be >%d\r\n", 10);
      }
    }
    else
    {
      PRINTF("Wrong command string format\r\n");
    }
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !txtimerintv-NNN to set the tx timer interval in ms\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "where NNN is the interval\r\n");
  }
}


/**
  * @brief Set the system setting for lora Data Rate
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetLoraDR)
{
  char * p_char_identifier = 0;
  uint32_t nScOut;
  int nLoraDR;
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LoRa Data Rate. See Region.h for details\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Changes will take effect after restart\r\n");
  
  p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    nScOut = 0;
    nScOut = sscanf(p_char_identifier, "-%d",  &nLoraDR);
    if(nScOut==1)
    {
      if(nLoraDR <= 13)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LoRa Data Rate set to: %d\r\n", nLoraDR);
        PlatformStatus.b.RESTART_PENDING = 1;
        PlatformStatus.s.LORA_DR = nLoraDR;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
      }
      else
      {
        PRINTF("LoRa Data Rate must be <=%d\r\n", 5);
      }
    }
    else
    {
      PRINTF("Wrong command string format\r\n");
    }
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !loradr-NNN to set the LoRa Data Rate\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "where NNN is the Data Rate (0-15)\r\n");
  }
}


/**
  * @brief It switches on or off the GNSS feeding line 
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgPowerGNSS)
{
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      BSP_PowerGNSS(ENABLE);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGNSS feeding line is switched on\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      BSP_PowerGNSS(DISABLE);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGNSS feeding line is switched off\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nThe command syntax is invalid\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !powergnss-1 to switch on the GNSS feeding line\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !powergnss-0 to switch off the GNSS feeding line\r\n");
  }  
  
  return RET_VAL_CLI;
}


/**
  * @brief It switches on or off the EEPROM feeding line 
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgPowerEEPROM)
{
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      BSP_PowerEEPROM(ENABLE);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nEEPROM feeding line is switched on\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      BSP_PowerEEPROM(DISABLE);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nEEPROM feeding line is switched off\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nThe command syntax is invalid\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !powereeprom-1 to switch on the EEPROM feeding line\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !powereeprom-0 to switch off the EEPROM feeding line\r\n");
  }  
  
  return RET_VAL_CLI;  
}


/**
  * @brief It switches on or off the Type-C controller feeding line 
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgPowerTCCtrl)
{
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      BSP_PowerTypeCCtrl(ENABLE);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nType-C controller feeding line is switched on\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      BSP_PowerTypeCCtrl(DISABLE);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nType-C controller feeding line is switched off\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nThe command syntax is invalid\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !powertcctrl-1 to switch on the Type-C controller feeding line\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !powertcctrl-0 to switch off the Type-C controller feeding line\r\n");
  }  
  
  return RET_VAL_CLI;    
}


/**
  * @brief It switches on or off the sensors feeding line 
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgPowerSens)
{
  uint8_t param_valid = 0;
  char *p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == '1')
    {
      param_valid = 1;
      BSP_PowerSensors(ENABLE);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nSensors feeding line is switched on\r\n");
    }
    else if(*p_char_identifier == '0')
    {
      param_valid = 1;
      BSP_PowerSensors(DISABLE);
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nSensors feeding line is switched off\r\n");
    }
  }
  if(param_valid == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nThe command syntax is invalid\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !powersens-1 to switch on the Sensors feeding line\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !powersens-0 to switch off the Sensors feeding line\r\n");
  }  
  
  return RET_VAL_CLI;    
}

/**
  * @brief Get debug mode
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetDebugMode)
{
  if (PlatformStatus.b.USB_DBG)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nDebug over USB is enabled\r\n");      
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nDebug over USB is disabled\r\n");      
  }

  return RET_VAL_CLI;
}


/**
  * @brief Set debug mode
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetDebugMode)
{
  char * p_char_mode = 0;
  uint8_t bDebugChange = 0;
  
  p_char_mode = strstr(pcInStr, "S");
  
  if (p_char_mode)
  {
    if ((((*(p_char_mode+1)) == 'e') || (*(p_char_mode+1)) == 'E'))
    {
      bDebugChange = 1;
      PlatformStatus.b.USB_DBG = ENABLE;
      PlatformStatus.b.USB_TRACE = ENABLE;
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nDebug over USB is enabled\r\n");      
      
    }
    else if ((((*(p_char_mode+1)) == 'd') || (*(p_char_mode+1)) == 'D'))
    {
      bDebugChange = 1;
      PlatformStatus.b.USB_DBG = DISABLE;
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nDebug over USB is disabled\r\n");      
    }
  }
  
  if(bDebugChange==0)
  {      
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nUse the command !debugmodeSs\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "by replacing s with e (enable) or d (disable)\r\n");
  }  
  
  return RET_VAL_CLI;
}


/**
  * @brief Get LoRa device status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetDeviceStatus)
{
  LoraFlagStatus lora_join_status;
  
  lora_join_status = LORA_JoinStatus();
  if( lora_join_status == LORA_SET )
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nLoRa has joined\r\n");
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nLoRa has not joined\r\n");
  }

  return RET_VAL_CLI;
}


/**
  * @brief Get LoRa device join parameters
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetLoRaJoinParameters)
{
  extern uint8_t DevEui[];
  extern uint8_t JoinEui[];
  extern uint8_t AppKey[];
  extern uint8_t NwkKey[];
  uint8_t McuIdDevEui[8];
  HW_GetUniqueId(McuIdDevEui);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nDevEui(FromMcuId) = %02X %02X %02X %02X %02X %02X %02X %02X", HEX8(McuIdDevEui));
  
#if( OVER_THE_AIR_ACTIVATION != 0 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nApplication uses the Over-the-Air activation procedure.");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nActive keys:");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nDevEui = %02X %02X %02X %02X %02X %02X %02X %02X", HEX8(DevEui));
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nJoinEui = %02X %02X %02X %02X %02X %02X %02X %02X", HEX8(JoinEui));
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nAppKey = %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", HEX16(AppKey));
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nNwkKey = %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\r\n", HEX16(NwkKey));
  
  uint8_t EepromKeysCheck = EepromLoraKeysValidation();
  if(EepromKeysCheck != 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nEEPROM keys NOT used:\r\n");
    if(EepromKeysCheck & DEVICE_EUI_EEPROM_ID)
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "deveui missing\r\n");
    }
    if(EepromKeysCheck & JOIN_EUI_EEPROM_ID)
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "joineui missing\r\n");
    }
    if(EepromKeysCheck & APP_KEY_EEPROM_ID)
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "appkey missing\r\n");
    }
    if(EepromKeysCheck & NWK_KEY_EEPROM_ID)
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "nwkkey missing\r\n");
    }
  }
  
  void LoraGetInitParams(LoRaParam_t **LoRaParamInit);
  LoRaParam_t *LoRa_Param_Init;
  LoraGetInitParams(&LoRa_Param_Init);
  int32_t TxDatarate = LoRa_Param_Init->TxDatarate;
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nADR: %s, DATA RATE: DR_%d, PUBLIC NETWORK: %s\r\n", (LoRa_Param_Init->AdrEnable)?"Y":"N", TxDatarate, (LoRa_Param_Init->EnablePublicNetwork)?"Y":"N");
#else //( OVER_THE_AIR_ACTIVATION != 0 )
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nApplication uses the Personalization activation procedure");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nCheck ABP params in Commissioning.h\r\n");
#endif //( OVER_THE_AIR_ACTIVATION != 0 )
  
  return RET_VAL_CLI;
}


/**
  * @brief Set LoRa device EUI
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetDeviceEUI)
{
  char * p_char_identifier = 0;
  uint8_t temp_deveui[8] = {0};
  bool deveui_updated = false;
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LoRa device EUI\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Changes will take effect after restart\r\n");
  
  if (strlen(pcInStr)!= 27)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nCommand length is not compliant\r\n");
  }
  else
  {  
    p_char_identifier = strstr(pcInStr, "-");
    
    if (p_char_identifier)
    {
      deveui_updated = true;
      for (uint8_t i=0; i<8; i++)
      {
        if (isxdigit(*(p_char_identifier + 1 + (2*i))) && isxdigit(*(p_char_identifier + 2 + (2*i))))
        {
          temp_deveui[i] |= xdigit(*(p_char_identifier + 1 + (2*i)));
          temp_deveui[i] = (temp_deveui[i] << 4);
          temp_deveui[i] |= xdigit(*(p_char_identifier + 2 + (2*i)));
        }
        else
        {
          deveui_updated = false;
        }
      }
      
      if (deveui_updated)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nNew device EUI is %02X %02X %02X %02X %02X %02X %02X %02X\r\n", HEX8(temp_deveui));
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nRestart the device to activate news keys\r\n");
        PlatformStatus.b.RESTART_PENDING = 1;
#ifdef SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
        WriteInternalEepromBuffer(DEVICE_EUI_EEPROM_ADDRESS, DEVICE_EUI_EEPROM_LEN, temp_deveui);
#endif //SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
      }
    }
  }
  
  if(deveui_updated == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nUse the command !deviceeui-xxxxxxxxxxxxxxxx\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "by replacing xxxxxxxxxxxxxxxx with the device EUI\r\n");
  }  
  
  return RET_VAL_CLI;
}


/**
  * @brief Set LoRa join EUI
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetJoinEUI)
{
  char * p_char_identifier = 0;
  uint8_t temp_joineui[8] = {0};
  bool joineui_updated = false;

  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LoRa Join EUI\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Changes will take effect after restart\r\n");
  
  /* Check that the command length is compliant */
  if (strlen(pcInStr)!= 25)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nCommand length is not compliant\r\n");
  }
  else
  {  
    p_char_identifier = strstr(pcInStr, "-");
    
    if (p_char_identifier)
    {
      joineui_updated = true;
      for (uint8_t i=0; i<8; i++)
      {
        if (isxdigit(*(p_char_identifier + 1 + (2*i))) && isxdigit(*(p_char_identifier + 2 + (2*i))))
        {
          temp_joineui[i] |= xdigit(*(p_char_identifier + 1 + (2*i)));
          temp_joineui[i] = (temp_joineui[i] << 4);
          temp_joineui[i] |= xdigit(*(p_char_identifier + 2 + (2*i)));
        }
        else
        {
          joineui_updated = false;
        }
      }
      
      if (joineui_updated)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nNew join EUI is %02X %02X %02X %02X %02X %02X %02X %02X\r\n", HEX8(temp_joineui));
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nRestart the device to activate news keys\r\n");
        PlatformStatus.b.RESTART_PENDING = 1;
#ifdef SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
        WriteInternalEepromBuffer(JOIN_EUI_EEPROM_ADDRESS, JOIN_EUI_EEPROM_LEN, temp_joineui);
#endif //SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
      }
    }
  }
  
  if(joineui_updated == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nUse the command !joineui-xxxxxxxxxxxxxxxx\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "by replacing xxxxxxxxxxxxxxxx with the join EUI\r\n");
  }
  
  return RET_VAL_CLI;
}


/**
  * @brief Set LoRa application key
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetApplicationKey)
{
  char * p_char_identifier = 0;
  uint8_t temp_appkey[16] = {0};
  bool appkey_updated = false;

  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LoRa Application key\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Changes will take effect after restart\r\n");
  
  /* Check that the command length is compliant */
  if (strlen(pcInStr)!= 40)
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nCommand length is not compliant\r\n");
  else
  {
    p_char_identifier = strstr(pcInStr, "-");
    
    if (p_char_identifier)
    {
      appkey_updated = true;
      for (uint8_t i=0; i<16; i++)
      {
        if (isxdigit(*(p_char_identifier + 1 + (2*i))) && isxdigit(*(p_char_identifier + 2 + (2*i))))
        {
          temp_appkey[i] |= xdigit(*(p_char_identifier + 1 + (2*i)));
          temp_appkey[i] = (temp_appkey[i] << 4);
          temp_appkey[i] |= xdigit(*(p_char_identifier + 2 + (2*i)));
        }
        else
        {
          appkey_updated = false;
        }
      }
    }
    if (appkey_updated)
    {
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nNew AppKey = %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", HEX16(temp_appkey));
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nRestart the device to activate news keys\r\n");
      PlatformStatus.b.RESTART_PENDING = 1;
#ifdef SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
      WriteInternalEepromBuffer(APP_KEY_EEPROM_ADDRESS, APP_KEY_EEPROM_LEN, temp_appkey);
#endif //SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
    }
  }
  
  if (appkey_updated == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nUse the command !appkey-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "by replacing xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx with the application key\r\n");
  }

  return RET_VAL_CLI;
}

/**
  * @brief Set LoRa network key
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetNetworkKey)
{
  char * p_char_identifier = 0;
  uint8_t temp_nwkkey[16] = {0};
  bool nwkkey_updated = false;

  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Set LoRa network key\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Changes will take effect after restart\r\n");
  
  /* Check that the command length is compliant */
  if (strlen(pcInStr)!= 41)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nCommand length is not compliant\r\n");
  }
  else
  {
    p_char_identifier = strstr(pcInStr, "-");
    
    if (p_char_identifier)
    {
      nwkkey_updated = true;
      for (uint8_t i=0; i<16; i++)
      {
        if (isxdigit(*(p_char_identifier + 1 + (2*i))) && isxdigit(*(p_char_identifier + 2 + (2*i))))
        {
          temp_nwkkey[i] |= xdigit(*(p_char_identifier + 1 + (2*i)));
          temp_nwkkey[i] = (temp_nwkkey[i] << 4);
          temp_nwkkey[i] |= xdigit(*(p_char_identifier + 2 + (2*i)));
        }
        else
        {
          nwkkey_updated = false;
        }
      }
      
      if (nwkkey_updated)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nNew NwkKey = %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X", HEX16(temp_nwkkey));
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nRestart the device to activate news keys\r\n");
        PlatformStatus.b.RESTART_PENDING = 1;
#ifdef SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
        WriteInternalEepromBuffer(NWK_KEY_EEPROM_ADDRESS, NWK_KEY_EEPROM_LEN, temp_nwkkey);
#endif //SAVE_LORA_KEYS_IN_INTERNAL_EEPROM
      }
    }  
  }
  
  if(nwkkey_updated == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nUse the command !ntwkkey-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "by replacing xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx with the network key\r\n");
  }
  
  return RET_VAL_CLI;
}

/**
  * @brief Erase LoRa keys
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgEraseLoraKeys)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Erase LoRa keys...\r\n");
  uint8_t temp_lorakey[16] = {0};
  WriteInternalEepromBuffer(DEVICE_EUI_EEPROM_ADDRESS, DEVICE_EUI_EEPROM_LEN, temp_lorakey);
  WriteInternalEepromBuffer(JOIN_EUI_EEPROM_ADDRESS, JOIN_EUI_EEPROM_LEN, temp_lorakey);
  WriteInternalEepromBuffer(APP_KEY_EEPROM_ADDRESS, APP_KEY_EEPROM_LEN, temp_lorakey);
  WriteInternalEepromBuffer(NWK_KEY_EEPROM_ADDRESS, NWK_KEY_EEPROM_LEN, temp_lorakey);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "LoRa keys erased\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nLoad the news keys and restart the device\r\n");
  PlatformStatus.b.RESTART_PENDING = 1;
}

/**
  * @brief Trigger LoRa sending
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgTriggerLoRaSending)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nA sensor read and LoRa sending was triggered\r\n");
  PlatformStatus.s.xNextState = State_Read;

  return RET_VAL_CLI;
}

/**
  * @brief Set system state to run
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSystemStateRun)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nSet system state to run\r\n");
  PlatformStatus.s.xNextState = State_Run;

  return RET_VAL_CLI;
}

/**
  * @brief Set system state to Low Power
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSystemStateLowPower)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nSet system state to Low Power\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nDelay 5 seconds to disconnect USB cable\r\n");
  HAL_Delay(5000);
  PlatformStatus.s.xNextState = State_PrepareLowPower;

  return RET_VAL_CLI;
}

/**
  * @brief Set system state to Ultra Low Power
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSystemStateUltraLowPower)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nSet system state to Ultra Low Power\r\n");
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nDelay 5 seconds to disconnect USB cable\r\n");
  HAL_Delay(5000);
  PlatformStatus.s.xNextState = State_PrepareUltraLowPower;

  return RET_VAL_CLI;
}

/**
  * @brief Read accelerometer
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetSensorData)
{
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGet accelerometer data\r\n");
  BSP_sensor_Enable();
  BSP_accelero_Enable();
  
  BSP_sensor_Read( &sensor_data );
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Got sensor data: T: %.2f H: %.2f P: %.2f\r\n", sensor_data.temperature, sensor_data.humidity, sensor_data.pressure );
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Accelerometer: X: %d Y: %d Z: %d\r\n", sensor_data.acceleration_x, sensor_data.acceleration_y, sensor_data.acceleration_z );
}

/**
  * @brief GPS cold start
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetColdStart)
{
  void TeseoSendColdStart (void);
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nSend GPS cold start cmd to TESEO\r\n");
  TeseoSendColdStart();

  return RET_VAL_CLI;
}


/**
  * @brief Get the GPS position
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetGPSPosition)
{
  int32_t nLatitude, nLongitude, nAltitudeGps;
  uint8_t bFixValidity;
  void GetTeseoData (int32_t* pnLatitude, int32_t* pnLongitude , int32_t* pnAltitudeGps, uint8_t *bFixValidity);

  GetTeseoData (&nLatitude, &nLongitude , &nAltitudeGps, &bFixValidity);
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGPS coordinates: Latitude %f, Longitude %f, Altitude %f\r\n", (float)nLatitude/10000.0, (float)nLongitude/10000.0, (float)nAltitudeGps/100.0);

  return RET_VAL_CLI;
}

/**
  * @brief Set the GPS position
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgSetGeoFence)
{
  extern uint8_t bSendCommandGeofenceCfg;
  uint8_t temp_send_geofence_cfg = 0;
  uint8_t params_ok = 1;
  char * p_char_identifier = 0;
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGNSS geofence command\r\n");
  
  p_char_identifier = strstr(pcInStr, "-");
  if (p_char_identifier)
  {
    p_char_identifier++;
    if(*p_char_identifier == 'X')
    {
      temp_send_geofence_cfg = 1;
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nCancel geofence\r\n");
    }
    else if(*p_char_identifier == 'H')
    {
      temp_send_geofence_cfg = 7;
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence on current coords\r\n");
    }
    else if(*p_char_identifier == 'C')
    {
      temp_send_geofence_cfg = 6;
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence on ST Catania\r\n");
    }
    else if(*p_char_identifier == 'L')
    {
      temp_send_geofence_cfg = 5;
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence on ST Lecce\r\n");
    }
    else
    {
      params_ok = 0;
      DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nWrong param 1\r\n");
    }
    
    if(params_ok == 1)
    {
      if(temp_send_geofence_cfg == 1)
      {
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Cancel geofence\r\n");
        bSendCommandGeofenceCfg = temp_send_geofence_cfg;
        PlatformStatus.s.xNextState = State_Run;
        PlatformStatus.b.RESTART_PENDING = 1;
        BSP_SavePlatformStatusToEeprom();
        if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
        {
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
        }
        DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Wait confirmation for geofence activation before restart\r\n");
        int32_t nLatitude, nLongitude, nAltitudeGps;
        uint8_t bFixValidity;
        void GetTeseoData (int32_t* pnLatitude, int32_t* pnLongitude , int32_t* pnAltitudeGps, uint8_t *bFixValidity);
        
        GetTeseoData (&nLatitude, &nLongitude , &nAltitudeGps, &bFixValidity);
      }
      else
      {
        p_char_identifier = strstr(p_char_identifier+1, "-");
        if (p_char_identifier)
        {
          uint32_t nScOut = 0;
          int nRadius = 0;
          nScOut = sscanf(p_char_identifier, "-%d",  &nRadius);
          if(nScOut==1)
          {
            if(temp_send_geofence_cfg == 7)
            {
              int32_t nLatitude, nLongitude, nAltitudeGps;
              uint8_t bFixValidity;
              void GetTeseoData (int32_t* pnLatitude, int32_t* pnLongitude , int32_t* pnAltitudeGps, uint8_t *bFixValidity);
              
              GetTeseoData (&nLatitude, &nLongitude , &nAltitudeGps, &bFixValidity);
              
              if(bFixValidity)
              {
                DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Fix valid, using current coords\r\n");
              }
              else
              {
                DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Fix not valid, using old coords\r\n");
              }
              
              PlatformStatus.s.GNSS_GEOFENCE_LAT = (float)nLatitude / 10000.0;
              PlatformStatus.s.GNSS_GEOFENCE_LON = (float)nLongitude / 10000.0;
              DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Geofence settings (R=%d) coords: %f, %f\r\n", 
                                  (int32_t)nRadius, 
                                  PlatformStatus.s.GNSS_GEOFENCE_LAT, 
                                  PlatformStatus.s.GNSS_GEOFENCE_LON);
            }
            PlatformStatus.s.GNSS_GEOFENCE_RADIUS = nRadius;
            bSendCommandGeofenceCfg = temp_send_geofence_cfg;
            PlatformStatus.s.xNextState = State_Run;
            PlatformStatus.b.RESTART_PENDING = 1;
            BSP_SavePlatformStatusToEeprom();
            if(PlatformStatus.b.EEPROM_DATA_CAN_BE_CHANGED == 0)
            {
              DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "EEPROM settings are not in use, make sure you set USE_EEPROM_SETTINGS define to 1\r\n");
            }
            DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Wait confirmation for geofence activation before restart\r\n");
            int32_t nLatitude, nLongitude, nAltitudeGps;
            uint8_t bFixValidity;
            void GetTeseoData (int32_t* pnLatitude, int32_t* pnLongitude , int32_t* pnAltitudeGps, uint8_t *bFixValidity);
            
            GetTeseoData (&nLatitude, &nLongitude , &nAltitudeGps, &bFixValidity);
          }
          else
          {
            params_ok = 0;
            DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nWrong param 2\r\n");
          }
        }
        else
        {
          params_ok = 0;
          DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nWrong command string format\r\n");
        }
      }
    }
  }
  if(params_ok == 0)
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !geofence-X to stop geofence\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !geofence-H-NNNN to config geofence HERE (current coords)\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !geofence-C-NNNN to config geofence on ST-Catania coords\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "Use: !geofence-L-NNNN to config geofence on ST-Lecce coords\r\n");
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "where NNNN is the radius for geofence configuration\r\n");
  }
  return RET_VAL_CLI;
}

/**
  * @brief Get GPS geofence status
  * @param pcInStr pointer to input string
  * @retval None
  */
PROTO_FUNCTION_CLI(ProcDbgGetGeoFence)
{
  extern uint8_t bSendCommandGeofenceReq;
  bSendCommandGeofenceReq = 1;
  uint8_t bGeofenceActive=0;
  
  DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGet GPS geofence status\r\n");
  
  if(PlatformStatus.s.GNSS_GEOFENCE_MASK & (1<<GEOFENCE_LECCE))
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence on ST Lecce\r\n");
    bGeofenceActive = 1;
  }
  else if(PlatformStatus.s.GNSS_GEOFENCE_MASK & (1<<GEOFENCE_CATANIA))
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence on ST Catania\r\n");
    bGeofenceActive = 1;
  }
  else if(PlatformStatus.s.GNSS_GEOFENCE_MASK & (1<<GEOFENCE_CUR_COORDS))
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence on current coords\r\n");
    bGeofenceActive = 1;
  }
  else
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence not active\r\n");
  }
  
  if( bGeofenceActive )
  {
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence radius: %d\r\n", PlatformStatus.s.GNSS_GEOFENCE_RADIUS);
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence Latitude: %f\r\n", ABS(PlatformStatus.s.GNSS_GEOFENCE_LAT), LAT_NORD_SUD(PlatformStatus.s.GNSS_GEOFENCE_LAT));
    DBG_PRINTF_TERMINAL(TERMINAL_DEBUG_SEVERITY, "\r\nGeofence Longitude: %f\r\n", ABS(PlatformStatus.s.GNSS_GEOFENCE_LON), LON_EAST_WEST(PlatformStatus.s.GNSS_GEOFENCE_LON));
    int32_t nLatitude, nLongitude, nAltitudeGps;
    uint8_t bFixValidity;
    void GetTeseoData (int32_t* pnLatitude, int32_t* pnLongitude , int32_t* pnAltitudeGps, uint8_t *bFixValidity);
    
    GetTeseoData (&nLatitude, &nLongitude , &nAltitudeGps, &bFixValidity);
  }
  
  return RET_VAL_CLI;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
