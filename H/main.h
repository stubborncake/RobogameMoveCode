/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */


extern int target1,target2,target3,target4;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

extern int DoubleBegin;//�ж��Ƿ����΢���Ƕ�˫����ȫ�ֱ�����0�ǣ�1��
extern int Again;//�ж��Ƿ���һ�ν���˫�����飬��ζ���Ϊ�˲���˫�����ȶ��ԵĴ���

extern int test;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define m11_Pin GPIO_PIN_6
#define m11_GPIO_Port GPIOF
#define m12_Pin GPIO_PIN_7
#define m12_GPIO_Port GPIOF
#define m21_Pin GPIO_PIN_8
#define m21_GPIO_Port GPIOF
#define m22_Pin GPIO_PIN_9
#define m22_GPIO_Port GPIOF
#define m31_Pin GPIO_PIN_0
#define m31_GPIO_Port GPIOC
#define m32_Pin GPIO_PIN_1
#define m32_GPIO_Port GPIOC
#define m41_Pin GPIO_PIN_2
#define m41_GPIO_Port GPIOC
#define m42_Pin GPIO_PIN_3
#define m42_GPIO_Port GPIOC
#define SENSOR0_Pin GPIO_PIN_1
#define SENSOR0_GPIO_Port GPIOD
#define SENSOR1_Pin GPIO_PIN_2
#define SENSOR1_GPIO_Port GPIOD
#define SENSOR2_Pin GPIO_PIN_3
#define SENSOR2_GPIO_Port GPIOD
#define SENSOR3_Pin GPIO_PIN_4
#define SENSOR3_GPIO_Port GPIOD
#define SENSOR4_Pin GPIO_PIN_5
#define SENSOR4_GPIO_Port GPIOD
#define SELECTOR0_Pin GPIO_PIN_6
#define SELECTOR0_GPIO_Port GPIOD
#define SELECTOR1_Pin GPIO_PIN_7
#define SELECTOR1_GPIO_Port GPIOD
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
