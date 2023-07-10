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
 TIM_HandleTypeDef htim1;
 TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

void APB1_84MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime);
void APB2_168MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime);
void APB1_25MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime);
void APB2_25MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime);
void APB1_25MHz_InstantTimeDelay(TIM_HandleTypeDef *TimerHandle, float DelayTime);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

ITStatus	StartProcedure = RESET;
float		IndexTimeCounter = 20.00;

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(HAL_GPIO_ReadPin(Button_Port, Button_Pin) == GPIO_PIN_SET){

		  APB1_25MHz_InstantTimeDelay(H_TIM2, 20000);
		  if(HAL_GPIO_ReadPin(Button_Port, Button_Pin) == GPIO_PIN_SET){

			  while(HAL_GPIO_ReadPin(Button_Port, Button_Pin) == GPIO_PIN_SET);
			  HAL_GPIO_TogglePin(MCU_Led_Port, MCU_Led_Pin);

			  StartProcedure = !StartProcedure;
			  if(StartProcedure == SET){
				  HAL_TIM_Base_Start(H_TIM1);
				  IndexTimeCounter = IndexTimeCounter + 5.0;
			  }
			  else{
				  HAL_TIM_Base_Stop(H_TIM1);
			  }
		  }
	  }

	  if(StartProcedure == SET){
		  HAL_GPIO_TogglePin(SquareWave_Port, SquareWave_Pin);
		  APB2_25MHz_TIM(H_TIM2, IndexTimeCounter);
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

  /* Initializes the CPU, AHB and APB buses clocks*/
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK){
    Error_Handler();
  }
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void){

  /* USER CODE BEGIN TIM2_Init 0 */
  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */
  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xFFFFFFFF-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK){
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK){
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB7 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void APB1_84MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime){

	uint32_t Counter = 0;
	DelayTime = DelayTime - APB1_84MHz_InitialTimer_usValue;
	if((int)DelayTime)
		Counter = APB1_84MHz_InitialTimer_Counter + ((((uint16_t)(DelayTime/APB1_84MHz_IncrementTimer_usValue))-1)*APB1_84MHz_IncrementTimer_Counter);
	else
		Counter = APB1_84MHz_InitialTimer_Counter;

	__HAL_TIM_SET_COUNTER(TimerHandle, 0);
	while(__HAL_TIM_GET_COUNTER(TimerHandle) > Counter);

}

void APB2_168MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime){

	uint32_t Counter = 0;
	DelayTime = DelayTime - APB2_168MHz_InitialTimer_usValue;
	if((int)DelayTime)
		Counter = APB2_168MHz_InitialTimer_Counter + ((((uint16_t)(DelayTime/APB2_168MHz_IncrementTimer_usValue))-1)*APB2_168MHz_IncrementTimer_Counter);
	else
		Counter = APB2_168MHz_InitialTimer_Counter;

	__HAL_TIM_SET_COUNTER(TimerHandle, 0);
	while(__HAL_TIM_GET_COUNTER(TimerHandle) > Counter);

}

void APB1_25MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime){

	uint32_t Counter = 0;
	DelayTime = DelayTime - APB1_25MHz_InitialTimer_usValue;
	if((int)DelayTime)
		Counter = APB1_25MHz_InitialTimer_Counter + ((((uint16_t)(DelayTime/APB1_25MHz_IncrementTimer_usValue))-1)*APB1_25MHz_IncrementTimer_Counter);
	else
		Counter = APB1_25MHz_InitialTimer_Counter;

	__HAL_TIM_SET_COUNTER(TimerHandle, 0);
	while(__HAL_TIM_GET_COUNTER(TimerHandle) > Counter);

}

void APB2_25MHz_TIM(TIM_HandleTypeDef *TimerHandle, float DelayTime){

	uint32_t Counter = 0;
	DelayTime = DelayTime - APB2_25MHz_InitialTimer_usValue;
	if((int)DelayTime)
		Counter = APB2_25MHz_InitialTimer_Counter + ((((uint16_t)(DelayTime/APB2_25MHz_IncrementTimer_usValue))-1)*APB2_25MHz_IncrementTimer_Counter);
	else
		Counter = APB2_25MHz_InitialTimer_Counter;

	__HAL_TIM_SET_COUNTER(TimerHandle, 0);
	while(__HAL_TIM_GET_COUNTER(TimerHandle) > Counter);

}

void APB1_25MHz_InstantTimeDelay(TIM_HandleTypeDef *TimerHandle, float DelayTime){

	HAL_TIM_Base_Start(TimerHandle);

	uint32_t Counter = 0;
	DelayTime = DelayTime - APB1_25MHz_InitialTimer_usValue;
	if((int)DelayTime)
		Counter = APB1_25MHz_InitialTimer_Counter + ((((uint16_t)(DelayTime/APB1_25MHz_IncrementTimer_usValue))-1)*APB1_25MHz_IncrementTimer_Counter);
	else
		Counter = APB1_25MHz_InitialTimer_Counter;

	__HAL_TIM_SET_COUNTER(TimerHandle, 0);
	while(__HAL_TIM_GET_COUNTER(TimerHandle) > Counter);

	HAL_TIM_Base_Stop(TimerHandle);

}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void){
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
void assert_failed(uint8_t *file, uint32_t line){
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
