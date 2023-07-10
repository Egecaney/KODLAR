/*
 * Gpio.h
 *
 *  Created on: 26 Haz 2023
 *      Author: Egemen
 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include "platform_config.h"
#include "xgpio.h"
#include "xintc.h"

void 	GpioHandler(void *CallBackRef);
int		GPIO_Init(XGpio *GpioInstancePtr, uint16_t GpioDevice_ID);
int 	GPIO_Init_IT(XGpio *GpioInstancePtr, XIntc *InterruptInstancePtr, uint16_t GpioDevice_ID, uint16_t Interrupt_ID, uint16_t Interrupt_Mask);
void	ShowTheValueinDisplay(XGpio *GpioInstancePtr, uint8_t BeforeV, uint8_t AfterV);

#define GPIO_DEVICE_ID				XPAR_GPIO_0_DEVICE_ID
#define GPIO_1_DEVICE_ID			XPAR_GPIO_1_DEVICE_ID

#define INTC_GPIO_INTERRUPT_ID		XPAR_INTC_0_GPIO_0_VEC_ID

#define BUTTON_CHANNEL				(unsigned)1
#define LED_CHANNEL					(unsigned)2
#define DISPLAYLED_CHANNEL			(unsigned)1
#define DISPLAYANODE_CHANNEL		(unsigned)2
#define GPIO_ALL_INPUTS				(uint32_t)0xFFFF
#define GPIO_ALL_OUTPUTS			(uint32_t)0x0000

typedef enum{
	Zero				= 	(uint32_t)0b11000000,
	One					=	(uint32_t)0b11111001,
	Two					=	(uint32_t)0b10100100,
	Three				=	(uint32_t)0b10110000,
	Four				=	(uint32_t)0b10011001,
	Five				=	(uint32_t)0b10010010,
	Six					=	(uint32_t)0b10000010,
	Seven				=	(uint32_t)0b11111000,
	Eight				=	(uint32_t)0b10000000,
	Nine				=	(uint32_t)0b10010000,
}DisplayValue;

typedef enum{
	AnodeActive7		= 	(uint32_t)0b01111111,
	AnodeActive6		=	(uint32_t)0b10111111,
	AnodeActive5		=	(uint32_t)0b11011111,
	AnodeActive4		=	(uint32_t)0b11101111,
	AnodeActive3		=	(uint32_t)0b11110111,
	AnodeActive2		=	(uint32_t)0b11111011,
	AnodeActive1		=	(uint32_t)0b11111101,
	AnodeActive0		=	(uint32_t)0b11111110,
	NullAnodeCathode	=	(uint32_t)0b11111111,
}AnodeCathodeValue;

#endif /* SRC_GPIO_H_ */
