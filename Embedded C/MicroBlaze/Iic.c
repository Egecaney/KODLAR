/*
 * Iic.c
 *
 *  Created on: 26 Haz 2023
 *      Author: Egemen
 */

#include <stdio.h>
#include "Iic.h"

static volatile int IicReceivedFlag;
static volatile int IicTransmittedFlag;

uint8_t 			IicWriteBuffer[Iic_RW_MessageSize];
uint8_t 			IicReadBuffer[Iic_RW_MessageSize];

extern uint8_t		ADT7420_ValuesMessage[100];
extern XGpio		Gpio1;

int IIC_Init_IT(XIic *IicInstancePtr, XIntc *InterruptInstancePtr, uint16_t IicDevice_ID, uint16_t Interrupt_ID){

	XIic_Config *IicConfigurationPtr;
	IicConfigurationPtr = XIic_LookupConfig(IicDevice_ID);

	if(IicConfigurationPtr == NULL)
		return XST_DEVICE_NOT_FOUND;

	if(XIic_CfgInitialize(IicInstancePtr, IicConfigurationPtr, IicConfigurationPtr->BaseAddress) != XST_SUCCESS)
		return XST_FAILURE;

	if(XIntc_Connect(InterruptInstancePtr, Interrupt_ID, (XInterruptHandler)XIic_InterruptHandler, (void *)IicInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	if(XIntc_Start(InterruptInstancePtr, XIN_REAL_MODE) != XST_SUCCESS)
		return XST_FAILURE;

	XIntc_Enable(InterruptInstancePtr, Interrupt_ID);

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, InterruptInstancePtr);
	Xil_ExceptionEnable();

	XIic_SetSendHandler(IicInstancePtr, IicInstancePtr, (XIic_StatusHandler)IicSendHandler);
	XIic_SetRecvHandler(IicInstancePtr, IicInstancePtr, (XIic_StatusHandler)IicRecvHandler);
	XIic_SetStatusHandler(IicInstancePtr, IicInstancePtr, (XIic_StatusHandler)IicStatusHandler);

	if(XIic_SetAddress(IicInstancePtr, XII_ADDR_TO_SEND_TYPE, (int)ADT7420_DeviceAddress) != XST_SUCCESS)
		return XST_FAILURE;

	return XST_SUCCESS;

}

int	IicWriteData(XIic *IicInstancePtr, uint16_t ByteCount){

	IicTransmittedFlag = FALSE;
	IicInstancePtr->Stats.TxErrors = FALSE;

	if(XIic_Start(IicInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	if(XIic_MasterSend(IicInstancePtr, IicWriteBuffer, (int)ByteCount) != XST_SUCCESS)
		return XST_FAILURE;

	while((!IicTransmittedFlag) || (XIic_IsIicBusy(IicInstancePtr) == TRUE)){
		if(IicInstancePtr->Stats.TxErrors != FALSE){

			if(XIic_Start(IicInstancePtr) != XST_SUCCESS)
				return XST_FAILURE;

			if(!XIic_IsIicBusy(IicInstancePtr)){
				if(XIic_MasterSend(IicInstancePtr, IicWriteBuffer, (int)ByteCount) == XST_SUCCESS)
					IicInstancePtr->Stats.TxErrors = FALSE;
			}
		}
	}

	if(XIic_Stop(IicInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	return XST_SUCCESS;

}

int	IicReadData(XIic *IicInstancePtr, uint8_t *ReadBataBufferPtr, uint8_t ByteCount){

	IicReceivedFlag = FALSE;

	if(IicWriteData(IicInstancePtr, ADT7420_AddressSize) != XST_SUCCESS)
		return XST_FAILURE;

	if(XIic_Start(IicInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	if(XIic_MasterRecv(IicInstancePtr, IicReadBuffer, (int)ByteCount) != XST_SUCCESS)
		return XST_FAILURE;

	while((!IicReceivedFlag) || (XIic_IsIicBusy(IicInstancePtr) == TRUE)){}

	if(XIic_Stop(IicInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	return XST_SUCCESS;
}

int MeasurementTemperatureADT7420(XIic *IicInstancePtr){

	IicWriteBuffer[0] = ADT7420_MSB_TemperatureRegisterAddress;

	if(IicReadData(IicInstancePtr, IicReadBuffer, ADT7420_ReadTemperatureSize) != XST_SUCCESS)
		return XST_FAILURE;

	char TemperatureSign;
	switch((IicReadBuffer[0] & 0x80) >> 7){
	case 0:
		TemperatureSign = *"+";
		break;
	case 1:
		TemperatureSign = *"-";
		break;
	}

	uint16_t Temperature = (IicReadBuffer[0] << 8)|(IicReadBuffer[1]);
	uint8_t  TemperatureValue_BeforePoint = (uint8_t)((Temperature & 0x7F80) >> 7);
	uint16_t TemperatureValue_AfterPoint  = (uint16_t)(((Temperature & 0x0078) >> 3) * (1000/16));

	sprintf((char*)ADT7420_ValuesMessage, "\nTemperature = %c%u.%uC\n", TemperatureSign, TemperatureValue_BeforePoint, TemperatureValue_AfterPoint);
	ShowTheValueinDisplay(&Gpio1, TemperatureValue_BeforePoint, TemperatureValue_AfterPoint);

	return XST_SUCCESS;

}

void IicSendHandler(XIic *IicInstancePtr){
	IicTransmittedFlag = TRUE;
}
void IicRecvHandler(XIic *IicInstancePtr){
	IicReceivedFlag = TRUE;
}

void IicStatusHandler(XIic *IicInstancePtr, int Event){}

