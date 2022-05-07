#ifndef Gate.h
#define Gate .h
#include "../../settings.h"
#include "../other/debugger.h"
#include "../other/Timer.h"

#include "./IO.h"

//------------------//Alarm//------------------//

void handleGate(String &serial);

void gateOpen(String &serial);
void gateClose(String &serial);

bool isgateOpening();
bool isgateClosing();

#endif