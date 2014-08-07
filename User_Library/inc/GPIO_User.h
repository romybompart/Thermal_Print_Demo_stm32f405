#ifndef __GPIO_USER_H
#define __GPIO_USER_H

#include <stm32f4xx_gpio.h>
#include <stdarg.h>
#include "Delay.h"
#include "hardware.h"

#define Red 	1
#define Green 0
#define Black	10

#ifndef True
#define True  1
#endif
#ifndef False
#define False 0
#endif

#define ActiveRC 0
#define InactiveRC 1	


extern void Init_LedBi(void);
extern void SetColor(int Color);
extern void Blink(int num_args, ...);
extern void Blinking(int Color, int times,int Seconds,int GreenRed);
extern void Open_JP_RC(void);
extern int Check_JP_RC(void);
extern void Open_BT_RST(void);
extern int Check_BT_RST(void);


typedef struct
{
int iColor, iDelay, iBlinks,iAltern;
}BlinkArgs;


#endif
