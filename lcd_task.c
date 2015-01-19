#include "pose_task.h"

task lcd_task()
{
  while(1){
    NumOut(10,LCD_LINE1,global_cur_pose.x);
    NumOut(10,LCD_LINE2,global_cur_pose.y);
    NumOut(10,LCD_LINE3,global_cur_pose.phi);
    Wait(100);
  }
}
