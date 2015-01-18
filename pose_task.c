#include "pose_task.h"

/*Initial pose is zero*/
pose global_cur_pose={0.0,0.0,0.0};

task poseEstimator_task()
{
  long cur_enc_l=MotorRotationCount(MOTOR_LEFT); 
  long cur_enc_r=MotorRotationCount(MOTOR_RIGHT);
  long last_enc_l=cur_enc_l; 
  long last_enc_r=cur_enc_r; 
  long delta_enc_l=0; 
  long delta_enc_r=0; 
  float tmp=0.0;
  float delta_l_m=0.0;
  float deltaRightMeters=0.0;
  float magnitude=0.0;

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
        (last_enc_l<180 && cur_enc_l>180) )
      delta_enc_l=-1*delta_enc_l;      
  }
  /*Reverse sign of deltaAngleRight if zero crossing*/   
  if (delta_enc_r!=0){
    if ((last_enc_r>180 && cur_enc_r<180) || 
        (last_enc_r<180 && cur_enc_r>180) )
      delta_enc_r=-1*delta_enc_r;      
  }

  tmp=delta_enc_l/(360*WHEEL_GEAR_RATIO);
  delta_meters_l=PI*WHEEL_DIAMETER*deltaLeft; 
  tmp=delta_enc_r/(360*WHEEL_GEAR_RATIO);
  delta_meters_r=PI*WHEEL_DIAMETER*deltaRight;

  /*Approximately update the pose in global coordinate system */
  /*Assumes small angle so turn is line rather than arc.*/
  /*Magnitude of the movement*/
  magnitude=(delta_meters_l+delta_meters_l)/2.0;

  /*Calculate change in angle phi*/
  currentPose.phi+=(deltaRightMeters-deltaRLeftMeters)/WHEELBASE;
  /*Calculate x movement based on the new angle phi*/
  currentPose.x+=magnitude*cos(phi);
  /*Calculate y movement based on the new angle phi*/
  currentPose.y+=magnitude*sin(phi); 
  /*-------------------------------------------------------------*/

  /*Update prevAngle with curAngle for next iteration */
  prevAngleLeft=curAngleLeft;
  prevAngleRight=curAngleRight;
  }
}
