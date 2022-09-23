
#include "callback.h"
#include "connectivity.h"

#include "motor.h"
#include "pid.h"

#include "tracer.h"
#include "patrol.h"


/* Private functions defines ---------------------------------------------*/

/*更新tracer的数据*/
void updateTracer(void){
  direction_t newDir=tracerSelector.update();
  tracer[newDir].updateData();
}

/*更新PWM输出TODO:把注释加上*/
void updatePWM(void){
  static int pwm1=0,pwm2=0,pwm3=0,pwm4=0;
  static float enc1=0,enc2=0,enc3=0,enc4=0;
  static float testnumber[2];
  static int enc;
  if(DoubleBegin==0){	
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
    
    //������PID���ߵ���
    static uint8_t tempData[12] = {0,0,0,0,0,0,0,0,0,0,0x80,0x7F};
    testnumber[0]=enc4;
    testnumber[1]=100.0;
    memcpy(tempData, (uint8_t *)&testnumber, sizeof(testnumber));
    HAL_UART_Transmit(&huart3,(uint8_t *)tempData,12,0x000A);
  }else if(DoubleBegin==1){	
    if(Again==1){
      enc1=enc2=enc3=enc4=0;
      Again=0;
    }			
    enc=Read_Encoder(1);
    if(enc<0) enc=-enc;
    enc1 = enc1 + enc;
    pwm1 = PID_calc(&motor1_position,enc1,target1);//λ�û�
    pwm1 = PID_calc(&motor1_speed,enc,pwm1);//�ٶȻ�	
    if(pwm1<0) pwm1=0;
      __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_1,pwm1);

    enc=Read_Encoder(2);
    if(enc<0) enc=-enc;
    enc2 = enc2 + enc;
    pwm2 = PID_calc(&motor2_position,enc2,target2);//λ�û�
    pwm2 = PID_calc(&motor2_speed,Read_Encoder(2),pwm2);//�ٶȻ�	
    if(pwm2<0) pwm2=0;
      __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_2,pwm2);
    
    enc=Read_Encoder(3);
    if(enc<0) enc=-enc;
    enc3 = enc3 + enc;
    pwm3 = PID_calc(&motor3_position,enc3,target3);//λ�û�
    pwm3 = PID_calc(&motor3_speed,enc,pwm3);//�ٶȻ�	
    if(pwm3<0) pwm3=0;
      __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,pwm3);
    
    enc=Read_Encoder(8);
    if(enc<0) enc=-enc;
    enc4 = enc4 + enc;
    pwm4 = PID_calc(&motor4_position,enc4,target4);//λ�û�
    pwm4 = PID_calc(&motor4_speed,Read_Encoder(8),pwm4);//�ٶȻ�	
    if(pwm4<0) pwm4=0;
      __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,pwm4);			
  }			

}

/*输出tracer的数值到PC*/
__DEBUG void printSensorValues(void){
  static uint8_t testDir=(uint8_t)dirFront;
  tracer[testDir].printSensorVal();
	if(testDir<dirBack){
		testDir++;
	}else{
		testDir=dirFront;
	}
}

/*取二者较小的数值*/
inline uint8_t min(uint8_t a,uint8_t b){
  return (a<b)?a:b;
}

/*根据接收字符串和长度构造message_t类型*/
inline message_t buildMsgType(uint8_t *buff,uint8_t length){
  message_t newMsg;
  newMsg.command=(command_t)buff[0];
  for(uint8_t i=0;i<length;i++){
    newMsg.argList[i]=buff[i+1];
  }
  return newMsg;
}

/* Exported functions definations ---------------------------------------------*/

void tim6_callback(void){
  updateTracer();
}

void tim6_50period_callback(void){
  printSensorValues();
  updatePWM();
}

void USART2_IdleCallback(uint8_t *buff,uint8_t buffSize){
  const uint8_t length=min(argCountMax,buffSize-1);  
  message_t newMsg=buildMsgType(buff,length);
  receiveCommand(newMsg);
}
