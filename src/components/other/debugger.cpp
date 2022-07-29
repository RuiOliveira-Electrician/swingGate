#include "debugger.h"

String serialOnCache;

void getDebugAdress(String &serial, const char *FILE, const char *FUNCTION, const int LINE)
{
#ifdef __DebugAdress__
  serial += F("[");
  serial += FILE;
  serial += F("] [");
  serial += FUNCTION;
  serial += F("] [Line ");
  serial += LINE;
  serial += F("] ");
#endif
}

void getSerialOnCache(String &serial)
{
  if (serialOnCache.length() > 0)
  {
    serial += serialOnCache;
    serialOnCache = "";
  }
}

void setSerialOnCache(String &serial)
{
  serialOnCache += serial;
}