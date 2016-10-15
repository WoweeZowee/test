#include <CoDrone.h>
unsigned long StartTime;
 
void setup()
{
  CoDrone.begin(115200);
  CoDrone.AutoConnect(NearbyDrone);
  StartTime = millis();
}
void loop()
{
  byte bt1 = digitalRead(11);
  unsigned long CurrentTime = millis() - StartTime;
 
  if ( CurrentTime < 1000){
  THROTTLE = 100;
  CoDrone.Control();
  }
 
  else if (CurrentTime < 2500) {
  THROTTLE = -100;
  CoDrone.Control();
  }
 
  if (bt1)
  {
    CoDrone.FlightEvent(Stop);
  } 
}
