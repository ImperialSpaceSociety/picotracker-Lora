 /******************************************************************************
  * @file    test_rf.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    10-July-2018
  * @brief   Header for test_rf.c
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEST_RF_H__
#define __TEST_RF_H__

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

   /**
 * @brief RF transmit test command
 * @param [IN] buf Pointer to buffer of data
 * @param [IN] size Size of data
 * @retval LoRa status
 */
ATEerror_t TST_TxTone(const char *buf, unsigned bufSize);

/**
 * @brief RF Receive test command
 * @param [IN] buf Pointer to buffer of data
 * @param [IN] size Size of data
 * @retval LoRa status
 */
ATEerror_t TST_RxTone(const char *buf, unsigned bufSize);

ATEerror_t TST_TX_LoraStart(const char *buf, unsigned bufSize);

ATEerror_t TST_RX_LoraStart( void );

ATEerror_t TST_SET_lora_config(const char *buf, unsigned bufSize);

ATEerror_t TST_get_lora_config(const char *buf, unsigned bufSize);
/**
 * @brief RF test stop
 * @param [IN] None
 * @retval LoRa status
 */
ATEerror_t TST_stop( void );
#ifdef __cplusplus
}
#endif

#endif /* __TEST_RF_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
