/**
  ******************************************************************************
  * @file    PrintCode/header_hardware.c
  * @author  Romy Bompart - HARDWARE TEAM from The Factory HKA,CA
	* @location	Caracas, Venezuela
  * @version V1.0.1
  * @date    25-Febrary-2014
  * @brief   Printing Process Control 
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 <The Factory HKA, C.A.>
	*	Permission is hereby granted, free of charge, to any person obtaining a copy
	*	of this software and associated documentation files (the "Software"), to deal
	*	in the Software without restriction, including without limitation the rights
	*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	*	copies of the Software, and to permit persons to whom the Software is
	*	furnished to do so, subject to the following conditions:
	*
	*	The above copyright notice and this permission notice shall be included in
	*	all copies or substantial portions of the Software.
	*
	*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	*	THE SOFTWARE.
  ******************************************************************************
  */
#include "header_hardware.h"
#include <math.h>

/* variables ---------------------------------------------------------*/
#ifndef USE_TB6608FNGCT
uint8_t current_pos = 1;
#else
extern uint32_t PWM_COUNTER;
PWM_HeaderTimeStructure PWM;
#endif

uint16_t STBx_Pin[] = {STB1_PIN,STB2_PIN,STB3_PIN,STB4_PIN,STB5_PIN,STB6_PIN};
GPIO_TypeDef* STBx_Port[] = {STB1_PORT,STB2_PORT,STB3_PORT,STB4_PORT,STB5_PORT,STB6_PORT};
uint32_t STBx_Port_Clk[] = {STB1_PORT_CLK,STB2_PORT_CLK,STB3_PORT_CLK,STB4_PORT_CLK,STB5_PORT_CLK,STB6_PORT_CLK};

__IO uint16_t ADCConvertedValue;

/** 
  * @brief  Header Init function, this function configure every port pin used 
  *  to drive the printer header. 	
  */
