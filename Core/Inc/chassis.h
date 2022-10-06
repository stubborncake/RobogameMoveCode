
#ifndef __CHASSIS_H
#define __CHASSIS_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/


/* Exported constants ------------------------------------------------------------*/
static const uint8_t speedMaxDefault=200;
static const uint8_t armHeightDefault=10;

/* Exported functions prototypes ---------------------------------------------*/

/* Class defines -----------------------------------------------------------*/

class chassis_t{
private:
    /*速度上限，由于pid调参的局限性，行进速度不能过快*/
    const uint8_t speedMax;
    /*机械臂最高高度*/
    const uint8_t armHeightMax;
    /*当前预设移动速度*/
    uint8_t moveSpeed;
    /*当前预设旋转角速度*/
    uint8_t rotateSpeed;
    /*当前预估的机械臂高度*/
    uint8_t armHeight;

public:
    /*当前行进方向*/
    uint8_t headingDir;
    /*是否在巡线上,为1则使能巡线模块并返回trim指令*/
    status_t onTrail;
    /*默认构造函数和解构函数*/
    chassis_t();
    ~chassis_t();
    /* @breif 向指定方向直线前进
        @param newDir: 移动方向
        @param targetSpeed: 目标移动速度，会逐渐加速到该速度
        @param timeout: 最大移动时间，非0则在该时间内将主进程挂起
    */
    void move(direction_t newDir=dirFront,uint8_t targetSpeed=speedHigh,uint32_t timeout=0);
    /*直线定距离移动,TODO是否有必要在完成后停顿一段时间*/
    void moveDistance(direction_t newDir,uint16_t distance,uint32_t timeout=moveDistanceTime);
    /*原地旋转*/
    void rotate(direction_t newDir,uint8_t targetSpeed=speedHigh,uint32_t timeout=0);
    /*旋转指定角度，目前未实现*/
    __DEBUG void rotatebyDegree(direction_t newDir=dirLeft,uint8_t degree=180); 

    /*行进过程中微调方向*/
    void trim(direction_t newDir,uint8_t trimIntensity=trimIntensDefault);
    /*停止运动（移动或者旋转）*/
    void stop(uint32_t delayTime=timeoutDefault);
    /*停机*/
    void halt(void);
    /*  @brief 升高或者降低机械臂,无冰壶为0，有冰壶为5，发射时为7.
        @param distance: 机械臂移动距离，默认抬起高度为5，高难区冰壶高度为2 TODO
        @note 在抬起过程中不能再次发送该指令，否则会冲突
    */
    void raiseArm(tracer_nsp::up_down_t newDir, uint8_t distance,uint32_t delayTime=0);
    /*检测条形码或者冰壶颜色*/
    status_t detectCode(uint8_t attemptTimes=1)const;
    /*  @brief 推壶操作
        @param timeout: 在推出机械臂后等待时间，过长会导致气瓶漏气
    */
    void pushCurling()const;


    /*取壶操作，目前看来不是很必要*/
    __DEBUG status_t takeCurling(uint8_t argReserved=0);
    /*调整方位，整合了各个方向和当前节点的判断*/
    __DEBUG void adjustDirection(void);

    /*TODO:蜂鸣器鸣叫*/
    __DEBUG void buzz(uint8_t argReseved=0);

};


/* Exported macro ------------------------------------------------------------*/

extern chassis_t chassis;

/* Private defines -----------------------------------------------------------*/

#define __CHASSIS

#ifdef __cplusplus
}
#endif

#endif	/*__CHASSIS_H*/

