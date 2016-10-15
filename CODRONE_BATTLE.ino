#include<CoDrone.h>
void setup()
{
  CoDrone.begin(115200);
  CoDrone.AutoConnect(NearbyDrone);
  CoDrone.DroneModeChange(Flight);
  CoDrone.BattleBegin(TEAM_RED);
}

void loop()
{
  CoDrone.BattleReceive();

  byte bt1 = digitalRead(11);
  byte bt4 = digitalRead(14);
  byte bt8 = digitalRead(18);

  if (bt1 && !bt4 && !bt8)
  { 
    CoDrone.FlightEvent(Stop);
  }

  if (!bt1 && !bt4 && bt8)
  {
    CoDrone.BattleShooting();
    CoDrone.Buzz(4000, 10);
    CoDrone.ButtonPreesHoldWait(18);
    delay(200);
  }

  if (!bt1 && bt4 && !bt8)
  {
    YAW = 100;
    CoDrone.Control(50);
    delay(100);
    YAW = -100;
    CoDrone.Control(50);
    delay(100);
    YAW = 100;
    CoDrone.Control(50);
    delay(100);
    YAW = -100;
    CoDrone.Control(50);
    delay(100);
  }
  
  YAW = CoDrone.AnalogScaleChange(analogRead(A3));
  THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));
  ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));
  PITCH = -1 * CoDrone.AnalogScaleChange(analogRead(A6));
  CoDrone.Control(SEND_INTERVAL);
}
