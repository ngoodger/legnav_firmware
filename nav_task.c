#include "vehicle.h"  
#include "pose_task.h"
#define MAX_START_DISTANCE 3.0
#define MAX_CREEP_DISTANCE 0.05

enum nav_states{STATE_INIT,STATE_FREE_BUMPER,STATE_TURN_L,STATE_DRIVE_FWD,STATE_TURN_R};

task nav_task()
{
  static nav_states nav_state=STATE_INIT;  
  static int drive_fwd_oneshot=1;
  static int save_sensor_bumper=1;
  static pose init_pose;
 
  SetSensor(IN_1,SENSOR_TOUCH);
  while(1){
    switch(nav_state){
      /* Drive forward something is hit or distance limit is reached */
      case STATE_INIT:
      OnFwd(OUT_AC, 30);
	while (save_sensor_bumper!= 1 && magnitude<MAX_START_DISTANCE){
	  save_sensor_bumper=SENSOR_BUMPER;
	  magnitude=sqrt(global_cur_pose.x^2+global_cur_pose.y^2);
	}
	nav_state=STATE_FREE_BUMPER;
	break;
      /* Reverse until touch sensor not activated */
      case STATE_FREE_BUMPER:
	if (SENSOR_BUMPER== 1){
	  OnRev(OUT_AC, 10);
	  while(SENSOR_BUMPER==1)
	    Wait(1);
	}
	nav_state=STATE_TURN_L;
	break;
      /* Turn left about center */
      case STATE_TURN_L:
	RotateMotorEx(OUT_AC, 30, 10, 0, true, true); 
	nav_state=STATE_DRIVE_FWD;
	break;
      /* Drive forward for MAX_CREEP_DISTANCE or until bumper is hit */
      case STATE_DRIVE_FWD:
	OnFwdReg(OUT_AC,30,OUT_REGMODE_SYNC);
	save_sensor_bumper=SENSOR_BUMPER;
	if (drive_fwd_oneshot==1){
	  init_pose=global_cur_pose;
	  magnitude=0;
	  drive_fwd_oneshot=0;
	}
	while (save_sensor_bumper!= 1 && magnitude<MAX_CREEP_DISTANCE){
	  save_sensor_bumper=SENSOR_BUMPER;
	  magnitude=sqrt((init_pose.x-global_cur_pose.x)^2+(init_pose.y-global_cur_pose.y^2);
	}
	/* Reset oneshot so it is ready for next iteration of this state */
	drive_fwd_oneshot=1;
	if (save_sensor_bumper=1)
	  nav_state=STATE_TURN_LEFT;
	else
	  nav_state=STATE_TURN_R;
	break;
      /* Turn right about center */
      case STATE_TURN_R:
	RotateMotorEx(OUT_AC, 30, -10, 0, true, true); 
	nav_state=STATE_DRIVE_FWD;
	break;
      default:
	break;
    }
  }
}
