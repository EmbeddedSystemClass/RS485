/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f0xx_hal.h"

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
void TIMERExpiredISR(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LOCK_1_Pin GPIO_PIN_4
#define LOCK_1_GPIO_Port GPIOA
#define FB_1_Pin GPIO_PIN_5
#define FB_1_GPIO_Port GPIOA
#define LOCK_2_Pin GPIO_PIN_6
#define LOCK_2_GPIO_Port GPIOA
#define FB_2_Pin GPIO_PIN_7
#define FB_2_GPIO_Port GPIOA
#define LOCK_3_Pin GPIO_PIN_0
#define LOCK_3_GPIO_Port GPIOB
#define FB_3_Pin GPIO_PIN_1
#define FB_3_GPIO_Port GPIOB
#define LOCK_4_Pin GPIO_PIN_2
#define LOCK_4_GPIO_Port GPIOB
#define FB_4_Pin GPIO_PIN_10
#define FB_4_GPIO_Port GPIOB
#define LOCK_5_Pin GPIO_PIN_12
#define LOCK_5_GPIO_Port GPIOB
#define FB_5_Pin GPIO_PIN_13
#define FB_5_GPIO_Port GPIOB
#define Y2_Pin GPIO_PIN_11
#define Y2_GPIO_Port GPIOA
#define Y1_Pin GPIO_PIN_12
#define Y1_GPIO_Port GPIOA
#define X4_Pin GPIO_PIN_4
#define X4_GPIO_Port GPIOB
#define X3_Pin GPIO_PIN_5
#define X3_GPIO_Port GPIOB
#define X2_Pin GPIO_PIN_6
#define X2_GPIO_Port GPIOB
#define X1_Pin GPIO_PIN_7
#define X1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
