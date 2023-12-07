#include "Gate.h"

Timer timerGate(timeToGate, Timer::Scale::second, true);                              // (*Um Segundo)
Timer timerToEarlyGate(timeToEarlyGate, Timer::Scale::second, true);                  // (*Um Segundo)
Timer timerGateCloseAutomatic(timeToGateCloseAutomatic, Timer::Scale::minute, false); // (*Um Minuto)
Timer timerGateBlocked(timeToGateBlocked, Timer::Scale::second, true);                // (*Um Segundo)
Timer timerCommandClick(1, Timer::Scale::second, true);                               // (*Um Segundo)

uint8_t memorySensorInfraredActivated = 0;

boolean memoryGateStop = false;
uint8_t memoryGateTime = 0;
uint8_t memoryGateBlocked = 0, contGateBlocked = 0;

enum ConfigGate configGate = static_cast<ConfigGate>(EEPROM.read(Memory_Gate));

const GateCommandMapping gateCommandMapping[] PROGMEM = {
    {ConfigGate::close, "close"},
    {ConfigGate::setOpen, "setOpen"},
    {ConfigGate::openRight, "openRight"},
    {ConfigGate::waitTimeToOpenInBetween, "waitTimeToOpenInBetween"},
    {ConfigGate::openLeft, "openLeft"},
    {ConfigGate::waitTimeToOpenRightIsDone, "waitTimeToOpenRightIsDone"},
    {ConfigGate::openRightIsDone, "openRightIsDone"},
    {ConfigGate::waitTimeToOpenLeftIsDone, "waitTimeToOpenLeftIsDone"},
    {ConfigGate::openLeftIsDone, "openLeftIsDone"},
    {ConfigGate::saveEepromIsOpen, "saveEepromIsOpen"},
    {ConfigGate::open, "open"},
    {ConfigGate::setClose, "setClose"},
    {ConfigGate::closeRight, "closeRight"},
    {ConfigGate::waitTimeToCloseInBetween, "waitTimeToCloseInBetween"},
    {ConfigGate::closeLeft, "closeLeft"},
    {ConfigGate::waitTimeToCloseRightIsDone, "waitTimeToCloseRightIsDone"},
    {ConfigGate::closeRightIsDone, "closeRightIsDone"},
    {ConfigGate::waitTimeToCloseLeftIsDone, "waitTimeToCloseLeftIsDone"},
    {ConfigGate::closeLeftIsDone, "closeLeftIsDone"},
    {ConfigGate::saveEepromIsClose, "saveEepromIsClose"},
    {ConfigGate::gateStopedWhenOpening, "gateStopWhenOpen"}};