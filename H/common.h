
#ifndef __COMMON_H
#define __COMMON_H
/* Private includes ----------------------------------------------------------*/
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported constants ------------------------------------------------------------*/

static const uint8_t msgSizeDefault=10;/*调试用的信息最大长度*/
static const uint8_t directionCount=4;/*这个世界有四个方向*/
static const uint8_t argCountMax=3;/*指令的参数最多有3个*/

/*速度常量，待定TODO:*/
static const uint8_t superCharge=200;
static const uint8_t speedHigh=100;
static const uint8_t speedLow=10;

/*预设各个阶段运动的大致时间，TODO:设定最大timeout,例如原地旋转90度的所需时间*/

static const uint32_t timeoutDefault=0x00ff;;/*默认超时毫秒常量*/
static const uint32_t timeoutMax=0x0ffffffff;;/*最大超时参数，对于比赛时间而言即无穷*/
static const uint16_t waitforDelayTime=0x05;;/*waitFor函数的周期延时常量*/
namespace timeout_nsp{
	static const uint32_t wasteLandTime=16000;
	static const uint32_t rotateTime_90degree=1500;
	static const uint32_t rotateTime_180degree=2800;
	static const uint32_t decelerateTime=1000;
}

/* Exported types ------------------------------------------------------------*/
/*状态类型*/

/*方向类型*/
enum direction_t{
	dirFront=0,
	dirRight=1,
	dirLeft=2,
	dirBack=3,	
	dirNowhere=4,
	dirAll=5,
};

/*状态类型，即布尔值，但是boolean是int型，太长了*/
typedef uint8_t status_t;

/*tracer相关的类型*/
namespace tracer_nsp{
	enum on_off_t{
		off=0,
		on=1,
	};
	enum hit_leave_t{
		leave=0,
		hit=1,
	};

	enum sensorOrder_t{
		L2=0,
		L1=1,
		M=2,
		R1=3,
		R2=4,
	};
  static const status_t blackParcel=1;
  static const status_t whiteParcel=0;
}

/*指令类型*/
enum command_t{
  errorCmd=0,
  moveCmd=1,
  rotateCmd=2,
  trimCmd=3,
  stopCmd=4,
  pushCurlingCmd=5,
  armRaiseCmd=6,
  detectCodeCmd=7,
  detectCodeAns=8,
  reservedCmd=9,
  testCmd=10,
};
/*通信结构体封装*/
struct message_t{
  command_t command;
  uint8_t argList[argCountMax];
};

/* Exported macro ------------------------------------------------------------*/

/*用于和respberry通信，双向*/
extern UART_HandleTypeDef huart2;
/*用于和电脑通信，单向传输调试信息*/
extern UART_HandleTypeDef huart3;

/* Exported functions prototypes ---------------------------------------------*/

/*自定义的调试输出函数，不能像printf一样输出更多类型的数值*/
extern HAL_StatusTypeDef printMsg(
	uint8_t *newMsg,uint8_t msgSize=msgSizeDefault,\
	UART_HandleTypeDef printUart=huart3,uint32_t timeout=timeoutDefault);
/*延迟函数，实现微秒级别的延迟功能,或许需要一些修饰符，例如__STATIC_FORCEINLINE*/
extern void Delay_us(uint16_t us);

/*初始化包括tracer,selector,patrol等类对象*/
extern status_t tracerInit(void);
/*解构包括tracer,selector,patrol等类对象*/
extern status_t tracerDestrcut(void);

/*TODO:蜂鸣器叫一声函数*/
extern void howlingWraiths(void);
extern void buzzerBeep(uint8_t intensity);

/* Private defines -----------------------------------------------------------*/

/*__USED is unable to download into the chip*/
/*__STATIC_FORCEINLINE is not so necessary*/

/*条件等待函数，在__timeout的时间内，如果__exp为0,则保持死循环。
	结束条件：__exp为1时，或者__timeout的时间到了
	TODO:使用函数指针完成定义*/
#define WAIT_FOR(__exp,__timeout)	do{\
	static const uint16_t delayCountMax=(__timeout)/waitforDelayTime;\
	uint16_t delayCount=0;\
	while((__exp)==0 && delayCount<delayCountMax){\
		HAL_Delay(waitforDelayTime);\
		delayCount++;\
	}\
}while(0)


/*调试用函数标记*/
#define __DEBUG
#define __COMMON
#define TRUE_DUDE (1)

#ifdef __cplusplus
}
#endif

#endif	/*__COMMON_H*/
