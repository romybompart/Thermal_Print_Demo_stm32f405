/**
  ******************************************************************************
  * @file    main.c 
  * @author  Romy Bompart - HARDWARE TEAM from The Factory HKA,CA
	* @location	Caracas, Venezuela
  * @version V1.0.1
  * @date    25-Febrary-2014
  * @brief   Main Test program.
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
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Private variables ----------------------------------------------------------*/
RCC_ClocksTypeDef	Clocks;
 __ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_Core_dev __ALIGN_END ;
 __ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;
extern USB_OTG_CORE_HANDLE           USB_OTG_dev;
char Mybuffer[100],ReceiveBuffer[250];
uint8_t ON_OFF = 0,CW_CCW=0;
extern PWM_HeaderTimeStructure PWM;
extern uint8_t USBRx;

int main(void)
{ 
  TestInit();

	while(1)
			{	
 				ReceiveBuffer[0] = '0';
 				MyMenu();
			}	
}

void MyMenu()
{
	char Value[100];
	int8_t i = 0, y, temp;
	/************************************************************/
	strcpy(Mybuffer,"\n*************************Status*************************");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	sprintf(Mybuffer,"\n** Temperatura: %f Celcius - %f Kelvin",temperature(CELSIUS), temperature(KELVIN));
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	/************************************************************/
	if(IsPaper() == IS_PAPER)
		sprintf(Mybuffer,"\n** Sensor de papel: %s","Hay Papel!!!");
	else
		sprintf(Mybuffer,"\n** Sensor de papel: %s","No Hay Papel!!!");
	
		VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
		Usart_Send(Mybuffer,USARTPC);
	/************************************************************/
	sprintf(Mybuffer,"\n** Font Memory ID: 0x%x",WorkMemory_ID());
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));	
	/************************************************************/
	strcpy(Mybuffer,"\n*************************Menu*************************\n");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	strcpy(Mybuffer,"1.- Encender el motor\n");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	strcpy(Mybuffer,"2.- Cambiar Direccion de rotacion\n");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	strcpy(Mybuffer,"3.- Cambiar velocidad del motor\n");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	strcpy(Mybuffer,"4.- Cambiar Numero de pulsos del motor\n");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	strcpy(Mybuffer,"5.- Imprimir pagina de prueba hasta cierta temperatura\n");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	strcpy(Mybuffer,"6.- Imprimir lo que escribe\n");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	strcpy(Mybuffer,"Opcion: ");
	VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
	Usart_Send(Mybuffer,USARTPC);
	/************************************************************/
	/* waiting CPU response */
  while(ReceiveBuffer[0] == '0')
	{Delayms(100); USBRx = 0;}
  USBRx = 0;
	/************************************************************/
		switch(ReceiveBuffer[0])
		{
			case '1':
				if(ON_OFF)
				{
				MOTOR_DISABLE;
				Delayus(300);
				/**/
				TIM_Cmd(TIM1, DISABLE);
				TIM_CCxNCmd(TIM1,TIM_Channel_1,TIM_CCxN_Disable);
				PWM.EnableToCount = DISABLE;
				/**/
				DISABLE_VH;
				ON_OFF = 0;
				VCP_DataTx((uint8_t* )"Apagar Motor\n",13);
				}
				else
				{
				ENABLE_VH;
				Delayus(300);
				MOTOR_ENABLE;
				ON_OFF = 1;
				/**/
				TIM_Cmd(TIM1, ENABLE);
				TIM_CCxNCmd(TIM1,TIM_Channel_1,TIM_CCxN_Enable);
				PWM.EnableToCount = ENABLE;
				/**/
				VCP_DataTx((uint8_t* )"Encender Motor\n",15);
				}
			break;
				
			case '2':
					if(!CW_CCW)
					{
						CW_CCW = 1;
						CCW_ENABLE;
					}
					else
					{
						CW_CCW = 0;
						CW_ENABLE;
					}
			break;
					
		  case '3':					
			    sprintf(Mybuffer,"Frecuencia actual = %i \n",PWM.CFrequency);
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					strcpy(Mybuffer,"Ingresa el valor de la frecuencia (culmine con enter)\n Valor: ");
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
			  memset(Value,0,sizeof(Value));
			
				while(atoi(Value) <= 62 ) 
				{
					sprintf(Mybuffer,"\nIngrese Valores mayores a 61");
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					memset(Value,0,sizeof(Value));
					do
					{ 
						if(USBRx)
						{
							Value[i] = ReceiveBuffer[0];
							i++;
							USBRx = 0;
							sprintf(Mybuffer,"\nValor String: %s",Value);
							VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
							if(i > 10) 
							{	
								i = 0;
								memset(Value,0,sizeof(Value));
							}
						}
					}while(ReceiveBuffer[0] != 0x0D );
					ReceiveBuffer[0] = '\0';
					i=0;
				}
					Value[strlen(Value)] = '\0';
					PWM = BaseTimePwm(atoi(Value), PWM.NumbOfPulses, ENABLE);
					PWMBaseTimeChanging(PWM);
					sprintf(Mybuffer,"\nValor PWM: %u ",atoi(Value));
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));	
					sprintf(Mybuffer,"\nValor ARR: %u ",PWM.ARR);
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					sprintf(Mybuffer,"\nValor CCR: %u ",PWM.CCR);
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					sprintf(Mybuffer,"\nValor PRESCALER: %u ",PWM.Prescaler);
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					
					i = 0;
					memset(Value,0,sizeof(Value));
			break;
					
			case '4':
					sprintf(Mybuffer,"\nNumero de pulsos actual = %i \n",PWM.NumbOfPulses);
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					strcpy(Mybuffer,"\nIngresa el valor de numero de pulsos (culmine con enter)\n: ");
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					do
					{ 
						if(USBRx)
						{
							Value[i] = ReceiveBuffer[0];
							i++;
							USBRx = 0;
							sprintf(Mybuffer,"\nValor String: %s",Value);
							VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
							if(i > 10) 
							{	i = 0;
								memset(Value,0,sizeof(Value));
							}
						}
					}while(ReceiveBuffer[0] != 0x0D );
					Value[strlen(Value)] = '\0';
					PWM.NumbOfPulses = atoi(Value);
					i = 0;
					memset(Value,0,sizeof(Value));
			break;
					
			case '5':
			sprintf(Mybuffer,"\n** Temperatura Actual: %f Celcius - %f Kelvin\n",temperature(CELSIUS), temperature(KELVIN));
			VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
			
			strcpy(Mybuffer,"\nTemperatura Maxima: \n");
			VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
			do
			{ 
				if(USBRx)
				{
					Value[i] = ReceiveBuffer[0];
					i++;
					USBRx = 0;
					sprintf(Mybuffer,"\nValor String: %s Celsius",Value);
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					if(i > 2 && ReceiveBuffer[0]!= 0x0D) 
					{	i = 0;
						memset(Value,0,sizeof(Value));
					}
				}
			}while(ReceiveBuffer[0] != 0x0D );
			Value[strlen(Value)] = '\0';
		  temp = atoi(Value);
			while(temperature(CELSIUS)<temp)
			{
				ThermalPrint("PRINTING TEST\0");
				for(i=0x41;i<=0x60;i++)
				{
					for ( y = 0 ;y <24; y++)
							Value[y] = i;
					Value[24] = 0;
					ThermalPrint(Value);
				}
				sprintf(Mybuffer,"** Temperatura Actual: %f Celcius\n",temperature(CELSIUS));
				VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
		  }
		  memset(Value,0,sizeof(Value));
			i=0;
			break;
			
			case '6':
					strcpy(Mybuffer,"\n*** Escribe lo que quieras (escribe 0 para salir)*** \n");
					VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
					do
					{ 
						if(USBRx)
						{
							Value[i] = ReceiveBuffer[0];
							USBRx = 0;
							sprintf(Mybuffer,"\nTexto: %s",Value);
							VCP_DataTx((uint8_t* )Mybuffer,strlen(Mybuffer));
							i++;
							if( ReceiveBuffer[0] == 0x0D || i==100) 
							{	
								Value[i] = '\0';
								ThermalPrint(Value);
								memset(Value,0,sizeof(Value));
								i = 0;
							}
						}
					}while( ReceiveBuffer[0] != '0');
					Value[strlen(Value)] = '\0';
					i = 0;
					memset(Value,0,sizeof(Value));
			break;
		}
}

void fill_mybuffer(uint8_t* BuffIn,uint32_t Len)
{
  uint8_t i = 0;
	memset(ReceiveBuffer,0,sizeof(ReceiveBuffer));
	while( i < Len)
	{
		ReceiveBuffer [i] = BuffIn[i];
		i++;
	}
		VCP_DataTx((uint8_t* )ReceiveBuffer,i); // Returning the sent charcarter(s)
}

void TestInit(void)
{
	RCC_GetClocksFreq(&Clocks);
  InitDelay(1); // To configure the systick interruption to 1us 
	Init_LedBi(); // Led Initialization 
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb); //USB OTG Initialization
	Open_UartPC(); // USART Initizalitation
	Spi1_Open();// SPI3 for WorkMemory Initialization
	if(Header_Init() == IS_PAPER) // Printer Mechanism Initialization
	{VCP_DataTx((uint8_t* )"Hay Papel en la impresora :) !!!\n",33);}
	else
	{VCP_DataTx((uint8_t* )"No hay Papel en la impresora :( !!!\n",36);}
}

/* El desarrollo del hombre depende fundamentalmente de la invención.  */
/* Es el producto más importante de su cerebro creativo. Nicola Tesla  */
