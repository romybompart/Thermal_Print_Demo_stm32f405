/**
 * @file   hardware.h
  * @author  HARDWARE 
  * @version V1.0.0
  * @date    12-November-2013
  * @brief   This file is to customize the current firmware to be compatible with several ARM. 
**/
#ifndef __HARDWARE_H__
#define __HARDWARE_H__
//=================================================================
//				       USART1 PC
//=================================================================

#define PORT_UART1_CTS				GPIOA	   	 ///
#define PIN_UART1_CTS					GPIO_Pin_0	 ///
#define PORT_UART1_CTS_CLK   	RCC_AHB1Periph_GPIOA ///
#define USART1_CTS_PinSource  GPIO_PinSource0 

#define PORT_UART1_RTS				GPIOA		 ///
#define PIN_UART1_RTS					GPIO_Pin_1	 ///
#define PORT_UART1_RTS_CLK   	RCC_AHB1Periph_GPIOA ///
#define USART1_RTS_PinSource  GPIO_PinSource1 

#define PORT_UART1_TXD				GPIOA	 ///
#define PIN_UART1_TXD					GPIO_Pin_2	 ///
#define PORT_UART1_TXD_CLK   	RCC_AHB1Periph_GPIOA///
#define USART1_TXD_PinSource  GPIO_PinSource2 

#define PORT_UART1_RXD				GPIOA		 ///
#define PIN_UART1_RXD					GPIO_Pin_3	 ///
#define PORT_UART1_RXD_CLK   	RCC_AHB1Periph_GPIOA ///
#define USART1_RXD_PinSource  GPIO_PinSource3 


//=================================================================
//				       CRIPTO I2C 1
//=================================================================

#define PORT_CRYPTO1_SDA				GPIOB	 ///
#define PIN_CRYPTO1_SDA					GPIO_Pin_9   /// 
#define PORT_CRYPTO1_SDA_CLK   	RCC_AHB1Periph_GPIOB ///

#define PORT_CRYPTO1_SCL				GPIOB	 ///
#define PIN_CRYPTO1_SCL					GPIO_Pin_8   /// 
#define PORT_CRYPTO1_SCL_CLK   	RCC_AHB1Periph_GPIOB ///
//=================================================================
//				 SPI1 MEMORIA TRABAJO FLASH
//=================================================================

#define PORT_SPI1_SCLK				GPIOC	///
#define PIN_SPI1_SCLK					GPIO_Pin_10	///
#define PORT_SPI1_SCLK_CLK   	RCC_AHB1Periph_GPIOC ///
#define PIN_SPI1_SCLK_Source  GPIO_PinSource10 ///

#define PORT_SPI1_MISO				GPIOC		///
#define PIN_SPI1_MISO					GPIO_Pin_11	///
#define PORT_SPI1_MISO_CLK   	RCC_AHB1Periph_GPIOC ///
#define PIN_SPI1_MISO_Source  GPIO_PinSource11 ///

#define PORT_SPI1_MOSI				GPIOC		////
#define PIN_SPI1_MOSI					GPIO_Pin_12	////
#define PORT_SPI1_MOSI_CLK   	RCC_AHB1Periph_GPIOC ///
#define PIN_SPI1_MOSI_Source  GPIO_PinSource12 ///

#define PORT_SPI1_CS1					GPIOD	///
#define PIN_SPI1_CS1					GPIO_Pin_2  ///
#define PORT_SPI1_CS1_CLK   	RCC_AHB1Periph_GPIOD ///

#define PORT_SPI1_CSRAM1			GPIOB		///
#define PIN_SPI1_CSRAM1				GPIO_Pin_6  ///
#define PORT_SPI1_CSRAM1_CLK  RCC_AHB1Periph_GPIOB ///

//=================================================================
//				 SPI2 MEMORIA FISCAL
//=================================================================
#define PORT_SPI2_SCK					GPIOB		///
#define PIN_SPI2_SCK					GPIO_Pin_13	///
#define PORT_SPI2_SCK_CLK   	RCC_AHB1Periph_GPIOB ///
#define SPI2_SCK_PinSource   	GPIO_PinSource13 

#define PORT_MF_RST   				GPIOB		////
#define PIN_MF_RST   					GPIO_Pin_0	////
#define PORT_MF_RST_CLK   		RCC_AHB1Periph_GPIOB ///

#define PORT_MF_CD   					GPIOB		////
#define PIN_MF_CD   					GPIO_Pin_1	////
#define PORT_MF_CD_CLK   			RCC_AHB1Periph_GPIOB ///

#define PORT_SPI2_MISO				GPIOC		///
#define PIN_SPI2_MISO					GPIO_Pin_2	///
#define PORT_SPI2_MISO_CLK   	RCC_AHB1Periph_GPIOC ///
#define SPI2_MISO_PinSource   GPIO_PinSource2 

#define PORT_SPI2_MOSI				GPIOC		////
#define PIN_SPI2_MOSI					GPIO_Pin_3	////
#define PORT_SPI2_MOSI_CLK   	RCC_AHB1Periph_GPIOC ///
#define SPI2_MOSI_PinSource   GPIO_PinSource3 

