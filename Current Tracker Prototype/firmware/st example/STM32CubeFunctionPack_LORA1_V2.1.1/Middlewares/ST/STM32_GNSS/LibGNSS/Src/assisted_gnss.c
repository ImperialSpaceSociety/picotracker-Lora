/**
******************************************************************************
* @file       assisted_gnss.c
* @author     AST/CL
* @version    V1.0.0
* @date       Jun-2018
* @brief      Implements Assisted GNSS API
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
#include "assisted_gnss.h"
#include "gnss_if.h"

/* Global variables ----------------------------------------------------------*/

const uint8_t vendorId[] = "ZYDLLXxEH94dEeX2";
const uint8_t modelId[] = "MYST";

/* Private functions ---------------------------------------------------------*/

// Converts a byte to 2-char ASCII hexadecimal format
static void byte2hex(char hex[2], unsigned char byte)
{
  const char nibble2hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  unsigned char l, h;

  l = byte % 16;
  h = byte / 16;
  hex[0] = nibble2hex[h];
  hex[1] = nibble2hex[l];
}

// Extracts a byte from a byte array at specified position, where the position is expressed in bit
static void extract_byte(unsigned char* byte, unsigned char* buffer, unsigned long pos)
{
  unsigned int byte_pos, bit_pos, i;
  unsigned char bit;

  byte_pos = pos / 8;
  bit_pos = pos % 8;
  *byte = 0;

  for (i = 0; i < 8; i++)
  {
    if (i + bit_pos < 8)
    {
      bit = (buffer[byte_pos] & (1 << (7 - (i + bit_pos)))) != 0 ? 1 : 0;
    }
    else
    {
      bit = (buffer[byte_pos + 1] & (1 << (7 - (i + bit_pos - 8)))) != 0 ? 1 : 0;
    }
    *byte += bit << (7 - i);
  }
}

// Calculates NMEA checksum
static char checksum(const char *string)
{
  int index = 1;
  int checksum = 0;

  for (int i = index; string[i] != '\0'; i++)
  {
    checksum ^= string[i];
  }

  return checksum;
}

// Decodes the seed header returning initial time, current time, clock id, version of the seed and the number of satellites contained in the seed
static int decode_first_block_seed(char output_first_blk_seed[SINGLE_SEED_FIRST_BLOCK_BIT_LEN / 4 + 3],
                            unsigned char *seed_buffer)
{
  unsigned char seed_byte;
  unsigned long i;

  unsigned long current_pos = 0;

  memset(output_first_blk_seed, 0, SINGLE_SEED_FIRST_BLOCK_BIT_LEN / 4 + 3);
  for (i = 0; i < SINGLE_SEED_FIRST_BLOCK_BIT_LEN; i += 8)
  {
    extract_byte(&seed_byte, seed_buffer, current_pos);
    byte2hex(&output_first_blk_seed[i / 4], seed_byte);
    if (SINGLE_SEED_FIRST_BLOCK_BIT_LEN - i > 8)
    {
      current_pos += 8;
    }
    else
    {
      current_pos += SINGLE_SEED_FIRST_BLOCK_BIT_LEN - i;
      return current_pos;
    }
  }
  return 0;
}

// Decodes succeeding seed blocks
static void decode_next_blocks_seed(char output_seed[SINGLE_SEED_BIT_LEN / 4 + 4],
                             unsigned char *seed_buffer,
                             unsigned long *current_pos)
{
  unsigned char seed_byte;
  unsigned long i;

  memset(output_seed, 0, SINGLE_SEED_BIT_LEN / 4 + 4);
  for (i = 0; i < SINGLE_SEED_BIT_LEN; i += 8)
  {
    extract_byte(&seed_byte, seed_buffer, *current_pos);
    byte2hex(&output_seed[i / 4], seed_byte);
    if (SINGLE_SEED_BIT_LEN - i > 8)
    {
      *current_pos += 8;
    }
    else
    {
      *current_pos += SINGLE_SEED_BIT_LEN - i;
    }
  }
}

/* Public functions ----------------------------------------------------------*/

