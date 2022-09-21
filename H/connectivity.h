/*���Ƶ�main.h���棬Ҳ�����½�һ��connectivity.h,Ȼ���Ƶ�������*/

/* USER CODE BEGIN ET */
#include "main.h"
#include "usart.h"


typedef enum{
  errorCmd=0x00,  //Ԥ����������ָ�����ͨ�Ź����е�����
  moveCmd=0x01,  //���ٻ���ٵ�ָ�Ԥ��һ���ٶ�
  rotateCmd=0x02, //ԭ����תָ�Ĭ�ϴ�ʱ�Ǿ�ֹ״̬
  trimCmd=0x03, //ǰ�������е����Ƕȵ�ָ�����ԭ����ת
  stopCmd=0x04, //��ɲָ��
  detectCodeCmd=0x05, //���ǰ��������ָ���c8t6->respberry
  pushArmCmd=0x06,  //��������˶�ָ��
  detectCodeAns=0x07, //������ļ�ⷴ��ָ���respberry->c8t6
  reservedCmd=0x010,  //Ԥ��ָ��
  testCmd=0x011,  //ǰ�ڲ���ָ�ͨ��Э���Ƿ��������

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

/*ƽ���ڵ㣬��·���е�����ڵ����ͣ��ĸ�����������ֵ���������*/
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

/*�ؼ��ڵ㣬��Ѳ��ģ��Ķ�λ�ڵ�*/
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
