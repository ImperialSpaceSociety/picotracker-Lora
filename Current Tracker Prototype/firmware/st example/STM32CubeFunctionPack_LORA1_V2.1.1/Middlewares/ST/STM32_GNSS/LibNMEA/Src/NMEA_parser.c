/**
*******************************************************************************
* @file    NMEA_parser.c
* @author  AST / Central Lab
* @version V2.0.0
* @date    18-May-2017
* @brief   NMEA sentence parser
*
*******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
#include <stdlib.h>
#include "string.h"
#include "NMEA_parser.h"

/* Private defines -----------------------------------------------------------*/

/*
 * Constant for strtol base param
 */
#define BASE 10

/*
 * Enumeration structure that contains the two success states of a parsing process
 */
typedef enum {
  TENS = 0,
  HUNDREDS,
  THOUSANDS
} Decimal_t;

/* Private functions ---------------------------------------------------------*/
static int32_t NMEA_CheckGNSMsg(const char header[]);
static int32_t NMEA_CheckGSAMsg(const char header[]);
static int32_t NMEA_CheckGSVMsg(const  char header[]);
static int32_t NMEA_CheckGeofenceMsg(const char header[]);
static int32_t NMEA_CheckOdoMsg(const char header[]);
static int32_t NMEA_CheckDatalogMsg(const char header[]);
static int32_t NMEA_CheckListMsg(const char header[]);
static int32_t NMEA_CheckSaveparMsg(const char header[]);
static int32_t NMEA_CheckPassMsg(const char header[]);
static void NMEA_ResetGSVMsg(GSV_Info_t *pGSVInfo);

static uint32_t digit2int(uint8_t buf[], int32_t offset, Decimal_t d);
static void scan_utc(uint8_t *pUTCStr, UTC_Info_t *pUTC);
static uint32_t nmea_checksum(const uint8_t buf[]);
static void scan_timestamp_time(uint8_t buf[], Timestamp_Info_t *pTimestamp);
static void scan_timestamp_date(uint8_t buf[], Timestamp_Info_t *pTimestamp);

/* Private variables ---------------------------------------------------------*/
static uint8_t app[MAX_MSG_NUM][MAX_MSG_LEN];

/*
 * Function that checks the header of a GNS NMEA sentence.
 */
static int32_t NMEA_CheckGNSMsg(const char header[])
{
  int32_t is_gnsmsg = 1;
  
  if (strcmp(header, "$GPGNS") == 0)
  {
    is_gnsmsg = 0;
  }
  if (strcmp(header, "$GAGNS") == 0)
  {
    is_gnsmsg = 0;
  }
  if (strcmp(header, "$BDGNS") == 0)
  {
    is_gnsmsg = 0;
  }
  if (strcmp(header, "$QZGNS") == 0)
  {
    is_gnsmsg = 0;
  }
  if (strcmp(header, "$GNGNS") == 0)
  {
    is_gnsmsg = 0;
  }

  return is_gnsmsg;
}

/*
 * Function that checks the header of a GSA NMEA sentence.
 */
static int32_t NMEA_CheckGSAMsg(const char header[])
{
  int32_t is_gsamsg = 1;
  
  if (strcmp(header, "$GPGSA") == 0)
  {
    is_gsamsg = 0;
  }
  if (strcmp(header, "$GLGSA") == 0)
  {
    is_gsamsg = 0;
  }
  if (strcmp(header, "$GAGSA") == 0)
  {
    is_gsamsg = 0;
  }
  if (strcmp(header, "$BDGSA") == 0)
  {
    is_gsamsg = 0;
  }
  if (strcmp(header, "$GNGSA") == 0)
  {
    is_gsamsg = 0;
  }

  return is_gsamsg;
}

/*
 *  Function that checks the header of a GSV NMEA sentence.
 */
static int32_t NMEA_CheckGSVMsg(const char header[])
{
  int32_t is_gsvmsg = 1;
  
  if (strcmp(header, "$GPGSV") == 0)
  {
    is_gsvmsg = 0;
  }
  if (strcmp(header, "$GLGSV") == 0)
  {
    is_gsvmsg = 0;
  }
  if (strcmp(header, "$GAGSV") == 0)
  {
    is_gsvmsg = 0;
  }
  if (strcmp(header, "$BDGSV") == 0)
  {
    is_gsvmsg = 0;
  }
  if (strcmp(header, "$QZGSV") == 0)
  {
    is_gsvmsg = 0;
  }
  if (strcmp(header, "$GNGSV") == 0)
  {
    is_gsvmsg = 0;
  }

  return is_gsvmsg;
}

