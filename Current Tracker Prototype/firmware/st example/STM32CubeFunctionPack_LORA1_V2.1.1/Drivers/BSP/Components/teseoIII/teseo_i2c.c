/**
  *******************************************************************************
  * @file    teseo_i2c.c
  * @author  APG/AST/CL
  * @version V2.0.0
  * @date    Feb-2018
  * @brief   Teseo III I2C handler.
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

/* Includes ------------------------------------------------------------------*/
#ifdef LORA_SMART_TRACKER
#include "LoRaTracker_gnss.h"
#else //LORA_SMART_TRACKER
#include "x_nucleo_gnss1a1.h"
#endif //LORA_SMART_TRACKER

#include "teseo_i2c.h"
#include "teseo_queue.h"

/* Private defines -----------------------------------------------------------*/

//#define DEBUG
#ifdef DEBUG
#ifdef LORA_SMART_TRACKER
#define Console_Debug(x)        TestLoraSmartTrackerTransmit()
#else//LORA_SMART_TRACKER
#define Console_Debug(x) 		GNSS_ConsoleDbg(x)
#endif //LORA_SMART_TRACKER
#else
#define Console_Debug(x)
#endif

/*
 * Constant for I2C read
 */
#define I2C_READ	(0)
/*
 * Constant for I2C write
 */
#define I2C_WRITE	(1)

/*
 * Size of I2C buffer
 */
#define I2C_LOCAL_BUF	(16)

/* Private types -------------------------------------------------------------*/

/*
 * Enumeration structure that contains the I2C task states
 */
typedef enum
{
  IDLE,
  RUNNING,
  WAITING
} Task_Command_StateTypeDef;

/*
 * Enumeration structure that contains the I2C FSM states
 */
typedef enum
{
  i2c_fsm_discard,
  i2c_fsm_synch
} Teseo_I2C_FsmTypeDef;

/*
 * I2C private data handler
 */
typedef struct
{
  volatile Task_Command_StateTypeDef cmd;
  volatile Task_Command_StateTypeDef state;
  GNSS_MsgTypeDef *wr_msg;
  volatile Teseo_I2C_FsmTypeDef fsm_state;
  volatile Teseo_I2C_FsmTypeDef fsm_next_state;
  volatile uint32_t timeout;
  volatile int8_t nr_msg;
  volatile int8_t fsm_restart;

  uint8_t buf[I2C_LOCAL_BUF];
  
  GNSS_HandleTypeDef *pGNSS;
} Teseo_I2C_DataTypeDef;

/*
 * Instance of I2C private data handler
 */
static Teseo_I2C_DataTypeDef Teseo_I2C_Data;


/* Private functions ---------------------------------------------------------*/
static void i2c_fsm(uint8_t temp);

/*
 * I2C state machine function (param temp is char read on the I2C bus
 */
