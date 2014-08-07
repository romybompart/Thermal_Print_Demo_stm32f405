#ifndef __UART_HARDWARE_H
#define __UART_HARDWARE_H

#include <hardware.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>
#include <stdio.h>

//=======================MACROS====================================
#define USARTPC_BAUD					115200
#define USARTPC 							USART2
#define USARTPC_AF 						GPIO_AF_USART2
#define USARTPC_IT_RX					USART_IT_RXNE 
#define USARTPC_IT_TX					USART_IT_TXE
#define USARTPC_CLK						RCC_APB1Periph_USART2
#define USARTPC_CLK_CMD				RCC_APB1PeriphClockCmd
//=======================FUNCTIONS====================================
void Open_UartPC(void);
void Usart_Send(char *dat,USART_TypeDef  *USARTx );
char Usart_getc(USART_TypeDef  *USARTx);
uint8_t USART_Scanf(USART_TypeDef  *USARTx, uint32_t value);
void StrBTprotocol(char *buffer);

#endif