/*
 *  Helper function to reset GSV fields
 */
static void NMEA_ResetGSVMsg(GSV_Info_t *pGSVInfo)
{
  (void)memset(pGSVInfo->constellation, 0, (size_t)MAX_STR_LEN);
  pGSVInfo->amount = 0;
  pGSVInfo->number = 0;
  pGSVInfo->current_sats = 0;
  pGSVInfo->tot_sats = 0;
  for (int8_t i = 0; i < MAX_SAT_NUM; i++)
  {
    (void)memset(&pGSVInfo->gsv_sat_i[i], 0, sizeof(GSV_SAT_Info_t));
  }
}

/*
 * Function that checks the header of a Geofence message.
 */
static int32_t NMEA_CheckGeofenceMsg(const char header[])
{
  int32_t is_geofencemsg = 1;
  
  if (strcmp(header, "$PSTMCFGGEOFENCEOK") == 0)
  {
    is_geofencemsg = 0;
  }
  if (strcmp(header, "$PSTMCFGGEOFENCEERROR") == 0)
  {
    is_geofencemsg = 0;
  }
  if (strcmp(header, "$PSTMGEOFENCECFGOK") == 0)
  {
    is_geofencemsg = 0;
  }
  if (strcmp(header, "$PSTMGEOFENCECFGERROR") == 0)
  {
    is_geofencemsg = 0;
  }
  if (strcmp(header, "$PSTMGEOFENCESTATUS") == 0)
  {
    is_geofencemsg = 0;
  }
  if (strcmp(header, "$PSTMGEOFENCE") == 0)
  {
    is_geofencemsg = 0;
  }
  if (strcmp(header, "$PSTMGEOFENCEREQERROR") == 0)
  {
    is_geofencemsg = 0;
  }

  return is_geofencemsg;
}

/*
 *  Function that checks the header of a Odometer message.
 */
static int32_t NMEA_CheckOdoMsg(const char header[])
{
  int32_t is_odomsg = 1;
  
  if (strcmp(header, "$PSTMCFGODOOK") == 0)
  {
    is_odomsg = 0;
  }
  if (strcmp(header, "$PSTMCFGODOERROR") == 0)
  {
    is_odomsg = 0;
  }
  if (strcmp(header, "$PSTMODOSTARTOK") == 0)
  {
    is_odomsg = 0;
  }
  if (strcmp(header, "$PSTMODOSTARTERROR") == 0)
  {
    is_odomsg = 0;
  }
  if (strcmp(header, "$PSTMODOSTOPOK") == 0)
  {
    is_odomsg = 0;
  }
  if (strcmp(header, "$PSTMODOSTOPERROR") == 0)
  {
    is_odomsg = 0;
  }

  return is_odomsg;
}

/*
 * Function that checks the header of a Datalog message.
 */
static int32_t NMEA_CheckDatalogMsg(const char header[])
{
  int32_t is_datalogmsg = 1;
  
  if (strcmp(header, "$PSTMCFGLOGOK") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMCFGLOGERROR") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMLOGCREATEOK") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMLOGCREATEERROR") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMLOGSTARTOK") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMLOGSTARTERROR") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMLOGSTOPOK") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMLOGSTOPERROR") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMLOGERASEOK") == 0)
  {
    is_datalogmsg = 0;
  }
  if (strcmp(header, "$PSTMLOGERASEERROR") == 0)
  {
    is_datalogmsg = 0;
  }

  return is_datalogmsg;
}

/*
 * Function that checks the header of a List configuration message.
 */
static int32_t NMEA_CheckListMsg(const char header[])
{
  int32_t is_listmsg = 1;
  
  if (strcmp(header, "$PSTMCFGMSGLOK") == 0)
  {
    is_listmsg = 0;
  }
  if (strcmp(header, "$PSTMCFGMSGLERROR") == 0)
  {
    is_listmsg = 0;
  }

  return is_listmsg;
}

/*
 * Function that checks the header of a Save param message.
 */
static int32_t NMEA_CheckSaveparMsg(const char header[])
{
  int32_t is_savevarmsg = 1;
  
  if (strcmp(header, "$PSTMSAVEPAROK") == 0)
  {
    is_savevarmsg = 0;
  }
  if (strcmp(header, "$PSTMSAVEPARERROR") == 0)
  {
    is_savevarmsg = 0;
  }

  return is_savevarmsg;
}

