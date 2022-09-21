#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"
int Read_Encoder(int TIMX);
void FrontMove(void);//向前移动
void BackMove(void);//向后移动
void LeftMove(void);//水平向左移动
void RightMove(void);//水平向右移动
void SkipMove(void);//四轮滑动
void RightRotate(void);//向右旋转
void LeftRotate(void);//向左旋转
void StopMove(void);//四轮制动
void SetFourPWM(int a,int b,int c,int d);//四路PWM定值输出
#endif
