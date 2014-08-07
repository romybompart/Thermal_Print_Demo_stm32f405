/**
  ******************************************************************************
  * @file    PrintCode/header_hardware.h 
  * @author  Romy Bompart - HARDWARE TEMAN from The Factory HKA,CA
  * @version V1.0.1
  * @date    25-Febrary-2014
  * @brief   header file of header_hardware.c
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

#ifndef __HEADER_HARDWARE_H
#define __HEADER_HARDWARE_H

#include "main.h"
#include "fonts.h"

/** @addtogroup Header Pin Assignment and ports.
  * @{
  */
	
/** @brief SPI Pins pin configuration 
  *	@addtogroup SPI
  * @{
	*/
#define HEADER_SPI						SPI1
#define	HEADER_SPI_Cmd				RCC_APB2Periph_SPI1
#define HEADER_PIN_MOSI				GPIO_Pin_7
#define HEADER_PORT_MOSI			GPIOA
#define HEADER_PIN_MISO				GPIO_Pin_6
#define HEADER_PORT_MISO			GPIOA
#define HEADER_PIN_SCK				GPIO_Pin_5
#define HEADER_PORT_SCK				GPIOA
#define HEADER_PORT_SCK_CLK	 	RCC_AHB1Periph_GPIOA

#define HEADER_SPI_AF					GPIO_AF_SPI1
#define HEADER_PIN7_SOURCE		GPIO_PinSource7
#define HEADER_PIN5_SOURCE		GPIO_PinSource5
/**
	* @}
  * @brief Control Pins pin configuration 
  *	@addtogroup Pin control
  * @{
	*/
	
#define VH_PIN						GPIO_Pin_5
#define VH_PORT						GPIOC
#define VH_PORT_CLK				RCC_AHB1Periph_GPIOC

#define LATCH_PIN					GPIO_Pin_6
#define LATCH_PORT        GPIOA
#define LATCH_PORT_CLK		RCC_AHB1Periph_GPIOA

#define	PEM_CONTROL_PIN				GPIO_Pin_4
#define PEM_CONTROL_PORT			GPIOC
#define PEM_CONTROL_PORT_CLK	RCC_AHB1Periph_GPIOC
#define PEM_PIN								GPIO_Pin_0
#define PEM_PORT							GPIOC
#define	PEM_PORT_CLK					RCC_AHB1Periph_GPIOC
/**
	*@brief STB_NUMBER stand for STROBE NUMBER of lines, which means how many lines
	*        are going to be activated
**/
#define STB_NUMBER				1
/**
	*@comment In the case that use more than one, you should define STBx_PIN, STBx_PORT
	*          and STBx_PORT_CLK
**/
#define STB1_PIN					GPIO_Pin_4
#define	STB1_PORT					GPIOA
#define STB1_PORT_CLK			RCC_AHB1Periph_GPIOA
#define STB2_PIN					0
#define	STB2_PORT					0
#define STB2_PORT_CLK			0
#define STB3_PIN					0
#define	STB3_PORT					0
#define STB3_PORT_CLK			0
#define STB4_PIN					0
#define	STB4_PORT					0
#define STB4_PORT_CLK			0
#define STB5_PIN					0
#define	STB5_PORT					0
#define STB5_PORT_CLK			0
#define STB6_PIN					0
#define	STB6_PORT					0
#define STB6_PORT_CLK			0

/**
*@brief Motor designation pins
*@Descriptio CHIP_Driver Selects the Driver which is integrated into the printer
* Machine Mechanism Motor designation pins
*@Argument For CHIP_DRIVER:
*										1- TB6608FNGCT
*										2- L293D
**/
#define USE_TB6608FNGCT

#ifndef USE_TB6608FNGCT
	#define USE_L293D
#endif

#ifdef USE_L293D
	#define PH11_PIN								GPIO_Pin_9  //IN1 pin at L293D
	#define	PH11_PORT								GPIOB
	#define PH12_PIN								GPIO_Pin_8  //IN3 pin at L293D
	#define	PH12_PORT								GPIOD
	#define PH21_PIN								GPIO_Pin_10 //IN2 pin at L293D
	#define	PH21_PORT								GPIOD
	#define PH22_PIN								GPIO_Pin_9  //IN4 pin at L293D
	#define	PH22_PORT								GPIOD
	#define HEADER_M1CRTL_PORT_CLK 	RCC_AHB1Periph_GPIOB
	#define HEADER_M2CRTL_PORT_CLK 	RCC_AHB1Periph_GPIOD

	#define ENABLE1_PIN							GPIO_Pin_7
	#define ENABLE1_PORT						GPIOC
	#define ENABLE2_PIN							GPIO_Pin_11
	#define ENABLE2_PORT						GPIOD
	#define HEADER_E1CRTL_PORT_CLK 	RCC_AHB1Periph_GPIOC
	#define HEADER_E2CRTL_PORT_CLK 	RCC_AHB1Periph_GPIOD
	
#else //USE_TB6608FNGCT
	#define ENABLE_PIN				GPIO_Pin_0
	#define ENABLE_PORT				GPIOB
	#define	ENABLE_PORT_CLK		RCC_AHB1Periph_GPIOB

	#define CK_PIN						GPIO_Pin_13
	#define CK_PORT						GPIOB
	#define	CK_PORT_CLK				RCC_AHB1Periph_GPIOB
	#define CK_PIN_SOURCE		  GPIO_PinSource13
	
	#define HEADER_PWM					TIM1
