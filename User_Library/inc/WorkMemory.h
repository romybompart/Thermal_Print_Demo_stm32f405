#ifndef __WORKMEMORY_H
#define __WORKMEMORY_H

#include <stm32f4xx_spi.h>
#include <stm32f4xx_gpio.h>
#include <general.h>
#include <hardware.h>

//=======================MACROS====================================

#define SPI1_WM             	SPI3
#define SPI1_WM_AF            GPIO_AF_SPI3				 
#define SPI1_WM_CLK       		RCC_APB1Periph_SPI3	 
#define SPI1_WM_CLK_CMD      	RCC_APB1PeriphClockCmd

#define WM_CS1_HIGH 					GPIO_SetBits(PORT_SPI1_CS1,PIN_SPI1_CS1)
#define WM_CS1_LOW 						GPIO_ResetBits(PORT_SPI1_CS1,PIN_SPI1_CS1)

#define WM_CSRAM1_HIGH 				GPIO_SetBits(PORT_SPI1_CSRAM1,PIN_SPI1_CSRAM1)
#define WM_CSRAM1_LOW 				GPIO_ResetBits(PORT_SPI1_CSRAM1,PIN_SPI1_CSRAM1)

#define WM_CSRAM2_HIGH 				GPIO_SetBits(PORT_SPI1_CSRAM2,PIN_SPI1_CSRAM2)
#define WM_CSRAM2_LOW 				GPIO_ResetBits(PORT_SPI1_CSRAM2,PIN_SPI1_CSRAM2)

#define RAM1 1
#define RAM2 0

//Uncomment if you want to use the 23LVC1024 memory
//#define MEMORY_23LCV1024

#ifndef MEMORY_23LCV1024
	#define  MEMORY_M45PE80
#endif
//=======================COMMANDS====================================
//MEMORY_M45PE80
#define WREN 	  0x06  //Write Enable
#define WRDI 	  0x04  //Write Disable
#define RDID 	  0x9F  //Read Identification
#define RDSR 	  0x05  //Read Status Register
#define READ 	  0x03  //Read Data Bytes
#define F_READ 	0x0B	//Read Data Bytes at Higher Speed
#define PW   	  0x0A  //Page Write
#define PP	 	  0x02	//Page Program
#define PE	 	  0xDB	//Page Erase
#define SE	 	  0xD8	//Sector Erase
#define DP	 	  0xB9	//Deep Power-Down
#define RDP	 	  0xAB	//Release from Deep Power-Down
//MEMORY_23LCV1024
#define READ		0x03 	// 	0000 0011  	Read data from memory array beginning at selected address
#define WRITE		0x02 	// 	0000 0010 	Write data to memory array beginning at selected address
#define EDIO  	0x3B 	//	0011 1011 	Enter Dual I/O access
#define RSTIO 	0xFF 	//	1111 1111		Reset Dual I/O access
#define RDMR		0x05 	//	0000 0101 	Read Mode Register
#define WRMR 		0x01 	//	0000 0001		Write Mode Register

#define SRAMPageSize		32

#define WR_BY		0x00	// Byte mode
#define WR_PG		0x80  // Page mode
#define	WR_SQ		0x40	// Sequencial mode

//=======================FUNCTIONS====================================
extern void Spi1_Open(void);
extern uint8_t Spi1_Write(UINT8 data);
void Spi1_Write_str(UINT8 *buffer,INT16 len);
extern uint8_t Spi1_Read(void);
extern void Spi1_Read_str(UINT8 *buffer,INT16 len);
extern void WorkMemory_CMD(UINT8 Select,uint32_t DATA,uint8_t RWCmd);


/*M45PE80*/
extern UINT WorkMemory_state(void);
extern uint32_t WorkMemory_ID(void);
void WorkMemory_wait(void);
void WorkMemory_WEN(void);
void WorkMemory_Write(INT32 addr, UINT8 *buffer, INT16 size);
void WorkMemory_Read(INT32 addr, UINT8 *buffer, INT16 size);

/*23LCV1024*/
void RamMemory_Selection(UINT8 Select);
void RamMemory_Deselection(UINT8 Select);
extern void WorkMemory_WRITE_MB(UINT8 Select, UINT8 WriteMode);
extern void WorkMemory_READ_MB(UINT8 Select, char *Buffer);
extern void WorkMemory_WRITE_BYTE(UINT8 Select,uint32_t ADDRESS, uint8_t DATA);
extern void WorkMemory_WRITE_PAGE(UINT8 Select,uint32_t ADDRESS, unsigned char *DATA);
extern void WorkMemory_READ_PAGE(UINT8 Select,uint32_t ADDRESS, unsigned char *DATA);
extern void WorkMemory_WRITE_SEQ(UINT8 Select,uint32_t ADDRESS, unsigned char *DATA, uint32_t WriteBytes);
extern void WorkMemory_READ_SEQ(UINT8 Select,uint32_t ADDRESS, unsigned char *DATA, uint32_t WriteBytes);
extern uint8_t WorkMemory_READ_BYTE(UINT8 Select,uint32_t ADDRESS);
extern void WorkMemory_SPIMODE(UINT8 Select);

#endif

