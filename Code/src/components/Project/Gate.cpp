#include "Gate.h"

NewTimer timerGate(timeToGate, "Second", 1); // (*Um Segundo)

NewTimer timerToEarlyGate(timeToEarlyGate, "Second", 1); // (*Um Segundo)

uint8_t memorySensorInfraredActivated = 0;

uint8_t memoryGate = EEPROM.read(Memory_Gate);
boolean memoryCommand = false;
boolean memoryGateStop = false;
uint8_t memoryGateTime = 0;

void handleGate(String &serial)
{
  if ((commandBoard() || commandRadio()) && memoryCommand == false)
  {
    memoryCommand = true;
    if (isgateOpening())
    {
      if (memoryGate == 20)
      {
        memoryGateStop = true;
        memoryGate = 51;
      }
      else if (memoryGate != 20)
      {
        gateStop(serial);

        if (timerGate.getTimerPassed() > timeToGate)
        {
          timerGate.force();
        }
        else
        {
          memoryGateTime = timerGate.getTimerPassed();
          timerGate.edit(memoryGateTime + 1, "Second");
          timerGate.reset();
        }
        memoryGate = 20;
      }
    }

    if (memoryGate == 0)
    {
      memoryGateStop = false;
      memoryGate = 1;
      timerGate.edit(timeToGate, "Second");
      timerGate.force();
      gateOpen(serial);
    }
    if (memoryGate == 50)
    {
      memoryGateStop = false;
      memoryGate = 51;
      timerGate.edit(timeToGate, "Second");

      timerGate.force();
      gateClose(serial);
    }

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Radio clicado");
    serial += F("\n");
  }
  else if ((!commandBoard() && !commandRadio()) && memoryCommand == true)
  {
    memoryCommand = false;
  }

  if (isgateOpening())
  {
    gateOpen(serial);
  }
  else if (isgateClosing())
  {
    gateClose(serial);
  }
}

bool gateOpenBySensorInfrared(String &serial, uint8_t _memoryGate)
{
  if (commandSensorInfrared() && memorySensorInfraredActivated == 0)
  {
    setVar_onIO("releOpenLeft", 0);
    setVar_onIO("releOpenRight", 0);
    delay(1000);

    setVar_onIO("releOpen", 1);
    setVar_onIO("releOpenLeft", 1);
    setVar_onIO("releOpenRight", 1);

    if (timerGate.getTimerPassed() > timeToGate)
    {
      timerGate.force();
    }
    else
    {
      if (memoryGateStop == true)
      {
        timerGate.edit(timeToGate - memoryGateTime + 2, "Second");
      }
      else
      {
        timerGate.edit(timerGate.getTimerPassed() + 1, "Second");
      }

      timerGate.reset();
    }
    memoryGate = _memoryGate + 20;
    memorySensorInfraredActivated = 1;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir pelo SensorInfrared");
    serial += F("\n");
  }
  if (memorySensorInfraredActivated == 1)
  {
    if (timerGate.checkTimer())
    {
      setVar_onIO("releOpen", 0);
      setVar_onIO("releOpenLeft", 0);
      setVar_onIO("releOpenRight", 0);
      memoryGate = _memoryGate;
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

void gateOpen(String &serial)
{
  switch (memoryGate)
  {
  case 1:
    setVar_onIO("releOpen", 1);
    timerToEarlyGate.reset();
    memoryGate = 2;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir");
    serial += F("\n");
    break;
  case 2:
    setVar_onIO("releOpenRight", 1);
    timerToEarlyGate.reset();
    memoryGate = 3;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir direto");
    serial += F("\n");
    break;
  case 3:
    if (timerToEarlyGate.checkTimer())
    {
      memoryGate = 4;
    }
    break;
  case 4:
    setVar_onIO("releOpenLeft", 1);
    timerGate.reset();
    memoryGate = 5;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir esquerdo");
    serial += F("\n");
    break;
  case 5:
    if (timerGate.checkTimer())
    {
      memoryGate = 6;
    }
    break;
  case 6:
    setVar_onIO("releOpenRight", 0);
    timerToEarlyGate.reset();
    memoryGate = 7;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao aberto direito");
    serial += F("\n");
    break;
  case 7:
    if (timerToEarlyGate.checkTimer())
    {
      memoryGate = 8;
    }
    break;
  case 8:
    setVar_onIO("releOpenLeft", 0);
    memoryGate = 9;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao aberto esquerdo");
    serial += F("\n");
    break;
  case 9:
    gateStop(serial);
    memoryGate = 50;
    EEPROM.write(Memory_Gate, 50);

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao aberto");
    serial += F("\n");
    break;
  }
}

void gateClose(String &serial)
{
  if (!gateOpenBySensorInfrared(serial, 50))
  {
    switch (memoryGate)
    {
    case 51:
      setVar_onIO("releOpen", 0);
      timerToEarlyGate.reset();
      memoryGate = 52;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar");
      serial += F("\n");
      break;
    case 52:
      setVar_onIO("releOpenLeft", 1);
      timerToEarlyGate.reset();
      memoryGate = 53;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar esquerdo");
      serial += F("\n");
      break;
    case 53:
      if (timerToEarlyGate.checkTimer())
      {
        memoryGate = 54;
      }
      break;
    case 54:
      setVar_onIO("releOpenRight", 1);
      timerGate.reset();
      memoryGate = 55;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar direto");
      serial += F("\n");
      break;
    case 55:
      if (timerGate.checkTimer())
      {
        memoryGate = 56;
      }
      break;
    case 56:
      setVar_onIO("releOpenLeft", 0);
      timerToEarlyGate.reset();
      memoryGate = 57;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao fechado esquerdo");
      serial += F("\n");
      break;
    case 57:
      if (timerToEarlyGate.checkTimer())
      {
        memoryGate = 58;
      }
      break;
    case 58:
      setVar_onIO("releOpenRight", 0);
      memoryGate = 59;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao fechado direito");
      serial += F("\n");
      break;
    case 59:
      gateStop(serial);
      memoryGate = 0;
      EEPROM.write(Memory_Gate, 0);

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao fechado");
      serial += F("\n");
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

bool isgateOpening()
{
  if (memoryGate > 0 && memoryGate < 50)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool isgateClosing()
{
  if (memoryGate > 50)
  {
    return true;
  }
  else
  {
    return false;
  }
}