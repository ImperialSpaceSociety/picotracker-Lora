/**
*******************************************************************************
* @file    NMEA_parser.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @defgroup MIDDLEWARES MIDDLEWARES
 *  @{
 */

/** @defgroup ST ST
 *  @{
 */

/** @defgroup STM32_GNSS STM32_GNSS
 *  @brief Contains all platform independent modules (eg. NMEA Sentence Parser, ...).
 *  @{
 */
 
/** @defgroup LibNMEA LibNMEA
 *  @brief NMEA sentences parsing module.
 *  @{
 */

/** @defgroup LibNMEA_CONSTANTS_DEFINITIONS CONSTANTS DEFINITIONS
 * @{
 */

/* Exported defines ----------------------------------------------------------*/

/**
 * @brief Constant for boolean type
 */
#define BOOL int32_t

/**
 * @brief Constant for boolean TRUE
 */
#define TRUE 1

/**
 * @brief Constant for boolean FALSE
 */
#define FALSE 0
   
/**
 * @brief Constant that indicates the maximum lenght of an NMEA sentence
 */
#define MAX_NMEA_SENTENCE_LEN 80
   
/**
 * @brief Constant that indicates the maximum number of satellites.
 */  
#define MAX_SAT_NUM 12
  
/**
 * @brief Constant that indicates the maximum lenght of a string.
 */  
#define MAX_STR_LEN 32
  
/**
 * @brief Constant that indicates the maximum lenght of NMEA message field.
 */
#define MAX_MSG_LEN 24 /*48*/ /*32*/  /* was 19 */
#define MAX_MSG_NUM 20
  
/**
 * @brief Constant that indicates the maximum number of sat per GSV message.
 */
#define GSV_MSG_SATS 4

/**
 * @brief Constant that indicates the maximum number of geofence circles.
 */
#define MAX_GEOFENCES_NUM 8  
/**
 * @}
 */
  
/**
 * @brief Enumeration structure that contains the tipologies of Gps fixing process got from a NMEA string
 */
enum {
  INVALID = 0,          /**< Invalid Fix status */
  VALID = 1,            /**< Valid Fix status */
  DGPS_FIX = 2,         /**< DGPS Fix status */
  PPS_FIX = 3,          /**< PPS Fix status */
  REAL_TIME = 4,        /**< Real Time Fix status */
  FLOAT_REAL_TIME = 5,  /**< Float Real Time Fix status */
  ESTIMATED = 6,        /**< Estimated Fix status */
  MANUAL_MODE = 7,      /**< Manual Mode Fix status */
  SIMULATION_MODE = 8   /**< Simulation Mode Fix status */
};

/** @defgroup LibNMEA_EXPORTED_TYPES EXPORTED TYPES
 * @{
 */

/**
 * @brief MISRA compliant typedef for float
 */
typedef float float32_t;

/**
 * @brief MISRA compliant typedef for double
 */
typedef double float64_t;

/**
 * @brief Enumeration structure that contains the two states of a parsing process
 */
typedef enum {
  PARSE_FAIL = 1, /**< Fail status */
  PARSE_SUCC = 0  /**< Success status */
} ParseStatus_t;

/**
 * @brief Enumeration structure that contains the two results of a command
 */
typedef enum {
  GNSS_OP_OK,
  GNSS_OP_ERROR
} OpResult_t;

/**
 * @brief Enumeration structure that contains the types of feature messages
 */
typedef enum {
  GNSS_FEATURE_EN_MSG  = 0,
  GNSS_GEOFENCE_CFG_MSG,
  GNSS_GEOFENCE_STATUS_MSG,
  GNSS_GEOFENCE_ALARM_MSG,
  GNSS_ODO_START_MSG,
  GNSS_ODO_STOP_MSG,
  GNSS_DATALOG_CFG_MSG,
  GNSS_DATALOG_START_MSG,
  GNSS_DATALOG_STOP_MSG,
  GNSS_DATALOG_ERASE_MSG
} ParseFeatureMsg_t;

/**
 * @brief Data structure that contains the coordinates information
 */
typedef struct {
  float64_t lat;   /**< Latitude */
  float64_t lon;   /**< Longitude */
  float64_t alt;   /**< Altitude */
  uint8_t ns;  /**< Nord / Sud latitude type */
  uint8_t ew;  /**< East / West longitude type */
  uint8_t mis; /**< Altitude unit misure */
} Coords_t;
  
/**
 * @brief Data structure that contains the Gps geoids information
 */
typedef struct {
  int32_t height;   /**< Geoid height */
  uint8_t mis;  /**< Geoid height misure unit */
} Geoid_Info_t;
  
/**
 * @brief Data structure that contains the UTC information
 */
