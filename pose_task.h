#ifndef POSETASK_H 
#define POSETASK_H 

#endif /* POSETASK_H */

struct pose
{
  float x; /*x position meters*/
  float y; /*y position meters*/
  float phi /*rotation about z (radians)*/
}

int getCurrentPose(Pose *returnPose);
