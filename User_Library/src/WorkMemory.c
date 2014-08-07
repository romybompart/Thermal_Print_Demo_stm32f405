#include <WorkMemory.h>
#include <stdio.h>

//=================================================================
//				Work Memory Common Functions
//=================================================================
//======================SPI INIT===========================================
void Spi1_Open(void)
{ GPIO_InitTypeDef GPIO_InitStruct;  
 	SPI_InitTypeDef SPI_InitStruct;

	SPI1_WM_CLK_CMD(SPI1_WM_CLK, ENABLE); //Enable Clock SPI1
 
	GPIO_CLK_CMD(PORT_SPI1_SCLK_CLK, ENABLE); //Enable Clock SCKL
	GPIO_CLK_CMD(PORT_SPI1_MISO_CLK, ENABLE); //Enable Clock MISO
	GPIO_CLK_CMD(PORT_SPI1_MOSI_CLK, ENABLE); //Enable Clock MOSI
	
	GPIO_CLK_CMD(PORT_SPI1_CS1_CLK, ENABLE); //Enable Clock CS
	GPIO_CLK_CMD(PORT_SPI1_CSRAM1_CLK, ENABLE); //Enable Clock CS

 //********** Configure the Chip Select WM************//
  GPIO_InitStruct.GPIO_Pin = PIN_SPI1_CS1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(PORT_SPI1_CS1, &GPIO_InitStruct);
   
  WM_CS1_HIGH; 	
	
	#ifdef MEMORY_23LCV1024
	 //********** Configure the Chip Select RAM1************//
  GPIO_InitStruct.GPIO_Pin = PIN_SPI1_CSRAM1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(PORT_SPI1_CSRAM1, &GPIO_InitStruct);
    
	WM_CSRAM1_HIGH;
	#endif

//************* Configure the SCLK****************//
  GPIO_InitStruct.GPIO_Pin = PIN_SPI1_SCLK;
 	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF;
 	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
 	GPIO_Init(PORT_SPI1_SCLK, &GPIO_InitStruct);

//************* Configure the MISO****************//
 	GPIO_InitStruct.GPIO_Pin = PIN_SPI1_MISO;
 	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF;
 	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
 	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(PORT_SPI1_MISO, &GPIO_InitStruct);

//************* Configure the MOSI****************//
 	GPIO_InitStruct.GPIO_Pin = PIN_SPI1_MOSI ;
 	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF;
 	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
 	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(PORT_SPI1_MOSI, &GPIO_InitStruct);

 //**************Alternate Function SPI**********************//
 	GPIO_PinAFConfig(PORT_SPI1_MOSI, PIN_SPI1_MOSI_Source, SPI1_WM_AF);
 	GPIO_PinAFConfig(PORT_SPI1_MISO, PIN_SPI1_MISO_Source, SPI1_WM_AF);
 	GPIO_PinAFConfig(PORT_SPI1_SCLK, PIN_SPI1_SCLK_Source, SPI1_WM_AF);

//**************     SPI Config  ***************************//
 	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
 	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;     // transmit in master mode, NSS pin has to be always high
 	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
 	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
 	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
 	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//  | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
 	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; // SPI frequency is APB2 frequency / 2
 	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
 	SPI_Init(SPI1_WM, &SPI_InitStruct); 
 	SPI_Cmd(SPI1_WM, ENABLE); // enable SPI1
}

