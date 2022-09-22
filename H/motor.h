#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"
int Read_Encoder(int TIMX);//��ȡ��������encounter-]\-
//������ȫ�ǿ��������������򣬲������ٶ�
void FrontMove(void);//��ǰ�ƶ�
void BackMove(void);//����ƶ�
void LeftMove(void);//ˮƽ�����ƶ�
void RightMove(void);//ˮƽ�����ƶ�
void SkipMove(void);//���������ƻ���
void RightRotate(void);//������ת
void LeftRotate(void);//������ת
void StopMove(void);//�����ƶ�

void SetFourPWM(int a,int b,int c,int d);//��·PWM��ֵ���
void SetTarget(int a,int b,int c,int d);//�����ĸ�target��ֵ
//�����ǰ���������ٶȵĿ���
void Move(direction_t newdir,uint16_t newspeed);//���趨�ٶȺͷ���Move
/*���趨�ٶȺͷ���Trim��TrimIntensity��ʾtirm�ľ��ҳ̶�*/
void Trim(direction_t newdir,uint16_t newspeed,float TrimIntensity);
void Rotate(direction_t newdir,uint16_t newspeed);//���趨�ٶȺͷ���Rotate
void Stop(void);//�����ƶ�ֹͣ

void PidSet(void);//���ֽ���һ��PID���㲢���
#endif
