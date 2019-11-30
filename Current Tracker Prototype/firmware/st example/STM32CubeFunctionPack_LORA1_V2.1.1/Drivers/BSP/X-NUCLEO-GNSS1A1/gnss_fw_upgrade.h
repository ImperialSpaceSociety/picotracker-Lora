/**
 ******************************************************************************
 * @file    gnss_fw_upgrade.h
 * @author  AST/CL
 * @version V2.0.0
 * @date    Jan, 2018
 * @brief   FW Upgrade API
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
#ifndef GNSS_FW_UPGRADE_H
#define GNSS_FW_UPGRADE_H

/** @addtogroup DRIVERS
  * @{
  */
  
/** @addtogroup BSP
 * @{
 */

/** @addtogroup X_NUCLEO_GNSS1A1
  * @{
  */

/** @addtogroup GNSS1A1Driver_EXPORTED_DEFINES
 * @{
 */

/**	
 * @brief  Function managing the FW upgrading process. This feature must be used
 *         with the Flash Updater Tool enclosed in this package in folder 
 *         Utilities\PC_Software\FirmwareUpdaterTool
 * @param  None
 * @retval None
 */
void FWUpgrade(void);
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
 
#endif /* GNSS_FW_UPGRADE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