static void i2c_fsm(uint8_t temp)
{
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)(Teseo_I2C_Data.pGNSS->pData);
  uint32_t offset = 1;

  Teseo_I2C_Data.fsm_restart = 1;

  while(Teseo_I2C_Data.fsm_restart == 1)
  {
    Teseo_I2C_Data.fsm_state = Teseo_I2C_Data.fsm_next_state;
    
    switch (Teseo_I2C_Data.fsm_state)
    {
      
    case i2c_fsm_discard:
      Teseo_I2C_Data.fsm_restart = 0;
      Teseo_I2C_Data.fsm_next_state = i2c_fsm_discard;
      //Console_Debug((uint8_t *)".");
      
      if (temp != (uint8_t)'$') {
        break;
      }
      
      if (Teseo_I2C_Data.wr_msg == NULL)
      {
        Teseo_I2C_Data.wr_msg = teseo_queue_claim_wr_buffer(teseo_io_data->pQueue);
      }
      
      if (Teseo_I2C_Data.wr_msg == NULL)
      {
        break;
      }
      
      Teseo_I2C_Data.wr_msg->len = 0;
      Teseo_I2C_Data.wr_msg->buf[Teseo_I2C_Data.wr_msg->len] = temp; /* save '$' */
      Teseo_I2C_Data.wr_msg->len++;

      Teseo_I2C_Data.fsm_next_state = i2c_fsm_synch;
      Console_Debug((uint8_t*)"I2C buffer synch\n\r");
      break;
      
    case i2c_fsm_synch:
      Teseo_I2C_Data.fsm_restart = 0;
      Teseo_I2C_Data.wr_msg->buf[Teseo_I2C_Data.wr_msg->len] = temp;
      Teseo_I2C_Data.wr_msg->len++;
      
      if (Teseo_I2C_Data.wr_msg->buf[Teseo_I2C_Data.wr_msg->len-offset] == (uint8_t)'$')
      {
        --Teseo_I2C_Data.wr_msg->len;
        Teseo_I2C_Data.wr_msg->buf[Teseo_I2C_Data.wr_msg->len] = (uint8_t)'\0';
        teseo_queue_release_wr_buffer(teseo_io_data->pQueue, Teseo_I2C_Data.wr_msg);
        if (Teseo_I2C_Data.nr_msg != -1)
        {
          --Teseo_I2C_Data.nr_msg;
          if (Teseo_I2C_Data.nr_msg == 0)
          {
            Teseo_I2C_Data.cmd = IDLE;
            break;
          }
        }
        Console_Debug((uint8_t*)"I2C buffer released\n\r");
        Teseo_I2C_Data.wr_msg = NULL;
        Teseo_I2C_Data.fsm_next_state = i2c_fsm_discard;

        Teseo_I2C_Data.fsm_restart = 1; // check if we can resynch the new sentence
        break;
      }
#if 0
      //Console_Debug((uint8_t *)"+");
      if (Teseo_I2C_Data.wr_msg->len == (uint32_t)MAX_MSG_BUF)
      {
        Console_Debug("MESSAGE TOO LONG\n\r");
        /* it seems we lost some char and the sentence is too much long...
        * reset the msg->len and discand all teh buffer and wait a new '$' sentence
        */
        Teseo_I2C_Data.fsm_next_state = i2c_fsm_discard;
        Teseo_I2C_Data.wr_msg->len = 0;

        Teseo_I2C_Data.fsm_restart = 1;
        break;
      }
#endif
      Teseo_I2C_Data.fsm_next_state = i2c_fsm_synch;
      break;
      
    default:
      Teseo_I2C_Data.fsm_restart = 0;
      break;
    }
  }
}

/* Exported functions --------------------------------------------------------*/
void teseo_i2c_rx_callback(const I2C_HandleTypeDef *bus, Teseo_I2C_CB_CallerTypedef c)
{
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)(Teseo_I2C_Data.pGNSS->pData);

  // For L4/L0 I2C_HandleTypeDef does not include the Devaddress field 
#ifdef USE_STM32F4XX_NUCLEO
  uint32_t devAddress = Teseo_I2C_7bits_Addr << 1;
  uint8_t thisDev = (bus->Devaddress == devAddress) ? 1U : 0U;
#else
  uint8_t thisDev = 1U;
