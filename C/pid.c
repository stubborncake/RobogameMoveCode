#include "pid.h"
#include "main.h"
 
#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }
 
void PID_init(pid_type_def *pid, int mode, int max_out, int max_iout,float Kp,float Ki,float Kd)
{
  if (pid == NULL )
  {
    return;
  }
  pid->mode = mode;
  pid->Kp = Kp;
  pid->Ki = Ki;
  pid->Kd = Kd;
  pid->max_out = max_out;
  pid->max_iout = max_iout;
  pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0;
  pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->out = 0;
}

int PID_calc(pid_type_def *pid, int ref, int set)
{
  if (pid == NULL)
  {
    return 0;
  }
  pid->error[2] = pid->error[1];
  pid->error[1] = pid->error[0];
  pid->set = set;
  pid->fdb = ref;
  pid->error[0] = set - ref;
	//Î»ÖÃPID
  if (pid->mode == 1)
  {
    pid->Pout = pid->Kp * pid->error[0];
    pid->Iout += pid->Ki * pid->error[0];
    pid->Dbuf[2] = pid->Dbuf[1];
    pid->Dbuf[1] = pid->Dbuf[0];
    pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
    pid->Dout = pid->Kd * pid->Dbuf[0];
    LimitMax(pid->Iout, pid->max_iout);
    pid->out = pid->Pout + pid->Iout + pid->Dout;
    LimitMax(pid->out, pid->max_out);
  }
	//ÔöÁ¿PID
  else if (pid->mode == 2)
  {
    pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
    pid->Iout = pid->Ki * pid->error[0];
    pid->Dbuf[2] = pid->Dbuf[1];
    pid->Dbuf[1] = pid->Dbuf[0];
    pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
    pid->Dout = pid->Kd * pid->Dbuf[0];
    pid->out += pid->Pout + pid->Iout + pid->Dout;
    LimitMax(pid->out, pid->max_out);
  }
  return pid->out;
}
 
void PID_clear(pid_type_def *pid)
{
  if (pid == NULL)
  {
    return;
  }
  pid->error[0] = pid->error[1] = pid->error[2] = 0;
  pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0;
  pid->out = pid->Pout = pid->Iout = pid->Dout = 0;
  pid->fdb = pid->set = 0;
}
