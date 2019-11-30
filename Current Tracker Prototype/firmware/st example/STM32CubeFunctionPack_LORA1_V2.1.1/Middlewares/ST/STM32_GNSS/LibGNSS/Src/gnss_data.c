/**
******************************************************************************
* @file       gnss_data.c
* @author     AST/CL
* @version    V1.0.0
* @date       Jun-2018
* @brief      Implements API to access GNSS data - LibGNSS module middleware
*
******************************************************************************
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gnss_if.h"
#include "gnss_data.h"
#include "assisted_gnss.h"
#include "gnss_geofence.h"
#include "x_nucleo_gnss1a1.h"

/* Private defines -----------------------------------------------------------*/
#define MSG_SZ (256)
#define CMD_SZ (90)

/* Private variables ---------------------------------------------------------*/

/* Variable that holds the values got by the tracking process */
static GPGGA_Info_t stored_positions[MAX_STOR_POS];
static char msg[MSG_SZ];
static char gnssCmd[CMD_SZ];

static const char geofenceCirclePosition[4][8] = {
  "Unknown",
  "Outside",
  "Boundary",
  "Inside"
};

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/* Sends a command to the GNSS module. */
void GNSS_DATA_SendCommand(void *pHandle, char *pCommand)
{
  if (pCommand[0] != 36) /* An NMEA command must begin with '$' */
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"Invalid command (an NMEA command begins with '$').\n\r");
  }
  else
  {
    snprintf(gnssCmd, CMD_SZ, "%s\r\n", pCommand);
    GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnssCmd, strlen(gnssCmd), MAX_DURATION);
  }
}

/* Puts to console data parsed from GPGGA sentence */
void GNSS_DATA_GetGGAInfo(GNSSParser_Data_t *pGNSSParser_Data)
{
  snprintf(msg, MSG_SZ, "UTC:\t\t\t[ %02ld:%02ld:%02ld ]\n\r",
           pGNSSParser_Data->gpgga_data.utc.hh, 
           pGNSSParser_Data->gpgga_data.utc.mm, 
           pGNSSParser_Data->gpgga_data.utc.ss);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);

  snprintf(msg, MSG_SZ, "Latitude:\t\t[ %.0f' %d'' %c ]\n\r",
           (pGNSSParser_Data->gpgga_data.xyz.lat - ((int)pGNSSParser_Data->gpgga_data.xyz.lat % 100)) / 100, 
           ((int)pGNSSParser_Data->gpgga_data.xyz.lat % 100), 
           pGNSSParser_Data->gpgga_data.xyz.ns);          
  GNSS_IF_ConsoleWrite((uint8_t *)msg);

  snprintf(msg, MSG_SZ, "Longitude:\t\t[ %.0f' %d'' %c ]\n\r",
           (pGNSSParser_Data->gpgga_data.xyz.lon - ((int)pGNSSParser_Data->gpgga_data.xyz.lon % 100)) / 100, 
           ((int)pGNSSParser_Data->gpgga_data.xyz.lon % 100),
           pGNSSParser_Data->gpgga_data.xyz.ew);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);

  snprintf(msg, MSG_SZ, "Satellites locked:\t[ %ld ]\n\r",
           pGNSSParser_Data->gpgga_data.sats);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);

  snprintf(msg, MSG_SZ, "Position accuracy:\t[ %.1f ]\n\r",
           pGNSSParser_Data->gpgga_data.acc);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);

  snprintf(msg, MSG_SZ, "Altitude:\t\t[ %.2f%c ]\n\r",
           pGNSSParser_Data->gpgga_data.xyz.alt, 
           (pGNSSParser_Data->gpgga_data.xyz.mis + 32));
  GNSS_IF_ConsoleWrite((uint8_t *)msg);

  snprintf(msg, MSG_SZ, "Geoid infos:\t\t[ %ld%c ]\n\r",
           pGNSSParser_Data->gpgga_data.geoid.height, 
           pGNSSParser_Data->gpgga_data.geoid.mis);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);

  snprintf(msg, MSG_SZ, "Diff update:\t\t[ %ld ]\n\r",
           pGNSSParser_Data->gpgga_data.update);  
  GNSS_IF_ConsoleWrite((uint8_t *)msg);

  GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r>");
}

/* Puts to console data of correctly parsed GPGGA sentence */
void GNSS_DATA_GetValidInfo(GNSSParser_Data_t *pGNSSParser_Data)
{
  
  if(pGNSSParser_Data->gpgga_data.valid == VALID)
  {    
    GNSS_DATA_GetGGAInfo(pGNSSParser_Data);
  }
  else
  {
    snprintf(msg, MSG_SZ,  "Last position wasn't valid.\n\n\r");
    GNSS_IF_ConsoleWrite((uint8_t *)msg);

    GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r>");
  }
}