#endif /* USE_STM32F4XX_NUCLEO */

  int32_t i;
  
  /*
   * a different bus or a different slave-device ... are not a teseo issue
   */
  if ((bus != teseo_io_data->hi2c) || (thisDev == 0U))
  {
    return;
  }

  if (Teseo_I2C_Data.cmd == IDLE)
  {
    /* turn-off I2C-ISR... */
    Teseo_I2C_Data.state = IDLE;
    return;
  }

  if (c == _i2c_abort)
  {
    Console_Debug((uint8_t*)"Teseo I2C Abort on ISR\n\r");
    /* turn-off I2C-ISR... */
    Teseo_I2C_Data.state = IDLE;
    return;
  }
  
  if (c == _i2c_error)
  {
    Console_Debug((uint8_t*)"Teseo I2C Error on ISR\n\r");
    /* suspend I2C-ISR... and try to resume later...*/
#define TIMEOUT_DELAY	(uint32_t)100
    Teseo_I2C_Data.timeout = HAL_GetTick() + TIMEOUT_DELAY;
    Teseo_I2C_Data.state = WAITING; /* turn-off */
    return;
  }
  
  Console_Debug((uint8_t*)"I2C ISR\n\r");
  for (i = 0; i < I2C_LOCAL_BUF; ++i)
  {
    if (Teseo_I2C_Data.buf[i] != (uint8_t)0xff)
    {
      i2c_fsm(Teseo_I2C_Data.buf[i]);
    }
  } 
  
  if (Teseo_I2C_Data.buf[I2C_LOCAL_BUF-1] == (uint8_t)0xff)
  {
    Teseo_I2C_Data.timeout = HAL_GetTick() + TIMEOUT_DELAY;
    Teseo_I2C_Data.state = WAITING;
    return;
  }

  Teseo_I2C_Data.timeout = HAL_GetTick();
  Teseo_I2C_Data.state = RUNNING;
  (void)HAL_I2C_Master_Receive_IT(teseo_io_data->hi2c,
                                  (uint16_t)(Teseo_I2C_7bits_Addr << 1),
                                  (uint8_t *)Teseo_I2C_Data.buf,
                                  I2C_LOCAL_BUF);
}

void teseo_i2c_onoff(GNSS_HandleTypeDef *pGNSS, uint8_t enable, int8_t nr_msg)
{
  Teseo_I2C_Data.pGNSS = pGNSS;
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)(Teseo_I2C_Data.pGNSS->pData);

  if (teseo_io_data->hi2c == NULL)
  {
    return;
  }
  if ((Teseo_I2C_Data.state == RUNNING) && (enable == 1U))
  {
    return;
  }
  if ((Teseo_I2C_Data.state == IDLE) && (enable == 0U))
  {
    return;
  }
  
  if (enable == 1U)
  {
    Console_Debug((uint8_t*)"I2C running\n\r");
    teseo_io_data->pQueue = teseo_queue_init();
    Teseo_I2C_Data.fsm_next_state = i2c_fsm_discard;
    Teseo_I2C_Data.fsm_restart = 1;
    Teseo_I2C_Data.nr_msg = nr_msg;
    Teseo_I2C_Data.timeout = HAL_GetTick();
    Teseo_I2C_Data.wr_msg = NULL;
    Teseo_I2C_Data.cmd = RUNNING;
    (void)HAL_I2C_Master_Receive_IT(teseo_io_data->hi2c,
                                    (uint16_t)(Teseo_I2C_7bits_Addr << 1),
                                    (uint8_t *)Teseo_I2C_Data.buf,
                                    I2C_LOCAL_BUF);
    
    return;
  }

  Teseo_I2C_Data.cmd = IDLE;
  while (Teseo_I2C_Data.state == RUNNING) {};
  /*
   * This function returns when the I2C-FiniteStateMachine is no more running...
   */
}

void teseo_i2c_background_process(void)
{
  Teseo_IO_DataTypeDef *teseo_io_data = (Teseo_IO_DataTypeDef *)(Teseo_I2C_Data.pGNSS->pData);

  if (Teseo_I2C_Data.cmd == IDLE)
  {
    return;
  }

  if (teseo_io_data->hi2c == NULL)
  {
    return;
  }

  if (HAL_GetTick() > Teseo_I2C_Data.timeout)
  {
    Console_Debug((uint8_t*)"I2C Idle running\n\r");
    Teseo_I2C_Data.state = RUNNING;
    (void)HAL_I2C_Master_Receive_IT(teseo_io_data->hi2c,
                                    (uint16_t)(Teseo_I2C_7bits_Addr << 1),
                                    (uint8_t *)Teseo_I2C_Data.buf,
                                    I2C_LOCAL_BUF);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
