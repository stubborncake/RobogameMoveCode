/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "connectivity.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */
uint8_t res=0;
uint8_t resBuffPtr=0;
uint8_t receiveBuff[receiveBuffSize]={0};

int test=0;

void USART2_IdleCallback__(uint8_t *receiveBuff,uint8_t resBuffPtr)
{
	while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC) != SET);	
	HAL_UART_Transmit(&huart2,receiveBuff,resBuffPtr,0x00ff);	
	return;
	message_t newmsg; 
	newmsg.command=receiveBuff[0];
	newmsg.argCount=receiveBuff[1];
	newmsg.argList=&receiveBuff[2];	
	receiveCmd(newmsg);	
}



/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt.
  */
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */

  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */

  /* USER CODE END TIM6_IRQn 1 */
}

/* USER CODE BEGIN 1 */

//基本定时器中断，1ms一次
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{	
	if(htim==&htim6) // 判断是哪一个定时器
	{
		static int time;
		time++;		
		static int pwm1=0;
		static int pwm2=0;
		static int pwm3=0;
		static int pwm4=0;
		static float enc1=0,enc2=0,enc3=0,enc4=0;
		static float testnumber[2];
		static int enc;
  if(htim->Instance == htim6.Instance)
  {
		//每50ms进入一次PID计算中断
		if(time % 50 == 0)
		{		
			//单环速度PID
			if(DoubleBegin==0)
			{	
			enc1=Read_Encoder(1);
			if(enc1<0) enc1=-enc1;
			pwm1=PID_calc(&motor1_speed,enc1,target1);
			if(pwm1<0) pwm1=0;
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_1,pwm1);		
									
			enc2=Read_Encoder(2);
			if(enc2<0) enc2=-enc2;
			pwm2=PID_calc(&motor2_speed,enc2,target2);
			if(pwm2<0) pwm2=0;
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_2,pwm2);	
						
			enc3=Read_Encoder(3);
			if(enc3<0) enc3=-enc3;
			pwm3=PID_calc(&motor3_speed,enc3,target3);
			if(pwm3<0) pwm3=0;
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,pwm3);	
			
			enc4=Read_Encoder(8);
			if(enc4<0) enc4=-enc4;
			pwm4=PID_calc(&motor4_speed,enc4,target4);
			if(pwm4<0) pwm4=0;
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,pwm4);	
			
			//这里是PID曲线调参
			static uint8_t tempData[12] = {0,0,0,0,0,0,0,0,0,0,0x80,0x7F};
			testnumber[0]=enc4;
			testnumber[1]=100.0;
			memcpy(tempData, (uint8_t *)&testnumber, sizeof(testnumber));
			HAL_UART_Transmit(&huart3,(uint8_t *)tempData,12,0x000A);
			}
			//双环位置PID
			else if(DoubleBegin==1)
			{	
			if(Again==1)
			{
				enc1=enc2=enc3=enc4=0;
				Again=0;
			}
			
			enc=Read_Encoder(1);
			if(enc<0) enc=-enc;
      enc1 = enc1 + enc;
			pwm1 = PID_calc(&motor1_position,enc1,target1);//位置环
			pwm1 = PID_calc(&motor1_speed,enc,pwm1);//速度环	
			if(pwm1<0) pwm1=0;
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_1,pwm1);

			enc=Read_Encoder(2);
			if(enc<0) enc=-enc;
			enc2 = enc2 + enc;
			pwm2 = PID_calc(&motor2_position,enc2,target2);//位置环
			pwm2 = PID_calc(&motor2_speed,Read_Encoder(2),pwm2);//速度环	
			if(pwm2<0) pwm2=0;
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_2,pwm2);
			
			enc=Read_Encoder(3);
			if(enc<0) enc=-enc;
			enc3 = enc3 + enc;
			pwm3 = PID_calc(&motor3_position,enc3,target3);//位置环
			pwm3 = PID_calc(&motor3_speed,enc,pwm3);//速度环	
			if(pwm3<0) pwm3=0;
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,pwm3);
			
			enc=Read_Encoder(8);
			if(enc<0) enc=-enc;
			enc4 = enc4 + enc;
			pwm4 = PID_calc(&motor4_position,enc4,target4);//位置环
			pwm4 = PID_calc(&motor4_speed,Read_Encoder(8),pwm4);//速度环	
			if(pwm4<0) pwm4=0;
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,pwm4);			
			}			
		}		
		if(time >= 1000) time = 0;							
  }
	}
}
	
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
