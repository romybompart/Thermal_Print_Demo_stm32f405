#include "GPIO_User.h"

void Init_LedBi(void)
	{
	GPIO_InitTypeDef GPIO_InitStruct; 
	GPIO_CLK_CMD(PORT_LED1_CLK ,ENABLE);
	GPIO_InitStruct.GPIO_Pin = PIN_LED1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(PORT_LED1, &GPIO_InitStruct);
  GPIO_ResetBits(PORT_LED1,PIN_LED1);
  
	GPIO_CLK_CMD(PORT_LED2_CLK ,ENABLE);
	GPIO_InitStruct.GPIO_Pin = PIN_LED2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(PORT_LED2, &GPIO_InitStruct);
  GPIO_ResetBits(PORT_LED2,PIN_LED2);  
	}
	
void Open_JP_RC(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_CLK_CMD(PORT_JP_RC_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = PIN_JP_RC;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(PORT_JP_RC, &GPIO_InitStruct);
}	

void Open_Power_Detect(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_CLK_CMD(PORT_POWER_FAIL_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = PIN_POWER_FAIL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(PORT_JP_RC, &GPIO_InitStruct);
}	

int Check_JP_RC(void)
{int status;
 status= GPIO_ReadInputDataBit(PORT_JP_RC,PIN_JP_RC);	 	
 return status;
}

void Open_BT_RST(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_CLK_CMD(PORT_BT_RST_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = PIN_BT_RST;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
 	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(PORT_BT_RST, &GPIO_InitStruct);
}	

int Check_BT_RST()
{int status;
 status= GPIO_ReadInputDataBit(PORT_BT_RST,PIN_BT_RST);	 	
 return status;
}
	/**
  * @brief La función permite englobar en una sola funcion la posibilidad de usar mutiples variables
	* @param  Los argumentos deben enviarse en el orden que se describe abajo, pero el primero debe
	*						identificar el numero de argumentos. Por Ejemplo: Blink(3,arg1,arg2,arg3), 3 indica el numero de
  *						argumentos a usar  
  *         Este parametro puede ser cualquiera de los siguientes valores:
  *            @arg Color:					El color que se quiere encender
	*																	Este puede ser: Red, Green o Black
	*            @arg NumberBlinks:   Veces que se quiere titilar el led: 1 - 254
  *            @arg DelayTime:      El tiempo que se quiere dejar encendido entre cada blink (en segundos)
	*					   @arg Alternating:		Indica si titilara de forma alterna: True, False
  * @retval None
  */
void Blink(int num_args,...)
{
		va_list var_list;
	  BlinkArgs Args;
	  int i=0;
	  va_start(var_list,num_args);	
		while(i < num_args)
		{
			switch(i)
			{
				case 0:
					Args.iColor = va_arg(var_list,int); // Color
				break;
				
				case 1:
					Args.iDelay = va_arg(var_list,int); // numbers of blinkings 
				break;
				
				case 2:
					Args.iBlinks = va_arg(var_list,int);// Delay between each blink 
				break;
				
				case 3:
					Args.iAltern = va_arg(var_list,int);// whether it is going to blink red and green. 
				break;
			}
			i++;
		}
		va_end(var_list);
		if(i==1)	
			Blinking(Args.iColor,1,1,0);
		if(i==2)
			Blinking(Args.iColor,Args.iBlinks,1,0);
		if(i==3)
		  Blinking(Args.iColor,Args.iBlinks,Args.iDelay,0);
		if(i==4)
			Blinking(Args.iColor,Args.iBlinks,Args.iDelay,Args.iAltern);
}	
	
void SetColor(int Color)
{
		switch(Color)
			{
			case 0:
			GPIO_SetBits(PORT_LED1,PIN_LED1); 
			GPIO_ResetBits(PORT_LED2,PIN_LED2);
			break;
			case 1:
			GPIO_SetBits(PORT_LED2,PIN_LED2);
			GPIO_ResetBits(PORT_LED1,PIN_LED1);
			break;
			case 10:
			GPIO_ResetBits(PORT_LED2,PIN_LED2);
			GPIO_ResetBits(PORT_LED1,PIN_LED1);	
			break;
			}
}

void Blinking(int Color, int times,int Seconds,int GreenRed)
{
	int ForTimes = 1;
	while(ForTimes<=(times*2))
	{
		if(Color>=0 && Color<=1)
		{
			if(!GreenRed)
			{
				if(ForTimes%2)
				SetColor(Color);
				else
				SetColor(Black);
				
				Delays((uint32_t)Seconds);
			}
			else
			{
				SetColor(Red);
				Delayms((uint32_t)Seconds*500);
				SetColor(Green);
				Delayms((uint32_t)Seconds*500);
			}	
		}
		else
		{
			SetColor(Black);
		}
				ForTimes++;
	}
	SetColor(Black);
}






