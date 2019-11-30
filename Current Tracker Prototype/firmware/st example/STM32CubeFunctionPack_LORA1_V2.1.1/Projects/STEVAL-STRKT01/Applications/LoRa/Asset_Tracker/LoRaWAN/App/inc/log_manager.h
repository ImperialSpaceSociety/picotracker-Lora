/**
 ******************************************************************************
 * @file    log_manager.h
 * @author  System Lab - System development
 * @version V1.0.0
 * @date    November-2018
 * @brief   This header file contains the functions prototypes common for logging
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
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
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOG_MANAGER_H
#define __LOG_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "hw.h"

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

/** @defgroup STEVAL-STRKT01_LogManager LogManager
  * @brief Log events manager
 * @{
 */
  
/** @addtogroup STEVAL-STRKT01_LogManager_Public_Defines LogManager Public Definitions
  * @brief Public definitions
  * @{
 */
#define LOG_EV_HEADER_SIZE              ((uint8_t)sizeof(LogEvent_Header_t))
#define LOG_EV_NRM_ITEM_SIZE            64u
#define LOG_EV_SYS_ITEM_SIZE            16u
#define LOG_EV_CRT_ITEM_SIZE            16u
#define LOG_EV_MAX_PAYLOAD_SIZE         ((uint8_t)(LOG_EV_NRM_ITEM_SIZE - LOG_EV_HEADER_SIZE)) /* the bigger */
#define LOG_EV_PAYLOAD_SIZE(_Type_)     ((uint8_t)(LOG_EV_SIZE(_Type_) - LOG_EV_HEADER_SIZE))

#define LOG_EV_COUNT_EMPTY              0xFFFF
#define LOG_EV_COUNT_DEAD               0xDEAD
#define LOG_EV_TIMESTAMP_EMPTY          0xFFFFFFFF
#define LOG_EV_CRC_EMPTY                0xFF
#define LOG_EV_CRC_ERROR                0xFFFFFFFF
#define LOG_EV_TIMESTAMP_DONTCARE       0xA5A5A5A5
#define LOG_EV_TYPE_NUM                 3u
#define LOG_EV_TYPE_IS_VALID(_Type_)    ((LOG_EV_NRM == (_Type_)) || (LOG_EV_SYS == (_Type_)) || (LOG_EV_CRT == (_Type_)))

#define LOG_EV_CONF(_Type_, _Field_)    (((LogEvent_Conf_t *)(&LogEvent_Conf[(uint8_t)_Type_]))->_Field_)

/**
  * @}
  */

/** @addtogroup STEVAL-STRKT01_LogManager_Public_TypesDefinitions LogManager Public Types Definitions
  * @brief Public types definitions
  * @{
 */
typedef enum
{
  TEST_OK = 0,
  TEST_SKP = 1,
  TEST_ERR = 2,
} TestResTypeDef;

typedef enum
{
  LOG_EV_NRM = 0,
  LOG_EV_SYS = 1,
  LOG_EV_CRT = 2,
  LOG_EV_NAN = 0xFF,
} LogEvent_Type_t;

typedef struct LogEvent_Conf_s {
  uint16_t ItemSize;
  uint16_t ItemPayloadSize;
  uint16_t ItemNum;
  uint16_t ItemNumXPage;
  uint16_t ItemNumTotal;
  uint16_t PageStart;
  uint16_t PageEnd;
  uint32_t AddressBase;
  uint8_t  Name[8];
} LogEvent_Conf_t;

typedef struct
{
  uint16_t Count;
  LogEvent_Type_t Type;
  uint8_t Crc;
  uint32_t TimeStamp; /* sec */
} LogEvent_Header_t;

typedef struct
{
  LogEvent_Header_t Header;
  uint8_t Payload[LOG_EV_MAX_PAYLOAD_SIZE];
} LogEvent_Item_t;

/**
  * @}
  */

extern const LogEvent_Conf_t LogEvent_Conf[LOG_EV_TYPE_NUM];

/** @addtogroup STEVAL-STRKT01_LogManager_Public_FunctionPrototypes LogManager Public Function Prototypes
  * @brief Public functions prototypes
  * @{
 */
int8_t LogEvent_Push_Printf(LogEvent_Type_t Type, char const *sFormatString, ...);
ErrorStatus LogEvent_Push(LogEvent_Type_t Type, LogEvent_Item_t *pLogItem);
ErrorStatus LogEvent_UpdateItem(LogEvent_Item_t *pLogItem);
ErrorStatus LogEvent_Get(LogEvent_Item_t *pLogItem, LogEvent_Type_t Type, uint16_t Count, uint8_t bReqPos);
ErrorStatus LogEvent_Format(uint32_t *pFailure);
ErrorStatus LogEvent_FormatType(LogEvent_Type_t Type, uint32_t *pFailure);
ErrorStatus LogEvent_Init(uint8_t ForceFormat);
uint16_t LogEvent_GetCount( LogEvent_Type_t Type );
uint16_t LogEvent_GetTotalCount( LogEvent_Type_t Type );
char* LogEvent_GetTypeName( LogEvent_Type_t Type );

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __LOG_MANAGER_H */

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