//===================SPI WRITE==============================================
uint8_t Spi1_Write(UINT8 data)
{
	SPI1_WM->DR = data; // write data to be transmitted to the SPI data register
	while( !(SPI1_WM->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	while( !(SPI1_WM->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
	while( SPI1_WM->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
	return SPI1_WM->DR;
}
//====================SPI READ=============================================
uint8_t Spi1_Read(void)
{ 
	SPI1_WM->DR = 0xFF; // Dummy Char For Clock
	while( !(SPI1_WM->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	while( !(SPI1_WM->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
	while( SPI1_WM->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
	return SPI1_WM->DR;
}
//===================SPI WRITE STRING===========================================
void Spi1_Write_str(UINT8 *buffer,INT16 len)
{	INT i;
    for(i=1;i<=len;i++)
	{Spi1_Write(*buffer);
	++buffer;
	}

}			  
//===================SPI WRITE STRING===========================================
void Spi1_Read_str(UINT8 *buffer,INT16 len)
{	UINT8 i;
   for(i=1;i<=len;i++)
	{*buffer=Spi1_Read();
	++buffer;
	}
}			
//==================== COMMAND ==================================
void WorkMemory_CMD(UINT8 Select,uint32_t DATA,uint8_t RWCmd)
{
	Spi1_Write(RWCmd);
	Spi1_Write(DATA>>16	& 0xFF);
	Spi1_Write(DATA>>8	& 0xFF);
	Spi1_Write(DATA>>0	& 0xFF);
}

//=================================================================
//				Work Memory Functions M45PE80
//=================================================================
//====================READ STATUS=============================================
UINT WorkMemory_state(void)
{
 INT ret=0;
 WM_CS1_LOW;
 
 Spi1_Write(RDSR);
 ret=Spi1_Read();

 WM_CS1_HIGH;
 return ret;
}

//====================READ ID=============================================
uint32_t WorkMemory_ID(void)
{
 uint32_t ret = 0x00000000, dat=0x00000000;
 WM_CS1_LOW;
 Spi1_Write(RDID);
 dat = Spi1_Read();
 ret =  (	dat << 	16) & 0x00FF0000;
 dat = Spi1_Read();
 ret |= (dat	<< 	8 ) & 0x0000FF00;
 dat = Spi1_Read();
 ret |= (dat 	<<	0	) & 0x000000FF;
 WM_CS1_HIGH;
 return ret;
}


//====================Wait Until Not Busy====================================
void WorkMemory_wait(void)
{
 #define WIP 0x01
 INT state;

 WM_CS1_LOW;

 Spi1_Write(RDSR);
 state=Spi1_Read();

 while(state & WIP)
 {  
    Spi1_Write(RDSR);
	state=Spi1_Read();
 }

 WM_CS1_HIGH;
}

//====================Write Enable========================================
void WorkMemory_WEN(void)
{
 WM_CS1_LOW;
 Spi1_Write(WREN);
 WM_CS1_HIGH;
}
//====================Write ========================================
void WorkMemory_Write(INT32 addr, UINT8 *buffer, INT16 size)
{
 UINT8 *p=buffer, *_end;
 INT32 end= addr+size;
 INT32 i,next_page;
 INT16 len;

 for(i=addr;i<end;)
 	{
	next_page= (i | 0xFF)+1;
	if(next_page>end)
	{
		next_page=end;
	}
  _end= p + (next_page - i);
  WorkMemory_wait();
  WorkMemory_WEN();
	
  WM_CS1_LOW;
  Spi1_Write(PP);
  Spi1_Write((i >> 16) & 0xFF);
  Spi1_Write((i >> 8) & 0xFF);
  Spi1_Write((i >> 0) & 0xFF);
  len=(_end-p);
  Spi1_Write_str(p,len);
  p=_end;
  WM_CS1_HIGH;
	
  i=next_page;
  }
}

//====================READ ========================================
void WorkMemory_Read(INT32 addr, UINT8 *buffer, INT16 size)
{
	WorkMemory_wait();
  WM_CS1_LOW;
  Spi1_Write(READ);
	Spi1_Write((addr >> 16) & 0xFF);
  Spi1_Write((addr >> 8) & 0xFF);
  Spi1_Write((addr >> 0) & 0xFF);
	Spi1_Read_str(buffer,size);
	WM_CS1_HIGH;
}

//=================================================================
//				Work Memory Functions 23LCV1024
//=================================================================
void WorkMemory_SPIMODE(UINT8 Select)
{
	RamMemory_Selection(Select);
	Spi1_Write(RSTIO);
	RamMemory_Deselection(Select);
}
//====================RAM SELECTION ===============================
void RamMemory_Selection(UINT8 Select)
{if(Select)
		WM_CSRAM1_LOW;
 else
 {}//WM_CSRAM2_LOW;
}

//====================RAM DESELECTION ===============================
void RamMemory_Deselection(UINT8 Select)
{if(Select)
		WM_CSRAM1_HIGH;
	else
	{}//		WM_CSRAM2_HIGH;
}	
//====================WRITE MODEBYTE ===============================
void WorkMemory_WRITE_MB(UINT8 Select, UINT8 WriteMode)
{
				RamMemory_Selection(Select);
				Spi1_Write(WRMR);
				Spi1_Write(WriteMode);
			  RamMemory_Deselection(Select);
}
//====================READ MODEBYTE ================================
void WorkMemory_READ_MB(UINT8 Select, char *Buffer)
{
				uint8_t data;
		   	RamMemory_Selection(Select);
			  Spi1_Write(RDMR);
				data = Spi1_Read();
	      RamMemory_Deselection(Select);
				sprintf(Buffer,"\n Mode Register: %x ",data);
}
//====================WRITE BYTE ================================
void WorkMemory_WRITE_BYTE(UINT8 Select,uint32_t ADDRESS, uint8_t DATA)
{   
		WorkMemory_WRITE_MB(Select, WR_BY);
		RamMemory_Selection(Select);
		WorkMemory_CMD(Select,ADDRESS,WRITE);
		Spi1_Write(DATA);
		RamMemory_Deselection(Select);
}
//====================READ BYTE ================================
uint8_t WorkMemory_READ_BYTE(UINT8 Select,uint32_t ADDRESS)
{
		uint8_t DATA;
	  
		WorkMemory_WRITE_MB(Select,WR_BY);
		RamMemory_Selection(Select);
		WorkMemory_CMD(Select,ADDRESS,READ);
		DATA = Spi1_Read(); //Dummy
		RamMemory_Deselection(Select);
	  return DATA;
}
//====================WRITE PAGE ================================
void WorkMemory_WRITE_PAGE(UINT8 Select,uint32_t ADDRESS, unsigned char *DATA)
{   
		int WriteCnt;
	  WorkMemory_WRITE_MB(Select,WR_PG);
		RamMemory_Selection(Select);
		WorkMemory_CMD(Select,ADDRESS,WRITE);
		for(WriteCnt=0;WriteCnt<SRAMPageSize;WriteCnt++)
		{	
				Spi1_Write(DATA[WriteCnt]);
		}
		RamMemory_Deselection(Select);
}
//====================READ PAGE ================================
void WorkMemory_READ_PAGE(UINT8 Select,uint32_t ADDRESS, unsigned char *DATA)
{   
		int ReadCnt;
	  WorkMemory_WRITE_MB(Select,WR_PG);
		RamMemory_Selection(Select);
		WorkMemory_CMD(Select,ADDRESS,READ);
		for(ReadCnt=0;ReadCnt<SRAMPageSize;ReadCnt++)
		{	
				DATA[ReadCnt] = Spi1_Read();
		}
		RamMemory_Deselection(Select);
}
//====================WRITE SEQUENTIALLY ================================
void WorkMemory_WRITE_SEQ(UINT8 Select,uint32_t ADDRESS, unsigned char *DATA, uint32_t WriteBytes)
{   
	  WorkMemory_WRITE_MB(Select,WR_SQ);
		RamMemory_Selection(Select);
		WorkMemory_CMD(Select,ADDRESS,WRITE);
		while(WriteBytes>0)
		{	
				WriteBytes--;
				Spi1_Write(DATA[WriteBytes]);
		}
		RamMemory_Deselection(Select);
}
//====================READ SEQUENTIALLY ================================
void WorkMemory_READ_SEQ(UINT8 Select,uint32_t ADDRESS, unsigned char *DATA, uint32_t WriteBytes)
{  
	  WorkMemory_WRITE_MB(Select,WR_SQ);
		RamMemory_Selection(Select);
		WorkMemory_CMD(Select,ADDRESS,READ);
		while(WriteBytes>0)
		{	
				WriteBytes--;
				DATA[WriteBytes] = Spi1_Read();
		}
		RamMemory_Deselection(Select);
}
