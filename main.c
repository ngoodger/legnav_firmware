
#define MAX_START_DISTANCE 3.0
#define MAX_CREEP_DISTANCE 0.05
task main()
{
  byte saveSensor1=0;
  long t0, time;

  t0 = CurrentTick();
  time = CurrentTick()-t0;
  
  byte map[100][100]; //50mm x 50mm squares.  1=covered, 0=not covered.

}
