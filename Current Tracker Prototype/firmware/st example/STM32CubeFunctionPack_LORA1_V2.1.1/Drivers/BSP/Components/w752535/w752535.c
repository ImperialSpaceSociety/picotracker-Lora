/**
 ******************************************************************************
 * @file    w752535.c
 * @author  SRA - System Lab - Sensing & Connectivity Application Team
 * @version V2.1.1
 * @date    10-Oct-2019
 * @brief   w752535 source code file
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
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "w752535.h"

/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup Component Component
 * @{
 */

/** @defgroup HTS221 HTS221
 * @{
 */

/** @defgroup HTS221_Exported_Variables HTS221 Exported Variables
 * @{
 */

const battery_points_t a_battery_profile[NUMBER_OF_BATTERY_PROFILE_SAMPLES] = 
{
  {4170, 5000, 0, 100},
  {4150, 4170, 60.00400027, -150.2166811},
  {4100, 4150, 122.4081605, -409.1939463},
  {4050, 4100, 146.4097607, -507.6005067},
  {4000, 4050, 81.60544036, -245.1430095},
  {3950, 4000, 129.6086406, -437.1558104},
  {3900, 3950, 139.2092806, -475.0783386},
  {3850, 3900, 170.4113608, -596.7664511},
  {3800, 3850, 235.2156810, -846.2630842},
  {3750, 3800, 321.6214414, -1174.604974},
  {3700, 3750, 273.6182412, -994.5929729},
  {3690, 3700, 228.0152010, -825.8617241},
  {3660, 3690, 280.0186679, -1017.754517},
  {3650, 3660, 60.00400027, -212.5008334},
  {3500, 3650, 26.40176012, -89.85265684},
  {3300, 3500, 12.60084006, -41.54943663},
  {0, 3300, 0, 0.03}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
