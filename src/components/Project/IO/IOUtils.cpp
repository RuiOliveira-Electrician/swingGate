#include "IO.h"

uint8_t commandRadio()
{
  return digitalRead(BUTTONRADIO);
}
uint8_t commandBoard()
{
  return !digitalRead(BUTTONBOARD);
}
uint8_t commandSensorInfrared()
{
  return !digitalRead(GATEINFRARED);
}