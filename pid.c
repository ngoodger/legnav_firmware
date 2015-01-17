#include "pid.h"

int initPID(sPIDdata*PIDdata,Kp,Ki,Kd)
{
  PIDdata->Kp=Kp;
  PIDdata->Ki=Ki;
  PIDdata->Kd=Kd; 
  PIDdata->input=0;
  PIDdata->setpoint=0;
  PIDdata->output=0;
  PIDdata->lastProportionalError=0;
  PIDdata->IntegralError=0;
  PIDdata->lastTime=0;
}

int iteratePID(sPIDdata*PIDdata)
{
  float ProportionalError;
  float DerivativeError;
  long currentTime;

  ProportionalError=PIDdata->input-PIDdata->setpoint;
  currentTime=currentTick(); 
  timeStep=currentTime-lastTime;
  IntegralError+=ProportionalError*timeStep;
  DerivativeError=(ProportionalError-PIDdata->lastProportionalError)/timeStep;
  PIDdata->lastProportionalError=ProportionalError;

  output=PIDdata->Kp*ProportionalError+
         PIDdata->Ki*IntegralError+
         PIDdata->Kd*DifferentialError;

  return output;
}


