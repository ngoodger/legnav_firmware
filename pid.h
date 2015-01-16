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

float iteratePID(sPIDdata*PIDdata);
#endif /* PID_H */
