 /**
  ******************************************************************************
  * @file    log_manager.c
  * @author  System Lab - System development
  * @version V1.0.0
  * @date    November-2018
  * @brief   Manager to log the events
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

/** @addtogroup STEVAL-STRKT01_LogManager LogManager
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <string.h>

#include "log_manager.h"
#include "M95M02_DR_driver.h"
#include "component.h"
#include "LoRaTracker_eeprom.h"

/** @addtogroup STEVAL-STRKT01_LogManager_Private_Defines LogManager Private Definitions
  * @brief Private definitions
  * @{
 */

#define CRC8_BASE_INI 0xA5
#define CRC8_BASE_END 0x5A

#define LOG_EV_NRM_PAYLOAD_SIZE          ((uint8_t)(LOG_EV_NRM_ITEM_SIZE - LOG_EV_HEADER_SIZE))
#define LOG_EV_SYS_PAYLOAD_SIZE          ((uint8_t)(LOG_EV_SYS_ITEM_SIZE - LOG_EV_HEADER_SIZE))
#define LOG_EV_CRT_PAYLOAD_SIZE          ((uint8_t)(LOG_EV_CRT_ITEM_SIZE - LOG_EV_HEADER_SIZE))

#define LOG_EV_INFO_KEY                  ((uint32_t)0xA4B3C2D2)
#define LOG_EV_INFO_KEY_SIZE             (sizeof(uint32_t))
#define LOG_EV_INFO_PAGE                 ((uint16_t)2u)
#define LOG_EV_INFO_KEY_OFFSET           ((uint32_t)0u)
#define LOG_EV_INFO_COUNTS_OFFSET        ((uint32_t)LOG_EV_INFO_KEY_SIZE)

#define LOG_EV_NRM_PAGE_START            ((uint16_t)3u)
#define LOG_EV_NRM_PAGE_END              ((uint16_t)902u)
#define LOG_EV_SYS_PAGE_START            ((uint16_t)903u)
#define LOG_EV_SYS_PAGE_END              ((uint16_t)972u)
#define LOG_EV_CRT_PAGE_START            ((uint16_t)973u)
#define LOG_EV_CRT_PAGE_END              ((uint16_t)990u)
#define LOG_EV_ITEM_FACTOR_COUNT         10u

#define LOG_EV_PAGE_START(_Type_)        (uint16_t)((_Type_) == LOG_EV_SYS ? LOG_EV_SYS_PAGE_START : ((_Type_) == LOG_EV_CRT ? LOG_EV_CRT_PAGE_START : LOG_EV_NRM_PAGE_START))
#define LOG_EV_PAGE_END(_Type_)          (uint16_t)((_Type_) == LOG_EV_SYS ? LOG_EV_SYS_PAGE_END   : ((_Type_) == LOG_EV_CRT ? LOG_EV_CRT_PAGE_END   : LOG_EV_NRM_PAGE_END  ))
#define LOG_EV_PAGE_NUM(_Type_)          ((LOG_EV_PAGE_END(_Type_)) - LOG_EV_PAGE_START(_Type_) + 1)
#define LOG_EV_ITEM_NUM(_Type_)          (((M95M02_DR_PAGE_SIZE) / (LOG_EV_ITEM_SIZE(_Type_))) * LOG_EV_PAGE_NUM(_Type_))
#define LOG_EV_ITEM_SIZE(_Type_)         (uint8_t)((_Type_) == LOG_EV_SYS ? LOG_EV_SYS_ITEM_SIZE : ((_Type_) == LOG_EV_CRT ? LOG_EV_CRT_ITEM_SIZE : LOG_EV_NRM_ITEM_SIZE))
#define LOG_EV_ITEM_PAYLOAD_SIZE(_Type_) (uint8_t)((_Type_) == LOG_EV_SYS ? LOG_EV_SYS_PAYLOAD_SIZE : ((_Type_) == LOG_EV_CRT ? LOG_EV_CRT_PAYLOAD_SIZE : LOG_EV_NRM_PAYLOAD_SIZE))
#define LOG_EV_ITEM_NUM_TOTAL(_Type_)    (uint16_t)(LOG_EV_ITEM_NUM(_Type_) * LOG_EV_ITEM_FACTOR_COUNT)


