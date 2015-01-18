#include "navigationTask.h"  

enum nav_states{STATE_INIT,STATE_FREE_BUMPER,STATE_TURN_L,STATE_DRIVE_FWD,STATE_TURN_R};

task nav_task()
{
  nav_states nav_state=STATE_INIT;  
  drive_fwd_oneshot=1;

  SetSensor(IN_1,SENSOR_TOUCH);
  switch(NavigationState){
    /* Drive forward something is hit or distance limit is reached */
    case STATE_INIT:
      OnFwd(OUT_AC, 30);
      while (save_sensor_bumper!= 1 && magnitude<MAX_START_DISTANCE){
        save_sensor_bumper=SENSOR_BUMPER;
        magnitude=sqrt(CurrentPose.x^2+CurrentPose.y^2);
      }
      nav_state=STATE_FREE_BUMPER;
      break;
    /*Reverse until touch sensor not activated*/
    case STATE_FREE_BUMPER:
      if (SENSOR_BUMPER== 1){
        OnRev(OUT_AC, 10);
        while(SENSOR_BUMPER==1)
          Wait(1);
      }
      nav_state=STATE_TURN_L;
      break;
    case STATE_TURN_L:
      RotateMotorEx(OUT_AC, 30, 10, 0, true, true); 
      nav_state=STATE_DRIVE_FWD;
      break;
    case STATE_DRIVE_FWD:
      OnFwdReg(OUT_AC,30,OUT_REGMODE_SYNC);
      save_sensor_bumper=SENSOR_BUMPER;
      if (drive_fwd_oneshot==1){
        InitialPose=CurrentPose;
        magnitude=0;
        drive_fwd_oneshot=0;
      }
      while (save_sensor_bumper!= 1 && magnitude<MAX_CREEP_DISTANCE){
        save_sensor_bumper=SENSOR_BUMPER;
        magnitude=sqrt((InitialPose.x-CurrentPose.x)^2+(InitialPose.y-CurrentPose.y^2);
      }
      /* Reset oneshot so it is ready for next iteration of this state */
      drive_fwd_oneshot=1;
      NavigationState=turnRight;
      break;
    case stateTurnRight:
      OnFwdReg(OUT_AC,30,OUT_REGMODE_SYNC);
      NavigationState=turnLeft;
      break;
    default:
      break;
  }
}
