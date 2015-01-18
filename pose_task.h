#ifndef POSE_TASK_H 
#define POSE_TASK_H 

  #define MOTOR_RIGHT OUT_A
  #define MOTOR_LEFT OUT_B
  #define WHEEL_GEAR_RATIO 10.0
  #define WHEEL_DIAMETER 0.03 
  #define WHEELBASE 0.15
  #define PI 3.141593

  struct pose
  {
    float x; /*x position meters*/
    float y; /*y position meters*/
    float phi /*rotation about z (radians)*/
  }

  int getCurrentPose(Pose *returnPose);

#endif /* POSE_TASK_H */


