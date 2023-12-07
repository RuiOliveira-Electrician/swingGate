#include "Gate.h"

void gateOpen(String &serial)
{
  if (!isWaitingTimeToCloseOrOppenGate())
  {
    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += getCommandDebug(configGate);
    serial += F("\n");
  }
  switch (configGate)
  {
  case ConfigGate::setOpen:
    setVar_onIO("releOpen", 1);
    timerToEarlyGate.reset();
    configGate = ConfigGate::openRight;
    break;
  case ConfigGate::openRight:
    setVar_onIO("releOpenRight", 1);
    timerToEarlyGate.reset();
    configGate = ConfigGate::waitTimeToOpenInBetween;
    break;
  case ConfigGate::waitTimeToOpenInBetween:
    if (timerToEarlyGate.hasEndedDelay())
    {
      configGate = ConfigGate::openLeft;
    }
    break;
  case ConfigGate::openLeft:
    setVar_onIO("releOpenLeft", 1);
    timerGate.reset();
    configGate = ConfigGate::waitTimeToOpenRightIsDone;
    break;
  case ConfigGate::waitTimeToOpenRightIsDone:
    if (timerGate.hasEndedDelay())
    {
      configGate = ConfigGate::openRightIsDone;
    }
    break;
  case ConfigGate::openRightIsDone:
    setVar_onIO("releOpenRight", 0);
    timerToEarlyGate.reset();
    configGate = ConfigGate::waitTimeToOpenLeftIsDone;
    break;
  case ConfigGate::waitTimeToOpenLeftIsDone:
    if (timerToEarlyGate.hasEndedDelay())
    {
      configGate = ConfigGate::openLeftIsDone;
    }
    break;
  case ConfigGate::openLeftIsDone:
    setVar_onIO("releOpenLeft", 0);
    configGate = ConfigGate::saveEepromIsOpen;
    break;
  case ConfigGate::saveEepromIsOpen:
    gateStop(serial);
    configGate = ConfigGate::open;
    EEPROM.write(Memory_Gate, ConfigGate::open);
    break;
  }
}