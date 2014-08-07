#ifndef __MAIN_H
#define __MAIN_H

/* Private includes ------------------------------------------------------------*/

#ifndef HSE_STARTUP_TIMEOUT
#define HSE_STARTUP_TIMEOUT (0x1500)
#endif

#include <stm32f4xx.h>
#include <stm32f4xx_conf.h>
#include "general.h"
#include "hardware.h"
#include "Uart_Hardware.h"
#include "GPIO_User.h"
#include "Delay.h"
#include "WorkMemory.h"

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"

#include "fonts.h"
#include "header_hardware.h"




/* MAIN definitions ------------------------------------------------------------*/
#define TRUE 1
#define FALSE 0

/* Public protoypes ---------------------------------------------------------*/
extern void TestInit(void);
void MyMenu(void);
void fill_mybuffer(uint8_t* BuffIn,uint32_t Len);

#endif


