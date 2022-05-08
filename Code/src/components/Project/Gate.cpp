#include "Gate.h"

NewTimer timerToOpenGate(19, "Second", 1);  // (*Um Segundo)
NewTimer timerToCloseGate(19, "Second", 1); // (*Um Segundo) //Tento verificar se a porta foi fechada

NewTimer timerToEarlyGate(1, "Second", 1);                   // (*Um Segundo)
NewTimer timerToOpenGateWithSensorInfrared(20, "Second", 1); // (*Um Segundo)

uint8_t memorySensorInfraredActivated = 0;

uint8_t memoryGate = EEPROM.read(Memory_Gate);

void handleGate(String &serial)
{
  if (!isgateOpening() && !isgateClosing())
  {
    if (commandBoard() || commandRadio())
    {
      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Radio clicado");
      serial += F("\n");
      if (memoryGate == 50)
      {
        memoryGate = 51;
        timerToCloseGate.force();
        gateClose(serial);
      }
      if (memoryGate == 0)
      {
        memoryGate = 1;
        timerToOpenGate.force();
        gateOpen(serial);
      }
    }
  }
  else if (isgateOpening())
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
    setVar_onIO("releOpen", 1);
    setVar_onIO("releOpenLeft", 1);
    setVar_onIO("releOpenRight", 1);
    DEBUG_LN(timerToCloseGate.getTimerPassed());

    if (timerToCloseGate.getTimerPassed() > 20)
    {
      timerToOpenGateWithSensorInfrared.force();
    }
    else
    {
      timerToOpenGateWithSensorInfrared.edit(timerToCloseGate.getTimerPassed() + 1, "Second");
      timerToOpenGateWithSensorInfrared.reset();
    }
    memoryGate = _memoryGate + 20;
    memorySensorInfraredActivated = 1;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir pelo SensorInfrared");
    serial += F("\n");
  }
  if (memorySensorInfraredActivated == 1)
  {
    if (timerToOpenGateWithSensorInfrared.checkTimer())
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
  if (memoryGate == 1)
  {
    setVar_onIO("releOpen", 1);
    timerToEarlyGate.reset();
    memoryGate = 2;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir");
    serial += F("\n");
  }
  else if (memoryGate == 2)
  {
    setVar_onIO("releOpenRight", 1);
    timerToEarlyGate.reset();
    memoryGate = 3;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir direto");
    serial += F("\n");
  }
  else if (memoryGate == 3 && timerToEarlyGate.checkTimer())
  {
    memoryGate = 4;
  }
  else if (memoryGate == 4)
  {
    setVar_onIO("releOpenLeft", 1);
    timerToOpenGate.reset();
    memoryGate = 5;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao a abrir esquerdo");
    serial += F("\n");
  }
  else if (memoryGate == 5 && timerToOpenGate.checkTimer())
  {
    memoryGate = 6;
  }
  else if (memoryGate == 6)
  {
    setVar_onIO("releOpenRight", 0);
    timerToEarlyGate.reset();
    memoryGate = 7;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao aberto direito");
    serial += F("\n");
  }
  else if (memoryGate == 7 && timerToEarlyGate.checkTimer())
  {
    memoryGate = 8;
  }
  else if (memoryGate == 8)
  {
    setVar_onIO("releOpenLeft", 0);
    memoryGate = 9;

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao aberto esquerdo");
    serial += F("\n");
  }
  else if (memoryGate == 9)
  {
    setVar_onIO("releOpen", 0);
    memoryGate = 50;
    EEPROM.write(Memory_Gate, 50);

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao aberto");
    serial += F("\n");
  }
}

void gateClose(String &serial)
{
  if (!gateOpenBySensorInfrared(serial, 50))
  {
    if (memoryGate == 51)
    {
      setVar_onIO("releOpen", 0);
      timerToEarlyGate.reset();
      memoryGate = 52;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar");
      serial += F("\n");
    }
    else if (memoryGate == 52)
    {
      setVar_onIO("releOpenLeft", 1);
      timerToEarlyGate.reset();
      memoryGate = 53;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar esquerdo");
      serial += F("\n");
    }
    else if (memoryGate == 53 && timerToEarlyGate.checkTimer())
    {
      memoryGate = 54;
    }
    else if (memoryGate == 54)
    {
      setVar_onIO("releOpenRight", 1);
      timerToCloseGate.reset();
      memoryGate = 55;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar direto");
      serial += F("\n");
    }
    else if (memoryGate == 55 && timerToCloseGate.checkTimer())
    {
      memoryGate = 56;
    }
    else if (memoryGate == 56)
    {
      setVar_onIO("releOpenLeft", 0);
      timerToEarlyGate.reset();
      memoryGate = 57;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao fechado esquerdo");
      serial += F("\n");
    }
    else if (memoryGate == 57 && timerToEarlyGate.checkTimer())
    {
      memoryGate = 58;
    }
    else if (memoryGate == 58)
    {
      setVar_onIO("releOpenRight", 0);
      memoryGate = 59;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao fechado direito");
      serial += F("\n");
    }
    else if (memoryGate == 59)
    {
      setVar_onIO("releOpen", 0);
      memoryGate = 0;
      EEPROM.write(Memory_Gate, 0);

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao fechado");
      serial += F("\n");
    }
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