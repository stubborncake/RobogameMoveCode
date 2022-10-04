
#ifndef __COMMON_H
#define __COMMON_H
/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "debug.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/* Exported constants ------------------------------------------------------------*/

	static const uint8_t msgSizeDefault = 10; /*调试用的信息最大长度*/
	static const uint8_t directionCount = 4;  /*这个世界有四个方向*/
	static const uint8_t argCountMax = 3;	  /*指令的参数最多有3个*/
	static const uint8_t baselineNodeCount=6; /*基准线上的节点数，包括最左端的T字口*/
	/*时间常量单位一律为毫秒ms*/
	/*速度常量，待定TODO:*/

	/* @brief 在中间无巡线阶段的冲刺速度*/
	static const uint8_t superDash = 120;
	/* @brief 一般行进速度*/
	static const uint8_t speedHigh = 80;
	/* @brief 在检测到节点后的减速运动；定距离移动的速度*/
	static const uint8_t speedLow = 30;
	/* @brief 微调时两侧轮子速度之比的默认值*/
	static const float trimIntensDefault = 0.8;
	
	/* @brief 通信上面的默认超时毫秒常量*/
	static const uint32_t timeoutDefault = 0x00ff; 
	/* @brief 最大超时参数，对于比赛时间而言即无穷*/
	static const uint32_t timeoutMax = 0x0fffffff; 
	/* @brief waitFor函数的周期延时常量*/													
	static const uint16_t waitforDelayTime = 0x04;
	/* @brief 定距离移动的默认移动时间*/
	static const uint32_t moveDistanceTime=2000;
	/* @brief 检测冰壶颜色的发送指令时间间隔*/
	static const uint32_t detectInterval=300;
	/* @brief 发射冰壶时，继电器的给高压时间*/
	static const uint32_t pushCurlingTime=600;
	namespace timeout_nsp
	{
		static const uint32_t initTime = 100;
		static const uint32_t startLineWaitingTime =5000;
		static const uint32_t leavingStartLineTime=5000;
		static const uint32_t upperTurningTime = 13000;
		static const uint32_t guideLineTime=1800;
		static const uint32_t wasteLandTime = 15000;
		static const uint32_t rotateTime_90degree = 3500;
		static const uint32_t rotateTime_180degree = 7000;
		static const uint32_t decelerateTime = 2000;
		static const uint32_t curlingDepositeTime = 1500;
		static const uint32_t quiteLongTime = 15000;
		static const uint32_t curlingIntervalTime=3000;
		static const uint32_t passingForkTime=1000;
		static const uint32_t easyCurlingTakeTime=2800;
		static const uint32_t hardCurlingTakeTime=3800;

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
		enum up_down_t	/*由于和机械臂的通信，保留最初的设计，历史遗留*/
		{
			up = 0,
			down = 1,
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
		errorCmd = 0,/*在使用*/
		moveCmd = 1, 
		rotateCmd = 2,
		trimCmd = 3,
		stopCmd = 4,
		pushCurlingCmd = 5,
		armRaiseCmd = 6, 	/*在使用*/
		detectCodeCmd = 7,	/*在使用*/
		detectCodeAns = 8,	/*在使用*/
		reservedCmd = 9,
		testCmd = 10,
	};

#if (BACKUP_PLAN==0)
	/*基准线上的节点名称*/
	enum baselineNode_t{
		lowerRightTurning=0,
		easyCurlingRight_1=1,
		easyCurlingRight_2=2,		
		launchRight=3,
		hardCurling_1=3,
		easyCurlingMide=4,
		hardCurling_2=4,
		launchLeft=5,
		hardCurling_3=5,
		deadend=6,
	};

#else
	/*基准线上的节点名称*/
	enum baselineNode_t{
		lowerRightTurning=0,
		easyCurlingRight_1=EASY_CURLING_NODE_1,
		easyCurlingRight_2=2,		
		launchRight=3,
		hardCurling_1=HARD_CURLING_NODE_1,
		easyCurlingMide=4,
		hardCurling_2=HARD_CURLING_NODE_2,
		launchLeft=5,
		hardCurling_3=5,
		deadend=6,
	};



#endif

	/*通信结构体封装,未使用*/
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
	/*是否检测到了正确的冰壶*/
	extern status_t flagDetectCode;
	/* Exported functions prototypes ---------------------------------------------*/

	/*取得当前方向的反方向*/
	direction_t oppositeDir(uint8_t newDir);
	/*取得当前方向的右边的方向*/
	direction_t getRightDir(direction_t newDir);
	/*取得当前方向的左边的方向*/
	direction_t getLeftDir(direction_t newDir);

	/*	@breif 自定义的调试输出函数，不能像printf一样输出更多类型的数值
		@param newMsg: uint8型的字符信息
	*/
	HAL_StatusTypeDef printMsg(uint8_t *newMsg, uint8_t msgSize = msgSizeDefault, UART_HandleTypeDef printUart = huart3, uint32_t timeout = timeoutDefault);
	/*	@breif 直接输出一段文字方便调试,似乎不支持函数重载
		@param newMsg: 标准字符串型
		@example  printText("hello"）;		
	*/
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

/*	@brief 条件等待函数，在不满足条件时将主进程挂起
	@param __exp: 关于巡线的表达式，为0则挂起主进程，为1时退出挂起状态
	@param __timeout: 最大挂起时间，到时间后无条件退出挂起状态,必须为const
	@todo 使用函数指针实现该效果
*/
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

#define MIN(__a, __b) ((__a) < (__b) ? (__a) : (__b))

#define MAX(__a, __b) ((__a) > (__b) ? (__a) : (__b))

#define __COMMON

#ifdef __cplusplus
}
#endif

#endif /*__COMMON_H*/
