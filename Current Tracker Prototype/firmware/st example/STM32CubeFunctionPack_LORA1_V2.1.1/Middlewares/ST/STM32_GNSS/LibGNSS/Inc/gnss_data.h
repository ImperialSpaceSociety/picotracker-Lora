/**
*******************************************************************************
* @file    gnss_data.h
* @author  AST/CL
* @version V2.0.0
* @date    Jun-2018
* @brief   Provides API to access GNSS data - LibGNSS module middleware
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
#ifndef GNSS_DATA_H
#define GNSS_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
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

/** @defgroup GNSS_DATA_FUNCTIONS GNSS DATA FUNCTIONS
 *  @brief Prototypes of the API allowing the application to interface the driver
 *  and interact with GNSS module (sending commands, retrieving parsed NMEA info, etc.).
 *  The implementation is up to the application according to specific needs.
 *  @{
 */

/**
 * @brief  This function sends a command to the GNSS module.
 * @param  pHandle  Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  pCommand  The string with NMEA command to be sent to the GNSS module
 * @retval None
 */
void GNSS_DATA_SendCommand(void *pHandle, char *pCommand);

/**
 * @brief  Function that retrieves data from GPGGA sentence.
 * @param  pGNSSParser_Data The parsed GPGGA sentence
 * @retval None
 */
void GNSS_DATA_GetGGAInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**
 * @brief  Function that retrieves data from correctly parsed GPGGA sentence.
 * @param  pGNSSParser_Data The parsed GPGGA sentence
 * @retval None
 */
void GNSS_DATA_GetValidInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function retrieves the tracking data using the result of parsed GPGGA sentence.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @param  how_many         The number of the position to track
 * @param  time             Time delay between the tracking of two different positions
 * @retval how_many number of actual acquired positions if the process went good, 0 if didn't
 */
int32_t GNSS_DATA_TrackGotPos(GNSSParser_Data_t *pGNSSParser_Data, uint32_t how_many, uint32_t time);

/**	
 * @brief  This function prints on the console all the position got by a tracking position process.
 * @param  None
 * @retval None
 */
void GNSS_DATA_PrintTrackedPositions(int how_many);

/**	
 * @brief  This function prints on the console the info about Fix data for single 
 *         or combined satellite navigation system.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetGNSInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function prints on the console the info about GPS Pseudorange.
 *         Noise Statistics.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetGPGSTInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function prints on the console the info about Recommended Minimum Specific
 *         GPS/Transit data got by the most recent reception process.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetGPRMCInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function prints on the console the info about GSA satellites got 
 *         by the most recent reception process.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetGSAInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function prints on the console the info about GSV satellites got
 *         by the most recent reception process.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetGSVInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function prints on the console the info about FW version.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetPSTMVerInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**	
 * @brief  This function prints on the console the geofence infos each time an alarm is received.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetGeofenceInfo(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data);

/** 
 * @brief  This function prints on the console the info about Odometer.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetOdometerInfo(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data);

/** 
 * @brief  This function prints on the console the info about Datalog.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetDatalogInfo(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data);

/**
 * @brief  This function gets the ACK from the GPS data.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetMsglistAck(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data);

/**
  * @brief  This function gets the ACK from the GNSS data.
  * @param  pHandle Handler of the GNSS object
  * @retval None
  */
void GNSS_DATA_GetGNSSAck(void *pHandle, GNSSParser_Data_t *pGNSSParser_Data);

/**
 * @brief  This function configures the message list.
 * @param  pHandle  Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  lowMask This LOW_BITS Mask for configuring message list
 * @param  highMask This HIGH_BITS Mask for configuring message list
 * @retval None
 */
void GNSS_DATA_CfgMessageList(void *pHandle, int lowMask, int highMask);

/**
 * @brief  This function sends a command to enable/disable geofence.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  toggle  The toggle to enable/disable geofence
 * @retval None
 */
void GNSS_DATA_EnableGeofence(void *pHandle, int toggle);

/**	
 * @brief  This function sends a command to config a geofence region 
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  gnss_geofence The geofence region to be configured
 * @retval None
 */
void GNSS_DATA_ConfigGeofence(void *pHandle, void* gnss_geofence);

/**	
 * @brief  This function sends a command to enable/disable odometer.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  toggle The toggle to enable/disable odometer
 * @retval None
 */
void GNSS_DATA_EnableOdo(void *pHandle, int toggle);

/**
 * @brief  This function sends a command to start odometer.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  alarmDistance The distance to raise an alarm
 * @retval None
 */
void GNSS_DATA_StartOdo(void *pHandle, unsigned alarmDistance);

/**
 * @brief  This function sends a command to stop odometer.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @retval None
 */
void GNSS_DATA_StopOdo(void *pHandle);

/**	
 * @brief  This function sends a command to enable/disable datalogging.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  toggle The toggle to enable/disable datalogging
 * @retval None
 */
void GNSS_DATA_EnableDatalog(void *pHandle, int toggle);

/**	
 * @brief  This function sends a command to config datalogging.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  gnss_datalog The datalog configuration
 * @retval None
 */
void GNSS_DATA_ConfigDatalog(void *pHandle, void *gnss_datalog);

/**	
 * @brief  This function sends a command to start datalogging.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @retval None
 */
void GNSS_DATA_StartDatalog(void *pHandle);

/**	
 * @brief  This function sends a command to stop datalogging.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @retval None
 */
void GNSS_DATA_StopDatalog(void *pHandle);

/**
 * @brief  This function sends a command to erase datalogging.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @retval None
 */
void GNSS_DATA_EraseDatalog(void *pHandle);

/**
 * @brief  This function requests the generation of a password to access the A-GPS server.
 * @param  pHandle Handler of the GNSS object. Is set to void * to guarantee the generality of the method
 * @param  currentTime GPS time
 * @retval None
 */
void GNSS_DATA_PassGen(void *pHandle, uint32_t currentTime);

/**
 * @brief  This function prints on the console the info about DeviceId and Pwd.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetPSTMPassInfo(GNSSParser_Data_t *pGNSSParser_Data);

/**
 * @brief  This function prints on the console the status of the STAGPS processing.
 * @param  pGNSSParser_Data Handler of the GNSS data
 * @retval None
 */
void GNSS_DATA_GetPSTMAGPSStatus(GNSSParser_Data_t *pGNSSParser_Data);

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

#endif /* GNSS_DATA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
