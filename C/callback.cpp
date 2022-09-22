
#include "callback.h"
#include "tracer.h"
#include "connectivity.h"
#include "patrol.h"

/* Private functions defines ---------------------------------------------*/
/*取二者较小的数值*/
inline uint8_t min(uint8_t a,uint8_t b){
  return (a<b)?a:b;
}

/*根据接收字符串和长度构造message_t类型*/
inline message_t buildMsgType(uint8_t *buff,uint8_t length){
  message_t newMsg;
  newMsg.command=(command_t)buff[0];
  for(uint8_t i=0;i<length;i++){
    newMsg.argList[i]=receiveBuff[i+1];
  }
  return newMsg;
}


/* Exported functions definations ---------------------------------------------*/

void tim3_callback(void){
  direction_t newDir=tracerSelector.update();
  tracer[newDir].updateData();
}

uint8_t testDir=dirFront;
void tim3_100period_callback(void){
  tracer[testDir].printSensorVal();
	if(testDir<dirBack){
		testDir++;
	}else{
		testDir=dirFront;
	}
}

void uart1_callback(uint8_t *buff,uint8_t buffSize){
  const uint8_t length=min(argCountMax,buffSize-1);  
  message_t newMsg=buildMsgType(buff,length);
  receiveCommand(newMsg);
}
