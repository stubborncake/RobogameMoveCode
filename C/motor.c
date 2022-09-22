#include "motor.h"
#include "connectivity.h"
//读取编码器的值
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
//向前
void FrontMove(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_RESET);//1号轮向前

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_SET);//2号轮向前

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_RESET);//3号轮向前

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_SET);//4号轮向前
}
//向后
void BackMove(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_SET);//1号轮向后

	
HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_RESET);//2号轮向后	

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_SET);//3号轮向后

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_RESET);//4号轮向后
}
//向左
void LeftMove(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);//1号轮向后

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_SET);//2号轮向前

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_RESET);//3号轮向前

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_RESET);//4号轮向后
}
//向右
void RightMove(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_RESET);//1号轮向前

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_RESET);//2号轮向后

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_SET);//3号轮向后

HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_SET);//4号轮向前

}
//四轮滑行
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

//向左旋转
void LeftRotate(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_SET);//1号轮向后

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_SET);//2号轮向前

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_SET);//3号轮向后
	
HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_SET);//4号轮向前	
	

}	

//向右旋转
void RightRotate(void)
{
HAL_GPIO_WritePin(GPIOF,m11_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m12_Pin,GPIO_PIN_RESET);//1号轮向前

HAL_GPIO_WritePin(GPIOF,m21_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOF,m22_Pin,GPIO_PIN_RESET);//2号轮向后	

HAL_GPIO_WritePin(GPIOC,m31_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m32_Pin,GPIO_PIN_RESET);//3号轮向前	
	
HAL_GPIO_WritePin(GPIOC,m41_Pin,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC,m42_Pin,GPIO_PIN_RESET);//4号轮向后	
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
	if(newdir==goFront)
		{
			FrontMove();
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
		}	
	if(newdir==goBack)
		{
			BackMove();
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
		}
	if(newdir==goLeft)
		{
			LeftMove();
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
		}
	if(newdir==goRight)
		{
			RightMove();
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
		}		
}	
void Trim(direction_t newdir,uint16_t newspeed,float TrimIntensity)
{
	if(newdir==goLeft)
	{
		FrontMove();
		SetTarget(newspeed*100*TrimIntensity/255,newspeed*100*TrimIntensity/255,newspeed*100/255,newspeed*100/255);
	}
	if(newdir==goRight)
	{
		FrontMove();
		SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100*TrimIntensity/255,newspeed*100*TrimIntensity/255);
	}		
}	
void Rotate(direction_t newdir,uint16_t newspeed)
{
	if(newdir==goLeft)
	{
			LeftRotate();			
			SetTarget(newspeed*100/255,newspeed*100/255,newspeed*100/255,newspeed*100/255);
	}		
	if(newdir==goRight)
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