uint8_t Header_Init(void)
{
	GPIO_InitTypeDef GPIO_Struct;
	uint8_t x;
	/**
	*@Title		Control OUTPUT pins configuration Part1:
	*	1.- STB line(s)
	* 2.- Latch line
	* 3.- Motor Lines:
	*		3.1- L293D
	*		3.2- TB6608FNGCT
	*	4.-	SPI lines
	* 5.- Power Supply Controllines
	*		5.1- Header Power Supply
	*		5.2- Photo Diode Emitter Supply
	* 6.- Photo Diode Emitter line
	* 7.- Thermistor line
	**/	
	
	/**
	*@brief STB line(s) configuration
	**/
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;
	for(x = 0; x < STB_NUMBER;  x++)
	{
		RCC_AHB1PeriphClockCmd(STBx_Port_Clk[x],ENABLE);
		GPIO_Struct.GPIO_Pin = STBx_Pin[x];
		GPIO_Init(STBx_Port[x], &GPIO_Struct);
		//Setting the initial condition for STBx Line
		GPIO_ResetBits(STBx_Port[x],STBx_Pin[x]);
	}
	/**
	*@brief Latch Line configuration
	**/
	RCC_AHB1PeriphClockCmd(LATCH_PORT_CLK,ENABLE);
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Struct.GPIO_Pin = LATCH_PIN;
	GPIO_Init(LATCH_PORT, &GPIO_Struct);
	//Setting the initial condition for latch
	LATCH_DISABLE;
  /**
	*@Title Motor Lines configuration
	**/
	#ifdef USE_L293D
		/**
		*@brief Phases Configuration
		**/
		RCC_AHB1PeriphClockCmd(HEADER_M2CRTL_PORT_CLK,ENABLE);
		GPIO_Struct.GPIO_Pin = PH12_PIN | PH21_PIN | PH22_PIN | ENABLE2_PIN;
		GPIO_Init(HEADER_PORT_GROUP_D, &GPIO_Struct);
		GPIO_ResetBits(HEADER_PORT_GROUP_D,PH12_PIN | PH21_PIN | PH22_PIN | ENABLE2_PIN);
		/**
		*@brief Enable pins Configuration
		**/
		RCC_AHB1PeriphClockCmd(HEADER_E1CRTL_PORT_CLK,ENABLE);
		GPIO_Struct.GPIO_Pin = ENABLE1_PIN;
		GPIO_Init(HEADER_PORT_GROUP_C, &GPIO_Struct);
		GPIO_ResetBits(HEADER_PORT_GROUP_C,ENABLE1_PIN);
	#else //USE_TB6608FNGCT
		/**
		*@brief ENABLE Configuration
		**/
		RCC_AHB1PeriphClockCmd(ENABLE_PORT_CLK, ENABLE);
		GPIO_Struct.GPIO_Pin = ENABLE_PIN;
		GPIO_Init(ENABLE_PORT, &GPIO_Struct);
		MOTOR_DISABLE;
		/**
		*@brief CW/CCW Configuration
		**/
		RCC_AHB1PeriphClockCmd(CW_CCW_PORT_CLK, ENABLE);
		GPIO_Struct.GPIO_Pin = CW_CCW_PIN;
		GPIO_Init(CW_CCW_PORT, &GPIO_Struct);
		CW_ENABLE;
		/**
		*@brief CK Configuration
		*@description TIM1_CH1 (PB13)
		**/
		RCC_AHB1PeriphClockCmd(CK_PORT_CLK, ENABLE);
		GPIO_Struct.GPIO_Pin = CK_PIN;
		GPIO_Struct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Struct.GPIO_OType = GPIO_OType_PP;
		GPIO_Struct.GPIO_PuPd = GPIO_PuPd_DOWN ;
		GPIO_Init(CK_PORT, &GPIO_Struct); 
		/* Connect TIM1 pins to AF2 */  
		GPIO_PinAFConfig(CK_PORT, CK_PIN_SOURCE, GPIO_AF_TIM1);
		/* Cofiguring TIMx to enable a clock signal to the IC*/
		Init_HTIMx();
		/**/
	#endif
	/**
	*@Title		SPI pins configuration
	**/
	RCC_AHB1PeriphClockCmd(HEADER_PORT_SCK_CLK,ENABLE);
	GPIO_Struct.GPIO_Pin = HEADER_PIN_MOSI | HEADER_PIN_SCK;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(HEADER_PORT_MOSI, &GPIO_Struct);
	GPIO_PinAFConfig(HEADER_PORT_MOSI,HEADER_PIN7_SOURCE,HEADER_SPI_AF);
	GPIO_PinAFConfig(HEADER_PORT_SCK,HEADER_PIN5_SOURCE,HEADER_SPI_AF);
	/*SPI initialization*/
	Init_HPrinterSPI();
	/*Clearing Buffer */
	ClearPrinterBuffer();
	
	/**
	*@Title		Power Supply Control
	*@Description Header Power Supply
	**/
	RCC_AHB1PeriphClockCmd(VH_PORT_CLK,ENABLE);
	GPIO_Struct.GPIO_Pin = VH_PIN;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(VH_PORT, &GPIO_Struct);
	DISABLE_VH;
	/**
	*@Description Photo Transistor Power Supply
	**/
	RCC_AHB1PeriphClockCmd(PEM_CONTROL_PORT_CLK,ENABLE);
	GPIO_Struct.GPIO_Pin = PEM_CONTROL_PIN;
	GPIO_Init(PEM_CONTROL_PORT, &GPIO_Struct);
	DISABLE_PEM;
	/**
	*@Title Photo Diode Emitter configuratio
	**/
	GPIO_Struct.GPIO_Pin = PEM_PIN;
  GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(PEM_PORT, &GPIO_Struct);
	/**
	*@Title	Thermistor
	**/
	RCC_AHB1PeriphClockCmd(RCCTHERMISTORPORT,ENABLE);
  GPIO_Struct.GPIO_Pin = THERMISTORPIN;
  GPIO_Struct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz ;
  GPIO_Init(THERMISTORPORT,&GPIO_Struct);
	Init_HADC();

	return IsPaper();
}

/**
	*@function Init_HPrinterSPI()
	*@brief	This function allows the configuration of SPI for Header
**/
void Init_HPrinterSPI()
{
	SPI_InitTypeDef SPI_Struct;
	
	RCC_APB2PeriphClockCmd(HEADER_SPI_Cmd,ENABLE);
	SPI_Struct.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_Struct.SPI_Mode = SPI_Mode_Master; 
	SPI_Struct.SPI_DataSize = SPI_DataSize_16b; 
	SPI_Struct.SPI_CPOL = SPI_CPOL_Low; 
	SPI_Struct.SPI_CPHA = SPI_CPHA_1Edge; 
	SPI_Struct.SPI_NSS = SPI_NSS_Soft; 
	SPI_Struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; 
	SPI_Struct.SPI_FirstBit = SPI_FirstBit_MSB; 
	SPI_Init(HEADER_SPI, &SPI_Struct); 
	SPI_Cmd(HEADER_SPI, ENABLE);           /* Enable the SPI  */  
}


