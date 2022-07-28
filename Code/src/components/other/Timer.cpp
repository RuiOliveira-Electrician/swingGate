#include "Timer.h"

Timer::Timer(int delay = 1, unsigned long scale = Timer::Scale::second, bool initialState = false)
{
  this->previous_millis = 0;
  this->delay = delay;
  this->scale = scale;

  if (initialState)
  {
    this->force();
  }
}

void Timer::edit(int delay = 1, unsigned long scale = Timer::Scale::second, bool initialState = false)
{
  this->delay = delay;
  this->scale = scale;

  if (initialState)
  {
    this->force();
  }
}

String Timer::debug()
{
  String serial;
  serial += F("Old_Millis  ");
  serial += this->previous_millis;
  serial += F("  time  ");
  serial += this->delay;
  serial += F("  multiplier  ");
  serial += this->scale;
  serial += F("  time * multiplier  ");
  serial += this->getIntervalInMillis();
  serial += F("  time passed  ");
  serial += this->getTimePassedInMillis();
  serial += F("\n");

  return serial;
}

unsigned long Timer::getIntervalInMillis()
{
  return (unsigned long)this->delay * this->scale;
}

unsigned long Timer::getTimePassedInMillis()
{
  return (unsigned long)(millis() - this->previous_millis);
}

unsigned long Timer::getTimePassedByScale()
{
  return (unsigned long)(this->getTimePassedInMillis() / this->scale);
}

bool Timer::hasEndedDelay()
{
  return this->getTimePassedInMillis() >= this->getIntervalInMillis();
}

void Timer::reset()
{
  this->previous_millis = millis();
}

void Timer::force()
{
  this->previous_millis = this->getIntervalInMillis();
}