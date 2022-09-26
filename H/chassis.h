
#ifndef __CHASSIS_H
#define __CHASSIS_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/


/* Exported constants ------------------------------------------------------------*/
static const uint8_t speedMaxDefault=90;
static const uint8_t armHeightDefault=0;

/* Exported functions prototypes ---------------------------------------------*/

/* Class defines -----------------------------------------------------------*/

class chassis_t{
private:
    const uint8_t speedMax;
    const uint8_t armHeightMax;

    uint8_t moveSpeed;
    uint8_t rotateSpeed;
    uint8_t armHeight;

public:
    direction_t headingDir;
    status_t onTrail;

    chassis_t();
    ~chassis_t();

    void move(direction_t newDir,uint8_t targetSpeed=speedHigh);
    void rotate(direction_t newDir,uint8_t targetSpeed=speedHigh);
    void trim(direction_t newDir,uint8_t trimIntensity=trimIntensDefault);
    void stop(uint8_t stopIntensity=1);
    void takeCurling(uint8_t argReserved=0);
    void raiseArm(tracer_nsp::up_down_t newDir, uint8_t distance);
    void detectCode(uint8_t attemptTimes=1);
    void pushCurling(uint8_t argReserved=0);
    /*旋转指定角度*/
    __DEBUG void rotatebyDegree(direction_t newDir,uint8_t degree); 

    void halt(void);
};


/* Exported macro ------------------------------------------------------------*/

extern chassis_t chassis;

/* Private defines -----------------------------------------------------------*/

#define __CHASSIS

#ifdef __cplusplus
}
#endif

#endif	/*__CHASSIS_H*/
