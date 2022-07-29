#ifndef SERIALPC_H
#define SERIALPC_H
#include <HardwareSerial.h>
#include <Arduino.h>

#include "../debugger.h"
#include "../../Project/IO.h"

void setupSerialPc(String &serial);
void handleSerialPc(String &serial);
void handleSerialAvailable(String &serial, String textString);

#endif