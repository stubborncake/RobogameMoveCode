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

void SetFourPWM(int a,int b,int c,int d);//四路PWM定值输出
void SetTarget(int a,int b,int c,int d);//设置四个target数值
//下面是包含方向和速度的控制
void Move(direction_t newdir,uint16_t newspeed);
void Trim(direction_t newdir,uint16_t newspeed,float TrimIntensity);
void Rotate(direction_t newdir,uint16_t newspeed);
void Stop(void);
/*双环PID控制移动距离，其中distance参数，2808为轮子旋转一整圈,切记每次双环PID移动结束，要手动把DoubleBegin全局变量置零*/
void DoublePidMove(direction_t newdir,uint16_t distance);
/*双环PID控制旋转距离，其中distance参数，2808为轮子旋转一整圈,切记每次双环PID移动结束，要手动把DoubleBegin全局变量置零*/
void DoublePidRotate(direction_t newdir,uint16_t distance);
#endif
