#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xil_printf.h"

XGpio			Gpio, Gpio1;
XSpi			Spi;
XIic			Iic;
XUartLite		UartLite;
XIntc			InterruptController;

uint8_t 		UartReceiveBuffer[UART_RX_MessageSize];

volatile int 	UartReceivedFlag;
volatile int 	UartTransmittedFlag;

const char		Uart_StartMessage[] = "The process started.\n\n";
uint8_t 		ADXL362_ValuesMessage[100];
uint8_t			ADT7420_ValuesMessage[100];

int main(void){

	if(XIntc_Initialize(&InterruptController, INTC_DEVICE_ID) != XST_SUCCESS){
		xil_printf("Interrupt Initialize Failed!\r\n");
		return XST_FAILURE;
	}

	if(GPIO_Init_IT(&Gpio, &InterruptController, GPIO_DEVICE_ID, INTC_GPIO_INTERRUPT_ID, BUTTON_CHANNEL) != XST_SUCCESS){
		xil_printf("GPIO Interrupt Failed!\r\n");
		return XST_FAILURE;
	}

	if(GPIO_Init(&Gpio1, GPIO_1_DEVICE_ID) != XST_SUCCESS){
		xil_printf("GPIO1 Failed!\r\n");
		return XST_FAILURE;
	}

	if(UartLite_Init_IT(&UartLite, &InterruptController, UARTLITE_DEVICE_ID, INTC_UARTLITE_INTERRUPT_ID) != XST_SUCCESS){
		xil_printf("UartLite Interrupt Failed!\r\n");
		return XST_FAILURE;
	}

	if(SPI_Init_IT(&Spi, &InterruptController, SPI_DEVICE_ID, INTC_SPI_INTERRUPT_ID) != XST_SUCCESS){
		xil_printf("SPI Interrupt Failed!\r\n");
		return XST_FAILURE;
	}

	if(IIC_Init_IT(&Iic, &InterruptController, IIC_DEVICE_ID, INTC_IIC_INTERRUPT_ID) != XST_SUCCESS){
		xil_printf("IIC Interrupt Failed!\r\n");
		return XST_FAILURE;
	}

	if(ConfigurationADXL362(&Spi) != XST_SUCCESS){
		xil_printf("ADXL362 Configuration Failed!\r\n");
		return XST_FAILURE;
	}

	XUartLite_Send(&UartLite, (uint8_t*)Uart_StartMessage, sizeof(Uart_StartMessage));
	while(UartTransmittedFlag != TRUE){}
	UartTransmittedFlag = FALSE;

	while(TRUE){
		if(UartReceivedFlag == TRUE){
			UartReceivedFlag = FALSE;

			uint32_t Leds_Value = ((UartReceiveBuffer[0] << 8) | UartReceiveBuffer[1]);
			XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, Leds_Value);

			if(MeasurementTemperatureADT7420(&Iic) != XST_SUCCESS){
				xil_printf("ADT7420 Measurement Failed!\r\n");
				return XST_FAILURE;
			}
			XUartLite_Send(&UartLite, ADT7420_ValuesMessage, strlen((char*)ADT7420_ValuesMessage));
			while(UartTransmittedFlag != TRUE){}
			UartTransmittedFlag = FALSE;

			if(MeasurementAccelerometerADXL362(&Spi) != XST_SUCCESS){
				xil_printf("ADXL362 Measurement Failed!\r\n");
				return XST_FAILURE;
			}
			XUartLite_Send(&UartLite, ADXL362_ValuesMessage, strlen((char*)ADXL362_ValuesMessage));
			while(UartTransmittedFlag != TRUE){}
			UartTransmittedFlag = FALSE;
		}
	}
}
