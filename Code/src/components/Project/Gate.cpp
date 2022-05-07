#include "Gate.h"

NewTimer timerToOpenGate(19, "Second", 1);  // (*Um Segundo)
NewTimer timerToCloseGate(19, "Second", 1); // (*Um Segundo) //Tento verificar se a porta foi fechada

NewTimer timerToEarlyGate(2, "Second", 1);                   // (*Um Segundo)
NewTimer timerToOpenGateWithSensorInfrared(20, "Second", 1); // (*Um Segundo)

boolean memorySensorInfraredActivated = false;

int memoryGate = EEPROM.read(Memory_Gate);

void handleGate(String &serial)
{
  if (!isgateOpening() && !isgateClosing())
  {
    if (commandRadio())
    {
      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Radio clicado");
      serial += F("\n");
      if (memoryGate == 10)
      {
        memoryGate = 11;
        gateClose(serial);
      }
      if (memoryGate == 0)
      {
        memoryGate = 1;
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

bool gateOpenBySensorInfrared(String &serial, int _memoryGate)
{
  if (!commandSensorInfrared() && memorySensorInfraredActivated == true)
  {
    memorySensorInfraredActivated = false;
  }
  if (commandSensorInfrared())
  {
    if (memorySensorInfraredActivated == false)
    {
      setVar_onIO("releOpen", 1);
      setVar_onIO("releOpenLeft", 1);
      setVar_onIO("releOpenRight", 1);
      timerToOpenGateWithSensorInfrared.reset();
      memorySensorInfraredActivated = true;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a abrir SensorInfrared");
      serial += F("\n");
    }
    else if (timerToOpenGateWithSensorInfrared.checkTimer())
    {
      setVar_onIO("releOpen", 0);
      setVar_onIO("releOpenLeft", 0);
      setVar_onIO("releOpenRight", 0);
    }
    memoryGate = _memoryGate;
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
    memoryGate = 10;
    EEPROM.write(Memory_Gate, 10);

    getDebugAdress(serial, __FILE__, __func__, __LINE__);
    serial += F("Portao aberto");
    serial += F("\n");
  }
}

void gateClose(String &serial)
{
  if (!gateOpenBySensorInfrared(serial, 11))
  {
    if (memoryGate == 11)
    {
      setVar_onIO("releOpen", 0);
      timerToEarlyGate.reset();
      memoryGate = 12;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar");
      serial += F("\n");
    }
    else if (memoryGate == 12)
    {
      setVar_onIO("releOpenLeft", 1);
      timerToEarlyGate.reset();
      memoryGate = 13;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar esquerdo");
      serial += F("\n");
    }
    else if (memoryGate == 13 && timerToEarlyGate.checkTimer())
    {
      memoryGate = 14;
    }
    else if (memoryGate == 14)
    {
      setVar_onIO("releOpenRight", 1);
      timerToCloseGate.reset();
      memoryGate = 15;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao a fechar direto");
      serial += F("\n");
    }
    else if (memoryGate == 15 && timerToCloseGate.checkTimer())
    {
      memoryGate = 16;
    }
    else if (memoryGate == 16)
    {
      setVar_onIO("releOpenLeft", 0);
      timerToEarlyGate.reset();
      memoryGate = 17;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao fechado esquerdo");
      serial += F("\n");
    }
    else if (memoryGate == 17 && timerToEarlyGate.checkTimer())
    {
      memoryGate = 18;
    }
    else if (memoryGate == 18)
    {
      setVar_onIO("releOpenRight", 0);
      memoryGate = 19;

      getDebugAdress(serial, __FILE__, __func__, __LINE__);
      serial += F("Portao fechado direito");
      serial += F("\n");
    }
    else if (memoryGate == 19)
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
  if (memoryGate > 0 && memoryGate < 10)
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
  if (memoryGate > 10)
  {
    return true;
  }
  else
  {
    return false;
  }
}