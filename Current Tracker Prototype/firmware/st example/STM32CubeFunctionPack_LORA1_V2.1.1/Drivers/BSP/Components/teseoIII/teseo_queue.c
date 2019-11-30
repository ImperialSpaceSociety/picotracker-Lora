/**
  *******************************************************************************
  * @file    teseo_queue.c
  * @author  APG/AST/CL
  * @version V2.0.0
  * @date    Feb-2018
  * @brief   Teseo III buffer queue manager.
  *
  *******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
#include <string.h>
#include "teseo_queue.h"

/* Defines -------------------------------------------------------------------*/
#ifdef _DEBUG
#define Console_Debug(x) GNSS_ConsoleDbg(x)
#else
#define Console_Debug(x)
#endif

/* Private variables ---------------------------------------------------------*/
#ifdef USE_FREE_RTOS
static BaseType_t b = configLIBRARY_LOWEST_INTERRUPT_PRIORITY;
#endif /* USE_FREE_RTOS */

/* Private functions ---------------------------------------------------------*/

/*
 * ffs - find first bit set
 * @x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 * Source: 
 * git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git/tree/include/asm-generic/bitops/ffs.h?h=v4.1.46
 */
static inline int32_t ffs(uint32_t _w)
{
  int32_t r = 1;
  uint32_t w = _w;
  
  if (w == 0U)
  {
    return 0;
  }
  if ((w & 0xffffU) == 0U)
  {
    w >>= 16;
    r += 16;
  }
  if ((w & 0xffU) == 0U)
  {
    w >>= 8;
    r += 8;
  }
  if ((w & 0xfU) == 0U)
  {
    w >>= 4;
    r += 4;
  }
  if ((w & 3U) == 0U)
  {
    w >>= 2;
    r += 2;
  }
  if ((w & 1U) == 0U)
  {
    r += 1;
  }
  return r;
}

#ifdef USE_FREE_RTOS
/*
 * Wrapper for Semaphore lock.
 */
static inline void semaphore_lock(SemaphoreHandle_t sem)
{
  (void)xSemaphoreTake(sem, 5000);
}

/*
 * Wrapper for Semaphore release.
 */
static inline void semaphore_free(SemaphoreHandle_t sem)
{
  (void)xSemaphoreGive(sem);
}

/*
 * Wrapper for Semaphore lock from interrupt context.
 */
static inline BaseType_t semaphore_lock_irq(SemaphoreHandle_t sem)
{
  return xSemaphoreTakeFromISR(sem,  &b);
}

/*
 * Wrapper for Semaphore release from interrupt context.
 */
static inline void semaphore_free_irq(SemaphoreHandle_t sem)
{
  (void)xSemaphoreGiveFromISR(sem, &b);
}
#endif /* USE_FREE_RTOS */

/*
 * Returns the static instance of a Queue object.
 */
static Teseo_QueueTypeDef *Teseo_Queue_static_alloc(void)
{
  static Teseo_QueueTypeDef Teseo_Queue_Instance;
  return &Teseo_Queue_Instance;
}

/*
 * Returns the index of a message in the queue.
 */
static int32_t __find_msg_idx(const Teseo_QueueTypeDef *pTeseoQueue, const GNSS_MsgTypeDef *pMsg)
{
  int32_t i;
  
  for (i = 0; i < MAX_MSG_QUEUE; ++i)
  {
    if (&pTeseoQueue->nmea_queue[i] == pMsg)
    {
      return i;
    }
  }
  
  return -1;
}

/*
 * Checks for buffers not yet released.
 */
static void __check_unreleased_buffer(Teseo_QueueTypeDef *pTeseoQueue)
{
#ifdef USE_FREE_RTOS
  if (pTeseoQueue->bitmap_unreleased_buffer_irq == 0UL)
  {
    return;
  }
  
  Console_Debug("R\n\r");
  pTeseoQueue->bitmap_buffer_readable |= pTeseoQueue->bitmap_unreleased_buffer_irq;
  pTeseoQueue->bitmap_unreleased_buffer_irq = 0;
#endif /* USE_FREE_RTOS */
}