/* Builds the Json payload for rxn request */
int32_t A_GNSS_BuildJsonReq(char *JsonData, int seedMask, int *seedSize)
{
  if(JsonData == NULL)
  {
    return -1;
  }

  //GNSS_DATA_IF_ConsoleWrite((uint8_t *)"DEFAULT_CONSTELLATION\r\n");

  if( (seedMask | GPS_CONSTELLATION) == GPS_CONSTELLATION)  // only GPS
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"gps\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_8K;
  }
  else if( (seedMask | GLO_CONSTELLATION) == GLO_CONSTELLATION)  // only GLO
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"glonass\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_6K;
  }
  else if( (seedMask | GAL_CONSTELLATION) == GAL_CONSTELLATION)  // only GAL
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"galileo\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_4K;
  }
  else if( (seedMask | BEI_CONSTELLATION) == BEI_CONSTELLATION) // only BEI
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"beidou\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_4K;
  }
  else if( (seedMask | (GPS_CONSTELLATION | GLO_CONSTELLATION)) == (GPS_CONSTELLATION | GLO_CONSTELLATION)) // GPS + GLO
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"gps\", \"glonass\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_15K;
  }
  else if( (seedMask | (GPS_CONSTELLATION | GAL_CONSTELLATION)) == (GPS_CONSTELLATION | GAL_CONSTELLATION))// GPS + GAL
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"gps\", \"galileo\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_12K;
  }
  else if( (seedMask | (GPS_CONSTELLATION | BEI_CONSTELLATION)) == (GPS_CONSTELLATION | BEI_CONSTELLATION)) // GPS + BEI
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"gps\", \"beidou\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_12K;
  }
  else if( (seedMask | (GLO_CONSTELLATION | GAL_CONSTELLATION)) == (GLO_CONSTELLATION | GAL_CONSTELLATION)) // GLO + GAL
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"glonass\", \"galileo\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_9K;
  }
  else if( (seedMask | (GAL_CONSTELLATION | BEI_CONSTELLATION)) == (GAL_CONSTELLATION | BEI_CONSTELLATION)) // GAL + BEI
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"beidou\", \"galileo\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_8K;
  }
  else if( (seedMask | (GPS_CONSTELLATION | GLO_CONSTELLATION | GAL_CONSTELLATION)) == (GPS_CONSTELLATION | GLO_CONSTELLATION | GAL_CONSTELLATION)) // GPS + GLO + GAL
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"gps\", \"glonass\", \"galileo\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_16K;
  }
  else if( (seedMask | (GPS_CONSTELLATION | GAL_CONSTELLATION | BEI_CONSTELLATION)) == (GPS_CONSTELLATION | GAL_CONSTELLATION | BEI_CONSTELLATION)) // GPS +  GAL + BEI
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"gps\", \"beidou\", \"galileo\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_16K;
  }
  else if(seedMask | DEFAULT_CONSTELLATION) 
  {
    strcat(JsonData, "[ { \"ee\": {\"version\": 8, \"constellations\": [ \"gps\", \"glonass\", \"galileo\" ], \"seedAge\": 0} } ]");
    *seedSize = BUF_SIZE_16K;
  }
  
  return strlen(JsonData);
}

void A_GNSS_BuildAuthHeader(GNSSParser_Data_t *pGNSSParser_Data, char *auth_string)
{
  if(pGNSSParser_Data == NULL)
  {
    return;
  }
  
  snprintf(auth_string, 128, "RXN-SP cId=%s,mId=%s,dId=%s,pw=%s",
           vendorId,
           modelId,
           pGNSSParser_Data->pstmpass_data.deviceId,
           pGNSSParser_Data->pstmpass_data.pwd);
}

