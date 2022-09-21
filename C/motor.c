#include "motor.h"
//��ȡ��������ֵ
int Read_Encoder(int TIMX)
{		
	int Encoder_TIM;		
	switch(TIMX)
	{
		 case 1: 	Encoder_TIM = (short)TIM1 -> CNT; 			
					TIM1 -> CNT=0;break;	
		 case 2:  Encoder_TIM = (short)TIM2 -> CNT;  
					TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM = (short)TIM3 -> CNT;  
					TIM3 -> CNT=0;break;	
		 case 8:  Encoder_TIM = (short)TIM8 -> CNT;  
					TIM8 -> CNT=0;break;
		 default:  Encoder_TIM = 0;
	}
	return Encoder_TIM;
}
//��ǰ
void FrontMove(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_RESET);//1������ǰ

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_SET);//2������ǰ

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_RESET);//3������ǰ

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_SET);//4������ǰ
}
//���
void BackMove(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_SET);//1�������

	
HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_RESET);//2�������	

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_SET);//3�������

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_RESET);//4�������
}
//����
void LeftMove(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);//1�������

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_SET);//2������ǰ

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_RESET);//3������ǰ

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_RESET);//4�������
}
//����
void RightMove(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_RESET);//1������ǰ

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_RESET);//2�������

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_SET);//3�������

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_SET);//4������ǰ

}
//���ֻ���
void SkipMove(void)
{	
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF	,m12_Pin,GPIO_PIN_SET);
	
HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_SET);
	
HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_SET);

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_SET);
	

}

//������ת
void LeftRotate(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_SET);//1�������

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_SET);//2������ǰ

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_SET);//3�������
	
HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_SET);//4������ǰ	
	

}	

//������ת
void RightRotate(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_RESET);//1������ǰ

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_RESET);//2�������	

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_RESET);//3������ǰ	
	
HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_RESET);//4�������	
}
void StopMove(void)
{	
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_RESET);
	
HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_RESET);
	
HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_RESET);

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_RESET);
}
void SetFourPWM(int a,int b,int c,int d)
{
__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_1,a);
__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_2,b);
__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,c);
__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,d);	
}	
