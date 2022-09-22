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
 
extern pid_type_def motor1_speed;
extern pid_type_def motor1_position;
extern pid_type_def motor2_speed;
extern pid_type_def motor2_position;
extern pid_type_def motor3_speed;
extern pid_type_def motor3_position;
extern pid_type_def motor4_speed;
extern pid_type_def motor4_position;

extern float Kp_position1,Ki_position1,Kd_position1;
extern float Kp_position2,Ki_position2,Kd_position2;
extern float Kp_position3,Ki_position3,Kd_position3;
extern float Kp_position4,Ki_position4,Kd_position4;
extern float Kp_speed1,Ki_speed1,Kd_speed1;
extern float Kp_speed2,Ki_speed2,Kd_speed2;
extern float Kp_speed3,Ki_speed3,Kd_speed3;
extern float Kp_speed4,Ki_speed4,Kd_speed4;


extern void PID_init(pid_type_def *pid, int mode,  int max_out, int max_iout,float Kp,float Ki,float Kd);//PID初始化
extern int PID_calc(pid_type_def *pid, int ref, int set);//PID计算
extern void PID_clear(pid_type_def *pid);//PID清除
extern void PID_Value_Init(void);
#endif
