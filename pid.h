#ifndef PID_H 
#define PID_H 

  struct pid_data 
  {
    float kp;
    float ki;
    float kd;
    float input;
    float setpoint;
    float output;
    float last_p_err;
    float i_err;
    float lastTime 
  }

  int init_pid(pid_data *pd);
  int iterate_pid(pid_data *pd);

#endif /* PID_H */
