/*********************************************************************
 *
 *                  Generic Type Definitions
 *
 *********************************************************************
 * FileName:        general.h
 * Dependencies:	None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F
 * Complier:        Microchip C18, C30
 *					HI-TECH PICC-18
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") is intended and supplied to you, the Company's
 * customer, for use solely and exclusively with products manufactured
 * by the Company.
 *
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * Author					Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti			07/12/04	Rel 0.9
 * Nilesh Rajbharti			11/24/04	Rel 0.9.1
 * Rawin Rojvanit			09/17/05	Rel 0.9.2
 * D Flowers & H Schlunder	08/10/06	Much better now (1.0)
 * D Flowers & H Schlunder	09/11/06	Add base signed types (1.1)
 * D Flo, H Sch, et. al		02/28/07	Add QWORD, LONGLONG, QWORD_VAL (1.2)
 ********************************************************************/

#ifndef __GENERAL_H_
#define __GENERAL_H_

// typedef enum _BOOL {
// 	 FALSE = 0, 
// 	 TRUE=!FALSE
// } BOOL;	// Undefined size

/*
typedef enum _BIT { 
	CLEAR = 0, 
	SET 
} BIT;*/


//#define FALSE 0
//#define TRUE 	1
#define CLEAR 0
//#define SET   1


#define PUBLIC                                  /* Function attributes */
#define PROTECTED
#define PRIVATE   static

/* INT is processor specific in length may vary in size */
typedef signed short        INT;  // Para compatibilidad con las otras maquinas 
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed int          INT32;
typedef signed long long    INT64;

/* UINT is processor specific in length may vary in size */
typedef unsigned short      UINT;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;     /* other name for 32-bit integer */
typedef unsigned long long  UINT64;


/* Alternate definitions */
typedef void                VOID;
typedef char                CHAR8;
typedef unsigned char       UCHAR8;
typedef unsigned char				BYTE;				// 8-bit unsigned
typedef unsigned short    	WORD;				// 16-bit unsigned
typedef unsigned long				DWORD;			// 32-bit unsigned
typedef unsigned long long	QWORD;			// 64-bit unsigned
typedef signed char					CHAR;				// 8-bit signed
typedef signed short    		SHORT;			// 16-bit signed
typedef signed long					LONG;				// 32-bit signed
typedef signed long long		WIDE;		// 64-bit signed


typedef union
{
    UINT8 Val;
    struct
    {
        UINT8 b0:1;
        UINT8 b1:1;
        UINT8 b2:1;
        UINT8 b3:1;
        UINT8 b4:1;
        UINT8 b5:1;
        UINT8 b6:1;
        UINT8 b7:1;
			
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union 
{
    UINT16 Val;
    UINT8 v[2] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
    } byte;
    struct __PACKED
    {
        UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;

typedef union
{
    UINT32 Val;
    UINT16 w[2] ;
    UINT8  v[4] ;
    struct 
    {
        UINT16 LW;
        UINT16 HW;
    } word;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
        UINT8 MB;
    } byte;
    struct 
    {
        UINT16_VAL low;
        UINT16_VAL high;
    }wordUnion;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
         UINT8 b24:1;
         UINT8 b25:1;
         UINT8 b26:1;
         UINT8 b27:1;
         UINT8 b28:1;
         UINT8 b29:1;
         UINT8 b30:1;
         UINT8 b31:1;
    } bits;
} UINT32_VAL;

typedef union
{
    UINT64 Val;
    UINT32 d[2] ;
    UINT16 w[4] ;
    UINT8 v[8]  ;
    struct 
    {
        UINT32 LD;
        UINT32 HD;
    } dword;
    struct 
    {
        UINT16 LW;
        UINT16 HW;
        UINT16 UW;
        UINT16 MW;
    } word;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
         UINT8 b24:1;
         UINT8 b25:1;
         UINT8 b26:1;
         UINT8 b27:1;
         UINT8 b28:1;
         UINT8 b29:1;
         UINT8 b30:1;
         UINT8 b31:1;
         UINT8 b32:1;
         UINT8 b33:1;
         UINT8 b34:1;
         UINT8 b35:1;
         UINT8 b36:1;
         UINT8 b37:1;
         UINT8 b38:1;
         UINT8 b39:1;
         UINT8 b40:1;
         UINT8 b41:1;
         UINT8 b42:1;
         UINT8 b43:1;
         UINT8 b44:1;
         UINT8 b45:1;
         UINT8 b46:1;
         UINT8 b47:1;
         UINT8 b48:1;
         UINT8 b49:1;
         UINT8 b50:1;
         UINT8 b51:1;
         UINT8 b52:1;
         UINT8 b53:1;
         UINT8 b54:1;
         UINT8 b55:1;
         UINT8 b56:1;
         UINT8 b57:1;
         UINT8 b58:1;
         UINT8 b59:1;
         UINT8 b60:1;
         UINT8 b61:1;
         UINT8 b62:1;
         UINT8 b63:1;
    } bits;
} UINT64_VAL;



typedef union _BYTE_VAL
{
    BYTE Val;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
    } bits;
} BYTE_VAL;

typedef union _WORD_VAL
{
    WORD Val;
    BYTE v[2];
    struct
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
    } bits;
} WORD_VAL;

typedef union _DWORD_VAL
{
    DWORD Val;
	WORD w[2];
    BYTE v[4];
    struct
    {
        WORD LW;
        WORD HW;
    } word;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
        unsigned char b16:1;
        unsigned char b17:1;
        unsigned char b18:1;
        unsigned char b19:1;
        unsigned char b20:1;
        unsigned char b21:1;
        unsigned char b22:1;
        unsigned char b23:1;
        unsigned char b24:1;
        unsigned char b25:1;
        unsigned char b26:1;
        unsigned char b27:1;
        unsigned char b28:1;
        unsigned char b29:1;
        unsigned char b30:1;
        unsigned char b31:1;
    } bits;
} DWORD_VAL;

typedef union _QWORD_VAL
{
    QWORD Val;
	DWORD d[2];
	WORD w[4];
    BYTE v[8];
    struct
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
        unsigned char b16:1;
        unsigned char b17:1;
        unsigned char b18:1;
        unsigned char b19:1;
        unsigned char b20:1;
        unsigned char b21:1;
        unsigned char b22:1;
        unsigned char b23:1;
        unsigned char b24:1;
        unsigned char b25:1;
        unsigned char b26:1;
        unsigned char b27:1;
        unsigned char b28:1;
        unsigned char b29:1;
        unsigned char b30:1;
        unsigned char b31:1;
        unsigned char b32:1;
        unsigned char b33:1;
        unsigned char b34:1;
        unsigned char b35:1;
        unsigned char b36:1;
        unsigned char b37:1;
        unsigned char b38:1;
        unsigned char b39:1;
        unsigned char b40:1;
        unsigned char b41:1;
        unsigned char b42:1;
        unsigned char b43:1;
        unsigned char b44:1;
        unsigned char b45:1;
        unsigned char b46:1;
        unsigned char b47:1;
        unsigned char b48:1;
        unsigned char b49:1;
        unsigned char b50:1;
        unsigned char b51:1;
        unsigned char b52:1;
        unsigned char b53:1;
        unsigned char b54:1;
        unsigned char b55:1;
        unsigned char b56:1;
        unsigned char b57:1;
        unsigned char b58:1;
        unsigned char b59:1;
        unsigned char b60:1;
        unsigned char b61:1;
        unsigned char b62:1;
        unsigned char b63:1;
    } bits;
} QWORD_VAL;


#endif //__GENERIC_TYPE_DEFS_H_
