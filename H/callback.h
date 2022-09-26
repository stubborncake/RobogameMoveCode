
#ifndef __CALLBACK_H
#define __CALLBACK_H

/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/* Exported functions prototypes ---------------------------------------------*/

/*输出所有巡线模块的数值*/
__DEBUG void printSensorValues(void);

/*TIM6的中断响应函数*/
extern void tim6_callback(void);
/*TIM6的50个周期的的中断响应函数*/
extern void tim6_50period_callback(void);

/*UART2的接收中断函数,
    目前的设计只需要接收detectCodeAns指令即可，即是否收到正确冰壶检测的响应*/
extern void USART2_IdleCallback(uint8_t *buff,uint8_t size);

/* Private defines -----------------------------------------------------------*/

#define __CALLBACK


#ifdef __cplusplus
}
#endif

#endif	/*__CALLBACK_H*/
