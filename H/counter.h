
#ifndef __COUNTER_H
#define __COUNTER_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/


/* Exported constants ------------------------------------------------------------*/

static const uint8_t intervalDefault=1;

/* Exported functions prototypes ---------------------------------------------*/


/* Class defines -----------------------------------------------------------*/

class counter_t
{
private:
    /*每次计数的增加值，由于硬件设置为1ms，故每次加一即可，不再动用该预设值*/
    const uint8_t interval;
    /*是否计数到达预设值*/
    status_t flag_timeout;
    /*当前计数器是否开启*/
    status_t flag_working;
    /*预设计数值，即等待时常*/
    uint32_t prescaler;
    /*计数变量*/
    uint32_t tick;

    /*清空当前所有变量数值*/
    void clearData(void);    
    /*计数器达到阈值*/
    status_t timeUp(void);


public:
    /*默认的构造函数和解构函数*/
    counter_t();
    ~counter_t();
    /*开启计数器*/
    void setup(uint32_t newTimeout);
    /*关闭计数器*/
    void turnOff(void);
    /*更新计数器*/
    void updateDate(void);
};

/* Exported macro ------------------------------------------------------------*/
extern counter_t counter;

/* Private defines -----------------------------------------------------------*/

#define __COUNTER

#ifdef __cplusplus
}
#endif

#endif	/*__COUNTER_H*/
