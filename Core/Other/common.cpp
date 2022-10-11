/**
 * @file common.cpp
 * @author Swayee2022 (malygosa@mail.ustc.edu.cn)
 * @brief 一些基本的辅助函数
 * 
 * 方向的转换，微妙级别的延时，脱线后的尝试矫正函数入口
 * 
 * @version 1.4
 * @date 2022-10-06
 * @see https://github.com/Deagle-PrintStream/connectivity_merge/tree/project_struct_rebuild
 * @copyright Copyright (c) 2022
 * 
 */
#include "common.h"
#include "tracer.h"
#include "patrol.h"
#include "path.h"
#include "motor.h"
#include "pid.h"

/**
 * @brief TODO list
 * 
 * 修改微调的实现函数，使得在微调过程中的宏观移动速度保持不变
 * 修改pid参数，使得起步阶段的加速过程不会和微调指令发生冲突
 * 修改通信模块，增加发送指令的确认反馈，计划修改方案：
 *      利用hal_transmit的反馈值，当不是hal_ok时，多次发送
 *      新增一个确认收到的指令，当没有收到时，多次发送
 *      无反馈，一次性发送多个相同指令，希望能有一次收到
 * 
 * 修改发射操作，适配新的铲壶机构，不用再后退
 * 在发射阶段调整角度发射
 * 修改部分阶段的移动速度，尽可能减少无操作的等待时间
 * 
 */


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

void lostTrace_Handler(void){

/*not used yet*/
#ifndef __DEBUG
  uint8_t flag=0;
  flag=path.adjustBacktoTrace();  
  if(flag==1){
    return;//成功矫正了回来
  }else{
      //没有矫正回来
  }
#endif

}
