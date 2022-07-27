#include "Timer.h"

NewTimer::NewTimer(uint8_t time, String multiplier, uint8_t forceState)
{
  this->Old_Millis = 0;
  this->time = time;
  this->forceState = forceState;
  
  getMultiplier(multiplier);

  if (this->forceState == 1)
  {
    this->Old_Millis = (unsigned long)this->time * this->multiplier;
  }
}

bool NewTimer::checkTimer()
{
  return ((unsigned long)(millis() - this->Old_Millis) >= (unsigned long)this->time * this->multiplier);
}

uint8_t NewTimer::getTimerPassed()
{
  return (((unsigned long)(millis() - this->Old_Millis) / this->multiplier));
}

void NewTimer::reset()
{
  this->Old_Millis = millis();
}

void NewTimer::force()
{
  this->Old_Millis = (unsigned long)this->time * this->multiplier;
}

void NewTimer::edit(uint8_t time, String multiplier)
{
  this->time = time;
  getMultiplier(multiplier);
}

void NewTimer::getMultiplier(String multiplier)
{
  if (multiplier == "Hour")
  {
    this->multiplier = Hour;
  }
  else if (multiplier == "Minute")
  {
    this->multiplier = Minute;
  }
  else if (multiplier == "Second")
  {
    this->multiplier = Second;
  }
  else if (multiplier == "TenMillisSecond")
  {
    this->multiplier = TenMillisSecond;
  }
  else
  {
    this->multiplier = defaultTime;
  }
}