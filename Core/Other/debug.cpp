#include "common.h"
#include "path.h"
#include "chassis.h"
#include "tracer.h"

uint8_t flag_fatalError=0;

#ifdef __DEBUG

/*备用方案，在视觉无法实现时启用*/
#if (BACKUP_PLAN==1)


#elif(BACKUP_PLAN==2)

uint8_t bp_easyCurlingNode=1;
uint8_t bp_hardCurlingNode_1=3;
uint8_t bp_hardCurlingNode_2=4;

#endif

/*向电脑发送的调试信息的相关函数*/

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

/*一些其他的测试函数*/

void testSensors(void){
    static uint8_t testDir=dirFront;
    tracer[testDir].printSensorVal();
    tracer[testDir].printPathStatus();
    testDir=getRightDir((direction_t)testDir);
    HAL_Delay(testPrintInterval);
}

void testPatrol(void){
    patrol.printPlainNode();
    HAL_Delay(testPrintInterval);
}

void testDetectCurling(void){
    if(chassis.detectCode(1)==1){
      chassis.raiseArm(tracer_nsp::up,5);
      HAL_Delay(2000);
      chassis.raiseArm(tracer_nsp::down,5);
    }else{
      //do nothing
    }
    HAL_Delay(testPrintInterval);
}

#endif