#ifndef USE_L293D

/**
	*@function Init_HPrinterSPI()
	*@brief	This function configurates the timmer 1 to use it as a PWM
**/
void Init_HTIMx()
{
	 /* -----------------------------------------------------------------------
    TIM1 Configuration: generates 1 PWM signal with 50% of duty cycles.
    
    TIM1 input clock (TIM1CLK) is set to 2 * APB2 clock (PCLK2), 
    since APB2 prescaler is different from 1.   
      TIM1CLK = 2 * PCLK2  
      PCLK2 = HCLK / 2 
      => TIM1CLK = HCLK = SystemCoreClock 
    
    To get TIM1 counter clock at 21 MHz, the prescaler is computed as follows:
       Prescaler = (TIM1CLK / TIM1 counter clock) - 1
       Prescaler = ((SystemCoreClock) /21 MHz) - 1 , In our case SystemCoreClock =  168Mhz
			 Prescaler = ((168Mhz)/21Mhz) - 1 = 7  (We don't use it, but we wrote it if will be necesary)
	    
	     Note:
       It isn't necessary for frequencies which results an ARR value lower than 65535.
			 Prescaler is used when a Period is requeried but its value is higher than 65535. 
			 So a Prescaler might be calculate to achieve a suitable value for ARR register. 
                                              
    To get TIM1 output clock at 30 KHz, (the period (ARR)) is computed as follows:
       TIM1_ARR = (TIM1 counter clock / TIM1 output clock) - 1
       TIM1_ARR  = ( 21Mhz / 30Khz ) - 1 = 699
                  
    TIM1 Channel1 duty cycle = (TIM1_CCR1/ TIM1_ARR)* 100 = 50%
	  TIM1_CCR1 = 0.5 * TIM1_ARR = 139.8 aprox. 140

    Note: 
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
     function to update SystemCoreClock variable value. Otherwise, any configuration
     based on this variable will be incorrect.
     
     To understand how do HEADER_PWM_ARR and HEADER_PWM_CCR are configured, please go to 
     header_hardware.h at line 146 and 147.	 
  ----------------------------------------------------------------------- */   
	TIM_TimeBaseInitTypeDef  PWM_TimeBaseStructure;
  TIM_OCInitTypeDef  PWM_OCInitStructure;
	PWM_HeaderTimeStructure Settings;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the TIM1 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	/* Calculating ARR and CCR, and Prescaler if it is necesary*/	
	Settings = BaseTimePwm(HEADER_PWM_FREQ, 1, DISABLE);
	
  /* Time base configuration */
  PWM_TimeBaseStructure.TIM_Period = Settings.ARR; // Period of time.
  PWM_TimeBaseStructure.TIM_Prescaler = Settings.Prescaler; //Prescaler 
  PWM_TimeBaseStructure.TIM_ClockDivision = 0;
  PWM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	PWM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(HEADER_PWM, &PWM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  PWM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  PWM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	PWM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  PWM_OCInitStructure.TIM_Pulse = Settings.CCR; // Duty Cicly
  PWM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  PWM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  PWM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  PWM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  
	TIM_OC1Init(HEADER_PWM, &PWM_OCInitStructure);
 	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_CCxNCmd(TIM1,TIM_Channel_1,TIM_CCxN_Disable);
	
	/* TIM IT enable */
  TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
}

/**
	*@function PWMBaseTimeChanging
	*@brief	This function allows the changing of PWM frequency
**/
void PWMBaseTimeChanging(PWM_HeaderTimeStructure Settings)
{
	TIM_TimeBaseInitTypeDef  PWM_TimeBaseStructure;

	  /* Time base configuration */
  PWM_TimeBaseStructure.TIM_Period = Settings.ARR; // Period of time.
  PWM_TimeBaseStructure.TIM_Prescaler = Settings.Prescaler; //Prescaler 
  PWM_TimeBaseStructure.TIM_ClockDivision = 0;
  PWM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	PWM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(HEADER_PWM, &PWM_TimeBaseStructure);
	
	TIM_SetCompare1(TIM1, Settings.CCR);
}

/**
	*@function BaseTimePwm
	*@brief	This function computes the necessary values to setting the PWM frequency at 50% of Duty Cycle
**/
PWM_HeaderTimeStructure BaseTimePwm(uint32_t Frequency, uint16_t NumbOfPulses,FunctionalState NewState)
{
	volatile uint32_t ARR = 0;

	PWM.CFrequency = Frequency;

	PWM.Prescaler = 41;
	PWM.ARR = (uint16_t)((float) (((SystemCoreClock/((PWM.Prescaler+1)*PWM.CFrequency)) - 1)));
	
	PWM.CCR = (uint16_t) ((PWM.ARR/2));
	PWM.NumbOfPulses = NumbOfPulses;
	PWM.EnableToCount = NewState;
	
	return PWM;
}
#endif

/**
	*@function Init_HADC
	*@brief	This function configures the ADC channel 
**/
void Init_HADC()
{
	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	/* Enable peripheral clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStruct);
	
	/*ADC Configuration */
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
  ADC_InitStruct.ADC_ScanConvMode=DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConv=DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
	ADC_InitStruct.ADC_DataAlign= ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1,&ADC_InitStruct);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_144Cycles); // PC3
	ADC_Cmd(ADC1,ENABLE);	
}

