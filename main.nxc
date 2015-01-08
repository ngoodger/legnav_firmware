
#define MAX_START_DISTANCE 3.0
task main()
{
byte saveSensor1=0;
long t0, time;
t0 = CurrentTick();
  time = CurrentTick()-t0;
  
byte map[100][100]; //50mm x 50mm squares.  1=covered, 0=not covered.
 
SetSensor(IN_1,SENSOR_TOUCH);
OnFwd(OUT_AC, 30);

/* Drive forward something is hit or distance limit is reached */
while (saveSensor1 != 1 && magnitude<MAX_START_DISTANCE){
    saveSensor1=SENSOR_1;
    magnitude=sqrt(CurPose.x^2+CurPose.y^2);
  }
    
  /*Collision detected*/
  if (saveSensor1 == 1)
    RotateMotorEx(OUT_AC, 30, 10, 0, true, true);

   while (true)
 {
 if (SENSOR_1 == 1)
 {
    
 }
}

}
