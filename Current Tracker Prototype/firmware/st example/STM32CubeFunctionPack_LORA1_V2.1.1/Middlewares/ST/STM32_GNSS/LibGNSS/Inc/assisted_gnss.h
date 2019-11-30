/**
*******************************************************************************
* @file    assisted_gnss.h
* @author  AST/CL
* @version V2.0.0
* @date    Jun-2018
* @brief   Provides API for A-GNSS - LibGNSS module middleware
*
*******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
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
#ifndef ASSISTED_GNSS_H
#define ASSISTED_GNSS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gnss_parser.h"

/** @addtogroup MIDDLEWARES
 *  @{
 */

/** @addtogroup ST
 *  @{
 */

/** @addtogroup STM32_GNSS
 *  @{
 */
 
/** @addtogroup LibGNSS
 *  @{
 */

/* Exported variables --------------------------------------------------------*/

extern const uint8_t vendorId[];
extern const uint8_t modelId[];

/* Defines -------------------------------------------------------------------*/
//#define ASSISTED_GNSS 1

#define BUF_SIZE_4K     (4*1024)
#define BUF_SIZE_5K     (5*1024)
#define BUF_SIZE_6K     (6*1024)
#define BUF_SIZE_8K     (8*1024)
#define BUF_SIZE_9K     (9*1024)
#define BUF_SIZE_12K    (12*1024)
#define BUF_SIZE_15K    (15*1024)
#define BUF_SIZE_16K    (16*1024)
#define BUF_SIZE_18K    (18*1024)

#define GPS_CONSTELLATION 0x01
#define GLO_CONSTELLATION 0x02
#define GAL_CONSTELLATION 0x04
#define BEI_CONSTELLATION 0x08
#define DEFAULT_CONSTELLATION \
   (GPS_CONSTELLATION | \
     GLO_CONSTELLATION | \
       GAL_CONSTELLATION)

#define MAX_BLOCK_TYPE_SIZE 128
#define MAX_SLOT_FREQ_SIZE 128
#define MAX_TIME_MODEL_SIZE 128

#define SINGLE_SEED_BIT_LEN                1240
#define SINGLE_SEED_FIRST_BLOCK_BIT_LEN    171

#define MAX_NUM_GPS_PRNS    32
#define MAX_NUM_GLO_PRNS    24
#define MAX_NUM_GAL_PRNS    30
#define MAX_NUM_BEI_PRNS    37
#define MIN_GLO_PRN         65
#define MIN_GAL_PRN         301

#define MIN_GLONASS_SAT_ID        65
#define MAX_GLONASS_SAT_ID        92

#define MIN_GALILEO_SAT_ID        301
#define MAX_GALILEO_SAT_ID        330

/* Exported types ------------------------------------------------------------*/
/**
 * @brief Seed type
 */
typedef enum
{
  GPS_SEED,
  GLO_SEED,
  GAL_SEED,
  BEI_SEED,
} seed_type_t;

/**
 * @brief Data structure that contains all of the information about Seed
 */
typedef struct {
  uint8_t *jsonBuffer;
  int curr_secs;
  int next_gps_time;
  int next_secs;
  unsigned char *seed;
  unsigned char block_types[MAX_BLOCK_TYPE_SIZE];
  unsigned char slot_freq[MAX_SLOT_FREQ_SIZE];
  unsigned char time_model[MAX_TIME_MODEL_SIZE];
  unsigned short nsat;
  unsigned short max_satid;
} seed_info_t;

typedef struct
{
  unsigned char SV_ID;  //slot_num;
  signed char   ch_num; //freq_num;
  unsigned char signal_available;
} glo_slot_freq_t;

typedef struct
{
  unsigned char SV_ID; 
  signed char   block_type; 
} block_type_t;

/** @defgroup ASSISTED_GNSS_FUNCTIONS ASSISTED GNSS FUNCTIONS
 *  @brief Prototypes of the API for Assisted GNSS support.
 *  @{
 */

/**
 * @brief  This function builds the Json request for RXN server.
 * @param  jsonData The string that will contain the request in json format
 * @retval 0 on success -1 on error
 */
int32_t A_GNSS_BuildJsonReq(char *jsonData,
                            int seedMask,
                            int *seedSize);

 /**
 * @brief  This function builds the authorization HTTP header for RXN server.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @param  auth_string The string that will contain the auth header
 * @retval 0 on success -1 on error
 */
 void A_GNSS_BuildAuthHeader(GNSSParser_Data_t *pGNSSParser_Data, char *auth_string);
 
/**
 * @brief  This function completes decoding and send seed.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  constellation The seed constellation
 * @param  seed_info Pointer to seed related info
 * @retval None
 */
void A_GNSS_SendSeed(void *pHandle,
                     unsigned char constellation,
                     seed_info_t *seed_info);

/**
 * @brief  This function builds and send the seed propagate command.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @retval None
 */
void A_GNSS_PropagateSeed(void *pHandle);

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

#endif /* ASSISTED_GNSS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
