#include "pose_task.h"
#include "vehicle.h"
#define PI 3.141593

/*Initial pose is zero*/
static pose global_cur_pose={0.0,0.0,0.0};

task poseEstimator_task()
{
  static long cur_enc_l=MotorRotationCount(MOTOR_LEFT); 
  static long cur_enc_r=MotorRotationCount(MOTOR_RIGHT);
  static long last_enc_l=cur_enc_l; 
  static long last_enc_r=cur_enc_r; 
  static long delta_enc_l=0; 
  static long delta_enc_r=0; 
  static float tmp=0.0;
  static float delta_l_m=0.0;
  static float delta_r_m=0.0;
  static float magnitude=0.0;

  while (true)
  {
    /*Wait for encoder value change (Movement)*/
    while (cur_enc_l==last_enc_l && cur_enc_r==last_enc_r){
      Wait(1);
      cur_enc_l= MotorRotationCount(MOTOR_LEFT);
      cur_enc_r= MotorRotationCount(MOTOR_RIGHT);
    }

    delta_enc_l=cur_enc_l-last_enc_l;   
    delta_enc_r=cur_enc_r-last_enc_r;

    /*Reverse sign of deltaAngleRight if zero crossing*/   
    if (delta_enc_l!=0){
      if ((last_enc_l>180 && cur_enc_l<180) || 
          (last_enc_l<180 && cur_enc_l>180))
        delta_enc_l=-1*delta_enc_l;      
    }
    /*Reverse sign of deltaAngleRight if zero crossing*/   
    if (delta_enc_r!=0){
      if ((last_enc_r>180 && cur_enc_r<180) || 
          (last_enc_r<180 && cur_enc_r>180))
        delta_enc_r=-1*delta_enc_r;      
    }

    tmp=delta_enc_l/(360*WHEEL_GEAR_RATIO);
    delta_meters_l=PI*WHEEL_DIAMETER*tmp; 
    tmp=delta_enc_r/(360*WHEEL_GEAR_RATIO);
    delta_meters_r=PI*WHEEL_DIAMETER*tmp;

    /*Approximately update the pose in global coordinate system */
    /*Assumes small angle so turn is line rather than arc.*/
    /*Magnitude of the movement*/
    magnitude=(delta_meters_l+delta_meters_r)/2.0;
    /*Calculate change in angle phi*/
    global_cur_pose.phi+=(delta_meters_l-delta_meters_r)/WHEELBASE;
    /*Calculate x movement based on the new angle phi*/
    global_cur_pose.x+=magnitude*cos(global_cur_pose.phi);
    /*Calculate y movement based on the new angle phi*/
    global_cur_pose.y+=magnitude*sin(global_cur_pose.phi); 

    /*Update prevAngle with curAngle for next iteration */
    prevAngleLeft=curAngleLeft;
    prevAngleRight=curAngleRight;
  }
}