/*
 * Checks for messages longer than MAX_MSG_BUF.
 */
static void check_longer_msg(Teseo_QueueTypeDef *pTeseoQueue, const GNSS_MsgTypeDef *pMsg, uint32_t idx, int8_t wr_or_rd)
{
  if (pMsg->len <= (uint32_t)MAX_MSG_BUF)
  {
    return;
  }
  
  uint32_t j;
  uint32_t extra_bufs = (pMsg->len / (uint32_t)MAX_MSG_BUF) + (((pMsg->len % (uint32_t)MAX_MSG_BUF) != 0U) ? 1U : 0U);
  
  for (j = 0; j < extra_bufs; j++)
  {
    uint32_t rhs = (idx + j);

    if (wr_or_rd == 1)
    {
      if(rhs < 32U)
      {
        pTeseoQueue->bitmap_buffer_writable &= ~(1UL << rhs);
      }
    }
    else
    {
      if(rhs < 32U)
      {
        pTeseoQueue->bitmap_buffer_writable |= (1UL << rhs);
      }
    }
  }
}

/* Exported functions --------------------------------------------------------*/
Teseo_QueueTypeDef *teseo_queue_init(void)
{
  Teseo_QueueTypeDef *pTeseoQueue = Teseo_Queue_static_alloc();
  int8_t i;
  GNSS_MsgTypeDef *GNSS_Msg_p;
  
  Console_Debug("teseo_queue_init...\n\r" );
  pTeseoQueue->bitmap_buffer_writable = 0;
  for (i = 0;  i < MAX_MSG_QUEUE; ++i)
  {
    GNSS_Msg_p = &pTeseoQueue->nmea_queue[i];

    GNSS_Msg_p->buf = &pTeseoQueue->single_message_buffer[i * MAX_MSG_BUF];
    GNSS_Msg_p->len = 0;
    pTeseoQueue->bitmap_buffer_writable |=  (1UL << (uint8_t)i);
  }
  pTeseoQueue->bitmap_buffer_readable = 0;

#ifdef USE_FREE_RTOS
  pTeseoQueue->bitmap_unreleased_buffer_irq = 0;
  pTeseoQueue->semaphore = xSemaphoreCreateMutex();
#endif /* USE_FREE_RTOS */

  Console_Debug("teseo_queue_init: Done\n\r");
  
  return pTeseoQueue;
}

GNSS_MsgTypeDef *teseo_queue_claim_wr_buffer(Teseo_QueueTypeDef *pTeseoQueue)
{
  int32_t i;
  GNSS_MsgTypeDef *pMsg;

#ifdef USE_FREE_RTOS
  BaseType_t ret;
  
  ret = semaphore_lock_irq(pTeseoQueue->semaphore);
  
  /* semaphore already taken.... */
  if (ret == pdFAIL) {
    return NULL;
  }
#endif /* USE_FREE_RTOS */

  /* first available buffer writable */
  i = ffs(pTeseoQueue->bitmap_buffer_writable);
  
  if (i == 0) {
#ifdef USE_FREE_RTOS
    /* release the semaphore */
    semaphore_free_irq(pTeseoQueue->semaphore);
#endif /* USE_FREE_RTOS */

    Console_Debug("-\n\r");
    return NULL;
  }
  
  i--; /* first available buffer writable */
  
  /* buffer no more writable */
  pTeseoQueue->bitmap_buffer_writable &= ~(1U << (uint32_t)i);
  
  __check_unreleased_buffer(pTeseoQueue);

#ifdef USE_FREE_RTOS
  semaphore_free_irq(pTeseoQueue->semaphore);
#endif /* USE_FREE_RTOS */

  pMsg = &pTeseoQueue->nmea_queue[i];
  pMsg->len = 0;
  
  return pMsg;
}

