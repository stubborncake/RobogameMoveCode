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
#include "pid.h"
#include "motor.h"
#include "string.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern pid_type_def motor1_speed;
extern pid_type_def motor1_position;
extern pid_type_def motor2_speed;
extern pid_type_def motor2_position;
extern pid_type_def motor3_speed;
extern pid_type_def motor3_position;
extern pid_type_def motor4_speed;
extern pid_type_def motor4_position;

extern int target1,target2,target3,target4;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

extern float Kp_position1,Ki_position1,Kd_position1;
extern float Kp_position2,Ki_position2,Kd_position2;
extern float Kp_position3,Ki_position3,Kd_position3;
extern float Kp_position4,Ki_position4,Kd_position4;
extern float Kp_speed1,Ki_speed1,Kd_speed1;
extern float Kp_speed2,Ki_speed2,Kd_speed2;
extern float Kp_speed3,Ki_speed3,Kd_speed3;
extern float Kp_speed4,Ki_speed4,Kd_speed4;

extern int DoubleBegin;//判断是否进入微调角度双环的全局变量，0非，1是
extern int Again;//判断是否又一次进行双环测验，这段都是为了测试双环的稳定性的代码

extern uint8_t res;
extern uint8_t resBuffPtr;
static const uint8_t receiveBuffSize=100;
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
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