#define LOG_EV_CONF_INIT(_Type_, _Name_) { \
    .ItemSize           = (uint16_t)(LOG_EV_ITEM_SIZE((LogEvent_Type_t)_Type_)), \
    .ItemPayloadSize    = (uint16_t)(LOG_EV_ITEM_PAYLOAD_SIZE((LogEvent_Type_t)_Type_)), \
    .ItemNum            = (uint16_t)(LOG_EV_ITEM_NUM((LogEvent_Type_t)_Type_)), \
    .ItemNumXPage       = (uint16_t)(M95M02_DR_PAGE_SIZE / LOG_EV_ITEM_SIZE((LogEvent_Type_t)_Type_)), \
    .ItemNumTotal       = (uint16_t)(LOG_EV_ITEM_NUM_TOTAL((LogEvent_Type_t)_Type_)), \
    .PageStart          = (uint16_t)LOG_EV_PAGE_START((LogEvent_Type_t)_Type_), \
    .PageEnd            = (uint16_t)LOG_EV_PAGE_END((LogEvent_Type_t)_Type_), \
    .AddressBase        = (uint32_t)M95M02_DR_ADDRESS_PAGE(LOG_EV_PAGE_START((LogEvent_Type_t)_Type_)), \
    .Name               = _Name_ \
  }

#define TEST_EVAL(_Cond_)   PRINTF( (_Cond_) ? "TEST_OK \r\n" : "TEST_ERR \r\n" )

#define TEST_RESULT(_Cond_, ...) { PRINTF(__VA_ARGS__); TEST_EVAL(_Cond_); }

const LogEvent_Conf_t LogEvent_Conf[LOG_EV_TYPE_NUM] = {
  LOG_EV_CONF_INIT(0, "NRM"),
  LOG_EV_CONF_INIT(1, "SYS"),
  LOG_EV_CONF_INIT(2, "CRT"),
};

/**
  * @}
  */

const LogEvent_Item_t EmptyItem = {
  .Header = {.Count = LOG_EV_COUNT_EMPTY, .Type = LOG_EV_NAN, .TimeStamp = LOG_EV_TIMESTAMP_EMPTY, .Crc = LOG_EV_CRC_EMPTY},
  .Payload = { 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
    }
};

static const uint8_t kCrcTable[256] =
{
  0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
  0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
  0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
  0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
  0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
  0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
  0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
  0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
  0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
  0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
  0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
  0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
  0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
  0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
  0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
  0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
  0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
  0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
  0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
  0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
  0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
  0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
  0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
  0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
  0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
  0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
  0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
  0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
  0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
  0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
  0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
  0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};

/** @addtogroup STEVAL-STRKT01_LogManager_Private_Variables LogManager Private Variables
  * @brief Private variables
  * @{
 */
static uint16_t Counts[LOG_EV_TYPE_NUM] = {0};
extern void *M95M02_handle;
/**
  * @}
  */


/** @addtogroup STEVAL-STRKT01_LogManager_Private_FunctionPrototypes LogManager Private Function Prototypes
  * @brief Private functions prototypes
  * @{
 */

extern uint32_t App_GetTimeStamp(void);
static uint32_t LogEvent_CalcCRC(LogEvent_Item_t * pLogItem);
ErrorStatus LogEvent_CheckCRC(LogEvent_Item_t * pLogItem);
static uint8_t LogEvent_IsFull(LogEvent_Type_t Type);
static uint32_t LogEvent_CalcMemAddress(LogEvent_Type_t Type, uint16_t Pos);
static ErrorStatus LogEvent_CheckKey(void);
static ErrorStatus LogEvent_SetKey(void);
static ErrorStatus LogEvent_WriteCounts(void);
static ErrorStatus LogEvent_ReadCounts(void);
static ErrorStatus LogEvent_CheckCount(LogEvent_Type_t Type, uint16_t Count);
ErrorStatus LogEvent_Recovery(void);

/**
  * @}
  */

/** @addtogroup STEVAL-STRKT01_LogManager_Private_FunctionDefinition LogManager Private Function Definition
  * @brief Private functions definitions
  * @{
 */