#ifdef USE_L293D
/**
	*@function Motor_Stepper_Pos
	*@brief	This function move the motor with the L293 Driver
**/
void Motor_Stepper_Pos(uint8_t Position)
{
	  Delayus(6700);
		switch(Position){
			case 0:
				GPIO_ResetBits(PH11_PORT,PH11_PIN);
				GPIO_ResetBits(PH12_PORT,PH12_PIN);
				GPIO_ResetBits(PH21_PORT,PH21_PIN);			
				GPIO_ResetBits(PH22_PORT,PH22_PIN);
			break;
			case 1:
				GPIO_SetBits(PH11_PORT,PH11_PIN);
				GPIO_ResetBits(PH12_PORT,PH12_PIN);
				GPIO_ResetBits(PH21_PORT,PH21_PIN);			
				GPIO_SetBits(PH22_PORT,PH22_PIN);
 			break;
			case 2:
				GPIO_SetBits(PH11_PORT,PH11_PIN);
				GPIO_ResetBits(PH12_PORT,PH12_PIN);
				GPIO_SetBits(PH21_PORT,PH21_PIN);			
				GPIO_ResetBits(PH22_PORT,PH22_PIN);
			break;
			case 3:
				GPIO_ResetBits(PH11_PORT,PH11_PIN);
				GPIO_SetBits(PH12_PORT,PH12_PIN);
				GPIO_SetBits(PH21_PORT,PH21_PIN);			
				GPIO_ResetBits(PH22_PORT,PH22_PIN);
			break;
			case 4:
				GPIO_ResetBits(PH11_PORT,PH11_PIN);
				GPIO_SetBits(PH12_PORT,PH12_PIN);
				GPIO_ResetBits(PH21_PORT,PH21_PIN);			
				GPIO_SetBits(PH22_PORT,PH22_PIN);
			break;
		}
}
#endif

/**
	*@function feed_pitch
	*@brief	This function drives the feeding paper procedure 
	*@note This function depends on the chip that is implemented etheir
  *    L293D or TB6608FNGCT
**/
uint8_t feed_pitch(uint64_t lines, uint8_t forward_backward)
{
	#ifdef USE_L293D
	uint8_t pos = current_pos;
	uint8_t restor =  ~forward_backward;
	
	restor &= 0x01;
	
	if(lines>0)
	{
		MOTOR_ENABLE1;
		MOTOR_ENABLE2;
		while(lines>0)
		{

			Motor_Stepper_Pos(pos);     /* 0.0625mm */

			if(pos >= 1 && pos <= 4)
        pos = pos + (1 - 2*forward_backward); // adding or subtracting
			if(pos < 1 || pos > 4)
				pos = pos + (4 - 8*restor); // restoring pos
			
			lines--;
		}
	  MOTOR_DISABLE1;
		MOTOR_DISABLE2;
	}
	else
	{
		return ERROR_FEED_PITCH;
  }
	current_pos = pos;
	return 0;
	#else
	if(lines>0)
	{
		ENABLE_VH;			
		if(!forward_backward)
		{CW_ENABLE;}
		else
		{CCW_ENABLE;}
		MOTOR_ENABLE;
		PWM.NumbOfPulses = lines;
		PWM.EnableToCount = ENABLE;
		TIM_Cmd(TIM1, ENABLE);
		TIM_CCxNCmd(TIM1,TIM_Channel_1,TIM_CCxN_Enable);
		Delayus(3);
		while(PWM.EnableToCount == ENABLE){Delayus(1);}
		return 0;
	}
	else
	{
		return ERROR_FEED_PITCH;
  }
	#endif
}

