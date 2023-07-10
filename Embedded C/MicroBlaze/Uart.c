/*
 * Uart.c
 *
 *  Created on: 26 Haz 2023
 *      Author: Egemen
 */

#include <stdio.h>
#include "Uart.h"

extern XUartLite	UartLite;

extern volatile int UartReceivedFlag;
extern volatile int UartTransmittedFlag;

extern uint8_t 		UartReceiveBuffer[UART_RX_MessageSize];

int UartLite_Init_IT(XUartLite *UartLiteInstancePtr, XIntc *InterruptInstancePtr, uint16_t UartLiteDevice_ID, uint16_t Interrupt_ID){

	if(XUartLite_Initialize(UartLiteInstancePtr, UartLiteDevice_ID) != XST_SUCCESS)
		return XST_FAILURE;

	if(XUartLite_SelfTest(UartLiteInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	if(XIntc_Connect(InterruptInstancePtr, Interrupt_ID, (XInterruptHandler)XUartLite_InterruptHandler, (void *)UartLiteInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	if(XIntc_Start(InterruptInstancePtr, XIN_REAL_MODE) != XST_SUCCESS)
		return XST_FAILURE;

	XIntc_Enable(InterruptInstancePtr, Interrupt_ID);

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, InterruptInstancePtr);
	Xil_ExceptionEnable();

	XUartLite_SetSendHandler(UartLiteInstancePtr, UartSendHandler, UartLiteInstancePtr);
	XUartLite_SetRecvHandler(UartLiteInstancePtr, UartRecvHandler, UartLiteInstancePtr);

	XUartLite_EnableInterrupt(UartLiteInstancePtr);

	UartReceivedFlag = FALSE;
	XUartLite_Recv(UartLiteInstancePtr, UartReceiveBuffer, UART_RX_MessageSize);

	return XST_SUCCESS;

}

void	UartSendHandler(void *CallBackRef, unsigned int EventData){
	UartTransmittedFlag = TRUE;
}

void	UartRecvHandler(void *CallBackRef, unsigned int EventData){
	UartReceivedFlag = TRUE;
	XUartLite_Recv(&UartLite, UartReceiveBuffer, UART_RX_MessageSize);
}

