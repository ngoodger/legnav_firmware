
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

float PIDcontroller(sPIDdata*PIDdata)
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


