#include "Gate.h"

void checkGateStopedWhenOpening(String &serial)
{
  if (isgateOpening())
  {
    gateStop(serial);

    if (timerGate.getTimePassedByScale() > timeToGate)
    {
      timerGate.force();
    }
    else
    {
      memoryGateTime = timerGate.getTimePassedByScale();
      timerGate.edit(memoryGateTime + 1, Timer::Scale::second, false);
      timerGate.reset();
    }
    configGate = ConfigGate::gateStopedWhenOpening;
  }
  else if (isGateStopedWhenOpening())
  {
    memoryGateStop = true;
    configGate = ConfigGate::setClose;
  }
}