#define PORT_SPI2_CS					GPIOB		///
#define PIN_SPI2_CS						GPIO_Pin_12 ///
#define PORT_SPI2_CS_CLK   		RCC_AHB1Periph_GPIOB ///
#define SPI2_CS_PinSource   	GPIO_PinSource12 


#define PORT_MF_PS   					GPIOC		////
#define PIN_MF_PS   					GPIO_Pin_5	////
#define PORT_MF_PS_CLK   			RCC_AHB1Periph_GPIOC ///

//=================================================================
//				  MEMORIA AUDITORIA
//=================================================================

/******SDIO******/

#define PORT_SDIO_D0						GPIOC		///
#define PIN_SDIO_D0							GPIO_Pin_8 ///
#define PORT_SDIO_DO_CLK   			RCC_AHB1Periph_GPIOC ///
#define SDIO_DO_PinSource   		GPIO_PinSource8

#define PORT_SDIO_D1						GPIOC		///
#define PIN_SDIO_D1							GPIO_Pin_9 ///
#define PORT_SDIO_D1_CLK   			RCC_AHB1Periph_GPIOC ///
#define SDIO_D1_PinSource   		GPIO_PinSource9

#define PORT_SDIO_D2						GPIOC		///
#define PIN_SDIO_D2							GPIO_Pin_10 ///
#define PORT_SDIO_D2_CLK   			RCC_AHB1Periph_GPIOC ///
#define SDIO_D2_PinSource   		GPIO_PinSource10

#define PORT_SDIO_D3						GPIOC		///
#define PIN_SDIO_D3							GPIO_Pin_11 ///
#define PORT_SDIO_D3_CLK   			RCC_AHB1Periph_GPIOC ///
#define SDIO_D3_PinSource   		GPIO_PinSource11

#define PORT_SDIO_SCLK					GPIOC		///
#define PIN_SDIO_SCLK						GPIO_Pin_12 ///
#define PORT_SDIO_SCLK_CLK   		RCC_AHB1Periph_GPIOC ///
#define SDIO_SCLK_PinSource   	GPIO_PinSource12

#define PORT_SDIO_CMD						GPIOD		///
#define PIN_SDIO_CMD						GPIO_Pin_2 ///
#define PORT_SDIO_CMD_CLK   		RCC_AHB1Periph_GPIOD ///
#define SDIO_CMD_PinSource   		GPIO_PinSource2

#define SD_DETECT_PIN           GPIO_Pin_14                 
#define SD_DETECT_GPIO_PORT     GPIOB                    
#define SD_DETECT_GPIO_CLK      RCC_AHB1Periph_GPIOB

#define PORT_EJ_PS   		GPIOB		////
#define PIN_EJ_PS   		GPIO_Pin_15	////
#define PORT_EJ_PS_CLK  RCC_AHB1Periph_GPIOB ///

#define EJ_PS_ON 				GPIO_ResetBits(PORT_EJ_PS,PIN_EJ_PS)
#define EJ_PS_OFF 			GPIO_SetBits(PORT_EJ_PS,PIN_EJ_PS)

//=================================================================
//					 USB DEVICE
//=================================================================

#define PORT_USB_DEVICE_DM	GPIOA		///
#define PIN_USB_DEVICE_DM	GPIO_Pin_11	///

#define PORT_USB_DEVICE_DP	GPIOA		///
#define PIN_USB_DEVICE_DP	GPIO_Pin_12	///


#define PORT_VTEST  		GPIOC	    ///	Power Fail
#define PIN_VTEST   		GPIO_Pin_15	///


//=================================================================
//					 USB HOST
//=================================================================


#define PORT_LED2		    GPIOC	    ///LED2_TEST	
#define PIN_LED2		    GPIO_Pin_9	///PORT_LED2_TEST	
#define PORT_LED2_CLK   RCC_AHB1Periph_GPIOC ///ENABLE_LED2_TEST


#define PORT_LED1		    GPIOA	    ///PORT_LED1_TEST
#define PIN_LED1		    GPIO_Pin_8	///LED1_TEST	
#define PORT_LED1_CLK   RCC_AHB1Periph_GPIOA ///ENABLE_LED1_TEST

#define PORT_TAMPER_RTC		GPIOC		///
#define PIN_TAMPER_RTC		GPIO_Pin_13	///	Tamper Event Dectect

#define PORT_TAMPER_CD		GPIOC		///
#define PIN_TAMPER_CD		GPIO_Pin_6	///	Tamper Detect

#define PORT_JP_RC		  GPIOC		///	Ram Clear Jumper
#define PIN_JP_RC    		GPIO_Pin_1	///
#define PORT_JP_RC_CLK  RCC_AHB1Periph_GPIOC

#define PORT_BT_RST		   GPIOB		///	RESET
#define PIN_BT_RST    	 GPIO_Pin_7	///
#define PORT_BT_RST_CLK  RCC_AHB1Periph_GPIOB

#define PORT_POWER_FAIL		   GPIOC		///	
#define PIN_POWER_FAIL    	 GPIO_Pin_0	///
#define PORT_POWER_FAIL_CLK  RCC_AHB1Periph_GPIOC
//=============================================================================
#define GPIO_CLK_CMD                RCC_AHB1PeriphClockCmd ///


#endif

