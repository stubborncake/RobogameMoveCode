#include "motor.h"
#include "connectivity.h"
#include "pid.h"

int target1, target2, target3, target4;
int DoubleBegin, Again;

//��ȡ��������ֵ
int Read_Encoder(int TIMX)
{
	int Encoder_TIM;
	switch (TIMX)
	{
	case 1:
		Encoder_TIM = (short)TIM1->CNT;
		TIM1->CNT = 0;
		break;
	case 2:
		Encoder_TIM = (short)TIM2->CNT;
		TIM2->CNT = 0;
		break;
	case 3:
		Encoder_TIM = (short)TIM3->CNT;
		TIM3->CNT = 0;
		break;
	case 8:
		Encoder_TIM = (short)TIM8->CNT;
		TIM8->CNT = 0;
		break;
	default:
		Encoder_TIM = 0;
	}
	return Encoder_TIM;
}

#define WRITE_PIN(a1, a2, a3, a4, a5, a6, a7, a8) \
	do                                            \
	{                                             \
		HAL_GPIO_WritePin(GPIOF, m11_Pin, a1);    \
		HAL_GPIO_WritePin(GPIOF, m12_Pin, a2);    \
		HAL_GPIO_WritePin(GPIOF, m21_Pin, a3);    \
		HAL_GPIO_WritePin(GPIOF, m22_Pin, a4);    \
		HAL_GPIO_WritePin(GPIOC, m31_Pin, a5);    \
		HAL_GPIO_WritePin(GPIOC, m32_Pin, a6);    \
		HAL_GPIO_WritePin(GPIOC, m41_Pin, a7);    \
		HAL_GPIO_WritePin(GPIOC, m42_Pin, a8);    \
	} while (0)

#define ON (GPIO_PIN_SET)
#define OFF (GPIO_PIN_RESET)

//��ǰ
void FrontMove(void)
{
	WRITE_PIN(ON, OFF, OFF, ON, ON, OFF, OFF, ON);
}
//���
void BackMove(void)
{
	WRITE_PIN(OFF, ON, ON, OFF, OFF, ON, ON, OFF);
}
//����
void LeftMove(void)
{
	WRITE_PIN(OFF, ON, OFF, ON, ON, OFF, ON, OFF);
}
//����
void RightMove(void)
{
	WRITE_PIN(ON, OFF, ON, OFF, OFF, ON, OFF, ON);
}
//���ֻ���
void SkipMove(void)
{
	WRITE_PIN(ON, ON, ON, ON, ON, ON, ON, ON);
}

//������ת
void LeftRotate(void)
{
	WRITE_PIN(OFF, ON, OFF, ON, OFF, ON, OFF, ON);
}

//������ת
void RightRotate(void)
{
	WRITE_PIN(ON, OFF, ON, OFF, ON, OFF, ON, OFF);
}
void StopMove(void)
{
	WRITE_PIN(OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF);
}

/*更新PWM输出*/
void updatePWM(void)
{
	static int pwm1 = 0, pwm2 = 0, pwm3 = 0, pwm4 = 0;
	static float enc1 = 0, enc2 = 0, enc3 = 0, enc4 = 0;
	static float testnumber[2];
	static int enc;
	if (DoubleBegin == 0)
	{
		enc1 = Read_Encoder(1);
		if (enc1 < 0)
			enc1 = -enc1;
		pwm1 = PID_calc(&motor1_speed, enc1, target1);
		if (pwm1 < 0)
			pwm1 = 0;
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, pwm1);

		enc2 = Read_Encoder(2);
		if (enc2 < 0)
			enc2 = -enc2;
		pwm2 = PID_calc(&motor2_speed, enc2, target2);
		if (pwm2 < 0)
			pwm2 = 0;
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, pwm2);

		enc3 = Read_Encoder(3);
		if (enc3 < 0)
			enc3 = -enc3;
		pwm3 = PID_calc(&motor3_speed, enc3, target3);
		if (pwm3 < 0)
			pwm3 = 0;
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm3);

		enc4 = Read_Encoder(8);
		if (enc4 < 0)
			enc4 = -enc4;
		pwm4 = PID_calc(&motor4_speed, enc4, target4);
		if (pwm4 < 0)
			pwm4 = 0;
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm4);

		//������PID���ߵ���
		static uint8_t tempData[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0x7F};
		testnumber[0] = enc4;
		testnumber[1] = 100.0;
		memcpy(tempData, (uint8_t *)&testnumber, sizeof(testnumber));
		HAL_UART_Transmit(&huart3, (uint8_t *)tempData, 12, 0x000A);
	}
	else if (DoubleBegin == 1)
	{
		if (Again == 1)
		{
			enc1 = enc2 = enc3 = enc4 = 0;
			Again = 0;
		}
		enc = Read_Encoder(1);
		if (enc < 0)
			enc = -enc;
		enc1 = enc1 + enc;
		pwm1 = PID_calc(&motor1_position, enc1, target1); //λ�û�
		pwm1 = PID_calc(&motor1_speed, enc, pwm1);		  //�ٶȻ�
		if (pwm1 < 0)
			pwm1 = 0;
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, pwm1);

		enc = Read_Encoder(2);
		if (enc < 0)
			enc = -enc;
		enc2 = enc2 + enc;
		pwm2 = PID_calc(&motor2_position, enc2, target2); //λ�û�
		pwm2 = PID_calc(&motor2_speed, enc, pwm2);		  //�ٶȻ�
		if (pwm2 < 0)
			pwm2 = 0;
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, pwm2);

		enc = Read_Encoder(3);
		if (enc < 0)
			enc = -enc;
		enc3 = enc3 + enc;
		pwm3 = PID_calc(&motor3_position, enc3, target3); //λ�û�
		pwm3 = PID_calc(&motor3_speed, enc, pwm3);		  //�ٶȻ�
		if (pwm3 < 0)
			pwm3 = 0;
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm3);

		enc = Read_Encoder(8);
		if (enc < 0)
			enc = -enc;
		enc4 = enc4 + enc;
		pwm4 = PID_calc(&motor4_position, enc4, target4); //λ�û�
		pwm4 = PID_calc(&motor4_speed, enc, pwm4);		  //�ٶȻ�
		if (pwm4 < 0)
			pwm4 = 0;
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm4);
	}
}

