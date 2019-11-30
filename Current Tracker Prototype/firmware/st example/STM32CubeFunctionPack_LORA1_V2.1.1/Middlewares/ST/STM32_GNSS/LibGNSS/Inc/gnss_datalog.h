/**
 ******************************************************************************
 * @file    gnss_datalog.h
 * @author  AST/CL
 * @version V2.0.0
 * @date    Nov, 2017
 * @brief   LibGNSS module middleware.
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

#ifndef GNSS_DATALOG_H
#define GNSS_DATALOG_H

#ifdef __cplusplus
extern "C" {
#endif

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

/** @defgroup GNSSDatalog_EXPORTED_TYPES GNSSDatalog EXPORTED TYPES
 *  @brief Types related to Datalog
 *  @{
 */

/**
 * @brief Data structure that contains the Datalog data
 */ 
typedef struct
{      
  uint8_t   enableBufferFullAlarm;
  uint8_t   enableCircularBuffer;
  unsigned  minRate;
  unsigned  minSpeed;
  unsigned  minPosition;
  int       logMask;  
} GNSSDatalog_t;
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

#endif /* GNSS_DATALOG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