/**
	*@function PrintDots
	*@brief	This function drives the printing line dots procedure 
**/
void PrintDots(uint16_t *Array, uint8_t characters) 
{
	uint8_t i=0,y=0, MAX = Maxcharacterperline;
	    
		ENABLE_VH;
			while((i<characters) && (i<MAX))
			{
				Printer_SendWorld(Array[i]);
				i++;
			}
			
			while( i < MAX)
			{
				Printer_SendWorld(0x0000);
				i++;
			}
			
			LATCH_ENABLE;
				Delayus(1);
			LATCH_DISABLE;
				Delayus(1);
			i =0;
      while(y<STB_NUMBER)
			{
					while(i <10)
					{
						GPIO_SetBits(STBx_Port[y],STBx_Pin[y]);
						Delayus(550);
						GPIO_ResetBits(STBx_Port[y],STBx_Pin[y]);
						Delayus(14);
						i++;
					}
					y++;
			}
		feed_pitch(4,BACKWARD);
		DISABLE_VH;
}
/**
	*@function Printer_SendWorld
	*@brief	This function send 16 bits once to the printer mechanism
**/
void Printer_SendWorld(uint16_t World)
{
	SPI_I2S_SendData(HEADER_SPI,World);
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
}
/**
	*@function ClearPrinterBuffer
	*@brief	This function sends 0x0000 twenty four times to the printer mechanism and load
  *         the data into the the latch register of the printer mechanism. 
**/
void ClearPrinterBuffer()
{
	uint8_t i= 0;
	
	 for(i=0;i<24;i++)
	   Printer_SendWorld(0x0000);
	
	LATCH_ENABLE;
	Delayus(1);
  LATCH_DISABLE;
	Delayus(1);
}
/**
	*@function IsPaper
	*@brief	This function detects whether the paper is mounted or not. 
**/
uint8_t IsPaper()
{
	uint8_t status;
	ENABLE_PEM;
	Delayms(1);
	if(!ASK4PAPER)
	{status = IS_PAPER;}
	else
	{status = NO_PAPER;}
	DISABLE_PEM;

return status;
}
/**
	*@function temperature
	*@brief	This function senses the voltage from the RTC and converts it on 
  *         temperature 
**/
double temperature(uint8_t Grade_K_C)
{  
	double Rthermistor = 0, TempThermistor = 0, ADCSamples=0;
	int Sample = 1;
	
	assert_param(IS_TNUMSAMPLES_ADC(NumSamples));
	/* Start ADC1 Software Conversion */ 
	while(Sample<=NumSamples)
	{
		ADC_SoftwareStartConv(ADC1); 
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		{}	
			ADCSamples += ADC_GetConversionValue(ADC1);
			Sample++;
	}
	/*Thermistor Resistance at x Kelvin*/
  ADCConvertedValue = ADCSamples/NumSamples;
	Rthermistor = (ADCResolution/ADCConvertedValue) - 1;
	Rthermistor =  SeriesResistor/Rthermistor;
	/*Thermistor temperature in Kelvin*/
	TempThermistor =  Rthermistor / RthNominal ;
	TempThermistor =  log(TempThermistor);
	TempThermistor /= BCoefficent;
	TempThermistor +=  (1/(TempNominal + 273.15));
	TempThermistor = 1/TempThermistor;
	if (Grade_K_C == KELVIN)
	/*Thermistor temperature in Kelvin*/
		return TempThermistor;
	else
	/*Thermistor temperature in Celcius*/
		return	(TempThermistor - 273.15);
}

/*Sólo se progresa cuando se piensa que siempre se puede hacer algo más.*/
/*Guillermo Marconi*/
