#include "Delay.h"

//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8)
//  Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
//     
//        - Reload Value is the parameter to be passed for SysTick_Config() function
//        - Reload Value should not exceed 0xFFFFFF
void InitDelay(__IO uint32_t BaseTime)
{
		RCC_ClocksTypeDef    RCC_Clocks;
		RCC_GetClocksFreq(&RCC_Clocks);
	  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
		if(SysTick_Config((uint32_t)(BaseTime*(RCC_Clocks.HCLK_Frequency))/1000000))
				while(1); // capture an error	
}

void Delays(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime*1000000;
  while(uwTimingDelay != 0){};
}

void Delayms(__IO uint32_t nTime)
{
	uwTimingDelay = nTime*1000;
  while(uwTimingDelay != 0){};
}

void Delayus(__IO uint32_t nTime)
{
	uwTimingDelay = nTime;
  while(uwTimingDelay != 0){};
}

void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}

extern void Change_Clock(int PLL_M, uint16_t PLL_N,int PLL_P,int PLL_Q)
{//int PLL_M=25, PLL_N=336,PLL_P =2, PLL_Q =7;//SystemCoreClock=168000000;

	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	RCC_WaitForHSEStartUp();
	 
	
	 RCC_PLLConfig(RCC_PLLSource_HSE,PLL_M,PLL_N,PLL_P,PLL_Q);
	 RCC_PLLCmd(ENABLE);
	   while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
   
	 //Delays(0x0F);
	 RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	 RCC_HCLKConfig(RCC_SYSCLK_Div1);
	 RCC_PCLK1Config(RCC_HCLK_Div4);
	 RCC_PCLK2Config(RCC_HCLK_Div2);
	 SystemCoreClockUpdate();
	
}
