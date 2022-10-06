
#ifndef __DEBUG_H
#define __DEBUG_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Private defines -----------------------------------------------------------*/

#define FATAL_ERROR (1)

#define STATIC_DEBUG (0) /*让小车在静止时进行调试*/

#define BACKUP_PLAN (0) /*备用方案*/

#if(BACKUP_PLAN==0)

    #define VISION_MODULE (1)

#elif (BACKUP_PLAN==1)

    #define EASY_CURLING_NODE_1 (2)
    #define HARD_CURLING_NODE_1 (3)
    #define HARD_CURLING_NODE_2 (5)

#elif(BACKUP_PLAN==2)

    extern uint8_t bp_easyCurlingNode;
    extern uint8_t bp_hardCurlingNode_1;
    extern uint8_t bp_hardCurlingNode_2;

#endif

#define __DEBUG /*调试用的函数或者变量标记*/

/* Exported types ------------------------------------------------------------*/

#if(BACKUP_PLAN == 1)
/*基准线上的节点名称*/
enum baselineNode_t
{
	lowerRightTurning = 0,
	easyCurlingRight_1 = EASY_CURLING_NODE_1,
	easyCurlingRight_2 = 2,
	launchRight = 3,
	hardCurling_1 = HARD_CURLING_NODE_1,
	easyCurlingMide = 4,
	hardCurling_2 = HARD_CURLING_NODE_2,
	launchLeft = 5,
	hardCurling_3 = 5,
	deadend = 6,
};
#elif(BACKUP_PLAN == 2)
enum baselineNode_t
{
	lowerRightTurning = 0,
	easyCurlingRight_1 = 1,
	easyCurlingRight_2 = 2,
	launchRight = 3,
	hardCurling_1 = 3,
	easyCurlingMide = 4,
	hardCurling_2 = 4,
	launchLeft = 5,
	hardCurling_3 = 5,
	deadend = 6,
};
#endif

/* Exported constants ------------------------------------------------------------*/

/*调试用的信息最大长度*/
static const uint8_t msgSizeDefault = 10;	
/* @brief 通信上面的默认超时毫秒常量*/
static const uint32_t timeoutDefault = 0x00ff;

/* Exported macro ------------------------------------------------------------*/

/*出现了致命问题，用于在基准线附近移动时脱线的标志*/
extern uint8_t flag_fatalError;

/*用于和电脑通信，单向传输调试信息*/
extern UART_HandleTypeDef huart3;

/* Exported functions prototypes ---------------------------------------------*/

/*	@breif 自定义的调试输出函数，不能像printf一样输出更多类型的数值
    @param newMsg: uint8型的字符信息
*/
HAL_StatusTypeDef printMsg(uint8_t *newMsg, uint8_t msgSize = msgSizeDefault, UART_HandleTypeDef printUart = huart3, uint32_t timeout = timeoutDefault);
/*	@breif 直接输出一段文字方便调试,似乎不支持函数重载
    @param newMsg: 标准字符串型
    @example  printText("hello"）;
*/
HAL_StatusTypeDef printText(const char *newMsg);

/*测试四个巡线模块是否正常工作*/
void testSensors(void);
/*测试节点识别算法能否工作*/
void testPatrol(void);
/*测试机械臂能否正常工作*/
void testDetectCurling(void);

#ifdef __cplusplus
}
#endif

#endif	/*__DEBUG_H*/
