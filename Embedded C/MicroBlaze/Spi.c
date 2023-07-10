/*
 * Spi.c
 *
 *  Created on: 26 Haz 2023
 *      Author: Egemen
 */

#include <stdio.h>
#include "Spi.h"

static volatile int SpiFlag;
static volatile int SpiErrorFlag = FALSE;

uint8_t 			SpiWriteBuffer[Spi_RW_MessageSize];
uint8_t 			SpiReadBuffer[Spi_RW_MessageSize];
extern uint8_t 		ADXL362_ValuesMessage[100];

int SPI_Init_IT(XSpi *SpiInstancePtr, XIntc *InterruptInstancePtr, uint16_t SpiDevice_ID, uint16_t Interrupt_ID){

	XSpi_Config *SpiConfigurationPtr;
	SpiConfigurationPtr = XSpi_LookupConfig(SpiDevice_ID);

	if(SpiConfigurationPtr == NULL)
		return XST_DEVICE_NOT_FOUND;

	if(XSpi_CfgInitialize(SpiInstancePtr, SpiConfigurationPtr, SpiConfigurationPtr->BaseAddress) != XST_SUCCESS)
		return XST_FAILURE;

	if(XSpi_SelfTest(SpiInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	if(SpiInstancePtr->SpiMode != XSP_STANDARD_MODE)
		return XST_SUCCESS;

	if(XIntc_Connect(InterruptInstancePtr, Interrupt_ID, (XInterruptHandler)XSpi_InterruptHandler, (void *)SpiInstancePtr) != XST_SUCCESS)
		return XST_FAILURE;

	XIntc_Enable(InterruptInstancePtr, Interrupt_ID);

	if(XIntc_Start(InterruptInstancePtr, XIN_REAL_MODE) != XST_SUCCESS)
		return XST_FAILURE;

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, InterruptInstancePtr);
	Xil_ExceptionEnable();

	XSpi_SetStatusHandler(SpiInstancePtr, SpiInstancePtr, (XSpi_StatusHandler)SpiHandler);

	if(XSpi_SetOptions(SpiInstancePtr, XSP_MASTER_OPTION|XSP_MANUAL_SSELECT_OPTION|XSP_CLK_PHASE_1_OPTION|XSP_CLK_ACTIVE_LOW_OPTION) != XST_SUCCESS)
		return XST_FAILURE;

	if(XSpi_SetSlaveSelect(SpiInstancePtr, ADXL362_SPI_SELECT) != XST_SUCCESS)
		return XST_FAILURE;


	XSpi_Start(SpiInstancePtr);

	return XST_SUCCESS;

}

int ConfigurationADXL362(XSpi *SpiInstancePtr){

	memset(SpiWriteBuffer, 0x00, sizeof(SpiWriteBuffer));
	memset(SpiReadBuffer, 0x00, sizeof(SpiReadBuffer));
	SpiWriteBuffer[0] = ADXL362_ReadCommand;
	SpiWriteBuffer[1] = ADXL362_DeviceAddress;

	if(XSpi_Transfer(SpiInstancePtr, SpiWriteBuffer, SpiReadBuffer, Spi_ConfigMessageSize) != XST_SUCCESS)
		return XST_FAILURE;

	while(SpiFlag != TRUE){}
	SpiFlag = FALSE;

	if(SpiReadBuffer[2] != ADXL362_DeviceAddressValue)
		return XST_FAILURE;

	memset(SpiWriteBuffer, 0x00, sizeof(SpiWriteBuffer));
	memset(SpiReadBuffer, 0x00, sizeof(SpiReadBuffer));
	SpiWriteBuffer[0] = ADXL362_WriteCommand;
	SpiWriteBuffer[1] = ADXL362_PowerCTRL_RegisterAddress;
	SpiWriteBuffer[2] = ADXL362_MeasurementModeEnable;

	if(XSpi_Transfer(SpiInstancePtr, SpiWriteBuffer, SpiReadBuffer, Spi_ConfigMessageSize) != XST_SUCCESS)
		return XST_FAILURE;

	while(SpiFlag != TRUE){}
	SpiFlag = FALSE;

	return XST_SUCCESS;

}

int MeasurementAccelerometerADXL362(XSpi *SpiInstancePtr){

	memset(SpiWriteBuffer, 0x00, sizeof(SpiWriteBuffer));
	memset(SpiReadBuffer, 0x00, sizeof(SpiReadBuffer));

	SpiWriteBuffer[0] = ADXL362_ReadCommand;
	SpiWriteBuffer[1] = ADXL362_AccValues_InitialAddress;

	if(XSpi_Transfer(SpiInstancePtr, SpiWriteBuffer, SpiReadBuffer, Spi_ConfigMessageSize) != XST_SUCCESS)
		return XST_FAILURE;

	while(SpiFlag != TRUE){}
	SpiFlag = FALSE;

	sprintf((char*)ADXL362_ValuesMessage, "\nXDATA[7:0] = %u\nYDATA[7:0] = %u\nZDATA[7:0] = %u\n", SpiReadBuffer[2], SpiReadBuffer[4], SpiReadBuffer[6]);

	return XST_SUCCESS;

}

void SpiHandler(void *CallBackRef, uint32_t StatusEvent, uint32_t ByteCount){
	SpiFlag = TRUE;										/* Indicate the transfer on the SPI bus is no longer in progress regardless of the status event. */
	if(StatusEvent != XST_SPI_TRANSFER_DONE){			/* If the event was not transfer done, then track it as an error. */
		SpiErrorFlag = TRUE;
	}
}

