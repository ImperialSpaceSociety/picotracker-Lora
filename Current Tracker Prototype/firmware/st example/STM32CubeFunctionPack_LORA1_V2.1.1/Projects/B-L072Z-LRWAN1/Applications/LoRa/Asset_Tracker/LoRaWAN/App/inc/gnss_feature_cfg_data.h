/**
 ******************************************************************************
 * @file    Applications/SimOSGetPos/Inc/gnss_feature_cfg_data.h
 * @author  AST/CL
 * @version V2.0.0
 * @date    Nov, 2017
 * @brief   Defines configuration parameters for GNSS advanced features.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
#ifndef GNSS_FEATURE_CFG_DATA_H
#define GNSS_FEATURE_CFG_DATA_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "gnss_geofence.h"
#include "gnss_datalog.h"

/** @addtogroup PROJECTS PROJECTS
  * @{
  */
   
/** @addtogroup B-L072Z-LRWAN1 B-L072Z-LRWAN1
  * @{
  */  
   
/** @addtogroup B-L072Z-LRWAN1_LoRaWAN LoRaWAN
  * @{
 */

/** @addtogroup B-L072Z-LRWAN1_SimOSGetPos
 * @{
 */
 	
/** @addtogroup B-L072Z-LRWAN1_SimOSGetPos_GNSS_FEATURE_CFG_DATA GNSS_FEATURE_CFG_DATA
 * @{
 */

/* See CDB-ID 228 - HIGH_BITS Mask */
#define ODOMETER_NMEA_MSG 50U
#define GEOFENCE_NMEA_MSG 51U
#define DATALOG_NMEA_MSG 52U

#define ODOMETER ((uint32_t)1<<(ODOMETER_NMEA_MSG-32U))
#define GEOFENCE ((uint32_t)1<<(GEOFENCE_NMEA_MSG-32U))
#define DATALOG ((uint32_t)1<<(DATALOG_NMEA_MSG-32U))

GNSSGeofence_t Geofence_STLecce = {
    .id = 5,
    .enabled = 1,
    .tolerance = 1,
    .lat = 40.336055,
    .lon = 18.120611,
    .radius = 200,
    .status = 0
  };
  
GNSSGeofence_t Geofence_Catania = {
    .id = 6,
    .enabled = 1,
    .tolerance = 1,
    .lat = 37.4908266,
    .lon = 15.0073063,
    .radius = 200,
    .status = 0
};

GNSSDatalog_t SampleDatalog = {
  .enableBufferFullAlarm = 0,
  .enableCircularBuffer = 1,
  .minRate = 5,
  .minSpeed = 0,
  .minPosition = 0,
  .logMask = 1
};
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

#ifdef __cplusplus
}
#endif

#endif /* GNSS_FEATURE_CFG_DATA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

