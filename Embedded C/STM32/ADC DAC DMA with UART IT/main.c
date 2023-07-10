/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
 ADC_HandleTypeDef hadc1;
 ADC_HandleTypeDef hadc2;
 DMA_HandleTypeDef hdma_adc1;
 DAC_HandleTypeDef hdac;
 TIM_HandleTypeDef htim1;
 UART_HandleTypeDef huart3;
/* USER CODE BEGIN PV */

 Communication_Item usart3;
 ADC_Item			Adc2_In0, Adc2_In1, Adc1_In2, Adc2_In3, Adc1_TemperatureSensor;
 DAC_Item			Dac_Out0;
 ADC_DAC_Values		Input0, Input1, Input3, Output0, AdcDMA = {0.0, 0.0, 0.0, 0, {0,0}};
 Floating_Values	In0_Fvalue, In1_Fvalue, In2_Fvalue, In3_Fvalue, Temperature_Fvalue, Dac_Fvalue;
 AdcChannels		SelectedChannel;
 AdcStartStop		SelectedStartStop;

 ITStatus			UsartMessage_Available 			= RESET;
 ITStatus			UsartTXMessage_Available 		= RESET;
 ITStatus			AdcTemperatureMessage_Available = SET;
 ITStatus			AdcInput2Message_Available 		= SET;

 uint8_t			MessageBuffer[USART_TXMessageSize];
 uint16_t 			SinWaveIndex = 0;
 uint32_t			SinWave[371];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

void CommunicationInitialization(void);
void AnalyzeMessage(void);
void ConverttoFloatingMessage(ADC_DAC_Values AdcDacValues, Floating_Values *FValue, MeasurementType MType);

