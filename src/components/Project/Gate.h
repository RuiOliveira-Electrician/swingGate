#ifndef GATE_H
#define GATE_H
#include <Timer.h>
#include "../../settings.h"
#include "../other/debugger.h"
#include "../Memory/Eeprom.h"

#include "./IO.h"

//------------------//Alarm//------------------//

void handleGate(String &serial);

void gateOpen(String &serial);
void gateClose(String &serial);
void gateStop(String &serial);
void gateBlocked(String &serial);

bool isgateOpen();
bool isgateClose();
bool isgateOpening();
bool isgateClosing();
bool isgateStoped();
bool isgateBlocked();
bool isgateReadyToOpenAutomatic();

#endif