/*
 * Function that checks the header of a Pass message.
 */
static int32_t NMEA_CheckPassMsg(const char header[])
{
  int32_t is_passmsg = 1;
  
  if (strcmp(header, "$PSTMSTAGPS8PASSRTN") == 0)
  {
    is_passmsg = 0;
  }
  if (strcmp(header, "$PSTMSTAGPS8PASSGENERROR") == 0)
  {
    is_passmsg = 0;
  }

  return is_passmsg;
}

/*
 * Function that scans a string with UTC Info_t and fills all fields of a
 * UTC_Info_t struct
 */
static void scan_utc(uint8_t *pUTCStr, UTC_Info_t *pUTC)
{
  pUTC->utc = strtol((char *)pUTCStr,NULL,10);
  
  pUTC->hh = (pUTC->utc / 10000);
  pUTC->mm = (pUTC->utc - (pUTC->hh * 10000)) / 100;
  pUTC->ss = pUTC->utc - ((pUTC->hh * 10000) + (pUTC->mm * 100));
  
  return;
}

/*
 * Function that executes the 'OR' operation between first two elements of a buffer
 */
static uint32_t nmea_checksum(const uint8_t buf[])
{
  return ((char2int(buf[0]) << 4) | (char2int(buf[1])));
}

/*
 * Function that converts a sequence of digits from a buffer in an integer
 */
static uint32_t digit2int(uint8_t buf[], int32_t offset, Decimal_t d)
{
  uint32_t ret = (unsigned char)0;
  uint32_t hu, hd, hc, hm;

  switch (d)
  {
  case TENS:
    hd = char2int(buf[offset]);
    hu = char2int(buf[offset+1]);
        
    ret = (hd * (unsigned)10) + hu;
    break;
    
  case HUNDREDS:
    hc = char2int(buf[offset]);
    hd = char2int(buf[offset+1]);
    hu = char2int(buf[offset+2]);
        
    ret = (hc * (unsigned)100) + (hd * (unsigned)10) + hu;
    break;
    
  case THOUSANDS:
    hm = char2int(buf[offset]);
    hc = char2int(buf[offset+1]);
    hd = char2int(buf[offset+2]);
    hu = char2int(buf[offset+3]);
        
    ret = (hm * (unsigned)1000) + (hc * (unsigned)100) + (hd * (unsigned)10) + hu;
    break;
    
  default:
    break;
 }

 return ret;
}

/*
 * Function that reads time from a timestamp string
 */
static void scan_timestamp_time(uint8_t buf[], Timestamp_Info_t *pTimestamp)
{
  /* FORMAT: HHMMSS */
  pTimestamp->hh = digit2int(buf, 0, TENS);
  pTimestamp->mm = digit2int(buf, 2, TENS);
  pTimestamp->ss = digit2int(buf, 4, TENS);
}

/*
 * Function that reads date from a timestamp string
 */
static void scan_timestamp_date(uint8_t buf[], Timestamp_Info_t *pTimestamp)
{
  /* FORMAT: YYYYMMDD */
  pTimestamp->year = digit2int(buf, 0, THOUSANDS);
  pTimestamp->month = digit2int(buf, 4, TENS);
  pTimestamp->day = digit2int(buf, 6, TENS);
}

static uint8_t GNSS_GetLen(uint8_t *buf)
{
    uint8_t  len = 0;

    while (*buf != '\0') 
    {
        len++;
        buf++;
    }

    return len;
}

void checkMaxApp()
{
  static uint32_t nAppStrMaxLen = 0;
  static uint32_t nAppStrMaxNum = 0;
  for (int8_t i = 0; i < MAX_MSG_NUM; i++)
  {
    uint32_t l = GNSS_GetLen(&app[i][0]);
    if(l>0)
    {
      if(i>nAppStrMaxNum)
      {
        nAppStrMaxNum = i;
      }
      if(l>nAppStrMaxLen)
      {
        nAppStrMaxLen = l;
      }
    }
  }
}

