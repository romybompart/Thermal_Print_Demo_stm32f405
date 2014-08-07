#ifndef __DELAY_H
#define __DELAY_H

#include <stm32f4xx.h>

static __IO uint32_t uwTimingDelay;
extern void Delays(__IO uint32_t nTime);
extern void Delayms(__IO uint32_t nTime);
extern void Delayus(__IO uint32_t nTime);
extern void InitDelay(__IO uint32_t TickDivider);
extern void TimingDelay_Decrement(void);
extern void Change_Clock(int PLL_M, uint16_t PLL_N,int PLL_P,int PLL_Q);
#endif
