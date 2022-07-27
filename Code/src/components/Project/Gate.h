#ifndef Gate.h
#define Gate .h
#include "../../settings.h"
#include "../other/debugger.h"
#include "../other/Timer.h"
#include "../Memory/Eeprom.h"

#include "./IO.h"

//------------------//Alarm//------------------//

void handleGate(String &serial);

void gateOpen(String &serial);
void gateClose(String &serial);
void gateStop(String &serial);
void gateBlocked(String &serial);

bool isgateOpening();
bool isgateClosing();
bool isgateBlocked();

#endif
