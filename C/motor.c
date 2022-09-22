#include "motor.h"
#include "connectivity.h"
#include "pid.h"
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
void PidSet()
{
		static int pwm1=0,pwm2=0,pwm3=0,pwm4=0;
		static float enc1=0,enc2=0,enc3=0,enc4=0;
		static float enc=0;
		static float testnumber[2];
	
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
