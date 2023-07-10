/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Led_Blue_Pin 			GPIO_PIN_7
#define Led_Blue_GPIO_Port 		GPIOB

#define USART_TXMessageSize		(uint8_t)100
#define USART_RXMessageSize		(uint8_t)1
#define AdcDMA_MessageSize		(uint32_t)2

#define Resolution_12Bit		(uint32_t)4095
#define VoltageLevel			(float)3.3
#define MaxAngelLevel			(uint32_t)360
#define TempSensor_V25			(float)0.76
#define TempSensor_AvgSlope		(float)0.0025
#define TempSensor_Vsense		(float)(3.3/4095)

#define IncreasedVoltageLevel	(float)0.10
#define DecreasedVoltageLevel	(float)0.10

#define APB2_ClockFrequencyMHz	(uint16_t)25

#define H_USART3				&huart3
#define H_ADC1					&hadc1
#define H_ADC2					&hadc2
#define H_DMA_ADC1				&hdma_adc1
#define H_DAC					&hdac
#define H_TIM1					&htim1

/* APB2 Timer Clock = 25MHz, Prescaler = 1-1  */
#define APB2_25MHz_InitialTimer_usValue		(float)6.8900
#define APB2_25MHz_IncrementTimer_usValue	(float)1.5600
#define APB2_25MHz_InitialTimer_Counter		(uint16_t)2
#define APB2_25MHz_IncrementTimer_Counter	(uint16_t)12

typedef enum{
	Stop,
	Transmit,
	Receive,
	Reset
}CommunicationMission;

typedef enum{
	IN0,
	IN1,
	IN2,
	IN3,
	Temperature_Sensor_Channel,
	Out0,
	SinWaveDAC,
	None
}AdcChannels;

typedef enum{
	StopChannel,
	StartChannel
}AdcStartStop;

typedef enum{
	MeasurementVoltage,
	MeasurementAngle,
	MeasurementTemperature,
}MeasurementType;

typedef enum{
	usart_element,
	adc2_in0_element,
	adc2_in1_element,
	adc2_in3_element,
	adc1_in2_element,
	adc1_temp_element,
	dac_out0_element
}CommunicationElement;

typedef struct __ADC_Item{
	CommunicationElement	Element;
	uint32_t				AdcResolution;
	uint32_t				AdcMaxAngelLevel;
	float					AdcVoltageLevel;
	float					AdcTempSensor_V25;
	float					AdcTempSensor_AvgSlope;
	float					AdcTempSensor_VSense;
}ADC_Item;

typedef struct __DAC_Item{
	CommunicationElement	Element;
	uint32_t				DacResolution;
	float					DacVoltageLevel;
	float					DacIncreasedVoltageLevel;
	float					DacDecreasedVoltageLevel;
}DAC_Item;

typedef struct __Communication_Item{
	CommunicationElement	Element;
	CommunicationMission	Mission;
	uint8_t					Tx_Buffer[USART_TXMessageSize];
	uint8_t					Rx_Buffer[USART_RXMessageSize];
	uint8_t					TX_Message_Size;
	uint8_t					RX_Message_Size;
}Communication_Item;

typedef struct __ADC_DAC_Values{
	float					Temperature;
	float					Voltage;
	float					Angle;
	uint32_t 				PollingValue;
	uint32_t				DMAValues[AdcDMA_MessageSize];
}ADC_DAC_Values;

typedef struct __Floating_Values{
	uint8_t					Voltage_AfterPoint;
	uint8_t					Voltage_BeforePoint;
	uint16_t				Angle_AfterPoint;
	uint16_t				Angle_BeforePoint;
	uint8_t					Temperature_AfterPoint;
	uint8_t					Temperature_BeforePoint;
}Floating_Values;

/*
 * T_conv = (Sampling_Time + 12.5cycles)/(ADC_Clock)
 * 		When T_conv = 17.1us:
 * 			Sampling_Time = 71.5cycles, ADC_Clock = 5MHz 	=> (71.5+12.5)/5 = 16.8us
 * 			Sampling_Time = 144cycles, ADC_Clock = 9MHz 	=> (144+12.5)/9 = 17.4us
 * 		DMA Setting
 * 			Data Width					: Word
 * 			Mode						: Circular
 * 			Scan Conversion Mode		: Enabled (Parameter Setting)
 * 			Continuous Conversion Mode	: Enabled
 * 			DMA Continuous Requests		: Enabled
 *
 * Timer1:
 * 		Clock Source 	: Internal Clock
 * 		Prescaler	 	: 1-1
 * 		Counter Period	: 0xFFFF-1
 *
 */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
