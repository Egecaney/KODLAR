/*
 * Spi.h
 *
 *  Created on: 26 Haz 2023
 *      Author: Egemen
 */

#ifndef SRC_SPI_H_
#define SRC_SPI_H_

#include "platform_config.h"
#include "xspi.h"
#include "xintc.h"

int 	SPI_Init_IT(XSpi *SpiInstancePtr, XIntc *InterruptInstancePtr, uint16_t SpiDevice_ID, uint16_t Interrupt_ID);
int 	ConfigurationADXL362(XSpi *SpiInstancePtr);
int 	MeasurementAccelerometerADXL362(XSpi *SpiInstancePtr);
void	SpiHandler(void *CallBackRef, uint32_t StatusEvent, uint32_t ByteCount);

#define SPI_DEVICE_ID							XPAR_SPI_0_DEVICE_ID
#define INTC_SPI_INTERRUPT_ID					XPAR_INTC_0_SPI_0_VEC_ID

#define Spi_ConfigMessageSize					(int)3
#define Spi_RW_MessageSize						(int)8

#define ADXL362_SPI_SELECT						(uint32_t)0x01
#define ADXL362_WriteCommand					(uint32_t)0x0A
#define ADXL362_ReadCommand						(uint32_t)0x0B
#define ADXL362_DeviceAddress					(uint32_t)0x00
#define ADXL362_DeviceAddressValue				(uint32_t)0xAD
#define ADXL362_PowerCTRL_RegisterAddress		(uint32_t)0x2D
#define ADXL362_AccValues_InitialAddress		(uint32_t)0x0E
#define ADXL362_MeasurementModeEnable			(uint32_t)0x02

#endif /* SRC_SPI_H_ */