ParseStatus_t NMEA_ParseGPGGA(GPGGA_Info_t *pGPGGAInfo, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;

  ParseStatus_t status = PARSE_FAIL;
  
  if(NMEA != NULL) {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }

    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;

        if (strcmp((char *)app[0], "$GPGGA") == 0) {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }

    if (valid_msg == TRUE)
    {
      int32_t valid = strtol((char *)app[6], NULL, BASE);
      if((valid == 1) || (valid == 0))
      {
        pGPGGAInfo->valid = (uint8_t)valid;
      }

      scan_utc(app[1], &pGPGGAInfo->utc);
      pGPGGAInfo->xyz.lat = strtod((char *)app[2], NULL);
      pGPGGAInfo->xyz.ns = *((uint8_t*)app[3]);
      pGPGGAInfo->xyz.lon = strtod((char *)app[4], NULL);
      pGPGGAInfo->xyz.ew = *((uint8_t*)app[5]);
      pGPGGAInfo->sats = strtol((char *)app[7], NULL, BASE);
      pGPGGAInfo->acc = strtof((char *)app[8], NULL);
      pGPGGAInfo->xyz.alt = strtof((char *)app[9], NULL);
      pGPGGAInfo->xyz.mis = *((uint8_t*)app[10]);
      pGPGGAInfo->geoid.height = strtol((char *)app[11], NULL, BASE);
      pGPGGAInfo->geoid.mis = *((uint8_t*)app[12]);
      // This field is reserved
      //pGPGGAInfo->update = strtol((char *)app[13], NULL, BASE);
      pGPGGAInfo->checksum = nmea_checksum(app[15]);
      
      status = PARSE_SUCC;
    }
  }
  
  checkMaxApp();

  return status;
}

ParseStatus_t NMEA_ParseGNS(GNS_Info_t *pGNSInfo, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;
  
  if(NMEA != NULL) {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }

    for (int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (NMEA_CheckGNSMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0) {
        app[j][k] = NMEA[i];
        k++;
      }
    }
    
    if (valid_msg == TRUE)
    {
      (void)strcpy((char *)pGNSInfo->constellation, (char *)app[0]);
      scan_utc(app[1], &pGNSInfo->utc);
      pGNSInfo->xyz.lat = strtod((char *)app[2], NULL);
      pGNSInfo->xyz.ns = *((uint8_t*)app[3]);
      pGNSInfo->xyz.lon = strtod((char *)app[4], NULL);
      pGNSInfo->xyz.ew = *((uint8_t*)app[5]);
      pGNSInfo->gps_mode = *((uint8_t*)app[6]);
      pGNSInfo->glonass_mode = *((uint8_t*)app[7]);
      pGNSInfo->sats = strtol((char *)app[8], NULL, BASE);
      pGNSInfo->hdop = strtof((char *)app[9], NULL);
      pGNSInfo->xyz.alt = strtof((char *)app[10], NULL);
      pGNSInfo->geo_sep = strtof((char *)app[11], NULL);
      pGNSInfo->dgnss_age = *((uint8_t*)app[12]);
      pGNSInfo->dgnss_ref = *((uint8_t*)app[13]);
      pGNSInfo->checksum = nmea_checksum(app[14]);

      status = PARSE_SUCC;
    }
  }
  checkMaxApp();

  return status;
}
  
