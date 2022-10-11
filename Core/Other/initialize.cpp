/**
 * @file initialize.cpp
 * @author Swayee2022 (malygosa@mail.ustc.edu.cn)
 * @brief 初始化电机相关的硬件和巡线相关的类对象
 * @version 1.0
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "initialize.h"

#include "tracer.h"
#include "patrol.h"/*patrol到现在还不能用，如果最后不用就删掉TODO*/
#include "motor.h"
#include "pid.h"


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
  return 1;
}

status_t curlingNodeInit(void){
#define READ_NODE_INPUT(__order)           \
  do                                       \
  {                                        \
    nodeInput[__order] = HAL_GPIO_ReadPin( \
        NODE_INPUT_##__order##_GPIO_Port,  \
        NODE_INPUT_##__order##_Pin);       \
  } while (0)

#if(BACKUP_PLAN==2)
  uint8_t nodeInput[3]={0};
  READ_NODE_INPUT(0);
  READ_NODE_INPUT(1);
  READ_NODE_INPUT(2);

  if(nodeInput[0]==0){/*当nodeInput=0时表示在该节点有我方壶*/
    bp_easyCurlingNode=1;
  }else{
    bp_easyCurlingNode=2;
  }
  if(nodeInput[1]==0){
    bp_hardCurlingNode_1=3;
      if(nodeInput[2]==0){
        bp_hardCurlingNode_2=4;
      }else{
        bp_hardCurlingNode_2=5;
      }
  }else{
    bp_hardCurlingNode_1=4;
    bp_hardCurlingNode_2=5;
  }
  return 1;

#else
  return 0;
#endif

#undef READ_NODE_INPUT
}

status_t tracerDestrcut(void){
  tracerSelector.~selector_t();
  patrol.~patrol_t();
  for(uint8_t i=0;i<directionCount;i++){
    tracer[i].~tracer_t();
  }
  return 1;
}
