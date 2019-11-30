/**
 ******************************************************************************
 * @file    console.h
 * @author  MCD Application Team
 * @brief   Header for dbg_trace.c
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UTIL_CONSOLE_H
#define __UTIL_CONSOLE_H

#include <stdint.h>
#include "trace.h"
#include "systime.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define PPRINTF(...)            PRINTF(__VA_ARGS__)

#ifdef LORA_SMART_TRACKER
  #ifdef DEBUG
			#if defined ( __ICCARM__ )
				#define PRINTF(...)            do{DBG_PRINTF_LOG(0, 0, __VA_ARGS__);extern uint8_t bDebuggerConnected;if(bDebuggerConnected)printf(__VA_ARGS__);}while(0)
			#else //( __ICCARM__ )
				#define PRINTF(...)            do{DBG_PRINTF_LOG(0, 0, __VA_ARGS__);}while(0)
			#endif
    #define PRINTF_SAFE(...)         do{DBG_PRINTF_LOG(1, 0, __VA_ARGS__);}while(0)
  #else //DEBUG
    #define PRINTF(...)
    #define PRINTF_SAFE(...)
  #endif //DEBUG
#else// LORA_SMART_TRACKER
  #define PRINTF(...)     do{  TraceSend(__VA_ARGS__); }while(0)
  #define PRINTF_SAFE(...)         do{DBG_PRINTF_LOG_SAFE(0, __VA_ARGS__);}while(0)
#endif // LORA_SMART_TRACKER

  #include "usb_user.h"

#define PRINTNOW()      /*do{                                                           \
                          SysTime_t stime  =SysTimeGetMcuTime();                      \
                          TraceSend("%3ds%03d: ",stime.Seconds, stime.SubSeconds); \
                         }while(0)  */

#define TVL1(X)    do{ if(VERBOSE_LEVEL>=VERBOSE_LEVEL_1) { X } }while(0);
#define TVL2(X)    do{ if(VERBOSE_LEVEL>=VERBOSE_LEVEL_2) { X } }while(0);


#ifdef __cplusplus
}
#endif

#endif /*__UTIL_CONSOLE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
