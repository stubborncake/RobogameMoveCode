#include "chassis.h"
#include "motor.h"
#include "connectivity.h"

/* Exported macro ------------------------------------------------------------*/
chassis_t chassis;

/* Public functions defines ---------------------------------------------*/
chassis_t::chassis_t() : speedMax(speedMaxDefault), armHeightMax(armHeightDefault)
{
    armHeight = 0;
    stop();
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
    if (headingDir == dirNowhere)
        return;
    if (onTrail == 0)
        return;
    // TODO:根据前进方向的不同发送不同的trim指令:
    if (newDir == dirRight || newDir == dirLeft)
    {
        motorTrim(newDir, moveSpeed, trimIntensity); /*根据上一次的move来觉得这次的微调的速度*/
    }else if(newDir==dirFront){
        motorMove(dirFront,moveSpeed);
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

void chassis_t::detectCode(uint8_t attemptTimes)
{
    /*根据参数进行多次的条形码检测尝试*/
    sendCommadbyRaw(detectCodeCmd);
}

void chassis_t::pushCurling(uint8_t argReserved)
{
    /*推壶操作*/
}

void chassis_t::takeCurling(uint8_t argReserved)
{
    /*TODO:将detectCode 和 takeCurling整合到一起，参数表示是高难区还是低难区*/
}

__DEBUG void chassis_t::buzz(uint8_t argReseved){

}

__DEBUG void chassis_t::rotatebyDegree(direction_t newDir, uint8_t degree)
{
}

void chassis_t::halt(void)
{
    motorStop();
    /*TODO:添加停机相关的操作，目前看来还没啥需要的*/
}
