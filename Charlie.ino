#include <CoDrone.h>
int Mode;
unsigned long StartTime;
int FLAG;

void setup()
{
  CoDrone.begin(115200);
  CoDrone.AutoConnect(NearbyDrone);
  CoDrone.DroneModeChange(Flight);
}
// jkhgkjhgjhgjhgjhgjhg
void loop()
{
  byte bt1 = digitalRead(11);
  byte bt4 = digitalRead(14);
  byte bt8 = digitalRead(18);

  if (bt1)
  {
    CoDrone.FlightEvent(Stop);
    FLAG = 0;
  }

  if (!bt1 && !bt4 && bt8)
  {
    Mode = Mode + 1;
    if (Mode > 2) 
    {
      Mode = 0;
    }
    CoDrone.Buzz(2000 + (Mode * 3000), 7);
    delay(200);
  }

  if (!bt1 && bt4 && !bt8)
  {
    FLAG = 1;
    StartTime = millis();
  }

  if (Mode == 0)
  {
    if (PAIRING == true && FLAG == 0)
    {
      YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));
      THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));
      ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));
      PITCH = CoDrone.AnalogScaleChange(analogRead(A6));

      CoDrone.Control(50);
    }
  }
  else if (Mode == 1)
  {
    if (FLAG == 1)
    {
      int CurrentTime = millis() - StartTime;

      if (CurrentTime < 1000)
      {
        THROTTLE = 70;
        CoDrone.Control(50);
      }
      else if (CurrentTime < 2500)
      {
        PITCH = 50;
        CoDrone.Control(50);
      }
      else if (CurrentTime < 3000)
      {
        CoDrone.FlightEvent(Stop);
      }
      else
      {
        FLAG = 0;
      }
    }
  }
  else
  {
    if (FLAG == 1)
    {
      int CurrentTime = millis() - StartTime;

      if (CurrentTime < 1000)
      {
        THROTTLE = 70;
        CoDrone.Control(50);
      }
      else if (CurrentTime < 2500)
      {
        CoDrone.Control(50);
      }
      else if (CurrentTime < 3000)
      {
        CoDrone.FlightEvent(Stop);
      }
      else
      {
        FLAG = 0;
      }
    }
  }
}
