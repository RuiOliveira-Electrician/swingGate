#include "Gate.h"

Timer timerGate(timeToGate, Timer::Scale::second, true); // (*Um Segundo)

Timer timerToEarlyGate(timeToEarlyGate, Timer::Scale::second, true); // (*Um Segundo)

Timer timerGateCloseAutomatic(timeToGateCloseAutomatic, Timer::Scale::minute, false); // (*Um Minuto)

Timer timerGateBlocked(timeToGateBlocked, Timer::Scale::second, true); // (*Um Segundo)

Timer timerCommandClickGateBlocked(1, Timer::Scale::second, true); // (*Um Segundo)

uint8_t memorySensorInfraredActivated = 0;

uint8_t memoryGate = EEPROM.read(Memory_Gate);
boolean memoryCommand = false;
boolean memoryGateStop = false;
uint8_t memoryGateTime = 0;
uint8_t memoryGateBlocked = 0, contGateBlocked = 0;

void handleGate(String &serial)
{
  gateBlocked(serial);
  if (!isgateBlocked())
  {
    if (commandSensorInfrared())
    {
      timerGateCloseAutomatic.reset();
    }
    if ((commandBoard() || commandRadio() || isgateReadyToOpenAutomatic()) && memoryCommand == false)
    {
      if (isgateReadyToOpenAutomatic())
      {
        getDebugAdress(serial, __FILE__, __func__, __LINE__);
        serial += F("Portao fechado pelo tempo maximo");
        serial += F("\n");
      }
      timerGateCloseAutomatic.reset();
      memoryCommand = true;
      if (isgateOpening())
      {
        if (isgateStoped())
        {
          memoryGateStop = true;
          memoryGate = 51;
        }
        else if (!isgateStoped())
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
          memoryGate = 20;
        }
      }

      if (isgateClose())
      {
        memoryGateStop = false;
        memoryGate = 1;
        timerGate.edit(timeToGate, Timer::Scale::second, false);
        timerGate.force();
        gateOpen(serial);
      }
      if (isgateOpen())
      {
        memoryGateStop = false;
        memoryGate = 51;
        timerGate.edit(timeToGate, Timer::Scale::second, false);

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
    memoryGate = _memoryGate + 20;
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
    if (timerToEarlyGate.hasEndedDelay())
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
    if (timerGate.hasEndedDelay())
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
    if (timerToEarlyGate.hasEndedDelay())
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
      if (timerToEarlyGate.hasEndedDelay())
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
      if (timerGate.hasEndedDelay())
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
      if (timerToEarlyGate.hasEndedDelay())
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

void gateBlocked(String &serial)
{
  if ((commandBoard() || commandRadio()) && contGateBlocked == 0 && timerCommandClickGateBlocked.hasEndedDelay())
  {
    contGateBlocked = 1;
    timerGateBlocked.reset();
    timerCommandClickGateBlocked.reset();
  }
  else if ((commandBoard() || commandRadio()) && contGateBlocked >= 1 && timerCommandClickGateBlocked.hasEndedDelay())
  {
    timerCommandClickGateBlocked.reset();
    contGateBlocked++;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("portao cont: ");
    serial += contGateBlocked;
    serial += F("\n");

    if (contGateBlocked > 5)
    {
      memoryGateBlocked = 1;
      gateStop(serial);
      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("portao bolqueado");
      serial += F("\n");
    }
  }
  else if (timerGateBlocked.hasEndedDelay() && contGateBlocked <= 5 && contGateBlocked != 0)
  {
    contGateBlocked = 0;
    memoryGateBlocked = 0;
    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("portao resetado do bolqueio");
    serial += F("\n");
  }
}

bool isgateOpen()
{
  if (memoryGate == 50)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool isgateClose()
{
  if (memoryGate == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
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
bool isgateStoped()
{
  if (memoryGate == 20)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool isgateBlocked()
{
  return memoryGateBlocked;
}
bool isgateReadyToOpenAutomatic()
{
  return timerGateCloseAutomatic.hasEndedDelay() && (isgateOpen() || isgateStoped());
}
