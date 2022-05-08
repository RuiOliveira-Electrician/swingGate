#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>

class NewTimer
{
public:
    NewTimer(uint8_t delay, String multiplier);
    NewTimer(uint8_t delay, String multiplier, uint8_t forceState);
    bool checkTimer();
    uint8_t getTimerPassed();
    void reset();
    void force();
    void edit(uint8_t delay, String multiplier);

private:
    const int Hour = 3600000, Minute = 60000, Second = 1000, TenMillisSecond = 10, defaultTime = 1000;
    uint8_t time;
    int multiplier;
    uint8_t forceState;
    unsigned long Old_Millis;

    void getMultiplier(String multiplier);
};

#endif