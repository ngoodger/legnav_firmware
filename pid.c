#include "pid.h"

int init_pid(pid_data *pd,kp,ki,kd)
{
  pd->kp=kp;
  pd->ki=ki;
  pd->kd=kd; 
  pd->input=0;
  pd->setpoint=0;
  pd->output=0;
  pd->last_p_err=0;
  pd->i_err=0;
  pd->last_time=0;
}

int iterate_pid(pid_data *pd)
{
  static float p_err;
  static float d_err;
  static long cur_time;
  static long time_step;

  p_err=pd->input-pd->setpoint;
  cur_time=currentTick(); 
  time_step=cur_time-pd->last_time;
  p->i_err+=p_err*time_step;
  d_err=(p_err-pd->last_p_err)/time_step;
  pd->last_p_err=p_err;

  pd->output=pd->kp*p_err+
         pd->ki*i_err+
         pd->kd*d_err;

  return 0;
}


