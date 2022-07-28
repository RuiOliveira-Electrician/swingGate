#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>

class Timer
{
public:
    struct Scale
    {
        static const unsigned long millis = 1;
        static const unsigned long second = 1000;
        static const unsigned long minute = 60000;
        static const unsigned long hour = 3600000;
    };
    Timer(int delay = 1, unsigned long scale = Timer::Scale::second, bool initialState = false);
    void edit(int delay = 1, unsigned long scale = Timer::Scale::second, bool initialState = false);
    unsigned long getIntervalInMillis();
    unsigned long getTimePassedInMillis();
    unsigned long getTimePassedByScale();
    bool hasEndedDelay();
    void reset();
    void force();
    String debug();

private:
    int delay;
    unsigned long scale;
    unsigned long previous_millis;
};

#endif