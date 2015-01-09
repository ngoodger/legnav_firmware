

struct GainPID
{
  float Kp;
  float Ki;
  float Kd;
}

SteerPID (float input, float setpoint,GainPID ErrorGain)
{
  ProportionalError=input-setpoint;
  IntegralError+=IntegralError+ProportionalError*timeStep;
  DerivativeError=(ProportionalError-LastProportionalError)/timeStep;
  LastProportionalError=ProportionalError;

  SteerAction=ErrorGain.Kp*ProportionalError+
	      ErrorGain.Ki*IntegralError+
	      ErrorGain.Kd*DifferentialError;
}


