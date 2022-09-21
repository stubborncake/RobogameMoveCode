/*复制到main.h里面，也可以新建一个connectivity.h,然后复制到这里面*/

/* USER CODE BEGIN ET */
#include "main.h"
#include "usart.h"


typedef enum{
  errorCmd=0x00,  //预设的意外错误指令，或者通信过程中的噪声
  moveCmd=0x01,  //加速或减速的指令，预设一个速度
  rotateCmd=0x02, //原地旋转指令，默认此时是静止状态
  trimCmd=0x03, //前进过程中调整角度的指令，不是原地旋转
  stopCmd=0x04, //急刹指令
  detectCodeCmd=0x05, //检测前方条形码指令，由c8t6->respberry
  pushArmCmd=0x06,  //步进电机运动指令
  detectCodeAns=0x07, //条形码的检测反馈指令，由respberry->c8t6
  reservedCmd=0x010,  //预留指令
  testCmd=0x011,  //前期测试指令，通信协议是否可以运行

}command_t;

typedef struct{
  command_t command;
  uint8_t argCount;
  uint8_t * argList;
  uint32_t timeout;
}message_t;

typedef enum{
  sensorDirFront=0x00,
  sensorDirRight=0x01,
  sensorDirBack=0x02,
  sensorDirLeft=0x03,
}sensorDir_t;


typedef enum{
  goFront=0,
  goRight=1,
  goBack=2,
  goLeft=3,
}direction_t;

typedef uint8_t status_t;

/*平凡节点，即路程中的任意节点类型，四个传感器返回值的排列组合*/
typedef enum{
  nowhere=0,
  frontOnly=1,
  backOnly=2,
  rightOnly=3,
  leftOnly=4,
  straightLine=5,
  horizontalLine=6,
  rightTurn=7,
  leftTurn=8,
  rightFork=9,
  leftFork=10,
  T_crossing=11,
  crossing=12,
}plainNode_t;

/*关键节点，即巡线模块的定位节点*/
typedef enum{
  startLine=0,
  upperRightTurning=1,
  lowerRightTurning=2,
  baseNode=3,
  crossroadLeft=4,
  crossroadMid=5,
  crossroadRight=6,
  curlingDepositEasy=7,
  curlingDepositHard=8, 

}keyNode_t;

HAL_StatusTypeDef sendCommand(message_t newMsg);
void receiveCmd(message_t newMsg);
void Delay_us(uint16_t us);
/* USER CODE END ET */
