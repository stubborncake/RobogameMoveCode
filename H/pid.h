#ifndef PID_H
#define PID_H
//PIDģʽ
enum PID_MODE
{
  PID_POSITION = 0,
  PID_DELTA
};
 //PIDָ�붨��
typedef struct
{
  int mode;//1Ϊλ��PID��2Ϊ����PID
  //PID ������
  float Kp;
  float Ki;
  float Kd;
 
  int max_out;  //������
  int max_iout; //���������
 
  int set;
  int fdb;
 
  int out;
  int Pout;
	int Iout;
  int Dout;
  int Dbuf[3];  //΢���� 0���� 1��һ�� 2���ϴ�
  int error[3]; //����� 0���� 1��һ�� 2���ϴ�
 
} pid_type_def;
 
extern void PID_init(pid_type_def *pid, int mode,  int max_out, int max_iout,float Kp,float Ki,float Kd);//PID��ʼ��
extern int PID_calc(pid_type_def *pid, int ref, int set);//PID����
extern void PID_clear(pid_type_def *pid);//PID���
 
#endif