typedef struct {
  int32_t utc; /**< UTC Info */
  int32_t hh;  /**< Hours */
  int32_t mm;  /**< Minutes */
  int32_t ss;  /**< Seconds */
} UTC_Info_t;

/**
 * @brief Data structure that contains the GSV information
 */
typedef struct {
  int32_t prn;  /**< PRN */
  int32_t elev; /**< Elevation of satellite in degree, 0 ... 90 */
  int32_t azim; /**< Azimuth of satellite in degree, ref. "North, " 0 ... 359 */
  int32_t cn0;  /**< Carrier to noise ratio for satellite in dB, 0 ... 99 */
} GSV_SAT_Info_t;

/**
 * @brief Data structure that contains all of the information about the GPS position 
 */
typedef struct {
  UTC_Info_t utc;         /**< UTC Time */
  Coords_t xyz;	          /**< Coords data member */
  float32_t acc;	          /**< GPS Accuracy */
  int32_t sats;	          /**< Number of satellities acquired */
  uint8_t valid;      /**< GPS Signal fix quality */
  Geoid_Info_t geoid;	  /**< Geoids data info member */
  int32_t update;		  /**< Update time from the last acquired GPS Info */
  uint32_t checksum;	  /**< Checksum of the message bytes */
} GPGGA_Info_t;

/**
 * @brief Data structure that contains all of the information about the fix data for single or 
 *        combined satellite navigation system.
 */
typedef struct {
  uint8_t constellation[MAX_STR_LEN]; /**< Constellation enabled: GPGNS (GPS), GLGNS (GLONASS), GAGNS (GALILEO), BDGNS (BEIDOU), QZGNS (QZSS), GNGNS (more than one) */ 
  UTC_Info_t utc;                  /**< UTC Time */
  Coords_t xyz;	                   /**< Coords data member */
  uint8_t gps_mode;                /**< N = NO Fix, A = Autonomous, D = Differential GPS, E = Estimated (dead reckoning mode) */
  uint8_t glonass_mode;            /**< N = NO Fix, A = Autonomous, D = Differential Glonass, E = Estimated (dead reckoning mode) */
  int32_t sats;	                   /**< Number of satellities acquired */
  float32_t hdop;                  /**< Horizontal Dilution of Precision, max: 99.0 */
  float32_t geo_sep;               /**< Geoidal separation, meter */
  uint8_t dgnss_age;               /**< Not supported */
  uint8_t dgnss_ref;               /**< Not supported */
  uint32_t checksum;               /**< Checksum of the message bytes */
} GNS_Info_t;

/**
 * @brief Data structure that contains all of information about the GPS Pseudorange Noise Statistics.
 */
typedef struct {
  UTC_Info_t utc;         /**< UTC Time */
  float32_t EHPE;	          /**< Equivalent Horizontal Position Error */
  float32_t semi_major_dev;   /**< Standard deviation (meters) of semi-major axis of error ellipse */
  float32_t semi_minor_dev;   /**< Standard deviation (meters) of semi-minor axis of error ellipse */
  float32_t semi_major_angle; /**< Orientation of semi-major axis of error ellipse (true north degrees) */
  float32_t lat_err_dev;      /**< Standard deviation (meters) of latitude error */
  float32_t lon_err_dev;      /**< Standard deviation (meters) of longitude error */
  float32_t alt_err_dev;      /**< Standard deviation (meters) of altitude error */
  uint32_t checksum;      /**< Checksum of the message bytes */
} GPGST_Info_t;

/**
 * @brief Data structure that contains all the Recommended Minimum Specific GPS/Transit data.
 */
typedef struct {
  UTC_Info_t utc;         /**< UTC Time */
  uint8_t status;            /**< “A” = valid, “V” = Warning */
  Coords_t xyz;           /**< Coords data member */
  float32_t speed;            /**< Speed over ground in knots */
  float32_t trackgood;        /**< Course made good */
  int32_t date;               /**< Date of Fix */
  float32_t mag_var;          /**< Magnetic Variation */
  uint8_t mag_var_dir;       /**< Magnetic Variation Direction */
  uint32_t checksum;      /**< Checksum of the message bytes */
} GPRMC_Info_t;

/**
 * @brief Data structure that contains all of the information about the GSA satellites 
 */
