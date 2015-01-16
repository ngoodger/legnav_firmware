  enum NavigationStates {freeBumper,turnLeft,driveForward,turnRight};

NavigationStates NavigationState;  

 SetSensor(IN_1,SENSOR_TOUCH);
  OnFwd(OUT_AC, 30);

  /* Drive forward something is hit or distance limit is reached */
  while (saveSensor1 != 1 && magnitude<MAX_START_DISTANCE){
    saveSensor1=SENSOR_1;
    magnitude=sqrt(CurrentPose.x^2+CurrentPose.y^2);
  }

  switch(NavigationState)
  {
    case freeBumper:
      /*Collision detected*/
      if (saveSensor1 == 1){
        /*Reverse until touch sensor not activated*/
        OnRev(OUT_AC, 10);
        while(SENSOR_1==1)
          Wait(1);
      }
      NavigationState=turnLeft;
      break;
    case turnLeft:
      RotateMotorEx(OUT_AC, 30, 10, 0, true, true); 
      NavigationState=driveForward;
      break;
    case driveForward:
      OnFwdReg(OUT_AC,30,OUT_REGMODE_SYNC);
      saveSensor1=SENSOR_1;
      if (driveForwardOneshot){
        InitialPose=CurrentPose;
        magnitude=0;
      }
      while (saveSensor1 != 1 && magnitude<MAX_CREEP_DISTANCE){
        saveSensor1=SENSOR_1;
        magnitude=sqrt((InitialPose.x-CurrentPose.x)^2+(InitialPose.y-CurrentPose.y^2);
      }
      driveForwardOneshot;
      NavigationState=turnRight;
      break;
    case turnRight:
      OnFwdReg(OUT_AC,30,OUT_REGMODE_SYNC);
      NavigationState=turnLeft;
      break;
    default:
      break;
  }