/* Puts to console the tracking data using the result of parsed GPGGA sentence */
int32_t GNSS_DATA_TrackGotPos(GNSSParser_Data_t *pGNSSParser_Data, uint32_t how_many, uint32_t time)
{
  int32_t tracked = 0;
  for(int i = 0; i < how_many; i++)
  {
    if(pGNSSParser_Data->gpgga_data.valid != VALID)
    {
      break;
    }
    
    tracked++;
    
    snprintf(msg, MSG_SZ,  "Position %d just get.\r\n", i + 1);
    
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    if(pGNSSParser_Data->debug == DEBUG_ON)
    {
      GNSS_IF_ConsoleWrite((uint8_t *)"Debug ON.\r\n");
      
      snprintf(msg, MSG_SZ,  "UTC:\t\t\t[ %02ld:%02ld:%02ld ]\n\r",
              pGNSSParser_Data->gpgga_data.utc.hh,
              pGNSSParser_Data->gpgga_data.utc.mm, 
              pGNSSParser_Data->gpgga_data.utc.ss);
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
      snprintf(msg, MSG_SZ, "Latitude:\t\t[ %.0f' %d'' %c ]\n\r",
              (pGNSSParser_Data->gpgga_data.xyz.lat - ((int)pGNSSParser_Data->gpgga_data.xyz.lat % 100)) / 100, 
              ((int)pGNSSParser_Data->gpgga_data.xyz.lat % 100), 
              pGNSSParser_Data->gpgga_data.xyz.ns);          
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
      snprintf(msg, MSG_SZ, "Longitude:\t\t[ %.0f' %d'' %c ]\n\r",
              (pGNSSParser_Data->gpgga_data.xyz.lon - ((int)pGNSSParser_Data->gpgga_data.xyz.lon % 100)) / 100, 
              ((int)pGNSSParser_Data->gpgga_data.xyz.lon % 100),
              pGNSSParser_Data->gpgga_data.xyz.ew);
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
      snprintf(msg, MSG_SZ, "Satellites locked:\t[ %ld ]\n\r",
              pGNSSParser_Data->gpgga_data.sats);
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
      snprintf(msg, MSG_SZ, "Position accuracy:\t[ %.1f ]\n\r",
              pGNSSParser_Data->gpgga_data.acc);
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
      snprintf(msg, MSG_SZ, "Altitude:\t\t[ %.2f%c ]\n\r",
              pGNSSParser_Data->gpgga_data.xyz.alt, 
              (pGNSSParser_Data->gpgga_data.xyz.mis + 32));
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
      snprintf(msg, MSG_SZ, "Geoid infos:\t\t[ %ld%c ]\n\r",
              pGNSSParser_Data->gpgga_data.geoid.height, 
              pGNSSParser_Data->gpgga_data.geoid.mis);
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
      snprintf(msg, MSG_SZ, "Diff update:\t\t[ %ld ]\n\r",
              pGNSSParser_Data->gpgga_data.update);  
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
      GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r");
    }
    NMEA_Copy_Data(&stored_positions[i], pGNSSParser_Data->gpgga_data);
    if(time != 0) {
      GNSS_IF_Delay(time * 1000);
    }
  }
  return tracked;
}

/*  Puts to console all the position got by a tracking position process */
void GNSS_DATA_PrintTrackedPositions(int how_many)
{  
  for(int i = 0; i < how_many; i++)
  {
    snprintf(msg, MSG_SZ,  "Position n. %d:\r\n", i + 1);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ,  "UTC:\t\t\t[ %02ld:%02ld:%02ld ]\n\r",
            stored_positions[i].utc.hh, stored_positions[i].utc.mm, stored_positions[i].utc.ss);                                 
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ,  "Latitude:\t\t[ %.0f' %d'' %c ]\n\r",
            (stored_positions[i].xyz.lat - ((int)stored_positions[i].xyz.lat % 100)) / 100, 
            ((int)stored_positions[i].xyz.lat % 100), 
            stored_positions[i].xyz.ns);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ,  "Longitude:\t\t[ %.0f' %d'' %c ]\n\r",
            (stored_positions[i].xyz.lon - ((int)stored_positions[i].xyz.lon % 100)) / 100, 
            ((int)stored_positions[i].xyz.lon % 100), 
            stored_positions[i].xyz.ew);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ,  "Satellites locked:\t[ %ld ]\n\r",
            stored_positions[i].sats);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ,  "Position accuracy:\t[ %.1f ]\n\r", 
            stored_positions[i].acc);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ,  "Altitude:\t\t[ %.2f%c ]\n\r", 
            stored_positions[i].xyz.alt, 
            (stored_positions[i].xyz.mis + 32));
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ,  "Geoid infos:\t\t[ %ld%c ]\n\r",
            stored_positions[i].geoid.height, 
            stored_positions[i].geoid.mis);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ,  "Diff update:\t\t[ %ld ]\n\r",
            stored_positions[i].update);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);

    GNSS_IF_ConsoleWrite((uint8_t *)"\r\n\n>");
  }
}