void ADC_SelectedChannel(ADC_HandleTypeDef *AdcHandle, AdcChannels AdcChannel);
void ADC_GetValue(ADC_HandleTypeDef *AdcHandle, ADC_DAC_Values *Adc);
void DAC_SetValue(DAC_HandleTypeDef *DacHandle, ADC_DAC_Values *Dac);
void SinWaveDAC_SetValue(DAC_HandleTypeDef *DacHandle);
void APB2_25MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime);
void UART_Transmit(UART_HandleTypeDef *UartHandle, uint8_t *pData);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void){
  /* USER CODE BEGIN 1 */

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_DAC_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  UART_Transmit(H_USART3, (uint8_t*)"The process started.\n\n");

  CommunicationInitialization();

  HAL_TIM_Base_Start(H_TIM1);
  HAL_UART_Receive_IT(H_USART3, (uint8_t*)(usart3.Rx_Buffer), usart3.RX_Message_Size);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(UsartMessage_Available == SET){

		  UsartMessage_Available = RESET;
		  AnalyzeMessage();

		  if(SelectedStartStop == StartChannel){

			  HAL_GPIO_WritePin(Led_Blue_GPIO_Port, Led_Blue_Pin, SET);

			  if(SelectedChannel == Out0){

				  Output0.Voltage 	+= Dac_Out0.DacIncreasedVoltageLevel;
				  if(Output0.Voltage >= Dac_Out0.DacVoltageLevel)
					  Output0.Voltage = 0;

				  Output0.PollingValue = ((Output0.Voltage)*(Dac_Out0.DacResolution))/Dac_Out0.DacVoltageLevel;

				  DAC_SetValue(H_DAC, &Output0);
				  ConverttoFloatingMessage(Output0, &Dac_Fvalue, MeasurementVoltage);

				  sprintf((char*)MessageBuffer, "\nDAC Variable: %lu\nRefers to %u.02%u (Volt)\n",(unsigned long)Output0.PollingValue, Dac_Fvalue.Voltage_BeforePoint, Dac_Fvalue.Voltage_AfterPoint);
				  UART_Transmit(H_USART3, MessageBuffer);

			  }
			  else if((SelectedChannel == IN0) || (SelectedChannel == IN1) || (SelectedChannel == IN3)){

				  ADC_SelectedChannel(H_ADC2, SelectedChannel);

				  if(SelectedChannel == IN0){

					  ADC_GetValue(H_ADC2, &Input0);

					  Input0.Voltage = (Input0.PollingValue*Adc2_In0.AdcVoltageLevel)/Adc2_In0.AdcResolution;
					  Input0.Angle = ((Input0.Voltage)*Adc2_In0.AdcMaxAngelLevel)/Adc2_In0.AdcVoltageLevel;

					  ConverttoFloatingMessage(Input0, &In0_Fvalue, MeasurementVoltage);
					  ConverttoFloatingMessage(Input0, &In0_Fvalue, MeasurementAngle);

					  sprintf((char*)MessageBuffer, "\n\nADC2 Input0\nVoltage: %u.02%u (Volt)\nAngle: %u.02%u (Degree)\n",In0_Fvalue.Voltage_BeforePoint, In0_Fvalue.Voltage_AfterPoint, In0_Fvalue.Angle_BeforePoint, In0_Fvalue.Angle_AfterPoint);
					  UART_Transmit(H_USART3, MessageBuffer);

				  }
				  if(SelectedChannel == IN1){

					  ADC_GetValue(H_ADC2, &Input1);

					  Input1.Voltage = (Input1.PollingValue*Adc2_In1.AdcVoltageLevel)/Adc2_In1.AdcResolution;
					  ConverttoFloatingMessage(Input1, &In1_Fvalue, MeasurementVoltage);

					  sprintf((char*)MessageBuffer, "\n\nADC2 Input1\nVoltage: %u.02%u (Volt)\n",In1_Fvalue.Voltage_BeforePoint, In1_Fvalue.Voltage_AfterPoint);
					  UART_Transmit(H_USART3, MessageBuffer);

				  }
				  if(SelectedChannel == IN3){

					  ADC_GetValue(H_ADC2, &Input3);

					  Input3.Voltage = (Input3.PollingValue*Adc2_In3.AdcVoltageLevel)/Adc2_In3.AdcResolution;
					  ConverttoFloatingMessage(Input3, &In3_Fvalue, MeasurementVoltage);

					  sprintf((char*)MessageBuffer, "\n\nADC2 Input3\nVoltage: %u.02%u (Volt)\n",In3_Fvalue.Voltage_BeforePoint, In3_Fvalue.Voltage_AfterPoint);
					  UART_Transmit(H_USART3, MessageBuffer);

				  }
			  }
			  else if((SelectedChannel == Temperature_Sensor_Channel) || (SelectedChannel == IN2)){

				  if(SelectedChannel == Temperature_Sensor_Channel){

					  if(AdcTemperatureMessage_Available == SET){

						  AdcTemperatureMessage_Available = RESET;
						  if(HAL_ADC_Start_DMA(H_ADC1, AdcDMA.DMAValues, 2) != HAL_OK){
							  Error_Handler();
						  }
						  while(AdcTemperatureMessage_Available != SET){}

						  AdcDMA.Temperature = ((Adc1_TemperatureSensor.AdcTempSensor_V25-(Adc1_TemperatureSensor.AdcTempSensor_VSense*AdcDMA.DMAValues[0]))/Adc1_TemperatureSensor.AdcTempSensor_AvgSlope) +25;
						  ConverttoFloatingMessage(AdcDMA, &Temperature_Fvalue, MeasurementTemperature);

						  sprintf((char*)MessageBuffer, "\nTemperature: %u.02%u C\r\n",Temperature_Fvalue.Temperature_BeforePoint, Temperature_Fvalue.Temperature_AfterPoint);
						  UART_Transmit(H_USART3, MessageBuffer);

					  }

				  }
				  else if(SelectedChannel == IN2){

					  if(AdcInput2Message_Available == SET){

						  AdcInput2Message_Available = RESET;
						  if(HAL_ADC_Start_DMA(H_ADC1, AdcDMA.DMAValues, 2) != HAL_OK){
							  Error_Handler();
						  }
						  while(AdcInput2Message_Available != SET){}

						  AdcDMA.Voltage = (AdcDMA.DMAValues[1]*Adc1_In2.AdcVoltageLevel)/Adc1_In2.AdcResolution;
						  ConverttoFloatingMessage(AdcDMA, &In2_Fvalue, MeasurementVoltage);

						  sprintf((char*)MessageBuffer, "\nADC1 Input2\nVoltage: %u.02%u (Volt)\n",In2_Fvalue.Voltage_BeforePoint, In2_Fvalue.Voltage_AfterPoint);
						  UART_Transmit(H_USART3, MessageBuffer);

					  }
				  }
			  }
			  else if(SelectedChannel == SinWaveDAC){
				  while(UsartMessage_Available == RESET){
					  SinWaveDAC_SetValue(H_DAC);
					  if(SinWaveIndex == 371)
						  SinWaveIndex = 0;
				  }
			  }
		  }
		  else if(SelectedStartStop == StopChannel){

			  HAL_GPIO_WritePin(Led_Blue_GPIO_Port, Led_Blue_Pin, RESET);
			  if(SelectedChannel == Out0){

				  Output0.Voltage 	-= Dac_Out0.DacDecreasedVoltageLevel;
				  if(Output0.Voltage <= 0.01)
					  Output0.Voltage = Dac_Out0.DacVoltageLevel;

				  Output0.PollingValue = ((Output0.Voltage)*(Dac_Out0.DacResolution))/Dac_Out0.DacVoltageLevel;

				  DAC_SetValue(H_DAC, &Output0);
				  ConverttoFloatingMessage(Output0, &Dac_Fvalue, MeasurementVoltage);

				  sprintf((char*)MessageBuffer, "\nDAC Variable: %lu\nRefers to %u.02%u (Volt)\n",(unsigned long)Output0.PollingValue, Dac_Fvalue.Voltage_BeforePoint, Dac_Fvalue.Voltage_AfterPoint);
				  UART_Transmit(H_USART3, MessageBuffer);

			  }
			  else if(SelectedChannel == Temperature_Sensor_Channel){
				  HAL_ADC_Stop_DMA(H_ADC1);
			  }
			  else{
				  HAL_ADC_Stop_DMA(H_ADC2);
			  }

			  SelectedChannel = None;

		  }
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void){
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK){
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void){

  /* USER CODE BEGIN ADC1_Init 0 */
  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */
  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK){
    Error_Handler();
  }

  /* Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.*/
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_144CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK){
    Error_Handler();
  }

  /* Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.*/
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 2;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void){

  /* USER CODE BEGIN ADC2_Init 0 */
  /* USER CODE END ADC2_Init 0 */
  /* USER CODE BEGIN ADC2_Init 1 */
  /* USER CODE END ADC2_Init 1 */

  /* Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)*/
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ENABLE;
  hadc2.Init.ContinuousConvMode = ENABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */
  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void){

  /* USER CODE BEGIN DAC_Init 0 */
  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */
  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK){
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */
  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void){

  /* USER CODE BEGIN TIM1_Init 0 */
  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */
  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 1-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xFFFF-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK){
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK){
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */
  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void){

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
  if (HAL_UART_Init(&huart3) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */
  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void){

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Led_Blue_GPIO_Port, Led_Blue_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Led_Blue_Pin */
  GPIO_InitStruct.Pin = Led_Blue_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Led_Blue_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void CommunicationInitialization(void){

	usart3.Element = usart_element;
	usart3.Mission = Receive;
	usart3.TX_Message_Size = USART_TXMessageSize;
	usart3.RX_Message_Size = USART_RXMessageSize;

	Adc2_In0.Element = adc2_in0_element;
	Adc2_In0.AdcResolution = Resolution_12Bit;
	Adc2_In0.AdcMaxAngelLevel = MaxAngelLevel;
	Adc2_In0.AdcVoltageLevel = VoltageLevel;

	Adc2_In1.Element = adc2_in1_element;
	Adc2_In1.AdcResolution = Resolution_12Bit;
	Adc2_In1.AdcMaxAngelLevel = MaxAngelLevel;
	Adc2_In1.AdcVoltageLevel = VoltageLevel;

	Adc2_In3.Element = adc2_in3_element;
	Adc2_In3.AdcResolution = Resolution_12Bit;
	Adc2_In3.AdcMaxAngelLevel = MaxAngelLevel;
	Adc2_In3.AdcVoltageLevel = VoltageLevel;

	Adc1_In2.Element = adc1_in2_element;
	Adc1_In2.AdcResolution = Resolution_12Bit;
	Adc1_In2.AdcMaxAngelLevel = MaxAngelLevel;
	Adc1_In2.AdcVoltageLevel = VoltageLevel;

	Adc1_TemperatureSensor.Element = adc1_temp_element;
	Adc1_TemperatureSensor.AdcResolution = Resolution_12Bit;
	Adc1_TemperatureSensor.AdcMaxAngelLevel = MaxAngelLevel;
	Adc1_TemperatureSensor.AdcVoltageLevel = VoltageLevel;
	Adc1_TemperatureSensor.AdcTempSensor_V25 = TempSensor_V25;
	Adc1_TemperatureSensor.AdcTempSensor_AvgSlope = TempSensor_AvgSlope;
	Adc1_TemperatureSensor.AdcTempSensor_VSense = TempSensor_Vsense;

	Dac_Out0.Element = dac_out0_element;
	Dac_Out0.DacResolution = Resolution_12Bit;
	Dac_Out0.DacVoltageLevel = VoltageLevel;
	Dac_Out0.DacIncreasedVoltageLevel = IncreasedVoltageLevel;
	Dac_Out0.DacDecreasedVoltageLevel = DecreasedVoltageLevel;

}

void AnalyzeMessage(void){

	uint8_t StartStopControlBit = ((usart3.Rx_Buffer[0] & 0x08) >> 3);
	uint8_t SelectedChannelBit = (usart3.Rx_Buffer[0] & 0x07);

	if(StartStopControlBit == 0x00)
		SelectedStartStop = StopChannel;
	else if(StartStopControlBit == 0x01)
		SelectedStartStop = StartChannel;

	if(SelectedChannelBit == 0x00)
		SelectedChannel = IN0;
	else if(SelectedChannelBit == 0x01)
		SelectedChannel = IN1;
	else if(SelectedChannelBit == 0x02)
		SelectedChannel = IN2;
	else if(SelectedChannelBit == 0x03)
		SelectedChannel = IN3;
	else if(SelectedChannelBit == 0x04)
		SelectedChannel = Temperature_Sensor_Channel;
	else if(SelectedChannelBit == 0x05)
		SelectedChannel = Out0;
	else if(SelectedChannelBit == 0x06)
		SelectedChannel = SinWaveDAC;

}

void ConverttoFloatingMessage(ADC_DAC_Values AdcDacValues, Floating_Values *FValue, MeasurementType MType){

	if(MType == MeasurementVoltage){
		FValue->Voltage_BeforePoint = (uint8_t)AdcDacValues.Voltage;
		FValue->Voltage_AfterPoint = (uint8_t)((AdcDacValues.Voltage - FValue->Voltage_BeforePoint)*100);
	}
	else if(MType == MeasurementAngle){
		FValue->Angle_BeforePoint = (uint8_t)AdcDacValues.Angle;
		FValue->Angle_AfterPoint = (uint8_t)((AdcDacValues.Angle - FValue->Angle_BeforePoint)*100);
	}
	else if(MType == MeasurementTemperature){
		FValue->Temperature_BeforePoint = (uint8_t)AdcDacValues.Temperature;
		FValue->Temperature_AfterPoint = (uint8_t)((AdcDacValues.Temperature - FValue->Temperature_BeforePoint)*100);
	}

}

void ADC_SelectedChannel(ADC_HandleTypeDef *AdcHandle, AdcChannels AdcChannel){

	ADC_ChannelConfTypeDef sConfig = {0};

	if(AdcChannel == IN0){
		/* Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.*/
		sConfig.Channel = ADC_CHANNEL_0;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
		if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}
	else if(AdcChannel == IN1){
		/* Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.*/
		sConfig.Channel = ADC_CHANNEL_1;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
		if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}
	else if(AdcChannel == IN3){
		/* Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.*/
		sConfig.Channel = ADC_CHANNEL_3;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
		if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK){
			Error_Handler();
		}
	}

}

void ADC_GetValue(ADC_HandleTypeDef *AdcHandle, ADC_DAC_Values *Adc){

	if(HAL_ADC_Start(AdcHandle) != HAL_OK)
		Error_Handler();

	if(HAL_ADC_PollForConversion(AdcHandle, HAL_MAX_DELAY) != HAL_OK)
		Error_Handler();

	Adc->PollingValue = HAL_ADC_GetValue(AdcHandle);

	if(HAL_ADC_Stop(AdcHandle) != HAL_OK)
		Error_Handler();

}

void DAC_SetValue(DAC_HandleTypeDef *DacHandle, ADC_DAC_Values *Dac){

	if(HAL_DAC_SetValue(DacHandle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, Dac->PollingValue) != HAL_OK)
		Error_Handler();

	if(HAL_DAC_Start(DacHandle, DAC_CHANNEL_1) != HAL_OK)
		Error_Handler();

}

void SinWaveDAC_SetValue(DAC_HandleTypeDef *DacHandle){

	HAL_DAC_SetValue(DacHandle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, SinWave[SinWaveIndex]);
	HAL_DAC_Start(DacHandle, DAC_CHANNEL_1);

	APB2_25MHz_TIM(H_TIM1, 10.0);		// To change frequency of sin wave
	SinWaveIndex++;

}

void APB2_25MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime){

	uint32_t Counter = 0;
	DelayTime = DelayTime - APB2_25MHz_InitialTimer_usValue;
	if((int)DelayTime)
		Counter = APB2_25MHz_InitialTimer_Counter + ((((uint16_t)(DelayTime/APB2_25MHz_IncrementTimer_usValue))-1)*APB2_25MHz_IncrementTimer_Counter);
	else
		Counter = APB2_25MHz_InitialTimer_Counter;

	__HAL_TIM_SET_COUNTER(TimerHandle, 0);
	while(__HAL_TIM_GET_COUNTER(TimerHandle) < Counter);

}

void UART_Transmit(UART_HandleTypeDef *UartHandle, uint8_t *pData){

	if(HAL_UART_Transmit_IT(UartHandle, pData, strlen((char*)pData)) != HAL_OK){
		Error_Handler();
	}

	while(UsartTXMessage_Available != SET){}
	UsartTXMessage_Available = RESET;

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == H_USART3){
		UsartMessage_Available = SET;
		HAL_UART_Receive_IT(H_USART3, (uint8_t*)(usart3.Rx_Buffer), usart3.RX_Message_Size);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == H_USART3)
		UsartTXMessage_Available = SET;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	if(SelectedChannel == IN2)
		AdcInput2Message_Available = SET;
	else if(SelectedChannel == Temperature_Sensor_Channel)
		AdcTemperatureMessage_Available = SET;
}



/*
 *
 *
 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void){
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  const char FAIL_INFORMATION[] = "Error Handler!\n";
  HAL_UART_Transmit_IT(H_USART3, (uint8_t*)FAIL_INFORMATION, sizeof(FAIL_INFORMATION));
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
