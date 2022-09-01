/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

uint8_t  ReceiveTempBuffer[3];
uint8_t  ProtocolSelection[4];
uint8_t  ProtocolSelectionLength = 0;
bool     InterruptFlag = false;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

#define BME280_ADDRESS    0xEC
#define BME280_REG_ID     0xD0
#define BME280_ID         0x60

#define BME280_REG_SOFTRESET    0xE0
#define BME280_SOFTRESET_VALUE  0xB6
#define BME280_REGISTER_STATUS  0xF3
#define BME280_STATUS_IM_UPDATE 0x01
#define BME280_REGISTER_DIG_T1  0x88
#define BME280_REGISTER_DIG_T2  0x8A
#define BME280_REGISTER_DIG_T3  0x8C
#define BME280_REG_CONFIG       0xF5
#define BME280_REG_CTRL_MEAS    0xF4
#define BME280_REGISTER_TEMPDATA 0xFA

#define BME280_STBY_MSK    0xE0
#define BME280_FILTER_MSK  0x1C
#define BME280_OSRS_T_MSK  0XE0
#define BME280_MODE_MSK    0x03
#define BME280_MODE_NORMAL 0x03

#define BME280_STBY_1000 0xA0
#define BME280_FILTER_4  0x08
#define BME280_OSRS_T_x4 0x60

#define be24toward(a) ((((a)>>16)&0x000000ff)|((a)&0x0000ff00)|(((a)<<16)&0x00ff0000))

char str[100];
float Temperature = 0.0f;

typedef struct{
	uint16_t dig_T1;
	uint16_t dig_T2;
	uint16_t dig_T3;
}BME280_CalibData;
BME280_CalibData CalibData;

typedef struct{
	uint8_t ComPortControl:2 ;
	uint8_t Data:8 ;
	uint8_t RegisterAddress:8 ;

} InterfaceInformation;
InterfaceInformation InterfaceData;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart3){
		InterruptFlag = true;
		HAL_UART_Receive_IT(&huart3,ReceiveTempBuffer,3);
	}
}

void ProtSelect(void){

	InterfaceData.ComPortControl = (ReceiveTempBuffer[0] & 0x03);
	InterfaceData.Data = ((ReceiveTempBuffer[1]&0x03) << 6) + ((ReceiveTempBuffer[0] & 0xFC) >> 2);
	InterfaceData.RegisterAddress = ((ReceiveTempBuffer[2]&0x03) << 6) + ((ReceiveTempBuffer[1] & 0xFC) >> 2);

	if(InterfaceData.ComPortControl == 0){
		ProtocolSelectionLength = sprintf(ProtocolSelection,"UART");
	}
	else if(InterfaceData.ComPortControl == 1){
		ProtocolSelectionLength = sprintf(ProtocolSelection,"I2CR");
	}
	else if(InterfaceData.ComPortControl == 2){
		ProtocolSelectionLength = sprintf(ProtocolSelection,"SPI");
	}
	else if(InterfaceData.ComPortControl == 3){
		ProtocolSelectionLength = sprintf(ProtocolSelection,"I2CW");
	}

}

void BME280I2Cx_WriteData(uint8_t Reg, uint8_t Value){

	HAL_StatusTypeDef ret = HAL_OK;
	ret = HAL_I2C_Mem_Write(&hi2c1,BME280_ADDRESS,(uint16_t)Reg,I2C_MEMADD_SIZE_8BIT,&Value,1,1000);
	if(ret != HAL_OK){
		Error_Handler();
	}
}

uint8_t BME280I2Cx_ReadData(uint8_t Reg){

	HAL_StatusTypeDef ret = HAL_OK;
	uint8_t ValueReadData = 0;

	ret = HAL_I2C_Mem_Read(&hi2c1,BME280_ADDRESS,Reg,I2C_MEMADD_SIZE_8BIT,&ValueReadData,1,1000);
	if(ret != HAL_OK){
		Error_Handler();
	}
	return ValueReadData;
}