/* Puts to console the info about Fix data for single or combined satellite navigation system. */
void GNSS_DATA_GetGNSInfo(GNSSParser_Data_t *pGNSSParser_Data)
{
  GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
  
  snprintf(msg, MSG_SZ,  "Constellation:\t\t[ %s ]\n",
          pGNSSParser_Data->gns_data.constellation);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  if (strcmp((void*)pGNSSParser_Data->gns_data.constellation, "$GPGNS") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only GPS constellation is enabled\n\r");  
  }
  else if (strcmp((void*)pGNSSParser_Data->gns_data.constellation, "$GLGNS") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only GLONASS constellation is enabled\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gns_data.constellation, "$GAGNS") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only GALILEO constellation is enabled\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gns_data.constellation, "$BDGNS") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only BEIDOU constellation is enabled\n\r");    
  }
  else if (strcmp((void*)pGNSSParser_Data->gns_data.constellation, "$QZGNS") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only QZSS constellation is enabled\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gns_data.constellation, "$GNGSV") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- message to report all satellites for all enabled constellations\n\r");   
  }
  
  snprintf(msg, MSG_SZ,  "UTC:\t\t\t[ %02ld:%02ld:%02ld ]\n\r",
          pGNSSParser_Data->gns_data.utc.hh, 
          pGNSSParser_Data->gns_data.utc.mm, 
          pGNSSParser_Data->gns_data.utc.ss);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "Latitude:\t\t[ %.0f' %d'' %c ]\n\r",
          (pGNSSParser_Data->gns_data.xyz.lat - ((int)pGNSSParser_Data->gns_data.xyz.lat % 100)) / 100, 
          (int)pGNSSParser_Data->gns_data.xyz.lat % 100,
          pGNSSParser_Data->gns_data.xyz.ns);          
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "Longitude:\t\t[ %.0f' %d'' %c ]\n\r",
          (pGNSSParser_Data->gns_data.xyz.lon - ((int)pGNSSParser_Data->gns_data.xyz.lon % 100)) / 100, 
          (int)pGNSSParser_Data->gns_data.xyz.lon % 100,
          pGNSSParser_Data->gns_data.xyz.ew);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "Satellites locked:\t[ %ld ]\n\r",
          pGNSSParser_Data->gns_data.sats);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "HDOP:\t\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gns_data.hdop);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
  snprintf(msg, MSG_SZ, "Altitude:\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gns_data.xyz.alt);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "Geoid infos:\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gns_data.geo_sep);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r>");
}

/* Puts to console the info about GPS Pseudorange Noise Statistics */
void GNSS_DATA_GetGPGSTInfo(GNSSParser_Data_t *pGNSSParser_Data)
{  
  GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
    
  snprintf(msg, MSG_SZ,  "UTC:\t\t\t[ %02ld:%02ld:%02ld ]\n\r",
          pGNSSParser_Data->gpgst_data.utc.hh, 
          pGNSSParser_Data->gpgst_data.utc.mm, 
          pGNSSParser_Data->gpgst_data.utc.ss);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "EHPE:\t\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gpgst_data.EHPE);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "Semi-major Dev:\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gpgst_data.semi_major_dev);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "Semi-minor Dev:\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gpgst_data.semi_minor_dev);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "Semi-maior Angle:\t[ %.01f ]\n\r",
          pGNSSParser_Data->gpgst_data.semi_major_angle);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
      
  snprintf(msg, MSG_SZ, "Lat Err Dev:\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gpgst_data.lat_err_dev);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "Lon Err Dev:\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gpgst_data.lon_err_dev);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "Alt Err Dev:\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gpgst_data.alt_err_dev);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r>");

  return;
}

