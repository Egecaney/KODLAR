/*
 * Uart.h
 *
 *  Created on: 26 Haz 2023
 *      Author: Egemen
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_

#include "platform_config.h"
#include "xuartlite.h"
#include "xintc.h"

int 	UartLite_Init_IT(XUartLite *UartLiteInstancePtr, XIntc *InterruptInstancePtr, uint16_t UartLiteDevice_ID, uint16_t Interrupt_ID);
void	UartSendHandler(void *CallBackRef, unsigned int EventData);
void	UartRecvHandler(void *CallBackRef, unsigned int EventData);

#define UARTLITE_DEVICE_ID				XPAR_UARTLITE_0_DEVICE_ID
#define INTC_UARTLITE_INTERRUPT_ID		XPAR_INTC_0_UARTLITE_0_VEC_ID

#define UART_RX_MessageSize				(int)2
#define UART_TX_MessageSize				(int)2

#endif /* SRC_UART_H_ */
