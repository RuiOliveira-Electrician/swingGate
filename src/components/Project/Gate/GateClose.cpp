#include "Gate.h"

bool gateOpenBySensorInfrared(String &serial)
{
  if (commandSensorInfrared() && memorySensorInfraredActivated == 0)
  {
    gateStop(serial);
    delay(1000);

    setVar_onIO("releOpen", 1);
    setVar_onIO("releOpenLeft", 1);
    setVar_onIO("releOpenRight", 1);

    if (timerGate.getTimePassedByScale() > timeToGate)
    {
      timerGate.force();
    }
    else
    {
      if (memoryGateStop == true)
      {
        timerGate.edit(timeToGate - memoryGateTime + 2, Timer::Scale::second, false);
      }
      else
      {
        timerGate.edit(timerGate.getTimePassedByScale() + 1, Timer::Scale::second, false);
      }

      timerGate.reset();
    }
    memorySensorInfraredActivated = 1;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir pelo SensorInfrared");
    serial += F("\n");
  }
  if (memorySensorInfraredActivated == 1)
  {
    if (timerGate.hasEndedDelay())
    {
      setVar_onIO("releOpen", 0);
      setVar_onIO("releOpenLeft", 0);
      setVar_onIO("releOpenRight", 0);
      configGate = ConfigGate::open;
      memorySensorInfraredActivated = 0;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao aberto pelo SensorInfrared");
      serial += F("\n");
      return false;
    }
    return true;
  }
  return false;
}

void gateClose(String &serial)
{
  if (!gateOpenBySensorInfrared(serial))
  {
    if (!isWaitingTimeToCloseOrOppenGate())
    {
      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += getCommandDebug(configGate);
      serial += F("\n");
    }
    switch (configGate)
    {
    case ConfigGate::setClose:
      setVar_onIO("releOpen", 0);
      timerToEarlyGate.reset();
      configGate = ConfigGate::closeLeft;
      break;
    case ConfigGate::closeLeft:
      setVar_onIO("releOpenLeft", 1);
      timerToEarlyGate.reset();
      configGate = ConfigGate::waitTimeToCloseInBetween;
      break;
    case ConfigGate::waitTimeToCloseInBetween:
      if (timerToEarlyGate.hasEndedDelay())
      {
        configGate = ConfigGate::closeRight;
      }
      break;
    case ConfigGate::closeRight:
      setVar_onIO("releOpenRight", 1);
      timerGate.reset();
      configGate = ConfigGate::waitTimeToCloseLeftIsDone;
      break;
    case ConfigGate::waitTimeToCloseLeftIsDone:
      if (timerGate.hasEndedDelay())
      {
        configGate = ConfigGate::closeLeftIsDone;
      }
      break;
    case ConfigGate::closeLeftIsDone:
      setVar_onIO("releOpenLeft", 0);
      timerToEarlyGate.reset();
      configGate = ConfigGate::waitTimeToCloseRightIsDone;
      break;
    case ConfigGate::waitTimeToCloseRightIsDone:
      if (timerToEarlyGate.hasEndedDelay())
      {
        configGate = ConfigGate::closeRightIsDone;
      }
      break;
    case ConfigGate::closeRightIsDone:
      setVar_onIO("releOpenRight", 0);
      configGate = ConfigGate::saveEepromIsClose;
      break;
    case ConfigGate::saveEepromIsClose:
      gateStop(serial);
      configGate = ConfigGate::close;
      EEPROM.write(Memory_Gate, ConfigGate::close);
      break;
    }
  }
}

void gateStop(String &serial)
{
  setVar_onIO("releOpenLeft", 0);
  setVar_onIO("releOpenRight", 0);
  delay(1000);
  setVar_onIO("releOpen", 0);

  getDebugAdress(serial, __FILE__, __func__, __LINE__);
  serial += F("Portao a parado");
  serial += F("\n");
}
