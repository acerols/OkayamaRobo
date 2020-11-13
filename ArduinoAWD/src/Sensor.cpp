#include <Arduino.h>
#include <Sensor.hpp>

int getUSSLeft()
{
  int len = analogRead(USSensorLeft);
  return (len * 3);
}

int getUSSRight()
{
  int len = analogRead(USSensorRight);
  return (len * 3);
}

int getBSFront()
{
    return analogRead(BSensorFront);
}

int getBSLeft()
{
    return analogRead(BSensorLeft);
}

int getBSRight()
{
    return analogRead(BSensorRight);
}

int getBSRear()
{
    return analogRead(BSensorRear);
}
