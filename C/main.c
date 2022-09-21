/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/*pid������ʼ��--------------------*/
pid_type_def motor1_speed,motor1_position;
pid_type_def motor2_speed,motor2_position;
pid_type_def motor3_speed,motor3_position;
pid_type_def motor4_speed,motor4_position;

int target1,target2,target3,target4;
int DoubleBegin,Again;

float Kp_position1,Ki_position1,Kd_position1;
float Kp_position2,Ki_position2,Kd_position2;
float Kp_position3,Ki_position3,Kd_position3;
float Kp_position4,Ki_position4,Kd_position4;
float Kp_speed1,Ki_speed1,Kd_speed1;
float Kp_speed2,Ki_speed2,Kd_speed2;
float Kp_speed3,Ki_speed3,Kd_speed3;
float Kp_speed4,Ki_speed4,Kd_speed4;

/* USER CODE END PTD */

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
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_TIM8_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	//PWM���ʹ��
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	//�ٶ�ʽPID������ֵ
	Kp_speed1=Kp_speed2=Kp_speed3=40;
	Ki_speed1=Ki_speed2=Ki_speed3=0.25;
	Kd_speed1=Kd_speed2=Kd_speed3=Kd_speed4=0;
	Kp_speed4=40;
	Ki_speed4=0.25;
	//λ��ʽPID������ֵ	
	Kp_position1=20;Ki_position1=0;Kd_position1=0;
	Kp_position2=20;Ki_position2=0;Kd_position2=0;
	Kp_position3=20;Ki_position3=0;Kd_position3=0;
	Kp_position4=20;Ki_position4=0;Kd_position4=0;	
	//PID��ʼ��	
	PID_init(&motor1_speed,2,3600,2000,Kp_speed1,Ki_speed1,Kd_speed1);
	PID_init(&motor2_speed,2,3600,2000,Kp_speed2,Ki_speed2,Kd_speed2);
	PID_init(&motor3_speed,2,3600,2000,Kp_speed3,Ki_speed3,Kd_speed3);
	PID_init(&motor4_speed,2,3600,2000,Kp_speed4,Ki_speed4,Kd_speed4);	
	PID_init(&motor1_position,1,3600,2000,Kp_position1,Ki_position1,Kd_position1);
	PID_init(&motor2_position,1,3600,2000,Kp_position2,Ki_position2,Kd_position2);
	PID_init(&motor3_position,1,3600,2000,Kp_position3,Ki_position3,Kd_position3);
	PID_init(&motor4_position,1,3600,2000,Kp_position4,Ki_position4,Kd_position4);
	//������ʹ��
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_2);
	//��ʱ���ж�ʹ��	
	HAL_TIM_Base_Start_IT(&htim6);
	//���ͨ�ų�ʼ��
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,3,3);
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);
 	 //HAL_TIM_Base_Start_IT(&htim3); 

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
			
		DoubleBegin=0;
		Again=0;
		target1=target2=target3=target4=0;
		SetFourPWM(0,0,0,0);
		StopMove();
  while (1)
  {			
		
		/*
		//˫��Ч�����Դ���
		FrontMove();
		DoubleBegin=1;
		Again=1;
		target1=target2=target3=target4=2808;//enc=2808����Ȧ������תһ��Ȧ
		HAL_Delay(4000);	
		*/	
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
  while (1)
  {
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/