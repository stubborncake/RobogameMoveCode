#ifndef PID_H
#define PID_H
/*-----------------------------------typedefines export---------------------------------------*/
e
//PID模式enum
enum PID_MODE
{
  PID_POSITION = 0,
  PID_DELTA
};
 //PID指针定义
typedef struct
{
  int mode;//1为位置PID，2为增量PID
  //PID 三参数
  float Kp;
  float Ki;
  float Kd;
 
  int max_out;  //最大输出
  int max_iout; //最大积分输出
 
  int set;
  int fdb;
 
  int out;
  int Pout;
	int Iout;
  int Dout;
  int Dbuf[3];  //微分项 0最新 1上一次 2上上次
  int error[3]; //误差项 0最新 1上一次 2上上次
 
} pid_type_def;
 /*-----------------------------------functions export prototypes---------------------------------------*/
extern void PID_init(pid_type_def *pid, int mode,  int max_out, int max_iout,float Kp,float Ki,float Kd);//PID初始化
extern int PID_calc(pid_type_def *pid, int ref, int set);//PID计算
extern void PID_clear(pid_type_def *pid);//PID清除
 
#endif