//FIXME: Remove
#include "config_bus.h"
// Finalize decoding and send seed
void A_GNSS_SendSeed(void *pHandle, unsigned char constellation, seed_info_t *seed_info)
{
  unsigned short sat;
  unsigned char GNSS_to_ID;
  int i, k, index, max_sat;
  unsigned int week_number, ref_time;
  signed long T_A0, T_A1, T_A2;
  signed char deltaT;
  signed char slotfreq, blktype;
  glo_slot_freq_t *slot_freq_ptr;
  block_type_t *block_type_ptr;
  unsigned char *time_model_ptr;
  char gnss_cmd[350];
  char output_first_blk_seed[SINGLE_SEED_FIRST_BLOCK_BIT_LEN / 4 + 3] = {0};
  char output_seed[SINGLE_SEED_BIT_LEN / 4 + 4] = {0};

  const char nmea_seed_pkt[] = "$PSTMSTAGPSSEEDPKT,";
  const char nmea_seed_begin[] = "$PSTMSTAGPSSEEDBEGIN,";
  const char nmea_blk_type[] = "$PSTMSTAGPSBLKTYPE";
  const char nmea_slot_frq[] = "$PSTMSTAGPSSLOTFRQ";

  time_model_ptr = &(seed_info->time_model[0]);
  if(constellation == GPS_SEED + 1)
  {
    max_sat = MAX_NUM_GPS_PRNS;
  }
  else if(constellation == GLO_SEED + 1)
  {
    max_sat = MAX_NUM_GLO_PRNS;
  }
  else if(constellation == GAL_SEED + 1)
  {
    max_sat = MAX_NUM_GAL_PRNS;
  }
  else if(constellation == BEI_SEED + 1)
  {
    max_sat = MAX_NUM_BEI_PRNS;
    time_model_ptr = &(seed_info->time_model[1]);
  }

  ref_time = time_model_ptr[0] * 256 + time_model_ptr[1];
  T_A0 = (time_model_ptr[2] * 256 * 256 * 256 + time_model_ptr[3] * 256 * 256 + time_model_ptr[4] * 256 + time_model_ptr[5]);
  T_A1 = (time_model_ptr[6] * 256 * 256 * 256 + time_model_ptr[7] * 256 * 256 + time_model_ptr[8] * 256 + time_model_ptr[9]);
  T_A2 = time_model_ptr[10];
  GNSS_to_ID = time_model_ptr[11];
  week_number = time_model_ptr[12] * 256 + time_model_ptr[13];
  if(constellation == BEI_SEED + 1)
  {
    deltaT = time_model_ptr[14];
  }
  else
  {
    deltaT = 0;
  }

  /************************
   * STEP 1 ***************
   ************************/
  // Send $PSTMSTAGPSSEEDBEGIN command
  unsigned long current_pos = decode_first_block_seed(output_first_blk_seed, seed_info->seed);
  snprintf(gnss_cmd, sizeof(gnss_cmd), "%s%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",
		  nmea_seed_begin, constellation, seed_info->curr_secs, seed_info->next_gps_time,
		  seed_info->next_secs, ref_time, T_A0, T_A1, T_A2, GNSS_to_ID, week_number, deltaT,
                  output_first_blk_seed);
  // FIXME: To be replaced
  //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
  HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);

  // Compute and send the checksum
  snprintf(gnss_cmd, sizeof(gnss_cmd), "*%02x\r\n", checksum(gnss_cmd));
  // FIXME: To be replaced
  //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
  HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);

  /************************
   * STEP 2 ***************
   ************************/
  // Send $PSTMSTAGPSBLKTYPE command
  block_type_ptr = (block_type_t *)&(seed_info->block_types[1]);
  index = snprintf(gnss_cmd, sizeof(gnss_cmd), "%s", nmea_blk_type);
  for(i = 0; i < max_sat; i++)
  {
    for(k = 0; k < max_sat; k++)
    {
      if((block_type_ptr[k].SV_ID) == i)
      {
        blktype = block_type_ptr[k].block_type;
        break;
      }
      else
      {
        blktype = 0;
      }
    }
    index += snprintf(&gnss_cmd[index], sizeof(gnss_cmd)-index, ",%d", blktype);
  }
  // FIXME: To be replaced
  //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
  HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);

  // Compute and send the checksum
  snprintf(gnss_cmd, sizeof(gnss_cmd), "*%02x\r\n", checksum(gnss_cmd));
  // FIXME: To be replaced
  //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
  HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);

  /************************
   * STEP 3 ***************
   ************************/
  // Send $PSTMSTAGPSSLOTFRQ command
  if (constellation == (GLO_SEED + 1))
  {
    slot_freq_ptr = (glo_slot_freq_t *)&(seed_info->slot_freq[1]);
    index = snprintf(gnss_cmd, sizeof(gnss_cmd), "%s", nmea_slot_frq);

    for(i = 0; i < max_sat; i++)
    {
      if(slot_freq_ptr[i].ch_num)
      {
        slotfreq = slot_freq_ptr[i].ch_num;
      }
      else
      {
        slotfreq = 0;
      }
      index += snprintf(&gnss_cmd[index], sizeof(gnss_cmd)-index, ",%d", slotfreq);
    }
    // FIXME: To be replaced
    //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
    HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);

    // Compute and send the checksum
    snprintf(gnss_cmd, sizeof(gnss_cmd), "*%02x\r\n", checksum(gnss_cmd));
    // FIXME: To be replaced
    //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
    HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);
  }

  /************************
   * STEP 4 ***************
   ************************/
  for(sat = seed_info->nsat; sat < seed_info->max_satid; sat++)
  {
    decode_next_blocks_seed(output_seed, seed_info->seed, &current_pos);
    if (output_seed[0] != 0)
    {
      // Send $PSTMSTAGPSSEEDPKT command
      snprintf(gnss_cmd, sizeof(gnss_cmd), "%s%s", nmea_seed_pkt, output_seed);
      // FIXME: To be replaced
      //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
      HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);

      // Compute and send the checksum
      snprintf(gnss_cmd, sizeof(gnss_cmd), "*%02x\r\n", checksum(gnss_cmd));
      // FIXME: To be replaced
      //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
      HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);
    }
  }

//  printf("\n\n*********************sat = %d\n\n", sat);
//  printf("\n\n*********************seed_info->nsat = %d\n\n", seed_info->nsat);
//  printf("\n\n*********************seed_info->max_satid = %d\n\n", seed_info->max_satid);

  return;
}

// Propagate seed command
void A_GNSS_PropagateSeed(void *pHandle)
{
  char gnss_cmd[30];

  snprintf(gnss_cmd, sizeof(gnss_cmd), "$PSTMSTAGPSSEEDPROP");
  // FIXME: To be replaced
  //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
  HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);

  // Compute and send the checksum
  snprintf(gnss_cmd, sizeof(gnss_cmd), "*%02x\r\n", checksum(gnss_cmd));
  // FIXME: To be replaced
  //GNSS_IF_WriteCommand(pHandle, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), MAX_DURATION);
  HAL_UART_Transmit(&io_huart, (uint8_t *)gnss_cmd, (uint16_t)strlen(gnss_cmd), 1000);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
