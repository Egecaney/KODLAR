/*
 * Gpio.c
 *
 *  Created on: 26 Haz 2023
 *      Author: Egemen
 */

#include <stdio.h>
#include "Gpio.h"
#include "sleep.h"

static volatile int 	GpioFlag;
static const uint32_t	DisplayValueMap[] = {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};

int GPIO_Init_IT(XGpio *GpioInstancePtr, XIntc *InterruptInstancePtr, uint16_t GpioDevice_ID, uint16_t Interrupt_ID, uint16_t Interrupt_Mask){

	if(XGpio_Initialize(GpioInstancePtr, GpioDevice_ID) != XST_SUCCESS)
		return XST_FAILURE;

	XGpio_SetDataDirection(GpioInstancePtr, (unsigned)BUTTON_CHANNEL, (uint32_t)GPIO_ALL_INPUTS);
	XGpio_SetDataDirection(GpioInstancePtr, (unsigned)LED_CHANNEL, (uint32_t)GPIO_ALL_OUTPUTS);

	if(XIntc_Connect(InterruptInstancePtr, Interrupt_ID, (XInterruptHandler)GpioHandler, (void *)GpioInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	XIntc_Enable(InterruptInstancePtr, Interrupt_ID);

	if(XIntc_Start(InterruptInstancePtr, XIN_REAL_MODE) != XST_SUCCESS)
		return XST_FAILURE;

	XGpio_InterruptEnable(GpioInstancePtr, Interrupt_Mask);
	XGpio_InterruptGlobalEnable(GpioInstancePtr);

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, InterruptInstancePtr);
	Xil_ExceptionEnable();

	return XST_SUCCESS;

}

int	GPIO_Init(XGpio *GpioInstancePtr, uint16_t GpioDevice_ID){

	if(XGpio_Initialize(GpioInstancePtr, GpioDevice_ID) != XST_SUCCESS)
		return XST_FAILURE;

	XGpio_SetDataDirection(GpioInstancePtr, (unsigned)DISPLAYANODE_CHANNEL, (uint32_t)GPIO_ALL_OUTPUTS);
	XGpio_SetDataDirection(GpioInstancePtr, (unsigned)DISPLAYLED_CHANNEL, (uint32_t)GPIO_ALL_OUTPUTS);

	XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYANODE_CHANNEL, NullAnodeCathode);
	XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYLED_CHANNEL, NullAnodeCathode);

	return XST_SUCCESS;

}

void ShowTheValueinDisplay(XGpio *GpioInstancePtr, uint8_t BeforeV, uint8_t AfterV){

	for(int Index = 0; Index <50; Index++){
		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYANODE_CHANNEL, AnodeActive7);
		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYLED_CHANNEL, DisplayValueMap[BeforeV/10]);
		usleep(75);

		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYANODE_CHANNEL, AnodeActive6);
		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYLED_CHANNEL, (DisplayValueMap[BeforeV%10]&0x7F));
		usleep(75);

		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYANODE_CHANNEL, AnodeActive5);
		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYLED_CHANNEL, DisplayValueMap[AfterV/100]);
		usleep(75);

		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYANODE_CHANNEL, AnodeActive4);
		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYLED_CHANNEL, DisplayValueMap[AfterV%100]);
		usleep(75);
	}

	XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYANODE_CHANNEL, NullAnodeCathode);
		XGpio_DiscreteWrite(GpioInstancePtr, DISPLAYLED_CHANNEL, NullAnodeCathode);

}


void GpioHandler(void *CallBackRef){
	XGpio *GpioPtr	= (XGpio*)CallBackRef;
	GpioFlag = TRUE;
	XGpio_InterruptClear(GpioPtr, BUTTON_CHANNEL);	/* Clear the Interrupt */
}


