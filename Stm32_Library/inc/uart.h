#include "stm32f4xx.h" 
#include <string.h>

// puertos seriales
//Com3;
// define los macros para el uart3

#define COM3_TX_ON  TIM5->CR1 |= TIM_CR1_CEN 			//Timer 5 Enable
#define COM3_TX_OFF  TIM5->CR1 &= ~TIM_CR1_CEN 			//Timer 5 Disable

#define COM3_TX_F_Bit_OFF  TIM5->SR&= ~TIM_SR_UIF       //Flag timer 5


//UART 3  - IMPRESORA
#define COM3BAUD	19200    							//baudios com3
#define COM3PARIDAD	PARIDAD_NO
#define COM3TXB 	64	 								//tamaño del buffer de transmision com3
 

#define UART3_TX_CLOCK_EN RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN    //Clock Enable
#define UART3_TX_CLOCK_DI RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN   //Clock Disable

#define UART3_TX_MODE_OUT 	GPIOB->MODER = GPIO_MODER_MODER9_0  // TXPIN como Salida

#define UART3_TX_OD		GPIOB->OTYPER |= GPIO_OTYPER_OT_9  //OPEN DRAIN

#define UART3_TX_ODR    	GPIOB->ODR	         // Registro Salida
#define UART3_TX_IDR    	GPIOB->IDR	         // Registro Entrada

#define UART3_TX_PIN_1   	GPIOB->ODR |=  GPIO_OTYPER_ODR_9	 //Salida a 1
#define UART3_TX_PIN_0   	GPIOB->ODR &= ~GPIO_OTYPER_ODR_9 //Salida a 0

#define TX_ESPERA 0
#define TX_BYTE	 1
#define TX_ERR	2
#define TX_END 3

//Frecuencia APB1
#define APB1CLOCK 42000000 // SYSCLOCK/(AHB*APB1)
#define COM_MIN_TIMEOUT 20
#define COM_MAX_TIMEOUT 200

 


