#include "motor.h"
#include "connectivity.h"
#include "common.h"

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
void SetTarget(int a,int b,int c,int d)
{
	target1=a;
	target2=b;
	target3=c;
	target4=d;
}
void Move(direction_t newdir,uint16_t newspeed)
{
	if(newdir==dirFront)
		{
			FrontMove();
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
		}	
	if(newdir==dirBack)
		{
			BackMove();
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
		}
	if(newdir==dirLeft)
		{
			LeftMove();
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
		}
	if(newdir==dirRight)
		{
			RightMove();
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
		}		
}	
void Trim(direction_t newdir,uint16_t newspeed,float TrimIntensity)
{
	if(newdir==dirLeft)
	{
		FrontMove();
		SetTarget(newspeed*100*TrimIntensity/255,newspeed*100*TrimIntensity/255,newspeed*100/255,newspeed*100/255);
	}
	if(newdir==dirRight)
	{
		FrontMove();
		SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100*TrimIntensity/255,newspeed*100*TrimIntensity/255);
	}		
}	
void Rotate(direction_t newdir,uint16_t newspeed)
{
	if(newdir==dirLeft)
	{
			LeftRotate();			
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
	}		
	if(newdir==dirRight)
	{
			RightRotate();			
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
	}		
}	
void Stop()
{
	SetFourPWM(0,0,0,0);
	SetTarget(0,0,0,0);
	StopMove();
}
