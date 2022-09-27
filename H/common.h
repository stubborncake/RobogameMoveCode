
#ifndef __COMMON_H
#define __COMMON_H
/* Private includes ----------------------------------------------------------*/
#include "main.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported constants ------------------------------------------------------------*/

static const uint8_t msgSizeDefault = 10; /*调试用的信息最大长度*/
static const uint8_t directionCount = 4;  /*这个世界有四个方向*/
static const uint8_t argCountMax = 3;	  /*指令的参数最多有3个*/

/*速度常量，待定TODO:*/
static const uint8_t superDash = 80;
static const uint8_t speedHigh = 30;
static const uint8_t speedLow = 15;
static const float trimIntensDefault = 0.7; /*微调时两侧轮子速度之比*/

/*预设各个阶段运动的大致时间，TODO:设定最大timeout,例如原地旋转90度的所需时间*/

static const uint32_t timeoutDefault = 0x00ff;	/*默认超时毫秒常量,这个默认时间是用在通信上面的，不是用在巡线上面的*/
static const uint32_t timeoutMax = 0x0ffffffff; /*最大超时参数，对于比赛时间而言即无穷，
													在输入过程中会因为计算量过大导致问题*/
static const uint16_t waitforDelayTime = 0x05;	/*waitFor函数的周期延时常量*/
namespace timeout_nsp
{
	static const uint32_t initTime = 100;
	static const uint32_t wasteLandTime = 24000;
	static const uint32_t rotateTime_90degree = 3500;
	static const uint32_t rotateTime_180degree = 7000;
	static const uint32_t decelerateTime = 3000;
	static const uint32_t curlingDepositeTime = 1500;
	static const uint32_t quiteLongTime = 10000;
}

/* Exported types ------------------------------------------------------------*/
/*状态类型*/

/*方向类型*/
enum direction_t
{
	dirFront = 0,
	dirRight = 1,
	dirLeft = 2,
	dirBack = 3,
	dirNowhere = 4,
	dirAll = 5,
};

/*状态类型，即布尔值，但是boolean是int型，太长了*/
typedef uint8_t status_t;

/*tracer相关的类型*/
namespace tracer_nsp
{
	enum on_off_t
	{
		off = 0,
		on = 1,
	};
	enum up_down_t
	{
		up = 1,
		down = 0,
	};
	enum hit_leave_t
	{
		leave = 0,
		hit = 1,
	};

	enum sensorOrder_t
	{
		L2 = 0,
		L1 = 1,
		M = 2,
		R1 = 3,
		R2 = 4,
	};
	static const status_t blackParcel = 1;
	static const status_t whiteParcel = 0;
}

/*指令类型*/
enum command_t
{
	errorCmd = 0,
	moveCmd = 1,
	rotateCmd = 2,
	trimCmd = 3,
	stopCmd = 4,
	pushCurlingCmd = 5,
	armRaiseCmd = 6,
	detectCodeCmd = 7,
	detectCodeAns = 8,
	reservedCmd = 9,
	testCmd = 10,
};

/*通信结构体封装*/
struct message_t
{
	command_t command;
	uint8_t argList[argCountMax];
};

/* Exported macro ------------------------------------------------------------*/

/*用于和respberry通信，双向*/
extern UART_HandleTypeDef huart2;
/*用于和电脑通信，单向传输调试信息*/
extern UART_HandleTypeDef huart3;
/*类对象和硬件是否初始化完毕，用于避免callback在未初始化之前进入中断*/
extern status_t flagInitReady;

/* Exported functions prototypes ---------------------------------------------*/

/*取二者较小的数值*/
/*自定义的调试输出函数，不能像printf一样输出更多类型的数值*/
HAL_StatusTypeDef printMsg(uint8_t *newMsg, uint8_t msgSize = msgSizeDefault, UART_HandleTypeDef printUart = huart3, uint32_t timeout = timeoutDefault);
/*直接输出一段文字方便调试,似乎不支持函数重载*/
HAL_StatusTypeDef printText(const char *newMsg);

/*延迟函数，实现微秒级别的延迟功能,或许需要一些修饰符，例如__STATIC_FORCEINLINE*/
void Delay_us(uint16_t us);

/*初始化PID相关的参数*/
status_t motorInit(void);
/*初始化包括tracer,selector,patrol等类对象*/
status_t tracerInit(void);
/*解构包括tracer,selector,patrol等类对象*/
status_t tracerDestrcut(void);

/* Private defines -----------------------------------------------------------*/

/*__USED is unable to download into the chip*/
/*__STATIC_FORCEINLINE is not so necessary*/

/*条件等待函数，在__timeout的时间内，如果__exp为0,则保持死循环。
结束条件：__exp为1时，或者__timeout的时间到了
TODO:使用函数指针完成定义*/
#define WAIT_FOR(__exp, __timeout)                                            \
do                                                                        \
{                                                                         \
	static const uint16_t delayCountMax = (__timeout) / waitforDelayTime; \
	uint16_t delayCount = 0;                                              \
	while ((__exp) == 0 && delayCount < delayCountMax)                    \
	{                                                                     \
		HAL_Delay(waitforDelayTime);                                      \
		delayCount++;                                                     \
	}                                                                     \
} while (0)

#define MIN(__a,__b) ((__a)<(__b)?(__a):(__b))
#define MAX(__a,__b) ((__a)>(__b)?(__a):(__b))

#define __DEBUG		/*调试用的函数或者变量标记*/
#define BACKUP_PLAN /*备用方案*/
#define __COMMON
#define TRUE_DUDE (1) /*无意义的傻懒子定义*/

#ifdef __cplusplus
}
#endif

#endif /*__COMMON_H*/
