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

#define Button_Port				GPIOC
#define Button_Pin				GPIO_PIN_13
#define SquareWave_Port			GPIOB
#define SquareWave_Pin			GPIO_PIN_8
#define MCU_Led_Port			GPIOB
#define MCU_Led_Pin				GPIO_PIN_7

#define H_TIM1					&htim1
#define H_TIM2					&htim2

/* Clock Frequency = 168MHz - APB1 Timer Clock = 84MHz - Prescaler = 1-1 */
#define APB1_84MHz_InitialTimer_usValue			(float)2.4393
#define APB1_84MHz_IncrementTimer_usValue		(float)0.4643
#define APB1_84MHz_InitialTimer_Counter			(uint16_t)2
#define APB1_84MHz_IncrementTimer_Counter		(uint16_t)12

/* Clock Frequency = 168MHz - APB2 Timer Clock = 168MHz - Prescaler = 1-1 */
#define APB2_168MHz_InitialTimer_usValue		(float)2.4393
#define APB2_168MHz_IncrementTimer_usValue		(float)0.3480
#define APB2_168MHz_InitialTimer_Counter		(uint16_t)4
#define APB2_168MHz_IncrementTimer_Counter		(uint16_t)18

/* Clock Frequency = 50MHz - APB1 Timer Clock = 25MHz - Prescaler = 1-1 */
#define APB1_25MHz_InitialTimer_usValue			(float)6.8900
#define APB1_25MHz_IncrementTimer_usValue		(float)1.5600
#define APB1_25MHz_InitialTimer_Counter			(uint16_t)2
#define APB1_25MHz_IncrementTimer_Counter		(uint16_t)12

/* Clock Frequency = 50MHz - APB2 Timer Clock = 25MHz - Prescaler = 1-1 */
#define APB2_25MHz_InitialTimer_usValue			(float)6.8900
#define APB2_25MHz_IncrementTimer_usValue		(float)1.5600
#define APB2_25MHz_InitialTimer_Counter			(uint16_t)2
#define APB2_25MHz_IncrementTimer_Counter		(uint16_t)12

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