/* Puts to console the info about Recommended Minimum Specific GPS/Transit data got by the most recent reception process. */
void GNSS_DATA_GetGPRMCInfo(GNSSParser_Data_t *pGNSSParser_Data)
{
  GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
    
  snprintf(msg, MSG_SZ,  "UTC:\t\t\t\t[ %02ld:%02ld:%02ld ]\n\r",
          pGNSSParser_Data->gprmc_data.utc.hh, 
          pGNSSParser_Data->gprmc_data.utc.mm, 
          pGNSSParser_Data->gprmc_data.utc.ss);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "Status:\t\t\t\t[ %c ]\t\t",
          pGNSSParser_Data->gprmc_data.status);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  if (pGNSSParser_Data->gprmc_data.status == 'A')
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- Valid (reported in 2D and 3D fix conditions)\n\r");
  }
  else if (pGNSSParser_Data->gprmc_data.status == 'V')
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- Warning (reported in NO FIX conditions)\n\r");
  }
  else
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- Unknown status\n\r");
  }
    
  snprintf(msg, MSG_SZ, "Latitude:\t\t\t[ %.0f' %02d'' %c ]\n\r",
          (pGNSSParser_Data->gprmc_data.xyz.lat - ((int)pGNSSParser_Data->gprmc_data.xyz.lat % 100)) / 100, 
          ((int)pGNSSParser_Data->gprmc_data.xyz.lat % 100), 
          pGNSSParser_Data->gprmc_data.xyz.ns);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "Longitude:\t\t\t[ %.0f' %02d'' %c ]\n\r",
          (pGNSSParser_Data->gprmc_data.xyz.lon - ((int)pGNSSParser_Data->gprmc_data.xyz.lon % 100)) / 100, 
          ((int)pGNSSParser_Data->gprmc_data.xyz.lon % 100),
          pGNSSParser_Data->gprmc_data.xyz.ew);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "Speed over ground (knots):\t[ %.01f ]\n\r",
          pGNSSParser_Data->gprmc_data.speed);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "Trackgood:\t\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gprmc_data.trackgood);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "Date (ddmmyy):\t\t\t[ %ld ]\n\r",
          pGNSSParser_Data->gprmc_data.date);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  snprintf(msg, MSG_SZ, "Magnetic Variation:\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gprmc_data.mag_var);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  if ((pGNSSParser_Data->gprmc_data.mag_var_dir != 'E') &&
      (pGNSSParser_Data->gprmc_data.mag_var_dir != 'W')) {
    snprintf(msg, MSG_SZ, "Magnetic Var. Direction:\t[ - ]\n\r");
  }
  else {
    snprintf(msg, MSG_SZ, "Magnetic Var. Direction:\t[ %c ]\n\r",
          pGNSSParser_Data->gprmc_data.mag_var_dir);
  }
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r>");

  return;
}

/* Puts to console the info about GSA satellites got by the most recent reception process. */
void GNSS_DATA_GetGSAInfo(GNSSParser_Data_t *pGNSSParser_Data)
{
  GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
  
  snprintf(msg, MSG_SZ,  "Constellation:\t\t[ %s ]\t",
          pGNSSParser_Data->gsa_data.constellation);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  if (strcmp((void*)pGNSSParser_Data->gsa_data.constellation, "$GPGSA") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only GPS constellation is enabled\n\r");    
  }
  else if (strcmp((void*)pGNSSParser_Data->gsa_data.constellation, "$GLGSA") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only GLONASS constellation is enabled\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gsa_data.constellation, "$GAGSA") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only GALILEO constellation is enabled\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gsa_data.constellation, "$BDGSA") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- only BEIDOU constellation is enabled\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gsa_data.constellation, "$GNGSA") == 0)
  {
     GNSS_IF_ConsoleWrite((uint8_t *)"-- more than one constellation is enabled\n\r");   
  }
  
  snprintf(msg, MSG_SZ,  "Operating Mode:\t\t[ %c ]\t\t",
          pGNSSParser_Data->gsa_data.operating_mode);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  if (pGNSSParser_Data->gsa_data.operating_mode == 'A')
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- Auto (2D/3D)\n\r");
  }
  else if (pGNSSParser_Data->gsa_data.operating_mode == 'M')
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- Manual\n\r");
  }
  
  snprintf(msg, MSG_SZ, "Current Mode:\t\t[ %ld ]\t\t",
          pGNSSParser_Data->gsa_data.current_mode);          
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  if (pGNSSParser_Data->gsa_data.current_mode == 1)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- no fix available\n\r");
  }
  else if (pGNSSParser_Data->gsa_data.current_mode == 2)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- 2D\n\r");
  }
  else if (pGNSSParser_Data->gsa_data.current_mode == 3)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- 3D\n\r");
  }
  
  for (uint8_t i=0; i<12; i++)
  {  
    snprintf(msg, MSG_SZ, "SatPRN%02d:\t\t[ %ld ]\n\r", i+1,
            pGNSSParser_Data->gsa_data.sat_prn[i]);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  
  snprintf(msg, MSG_SZ, "PDOP:\t\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gsa_data.pdop);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "HDOP:\t\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gsa_data.hdop);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "VDOP:\t\t\t[ %.01f ]\n\r",
          pGNSSParser_Data->gsa_data.vdop);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r>");

  return;
}

