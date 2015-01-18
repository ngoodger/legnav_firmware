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
  float deltaLeft=0.0;
  float deltaRight=0.0;
  float deltaLeftMeters=0.0;
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

  deltaLeft=deltaAngleLeft/(360*WHEEL_GEAR_RATIO);
  deltaLeftMeters=PI*WHEEL_DIAMETER*deltaLeft; 
  deltaRight=deltaAngleRight/(360*WHEEL_GEAR_RATIO);
  deltaRightMeters=PI*WHEEL_DIAMETER*deltaRight;

  /*Approximately update the pose---------------------------------*/
  /*Assumes small angle so turn is line rather than arc.*/
  /*Magnitude of the movement*/
  magnitude=(deltaRightMeters+deltaRLeftMeters)/2.0;

  Acquire(mutexCurrentPose);
  /*Calculate change in angle phi*/
 currentPose.phi+=(deltaRightMeters-deltaRLeftMeters)/WHEELBASE;
  /*Calculate x movement based on the new angle phi*/
 currentPose.x+=magnitude*cos(phi);
  /*Calculate y movement based on the new angle phi*/
 currentPose.y+=magnitude*sin(phi); 
   /*-------------------------------------------------------------*/
  Release(mutexCurrentPose);

  /*Update prevAngle with curAngle for next iteration */
  prevAngleLeft=curAngleLeft;
  prevAngleRight=curAngleRight;
  }
}
