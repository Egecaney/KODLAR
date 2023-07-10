/*
 * Iic.h
 *
 *  Created on: 26 Haz 2023
 *      Author: Egemen
 */

#ifndef SRC_IIC_H_
#define SRC_IIC_H_

#include "platform_config.h"
#include "Gpio.h"
#include "xiic.h"
#include "xintc.h"

int 	IIC_Init_IT(XIic *IicInstancePtr, XIntc *InterruptInstancePtr, uint16_t IicDevice_ID, uint16_t Interrupt_ID);
int 	MeasurementTemperatureADT7420(XIic *IicInstancePtr);
int		IicReadData(XIic *IicInstancePtr, uint8_t *ReadBataBufferPtr, uint8_t ByteCount);
int		IicWriteData(XIic *IicInstancePtr, uint16_t ByteCount);

void 	IicSendHandler(XIic *IicInstancePtr);
void 	IicRecvHandler(XIic *IicInstancePtr);
void 	IicStatusHandler(XIic *IicInstancePtr, int Event);

#define IIC_DEVICE_ID								XPAR_IIC_0_DEVICE_ID
#define INTC_IIC_INTERRUPT_ID						XPAR_INTC_0_IIC_0_VEC_ID

#define Iic_ConfigMessageSize						(int)3
#define Iic_RW_MessageSize							(int)4

#define ADT7420_AddressSize							(int)1
#define ADT7420_ReadTemperatureSize					(int)2
#define ADT7420_DeviceAddress						(uint8_t)0x4B
#define ADT7420_MSB_TemperatureRegisterAddress		(uint8_t)0x00
#define ADT7420_LSB_TemperatureRegisterAddress		(uint8_t)0x01

#endif /* SRC_IIC_H_ */
