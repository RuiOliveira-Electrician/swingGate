#ifndef Eeprom_h
#define Eeprom_h

#include "../../settings.h"
#include "../other/debugger.h"

//------------------//EEPROM//------------------//
#include <EEPROM.h>
void setupEeprom(String &serial);
void resetEeprom(String &serial);
void writeIntIntoEEPROM(int address, int number);
int readIntFromEEPROM(int address);
#endif
