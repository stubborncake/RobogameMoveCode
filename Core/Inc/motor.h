#ifndef MOTOR_H
#define MOTOR_H
#include "common.h"

int Read_Encoder(int TIMX);
//下面完全是控制驱动电流方向，不控制速度
void FrontMove(void);//向前移动
void BackMove(void);//向后移动
void LeftMove(void);//水平向左移动
void RightMove(void);//水平向右移动
void SkipMove(void);//四轮滑动
void RightRotate(void);//向右旋转
void LeftRotate(void);//向左旋转
void StopMove(void);//四轮制动

/* Exported functions prototypes ---------------------------------------------*/

/*更新PWM输出波*/
void updatePWM(void);
void SetFourPWM(int a,int b,int c,int d);//四路PWM定值输出
void SetTarget(int a,int b,int c,int d);//设置四个target数值

//下面是包含方向和速度的控制
void motorMove(direction_t newdir,uint16_t newspeed);
/*newdir1代表行进方向;newdir2,left逆时针,right顺时针*/
void motorTrim(direction_t newdir1,direction_t newdir2,uint16_t newspeed,float TrimIntensity);
void motorRotate(direction_t newdir,uint16_t newspeed);
void motorStop(void);

/*双环PID控制移动距离，其中distance参数，2808为轮子旋转一整圈,EstimatedTime为预估时间,切记每次双环PID移动要预留充足的EstimatedTime*/
void DoublePidMove(direction_t newdir,uint16_t distance,uint32_t EstimatedTime);
/*双环PID控制旋转距离，其中distance参数，2808为轮子旋转一整圈,EstimatedTime为预估时间,切记每次双环PID移动要预留充足的EstimatedTime*/
void DoublePidRotate(direction_t newdir,uint16_t distance,uint32_t EstimatedTime);
/*无巡线旋转180度*/
void Rotate180degree(direction_t newDir=dirRight);

/*发射相关*/
void PushCurlingTrimBack(direction_t newdir);
void PushCurlingTrimFront(direction_t newdir);
void PushCurlingMoveFrontorBack(direction_t newdir);
void PushCurlingAllPeriod(direction_t newdir);

/*extern variables---------------------------------------------------*/


/*unknown global variables, set by @stubborncake for motor related functions*/
extern int DoubleBegin;
extern int Again;

extern int target1,target2,target3,target4;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;




#endif