uint8_t BME280_ReadReg_U16(uint8_t Reg, uint8_t* Value){

	HAL_StatusTypeDef ret = HAL_OK;
	ret = HAL_I2C_Mem_Read(&hi2c1,BME280_ADDRESS,Reg,I2C_MEMADD_SIZE_8BIT,(uint8_t*)Value,2,1000);
	if(ret != HAL_OK){
		Error_Handler();
	}
}

uint8_t BME280_ReadReg_S24(uint8_t Reg, uint8_t* Value){

	HAL_StatusTypeDef ret = HAL_OK;
	ret = HAL_I2C_Mem_Read(&hi2c1,BME280_ADDRESS,Reg,I2C_MEMADD_SIZE_8BIT,(uint8_t*)Value,3,1000);
	if(ret != HAL_OK){
		Error_Handler();
	}
	*(uint32_t *)Value = be24toward(*(uint32_t *)Value)&0x00FFFFFF;
}

void BME280_Init(){

	uint8_t Value = 0;

	Value = BME280I2Cx_ReadData(BME280_REG_ID);
	if(Value != BME280_ID){
		Error_Handler();
	}

	BME280I2Cx_WriteData(BME280_REG_SOFTRESET,BME280_SOFTRESET_VALUE);
	while(BME280I2Cx_ReadData(BME280_REGISTER_STATUS)&0x09 & BME280_STATUS_IM_UPDATE);

	BME280_ReadReg_U16(BME280_REGISTER_DIG_T1,&CalibData.dig_T1);
	BME280_ReadReg_U16(BME280_REGISTER_DIG_T2,&CalibData.dig_T2);
	BME280_ReadReg_U16(BME280_REGISTER_DIG_T3,&CalibData.dig_T3);

	Value = BME280I2Cx_ReadData(BME280_REG_CONFIG) &~ BME280_STBY_MSK;
	Value = BME280_STBY_1000 & BME280_STBY_MSK;
	BME280I2Cx_WriteData(BME280_REG_CONFIG,Value);

	Value = BME280I2Cx_ReadData(BME280_REG_CONFIG) &~ BME280_FILTER_MSK;
	Value = BME280_FILTER_4 & BME280_FILTER_MSK;
	BME280I2Cx_WriteData(BME280_REG_CONFIG,Value);

	Value = BME280I2Cx_ReadData(BME280_REG_CTRL_MEAS) &~ BME280_OSRS_T_MSK;
	Value = BME280_OSRS_T_x4 & BME280_OSRS_T_MSK;
	BME280I2Cx_WriteData(BME280_REG_CTRL_MEAS,Value);

	Value = BME280I2Cx_ReadData(BME280_REG_CTRL_MEAS) &~ BME280_MODE_MSK;
	Value |= BME280_MODE_NORMAL & BME280_MODE_MSK;
	BME280I2Cx_WriteData(BME280_REG_CTRL_MEAS,Value);
}

float BME280_ReadTemperature(){
	float TemperatureFloat = 0.0f;
	int32_t TemperatureRaw;
	int32_t TemperatureInt;
	int32_t Value1,Value2;

	BME280_ReadReg_S24(BME280_REGISTER_TEMPDATA,&TemperatureRaw);
	TemperatureRaw >>= 4;

	Value1 = ((((TemperatureRaw>>3)-((int32_t)CalibData.dig_T1 << 1)))*((int32_t)CalibData.dig_T2)) >> 11;
	Value2 = (((((TemperatureRaw>>4)-((int32_t)CalibData.dig_T1))*((TemperatureRaw>>4) - ((int32_t)CalibData.dig_T1))) >> 12)*((int32_t)CalibData.dig_T3)) >> 14;
	TemperatureInt = Value1 + Value2;
	TemperatureFloat = ((TemperatureInt*5+128) >> 8);
	TemperatureFloat /= 100.0f;
	return TemperatureFloat;

}