void teseo_queue_release_wr_buffer(Teseo_QueueTypeDef *pTeseoQueue, GNSS_MsgTypeDef *pMsg)
{
  int32_t i;
#ifdef USE_FREE_RTOS
  BaseType_t ret;
#endif /* USE_FREE_RTOS */
  
  if (pMsg == NULL) {
    return;
  }
  
  i = __find_msg_idx(pTeseoQueue, pMsg);
  if (i < 0) {
    /* this should NEVER happen... this means an external buffer was provided */
    return;
  }
  
#ifdef USE_FREE_RTOS 
  ret = semaphore_lock_irq(pTeseoQueue->semaphore);
  
  /* semaphore already taken.... */
  if (ret == pdFAIL) {
    Console_Debug("+\n\r" );
    /* mark the buffer as 'un-released'... and go-ahead... */
    pTeseoQueue->bitmap_unreleased_buffer_irq |= (1UL << (uint32_t)i);
    return;
  }
#endif /* USE_FREE_RTOS */
  
  /* mark the buffer as readable */
  pTeseoQueue->bitmap_buffer_readable |= (1UL << (uint32_t)i);

  /* check for longer message */
  check_longer_msg(pTeseoQueue, pMsg, (uint32_t)i, 1);

#ifdef USE_FREE_RTOS
  __check_unreleased_buffer(pTeseoQueue);
  semaphore_free_irq(pTeseoQueue->semaphore);
#endif /* USE_FREE_RTOS */
}

const GNSS_MsgTypeDef *teseo_queue_claim_rd_buffer(Teseo_QueueTypeDef *pTeseoQueue)
{
  const GNSS_MsgTypeDef *pMsg = NULL;
  int32_t i;

  uint8_t rd_buffer_re_try = 1;
  
  while(rd_buffer_re_try == 1U) {
#ifdef USE_FREE_RTOS

    semaphore_lock(pTeseoQueue->semaphore);
#endif /* USE_FREE_RTOS */

    /* first available readable buffer */
    i = ffs(pTeseoQueue->bitmap_buffer_readable);
    
    if (i == 0) {
#ifdef USE_FREE_RTOS
      /* release the semaphore */
      semaphore_free(pTeseoQueue->semaphore);
      //Console_Debug("No read buffer available... going to sleep...\n\r");
      vTaskDelay(portTICK_PERIOD_MS * 5U);
      continue;
#else
      break;
#endif /* USE_FREE_RTOS */
    }

    /* first available readable buffer */
    i -= 1;
    /* buffer no more readable */
    pTeseoQueue->bitmap_buffer_readable &= ~(1UL << (uint32_t)i);
    pMsg = &pTeseoQueue->nmea_queue[i];

#ifdef USE_FREE_RTOS
    semaphore_free(pTeseoQueue->semaphore);
#endif /* USE_FREE_RTOS */

    rd_buffer_re_try = 0;
  }
  return pMsg;
}

void teseo_queue_release_rd_buffer(Teseo_QueueTypeDef *pTeseoQueue, const GNSS_MsgTypeDef *pMsg)
{ 
  int32_t i;
  
  i = __find_msg_idx(pTeseoQueue, pMsg);
  if (i < 0) {
    /* this should NEVER happen... this means an external buffer was provided */
    return;
  }
#ifdef USE_FREE_RTOS
  semaphore_lock(pTeseoQueue->semaphore);
#endif /* USE_FREE_RTOS */

  /* mark the buffer as writeable */
  pTeseoQueue->bitmap_buffer_writable |= (1UL << (uint32_t)i);

  /* check for longer message */
  check_longer_msg(pTeseoQueue, pMsg, (uint32_t)i, 0);

#ifdef USE_FREE_RTOS
  semaphore_free(pTeseoQueue->semaphore);
#endif /* USE_FREE_RTOS */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