/* Puts to console the info about GSV satellites got by the most recent reception process. */
void GNSS_DATA_GetGSVInfo(GNSSParser_Data_t *pGNSSParser_Data)
{
  uint8_t i;
  uint8_t tot_sats = pGNSSParser_Data->gsv_data.tot_sats;
  uint8_t current_sats = pGNSSParser_Data->gsv_data.current_sats;
  int amount = pGNSSParser_Data->gsv_data.amount;
  int number = pGNSSParser_Data->gsv_data.number;
  
  char degree_ext_ASCII_char = 248;
  
  GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
  
  snprintf(msg, MSG_SZ,  "Constellation:\t\t[ %s ]\t",
          pGNSSParser_Data->gsv_data.constellation);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  if (strcmp((void*)pGNSSParser_Data->gsv_data.constellation, "$GPGSV") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- message to report all GPS satellites\n\r");    
  }
  else if (strcmp((void*)pGNSSParser_Data->gsv_data.constellation, "$GLGSV") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- message to report all GLONASS satellites\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gsv_data.constellation, "$GAGSV") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- message to report all GALILEO satellites\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gsv_data.constellation, "$BDGSV") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- message to report all BEIDOU satellites\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gsv_data.constellation, "$QZGSV") == 0)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"-- message to report all QZSS satellites\n\r");
  }
  else if (strcmp((void*)pGNSSParser_Data->gsv_data.constellation, "$GNGSV") == 0)
  {
     GNSS_IF_ConsoleWrite((uint8_t *)"-- message to report all satellites for all enabled constellations\n\r");   
  }
  
  snprintf(msg, MSG_SZ, "GSV message:\t\t[ %d of %d ]\n\r", number, amount);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  snprintf(msg, MSG_SZ, "Num of Satellites:\t[ %ld of %d ]\n\r", pGNSSParser_Data->gsv_data.current_sats, tot_sats);
  GNSS_IF_ConsoleWrite((uint8_t *)msg);
  
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\r");
  
  for (i=0; i<current_sats; i++)
  {
    snprintf(msg, MSG_SZ, "Sat%02dPRN:\t\t[ %03ld ]\n\r", i+1+(number-1)*GSV_MSG_SATS,
            pGNSSParser_Data->gsv_data.gsv_sat_i[i].prn);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ, "Sat%02dElev (%c):\t\t[ %03ld ]\n\r", i+1+(number-1)*GSV_MSG_SATS, degree_ext_ASCII_char,
            pGNSSParser_Data->gsv_data.gsv_sat_i[i].elev);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ, "Sat%02dAzim (%c):\t\t[ %03ld ]\n\r", i+1+(number-1)*GSV_MSG_SATS, degree_ext_ASCII_char,
            pGNSSParser_Data->gsv_data.gsv_sat_i[i].azim);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    snprintf(msg, MSG_SZ, "Sat%02dCN0 (dB):\t\t[ %03ld ]\n\r", i+1+(number-1)*GSV_MSG_SATS,
            pGNSSParser_Data->gsv_data.gsv_sat_i[i].cn0);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);  
    
    GNSS_IF_ConsoleWrite((uint8_t *)"\n\r");
  }
  
  GNSS_IF_ConsoleWrite((uint8_t *)"\r\n>");
  
}

/* Puts to console the info about FW version. */
void GNSS_DATA_GetPSTMVerInfo(GNSSParser_Data_t *pGNSSParser_Data)
{
  if(strlen((void *)pGNSSParser_Data->pstmver_data.pstmver_string) != 0 )
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
    snprintf(msg, MSG_SZ,  "Version Info:\t\t[ %s ]\t",
            pGNSSParser_Data->pstmver_data.pstmver_string);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r");
  }
  else
  {
    snprintf(msg, MSG_SZ,  "No version info available.\n\n\r");
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\r>");
}

