#include "chassis.h"
#include "tracer.h"
#include "motor.h"
#include "connectivity.h"

/* Exported macro ------------------------------------------------------------*/
chassis_t chassis;

/* Private functions defines ---------------------------------------------*/


/*计算trim指令的参数：偏转方向,数值越小，偏转程度越强*/
inline float calcTrimDIntensity(int8_t trimDir){
    float trimIntensity=0;
    if(trimDir<0)
        trimDir=-trimDir;

    /*线性换算，上限为1,下限为lowBound*/
    /*线性换算的相关参数变量*/
    static const float lowBound=0.7;
    static const uint8_t trimDirMax=54;
    static const float linerUnit=(1-lowBound)/trimDirMax;

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

void chassis_t::move(direction_t newDir, uint8_t targetSpeed,uint32_t timeout)
{
    if (newDir == dirNowhere || newDir == dirAll)
        return;
    headingDir = newDir;
    moveSpeed = MIN(targetSpeed, speedMax);
    motorMove(newDir, moveSpeed);
    if(timeout>0){
        HAL_Delay(timeout);
    }
}

void chassis_t::moveDistance(direction_t newDir,uint16_t distance,uint32_t timeout){
    if (newDir == dirNowhere || newDir == dirAll)
        return;
    headingDir = newDir;
    onTrail=0;
    DoublePidMove(newDir,distance,timeout);
    onTrail=1;
}


void chassis_t::rotate(direction_t newDir, uint8_t targetSpeed,uint32_t timeout)
{
    if (headingDir != dirNowhere)
        return;
    if (newDir == dirRight || newDir == dirLeft)
    {
        rotateSpeed = MIN(targetSpeed, speedMax);
        motorRotate(newDir, rotateSpeed);
    }
    if(timeout>0){
        HAL_Delay(timeout);
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

void chassis_t::raiseArm(tracer_nsp::up_down_t newDir, uint8_t distance,uint32_t delayTime)
{
    using namespace tracer_nsp;

#ifndef __DEBUG
    sendCommadbyRaw(armRaiseCmd, newDir, distance);
    HAL_Delay(delayTime);
#else
    uint8_t distanceCalc = 0;
    /*调试时取消安全边界判断TODO*/
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
        /*测试机械臂抬升过程中的延迟情况，是否可以和下一步的移动同时进行TODO*/
    }
#endif
    if(delayTime==0){
        HAL_Delay(distance*300);
    }else{
        HAL_Delay(delayTime);
    }

}

status_t chassis_t::detectCode(uint8_t attemptTimes)const
{
    /*根据参数进行多次的条形码检测尝试*/
    HAL_Delay(respberryTime_1);
    /*由于摄像头图像的延迟，需要等待至少2s才能传回即使图像*/
    for(uint8_t i=0;i<attemptTimes;i++){
        sendCommadbyRaw(detectCodeCmd);
        HAL_Delay(detectInterval);
    }
    HAL_Delay(respberryTime_2);
    if(flagDetectCode==1){
        flagDetectCode=0;
        return 1;
    }else{
        return 0;
    }
}

void chassis_t::pushCurling()const
{
    HAL_GPIO_WritePin(PUSH_A_GPIO_Port,PUSH_A_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PUSH_B_GPIO_Port,PUSH_B_Pin,GPIO_PIN_SET);//注意此处方向
    HAL_Delay(pushCurlingWaitTime);		
    HAL_GPIO_WritePin(PUSH_A_GPIO_Port,PUSH_A_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PUSH_B_GPIO_Port,PUSH_B_Pin,GPIO_PIN_RESET);
}

status_t chassis_t::takeCurling(uint8_t argReserved)
{
    /*测试阶段跳过检测判断*/

#ifdef __DEBUG
    status_t flag=detectCode(5);
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
    if (onTrail == 0){
        move((direction_t)headingDir,moveSpeed);
        return;
    }

    /*前后两个巡线模块的权重*/
    static const float frontWeight=1.0;
    static const float backWeight=0.8;
    /*计算结果若为正，则向右偏转,大小表示大致的偏转角度*/
    int8_t trimFront=0;
    int8_t trimBack=0;
    float trimIntensity=0;
    /*取得前进方向的前后两个tracer的偏移数值*/
    direction_t opDir=oppositeDir(headingDir);  
    trimFront=(tracer[headingDir].calcTrimDir())*frontWeight;
    trimBack=(tracer[opDir].calcTrimDir())*backWeight;

    /*如果二者均为0，即完美的在线上，则直接退出*/
    if(trimFront==0 && trimBack==0){
        move((direction_t)headingDir,moveSpeed);
        return;
    }
    /*若二者之和为0，但是二者不为零，说明横向偏移了巡线*/
    if(trimFront+trimBack==0){
        trimIntensity=calcTrimDIntensity(trimFront/2);
        if(trimFront>0){
            trim(dirRight,trimIntensity);
        }else if(trimFront<0){
            trim(dirLeft,trimIntensity);
        }
        return;
    }
    
    /*一般情况，一遍偏移了巡线*/
    trimIntensity=calcTrimDIntensity(trimFront+trimBack);
    if(trimFront+trimBack>0){
        trim(dirRight,trimIntensity);
    }else{
        trim(dirLeft,trimIntensity);
    }
    
}
