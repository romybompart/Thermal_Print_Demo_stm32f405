#ifndef __EJ_SDIO_H
#define	__EJ_SDIO_H

#include "stm32f4xx.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_dma.h"
#include "hardware.h"
#include "SD_Interface2.h"
#include "Uart_Hardware.h"

/** @addtogroup SDIO MACROS IMPLEMENTATION
  * @{
  */ 
#define SDIO_FIFO_ADDRESS                ((uint32_t)0x40012C80)

/** 
  * @brief  SDIO Intialization Frequency (400KHz max)
  */
#define SDIO_INIT_CLK_DIV                ((uint8_t)0x76)
/** 
  * @brief  SDIO Data Transfer Frequency (25MHz max) 
  */
#define SDIO_TRANSFER_CLK_DIV            ((uint8_t)0x0) 

#define SD_SDIO_DMA                   DMA2
#define SD_SDIO_DMA_CLK               RCC_AHB1Periph_DMA2
 
#define SD_SDIO_DMA_STREAM3	          3
//#define SD_SDIO_DMA_STREAM6           6

#ifdef SD_SDIO_DMA_STREAM3
 #define SD_SDIO_DMA_STREAM            DMA2_Stream3
 #define SD_SDIO_DMA_CHANNEL           DMA_Channel_4
 #define SD_SDIO_DMA_FLAG_FEIF         DMA_FLAG_FEIF3
 #define SD_SDIO_DMA_FLAG_DMEIF        DMA_FLAG_DMEIF3
 #define SD_SDIO_DMA_FLAG_TEIF         DMA_FLAG_TEIF3
 #define SD_SDIO_DMA_FLAG_HTIF         DMA_FLAG_HTIF3
 #define SD_SDIO_DMA_FLAG_TCIF         DMA_FLAG_TCIF3 
 #define SD_SDIO_DMA_IRQn              DMA2_Stream3_IRQn
 #define SD_SDIO_DMA_IRQHANDLER        DMA2_Stream3_IRQHandler 
#elif defined SD_SDIO_DMA_STREAM6
 #define SD_SDIO_DMA_STREAM            DMA2_Stream6
 #define SD_SDIO_DMA_CHANNEL           DMA_Channel_4
 #define SD_SDIO_DMA_FLAG_FEIF         DMA_FLAG_FEIF6
 #define SD_SDIO_DMA_FLAG_DMEIF        DMA_FLAG_DMEIF6
 #define SD_SDIO_DMA_FLAG_TEIF         DMA_FLAG_TEIF6
 #define SD_SDIO_DMA_FLAG_HTIF         DMA_FLAG_HTIF6
 #define SD_SDIO_DMA_FLAG_TCIF         DMA_FLAG_TCIF6 
 #define SD_SDIO_DMA_IRQn              DMA2_Stream6_IRQn
 #define SD_SDIO_DMA_IRQHANDLER        DMA2_Stream6_IRQHandler
#endif /* SD_SDIO_DMA_STREAM3 */

/**
  * @}
  */ 
	
/*Prototypes */
extern void uSD_InterfaceStart(void);
extern void NVIC_Config(void);
extern void SD_LowLevel_DeInit(void);
extern void SD_LowLevel_Init(void);
extern void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize);
extern void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
extern void SD_Process_Test(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
void SD_EraseTest(void);
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);




#endif

