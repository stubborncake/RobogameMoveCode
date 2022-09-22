#ifndef PID_H
#define PID_H
//PID模式
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
 
extern pid_type_def motor1_speed;//轮子1的速度PID指针
extern pid_type_def motor1_position;//轮子1的位置PID指针
extern pid_type_def motor2_speed;//轮子1的速度PID指针
extern pid_type_def motor2_position;//轮子1的位置PID指针
extern pid_type_def motor3_speed;//轮子1的速度PID指针
extern pid_type_def motor3_position;//轮子1的位置PID指针
extern pid_type_def motor4_speed;//轮子1的速度PID指针
extern pid_type_def motor4_position;//轮子1的位置PID指针

extern float Kp_position1,Ki_position1,Kd_position1;//轮子1的位置PID三参数
extern float Kp_position2,Ki_position2,Kd_position2;//轮子2的位置PID三参数
extern float Kp_position3,Ki_position3,Kd_position3;//轮子3的位置PID三参数
extern float Kp_position4,Ki_position4,Kd_position4;//轮子4的位置PID三参数
extern float Kp_speed1,Ki_speed1,Kd_speed1;//轮子1的速度PID三参数
extern float Kp_speed2,Ki_speed2,Kd_speed2;//轮子2的速度PID三参数
extern float Kp_speed3,Ki_speed3,Kd_speed3;//轮子3的速度PID三参数
extern float Kp_speed4,Ki_speed4,Kd_speed4;//轮子4的速度PID三参数


extern void PID_init(pid_type_def *pid, int mode,  int max_out, int max_iout,float Kp,float Ki,float Kd);//PID初始化
extern int PID_calc(pid_type_def *pid, int ref, int set);//PID计算
extern void PID_clear(pid_type_def *pid);//PID清除
extern void PID_Value_Init(void);//四轮PID的赋值函数
#endif
