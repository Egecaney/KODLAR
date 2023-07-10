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
/* USER CODE BEGIN Private defines */

#define USB_OTG_VBUS_SensePin	GPIO_PIN_13
#define USB_OTG_VBUS_SensePort  GPIOH
#define Vcc_ControlPin			GPIO_PIN_15
#define Vcc_ControlPort  		GPIOH
#define MCU_LedPin				GPIO_PIN_9
#define MCU_LedPort  			GPIOG

#define I2C_ChipSelectPin		GPIO_PIN_8
#define I2C_ChipSelectPort		GPIOG

#define SPI2_ChipSelectPin		GPIO_PIN_4
#define SPI2_ChipSelectPort		GPIOA
#define SPI2_FastLatchPin		GPIO_PIN_4
#define SPI2_FastLatchPort		GPIOC
#define SPI2_ResetPin			GPIO_PIN_3
#define SPI2_ResetPort			GPIOA

#define SPI4_ChipSelectPin		GPIO_PIN_11
#define SPI4_ChipSelectPort		GPIOE
#define SPI4_FastLatchPin		GPIO_PIN_15
#define SPI4_FastLatchPort		GPIOE
#define SPI4_ResetPin			GPIO_PIN_6
#define SPI4_ResetPort			GPIOH

#define SPI5_ChipSelectPin		GPIO_PIN_6
#define SPI5_ChipSelectPort		GPIOF
#define SPI5_FastLatchPin		GPIO_PIN_10
#define SPI5_FastLatchPort		GPIOF
#define SPI5_ResetPin			GPIO_PIN_0
#define SPI5_ResetPort			GPIOC

#define Port_B2_ControlPin		GPIO_PIN_2
#define Port_B3_ControlPin		GPIO_PIN_3
#define Port_B4_ControlPin		GPIO_PIN_4
#define Port_B5_ControlPin		GPIO_PIN_5
#define Port_B_ControlPort		GPIOD

#define Port_A3_ControlPin		GPIO_PIN_3
#define Port_A3_ControlPort		GPIOI
#define Port_A5_ControlPin		GPIO_PIN_12
#define Port_A5_ControlPort		GPIOC

#define H_I2C					&hi2c1
#define H_SPI2					&hspi2
#define H_SPI4					&hspi4
#define H_SPI5					&hspi5

#define NumberOfDiscretePin		(int)14

#define PC_Handshake_Code		0xFD00
#define Board_Handshake_Code	0xFDAA

#define I2C_EEPROM_ADDRESS		0xA2

#define ControlMessageSize		4
#define I2c_TxByteSize			3
#define I2c_RxByteSize			1
#define Spi2_TxByteSize			3
#define Spi2_RxByteSize			1
#define Spi4_TxByteSize			3
#define Spi4_RxByteSize			1
#define Spi5_TxByteSize			3
#define Spi5_RxByteSize			1

#define WriteBit				0
#define ReadBit					1

typedef enum{
	Voltage_3v3,
	Voltage_5v
}Voltage;

typedef enum{
	USB_OTG_Disable,
	USB_OTG_Enable
}USBStatus;

typedef enum{
	None,
	Control_I2C,
	Control_SPI,
	Control_Discrete,
	Handshake
}BoardOperation;

typedef enum{
	Stop,
	Transmit,
	Receive,
	Reset
}CommunicationMission;

typedef enum{
	usb_otg_element,
	i2c_element,
	spi2_element,
	spi4_element,
	spi5_element
}CommunicationElement;

typedef struct __GPIO_Pin{
	GPIO_TypeDef*		GPIO_Port;
	GPIO_InitTypeDef	GPIO_Init;
	GPIO_PinState		State;
}GPIO_Pin;

typedef struct __Communication_Item{
	CommunicationElement	Element;
	FunctionalState			State;
	CommunicationMission	Mission;
	uint16_t				Target_Address;
	uint16_t				Register_Address;
	uint8_t					Data;
	uint8_t					Tx_Buffer[ControlMessageSize];
	uint8_t					Rx_Buffer[ControlMessageSize];
	uint8_t					Tx_MessageSize;
	uint8_t					Rx_MessageSize;
	GPIO_Pin				ChipSelectPin;
	GPIO_Pin				FastLatchPin;
	GPIO_Pin				ResetPin;
}Communication_Item;

struct __cmd_gpio_struct{
	uint32_t 	BoardOperation	:2;
	uint32_t 	PinStatus		:1;
	uint32_t 	PinNumber		:4;
	uint32_t 	Parity			:1;
	uint32_t 	Reserved		:24;
};

struct __cmd_i2c_struct{
	uint32_t 	BoardOperation		:2;
	uint32_t 	Mission				:1;
	uint32_t 	Parity				:1;
	uint32_t 	Reserved			:4;
	uint32_t 	Register_Address	:16;
	uint32_t 	Data				:8;
};

struct __cmd_spi_struct{
	uint32_t 	BoardOperation		:2;
	uint32_t 	Port				:2;
	uint32_t 	Mission				:2;
	uint32_t 	Parity				:1;
	uint32_t 	Reserved			:4;
	uint32_t 	Register_Address	:10;
	uint32_t 	Data				:8;
};

struct __cmd_handshake_struct{
	uint32_t 	BoardOperation		:2;
	uint32_t 	Handshake_Code		:16;
	uint32_t 	Parity				:1;
	uint32_t 	Reserved			:13;
};

struct __cmd_write_i2c_struct{
	uint32_t 	Data				:8;
	uint32_t 	RegisterAddress		:16;
	uint32_t 	Reserved			:8;
};

struct __cmd_read_i2c_struct{
	uint32_t 	RegisterAddress	:16;
	uint32_t 	Reserved		:16;
};

struct __cmd_write_spi_struct{
	uint32_t 	Data			:8;
	uint32_t 	RegisterAddress	:15;
	uint32_t 	WR_Bit			:1;
	uint32_t 	Reserved		:8;
};

struct __cmd_read_spi_struct{
	uint32_t 	RegisterAddress	:15;
	uint32_t 	WR_Bit			:1;
	uint32_t 	Reserved		:16;
};

typedef union __Control_Message_Union{
	struct	__cmd_gpio_struct		CMD_GPIO_Bits;
	struct	__cmd_i2c_struct		CMD_I2C_Bits;
	struct	__cmd_spi_struct		CMD_SPI_Bits;
	struct	__cmd_handshake_struct	CMD_Handshake_Bits;
	uint32_t 						all;
}Control_Message_Union;

typedef union __I2C_CMD_Message_Union{
	struct	__cmd_write_i2c_struct	I2C_Write_CMD_Bits;
	struct	__cmd_read_i2c_struct	I2C_Read_CMD_Bits;
	uint32_t 						all;
}I2C_CMD_Message_Union;

typedef union __SPI_CMD_Message_Union{
	struct	__cmd_write_spi_struct	SPI_Write_CMD_Bits;
	struct	__cmd_read_spi_struct	SPI_Read_CMD_Bits;
	uint32_t 						all;
}SPI_CMD_Message_Union;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
