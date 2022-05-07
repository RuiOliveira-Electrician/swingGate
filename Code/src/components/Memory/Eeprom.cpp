#include "EEPROM.h"

void setupEeprom(String &serial)
{
  //EEPROM.begin(EEPROM_SIZE);

  if (EEPROM.read(EEPROM_RESET) != 255)
    for (uint8_t Cont = 0; Cont <= EEPROM_SIZE; Cont++)
      EEPROM.write(Cont, 0);

  EEPROM.write(EEPROM_RESET, 255);
 // EEPROM.commit();
  getDebugAdress(serial, __FILE__, __func__, __LINE__);
  serial += F("EEPROM started");
  serial += F("\n");
}

void resetEeprom(String &serial)
{
  EEPROM.write(EEPROM_RESET, 1);
  //EEPROM.commit();
  getDebugAdress(serial, __FILE__, __func__, __LINE__);
  serial += F("EEPROM reset");
  serial += F("\n");
  setupEeprom(serial);
}

void writeIntIntoEEPROM(int address, int number)
{
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int readIntFromEEPROM(int address)
{
 // byte byte1 = EEPROM.read(address);
//  byte byte2 = EEPROM.read(address + 1);
 // return (byte1 << 8) + byte2;
}