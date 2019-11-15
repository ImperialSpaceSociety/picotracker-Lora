/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2013 - 2016 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "stm32l1xx.h"                  // Device header
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons



volatile uint32_t msTicks;                      /* counts 1ms timeTicks       */
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;
}

/*----------------------------------------------------------------------------
  delays number of tick Systicks (happens every 10 ms)
 *----------------------------------------------------------------------------*/
void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) { __NOP(); }
}

/*----------------------------------------------------------------------------
  configure SystemCoreClock:
     System Clock source         PLL(HSI)
     SYSCLK                      32000000 Hz
     HCLK                        32000000 Hz
     AHB Prescaler               1
     APB1 Prescaler              1
     APB2 Prescaler              1
     HSI Frequency               16000000 Hz
     PLL DIV                     3
     PLL MUL                     6
     Flash Latency               1 WS
     SDIO clock (SDIOCLK)        48000000 Hz
     Require 48MHz for USB clock Disabled
 *----------------------------------------------------------------------------*/
static void SystemCoreClockConfigure(void) {

  RCC->CR |= ((uint32_t)RCC_CR_HSION);               /* Enable HSI */
  while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY) __NOP();

  FLASH->ACR |= FLASH_ACR_ACC64;                     /* Enable 64-bit access */
  FLASH->ACR |= FLASH_ACR_PRFTEN;                    /* Enable Prefetch Buffer */
  FLASH->ACR |= FLASH_ACR_LATENCY;                   /* Flash 1 wait state */

  RCC->APB1ENR |= RCC_APB1ENR_PWREN;                 /* Enable the PWR APB1 Clock         */
  PWR->CR = PWR_CR_VOS_0;                            /* Select the Voltage Range 1 (1.8V) */
  while((PWR->CSR & PWR_CSR_VOSF) != 0);             /* Wait for Voltage Regulator Ready  */

  RCC->CFGR |= (RCC_CFGR_HPRE_DIV1  |                /* HCLK = SYSCLK / 1 */
                RCC_CFGR_PPRE2_DIV1 |                /* PCLK2 = HCLK / 1 */
                RCC_CFGR_PPRE1_DIV2  );              /* PCLK1 = HCLK / 2 */

  RCC->CFGR &= ~(RCC_CFGR_PLLSRC   |                 /* clear settings */
                 RCC_CFGR_PLLMUL   |
                 RCC_CFGR_PLLDIV    );
  RCC->CFGR |=  (RCC_CFGR_PLLSRC_HSI |               /* configure PLL */
                 RCC_CFGR_PLLDIV3    |
                 RCC_CFGR_PLLMUL6     );


  RCC->CR |= RCC_CR_PLLON;                           /* Enable PLL */
  while((RCC->CR & RCC_CR_PLLRDY) == 0) __NOP();     /* Wait till PLL is ready */

  RCC->CFGR &= ~(RCC_CFGR_SW);                       /* clear settings */
  RCC->CFGR |= RCC_CFGR_SW_PLL;                      /* Select PLL as system clock source */
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) __NOP();
}


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
  int32_t num = -1;
  int32_t dir =  1;
  uint32_t btns = 0;
  uint32_t ledNum = LED_GetCount();

  SystemCoreClockConfigure();
  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */

  LED_Initialize();
  Buttons_Initialize();

  if (SysTick_Config(SystemCoreClock / 100)) {  /* SysTick 10 msec interrupts */
    while (1);                                  /* Capture error              */
  }

  while(1) {                                    /* Loop forever               */
    btns = Buttons_GetState();                  /* Read button state          */

    if (btns != (1UL << 0)) {
      /* Calculate 'num': 0,1,...,LED_NUM-1,LED_NUM-1,...,1,0,0,...  */
      num += dir;
      if (num == ledNum) { dir = -1; num =  ledNum-1; }
      else if   (num < 0) { dir =  1; num =  0;         }

      LED_On (num);
      Delay(10);                                /* Delay 100ms                */
      LED_Off(num);
      Delay(40);                                /* Delay 400ms                */
    }
    else {
      LED_SetOut ((1ul << ledNum) - 1);
      Delay(10);                                /* Delay 10ms                 */
    }
  }

}
