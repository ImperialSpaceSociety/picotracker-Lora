/**
 ******************************************************************************
 * @file    LoRaTracker_conf.h
 * @author  MEMS Application Team
 * @version V0.0.1
 * @date    29-January-2018
 * @brief   LORATRACKER configuration template file.
 *          This file should be copied to the application folder and renamed
 *          to LoRaTracker_conf.h.
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

/* Replace the header file names with the ones of the target platform */
#include "stm32l0xx_hal.h"
#include "loratracker_bus.h"
#include "loratracker_errno.h"

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LORATRACKER_CONF_H__
#define __LORATRACKER_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define USE_LORA_TRACKER_ENV_SENSOR_HTS221_0                1U
#define USE_LORA_TRACKER_ENV_SENSOR_LPS22HB_0               1U

#define USE_LORA_TRACKER_MOTION_SENSOR_LIS2DW12_0           1U 
#define USE_LORA_TRACKER_MOTION_SENSOR_LSM6DSL_0            0 //1U
#define USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_ACC_0      0 //1U
#define USE_LORA_TRACKER_MOTION_SENSOR_LSM303AGR_MAG_0      0 //1U

#define LORA_TRACKER_I2C1_Init BSP_I2C1_Init
#define LORA_TRACKER_I2C1_DeInit BSP_I2C1_DeInit
#define LORA_TRACKER_I2C1_ReadReg BSP_I2C1_ReadReg
#define LORA_TRACKER_I2C1_WriteReg BSP_I2C1_WriteReg
#define LORA_TRACKER_GetTick BSP_GetTick

#ifdef __cplusplus
}
#endif

#endif /* __LORATRACKER_CONF_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

