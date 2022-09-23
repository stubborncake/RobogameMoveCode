#include "motor.h"
#include "connectivity.h"
#include "common.h"

int target1,target2,target3,target4;
int DoubleBegin,Again;

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
	case 4:
		Encoder_TIM = (short)TIM8->CNT;
		TIM8->CNT = 0;
		break;
	default:
		Encoder_TIM = 0;
	}
	return Encoder_TIM;
}

#define WRITE_PIN(a1,a2,a3,a4,a5,a6,a7,a8) do{\
	HAL_GPIO_WritePin(GPIOF, m11_Pin, a1);\
	HAL_GPIO_WritePin(GPIOF, m12_Pin, a2); \
	HAL_GPIO_WritePin(GPIOF, m21_Pin, a3);\
	HAL_GPIO_WritePin(GPIOF, m22_Pin, a4); \
	HAL_GPIO_WritePin(GPIOC, m31_Pin, a5);\
	HAL_GPIO_WritePin(GPIOC, m32_Pin, a6); \
	HAL_GPIO_WritePin(GPIOC, m41_Pin, a7);\
	HAL_GPIO_WritePin(GPIOC, m42_Pin, a8); \
}while(0)

#define ON (GPIO_PIN_SET)
#define OFF (GPIO_PIN_RESET)



//��ǰ
void FrontMove(void)
{
	WRITE_PIN(ON,OFF,OFF,ON,ON,OFF,OFF,ON);
}
//���
void BackMove(void)
{
	WRITE_PIN(OFF,ON,ON,OFF,OFF,ON,ON,OFF);
}
//����
void LeftMove(void)
{
	WRITE_PIN(OFF,ON,OFF,ON,ON,OFF,ON,OFF);
}
//����
void RightMove(void)
{
	WRITE_PIN(ON,OFF,ON,OFF,OFF,ON,OFF,ON);
}
//���ֻ���
void SkipMove(void)
{
	WRITE_PIN(ON,ON,ON,ON,ON,ON,ON,ON);
}

//������ת
void LeftRotate(void)
{
	WRITE_PIN(OFF,ON,OFF,ON,OFF,ON,OFF,ON);
}

//������ת
void RightRotate(void)
{
	WRITE_PIN(ON,OFF,ON,OFF,ON,OFF,ON,OFF);
}
void StopMove(void)
{
	WRITE_PIN(OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF);
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

#define CalSpeed (newspeed * 100 / 255)

void Move(direction_t newdir, uint16_t newspeed)
{
	if (newdir == dirFront)
	{
		FrontMove();
		SetTarget(CalSpeed, CalSpeed, CalSpeed, CalSpeed);
	}
	if (newdir == dirBack)
	{
		BackMove();
		SetTarget(CalSpeed, CalSpeed,CalSpeed, CalSpeed);
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
void Trim(direction_t newdir, uint16_t newspeed, float TrimIntensity)
{
	if (newdir == dirLeft)
	{
		FrontMove();
		SetTarget(CalSpeed * TrimIntensity , CalSpeed * TrimIntensity , CalSpeed, CalSpeed);
	}
	if (newdir == dirRight)
	{
		FrontMove();
		SetTarget(CalSpeed, CalSpeed, CalSpeed * TrimIntensity , CalSpeed * TrimIntensity );
	}
}
void Rotate(direction_t newdir, uint16_t newspeed)
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
void Stop()
{
	SetFourPWM(0, 0, 0, 0);
	SetTarget(0, 0, 0, 0);
	StopMove();
}
