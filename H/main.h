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
typedef enum{
  goFront=0,
  goRight=1,
  goBack=2,
  goLeft=3,
}direction_t;

typedef enum{
  errorCmd=0x00,  //Ԥ����������ָ�����ͨ�Ź����е�����
  moveCmd=0x01,  //���ٻ���ٵ�ָ�Ԥ��һ���ٶ�
  rotateCmd=0x02, //ԭ����תָ�Ĭ�ϴ�ʱ�Ǿ�ֹ״̬
  trimCmd=0x03, //ǰ�������е����Ƕȵ�ָ�����ԭ����ת
  stopCmd=0x04, //��ɲָ��
  detectCodeCmd=0x05, //���ǰ��������ָ���c8t6->respberry
  pushArmCmd=0x06,  //��������˶�ָ��
  detectCodeAns=0x07, //������ļ�ⷴ��ָ���respberry->c8t6
  reservedCmd=0x010,  //Ԥ��ָ��
  testCmd=0x011,  //ǰ�ڲ���ָ�ͨ��Э���Ƿ��������
}command_t;

typedef struct{
  command_t command;
  uint8_t argCount;
  uint8_t * argList;
  uint32_t timeout;
}message_t;

typedef enum{
  sensorDirFront=0x00,
  sensorDirRight=0x01,
  sensorDirBack=0x02,
  sensorDirLeft=0x03,
}sensorDir_t;




typedef uint8_t status_t;

/*ƽ���ڵ㣬��·���е�����ڵ����ͣ��ĸ�����������ֵ���������*/
typedef enum{
  nowhere=0,
  frontOnly=1,
  backOnly=2,
  rightOnly=3,
  leftOnly=4,
  straightLine=5,
  horizontalLine=6,
  rightTurn=7,
  leftTurn=8,
  rightFork=9,
  leftFork=10,
  T_crossing=11,
  crossing=12,
}plainNode_t;

/*�ؼ��ڵ㣬��Ѳ��ģ��Ķ�λ�ڵ�*/
typedef enum{
  startLine=0,
  upperRightTurning=1,
  lowerRightTurning=2,
  baseNode=3,
  crossroadLeft=4,
  crossroadMid=5,
  crossroadRight=6,
  curlingDepositEasy=7,
  curlingDepositHard=8, 
}keyNode_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */


extern int target1,target2,target3,target4;//�ֱ�����ĸ����ӵ�Ŀ���ٶ�

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

extern int DoubleBegin;//�ж��Ƿ����΢���Ƕ�˫����ȫ�ֱ�����0�ǣ�1��
extern int Again;//�ж��Ƿ���һ�ν���˫�����飬��ζ���Ϊ�˲���˫�����ȶ��ԵĴ���

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
