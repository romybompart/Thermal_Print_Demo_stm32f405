/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Template/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    18-January-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "usb_hcd_int.h"

/* Private variables ---------------------------------------------------------*/

uint32_t PWM_COUNTER = 0;
uint8_t ENABLE_TO_COUNT = 1;
extern __IO uint16_t CCR1_Val;
extern PWM_HeaderTimeStructure PWM;


 extern USB_OTG_CORE_HANDLE           USB_OTG_dev;
 extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);

// extern USB_OTG_CORE_HANDLE          USB_OTG_Core_dev;
// extern USBH_HOST                    USB_Host;
// extern int Configure;

 extern void USB_OTG_BSP_TimerIRQ (void);


// int ret=0;
// int ret2=FALSE;
 
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}


/**
  * @brief  TIM2_IRQHandler
  *         This function handles Timer2 Handler.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
   USB_OTG_BSP_TimerIRQ();
}


/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
 TimingDelay_Decrement();

//  cronometer();
//  if(Configure==TRUE)
//  {
// 	 if(Check_JP_RC()==ActiveRC)
// 	 {	 ret++;
// 		 if(ret==2000)
// 		 { ret2++;
// 			 
// 			 SetColor(0x01&ret2);
// 			 ret=0;
// 		 }
// 	 }
// 		 if(Check_BT_RST()==ActiveRC)
// 	 {	 ret++;
// 		 if(ret==6000)
// 		 { ret2++;
// 			 SetColor(0x01&ret2);
// 			 ret=0;
// 		 }
// 	 }
//  }	 
}

// 	 if(Check_JP_RC()==ActiveRC)
// 	 {ret++;
// 		 if(ret==400)
// 		 { ret2=~ret2;
// 			 SetColor(ret2);
// 			 ret=0;
// 			 
// 	   } 

/**
  * @brief  This function handles EXTI15_10_IRQ Handler.
  * @param  None
  * @retval None
  */
// void OTG_FS_WKUP_IRQHandler(void)
// {
//   if(USB_OTG_dev.cfg.low_power)
//   {
//     *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ; 
//     SystemInit();
//     USB_OTG_UngateClock(&USB_OTG_dev);
//   }
//   EXTI_ClearITPendingBit(EXTI_Line18);
// }

void OTG_FS_IRQHandler(void)
{
  USBD_OTG_ISR_Handler (&USB_OTG_dev);
}

void OTG_HS_IRQHandler(void)
{
 // USBH_OTG_ISR_Handler (&USB_OTG_Core_dev);
}

/**
  * @brief  This function handles RTC Tamper and Time Stamp interrupts requests.
  * @param  None
  * @retval None
  */
void TAMP_STAMP_IRQHandler(void)
{
// 	float i,y;
// 	
//   if(RTC_GetFlagStatus(RTC_FLAG_TAMP1F) != RESET) // RTC_GetITStatus(RTC_IT_TAMP1) != RESET || 
//   { 
//     /* Tamper 1 detection event occurred */
//     Usart_Send("\n\r        /!\\***** Interrupcion del Damper ********/!\\ \n\r",USARTPRINTER);
//     SetColor(Red);
// 		for(i=0;i<100;i++){for(y=0;y<168000;y++){}}
// 		SetColor(Black);
//     /* Clear Tamper 1 pin Event(TAMP1F) pending flag */
//     RTC_ClearFlag(RTC_FLAG_TAMP1F);
// //     /* Disable Tamper pin 1 */
// //     RTC_TamperCmd(RTC_Tamper_1, DISABLE);
// 		RTC_TimeStampShow();
// 		if(RTC_GetFlagStatus(RTC_FLAG_TSF)!=RESET)			
// 		RTC_ClearFlag(RTC_FLAG_TSF);
// // 		RTC_WriteBackupRegister(RTC_BKP_DR0, ALREADY_CONFIG);
// // 		/* Enable Tamper pin */
// //     RTC_TamperCmd(RTC_Tamper_1, ENABLE);
// 		/* Clear the EXT_Line21 pending flag */
// 		EXTI_ClearFlag(EXTI_Line21);
// 	}
}
/******************************************************************************/
/**
  * @brief  This function handles SDIO global interrupt request.
  * @param  None
  * @retval None
  */
void SDIO_IRQHandler(void)
{
  /* Process All SDIO Interrupt Sources */
//  SD_ProcessIRQSrc();
}

/**
  * @brief  This function handles DMA2 Stream3 or DMA2 Stream6 global interrupts
  *         requests.
  * @param  None
  * @retval None
  */
void SD_SDIO_DMA_IRQHANDLER(void)
{
  /* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
//  SD_ProcessDMAIRQ();
}

/**
  * @brief  This function handles TIM1 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_CC_IRQHandler (void)
{

  if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
		
		if (PWM.EnableToCount)
			PWM_COUNTER++;
		
		if(PWM_COUNTER == PWM.NumbOfPulses)
		{	
				MOTOR_DISABLE;
				TIM_Cmd(TIM1, DISABLE);
				TIM_CCxNCmd(TIM1,TIM_Channel_1,TIM_CCxN_Disable);
				PWM.EnableToCount = DISABLE;
				PWM_COUNTER = 0;
			// Es necesario apagar el motor porque a veces algunas lineas del chip TB6
			// Se mantiene encendido
			DISABLE_VH;
		}

  }
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s).                         */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
