#include <Arduino.h>

#include "settings.h"

#include "components/Memory/Eeprom.h"
#include "components/Project/IO.h"
#include "components/Project/Gate.h"
#include "components/other/Serial/SerialPc.h"
#include "components/other/Timer.h"
#include "components/other/debugger.h"

void setup()
{
  String serial;
  serial += F("\n");
  setupSerialPc(serial);
  DEBUG_LN(F("Initializing..."));
  setupEeprom(serial);
  setupPort(serial);

  getDebugAdress(serial, __FILE__, __func__, __LINE__);
  serial += F("Initializing Done...");
  serial += F("\n");

  DEBUGLN(serial);

 // EEPROM.write(Memory_Gate, 0);
}

void loop()
{
  String serial;
  handleSerialPc(serial);
  handlePins(serial);
  handleGate(serial);

  if (serial.length() > 33)
  {
    serial.remove(serial.length() - 1, serial.length());
    DEBUG_LN(serial);
  }
}