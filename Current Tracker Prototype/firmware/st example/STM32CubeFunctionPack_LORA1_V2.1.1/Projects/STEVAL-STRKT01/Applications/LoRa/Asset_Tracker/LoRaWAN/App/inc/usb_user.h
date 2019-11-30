/**
  **************************************************************************************************
  * @file    usb_user.h
  * @author  SRA - System Lab - Sensing & Connectivity Application Team
  * @version V2.1.1
  * @date    10-Oct-2019
  * @brief   This file contains definitions for the usb_user.c file
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
  * @brief USB application files
  * @{
  */ 

/** @defgroup STEVAL-STRKT01_APP_USB_USER USB USER
  * @brief Set of user functions to manage USB peripheral 
  * @{
  */  


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_USER_H__
#define __USB_USER_H__

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#ifdef USB_ENABLED
#undef MIN /* to avoid redefinition warning */
#undef MAX /* to avoid redefinition warning */
#include "usbd_cdc_if.h"
#endif //USB_ENABLED
#include "vcom.h"


/** @defgroup STEVAL-STRKT01_APP_USB_USER_Private_Defines USB USER Private Definitions
  * @brief Private definitions
  * @{
 */   

/* Private define ------------------------------------------------------------*/
   
#define countof(A)             (sizeof(A)/sizeof(*A))                                                          //!< countof UTILITY    
#define in_range(c, lo, up)    ((uint8_t)c >= lo && (uint8_t)c <= up)                                          //!< in_range UTILITY   
#define isdigit(c)             in_range(c, '0', '9')                                                           //!< isdigit UTILITY    
#define digit(c)               (c - '0')                                                                       //!< digit UTILITY      
#define xdigit(c)              isdigit(c)?digit(c):in_range(c, 'a', 'f')?(10+c-'a'):(10+c-'A')                 //!< xdigit UTILITY     
#define isxdigit(c)            (isdigit(c) || in_range(c, 'a', 'f') || in_range(c, 'A', 'F'))                  //!< isxdigit UTILITY   
#define islower(c)             in_range(c, 'a', 'z')                                                           //!< islower UTILITY                                
#define isupper(c)             in_range(c, 'A', 'Z')                                                           //!< isupper UTILITY    
#define ischar(c)              (islower(c) || isupper(c))                                                      //!< ischar UTILITY     
#define isprint(c)             in_range(c, 0x20, 0x7f)                                                         //!< isprint UTILITY    
#define isspace(c)             (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')     //!< isspace UTILITY    
#define isEOL(c)               (c == '\r' || c == '\n')                                                        //!< isEOL UTILITY      
#define isNULL(c)              (c == '\0')                                                                     //!< isNULL UTILITY     
#define isescape(c)            (c == 0x1B)                                                                     //!< isescape UTILITY      
   
  /* Add your own PRINTF implementation */
//#define PRINTF(...)            do{DBG_PRINTF_LOG(L, __VA_ARGS__);extern uint8_t bDebuggerConnected; if(bDebuggerConnected)printf(__VA_ARGS__);}while(0) 

/**
  * @}
  */   
  
/** @defgroup STEVAL-STRKT01_APP_USB_USER_Private_TypesDefinitions USB USER Private Types Definitions
  * @brief Private types definitions
  * @{
 */

/* Private typedef -----------------------------------------------------------*/

/** 
  * @brief Command handler function typedef
  */
typedef void (*pCmdHandlerFunc_t)(char *pcInStr);

#ifdef COMMAND_INTERPRETER_H
  #define xCmdStruct_t                                    CLI_Command_Definition_t
  #define PROTO_FUNCTION_CLI(F)                           BaseType_t F(char *pcInStr, size_t len, const char *pcCommandString )
  #define RET_VAL_CLI                                     0
  #define CALL_CLI_FUNCTION(F)                                  F("", 0, "");
#else //COMMAND_INTERPRETER_H
  typedef long BaseType_t;
  typedef unsigned long UBaseType_t;
  /**
    * @brief Command handler descriptor
    */
  typedef struct s_cmd_struct {
    char cCmdString[20];                          //!< Command string
    char cCmdHelp[50];                            //!< Command help string
    pCmdHandlerFunc_t pCmdHandlerFunc;            //!< Command function pointer
    uint8_t bShowInHelp;                          //!< To show the function with '?' command
  } xCmdStruct_t;

  
  typedef struct LogData_s {
  uint32_t AccEnable;
  uint32_t temperature;
  uint32_t pressure;
  uint32_t humidity;
  int32_t latitude;
  int32_t longitude;
  int32_t altitudeGps;
  uint32_t epoch_value;
  int32_t accelero_x;
  int32_t accelero_y;
  int32_t accelero_z;
  uint32_t batteryLevel;
  uint8_t sentFlag;
} LogData_t;

/*
 * Prototype definition for command line interface
 */
  #define PROTO_FUNCTION_CLI(F)                           void F(char *pcInStr)

/*
 * Return value definition for command line interface
 */
  #define RET_VAL_CLI                                     

/*
 * Function caller for command line interface
 */
  #define CALL_CLI_FUNCTION(F)                                  F("");

#endif //COMMAND_INTERPRETER_H

/**
  * @}
  */

  
/** @defgroup STEVAL-STRKT01_APP_USB_USER_Public_Functions USB USER Public Functions
  * @brief Public functions
  * @{
 */