/**
	*@brief HEADER_PWM_FREQ determines the frequency of clock that is going to 
	*        move the motor, step by step. 
	*@Notes: Each step motor is 0.0625mm that the paper is going to roll, so 
	*         on each clock edge we are going to have 0.0625mm. If we fix 
	*         a frequency of 2400Hz for example, 2400 clock edges are going
	*         to occur, therefore the paper is going to roll at this speed:
  *         SPPED MOTOR [mm/s] = PWM_Frequency(Hz) * 0.0625mm 
	*
	*         SPEED MOTOR = 2400Hz *  0.0625mm = 150mm*Hz = 150mm/s 
	*
	*@WARNING:       !!!! HEADER_PWM_FREQ can't be more than 2400Hz  !!!!
	*                          according with the Datasheet
**/
	#define HEADER_PWM_FREQ     ((uint16_t)2400) // PWM FREQUENCY in Hz
	#define IS_PWM_FREQUENCY(FREQ) (((FREQ) >= 1) || ((FREQ) <= 2400))
	
	#define CW_CCW_PIN				GPIO_Pin_1
	#define	CW_CCW_PORT				GPIOB
	#define CW_CCW_PORT_CLK		RCC_AHB1Periph_GPIOB
#endif
	/**
		* @}
		*/
#define HEADER_PORT_GROUP_A	GPIOA
#define HEADER_PORT_GROUP_B	GPIOB
#define HEADER_PORT_GROUP_C	GPIOC
#define HEADER_PORT_GROUP_D GPIOD
#define HEADER_PORT_GROUP_E	GPIOE
/**
  *	@addtogroup Macros definitions
  * @{
	*/

#ifdef L293D
	#define MOTOR_ENABLE1			GPIO_SetBits(ENABLE1_PORT,ENABLE1_PIN)
	#define MOTOR_ENABLE2			GPIO_SetBits(ENABLE2_PORT,ENABLE2_PIN)
	#define MOTOR_DISABLE1		GPIO_ResetBits(ENABLE1_PORT,ENABLE1_PIN)
	#define MOTOR_DISABLE2		GPIO_ResetBits(ENABLE2_PORT,ENABLE2_PIN)
#else
	#define MOTOR_ENABLE 			GPIO_SetBits(ENABLE_PORT,ENABLE_PIN)
	#define MOTOR_DISABLE			GPIO_ResetBits(ENABLE_PORT,ENABLE_PIN)
	#define CW_ENABLE					GPIO_ResetBits(CW_CCW_PORT,CW_CCW_PIN)
	#define CCW_ENABLE				GPIO_SetBits(CW_CCW_PORT,CW_CCW_PIN)
#endif

#define ENABLE_VH					GPIO_SetBits(VH_PORT,VH_PIN)
#define	DISABLE_VH				GPIO_ResetBits(VH_PORT,VH_PIN)

#define ENABLE_PEM				GPIO_ResetBits(PEM_CONTROL_PORT,PEM_CONTROL_PIN)
#define DISABLE_PEM				GPIO_SetBits(PEM_CONTROL_PORT,PEM_CONTROL_PIN)

#define LATCH_ENABLE			GPIO_ResetBits(LATCH_PORT,LATCH_PIN)
#define LATCH_DISABLE			GPIO_SetBits(LATCH_PORT,LATCH_PIN)

#define ASK4PAPER					GPIO_ReadInputDataBit(PEM_PORT,PEM_PIN)

#define ERROR_FEED_PITCH	0x01
#define	IS_PAPER					0x00
#define	NO_PAPER					0x01

#define FORWARD						0x00
#define BACKWARD					0x01

/**
  * @brief Thermistor variables and definition 
  *	@addtogroup Thermistor
  * @{
	*/
/**	
	* @schematic This is the circuit schematic for the thermistor:
	
(3.3V) ---- (SeriesResistor) -------|------- (Thermistor) ---- (Ground)
                                    |
                              THERMISTORPIN (PC3)	
**/
	
#define THERMISTORPIN			GPIO_Pin_3
#define THERMISTORPORT		GPIOC
#define RCCTHERMISTORPORT	RCC_AHB1Periph_GPIOC

#define BCoefficent				((uint16_t)3950)
#define RthNominal				((double)30000.00)
#define	TempNominal				25 
#define ADCResolution			((double)4096.00)
#define	SeriesResistor		((double)10000.00) 

#define NumSamples				10       // Number of Samples Max = 15 times
#define IS_TNUMSAMPLES_ADC(NUMB) (((NUMB) >= 1) || ((NUMB) <= 15))

#define KELVIN						1
#define CELSIUS						0

			/**
				* @}
				*/
/**
  * @}
  */

/** @addtogroup Prototypes and variables
  * @{
  */	
/**
*	@brief Public variables
**/

typedef struct 
{
	uint32_t CFrequency;
	uint16_t ARR;
	uint16_t CCR;
	uint16_t Prescaler;
	uint16_t NumbOfPulses;
	FunctionalState	EnableToCount;
}PWM_HeaderTimeStructure;

/**
*	@brief Public Prototypes
**/
uint8_t Header_Init(void);
void PrintDots(uint16_t *Array, uint8_t max) ;
uint8_t feed_pitch(uint64_t lines, uint8_t forward_backward);
void ClearPrinterBuffer(void);
PWM_HeaderTimeStructure BaseTimePwm(uint32_t Frequency, uint16_t NumbOfPulses,FunctionalState NewState);
void PWMBaseTimeChanging(PWM_HeaderTimeStructure Settings);
double temperature(uint8_t Grade_K_C);
uint8_t IsPaper(void);
/**
*	@brief Private Prototypes
**/
void Motor_Stepper_Pos(uint8_t Position);
void Delay_motor(__IO uint32_t nCount);
void Printer_SendWorld(uint16_t World);
void Init_HPrinterSPI(void);
void Init_HTIMx(void);
void Init_HADC(void);

/**
  * @}
  */
	
	
#endif

