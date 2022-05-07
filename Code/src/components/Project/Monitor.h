#ifndef Monitor_h
#define Monitor_h
#include "../../settings.h"
#include "../other/debugger.h"
#include "../other/Timer.h"
#include "../Memory/Eeprom.h"

void monitor(String &serial);
void timerToForce_onMonitor(String timerName);

#endif