/**
  * @brief  Compute CRC
  * @param  pLogItem: Pointer to LogEvent Item
  * @retval CRC
  */
static uint32_t LogEvent_CalcCRC(LogEvent_Item_t * pLogItem)
{
  if((!pLogItem) || (!LOG_EV_TYPE_IS_VALID(pLogItem->Header.Type)))
  {
    return LOG_EV_CRC_ERROR;
  }
  
  /* init the crc */
  pLogItem->Header.Crc = CRC8_BASE_INI;

  /* get params */
  uint8_t *pdata = (uint8_t *)pLogItem;
  uint8_t len = LOG_EV_CONF(pLogItem->Header.Type, ItemSize);
  uint8_t index;
  uint8_t crc = CRC8_BASE_INI;
  
  /* calculate the crc */
  for (index=0; index < len; index++)
  {
    crc = kCrcTable[pdata[index] ^ crc];
  }
  
  crc ^= CRC8_BASE_END;
  pLogItem->Header.Crc = crc;
  
  return crc & 0x000000FF;
}

/**
  * @brief  Checks CRC
  * @param  pLogItem: Pointer to LogEvent Item
  * @retval SUCCESS if CRC is correct, ERROR otherwise
  */
ErrorStatus LogEvent_CheckCRC(LogEvent_Item_t * pLogItem)
{
  if((!pLogItem) || (!LOG_EV_TYPE_IS_VALID(pLogItem->Header.Type)))
  {
    return ERROR;
  }
  
  /* check the CRC */
  uint32_t crc1 = (uint16_t)pLogItem->Header.Crc;
  uint32_t crc2 = (uint16_t)LogEvent_CalcCRC(pLogItem);
  
  return crc1 == crc2 ? SUCCESS : ERROR;
}

/**
  * @brief  Checks if a specific type of item is full
  * @param  Type: LogEvent Type
  * @retval 0 if not full, n>0 otherwise 
  */
static uint8_t LogEvent_IsFull(LogEvent_Type_t Type)
{
  if (!LOG_EV_TYPE_IS_VALID(Type))
  {
    return 1 == 1;
  }
  return (Counts[(uint8_t)Type] >= LOG_EV_CONF(Type, ItemNum));
}

/**
  * @brief  This function computes memory address
  * @param  Type: LogEvent Type
  * @param  Pos: Position inside of the log
  * @retval Address
  */
static uint32_t LogEvent_CalcMemAddress(LogEvent_Type_t Type, uint16_t Pos)
{
  if (!LOG_EV_TYPE_IS_VALID(Type))
  {
    return 0;
  }
  
  uint32_t address = LOG_EV_CONF(Type, AddressBase) + (Pos % LOG_EV_CONF(Type, ItemNum)) * LOG_EV_CONF(Type, ItemSize);
    
  return address;
}

/**
  * @brief  This function check if the logmanager key is valid
  * @param  None
  * @retval SUCCESS if key is valid, ERROR otherwise
  */
static ErrorStatus LogEvent_CheckKey()
{
  DrvStatusTypeDef res;
  uint32_t key = 0;
  uint8_t size = LOG_EV_INFO_KEY_SIZE;
  uint32_t address = M95M02_DR_ADDRESS_PAGE(LOG_EV_INFO_PAGE) + LOG_EV_INFO_KEY_OFFSET;
  
  res = BSP_EEPROM_Read(M95M02_handle, address, (uint8_t *)&key, size);
  
  return COMPONENT_OK == res && key == LOG_EV_INFO_KEY ? SUCCESS : ERROR;
}

/**
  * @brief  Setting logmanager key
  * @param  None
  * @retval SUCCESS if key is correctly set, ERROR otherwise
  */
static ErrorStatus LogEvent_SetKey()
{
  DrvStatusTypeDef res;
  uint32_t key = LOG_EV_INFO_KEY;
  uint8_t size = LOG_EV_INFO_KEY_SIZE;
  uint32_t address = M95M02_DR_ADDRESS_PAGE(LOG_EV_INFO_PAGE) + LOG_EV_INFO_KEY_OFFSET;
  
  res = BSP_EEPROM_Write(M95M02_handle, address, (uint8_t *)&key, size);
  
  return COMPONENT_OK == res && key == LOG_EV_INFO_KEY ? SUCCESS : ERROR;
}

