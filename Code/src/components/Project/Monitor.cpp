#include "Monitor.h"
NewTimer timerToCheakMonitor(1, "Minute", 0); // (*Um Minuto) //Tempo para mostrar no monitor serial

void timerToForce_onMonitor(String timerName)
{
  if (timerName == "timerToCheakMonitor")
    timerToCheakMonitor.force();
}

void monitor(String &serial)
{
  if (timerToCheakMonitor.checkTimer()) // timePassed(Old_Millis[Old_Time_to_Cheak_SerialMonitor]) >= Time_to_Cheak_SerialMonitor * OneMinute)
  {
    timerToCheakMonitor.reset(); // Old_Millis[Old_Time_to_Cheak_SerialMonitor] = millis();

   
  }
}
