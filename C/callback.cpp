
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

/*行进过程中调整方向,仅支持向前行进时对tracer[dirFront]进行检测*/
__DEBUG void adjustDirFront(void){
  using namespace tracer_nsp;
  if(chassis.onTrail==0 || chassis.headingDir!=dirFront)
    return;
  if(tracer[dirFront].readSensorVal(L2)==blackParcel || tracer[dirFront].readSensorVal(R1)==whiteParcel ){
    chassis.trim(dirLeft,trimIntensDefault);
  }else if(tracer[dirFront].readSensorVal(R2)==blackParcel || tracer[dirFront].readSensorVal(L1)==whiteParcel){
    chassis.trim(dirRight,trimIntensDefault);
  }else{
    chassis.trim(dirFront,trimIntensDefault);
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
  //counter.updateDate();
  updateTracer();
}

void tim6_50period_callback(void)
{
  /*进入中断间隔为50ms*/
  if(flagInitReady==0)
    return;
  updatePWM();
  adjustDirFront();
}

void USART2_IdleCallback(uint8_t *buff, uint8_t buffSize)
{
  const uint8_t length = MIN(argCountMax, buffSize - 1);
  message_t newMsg = buildMsgType(buff, length);
  receiveCommand(newMsg);
}
