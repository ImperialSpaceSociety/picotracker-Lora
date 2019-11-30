/**
*******************************************************************************
* @file    gnss_parser.c
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

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "gnss_parser.h"

#ifdef USE_FREE_RTOS
#include "cmsis_os.h"
#define OS_Delay osDelay
#else
#define OS_Delay HAL_Delay
#endif /* USE_FREE_RTOS */

/* Exported functions --------------------------------------------------------*/

GNSSParser_Status_t GNSS_PARSER_Init(GNSSParser_Data_t *pGNSSParser_Data)
{
  if (pGNSSParser_Data == NULL)
  {
    return GNSS_PARSER_ERROR;
  }

  pGNSSParser_Data->debug = DEBUG_ON;
  (void)memset((void *)(&pGNSSParser_Data->gpgga_data), 0, sizeof(GPGGA_Info_t));
  pGNSSParser_Data->gpgga_data.xyz.ew = (uint8_t)' ';
  pGNSSParser_Data->gpgga_data.xyz.ns = (uint8_t)' ';
  pGNSSParser_Data->gpgga_data.xyz.mis = (uint8_t)' ';

  (void)memset((void *)(&pGNSSParser_Data->gns_data), 0, sizeof(GNS_Info_t));
  pGNSSParser_Data->gns_data.xyz.ew = (uint8_t)' ';
  pGNSSParser_Data->gns_data.xyz.ns = (uint8_t)' ';

  (void)memset((void *)(&pGNSSParser_Data->gpgst_data), 0, sizeof(GPGST_Info_t));

  (void)memset((void *)(&pGNSSParser_Data->gprmc_data), 0, sizeof(GPRMC_Info_t));
  pGNSSParser_Data->gprmc_data.xyz.ew = (uint8_t)' ';
  pGNSSParser_Data->gprmc_data.xyz.ns = (uint8_t)' ';

  (void)memset((void *)(&pGNSSParser_Data->gsa_data), 0, sizeof(GSA_Info_t));
  (void)memset((void *)(&pGNSSParser_Data->gsv_data), 0, sizeof(GSV_Info_t));
  (void)memset((void *)(&pGNSSParser_Data->pstmver_data), 0, sizeof(PSTMVER_Info_t));
  (void)memset((void *)(&pGNSSParser_Data->geofence_data), 0, sizeof(Geofence_Info_t));
  (void)memset((void *)(&pGNSSParser_Data->odo_data), 0, sizeof(Odometer_Info_t));
  (void)memset((void *)(&pGNSSParser_Data->datalog_data), 0, sizeof(Datalog_Info_t));
  (void)memset((void *)(&pGNSSParser_Data->result), 0, sizeof(OpResult_t));

  return GNSS_PARSER_OK;
}

GNSSParser_Status_t GNSS_PARSER_CheckSanity(uint8_t *pSentence, uint64_t len)
{
  uint32_t checksum, check = 0U;
  
  if((len > 0U) && (len < 5U)) {
    return GNSS_PARSER_ERROR;
  }
  if(len == 0U) {
    return GNSS_PARSER_OK;
  }
  checksum = (char2int(pSentence[len-4U]) << 4) | char2int(pSentence[len-3U]);
  
  for(uint64_t c = 1U; c < (len-5U); c++) {
    check = (check ^ pSentence[c]);
  }
  
  return (check == checksum) ? GNSS_PARSER_OK : GNSS_PARSER_ERROR;
}

GNSSParser_Status_t GNSS_PARSER_ParseMsg(GNSSParser_Data_t *pGNSSParser_Data, uint8_t msg, uint8_t *pBuffer)
{
  ParseStatus_t status = PARSE_FAIL;

  switch(msg) {
  case GPGGA:
    status = NMEA_ParseGPGGA(&pGNSSParser_Data->gpgga_data, pBuffer);
    break;
  case GNS:
    status = NMEA_ParseGNS(&pGNSSParser_Data->gns_data, pBuffer);
    break;
  case GPGST:
    status = NMEA_ParseGPGST(&pGNSSParser_Data->gpgst_data, pBuffer);
    break;
  case GPRMC:
    status = NMEA_ParseGPRMC(&pGNSSParser_Data->gprmc_data, pBuffer);
    break;
  case GSA:
    status = NMEA_ParseGSA(&pGNSSParser_Data->gsa_data, pBuffer);
    break;
  case GSV:
    status = NMEA_ParseGSV(&pGNSSParser_Data->gsv_data, pBuffer);
    break;
  case PSTMVER:
    status = NMEA_ParsePSTMVER(&pGNSSParser_Data->pstmver_data, pBuffer);
    break;
  case PSTMPASSRTN:
    status = NMEA_ParsePSTMPASSRTN(&pGNSSParser_Data->pstmpass_data, pBuffer);
    break;
  case PSTMAGPSSTATUS:
    status = NMEA_ParsePSTMAGPSSTATUS(&pGNSSParser_Data->pstmagps_status, pBuffer);
    break;
  case PSTMGEOFENCE:
    status = NMEA_ParsePSTMGeofence(&pGNSSParser_Data->geofence_data, pBuffer);
    break;
  case PSTMODO:
    status = NMEA_ParsePSTMOdo(&pGNSSParser_Data->odo_data, pBuffer);
    break;
  case PSTMDATALOG:
    status = NMEA_ParsePSTMDatalog(&pGNSSParser_Data->datalog_data, pBuffer);
    break;
  case PSTMSGL:
    status = NMEA_ParsePSTMsgl(&pGNSSParser_Data->result, pBuffer);
    break;
  case PSTMSAVEPAR:
    status = NMEA_ParsePSTMSavePar(&pGNSSParser_Data->result, pBuffer);
    break;
  default:
    break;
  }
    
  return ((status == PARSE_FAIL) ? GNSS_PARSER_ERROR : GNSS_PARSER_OK);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
