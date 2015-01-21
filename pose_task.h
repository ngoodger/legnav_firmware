#ifndef POSE_TASK_H 
#define POSE_TASK_H 

  struct pose{
    float x; /*x position meters*/
    float y; /*y position meters*/
    float phi; /*rotation about z (radians)*/
  };

  /* global_cur_pose should be protected by mutex for correctness but max error is 1 iteration */
  extern pose global_cur_pose;

#endif /* POSE_TASK_H */


