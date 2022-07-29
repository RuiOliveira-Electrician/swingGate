#ifndef DEBUGGER_H
#define DEBUGGER_H

#define __DEBUG__
#define __DebugAdress__

#ifdef __DEBUG__
#define USE_SERIAL Serial
#define SetDebugOutput Serial
#define Debug_Error 1
#define DEBUG(...) Serial.print(__VA_ARGS__)
#define DEBUG_LN(...) Serial.println(__VA_ARGS__)
#define DEBUGLN(...)             \
  Serial.print("[");             \
  Serial.print(__FILE__);        \
  Serial.print("] [");           \
  Serial.print("] [Line ");      \
  Serial.print(__LINE__);        \
  Serial.print("] ");            \
  Serial.println(__VA_ARGS__)
#else
#define Debug_Error 0
#define DEBUG(...)
#define DEBUGLN(...)
#endif
#include <WString.h>
void getDebugAdress(String &serial, const char *FILE, const char *FUNCTION, const int LINE);
void getSerialOnCache(String &serial);
void setSerialOnCache(String &serial);
#endif
//  Serial.print(FPSTR(__func__)); \