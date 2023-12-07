#include "IO.h"

void IO_setupPins(String &serial)
{
   for (const Config &config : configs)
   {
      pinMode(config.pin, config.type);
      if (config.type == OUTPUT)
      {
         digitalWrite(config.pin, config.initialState);
      }
   }

   getDebugAdress(serial, __FILE__, __func__, __LINE__);
   serial += F("Initialized Pins");
   serial += F("\n");
}