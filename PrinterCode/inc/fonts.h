/**
  ******************************************************************************
  * @file    PrintCode/fonts.h 
  * @author  Romy Bompart - HARDWARE TEMAN from The Factory HKA,CA
  * @version V1.0.1
  * @date    25-Febrary-2014
  * @brief   header file of fonts.c
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

#ifndef __FONTS_H
#define __FONTS_H
#include "main.h"
#include <string.h>
#include "header_hardware.h"

#define int16								uint16_t
#define int8								uint8_t

#define asciistart 					((uint8_t)'A')
#define netxcharacter				((uint8_t)24)
#define Fontrows						((uint8_t)24)
#define FontColums					((uint8_t)16)
#define Maxdotsperline			((uint16_t)384)
#define	nextcharactercolum	((uint8_t)Fontrows/8)
#define Maxcharacterperline	((uint16_t)Maxdotsperline/FontColums)


extern void ThermalPrint(char text[150]);
static int16 pixelsfont(int8 row, int8 letter);

#endif
				
