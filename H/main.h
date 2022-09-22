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
  errorCmd=0x00,  //预设的意外错误指令，或者通信过程中的噪声
  moveCmd=0x01,  //加速或减速的指令，预设一个速度
  rotateCmd=0x02, //原地旋转指令，默认此时是静止状态
  trimCmd=0x03, //前进过程中调整角度的指令，不是原地旋转
  stopCmd=0x04, //急刹指令
  detectCodeCmd=0x05, //检测前方条形码指令，由c8t6->respberry
  pushArmCmd=0x06,  //步进电机运动指令
  detectCodeAns=0x07, //条形码的检测反馈指令，由respberry->c8t6
  reservedCmd=0x010,  //预留指令
  testCmd=0x011,  //前期测试指令，通信协议是否可以运行
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

/*平凡节点，即路程中的任意节点类型，四个传感器返回值的排列组合*/
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

/*关键节点，即巡线模块的定位节点*/
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


extern int target1,target2,target3,target4;//分别代表四个轮子的目标速度

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;

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