/**
  * @brief  Store variable Counts in the info part of the EEPROM
  * @param  None
  * @retval SUCCESS if operation is correct, ERROR otherwise
  */
static ErrorStatus LogEvent_WriteCounts()
{
  DrvStatusTypeDef res;
  uint8_t *pdata = (uint8_t *)Counts;
  uint8_t size = sizeof(Counts);
  uint32_t address = M95M02_DR_ADDRESS_PAGE(LOG_EV_INFO_PAGE) + LOG_EV_INFO_COUNTS_OFFSET;
  
  res = BSP_EEPROM_Write(M95M02_handle, address, pdata, size);
  
  return COMPONENT_OK == res ? SUCCESS : ERROR;
}


/**
  * @brief  Read variable Counts from the info part of the EEPROM
  * @param  None
  * @retval SUCCESS if operation is correct, ERROR otherwise
  */
static ErrorStatus LogEvent_ReadCounts()
{
  if (ERROR == LogEvent_CheckKey())
  {
    return ERROR;
  }
  
  DrvStatusTypeDef res;
  uint8_t *pdata = (uint8_t *)Counts;
  uint8_t size = sizeof(Counts);
  uint32_t address = M95M02_DR_ADDRESS_PAGE(LOG_EV_INFO_PAGE) + LOG_EV_INFO_COUNTS_OFFSET;
  
  res = BSP_EEPROM_Read(M95M02_handle, address, pdata, size);
  
  return COMPONENT_OK == res ? SUCCESS : ERROR;
}


/**
  * @brief  Check if the count is valid 
  * @param  Type: LogEvent Type
  * @param  Count: number of stored items
  * @retval SUCCESS if Count is valid, ERROR otherwise
  */
static ErrorStatus LogEvent_CheckCount(LogEvent_Type_t Type, uint16_t Count)
{
  /* check the validity of Type */
  uint8_t cond = LOG_EV_TYPE_IS_VALID(Type);
  
  uint16_t curr_count = Counts[(uint8_t)Type];
  uint16_t item_num   = LOG_EV_CONF(Type, ItemNum);
  
  /* check max : count < Counts[type] */
  cond &= Count < curr_count;
  
  if (curr_count >= item_num) //full
  {
    /* check min : count >= Counts[type] - item_num */
    cond &= Count >= (curr_count - item_num);
  }
  
  return cond ? SUCCESS : ERROR;
}


/**
  * @brief  LogEvent Recovery
  * @param  None
  * @retval SUCCESS if operation is correct, ERROR otherwise
  */