ParseStatus_t NMEA_ParseGPGST(GPGST_Info_t *pGPGSTInfo, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;
  
  if(NMEA != NULL) {
  
    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for (int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (strcmp((char *)app[0], "$GPGST") == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }  
    
    if (valid_msg == TRUE)
    {         
      scan_utc(app[1], &pGPGSTInfo->utc);
      pGPGSTInfo->EHPE = strtof((char *)app[2], NULL);
      pGPGSTInfo->semi_major_dev = strtof((char *)app[3], NULL);
      pGPGSTInfo->semi_minor_dev = strtof((char *)app[4], NULL);
      pGPGSTInfo->semi_major_angle = strtof((char *)app[5], NULL);
      pGPGSTInfo->lat_err_dev = strtof((char *)app[6], NULL);
      pGPGSTInfo->lon_err_dev = strtof((char *)app[7], NULL);
      pGPGSTInfo->alt_err_dev = strtof((char *)app[8], NULL);
      pGPGSTInfo->checksum = nmea_checksum(app[9]);

      status = PARSE_SUCC;
    }
  }
  checkMaxApp();

  return status;
}

ParseStatus_t NMEA_ParseGPRMC(GPRMC_Info_t *pGPRMCInfo, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;
  
  if(NMEA != NULL)
  {
  
    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for (int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (strcmp((char *)app[0], "$GPRMC") == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }  
    
    if (valid_msg == TRUE)
    {      
      scan_utc(app[1],  &pGPRMCInfo->utc);
      pGPRMCInfo->status = *((uint8_t*)app[2]);
      pGPRMCInfo->xyz.lat = strtod((char *)app[3], NULL);
      pGPRMCInfo->xyz.ns = *((uint8_t*)app[4]);
      pGPRMCInfo->xyz.lon = strtod((char *)app[5], NULL);
      pGPRMCInfo->xyz.ew = *((uint8_t*)app[6]);
      pGPRMCInfo->speed = strtof((char *)app[7], NULL);
      pGPRMCInfo->trackgood = strtof((char *)app[8], NULL);
      pGPRMCInfo->date = strtol((char *)app[9], NULL, BASE);
      pGPRMCInfo->mag_var = strtof((char *)app[10], NULL);
      pGPRMCInfo->mag_var_dir = *((uint8_t*)app[11]);
      /* WARNING: from received msg, it seems there is another data (app[12]) before the checksum */
      pGPRMCInfo->checksum = nmea_checksum(app[13]);

      status = PARSE_SUCC;
    }
  }
  checkMaxApp();

  return status;
}
         
ParseStatus_t NMEA_ParseGSA(GSA_Info_t *pGSAInfo, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;
  
  if(NMEA != NULL)
  {
  
    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for (int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)(uint8_t)(uint8_t)(uint8_t)'\n'); i++)
    {
      new_field = 0;
      
      if ((NMEA[i] == (uint8_t)(uint8_t)(uint8_t)',') || (NMEA[i] == (uint8_t)(uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (NMEA_CheckGSAMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }  
    
    if (valid_msg == TRUE)
    {
      (void)strcpy((char *)pGSAInfo->constellation, (char *)app[0]);
      pGSAInfo->operating_mode = *((uint8_t*)app[1]);
      pGSAInfo->current_mode = strtol((char *)app[2], NULL, BASE);

      int32_t *sat_prn = pGSAInfo->sat_prn;
      for (int8_t i = 0; i < MAX_SAT_NUM; i++)
      {
        *(&sat_prn[i]) = strtol((char *)app[3+i], NULL, BASE);
      }

      pGSAInfo->pdop = strtof((char *)app[15], NULL);
      pGSAInfo->hdop = strtof((char *)app[16], NULL);
      pGSAInfo->vdop = strtof((char *)app[17], NULL);
      pGSAInfo->checksum = nmea_checksum(app[18]);

      status = PARSE_SUCC;
    }
  }
  checkMaxApp();

  return status;
}

ParseStatus_t NMEA_ParseGSV(GSV_Info_t *pGSVInfo, uint8_t NMEA[])
{
  int8_t app_idx;
  int32_t gsv_idx = 0;
  int32_t new_field;
  BOOL valid_gsv_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;

  if(NMEA != NULL)
  {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for (int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (NMEA_CheckGSVMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_gsv_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }

    if (valid_gsv_msg == TRUE)
    {
      NMEA_ResetGSVMsg(pGSVInfo);

      (void)strcpy((char *)pGSVInfo->constellation, (char *)app[0]);
      pGSVInfo->amount = strtol((char *)app[1], NULL, BASE);
      pGSVInfo->number = strtol((char *)app[2], NULL, BASE);
      pGSVInfo->tot_sats = strtol((char *)app[3], NULL, BASE);
      app_idx = 4;
      for (int8_t i = 1; i <= GSV_MSG_SATS; i++)
      {
        pGSVInfo->gsv_sat_i[gsv_idx].prn = strtol((char *)app[app_idx*i], NULL, BASE);
        pGSVInfo->gsv_sat_i[gsv_idx].elev = strtol((char *)app[(app_idx*i)+1], NULL, BASE);
        pGSVInfo->gsv_sat_i[gsv_idx].azim = strtol((char *)app[(app_idx*i)+2], NULL, BASE);
        pGSVInfo->gsv_sat_i[gsv_idx].cn0 = strtol((char *)app[(app_idx*i)+3], NULL, BASE);

        if(pGSVInfo->gsv_sat_i[gsv_idx].prn != 0)
        {
          pGSVInfo->current_sats++;
        }
        gsv_idx++;
      }

      status = PARSE_SUCC;
    }

  }
  checkMaxApp();

  return status;
}

ParseStatus_t NMEA_ParsePSTMVER(PSTMVER_Info_t *pPSTMVER, uint8_t NMEA[])
{
  int8_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;
  
  if(NMEA != NULL)
  {
  
    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (strcmp((char *)app[0], "$PSTMVER") == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }
    
    if (valid_msg == TRUE)
    {
      (void)strcpy((char *)pPSTMVER->pstmver_string, (char *)app[1]);

      status = PARSE_SUCC;
    }
  }
  checkMaxApp();
  return status;
}

ParseStatus_t NMEA_ParsePSTMGeofence(Geofence_Info_t *pGeofence, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;

  if(NMEA != NULL)
  {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (NMEA_CheckGeofenceMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }
    
    if (valid_msg == TRUE)
    {
      /* Enabling */
      if (strcmp((char *)app[0], "$PSTMCFGGEOFENCEOK") == 0)
      {
        pGeofence->op = GNSS_FEATURE_EN_MSG;
        pGeofence->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMCFGGEOFENCEERROR") == 0)
      {
        pGeofence->op = GNSS_FEATURE_EN_MSG;
        pGeofence->result = GNSS_OP_ERROR;
      }
      /* Configuring */
      if (strcmp((char *)app[0], "$PSTMGEOFENCECFGOK") == 0)
      {
        pGeofence->op = GNSS_GEOFENCE_CFG_MSG;
        pGeofence->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMGEOFENCECFGERROR") == 0)
      {
        pGeofence->op = GNSS_GEOFENCE_STATUS_MSG;
        pGeofence->result = GNSS_OP_ERROR;
      }
      /* Querying Status */
      if (strcmp((char *)app[0], "$PSTMGEOFENCESTATUS") == 0)
      {
        pGeofence->op = GNSS_GEOFENCE_STATUS_MSG;
        scan_timestamp_time(app[1], &pGeofence->timestamp);
        scan_timestamp_date(app[2], &pGeofence->timestamp);

        int32_t *geofence_status = pGeofence->status;
        for(int8_t i = 0; i < MAX_GEOFENCES_NUM; i++)
        {
          *(&geofence_status[i]) = strtol((char *)app[3+i], NULL, BASE);
        }
      }
      /* Alarm Msg */
      if (strcmp((char *)app[0], "$PSTMGEOFENCE") == 0)
      {
        pGeofence->op = GNSS_GEOFENCE_ALARM_MSG;
        scan_timestamp_time(app[1], &pGeofence->timestamp);
        scan_timestamp_date(app[2], &pGeofence->timestamp);
        pGeofence->idAlarm = strtol((char *)app[3], NULL, BASE);
        pGeofence->coords.lat = strtod((char *)app[4], NULL);
        pGeofence->coords.lon = strtod((char *)app[5], NULL);
        pGeofence->coords.radius = strtod((char *)app[6], NULL);
        pGeofence->coords.distance = strtod((char *)app[7], NULL);
        pGeofence->coords.tolerance = strtod((char *)app[8], NULL);
        pGeofence->status[pGeofence->idAlarm] = strtol((char *)app[9], NULL, BASE);
      }

      status = PARSE_SUCC;
    }
  }
  
  checkMaxApp();

  return status;
}

ParseStatus_t NMEA_ParsePSTMOdo(Odometer_Info_t *pOdo, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;

  if(NMEA != NULL)
  {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (NMEA_CheckOdoMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }
    
    if (valid_msg == TRUE)
    {
      /* Enabling */
      if (strcmp((char *)app[0], "$PSTMCFGODOOK") == 0)
      {
        pOdo->op = GNSS_FEATURE_EN_MSG;
        pOdo->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMCFGODOERROR") == 0)
      {
        pOdo->op = GNSS_FEATURE_EN_MSG;
        pOdo->result = GNSS_OP_ERROR;
      }
      
      /* Start */
      if (strcmp((char *)app[0], "$PSTMODOSTARTOK") == 0)
      {
        pOdo->op = GNSS_ODO_START_MSG;
        pOdo->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMODOSTARTERROR") == 0)
      {
        pOdo->op = GNSS_ODO_START_MSG;
        pOdo->result = GNSS_OP_ERROR;
      }
      
      /* Stop */
      if (strcmp((char *)app[0], "$PSTMODOSTOPOK") == 0)
      {
        pOdo->op = GNSS_ODO_STOP_MSG;
        pOdo->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMODOSTOPERROR") == 0)
      {
        pOdo->op = GNSS_ODO_STOP_MSG;
        pOdo->result = GNSS_OP_ERROR;
      }

      status = PARSE_SUCC;
    }
  }
  
  checkMaxApp();
  return status;
}

ParseStatus_t NMEA_ParsePSTMDatalog(Datalog_Info_t *pDatalog, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;

  if(NMEA != NULL)
  {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (NMEA_CheckDatalogMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0) {
        app[j][k] = NMEA[i];
        k++;
      }
    }
    
    if (valid_msg == TRUE) {
      /* Enabling */
      if (strcmp((char *)app[0], "$PSTMCFGLOGOK") == 0)
      {
        pDatalog->op = GNSS_FEATURE_EN_MSG;
        pDatalog->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMCFGLOGERROR") == 0)
      {
        pDatalog->op = GNSS_FEATURE_EN_MSG;
        pDatalog->result = GNSS_OP_ERROR;
      }
      /* Configuring */
      if (strcmp((char *)app[0], "$PSTMLOGCREATEOK") == 0)
      {
        pDatalog->op = GNSS_DATALOG_CFG_MSG;
        pDatalog->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMLOGCREATEERROR") == 0)
      {
        pDatalog->op = GNSS_DATALOG_CFG_MSG;
        pDatalog->result = GNSS_OP_ERROR;
      }
      /* Start */
      if (strcmp((char *)app[0], "$PSTMLOGSTARTOK") == 0)
      {
        pDatalog->op = GNSS_DATALOG_START_MSG;
        pDatalog->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMLOGSTARTERROR") == 0)
      {
        pDatalog->op = GNSS_DATALOG_START_MSG;
        pDatalog->result = GNSS_OP_ERROR;
      }
      /* Stop */
      if (strcmp((char *)app[0], "$PSTMLOGSTOPOK") == 0)
      {
        pDatalog->op = GNSS_DATALOG_STOP_MSG;
        pDatalog->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMLOGSTOPERROR") == 0)
      {
        pDatalog->op = GNSS_DATALOG_STOP_MSG;
        pDatalog->result = GNSS_OP_ERROR;
      }
      /* Erase */
      if (strcmp((char *)app[0], "$PSTMLOGERASEOK") == 0)
      {
        pDatalog->op = GNSS_DATALOG_ERASE_MSG;
        pDatalog->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMLOGERASEERROR") == 0)
      {
        pDatalog->op = GNSS_DATALOG_ERASE_MSG;
        pDatalog->result = GNSS_OP_ERROR;
      }

      status = PARSE_SUCC;
    }
  }
  
  checkMaxApp();
  return status;
}

ParseStatus_t NMEA_ParsePSTMsgl(OpResult_t *pResult, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;

  if(NMEA != NULL)
  {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (NMEA_CheckListMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }
    
    if (valid_msg == TRUE)
    {
      /* Enabling */
      if (strcmp((char *)app[0], "$PSTMCFGMSGLOK") == 0)
      {
        *pResult = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMCFGMSGLERROR") == 0)
      {
        *pResult = GNSS_OP_ERROR;
      }

      status = PARSE_SUCC;
    }

  }
  checkMaxApp();
  return status;
}

ParseStatus_t NMEA_ParsePSTMSavePar(OpResult_t *pResult, uint8_t NMEA[])
{
  int32_t new_field;
  BOOL valid_msg = FALSE;
  
  ParseStatus_t status = PARSE_FAIL;

  if(NMEA != NULL)
  {

    /* clear the app[][] buffer */ 
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }
    
    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;
        
        if (NMEA_CheckSaveparMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0) {
        app[j][k] = NMEA[i];
        k++;
      }
    }
    
    if (valid_msg == TRUE)
    {
      /* Enabling */
      if (strcmp((char *)app[0], "$PSTMSAVEPAROK") == 0)
      {
        *pResult = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMSAVEPARERROR") == 0)
      {
        *pResult = GNSS_OP_ERROR;
      }

      status = PARSE_SUCC;
    }
  }
  checkMaxApp();
  return status;
}

ParseStatus_t NMEA_ParsePSTMPASSRTN(PSTMPASSRTN_Info_t *pPSTMPASSRTN, uint8_t NMEA[])
{
  int8_t new_field;
  BOOL valid_msg = FALSE;

  ParseStatus_t status = PARSE_FAIL;

  if(NMEA != NULL)
  {

    /* clear the app[][] buffer */
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }

    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;

        if (NMEA_CheckPassMsg((char *)app[0]) == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }

    if (valid_msg == TRUE)
    {
      if (strcmp((char *)app[0], "$PSTMSTAGPS8PASSRTN") == 0)
      {
        (void)strcpy((char *)pPSTMPASSRTN->deviceId, (char *)app[1]);
        (void)strcpy((char *)pPSTMPASSRTN->pwd, (char *)app[2]);
        pPSTMPASSRTN->result = GNSS_OP_OK;
      }
      if (strcmp((char *)app[0], "$PSTMSTAGPS8PASSGENERROR") == 0)
      {
        pPSTMPASSRTN->result = GNSS_OP_ERROR;
      }

      status = PARSE_SUCC;
    }
  }
  checkMaxApp();
  return status;
}

ParseStatus_t NMEA_ParsePSTMAGPSSTATUS(PSTMAGPSSTATUS_Info_t *pPSTMAGPSSTATUS, uint8_t NMEA[])
{
  int8_t new_field;
  BOOL valid_msg = FALSE;

  ParseStatus_t status = PARSE_FAIL;

  if(NMEA != NULL)
  {
    /* clear the app[][] buffer */
    for (int8_t i = 0; i < MAX_MSG_NUM; i++)
    {
      (void)memset(app[i], 0, (size_t)MAX_MSG_LEN);
    }

    for(int32_t i = 0, j = 0, k = 0; (NMEA[i] != (uint8_t)'\n'); i++)
    {
      new_field = 0;

      if ((NMEA[i] == (uint8_t)',') || (NMEA[i] == (uint8_t)'*'))
      {
        app[j][k] = (uint8_t)'\0';
        new_field = 1;

        if (strcmp((char *)app[0], "$PSTMAGPSSTATUS") == 0)
        {
          j++;
          k = 0;
          valid_msg = TRUE;
        }
        else
        {
          break;
        }
      }
      if(new_field == 0)
      {
        app[j][k] = NMEA[i];
        k++;
      }
    }

    if (valid_msg == TRUE)
    {
      (void)strcpy((char *)pPSTMAGPSSTATUS->status, (char *)app[1]);
      pPSTMAGPSSTATUS->status = strtol((char *)app[1], NULL, BASE);

      status = PARSE_SUCC;
    }
  }
  checkMaxApp();
  return status;
}

void NMEA_Copy_Data(GPGGA_Info_t *pInfo, GPGGA_Info_t GPGGAInfo)
{
  pInfo->acc          = GPGGAInfo.acc;
  pInfo->geoid.height = GPGGAInfo.geoid.height;
  pInfo->geoid.mis    = GPGGAInfo.geoid.mis;
  pInfo->sats         = GPGGAInfo.sats;
  pInfo->update       = GPGGAInfo.update;
  pInfo->utc.hh       = GPGGAInfo.utc.hh;
  pInfo->utc.mm       = GPGGAInfo.utc.mm;
  pInfo->utc.ss       = GPGGAInfo.utc.ss;
  pInfo->utc.utc      = GPGGAInfo.utc.utc;
  pInfo->valid        = GPGGAInfo.valid;
  pInfo->xyz.alt      = GPGGAInfo.xyz.alt;
  pInfo->xyz.lat      = GPGGAInfo.xyz.lat;
  pInfo->xyz.lon      = GPGGAInfo.xyz.lon;
  pInfo->xyz.ew       = GPGGAInfo.xyz.ew;
  pInfo->xyz.ns       = GPGGAInfo.xyz.ns;
  pInfo->xyz.mis      = GPGGAInfo.xyz.mis;
  pInfo->checksum     = GPGGAInfo.checksum;
}

/**
 * @brief  Function that converts a character to unsigned integer
 * @param  c        The character to convert
 * @retval The returned unsigned integer
 */
uint32_t char2int(uint8_t c)
{
  uint32_t ret = (unsigned char)0;

  if((c >= (uint8_t)'0') && (c <= (uint8_t)'9'))
  {
    ret = (unsigned char)(c - (uint8_t)'0');
  }

  if((c >= (uint8_t)'A') && (c <= (uint8_t)'F'))
  {
    ret = (unsigned char)(c - (uint8_t)'A') + (unsigned)10;
  }

  if((c >= (uint8_t)'a') && (c <= (uint8_t)'f'))
  {
    ret = (unsigned char)(c - (uint8_t)'a') + (unsigned)10;
  }

  return ret;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
