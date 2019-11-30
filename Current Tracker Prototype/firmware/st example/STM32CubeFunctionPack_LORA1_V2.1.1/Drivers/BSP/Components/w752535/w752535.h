/**
 ******************************************************************************
 * @file    w752535.h
 * @author  SRA - System Lab - Sensing & Connectivity Application Team
 * @version V2.1.1
 * @date    10-Oct-2019
 * @brief   w752535 header driver file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
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
#ifndef W752535_H
#define W752535_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "stdint.h"
  
/** @addtogroup BSP BSP
* @{
  */
  
  /** @addtogroup Component Component
  * @{
  */
  
  /** @addtogroup w752535 w752535
  * @{
  */
  
  /** @defgroup w752535_Exported_Types LiPo-752535 battery Exported Types
  * @{
  */
  
  typedef struct
  {
    uint16_t    voltage_min;
    uint16_t    voltage_max;
    float       voltage_m;
    float       voltage_q;
  } battery_points_t;
  
  
  
  /**
  * @}
  */
  
  /** @defgroup w752535_Exported_Constants LiPo-752535 Exported Constants
  * @{
  */
#define NUMBER_OF_BATTERY_PROFILE_SAMPLES           17U
  
  
  /**
  * @}
  */
  
  
  /** @defgroup w752535_Exported_Variables LiPo-752535 Exported variables
  * @{
  */
  
extern const battery_points_t a_battery_profile[NUMBER_OF_BATTERY_PROFILE_SAMPLES];
  
  /**
  * @}
  */
  
  
#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