ErrorStatus LogEvent_Recovery()
{
  PRINTF("LogEvent_Recovery\r\n");
  uint8_t bManualInit = 0; //set this var by debugger
  if(bManualInit)
  {
    uint32_t nFailure = 0;
    LogEvent_Format(&nFailure);
  }
  
  LogEvent_Item_t xLogItem = { 0 };
  for(uint8_t xType = 0; xType < LOG_EV_TYPE_NUM; xType++)
  {
    PRINTF("Type %d: %s\r\n", xType, LogEvent_GetTypeName((LogEvent_Type_t)xType));
    Counts[xType] = LOG_EV_COUNT_EMPTY;
    for(uint16_t pos = 0; pos < LOG_EV_CONF(xType, ItemNum); pos++)
    {
      if(SUCCESS == LogEvent_Get(&xLogItem, (LogEvent_Type_t)xType, pos, 1))
      {
        if(xLogItem.Header.Count != LOG_EV_COUNT_EMPTY)
        {
          if(Counts[xType] == LOG_EV_COUNT_EMPTY)
          {
            Counts[xType]=0;
          }
          if(xLogItem.Header.Count >= Counts[xType])
          {
            Counts[xType] = xLogItem.Header.Count;
          }
          else
          {
            break;
          }
        }
        else
        {
          break;
        }
      }
    }
    uint16_t nItemSaved = ( Counts[xType] != LOG_EV_COUNT_EMPTY) ? Counts[xType]:0;
    PRINTF("%s events saved %d\r\n", LogEvent_GetTypeName((LogEvent_Type_t)xType), nItemSaved);
    UNUSED(nItemSaved);
    Counts[xType]++;//next item free
  }
  
  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup STEVAL-STRKT01_LogManager_Public_FunctionDefinition LogManager Public Function Definition
  * @brief Public functions definitions
  * @{
 */

/**
  * @brief  Add new item in EEPROM
  * @param  Type: LogEvent Type
  * @param  pLogItem: pointer to LogEvent Item
  * @retval SUCCESS if operation is correct, ERROR otherwise
  */
ErrorStatus LogEvent_Push(LogEvent_Type_t Type, LogEvent_Item_t *pLogItem)
{
  if ((!pLogItem) || !LOG_EV_TYPE_IS_VALID(Type))
  {
    PRINTF("Log: Push ... Failed. Invalid type.\r\n");
    return ERROR;
  }

  DrvStatusTypeDef res;

  /* Header */
  
  /* fill the Count with the current */
  uint16_t curr_count = Counts[Type];
  if (LOG_EV_COUNT_DEAD == curr_count)
  {
    PRINTF("Log: Push ... Failed. Invalid count.\r\n");
    return ERROR;
  }
  pLogItem->Header.Count = curr_count;
  
  /* fill the Type */
  pLogItem->Header.Type = Type;
  
  /* fill the Timestamp as the seconds passed from a specific date */
  pLogItem->Header.TimeStamp = App_GetTimeStamp();

  /* calculate the CRC and fill the field*/
  if (LOG_EV_CRC_ERROR == LogEvent_CalcCRC(pLogItem))
  {
    PRINTF("Log: Push ... Failed. CRC Calculation.\r\n");
    return ERROR; /* CRC failed */
  }
  
  /* get the memory address and the payload size according to the type */
  uint32_t address = LogEvent_CalcMemAddress(pLogItem->Header.Type, pLogItem->Header.Count);
  uint8_t payload_size = LOG_EV_CONF(pLogItem->Header.Type, ItemPayloadSize);
  
  /* first step: write the payload */
  res = BSP_EEPROM_Write(M95M02_handle, address + LOG_EV_HEADER_SIZE, (uint8_t *)pLogItem->Payload, payload_size);

  if (COMPONENT_OK != res)
  {
    PRINTF("Log: Push ... Failed. Can't save the payload.\r\n");
    return ERROR;
  }
  
  /* second step: write the header */
  res = BSP_EEPROM_Write(M95M02_handle, address, (uint8_t *)&pLogItem->Header, LOG_EV_HEADER_SIZE);
  
  if (COMPONENT_OK != res)
  {
    PRINTF("Log: Push ... Failed. Can't save the header.\r\n");
    return ERROR;
  }

  /* write ok, increment counts and update counts */
  Counts[(uint8_t)pLogItem->Header.Type]++;
  Counts[(uint8_t)Type] %= LOG_EV_CONF(Type, ItemNumTotal); 
  LogEvent_WriteCounts();
  
  PRINTF("Log: Push ... Ok. Item %-3d CRC %02X [%s]\r\n", pLogItem->Header.Count, pLogItem->Header.Crc, (char *)pLogItem->Payload);
  return COMPONENT_OK == res ? SUCCESS : ERROR;
}


/**
  * @brief  Pushing data to EEPROM 
  * @param  Type: Type of data to be pushed
  * @param  sFormatString:  string to be pushed
  * @retval item payload (-1 in case of error)
  */
int8_t LogEvent_Push_Printf(LogEvent_Type_t Type, char const *sFormatString, ...)
{
  if (!LOG_EV_TYPE_IS_VALID(Type))
  {
    return -1;
  }

  LogEvent_Item_t item;
  uint8_t payload_size = LOG_EV_CONF(Type, ItemPayloadSize);
  
  memset(item.Payload, 0, LOG_EV_MAX_PAYLOAD_SIZE);
  
  va_list ap;
  va_start (ap, sFormatString);
  
  /* NOTE: The functions snprintf() and vsnprintf() write at most size bytes (including the terminating null byte ('\0')) to str. */
  vsnprintf((char *)item.Payload, payload_size, sFormatString, ap);
  va_end (ap);

  if (ERROR == LogEvent_Push(Type, &item))
  {
    return -1;
  }
  return strlen((char *)item.Payload);
}


/**
  * @brief  This function updates a char
  * @param  Type: LogEvent Type
  * @param  Pos: 
  * @param  Offset: 
  * @param  Ch:
  * @retval SUCCESS if operation is correct, ERROR otherwise
  */
ErrorStatus LogEvent_UpdateItem(LogEvent_Item_t *pLogItem)
{
  DrvStatusTypeDef res;
  
  /* get the memory address and the payload size according to the type */
  uint32_t address = LogEvent_CalcMemAddress(pLogItem->Header.Type, pLogItem->Header.Count);
  uint16_t item_size = LOG_EV_CONF(pLogItem->Header.Type, ItemSize);

  /* calculate the CRC and fill the field*/
  if (LOG_EV_CRC_ERROR == LogEvent_CalcCRC(pLogItem))
  {
    PRINTF("Log: UpdateItem... Failed. CRC Calculation.\r\n");
    return ERROR; /* CRC failed */
  }
  
    /* first step: write the payload */
  res = BSP_EEPROM_Write(M95M02_handle, address, (uint8_t *)(&pLogItem->Header), item_size);

  if (COMPONENT_OK != res)
  {
    PRINTF("Log: UpdateItem ... Failed. Can't save the payload.\r\n");
    return ERROR;
  }

  
  return COMPONENT_OK == res ? SUCCESS : ERROR;
  
}


/**
  * @brief  This function gets a log item 
  * @param  pLogItem: pointer
  * @param  Type: LogEvent Type
  * @param  Count: number of required log item 
  * @param  bReqPos: absolute position condition (Yes_No)
  * @retval SUCCESS if operation is correct, ERROR otherwise
  */
ErrorStatus LogEvent_Get(LogEvent_Item_t *pLogItem, LogEvent_Type_t Type, uint16_t Count, uint8_t bReqPos)
{
  if ((!pLogItem) || !LOG_EV_TYPE_IS_VALID(Type))
  {
    return ERROR;
  }
  
  /* check the count if it is not requiring the absolute position */
  if ((!bReqPos) && (ERROR == LogEvent_CheckCount(Type, Count)))
  {
    return ERROR;
  }
  
  ErrorStatus ret;
  uint8_t *pdata = (uint8_t *)pLogItem;
  uint32_t address = LogEvent_CalcMemAddress(Type, Count);
  uint8_t size = LOG_EV_CONF(Type, ItemSize);
  ret = COMPONENT_OK == BSP_EEPROM_Read(M95M02_handle, address, pdata, size) ? SUCCESS : ERROR;
  
  if ((!bReqPos) && (SUCCESS == ret))
  {
    ret = LogEvent_CheckCRC(pLogItem);
  }
  return ret;
}


/**
  * @brief  Memory initialization
  * @param  pFailure: pointer to nb of failures
  * @retval SUCCESS if memory correctly initialized, ERROR otherwise
  */
ErrorStatus LogEvent_Format(uint32_t *pFailure)
{
  ErrorStatus res = SUCCESS;
  PRINTF("Format Memory\r\n");
  for(uint8_t type = 0; type < LOG_EV_TYPE_NUM; type++)
  {
    if(ERROR == LogEvent_FormatType((LogEvent_Type_t)type, pFailure))
    {
      res = ERROR;
    }
  }
  if (SUCCESS == res)
  {
    PRINTF("Log memory formatted, setting key ... ");
    res = LogEvent_SetKey();
    TEST_EVAL(SUCCESS == res);
  }
  return res;
}
   

/**
  * @brief  Memory initialization for specific type
  * @param  Type: LogEvent Type
  * @param  pFailure: pointer to nb of failures
  * @retval SUCCESS if operation is correct, ERROR otherwise
  */
ErrorStatus LogEvent_FormatType(LogEvent_Type_t Type, uint32_t *pFailure)
{
  if (!LOG_EV_TYPE_IS_VALID(Type))
  {
    return ERROR;
  }
  
  /* reset counts and status for the specified type */
  Counts[(uint8_t)Type] = 0;
  

  /* Format for each type */
  ErrorStatus ret = SUCCESS;
  DrvStatusTypeDef res;
  uint32_t address;
  uint8_t size;
  uint8_t *pdata = (uint8_t *)&EmptyItem;
  uint16_t num;
  
  PRINTF("Format memory type: %s (%d): ", LOG_EV_CONF(Type, Name), (uint8_t)Type);
  size = LOG_EV_CONF(Type, ItemSize);
  num = LOG_EV_CONF(Type, ItemNum);
  for(uint16_t pos = 0; pos < num ; pos++)
  {
    address = LogEvent_CalcMemAddress((LogEvent_Type_t)Type, pos);
    res = BSP_EEPROM_Write(M95M02_handle, address, pdata, size);
    if (COMPONENT_OK  == res)
    {
      PRINTF("#");
    }
    else
    {
      PRINTF("-");
      if (pFailure) (*pFailure)++;
      ret = ERROR;
      Counts[(uint8_t)Type] = LOG_EV_COUNT_DEAD;
    }
  }
  PRINTF("\r\n");

  /* update the */
  if (ERROR == LogEvent_WriteCounts())
  {
    PRINTF("Write counts failed.\r\n");
  }
  
  return ret;
}


/**
  * @brief  This function gets the number of log items per log type
  * @param  Type: LogEvent Type
  * @retval Number of log items per type
  */
uint16_t LogEvent_GetTotalCount( LogEvent_Type_t Type )
{
  return (LOG_EV_TYPE_IS_VALID(Type)) ? LOG_EV_CONF(Type, ItemNum) : LOG_EV_COUNT_EMPTY;
}


/**
  * @brief  This function gets the number of log items
  * @param  Type: LogEvent Type
  * @retval Number of log items
  */
uint16_t LogEvent_GetCount( LogEvent_Type_t Type )
{
  return (LOG_EV_TYPE_IS_VALID(Type)) ? Counts[(uint8_t)Type] : LOG_EV_COUNT_EMPTY;
}


/**
  * @brief  this function gets a string with the name of the type
  * @param  Type: LogEvent Type
  * @retval Name of the type
  */
char * LogEvent_GetTypeName( LogEvent_Type_t Type )
{
  return (char *)((LOG_EV_TYPE_IS_VALID(Type)) ? (char *)LOG_EV_CONF(Type, Name) : "INV");
}


/**
  * @brief  This function formats memory if it is not formatted, or if forced
  * @param  ForceFormat: force memory formatting
  * @retval SUCCESS if memory has been correctly initialized, ERROR otherwise
  */
ErrorStatus LogEvent_Init(uint8_t ForceFormat)
{
  /* to void warning */
  (void)LogEvent_IsFull;
  
  PRINTF("\r\nLog memory init\r\n");
  
  ErrorStatus cond = SUCCESS;
  
  if (SUCCESS == cond)
  {
    /* check the key stored in the table */
    PRINTF("- check key ... ");
    cond = LogEvent_CheckKey();
    TEST_EVAL(SUCCESS == cond);
  }
 
  if (SUCCESS != cond || ForceFormat)
  {
    PRINTF("- formatting memory\r\n");
    cond = LogEvent_Format(NULL);
    TEST_RESULT(SUCCESS == cond, "  format memory result ... ");
  }

  if (SUCCESS == cond)
  {
    /* read the counts from eeprom */
    PRINTF("- read counts ... ");
    cond = LogEvent_ReadCounts();
    TEST_EVAL(SUCCESS == cond);
  }

  if (SUCCESS != cond)
  {
    /* the log system is not available, set the counts to dead value */
    for(uint8_t i = 0; i < LOG_EV_TYPE_NUM; i++)
    {
      Counts[i] = LOG_EV_COUNT_DEAD;
    }
  }
  
  TEST_RESULT(SUCCESS == cond, "Log memory initialization ... ");
  return cond;
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
