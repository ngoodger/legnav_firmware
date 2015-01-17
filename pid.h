#ifndef PID_H 
#define PID_H 

struct sPIDdata 
{
  float Kp;
  float Ki;
  float Kd;
  float input;
  float setpoint;
  float output;
  float lastProportionalError;
  float IntegralError;
  float lastTime 
}

int iteratePID(sPIDdata*PIDdata);
int initPID( sPIDdata*PIDdata);

#endif /* PID_H */