/* Puts to console the geofence infos each time an alarm is received. */
void GNSS_DATA_GetGeofenceInfo(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data)
{  
  if(pGNSSParser_Data->geofence_data.op == GNSS_FEATURE_EN_MSG)
  {
    if(pGNSSParser_Data->geofence_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Enabling Geofence:\t[ %s ] (Saving params...)\t",
              "EN GEOFENCE OK");
      GNSS_DATA_SendCommand(pHandle, "$PSTMSAVEPAR");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Enabling Geofence:\t[ %s ]\t",
              "EN GEOFENCE ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  
  if(pGNSSParser_Data->geofence_data.op == GNSS_GEOFENCE_CFG_MSG)
  {
    if(pGNSSParser_Data->geofence_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Geofence Configuration:\t[ %s ]\t",
              "GEOFENCE CFG OK");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Geofence Configuration:\t[ %s ]\t",
              "GEOFENCE CFG ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  
  if(pGNSSParser_Data->geofence_data.op == GNSS_GEOFENCE_STATUS_MSG)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
    snprintf(msg, MSG_SZ,  "Time/Date:\t\t%02ld:%02ld:%02ld %02ld/%02ld/%04ld\n",
            pGNSSParser_Data->geofence_data.timestamp.hh,
            pGNSSParser_Data->geofence_data.timestamp.mm,
            pGNSSParser_Data->geofence_data.timestamp.ss,
            pGNSSParser_Data->geofence_data.timestamp.day,
            pGNSSParser_Data->geofence_data.timestamp.month,
            pGNSSParser_Data->geofence_data.timestamp.year);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    for(uint8_t i = 0; i<MAX_GEOFENCES_NUM; i++)
    {
      snprintf(msg, MSG_SZ,  "Position circle[%d]:\t%s\n",
              i, geofenceCirclePosition[pGNSSParser_Data->geofence_data.status[i]]);
      GNSS_IF_ConsoleWrite((uint8_t *)msg);
    }
  }
  
  if(pGNSSParser_Data->geofence_data.op == GNSS_GEOFENCE_ALARM_MSG)
  {
    GNSS_IF_ConsoleWrite((uint8_t *)"\r\nGeofence status:\r\n");
    // Print ID - Status
    int idAlarm = pGNSSParser_Data->geofence_data.idAlarm;
    snprintf(msg, MSG_SZ,  "[Circle %d - %s]\t", idAlarm,
            geofenceCirclePosition[pGNSSParser_Data->geofence_data.status[idAlarm]]);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    // Print time date
    snprintf(msg, MSG_SZ,  "%02ld:%02ld:%02ld %02ld/%02ld/%04ld\n",
            pGNSSParser_Data->geofence_data.timestamp.hh,
            pGNSSParser_Data->geofence_data.timestamp.mm,
            pGNSSParser_Data->geofence_data.timestamp.ss,
            pGNSSParser_Data->geofence_data.timestamp.day,
            pGNSSParser_Data->geofence_data.timestamp.month,
            pGNSSParser_Data->geofence_data.timestamp.year);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\r>");
}

/* Puts to console the info about Odometer. */
void GNSS_DATA_GetOdometerInfo(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data)
{ 
  if(pGNSSParser_Data->odo_data.op == GNSS_FEATURE_EN_MSG)
  {
    if(pGNSSParser_Data->odo_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Enabling Odometer:\t[ %s ] (Saving params...)\t",
              "EN ODOMETER OK");
      GNSS_DATA_SendCommand(pHandle, "$PSTMSAVEPAR");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Enabling Odometer:\t[ %s ]\t",
              "EN ODOMETER ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }

  if(pGNSSParser_Data->odo_data.op == GNSS_ODO_START_MSG)
  {
    if(pGNSSParser_Data->odo_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Odometer Operation:\t[ %s ]\t",
          "START ODOMETER OK");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Odometer Operation:\t[ %s ]\t",
          "START ODOMETER ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  
  if(pGNSSParser_Data->odo_data.op == GNSS_ODO_STOP_MSG)
  {
    if(pGNSSParser_Data->odo_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Odometer Operation:\t[ %s ]\t",
          "STOP ODOMETER OK");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Odometer Operation:\t[ %s ]\t",
          "STOP ODOMETER ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\r>");

  return;
}

/* Puts to console the info about Datalog. */
void GNSS_DATA_GetDatalogInfo(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data)
{ 
  if(pGNSSParser_Data->datalog_data.op == GNSS_FEATURE_EN_MSG)
  {
    if(pGNSSParser_Data->datalog_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Enabling Datalog:\t[ %s ] (Saving params...)\t",
              "EN DATALOG OK");
      GNSS_DATA_SendCommand(pHandle, "$PSTMSAVEPAR");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Enabling Datalog:\t[ %s ]\t",
              "EN DATALOG ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }

  if(pGNSSParser_Data->datalog_data.op == GNSS_DATALOG_CFG_MSG)
  {
    if(pGNSSParser_Data->datalog_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Datalog Configuring:\t\t[ %s ]\t",
            "DATALOG CFG OK");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Datalog Configuring:\t\t[ %s ]\t",
            "DATALOG CFG ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }

  if(pGNSSParser_Data->datalog_data.op == GNSS_DATALOG_START_MSG)
  {
    if(pGNSSParser_Data->datalog_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Datalog Start:\t\t[ %s ]\t",
            "DATALOG START OK");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Datalog Start:\t\t[ %s ]\t",
            "DATALOG START ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }

  if(pGNSSParser_Data->datalog_data.op == GNSS_DATALOG_STOP_MSG)
  {
    if(pGNSSParser_Data->datalog_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Datalog Stop:\t\t[ %s ]\t",
            "DATALOG STOP OK");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Datalog Stop:\t\t[ %s ]\t",
            "DATALOG STOP ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }

  if(pGNSSParser_Data->datalog_data.op == GNSS_DATALOG_ERASE_MSG)
  {
    if(pGNSSParser_Data->datalog_data.result == GNSS_OP_OK)
    {
      snprintf(msg, MSG_SZ,  "Datalog Erase:\t\t[ %s ]\t",
            "DATALOG ERASE OK");
    }
    else
    {
      snprintf(msg, MSG_SZ,  "Datalog Erase:\t\t[ %s ]\t",
            "DATALOG ERASE ERROR");
    }
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\r>");
  
}

 /* Puts to console the confirmation of an updated message list. */
void GNSS_DATA_GetMsglistAck(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data)
{ 
  if(pGNSSParser_Data->result == GNSS_OP_OK)
  {
    GNSS_DATA_SendCommand(pHandle, "$PSTMSAVEPAR");
    snprintf(msg, MSG_SZ,  "Saving NMEA msg configuration...\t");
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    GNSS_IF_ConsoleWrite((uint8_t *)"\n\r>");
  }
}

/* Puts to console the confirmation after saving params.
   NOTE: GNSS must be reset for the new saved params to have effect.
*/
void GNSS_DATA_GetGNSSAck(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data)
{ 
  if(pGNSSParser_Data->result == GNSS_OP_OK) {
    GNSS_Bus_Reset(pHandle);
    snprintf(msg, MSG_SZ,  " Resetting...\t");
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    GNSS_IF_ConsoleWrite((uint8_t *)"\n\r>");    
  }
}

/* Configures the message list. */
void GNSS_DATA_CfgMessageList(void *pHandle, int lowMask, int highMask)
{
  /* See CDB-ID 201 - This LOW_BITS Mask enables the following messages:
   * 0x1 $GPGNS Message
   * 0x2 $GPGGA Message
   * 0x4 $GPGSA Message
   * 0x8 $GPGST Message
   * 0x40 $GPRMC Message
   * 0x80000 $GPGSV Message
   * 0x100000 $GPGLL Message
   */
//  int lowMask = 0x000000;

  snprintf(gnssCmd, CMD_SZ, "$PSTMCFGMSGL,%d,%d,%x,%x",
          0, /*NMEA 0*/
          1, /*Rate*/
          lowMask,
          highMask);

  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to enable/disable Geofence */
void GNSS_DATA_EnableGeofence(void *pHandle, int toggle)
{
  //$PSTMCFGGEOFENCE,<en>,<tol>*<checksum><cr><lf>
  snprintf(gnssCmd, CMD_SZ, "$PSTMCFGGEOFENCE,%d,%d",toggle,1);
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Configures Geofence */
void GNSS_DATA_ConfigGeofence(void *pHandle, void* gnss_geofence)
{
  snprintf(gnssCmd, CMD_SZ, "$PSTMGEOFENCECFG,%d,%d,%d,%lf,%lf,%lf",
          ((GNSSGeofence_t*)gnss_geofence)->id,
          ((GNSSGeofence_t*)gnss_geofence)->enabled,
          ((GNSSGeofence_t*)gnss_geofence)->tolerance,
          ((GNSSGeofence_t*)gnss_geofence)->lat,
          ((GNSSGeofence_t*)gnss_geofence)->lon,
          ((GNSSGeofence_t*)gnss_geofence)->radius);
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to enable/disable odometer. */
void GNSS_DATA_EnableOdo(void *pHandle, int toggle)
{
  //$PSTMCFGODO,<en>,<enmsg>,<alarm>*<checksum><cr><lf>
  snprintf(gnssCmd, CMD_SZ, "$PSTMCFGODO,%d,1,1",toggle);
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to start odometer. */
void GNSS_DATA_StartOdo(void *pHandle, unsigned alarmDistance)
{
  snprintf(gnssCmd, CMD_SZ, "$PSTMODOSTART,%08x", alarmDistance);
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to stop odometer. */
void GNSS_DATA_StopOdo(void *pHandle)
{
  snprintf(gnssCmd, CMD_SZ, "$PSTMODOSTOP");
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to enable/disable Datalog. */
void GNSS_DATA_EnableDatalog(void *pHandle, int toggle)
{
  //$PSTMCFGLOG,<en>,<circ>,<rectype>,<oneshot>,<rate>,<speed>,<dist>*<checksum><cr><lf>
  snprintf(gnssCmd, CMD_SZ, "$PSTMCFGLOG,%d,%d,%d,%d,%u,%u,%u",
          toggle, //Enable/Disable the log
          1, //Enable/Disable circular mode
          1, //Record type
          0, //Enable/Disable one shot mode
          5, //time interval in seconds between two consecutive logged records
          0, //minimum speed threshold
          0  //distance threshold
          );
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to configure Datalog. */
void GNSS_DATA_ConfigDatalog(void *pHandle, void *gnss_datalog)
{
  //$PSTMLOGCREATE,<cfg>,<min-rate>,<min-speed>,<min-position>,<logmask>*<checksum><cr><lf>
  snprintf(gnssCmd, CMD_SZ, "$PSTMLOGCREATE,%03x,%u,%u,%u,%d",
          (((GNSSDatalog_t*)gnss_datalog)->enableBufferFullAlarm)<<1|(((GNSSDatalog_t*)gnss_datalog)->enableCircularBuffer),
          ((GNSSDatalog_t*)gnss_datalog)->minRate,
          ((GNSSDatalog_t*)gnss_datalog)->minSpeed,
          ((GNSSDatalog_t*)gnss_datalog)->minPosition,
          ((GNSSDatalog_t*)gnss_datalog)->logMask
          );
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to start Datalog. */
void GNSS_DATA_StartDatalog(void *pHandle)
{
  snprintf(gnssCmd, CMD_SZ, "$PSTMLOGSTART");
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to stop Datalog. */
void GNSS_DATA_StopDatalog(void *pHandle)
{
  snprintf(gnssCmd, CMD_SZ, "$PSTMLOGSTOP");
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Sends a command to erase Datalog. */
void GNSS_DATA_EraseDatalog(void *pHandle)
{
  snprintf(gnssCmd, CMD_SZ, "$PSTMLOGERASE");
  
  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

#if ASSISTED_GNSS

/* Requests the generation of a password to access the A-GNSS server */
void GNSS_DATA_PassGen(void *pHandle, uint32_t currentTime)
{
  currentTime = currentTime - ((365 * 10 + 7) * 24 * 60 * 60); // Current GPS time (approx)
  //printf("Gps time [sec] : %ld\n", currentTime);
  //$PSTMSTAGPS8PASSGEN,<time>,<Ven ID>,<Model ID>*<checksum><cr><lf>
  snprintf(gnssCmd, CMD_SZ, "$PSTMSTAGPS8PASSGEN,%ld,%s,%s",currentTime,vendorId,modelId);

  GNSS_DATA_SendCommand(pHandle, gnssCmd);
}

/* Puts to console the info about Password generation for A-GNSS. */
void GNSS_DATA_GetPSTMPassInfo(GNSSParser_Data_t *pGNSSParser_Data)
{
  if(pGNSSParser_Data->pstmpass_data.result == GNSS_OP_OK)
  {
    snprintf(msg, MSG_SZ, "Password Generation:\t[ %s ]\t",
             "PASS GEN OK");
    GNSS_IF_ConsoleWrite((uint8_t *)msg);

    /* DeviceId */
    GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
    snprintf(msg, MSG_SZ, "Device Id:\t[ %s ]\t",
             pGNSSParser_Data->pstmpass_data.deviceId);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);

    /* Password */
    GNSS_IF_ConsoleWrite((uint8_t *)"\r\n");
    snprintf(msg, MSG_SZ, "Password:\t[ %s ]\t",
             pGNSSParser_Data->pstmpass_data.pwd);
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
    
    GNSS_IF_ConsoleWrite((uint8_t *)"\n\n\r");
  }
  else
  {
    snprintf(msg, MSG_SZ, "Password Generation:\t[ %s ]\t",
             "PASS GEN ERROR");
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\r>");

  return;
}

/* Puts to console the status of the STAGPS processing (A-GNSS). */
void GNSS_DATA_GetPSTMAGPSStatus(GNSSParser_Data_t *pGNSSParser_Data)
{
  if(pGNSSParser_Data->pstmagps_status.status != 0)
  {
    snprintf(msg, MSG_SZ, "STAGPS processing is still ongoing\t");
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  else
  {
    snprintf(msg, MSG_SZ, "STAGPS processing is completed\t");
    GNSS_IF_ConsoleWrite((uint8_t *)msg);
  }
  
  GNSS_IF_ConsoleWrite((uint8_t *)"\n\r>");

  return;
}

#endif /*ASSISTED_GNSS */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
