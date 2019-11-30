/**
*******************************************************************************
* @file    gnss_parser.h
* @author  AST/CL
* @version V2.0.0
* @date    Mar-2018
* @brief   LibGNSS module middleware.
*
*******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
*        www.st.com/software_license_agreement_liberty_v2
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
********************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GNSS_PARSER_H
#define GNSS_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "NMEA_parser.h"
#include "gnss_geofence.h"
#include "gnss_datalog.h"
  
/** @addtogroup MIDDLEWARES
 *  @{
 */

/** @addtogroup ST
 *  @{
 */

/** @addtogroup STM32_GNSS
 *  @{
 */
 
/** @defgroup LibGNSS LibGNSS
 *  @brief Module handling GNSS parsed data.
 *  @{
 */

/** @defgroup LibGNSS_CONSTANTS_DEFINITIONS CONSTANTS DEFINITIONS
 * @{
 */

/**
 * @brief Constant that indicates the maximum number of positions that can be stored.
 */
#define MAX_STOR_POS 64
  
/**
 * @brief Constant that indicates the lenght of the buffer that stores the GPS data read by the GPS expansion.
 */
#define MAX_LEN 2*512
  
 
/**
 * @brief Constant the indicates the max duration of the data reading by the GPS expansion.
 */
#define MAX_DURATION  5000
  
/**
 * @brief Constant the indicates the ack value from the TeseoIII device during the FW upgrade process
 */ 
#define FWUPG_DEVICE_ACK   0xCCU

/**
 * @brief Constant that indicates the maximum number of nmea messages to be processed.
 */
#define NMEA_MSGS_NUM 14 //Note: update this constant coherently to eMsg enum type

/**
 * @}
 */

/** @defgroup LibGNSS_EXPORTED_TYPES EXPORTED TYPES
 * @{
 */

/**
 * @brief Enumeration structure that contains the two states of a parsing dispatcher process
 */
typedef enum
{
  GNSS_PARSER_OK = 0,
  GNSS_PARSER_ERROR
} GNSSParser_Status_t;

/**
 * @brief Enumeration structure that contains the two states of a debug process
 */
typedef enum {
  DEBUG_OFF = 0, /**< In this case, nothing will be printed on the console (nmea strings, positions and so on) */
  DEBUG_ON = 1   /**< In this case, nmea strings and just acquired positions will be printed on the console */
} Debug_State;

/**
 * @brief Enumeration structure that contains the NMEA messages types
 */
typedef enum
{
  GPGGA,
  GNS,
  GPGST,
  GPRMC,
  GSA,
  GSV,
  PSTMVER,
  PSTMPASSRTN,
  PSTMAGPSSTATUS,
  PSTMGEOFENCE,
  PSTMODO,
  PSTMDATALOG,
  PSTMSGL,
  PSTMSAVEPAR
} eNMEAMsg;

/**
 * @brief Data structure that contains the GNSS data
 */
typedef struct
{
  Debug_State debug;      /**< Debug status */
  GPGGA_Info_t gpgga_data; /**< $GPGGA Data holder */
  GNS_Info_t   gns_data;   /**< $--GNS Data holder */
  GPGST_Info_t gpgst_data; /**< $GPGST Data holder */
  GPRMC_Info_t gprmc_data; /**< $GPRMC Data holder */
  GSA_Info_t   gsa_data;   /**< $--GSA Data holder */
  GSV_Info_t   gsv_data;   /**< $--GSV Data holder */

  PSTMVER_Info_t pstmver_data;   /**< $PSTMVER Data holder */
  PSTMPASSRTN_Info_t pstmpass_data; /**< $PSTMPASSRTN Data holder */
  PSTMAGPSSTATUS_Info_t pstmagps_status; /**< $PSTMAGPSSTATUS */

  Geofence_Info_t geofence_data; /**< $PSTMGEOFENCE Data holder */
  Odometer_Info_t odo_data; /**< $PSTMODO Data holder */
  Datalog_Info_t datalog_data; /**< $PSTMDATALOG Data holder */
  OpResult_t result;
} GNSSParser_Data_t;

/**
 * @}
 */

/** @defgroup LibGNSS_EXPORTED_FUNCTIONS EXPORTED FUNCTIONS
 * @{
 */

/**	
 * @brief  This function initializes the agent handling parsed GNSS data
 * @param  pGNSSParser_Data The agent
 * @retval GNSS_PARSER_OK on success GNSS_PARSER_ERROR otherwise
 */
GNSSParser_Status_t GNSS_PARSER_Init(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function computes the checksum and checks the sanity of a GNSS sentence
 * @param  pSentence The sentence
 * @param  len The sentence length
 * @retval GNSS_PARSER_OK on success GNSS_PARSER_ERROR otherwise
 */
GNSSParser_Status_t GNSS_PARSER_CheckSanity(uint8_t *pSentence, uint64_t len);

/**	
 * @brief  This function dispatches a GNSS sentence to be parsed
 * @param  pGNSSParser_Data The agent
 * @param  msg The message type
 * @param  pBuffer The message to be dispatched
 * @retval GNSS_PARSER_OK on success GNSS_PARSER_ERROR otherwise
 */
GNSSParser_Status_t GNSS_PARSER_ParseMsg(GNSSParser_Data_t *pGNSSParser_Data, uint8_t msg, uint8_t *pBuffer);

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


#ifdef __cplusplus
}
#endif

#endif /* GNSS_PARSER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

