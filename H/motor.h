#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"
int Read_Encoder(int TIMX);
void FrontMove(void);//��ǰ�ƶ�
void BackMove(void);//����ƶ�
void LeftMove(void);//ˮƽ�����ƶ�
void RightMove(void);//ˮƽ�����ƶ�
void SkipMove(void);//���ֻ���
void RightRotate(void);//������ת
void LeftRotate(void);//������ת
void StopMove(void);//�����ƶ�
void SetFourPWM(int a,int b,int c,int d);//��·PWM��ֵ���
#endif
