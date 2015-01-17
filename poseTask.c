#include "poseTask.h"
#define MOTOR_RIGHT OUT_A
#define MOTOR_LEFT OUT_B
#define WHEEL_GEAR_RATIO 10.0
#define WHEEL_DIAMETER 0.03 
#define WHEELBASE 0.15
#define PI 3.141593

/*Initial pose is zero*/
posescurrentPose={0.0,0.0,0.0};
mutex mutexCurrentPose;

int getCurrentPose(Pose *returnPose)
{
  Acuquire(mutexCurrentPose);
  memcpy(returnPose,CurrentPose);
  Release(mutexCurrentPose);
}
task poseEstimator_task()
{
  long curAngleLeft=MotorRotationCount(MOTOR_LEFT); 
  long curAngleRight=MotorRotationCount(MOTOR_RIGHT);
  long prevAngleLeft=curAngleLeft; 
  long prevAngleRight=curAngleRight; 
  long deltaAngleLeft=0; 
  long deltaAngleRight=0; 
  float deltaLeft=0.0;
  float deltaRight=0.0;
  float deltaLeftMeters=0.0;
  float deltaRightMeters=0.0;
  float magnitude=0.0;

  while (true)
  {
  /*Wait for encoder value change (Movement)*/
  while (curAngleLeft==prevAngleLeft && curAngleRight==prevAngleRight){
      Wait(1);
    curAngleLeft = MotorRotationCount(MOTOR_LEFT);
    curAngleRight = MotorRotationCount(MOTOR_RIGHT);
  }

  deltaAngleLeft=curAngleLeft-prevAngleLeft;   
  deltaAngleRight=curAngleRight-prevAngleRight;

  /*Reverse sign of deltaAngleRight if zero crossing*/   
  if (deltaAngleLeft!=0){
    if ((prevAngleLeft>180 && curAngleLeft<180) || 
        (prevAngleLeft<180 && curAngleLeft>180) )
      deltaAngleLeft=-1*deltaAngleLeft;      
  }
  /*Reverse sign of deltaAngleRight if zero crossing*/
  if (deltaAngleRight!=0){
    if ((prevAngleRight>180 && curAngleRight<180) ||  
        (prevAngleRight<180 && curAngleRight>180) )
      deltaAngleRight=-1*deltaAngleRight;      
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
