#include "chassis.h"
#include "tracer.h"
#include "motor.h"
#include "connectivity.h"

/* Exported macro ------------------------------------------------------------*/
chassis_t chassis;

/* Private functions defines ---------------------------------------------*/


/*计算trim指令的参数：偏转方向,数值越小，偏转程度越强*/
inline float calcTrimDIntensity(int8_t trimDir){
    /*线性换算的相关参数变量*/
    static const float lowBound=0.8;
    static const uint8_t trimDirMax=6;
    static const float linerUnit=(1-lowBound)/trimDirMax;

    float trimIntensity=0;
    if(trimDir<0)
        trimDir=-trimDir;
    /*线性换算，上限为1,下限为lowBound*/
    trimIntensity=lowBound+trimDir*linerUnit;

    return trimIntensity;
}

/* Public functions defines ---------------------------------------------*/
chassis_t::chassis_t() : speedMax(speedMaxDefault), armHeightMax(armHeightDefault)
{
    armHeight = 0;
    headingDir=dirNowhere;
    onTrail=0;
}

chassis_t::~chassis_t()
{
    halt();
}

void chassis_t::move(direction_t newDir, uint8_t targetSpeed)
{
    if (newDir == dirNowhere || newDir == dirAll)
        return;
    headingDir = newDir;
    moveSpeed = MIN(targetSpeed, speedMax);
    motorMove(newDir, moveSpeed);
}

void chassis_t::moveDistance(direction_t newDir,uint16_t distance,uint32_t timeout){
    if (newDir == dirNowhere || newDir == dirAll)
        return;
    headingDir = newDir;
    onTrail=0;
    DoublePidMove(newDir,distance,timeout);
    onTrail=1;
}


void chassis_t::rotate(direction_t newDir, uint8_t targetSpeed)
{
    if (headingDir != dirNowhere)
        return;
    if (newDir == dirRight || newDir == dirLeft)
    {
        rotateSpeed = MIN(targetSpeed, speedMax);
        motorRotate(newDir, rotateSpeed);
    }
}

void chassis_t::trim(direction_t newDir, uint8_t trimIntensity)
{
    /*删掉这些判读TODO*/
    if (headingDir == dirNowhere)
        return;
    if (onTrail == 0)
        return;
    if (newDir == dirRight || newDir == dirLeft)
    {
        motorTrim((direction_t)headingDir,newDir, moveSpeed, trimIntensity); /*根据上一次的move来觉得这次的微调的速度*/
    }else if(newDir==dirFront){
        motorMove((direction_t)headingDir,moveSpeed);
    }
}

void chassis_t::stop(uint32_t delayTime)
{
    headingDir = dirNowhere;
    moveSpeed = 0;
    rotateSpeed = 0;
    motorStop();
    HAL_Delay(delayTime);
}

void chassis_t::halt(void)
{
    stop();
    buzz();
    HAL_Delay(1000);
    flagInitReady=0;
    /*TODO:添加停机相关的操作，目前看来还没啥需要的*/
}

void chassis_t::raiseArm(tracer_nsp::up_down_t newDir, uint8_t distance)
{
    using namespace tracer_nsp;
    uint8_t distanceCalc = 0;
    if (newDir == up)
    {
        distanceCalc = MIN(distance, armHeightMax - armHeight);
        armHeight += distanceCalc;
    }
    else if (newDir == down)
    {
        distanceCalc = MIN(distance, armHeight);
        armHeight -= distanceCalc;
    }
    if (distanceCalc != 0)
    {
        sendCommadbyRaw(armRaiseCmd, newDir, distanceCalc);
    }
}

status_t chassis_t::detectCode(uint8_t attemptTimes)const
{
    /*根据参数进行多次的条形码检测尝试*/
    for(int i=0;i<attemptTimes;i++){
        sendCommadbyRaw(detectCodeCmd);
        HAL_Delay(detectInterval);
    }
    if(flagDetectCode==1){
        flagDetectCode=0;
        return 1;
    }else{
        return 0;
    }
}

void chassis_t::pushCurling(uint8_t argReserved)const
{    
    /*推壶操作*/
    HAL_GPIO_WritePin(PUSH_GPIO_Port,PUSH_Pin,GPIO_PIN_SET);
    HAL_Delay(pushCurlingTime);
    HAL_GPIO_WritePin(PUSH_GPIO_Port,PUSH_Pin,GPIO_PIN_RESET);    
}

status_t chassis_t::takeCurling(uint8_t argReserved)
{
    /*测试阶段跳过检测判断*/
    raiseArm(up,5);/*上下的enum类型和距离待定TODO*/
    HAL_Delay(2000);
    return 1;

#ifndef __DEBUG
    status_t flag=detectCode();
    if(flag==1){
        raiseArm(up,5);
    }
    return flag;
#endif
}

__DEBUG void chassis_t::buzz(uint8_t argReseved){

}

__DEBUG void chassis_t::rotatebyDegree(direction_t newDir, uint8_t degree)
{
    if(degree==180 && newDir==dirLeft){
        Rotate180degree();
    }
}

__DEBUG void chassis_t::adjustDirection(void){
    /*如果没有在前进或者没有在巡线上，则退出*/
    if (headingDir == dirNowhere)
        return;
    if (onTrail == 0)
        return;

    /*计算结果若为正，则向右偏转,大小表示大致的偏转角度*/
    int8_t trimDir=0;
    float trimIntensity=0;
    /*取得前进方向的前后两个tracer*/
    direction_t opDir=oppositeDir(headingDir);  

    trimDir+=tracer[headingDir].calcTrimDir();
    trimDir+=tracer[opDir].calcTrimDir();
    trimIntensity=calcTrimDIntensity(trimDir);

    if(trimDir==0){
        move((direction_t)headingDir,moveSpeed);
    }else if(trimDir>0){
        trim(dirRight,trimIntensity);
    }else if(trimDir<0){
        trim(dirLeft,trimIntensity);
    }
}