typedef struct {
  uint8_t constellation[MAX_STR_LEN]; /**< Constellation enabled: GPGSA (GPS), GLGSA (GLONASS), GAGSA (GALILEO), BDGSA (BEIDOU), GNGSA (more than one) */ 
  uint8_t operating_mode;             /**< Operating Mode: 'M' = Manual, 'A' = Auto (2D/3D) */
  int32_t current_mode;                /**< Current Mode: 1. no fix available, 2. 2D, 3. 3D */
  int32_t sat_prn[MAX_SAT_NUM];        /**< Satellites list used in position fix (max N 12) */
  float32_t pdop;	                   /**< Position Dilution of Precision, max: 99.0 */
  float32_t hdop;                      /**< Horizontal Dilution of Precision, max: 99.0 */
  float32_t vdop;                      /**< Vertical Dilution of Precision, max: 99.0 */
  uint32_t checksum;               /**< Checksum of the message bytes */
} GSA_Info_t;
  
/**
 * @brief Data structure that contains all of the information about the GSV satellites 
 */
typedef struct {
  uint8_t constellation[MAX_STR_LEN];      /**< Constellation enabled: GPGSV (GPS), GLGSV (GLONASS), GAGSV (GALILEO), BDGSV (BEIDOU), QZGSV (QZSS), GNGSV (more than one) */ 
  int32_t amount;                           /**< Total amount of GSV messages, max. 3 */
  int32_t number;                           /**< Continued GSV number of this message */
  int32_t tot_sats;                         /**< Total Number of Satellites in view, max. 12 */
  int32_t current_sats;
  GSV_SAT_Info_t gsv_sat_i[MAX_SAT_NUM];  /**< Satellite info  */
  uint32_t checksum;	                /**< Checksum of the message bytes */
} GSV_Info_t;

/**
 * @brief Data structure that contains all of the information about FW version
 */
typedef struct {
  uint8_t pstmver_string[MAX_STR_LEN]; /**< String containing the version info required */ 
} PSTMVER_Info_t;

/**
 * @brief Data structure that contains the coordinates information
 */
typedef struct {
  float64_t lat;   /**< Latitude */
  float64_t lon;   /**< Longitude */
  float64_t radius;   /**< Circle Radius */
  float64_t distance;  /**< Distance from circle */
  float64_t tolerance;  /**< Sigma tolerance */
} Geofence_Coords_t;

/**
 * @brief Data structure that contains time/date stamp
 */
typedef struct {
  uint32_t hh;  /**< Hours */
  uint32_t mm;  /**< Minutes */
  uint32_t ss;  /**< Seconds */
  uint32_t year;  /**< Year */
  uint32_t month;  /**< Month */
  uint32_t day;  /**< Day */
} Timestamp_Info_t;

/**
 * @brief Data structure that contains all of the information about Geofence 
 */
typedef struct {
  ParseFeatureMsg_t op;          /**< Geofence type message (configuration/status) */
  OpResult_t result;
  Timestamp_Info_t timestamp;
  int32_t idAlarm;         /**< Id of the circle raising the alarm */
  Geofence_Coords_t coords;
  int32_t status[MAX_GEOFENCES_NUM];
  int32_t checksum;           /**< Checksum of the message bytes */
} Geofence_Info_t;

/**
 * @brief Data structure that contains all of the information about Ododmeter 
 */
typedef struct {
  ParseFeatureMsg_t op;          /**< Odometer type message (configuration/status) */
  OpResult_t result; /**< Odometer operation result (OK/ERROR) */
} Odometer_Info_t;

/**
 * @brief Data structure that contains all of the information about Datalog 
 */
typedef struct {
  ParseFeatureMsg_t op;          /**< Datalog type message (configuration/status) */
  OpResult_t result; /**< Datalog operation result (OK/ERROR) */
} Datalog_Info_t;

/**
 * @brief Data structure that contains all of the information about PWD generated
 */
typedef struct {
  uint8_t deviceId[MAX_STR_LEN]; /**< String containing the unique deviceID */
  uint8_t pwd[64]; /**< String containing the password */
  OpResult_t result;
} PSTMPASSRTN_Info_t;

/**
 * @brief Message status sent in response to commands PSTMGETAGPSSTATUS
 */
typedef struct {
  int32_t status;
} PSTMAGPSSTATUS_Info_t;

/**
 * @}
 */

/** @defgroup LibNMEA_EXPORTED_FUNCTIONS EXPORTED FUNCTIONS
 * @{
 */