/* Public functions ----------------------------------------------------------*/
  

  
void ProcessTerminalString(void);
uint8_t DBG_PRINTF_LOG(uint8_t Q, uint16_t L, const char* sFormatString, ...);
uint8_t DBG_PRINTF_LOG_SAFE(uint16_t L, const char* sFormatString, ...);
void USB_User_StoreCommand(uint8_t* pBuf, uint32_t *Len);
void FlushSafePrintf(void);

/**
  * @}
  */


/** @defgroup STEVAL-STRKT01_APP_USB_USER_Private_FunctionPrototypes USB USER Private Function Prototypes
  * @brief Private function prototypes
  * @{
 */

/* Private function prototypes -----------------------------------------------*/

PROTO_FUNCTION_CLI(ProcDbgHelp);
PROTO_FUNCTION_CLI(ProcDbgGetFwVersion);
PROTO_FUNCTION_CLI(ProcDbgGetMcuId);
PROTO_FUNCTION_CLI(ProcDbgSysReset);
PROTO_FUNCTION_CLI(ProcDbgSysShutdown);
PROTO_FUNCTION_CLI(ProcDbgWelcomeMessage);
PROTO_FUNCTION_CLI(ProcDbgRestoreSettings);
PROTO_FUNCTION_CLI(ProcDbgGetPlatformStatus);
PROTO_FUNCTION_CLI(ProcDbgPushLog);
PROTO_FUNCTION_CLI(ProcDbgFormateeprom);
PROTO_FUNCTION_CLI(ProcDbgGetLogs);
PROTO_FUNCTION_CLI(ProcDbgGetUnsentLogs);
PROTO_FUNCTION_CLI(ProcDbgGetSingleItem);
PROTO_FUNCTION_CLI(ProcDbgGetLogmanager);
PROTO_FUNCTION_CLI(ProcDbgSetLogmanager);
PROTO_FUNCTION_CLI(ProcDbgGetGnssAppConfig);
PROTO_FUNCTION_CLI(ProcDbgSetGnssAppConfig);
PROTO_FUNCTION_CLI(ProcDbgSetLpSleepTimer);
PROTO_FUNCTION_CLI(ProcDbgSetSendOnWake);
PROTO_FUNCTION_CLI(ProcDbgSetSendOnThreshold);
PROTO_FUNCTION_CLI(ProcDbgSetLpSensorEvent);
PROTO_FUNCTION_CLI(ProcDbgSetLoraADR);
PROTO_FUNCTION_CLI(ProcDbgSetSendInterval);
PROTO_FUNCTION_CLI(ProcDbgSetTxTimerInterval);
PROTO_FUNCTION_CLI(ProcDbgSetLoraDR);
PROTO_FUNCTION_CLI(ProcDbgGetLoraAckEnabled);
PROTO_FUNCTION_CLI(ProcDbgSetLoraAckEnabled);
PROTO_FUNCTION_CLI(ProcDbgPowerGNSS);
PROTO_FUNCTION_CLI(ProcDbgPowerEEPROM);
PROTO_FUNCTION_CLI(ProcDbgPowerTCCtrl);
PROTO_FUNCTION_CLI(ProcDbgPowerSens);
PROTO_FUNCTION_CLI(ProcDbgGetDebugMode);
PROTO_FUNCTION_CLI(ProcDbgSetDebugMode);
PROTO_FUNCTION_CLI(ProcDbgGetDeviceStatus);
PROTO_FUNCTION_CLI(ProcDbgGetLoRaJoinParameters);
PROTO_FUNCTION_CLI(ProcDbgSetDeviceEUI);
PROTO_FUNCTION_CLI(ProcDbgSetJoinEUI);
PROTO_FUNCTION_CLI(ProcDbgSetApplicationKey);
PROTO_FUNCTION_CLI(ProcDbgSetNetworkKey);
PROTO_FUNCTION_CLI(ProcDbgEraseLoraKeys);
PROTO_FUNCTION_CLI(ProcDbgTriggerLoRaSending);
PROTO_FUNCTION_CLI(ProcDbgGetIncludeEpochTime);
PROTO_FUNCTION_CLI(ProcDbgSetIncludeEpochTime);
PROTO_FUNCTION_CLI(ProcDbgGetShortenJoinReqIntv);
PROTO_FUNCTION_CLI(ProcDbgSetShortenJoinReqIntv);
PROTO_FUNCTION_CLI(ProcDbgSystemStateRun);
PROTO_FUNCTION_CLI(ProcDbgSetColdStart);
PROTO_FUNCTION_CLI(ProcDbgGetGPSPosition);
PROTO_FUNCTION_CLI(ProcDbgSetGeoFence);
PROTO_FUNCTION_CLI(ProcDbgGetGeoFence);
PROTO_FUNCTION_CLI(ProcDbgSystemStateLowPower);
PROTO_FUNCTION_CLI(ProcDbgSystemStateUltraLowPower);
PROTO_FUNCTION_CLI(ProcDbgGetSensorData);
                   
#ifdef USB_ENABLED

USBD_StatusTypeDef USB_User_SendWelcomeMessage(void);
USBD_StatusTypeDef USB_User_SendMessage(uint8_t* pBuf, uint16_t Lenght, uint32_t AttemptsNumber);

#endif //USB_ENABLED

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USB_USER_H__ */

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