int SPITest_AnalogDiscovery2(void){

	uint8_t SPIData[2];
	bool SPIFlag = false;

	// ChipSelect Pin should default HIGH
	HAL_StatusTypeDef ret;
	HAL_GPIO_WritePin(ChipSelect_GPIO_Port,ChipSelect_Pin,GPIO_PIN_SET);
    HAL_Delay(100);

    // READ DATA
    //1. Put ChipSelect LOW = Activate
    HAL_GPIO_WritePin(ChipSelect_GPIO_Port,ChipSelect_Pin,GPIO_PIN_RESET);
    HAL_Delay(100);

    //2. Transmit Register
    SPIData[0] = InterfaceData.Data;
    ret = HAL_SPI_Transmit(&hspi1,SPIData,1,100);
    HAL_Delay(100);
    if(ret != HAL_OK){
		Error_Handler();
	}
    else{
    	//3. Read
    	ret = HAL_SPI_Receive(&hspi1,&SPIData[1],1,100);
    	HAL_Delay(100);
    	if(ret != HAL_OK){
    		Error_Handler();
        }
    	else{
    		SPIFlag = true;
    	}
    }

    //4. Bring ChipSelect HIGH = Deactivate
	HAL_GPIO_WritePin(ChipSelect_GPIO_Port,ChipSelect_Pin,GPIO_PIN_SET);
    HAL_Delay(100);
    if(SPIFlag){
    	return (SPIData[1]);
    }
    else{
    	return (0);
    }

}

void ClearInformationData(void){

	// Clear InterfaceData & ProtocolSelection for Other Data
	InterfaceData.Data = 0x00;
	InterfaceData.ComPortControl = 0x00;
	InterfaceData.RegisterAddress = 0x00;
	sprintf(ProtocolSelection,"FULL");
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void){

  /* USER CODE BEGIN 1 */
	uint8_t Data;
	bool  BME280InitFlag = true;
	char aTXBuffer[16];
	HAL_StatusTypeDef ret;
	uint8_t SPIFinalData;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  HAL_UART_Receive_IT(&huart3, ReceiveTempBuffer, 3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1){
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(InterruptFlag){

		  ProtSelect();
		  InterruptFlag = false;

		  if(!(strcmp(ProtocolSelection,"UART"))){

		  	  // Transmit Data
		  	  Data = InterfaceData.Data;
	    	  ret = HAL_UART_Transmit_IT(&huart3,(uint8_t *)aTXBuffer, sprintf(aTXBuffer,"%d",Data));
		  	  if(ret != HAL_OK){
		  	      Error_Handler();
		  	  }
		  	  ClearInformationData();

		  }
		  else if(!(strcmp(ProtocolSelection,"I2CR"))){

		  	  // For I2CWrite operation BME280 initialization once
		  	  if(BME280InitFlag){
		  		  BME280_Init();
		  		  BME280InitFlag = false;
		  	  }

		  	  // Temperature Sensor BME280
		      Temperature = BME280_ReadTemperature();

		  	  // Transmit Data with UART
		  	  sprintf(str,"Temperature: %.2d C\n\n",(int)Temperature); // @suppress("Float formatting support")
		  	  ret = HAL_UART_Transmit_IT(&huart3,(uint8_t *)str,strlen(str));
		  	  if(ret != HAL_OK){
		  		  Error_Handler();
		  	  }
		      ClearInformationData();

		  }
		  else if(!(strcmp(ProtocolSelection,"I2CW"))){

		  	  ret = HAL_UART_Transmit_IT(&huart3,(uint8_t *)"I2CW\r\n",4);
		  	  if(ret != HAL_OK){
		  	   	  Error_Handler();
		  	  }
		  	  ClearInformationData();

		  }
		  else if(!(strcmp(ProtocolSelection,"SPI"))){

		  	  // Analog Discovery 2
		  	  SPIFinalData = SPITest_AnalogDiscovery2();
		  	  if(SPIFinalData != 0){
			      HAL_UART_Transmit_IT(&huart3,(uint8_t *)aTXBuffer, sprintf(aTXBuffer,"%d",SPIFinalData));
		  	  }
		  	  ClearInformationData();

		  }
	  }
 }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ChipSelect_GPIO_Port, ChipSelect_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ChipSelect_Pin */
  GPIO_InitStruct.Pin = ChipSelect_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ChipSelect_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
