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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
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

SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi4;
SPI_HandleTypeDef hspi5;

/* USER CODE BEGIN PV */

GPIO_Pin				DiscretePins[NumberOfDiscretePin];
uint8_t					SelectedDiscretePin;
GPIO_PinState			SelectedDiscretePinState;

Communication_Item		usb_otg, i2c, spi2, spi4, spi5;
BoardOperation			SelectedBoardOperation;
Communication_Item		SelectedCommunicationItem;

ITStatus				ControlMessage_Available = RESET;
ITStatus				I2C_Ready = SET, Transmitted_I2CReadCommand = RESET, Received_I2CMessage = RESET;
ITStatus				SPI_Ready = SET, Transmitted_SPIReadCommand = RESET, Received_SPIMessage = RESET;

Control_Message_Union	ControlMessage;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI4_Init(void);
static void MX_SPI5_Init(void);
/* USER CODE BEGIN PFP */

void SetVccVoltage(Voltage voltage);
USBStatus CheckUSBStatus(void);
void CommunicationInitialization(void);
void ControlCommunicationItem(CommunicationElement communicationElement, CommunicationMission mission);
void DiscretePinInitialization(void);
void ControlDiscretePin(void);
void AnalyzeControlMessage(void);
void ConfigurateCommunication(void);
void CreateProtocolCommandMessage(Communication_Item* protocol);
void UpdateControlMessage(void);
void TransmitterMessageSetting(Control_Message_Union message, uint8_t length);

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
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_SPI4_Init();
  MX_SPI5_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  // Set Vcc as 3.3 volts
  SetVccVoltage(Voltage_3v3);

  // Turn on MCU Led Pin
  HAL_GPIO_WritePin(MCU_LedPort, MCU_LedPin, GPIO_PIN_SET);

  // Activate A3, A5, B2, B3, B4 and B5 ports
  HAL_GPIO_WritePin(Port_A3_ControlPort, Port_A3_ControlPin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Port_A5_ControlPort, Port_A5_ControlPin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Port_B_ControlPort, Port_B2_ControlPin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Port_B_ControlPort, Port_B3_ControlPin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Port_B_ControlPort, Port_B4_ControlPin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Port_B_ControlPort, Port_B5_ControlPin, GPIO_PIN_SET);

  CommunicationInitialization();
  DiscretePinInitialization();

  // SET SPI CS Pins
  HAL_GPIO_WritePin(spi2.ChipSelectPin.GPIO_Port, spi2.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(spi4.ChipSelectPin.GPIO_Port, spi4.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(spi5.ChipSelectPin.GPIO_Port, spi5.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);

  // SET SPI SFL Pins
  HAL_GPIO_WritePin(spi2.FastLatchPin.GPIO_Port, spi2.FastLatchPin.GPIO_Init.Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(spi4.FastLatchPin.GPIO_Port, spi4.FastLatchPin.GPIO_Init.Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(spi5.FastLatchPin.GPIO_Port, spi5.FastLatchPin.GPIO_Init.Pin, GPIO_PIN_RESET);

  // SET SPI Reset Pins
  HAL_GPIO_WritePin(spi2.ResetPin.GPIO_Port, spi2.ResetPin.GPIO_Init.Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(spi4.ResetPin.GPIO_Port, spi4.ResetPin.GPIO_Init.Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(spi5.ResetPin.GPIO_Port, spi5.ResetPin.GPIO_Init.Pin, GPIO_PIN_SET);

  // Reset I2C WP Pin (WP is made by giving 3V in the hardware.)
  HAL_GPIO_WritePin(i2c.ChipSelectPin.GPIO_Port, i2c.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_RESET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  /* USB Communication Part */
	  if(usb_otg.State == ENABLE && usb_otg.Mission == Transmit){
		  CDC_Transmit_FS(usb_otg.Tx_Buffer, usb_otg.Tx_MessageSize);
		  usb_otg.Mission = Receive;
	  }

	  /* Analyzing Control Message */
	  if(ControlMessage_Available == SET){

		  int checkMessage = 0;
		  ControlMessage_Available = RESET;

		  /* Clear control message at the beginning. */
		  ControlMessage.all = 0;

		  for(int i=0; i < ControlMessageSize; i++){
			  ControlMessage.all |= (usb_otg.Rx_Buffer[i] << (8*i));
		  }

		  for(int i=0; i < (ControlMessageSize * 8); i++){
			  if((ControlMessage.all & (0x1 << i)) != 0)
				  checkMessage++;
		  }

		  /* If message is not correct program goes out of the if-state */
		  if(checkMessage %2 != 0)
			  continue;

		  /* If message is correct, sets board with given parameters */
		  AnalyzeControlMessage();

		  /* Operation Control Part */
		  if(SelectedBoardOperation == Control_Discrete){
			  ControlDiscretePin();
		  }
		  else if(SelectedBoardOperation == Control_SPI){
			  ConfigurateCommunication();
		  }
		  else if(SelectedBoardOperation == Control_I2C){
			  ConfigurateCommunication();
		  }
		  else if(SelectedBoardOperation == Handshake){
			  UpdateControlMessage();
			  TransmitterMessageSetting(ControlMessage, ControlMessageSize);
		  }

		  /* I2C Communication Part */
		  if(i2c.Mission != Stop){

			  if(i2c.Mission == Transmit && I2C_Ready == SET){

				  I2C_Ready = RESET;
				  do{
					  if(HAL_I2C_Master_Transmit_IT(H_I2C, i2c.Target_Address, (uint8_t*)(i2c.Tx_Buffer), i2c.Tx_MessageSize) != HAL_OK){
						  Error_Handler();
					  }
					  while(HAL_I2C_GetState(H_I2C) != HAL_I2C_STATE_READY){}
				  }while(HAL_I2C_GetError(H_I2C) == HAL_I2C_ERROR_AF);

				  HAL_Delay(10);
				  ControlCommunicationItem(i2c_element, Stop);

			  }
			  else if(i2c.Mission == Receive){

				  if(Transmitted_I2CReadCommand == RESET && I2C_Ready == SET){

					  I2C_Ready = RESET;
					  do{
						  if(HAL_I2C_Master_Transmit_IT(H_I2C, i2c.Target_Address, (uint8_t*)(i2c.Tx_Buffer), (i2c.Tx_MessageSize - i2c.Rx_MessageSize)) != HAL_OK){
							  Error_Handler();
						  }
						  while(HAL_I2C_GetState(H_I2C) != HAL_I2C_STATE_READY){}
					  }while(HAL_I2C_GetError(H_I2C) == HAL_I2C_ERROR_AF);
					  Transmitted_I2CReadCommand = SET;

				  }

				  if(Received_I2CMessage == RESET && Transmitted_I2CReadCommand == SET){

					  do{
						  // I2C target address updated with read bit
						  if(HAL_I2C_Master_Receive_IT(H_I2C, (i2c.Target_Address|ReadBit), (uint8_t*)(i2c.Tx_Buffer), i2c.Rx_MessageSize) != HAL_OK){
							  Error_Handler();
						  }
					  }while(HAL_I2C_GetError(H_I2C) == HAL_I2C_ERROR_AF);

					  HAL_Delay(10);
				  }

				  if(Received_I2CMessage == SET){
					  i2c.Data = i2c.Rx_Buffer[0];	//D7....D0
					  memset(i2c.Rx_Buffer, '\0', i2c.Rx_MessageSize);

					  Received_I2CMessage = RESET;
					  ControlCommunicationItem(i2c_element, Stop);

					  UpdateControlMessage();
					  TransmitterMessageSetting(ControlMessage, ControlMessageSize);

				  }
			  }
		  }

		  /* SPI Communication Part	*/
		  if(spi2.Mission != Stop){

			  if(spi2.Mission == Transmit && SPI_Ready == SET){

				  SPI_Ready = RESET;
				  if(HAL_SPI_Transmit_IT(H_SPI2, (uint8_t*)(spi2.Tx_Buffer), spi2.Tx_MessageSize) != HAL_OK){
					  Error_Handler();
				  }
				  while(SPI_Ready != SET){}

				  ControlCommunicationItem(spi2_element, Stop);

			  }
			  else if(spi2.Mission == Receive){

				  if(Transmitted_SPIReadCommand == RESET && SPI_Ready == SET){

					  SPI_Ready = RESET;
					  if(HAL_SPI_Transmit_IT(H_SPI2, (uint8_t*)(spi2.Tx_Buffer), (spi2.Tx_MessageSize - spi2.Rx_MessageSize)) != HAL_OK){
						  Error_Handler();
					  }
					  while(SPI_Ready != SET){}
					  Transmitted_I2CReadCommand = SET;

				  }

				  if(Received_SPIMessage == RESET && Transmitted_SPIReadCommand == SET){

					  if(HAL_SPI_Receive_IT(H_SPI2, (uint8_t*)(spi2.Tx_Buffer), spi2.Rx_MessageSize) != HAL_OK){
						  Error_Handler();
					  }

				  }

				  if(Received_SPIMessage == SET){
					  Received_SPIMessage = RESET;
					  ControlCommunicationItem(spi2_element, Stop);

					  spi2.Data = spi2.Rx_Buffer[0];	//D7....D0
					  memset(spi2.Rx_Buffer, '\0', spi2.Rx_MessageSize);

					  UpdateControlMessage();
					  TransmitterMessageSetting(ControlMessage, ControlMessageSize);
				  }
			  }
		  }
		  if(spi4.Mission != Stop){

			  if(spi4.Mission == Transmit && SPI_Ready == SET){

				  SPI_Ready = RESET;
				  if(HAL_SPI_Transmit_IT(H_SPI4, (uint8_t*)(spi4.Tx_Buffer), spi4.Tx_MessageSize) != HAL_OK){
					  Error_Handler();
				  }
				  while(SPI_Ready != SET){}

				  ControlCommunicationItem(spi4_element, Stop);

			  }
			  else if(spi4.Mission == Receive){

				  if(Transmitted_SPIReadCommand == RESET && SPI_Ready == SET){

					  SPI_Ready = RESET;
					  if(HAL_SPI_Transmit_IT(H_SPI4, (uint8_t*)(spi4.Tx_Buffer), (spi4.Tx_MessageSize - spi4.Rx_MessageSize)) != HAL_OK){
						  Error_Handler();
					  }
					  while(SPI_Ready != SET){}
					  Transmitted_I2CReadCommand = SET;

				  }

				  if(Received_SPIMessage == RESET && Transmitted_SPIReadCommand == SET){

					  if(HAL_SPI_Receive_IT(H_SPI4, (uint8_t*)(spi4.Tx_Buffer), spi4.Rx_MessageSize) != HAL_OK){
						  Error_Handler();
					  }

				  }

				  if(Received_SPIMessage == SET){
					  Received_SPIMessage = RESET;
					  ControlCommunicationItem(spi4_element, Stop);

					  spi4.Data = spi4.Rx_Buffer[0];	//D7....D0
					  memset(spi4.Rx_Buffer, '\0', spi4.Rx_MessageSize);

					  UpdateControlMessage();
					  TransmitterMessageSetting(ControlMessage, ControlMessageSize);
				  }
			  }
		  }
		  if(spi5.Mission != Stop){

			  if(spi5.Mission == Transmit && SPI_Ready == SET){

				  SPI_Ready = RESET;
				  if(HAL_SPI_Transmit_IT(H_SPI5, (uint8_t*)(spi5.Tx_Buffer), spi5.Tx_MessageSize) != HAL_OK){
					  Error_Handler();
				  }
				  while(SPI_Ready != SET){}

				  ControlCommunicationItem(spi5_element, Stop);

			  }
			  else if(spi5.Mission == Receive){

				  if(Transmitted_SPIReadCommand == RESET && SPI_Ready == SET){

					  SPI_Ready = RESET;
					  if(HAL_SPI_Transmit_IT(H_SPI5, (uint8_t*)(spi5.Tx_Buffer), (spi5.Tx_MessageSize - spi5.Rx_MessageSize)) != HAL_OK){
						  Error_Handler();
					  }
					  while(SPI_Ready != SET){}
					  Transmitted_I2CReadCommand = SET;

				  }

				  if(Received_SPIMessage == RESET && Transmitted_SPIReadCommand == SET){

					  if(HAL_SPI_Receive_IT(H_SPI5, (uint8_t*)(spi5.Tx_Buffer), spi5.Rx_MessageSize) != HAL_OK){
						  Error_Handler();
					  }

				  }

				  if(Received_SPIMessage == SET){
					  Received_SPIMessage = RESET;
					  ControlCommunicationItem(spi5_element, Stop);

					  spi5.Data = spi5.Rx_Buffer[0];	//D7....D0
					  memset(spi5.Rx_Buffer, '\0', spi5.Rx_MessageSize);

					  UpdateControlMessage();
					  TransmitterMessageSetting(ControlMessage, ControlMessageSize);
				  }
			  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 168;
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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK){
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void){

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
  if (HAL_I2C_Init(&hi2c1) != HAL_OK){
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK){
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */
  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void){

  /* USER CODE BEGIN SPI2_Init 0 */
  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */
  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI4_Init(void){

  /* USER CODE BEGIN SPI4_Init 0 */
  /* USER CODE END SPI4_Init 0 */

  /* USER CODE BEGIN SPI4_Init 1 */
  /* USER CODE END SPI4_Init 1 */
  /* SPI4 parameter configuration*/
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi4) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN SPI4_Init 2 */

  /* USER CODE END SPI4_Init 2 */

}

/**
  * @brief SPI5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI5_Init(void){

  /* USER CODE BEGIN SPI5_Init 0 */
  /* USER CODE END SPI5_Init 0 */

  /* USER CODE BEGIN SPI5_Init 1 */
  /* USER CODE END SPI5_Init 1 */
  /* SPI5 parameter configuration*/
  hspi5.Instance = SPI5;
  hspi5.Init.Mode = SPI_MODE_MASTER;
  hspi5.Init.Direction = SPI_DIRECTION_2LINES;
  hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi5.Init.NSS = SPI_NSS_SOFT;
  hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi5.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi5) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN SPI5_Init 2 */
  /* USER CODE END SPI5_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pins : PF6 PF10 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC4 PC6 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PE11 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PH6 PH15 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11
                           PD12 PD13 PD14 PD15
                           PD2 PD3 PD4 PD5 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PG2 PG3 PG4 PG5
                           PG6 PG8 PG9 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PH13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : PI3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void SetVccVoltage(Voltage voltage){

	if(voltage == Voltage_3v3)
		HAL_GPIO_WritePin(Vcc_ControlPort, Vcc_ControlPin, GPIO_PIN_SET);
	else if(voltage == Voltage_5v)
		HAL_GPIO_WritePin(Vcc_ControlPort, Vcc_ControlPin, GPIO_PIN_RESET);

}

USBStatus CheckUSBStatus(void){

	GPIO_PinState USB_OTG;
	USB_OTG = HAL_GPIO_ReadPin(USB_OTG_VBUS_SensePort, USB_OTG_VBUS_SensePin);

	if(USB_OTG == GPIO_PIN_SET)
		return USB_OTG_Enable;
	else
		return USB_OTG_Disable;

}

void CommunicationInitialization(void){

	usb_otg.Element = usb_otg_element;
	usb_otg.Mission = Receive;
	usb_otg.Tx_MessageSize = ControlMessageSize;
	usb_otg.Rx_MessageSize = ControlMessageSize;
	if(CheckUSBStatus() == USB_OTG_Enable)
		usb_otg.State = ENABLE;
	else
		usb_otg.State = DISABLE;

	i2c.Element = i2c_element;
	i2c.Target_Address = I2C_EEPROM_ADDRESS;
	i2c.Tx_MessageSize = I2c_TxByteSize;
	i2c.Rx_MessageSize = I2c_RxByteSize;
	i2c.ChipSelectPin.GPIO_Port = I2C_ChipSelectPort;
	i2c.ChipSelectPin.GPIO_Init.Pin = I2C_ChipSelectPin;
	ControlCommunicationItem(i2c_element, Stop);

	spi2.Element = spi2_element;
	spi2.Tx_MessageSize = Spi2_TxByteSize;
	spi2.Rx_MessageSize = Spi2_RxByteSize;
	spi2.ChipSelectPin.GPIO_Port = SPI2_ChipSelectPort;
	spi2.ChipSelectPin.GPIO_Init.Pin = SPI2_ChipSelectPin;
	spi2.FastLatchPin.GPIO_Port = SPI2_FastLatchPort;
	spi2.FastLatchPin.GPIO_Init.Pin = SPI2_FastLatchPin;
	spi2.ResetPin.GPIO_Port = SPI2_ResetPort;
	spi2.ResetPin.GPIO_Init.Pin = SPI2_ResetPin;
	ControlCommunicationItem(spi2_element, Stop);

	spi4.Element = spi4_element;
	spi4.Tx_MessageSize = Spi4_TxByteSize;
	spi4.Rx_MessageSize = Spi4_RxByteSize;
	spi4.ChipSelectPin.GPIO_Port = SPI4_ChipSelectPort;
	spi4.ChipSelectPin.GPIO_Init.Pin = SPI4_ChipSelectPin;
	spi4.FastLatchPin.GPIO_Port = SPI4_FastLatchPort;
	spi4.FastLatchPin.GPIO_Init.Pin = SPI4_FastLatchPin;
	spi4.ResetPin.GPIO_Port = SPI4_ResetPort;
	spi4.ResetPin.GPIO_Init.Pin = SPI4_ResetPin;
	ControlCommunicationItem(spi4_element, Stop);

	spi5.Element = spi5_element;
	spi5.Tx_MessageSize = Spi5_TxByteSize;
	spi5.Rx_MessageSize = Spi5_RxByteSize;
	spi5.ChipSelectPin.GPIO_Port = SPI5_ChipSelectPort;
	spi5.ChipSelectPin.GPIO_Init.Pin = SPI5_ChipSelectPin;
	spi5.FastLatchPin.GPIO_Port = SPI5_FastLatchPort;
	spi5.FastLatchPin.GPIO_Init.Pin = SPI5_FastLatchPin;
	spi5.ResetPin.GPIO_Port = SPI5_ResetPort;
	spi5.ResetPin.GPIO_Init.Pin = SPI5_ResetPin;
	ControlCommunicationItem(spi5_element, Stop);

}

void ControlCommunicationItem(CommunicationElement communicationElement, CommunicationMission mission){

	if(communicationElement == i2c_element){
		if(mission == Transmit && i2c.Mission != Transmit)
			i2c.Mission = Transmit;
		else
			i2c.Mission = mission;
	}
	else if(communicationElement == spi2_element){
		if(mission == Reset){
			HAL_GPIO_WritePin(spi2.ResetPin.GPIO_Port, spi2.ResetPin.GPIO_Init.Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(spi2.ResetPin.GPIO_Port, spi2.ResetPin.GPIO_Init.Pin, GPIO_PIN_SET);

			spi2.Mission = Stop;
			HAL_GPIO_WritePin(spi2.ChipSelectPin.GPIO_Port, spi2.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);
		}
		else{
			if(mission != Stop && spi2.Mission == Stop){
				spi2.Mission = mission;
				HAL_GPIO_WritePin(spi2.ChipSelectPin.GPIO_Port, spi2.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_RESET);
			}
			else if(mission == Stop && spi2.Mission != Stop){
				spi2.Mission = Stop;
				HAL_GPIO_WritePin(spi2.ChipSelectPin.GPIO_Port, spi2.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);
			}
		}
	}
	else if(communicationElement == spi4_element){
		if(mission == Reset){
			HAL_GPIO_WritePin(spi4.ResetPin.GPIO_Port, spi4.ResetPin.GPIO_Init.Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(spi4.ResetPin.GPIO_Port, spi4.ResetPin.GPIO_Init.Pin, GPIO_PIN_SET);

			spi4.Mission = Stop;
			HAL_GPIO_WritePin(spi4.ChipSelectPin.GPIO_Port, spi4.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);
		}
		else{
			if(mission != Stop && spi4.Mission == Stop){
				spi4.Mission = mission;
				HAL_GPIO_WritePin(spi4.ChipSelectPin.GPIO_Port, spi4.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_RESET);
			}
			else if(mission == Stop && spi4.Mission != Stop){
				spi4.Mission = Stop;
				HAL_GPIO_WritePin(spi4.ChipSelectPin.GPIO_Port, spi4.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);
			}
		}
	}
	else if(communicationElement == spi5_element){
		if(mission == Reset){
			HAL_GPIO_WritePin(spi5.ResetPin.GPIO_Port, spi5.ResetPin.GPIO_Init.Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(spi5.ResetPin.GPIO_Port, spi5.ResetPin.GPIO_Init.Pin, GPIO_PIN_SET);

			spi5.Mission = Stop;
			HAL_GPIO_WritePin(spi5.ChipSelectPin.GPIO_Port, spi5.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);
		}
		else{
			if(mission != Stop && spi5.Mission == Stop){
				spi5.Mission = mission;
				HAL_GPIO_WritePin(spi5.ChipSelectPin.GPIO_Port, spi5.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_RESET);
			}
			else if(mission == Stop && spi5.Mission != Stop){
				spi5.Mission = Stop;
				HAL_GPIO_WritePin(spi5.ChipSelectPin.GPIO_Port, spi5.ChipSelectPin.GPIO_Init.Pin, GPIO_PIN_SET);
			}
		}
	}


}

void DiscretePinInitialization(void){

	uint8_t Pin_Numbers[NumberOfDiscretePin] = {15, 14, 13, 12, 11, 10, 9, 8, 6, 6, 5, 4, 3, 2};

	/*
	 * GPIOA = 0			GPIOD = 3			GPIOG = 6
	 * GPIOB = 1			GPIOE = 4			GPIOH = 7
	 * GPIOC = 2			GPIOF = 5			GPIOI = 8
	 */

	uint8_t Pin_Ports[NumberOfDiscretePin] = {3, 3, 3, 3, 3, 3, 3, 3, 2, 6, 6, 6, 6, 6};

	GPIO_TypeDef* GPIO_Ports[9] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI};
	uint16_t GPIO_Pins[16] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8,
							  GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

	for(uint8_t i=0; i<NumberOfDiscretePin; i++){
		DiscretePins[i].GPIO_Port = GPIO_Ports[Pin_Ports[i]];
		DiscretePins[i].GPIO_Init.Pin = GPIO_Pins[Pin_Numbers[i]];
		DiscretePins[i].State = GPIO_PIN_RESET;
		DiscretePins[i].GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	}

}

void ControlDiscretePin(void){

	if(DiscretePins[SelectedDiscretePin].State == SelectedDiscretePinState)
		return;

	DiscretePins[SelectedDiscretePin].State = SelectedDiscretePinState;
	HAL_GPIO_WritePin(DiscretePins[SelectedDiscretePin].GPIO_Port, DiscretePins[SelectedDiscretePin].GPIO_Init.Pin, DiscretePins[SelectedDiscretePin].State);

}

void AnalyzeControlMessage(void){

	SelectedCommunicationItem.Register_Address = 0x00;
	SelectedCommunicationItem.Data = 0x00;

	if(ControlMessage.CMD_GPIO_Bits.BoardOperation == 0){
		SelectedBoardOperation = Control_Discrete;

		if(ControlMessage.CMD_GPIO_Bits.PinStatus == 0)
			SelectedDiscretePinState = GPIO_PIN_RESET;
		else
			SelectedDiscretePinState = GPIO_PIN_SET;

		SelectedDiscretePin = ControlMessage.CMD_GPIO_Bits.PinNumber;
	}
	else if(ControlMessage.CMD_GPIO_Bits.BoardOperation == 1){
		SelectedBoardOperation = Control_SPI;

		if(ControlMessage.CMD_SPI_Bits.Port == 0)
			SelectedCommunicationItem.Element = spi2_element;
		else if(ControlMessage.CMD_SPI_Bits.Port == 1)
			SelectedCommunicationItem.Element = spi4_element;
		else if(ControlMessage.CMD_SPI_Bits.Port == 2)
			SelectedCommunicationItem.Element = spi5_element;
		else
			return;

		if(ControlMessage.CMD_SPI_Bits.Mission == 0)
			SelectedCommunicationItem.Mission = Transmit;
		if(ControlMessage.CMD_SPI_Bits.Mission == 1)
			SelectedCommunicationItem.Mission = Receive;
		if(ControlMessage.CMD_SPI_Bits.Mission == 2)
			SelectedCommunicationItem.Mission = Reset;
		else
			return;

		if(SelectedCommunicationItem.Mission != Reset){
			SelectedCommunicationItem.Register_Address = ControlMessage.CMD_SPI_Bits.Register_Address;
			if(SelectedCommunicationItem.Mission == Transmit)
				SelectedCommunicationItem.Data = ControlMessage.CMD_SPI_Bits.Data;	//D7....D0
		}
	}
	else if(ControlMessage.CMD_GPIO_Bits.BoardOperation == 2){
		SelectedBoardOperation = Control_I2C;
		SelectedCommunicationItem.Element = i2c_element;

		if(ControlMessage.CMD_I2C_Bits.Mission == 0)
			SelectedCommunicationItem.Mission = Transmit;
		else
			SelectedCommunicationItem.Mission = Receive;

		SelectedCommunicationItem.Register_Address = ControlMessage.CMD_I2C_Bits.Register_Address;

		if(SelectedCommunicationItem.Mission == Transmit)
			SelectedCommunicationItem.Data = ControlMessage.CMD_I2C_Bits.Data;	//D7....D0

	}
	else if(ControlMessage.CMD_GPIO_Bits.BoardOperation == 3){
		if(ControlMessage.CMD_Handshake_Bits.Handshake_Code == PC_Handshake_Code){
			SelectedBoardOperation = Handshake;
		}
	}
}

void ConfigurateCommunication(void){

	if(SelectedCommunicationItem.Element == i2c.Element){
		ControlCommunicationItem(i2c.Element, SelectedCommunicationItem.Mission);

		i2c.Register_Address = SelectedCommunicationItem.Register_Address;
		if(i2c.Mission == Transmit)
			i2c.Data = SelectedCommunicationItem.Data;	//D7....D0

		CreateProtocolCommandMessage(&i2c);
	}
	else if(SelectedCommunicationItem.Element == spi2.Element){
		ControlCommunicationItem(spi2.Element, SelectedCommunicationItem.Mission);

		spi2.Register_Address = SelectedCommunicationItem.Register_Address;
		if(spi2.Mission == Transmit)
			spi2.Data = SelectedCommunicationItem.Data;	//D7....D0

		CreateProtocolCommandMessage(&spi2);
	}
	else if(SelectedCommunicationItem.Element == spi4.Element){
		ControlCommunicationItem(spi4.Element, SelectedCommunicationItem.Mission);

		spi4.Register_Address = SelectedCommunicationItem.Register_Address;
		if(spi4.Mission == Transmit)
			spi4.Data = SelectedCommunicationItem.Data;	//D7....D0

		CreateProtocolCommandMessage(&spi4);
	}
	else if(SelectedCommunicationItem.Element == spi5.Element){
		ControlCommunicationItem(spi5.Element, SelectedCommunicationItem.Mission);

		spi5.Register_Address = SelectedCommunicationItem.Register_Address;
		if(spi5.Mission == Transmit)
			spi5.Data = SelectedCommunicationItem.Data;	//D7....D0

		CreateProtocolCommandMessage(&spi5);
	}
}

void CreateProtocolCommandMessage(Communication_Item* protocol){

	memset(protocol->Tx_Buffer, '\0', protocol->Tx_MessageSize);

	if(protocol->Element == i2c_element){
		I2C_CMD_Message_Union	I2cCommand;

		if(protocol->Mission == Transmit){
			I2cCommand.I2C_Write_CMD_Bits.RegisterAddress = protocol->Register_Address;
			I2cCommand.I2C_Write_CMD_Bits.Data = protocol->Data;

			protocol->Tx_Buffer[0] = (I2cCommand.all >> 16) & 0xFF;
			protocol->Tx_Buffer[1] = (I2cCommand.all >> 8) & 0xFF;
			protocol->Tx_Buffer[2] = I2cCommand.all & 0xFF;
		}
		else if(protocol->Mission == Receive){
			Transmitted_I2CReadCommand = RESET;
			I2cCommand.I2C_Read_CMD_Bits.RegisterAddress = protocol->Register_Address;

			protocol->Tx_Buffer[0] = (I2cCommand.all >> 8) & 0xFF;
			protocol->Tx_Buffer[1] = I2cCommand.all & 0xFF;
		}
	}
	else if(protocol->Element != usb_otg_element){
		SPI_CMD_Message_Union	SpiCommand;

		if(protocol->Mission == Transmit){
			SpiCommand.SPI_Write_CMD_Bits.WR_Bit = WriteBit;
			SpiCommand.SPI_Write_CMD_Bits.RegisterAddress = protocol->Register_Address;
			SpiCommand.SPI_Write_CMD_Bits.Data = protocol->Data;

			protocol->Tx_Buffer[0] = (SpiCommand.all >> 16) & 0xFF;
			protocol->Tx_Buffer[1] = (SpiCommand.all >> 8) & 0xFF;
			protocol->Tx_Buffer[2] = SpiCommand.all & 0xFF;
		}
		else if(protocol->Mission == Receive){
			Transmitted_SPIReadCommand = RESET;
			SpiCommand.SPI_Read_CMD_Bits.WR_Bit = ReadBit;
			SpiCommand.SPI_Read_CMD_Bits.RegisterAddress = protocol->Register_Address;

			protocol->Tx_Buffer[0] = (SpiCommand.all >> 8) & 0xFF;
			protocol->Tx_Buffer[1] = SpiCommand.all & 0xFF;
		}
	}
}

void UpdateControlMessage(void){

	int parityBitControl = 0x00;

	if(SelectedBoardOperation == Control_SPI){
		ControlMessage.CMD_SPI_Bits.BoardOperation = 1;

		if(SelectedCommunicationItem.Element == spi2_element){
			ControlMessage.CMD_SPI_Bits.Port = 0;
			ControlMessage.CMD_SPI_Bits.Register_Address = spi2.Register_Address;
			ControlMessage.CMD_SPI_Bits.Data = spi2.Data;
		}
		else if(SelectedCommunicationItem.Element == spi4_element){
			ControlMessage.CMD_SPI_Bits.Port = 1;
			ControlMessage.CMD_SPI_Bits.Register_Address = spi4.Register_Address;
			ControlMessage.CMD_SPI_Bits.Data = spi4.Data;
		}
		else if(SelectedCommunicationItem.Element == spi5_element){
			ControlMessage.CMD_SPI_Bits.Port = 2;
			ControlMessage.CMD_SPI_Bits.Register_Address = spi5.Register_Address;
			ControlMessage.CMD_SPI_Bits.Data = spi5.Data;
		}
	}
	else if(SelectedBoardOperation == Control_I2C){
		ControlMessage.CMD_I2C_Bits.BoardOperation = 2;

		if(SelectedCommunicationItem.Element == i2c_element){
			ControlMessage.CMD_I2C_Bits.Register_Address = i2c.Register_Address;
			ControlMessage.CMD_I2C_Bits.Data = i2c.Data;
		}
	}
	else if(SelectedBoardOperation == Handshake){
		ControlMessage.CMD_Handshake_Bits.BoardOperation = 3;
		ControlMessage.CMD_Handshake_Bits.Handshake_Code = Board_Handshake_Code;
	}
	else
		return;

	for(int i=0; i<(ControlMessageSize*8); i++)
		parityBitControl += ControlMessage.all & (0x01 << i);

	if(parityBitControl % 2 == 0){
		if(SelectedBoardOperation == Control_SPI)
			ControlMessage.CMD_SPI_Bits.Parity = 0;
		else if(SelectedBoardOperation == Control_I2C)
			ControlMessage.CMD_I2C_Bits.Parity = 0;
		else if(SelectedBoardOperation == Handshake)
			ControlMessage.CMD_Handshake_Bits.Parity = 0;
	}
	else{
		if(SelectedBoardOperation == Control_SPI)
			ControlMessage.CMD_SPI_Bits.Parity = 1;
		else if(SelectedBoardOperation == Control_I2C)
			ControlMessage.CMD_I2C_Bits.Parity = 1;
		else if(SelectedBoardOperation == Handshake)
			ControlMessage.CMD_Handshake_Bits.Parity = 1;
	}
}

void TransmitterMessageSetting(Control_Message_Union message, uint8_t length){

	memset(usb_otg.Tx_Buffer, '\0', usb_otg.Tx_MessageSize);

	if(usb_otg.State == ENABLE){
		usb_otg.Mission = Transmit;

		for(int i = 0; i <length; i++)
			usb_otg.Tx_Buffer[i] = (message.all >> (8*i)) & 0xFF;

		usb_otg.Tx_MessageSize = length;
	}
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2cHandle){
	I2C_Ready = SET;
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2cHandle){
	Received_I2CMessage = SET;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
	SPI_Ready = SET;
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	if(SelectedCommunicationItem.Element == spi2.Element && hspi->Instance == hspi2.Instance)
		Received_SPIMessage = SET;
	else if(SelectedCommunicationItem.Element == spi4.Element && hspi->Instance == hspi4.Instance)
		Received_SPIMessage = SET;
	else if(SelectedCommunicationItem.Element == spi5.Element && hspi->Instance == hspi5.Instance)
		Received_SPIMessage = SET;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1){}
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
