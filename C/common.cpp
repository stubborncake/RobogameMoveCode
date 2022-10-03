
#include "common.h"
#include "tracer.h"
#include "patrol.h"
#include "path.h"
#include "motor.h"
#include "pid.h"

/* Exported macro ------------------------------------------------------------*/

status_t flagInitReady=0;
status_t flagDetectCode=0;
/* Private functions definations ---------------------------------------------*/

/* Exported functions definations ---------------------------------------------*/

direction_t oppositeDir(uint8_t newDir){
    uint8_t opDir=dirNowhere;
    switch ((direction_t)newDir)
    {
    case dirFront:
        opDir=dirBack;
        break;
    case dirRight:
        opDir=dirLeft;
        break;
    case dirLeft:
        opDir=dirRight;
        break;
    case dirBack:
        opDir=dirFront;
        break;
    default:
        opDir=dirNowhere;
        break;
    }
    return (direction_t)opDir;
}

direction_t getRightDir(direction_t newDir){
	uint8_t rightDir=dirNowhere;
    switch (newDir)
    {
    case dirFront:
        rightDir=dirRight;
        break;
    case dirRight:
        rightDir=dirBack;
        break;
    case dirLeft:
        rightDir=dirFront;
        break;
    case dirBack:
        rightDir=dirLeft;
        break;
    default:
        rightDir=dirNowhere;
        break;
    }
    return (direction_t)rightDir;
}

direction_t getLeftDir(direction_t newDir){
  return getRightDir(oppositeDir(newDir));
}


__DEBUG HAL_StatusTypeDef \
printMsg(uint8_t *newMsg,uint8_t msgSize,UART_HandleTypeDef printUart,uint32_t timeout){
  if(sizeof(newMsg)<msgSize)
      msgSize=sizeof(newMsg)+1;
  return HAL_UART_Transmit(&printUart,newMsg,msgSize,timeout);
}

__DEBUG HAL_StatusTypeDef printText(const char *newMsg){
  uint8_t msgSize=sizeof(newMsg)/sizeof(const unsigned char);
  uint8_t *newMsg_uint8=new uint8_t[msgSize];
  for(uint8_t i=0;i<msgSize;i++){
    newMsg_uint8[i]=(uint8_t)newMsg[i];
  }
  return printMsg(newMsg_uint8,msgSize,huart3,timeoutDefault);
}

void Delay_us(uint16_t us)
{
  const uint16_t Delay_Factor_us = HAL_RCC_GetHCLKFreq() / 1000 / 1000; // ought to be defined in .h file
  uint32_t tmp;
  SysTick->LOAD = us * Delay_Factor_us;
  SysTick->VAL = 0x00;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
  do
  {
    tmp = SysTick->CTRL;
  } while (tmp & 0x01 && !(tmp & (1 << 16)));
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL = 0x00;
}

status_t motorInit(void){
  //PWM init
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	//PID value init
	PID_Value_Init();
	//encode inite
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_2);

  DoubleBegin=0;
  Again=0;
  target1=target2=target3=target4=0;
  SetFourPWM(0,0,0,0);
  StopMove();
  return 1;
}

status_t tracerInit(void){
  status_t flag=1;
  tracerSelector.setCurrDir(dirFront);
  patrol.switchMode(tracer_nsp::on);
  patrol.setKeyNode(startLine);
  for(uint8_t i=0;i<directionCount;i++){
    tracer[i].clearData();
    tracer[i].detectMode(tracer_nsp::on);
    tracer[i].calcStatusMode(tracer_nsp::on);
  }
  HAL_Delay(10);
  flagInitReady=1;
  return flag;
}

status_t tracerDestrcut(void){
  tracerSelector.~selector_t();
  patrol.~patrol_t();
  for(uint8_t i=0;i<directionCount;i++){
    tracer[i].~tracer_t();
  }
  return 1;
}