void SetFourPWM(int a, int b, int c, int d)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, a);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, b);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, c);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, d);
}
void SetTarget(int a, int b, int c, int d)
{
	target1 = a;
	target2 = b;
	target3 = c;
	target4 = d;
}

/*速度的换算公式，保留不适用*/
#define CalSpeed (newspeed)

void motorMove(direction_t newdir, uint16_t newspeed)
{
	if (newdir == dirFront)
	{
		FrontMove();
		SetTarget(CalSpeed, CalSpeed, CalSpeed, CalSpeed);
	}
	if (newdir == dirBack)
	{
		BackMove();
		SetTarget(CalSpeed, CalSpeed, CalSpeed, CalSpeed);
	}
	if (newdir == dirLeft)
	{
		LeftMove();
		SetTarget(CalSpeed, CalSpeed, CalSpeed, CalSpeed);
	}
	if (newdir == dirRight)
	{
		RightMove();
		SetTarget(CalSpeed, CalSpeed, CalSpeed, CalSpeed);
	}
}
void motorTrim(direction_t newdir1,direction_t newdir2, uint16_t newspeed, float TrimIntensity)
{
      if(newdir1=dirFront)
	{
	FrontMove();	
	if (newdir2 == dirLeft) SetTarget(CalSpeed * TrimIntensity, CalSpeed * TrimIntensity, CalSpeed, CalSpeed);			
	if (newdir2 == dirRight) SetTarget(CalSpeed, CalSpeed, CalSpeed * TrimIntensity, CalSpeed * TrimIntensity);			
	}
      if(newdir1=dirBack)
	{
	BackMove();	
	if (newdir2 == dirLeft)  SetTarget(CalSpeed, CalSpeed, CalSpeed * TrimIntensity, CalSpeed * TrimIntensity);		
	if (newdir2 == dirRight)  SetTarget(CalSpeed * TrimIntensity, CalSpeed * TrimIntensity, CalSpeed, CalSpeed);		
	}
     if(newdir1=dirRight)
	{
	RightMove();	
	if (newdir2 == dirLeft) SetTarget(CalSpeed * TrimIntensity, CalSpeed , CalSpeed* TrimIntensity, CalSpeed);			
	if (newdir2 == dirRight) SetTarget(CalSpeed, CalSpeed * TrimIntensity, CalSpeed, CalSpeed * TrimIntensity);			
	}
     if(newdir1=dirLeft)
	{
	LeftMove();	
	if (newdir2 == dirLeft) SetTarget(CalSpeed, CalSpeed * TrimIntensity, CalSpeed, CalSpeed * TrimIntensity);				
	if (newdir2 == dirRight) SetTarget(CalSpeed * TrimIntensity, CalSpeed , CalSpeed* TrimIntensity, CalSpeed);		
	}
}
void motorRotate(direction_t newdir, uint16_t newspeed)
{
	if (newdir == dirLeft)
	{
		LeftRotate();
		SetTarget(CalSpeed, CalSpeed, CalSpeed, CalSpeed);
	}
	if (newdir == dirRight)
	{
		RightRotate();
		SetTarget(CalSpeed, CalSpeed, CalSpeed, CalSpeed);
	}
}
void motorStop(void)
{
	SetFourPWM(0, 0, 0, 0);
	SetTarget(0, 0, 0, 0);
	StopMove();
}

void DoublePidMove(direction_t newdir, uint16_t distance,uint16_t EstimatedTime)
{
	DoubleBegin = 1; //双环开始指示变量置1
	Again = 1;		 //双环第一次指示变量置1
	if (newdir == dirFront)
		FrontMove();
	if (newdir == dirBack)
		BackMove();
	if (newdir == dirLeft)
		LeftMove();
	if (newdir == dirRight)
		RightMove();
	SetTarget(distance, distance, distance, distance);
	HAL_Delay(EstimatedTime);
	DoubleBegin = 1;//双环开始指示变量置0
}

void DoublePidRotate(direction_t newdir, uint16_t distance,uint16_t EstimatedTime)
{
	DoubleBegin = 1; //双环开始指示变量置1
	Again = 1;		 //双环第一次指示变量置1
	if (newdir == dirLeft)
		LeftRotate();
	if (newdir == dirRight)
		RightRotate();
	SetTarget(distance, distance, distance, distance);
	HAL_Delay(EstimatedTime);
	DoubleBegin = 1;//双环开始指示变量置0
}

void Rotate180degree()
{
	PID_Value_Init();
	motorStop();
	HAL_Delay(500);
	LeftRotate();
	SetFourPWM(0,0,0,0);
	SetTarget(120,120,120,120);
	HAL_Delay(6650);
	motorStop();
}

void PushCurling(uint16_t EstimatedTime)
{
HAL_GPIO_WritePin(GPIOF,PUSH_Pin,GPIO_PIN_SET);
HAL_Delay(EstimatedTime);
HAL_GPIO_WritePin(GPIOF,PUSH_Pin,GPIO_PIN_RESET);
}
