#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"
int Read_Encoder(int TIMX);//读取编码器的encounter-]\-
//下面完全是控制驱动电流方向，不控制速度
void FrontMove(void);//向前移动
void BackMove(void);//向后移动
void LeftMove(void);//水平向左移动
void RightMove(void);//水平向右移动
void SkipMove(void);//四轮无限制滑动
void RightRotate(void);//向右旋转
void LeftRotate(void);//向左旋转
void StopMove(void);//四轮制动

void SetFourPWM(int a,int b,int c,int d);//四路PWM定值输出
void SetTarget(int a,int b,int c,int d);//设置四个target数值
//下面是包含方向和速度的控制
void Move(direction_t newdir,uint16_t newspeed);//按设定速度和方向Move
/*按设定速度和方向Trim，TrimIntensity表示tirm的剧烈程度*/
void Trim(direction_t newdir,uint16_t newspeed,float TrimIntensity);
void Rotate(direction_t newdir,uint16_t newspeed);//按设定速度和方向Rotate
void Stop(void);//四轮制动停止

void PidSet(void);//四轮进行一次PID计算并输出
#endif
