long Alpha(pose fromPose,pose toPose)
long leftMotorAction=0;
long rightMotorAction=0;

{
    long Alpha
    xError=toPose.x-toPose.x;
    yError=toPose.y-toPose.y;
    Alpha=atan2(xError/yError);
    return Alpha;
}

PIDcontroller(&steerPID)
if (commonMotorAction+differentialMotorAction>100.0)
  commonMotorAction=100.0-differentialMotorAction;
if (commonMotorAction+differentialMotorAction<-100.0)
  commonMotorAction=-100.0-differentialMotorAction;

/*Calculate Left and right Motor speeds. 0.5 Rounds to integer.*/
leftMotorAction=commonMotorAction+differentialMotorAction+0.5;
rightMotorAction=commonMotorAction-differentialMotorAction+0.5;			
if (leftMotorAction>100.0)
  leftMotorAction=100;
if (rightMotorAction<-100.0)
  rightMotorAction=-100;
OnFwd(OUT_A,leftMotorAction);
OnFwd(OUT_C,rightMotorAction);



