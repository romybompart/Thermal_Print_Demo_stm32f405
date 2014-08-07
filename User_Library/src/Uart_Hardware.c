/*                 Abstract

Uart Hardware 2.0 Modificado para MiniDragon
Se agrego funcion para envio de datos hacia BT

*/

#include "Uart_Hardware.h"
#include <string.h>

void Open_UartPC(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USARTPC_InitStruct;
	
	//********** Enable UART CLOCK************//
	USARTPC_CLK_CMD(USARTPC_CLK,ENABLE);
	//********** Enable PORTS CLOCK************//
	GPIO_CLK_CMD(PORT_UART1_CTS_CLK, ENABLE); //Enable Clock CTS
 	GPIO_CLK_CMD(PORT_UART1_RTS_CLK, ENABLE); //Enable Clock RTS
 	GPIO_CLK_CMD(PORT_UART1_TXD_CLK, ENABLE); //Enable Clock TXD
 	GPIO_CLK_CMD(PORT_UART1_RXD_CLK, ENABLE); //Enable Clock RXD
  //********** Configure the CTS PIN************//
	GPIO_InitStruct.GPIO_Pin = PIN_UART1_CTS;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(PORT_UART1_CTS, &GPIO_InitStruct);
	
	 //********** Configure the RTS PIN************//
	GPIO_InitStruct.GPIO_Pin = PIN_UART1_RTS;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; 
	GPIO_Init(PORT_UART1_RTS, &GPIO_InitStruct);
	
	 //********** Configure the TX PIN************//
	GPIO_InitStruct.GPIO_Pin = PIN_UART1_TXD;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(PORT_UART1_TXD, &GPIO_InitStruct);
	
	//********** Configure the RX PIN************//
	GPIO_InitStruct.GPIO_Pin = PIN_UART1_RXD;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(PORT_UART1_RXD, &GPIO_InitStruct);

	//********** Asigned the AF ************//

  GPIO_PinAFConfig(PORT_UART1_TXD,USART1_TXD_PinSource,USARTPC_AF); // OBS.
  GPIO_PinAFConfig(PORT_UART1_RXD,USART1_RXD_PinSource,USARTPC_AF);
	GPIO_PinAFConfig(PORT_UART1_CTS,USART1_RTS_PinSource,USARTPC_AF);
	GPIO_PinAFConfig(PORT_UART1_RTS,USART1_CTS_PinSource,USARTPC_AF);
	
	USARTPC_InitStruct.USART_BaudRate = USARTPC_BAUD;
	USARTPC_InitStruct.USART_WordLength = USART_WordLength_8b;
	USARTPC_InitStruct.USART_StopBits = USART_StopBits_1;
	USARTPC_InitStruct.USART_Parity = USART_Parity_No;
	USARTPC_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTPC_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx ;
	USART_Init(USARTPC, &USARTPC_InitStruct);
	
	//********** Interruption ************//
//  USART_ITConfig(USARTPRINTER, USART_IT_RXNE, ENABLE); 
// 	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		 
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
// 	NVIC_Init(&NVIC_InitStructure);							 
	
	USART_Cmd(USARTPC,ENABLE);
 	
}

void Usart_Send(char *dat,USART_TypeDef  *USARTx )
{
	while(*dat){
		// wait until data register is empty
		while( !(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, *dat);
		dat++;
	}
}

char Usart_getc(USART_TypeDef  *USARTx)
{
	char RxBuffer [2];
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)	{	}
  RxBuffer[0] = USART_ReceiveData(USARTx);
  USART_SendData(USARTPC,*RxBuffer);
  return RxBuffer[0];
}

/**
  * @brief  Gets numeric values from the hyperterminal.
  * @param  None
  * @retval None
  */
uint8_t USART_Scanf(USART_TypeDef  *USARTx, uint32_t value)
{
  uint32_t index = 0;
  uint32_t tmp[2] = {0, 0};
  char Bufferx[25];

  while (index < 2)
  {
    /* Loop until RXNE = 1 */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
    {}
    tmp[index++] = (USART_ReceiveData(USARTx));
    if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
    {
     Usart_Send("\n\r Please enter valid number between 0 and 9 \n\r", USARTPC);
      index--;
    }
  }
  /* Calculate the Corresponding value */
  index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);
  /* Checks */
  if (index > value)
  {
    sprintf(Bufferx, "\n\r Please enter valid number between 0 and %d \n\r", value);
		Usart_Send(Bufferx,USARTx);
    return 0xFF;
  }
  return index;
}

// // IRQ function 
// void USART2_IRQHandler(void) { 
//  // TX IRQ part 
//   if (USART2->SR & 0x0080) 
// 		{ // If TXE flag in SR is on then 
// 		 if (*OutString != '\0'){ 	// if not end of string 
// 			USART2->DR = *OutString++;// send next character and increment pointer 
// 			} 
// 		else 
// 			{// else 
// 			 USART2->CR1 &= ~0x0080; // disable TX interrupt 
// 			}
// 		}
// }


void StrBTprotocol(char *buffer)
{int len=0,i=0;

 char temp[2], buffer2[550];
	memset(buffer2,0,517);
	buffer2[0]=0x1D;
	buffer2[1]=0x23;
	len=strlen(buffer);
// 	scanf("%d",&len);
//	sprintf(temp,"%0.2h",len);

	if(len<512)
{/*
	while(len)
	{
		i++;
		temp[i]=len%16;
		len=len/16;	
		}*/
	
	  sprintf(temp,"%0.2x",len);
	 buffer2[2]=temp[1]-0x30;	
	 buffer2[3]=temp[0]-0x30;
	 //sprintf(buffer,"%s%s",buffer2,buffer);
	for(i=4;i<=(len+4);i++)
	{buffer2[i]=buffer[i-4];
	}	
	strcpy(buffer,buffer2);
	}
	
}
