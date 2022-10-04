
#include "callback.h"
#include "connectivity.h"
#include "counter.h"
#include "chassis.h"

#include "motor.h"
#include "pid.h"

#include "tracer.h"
#include "patrol.h"
#include "path.h"

/* Private functions defines ---------------------------------------------*/

/*更新tracer的数据*/
void updateTracer(void)
{
  direction_t newDir = tracerSelector.update();
  tracer[newDir].updateData();
}

/*输出tracer的数值到PC*/
__DEBUG void printSensorValues(void)
{
  static uint8_t testDir = (uint8_t)dirFront;
  uint8_t msgHead[]={(uint8_t)(testDir+'0'),':','\t'};
  printMsg(msgHead,3);
  tracer[testDir].printSensorVal();
  if (testDir < dirBack)
  {
    testDir++;
  }
  else
  {
    testDir = dirFront;
  }
}

/*根据接收字符串和长度构造message_t类型*/
inline message_t buildMsgType(uint8_t *buff, uint8_t length)
{
  message_t newMsg;
  newMsg.command = (command_t)buff[0];
  for (uint8_t i = 0; i < length; i++)
  {
    newMsg.argList[i] = buff[i + 1];
  }
  return newMsg;
}

/* Exported functions definations ---------------------------------------------*/

void tim6_callback(void)
{
  /*进入中断间隔为1ms*/

  if(flagInitReady==0)
    return;
  counter.updateDate();
  updateTracer();
  //patrol.updatePlainNode();
}

void tim6_50period_callback(void)
{
  /*进入中断间隔为50ms*/
  if(flagInitReady==0)
    return;

#if (STATIC_DEBUG==0)
  updatePWM();
  chassis.adjustDirection();
#endif
}

void USART2_IdleCallback(uint8_t *buff, uint8_t buffSize)
{
  //const uint8_t length = MIN(argCountMax, buffSize - 1);
#ifdef __DEBUG
  if(buff[0]==detectCodeAns){
    flagDetectCode=1;
  }
#else
  message_t newMsg = buildMsgType(buff, length);
  receiveCommand(newMsg);
#endif
}