/**
 * @brief  Function that makes the parsing of the $GPGGA NMEA string with all Global Positioning System Fixed data.
 * @param  pGPGGAInfo     Pointer to GPGGA_Info_t struct
 * @param  NMEA	          NMEA string read by the Gps expansion
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParseGPGGA(GPGGA_Info_t *pGPGGAInfo, uint8_t NMEA[]);

/**
 * @brief  Function that makes the parsing of the string read by the Gps expansion, capturing the right parameters from it.
 * @param  pGNSInfo      Pointer to GNS_Info_t struct
 * @param  NMEA[]        NMEA string read by the Gps expansion
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParseGNS(GNS_Info_t *pGNSInfo, uint8_t NMEA[]);

/**
 * @brief  Function that makes the parsing of the $GPGST NMEA string with GPS Pseudorange Noise Statistics.
 * @param  pGPGSTInfo    Pointer to a GPGST_Info_t struct
 * @param  NMEA	         NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParseGPGST(GPGST_Info_t *pGPGSTInfo, uint8_t NMEA[]);

/**
 * @brief  Function that makes the parsing of the $GPRMC NMEA string with Recommended Minimum Specific GPS/Transit data.
 * @param  pGPRMCInfo    Pointer to a GPRMC_Info_t struct
 * @param  NMEA	         NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParseGPRMC(GPRMC_Info_t *pGPRMCInfo, uint8_t NMEA[]);

/**
 * @brief  Function that makes the parsing of the $GSA NMEA string.
 * @param  pGSAInfo      Pointer to a GSA_Info_t struct
 * @param  NMEA	         NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParseGSA(GSA_Info_t *pGSAInfo, uint8_t NMEA[]);

/**
 * @brief  Function that makes the parsing of the $GSV NMEA string.
 * @param  pGSVInfo      Pointer to a GSV_Info_t struct
 * @param  NMEA	         NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParseGSV(GSV_Info_t *pGSVInfo, uint8_t NMEA[]);

/**
 * @brief  Function that parses of the $PSTMVER NMEA string with version data.
 * @param  pPSTMVER      Pointer to PSTMVER_Info_t struct
 * @param  NMEA	         NMEA string read by the Gps expansion
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParsePSTMVER(PSTMVER_Info_t *pPSTMVER, uint8_t NMEA[]);

/**
 * @brief  This function parses the geofence related messages
 * @param  pGeofence     Pointer to Geofence_Info_t
 * @param  NMEA	         NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParsePSTMGeofence(Geofence_Info_t *pGeofence, uint8_t NMEA[]);

/**
 * @brief  This function parses the odometer related messages
 * @param  pOdo          Pointer to a Odometer_Info_t struct
 * @param  NMEA          NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParsePSTMOdo(Odometer_Info_t *pOdo, uint8_t NMEA[]);

/**
 * @brief  This function parses the datalog related messages  
 * @param  pDatalog      Pointer to a Datalog_Info_t struct
 * @param  NMEA          NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParsePSTMDatalog(Datalog_Info_t *pDatalog, uint8_t NMEA[]);

/**
 * @brief  This function parses the list configuration message
 * @param  pResult             Ack from Teseo
 * @param  NMEA                NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParsePSTMsgl(OpResult_t *pResult, uint8_t NMEA[]);

/**
 * @brief  This function parses the SavePar messages
 * @param  pResult             Ack from Teseo
 * @param  NMEA                NMEA string read by the Gps expansion.
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParsePSTMSavePar(OpResult_t *pResult, uint8_t NMEA[]);


/**
 * @brief  Function that parses of the $PSTMSTAGPSPASSRTN NMEA string with version data.
 * @param  pPSTMPASSRTN  Pointer to PSTMPASSRTN_Info_t struct
 * @param  NMEA	         NMEA string read by the Gps expansion
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParsePSTMPASSRTN(PSTMPASSRTN_Info_t *pPSTMPASSRTN, uint8_t NMEA[]);

/**
 * @brief  Function that parses of the $PSTMSTAGPSSTATUS NMEA string with version data.
 * @param  pPSTMPASSRTN  Pointer to PSTMAGPSSTATUS_Info_t struct
 * @param  NMEA	         NMEA string read by the Gps expansion
 * @retval PARSE_SUCC if the parsing process goes ok, PARSE_FAIL if it doesn't
 */
ParseStatus_t NMEA_ParsePSTMAGPSSTATUS(PSTMAGPSSTATUS_Info_t *pPSTMAGPSSTATUS, uint8_t NMEA[]);

/**
 * @brief  This function makes a copy of the datas stored into GPGGAInfo into the pInfo param
 * @param  pInfo     Pointer to GPGGA_Info_t object where there are the GPGGA_Info_t to be copied
 * @param  GPGGAInfo Instance of a GPGGA_Info_t object pointer where the GPGGA_Info_t stored into pInfo have to be copied
 * @retval None
 */
void NMEA_Copy_Data(GPGGA_Info_t *pInfo, GPGGA_Info_t GPGGAInfo);

/**
 * @brief  This function converts a character to unsigned integer
 * @param  c The character to convert
 * @retval The returned unsigned integer
 */
uint32_t char2int(uint8_t c);
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

#endif /* NMEA_PARSER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
