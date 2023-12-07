#include "Gate.h"

bool isgateOpen()
{
    return configGate == ConfigGate::open;
}
bool isgateClose()
{
    return configGate == ConfigGate::close;
}

bool isgateOpening()
{
    return configGate == ConfigGate::setOpen || configGate == ConfigGate::openRight || configGate == ConfigGate::waitTimeToOpenInBetween ||
           configGate == ConfigGate::openLeft || configGate == ConfigGate::waitTimeToOpenRightIsDone || configGate == ConfigGate::openRightIsDone ||
           configGate == ConfigGate::waitTimeToOpenLeftIsDone || configGate == ConfigGate::openLeftIsDone || configGate == ConfigGate::saveEepromIsOpen;
}

bool isgateClosing()
{
    return configGate == ConfigGate::setClose || configGate == ConfigGate::closeRight || configGate == ConfigGate::waitTimeToCloseInBetween ||
           configGate == ConfigGate::closeLeft || configGate == ConfigGate::waitTimeToCloseRightIsDone || configGate == ConfigGate::closeRightIsDone ||
           configGate == ConfigGate::waitTimeToCloseLeftIsDone || configGate == ConfigGate::closeLeftIsDone || configGate == ConfigGate::saveEepromIsClose;
}
bool isGateStopedWhenOpening()
{
    return configGate == ConfigGate::gateStopedWhenOpening;
}
bool isgateBlocked()
{
    return memoryGateBlocked;
}
bool isgateReadyToCloseAutomatic()
{
    return timerGateCloseAutomatic.hasEndedDelay() && (isgateOpen() || isGateStopedWhenOpening());
}

bool isWaitingTimeToCloseOrOppenGate()
{
    return configGate == ConfigGate::waitTimeToCloseInBetween || configGate == ConfigGate::waitTimeToCloseLeftIsDone || configGate == ConfigGate::waitTimeToCloseRightIsDone ||
           configGate == ConfigGate::waitTimeToOpenInBetween || configGate == ConfigGate::waitTimeToOpenLeftIsDone || configGate == ConfigGate::waitTimeToOpenRightIsDone;
}

const char *getCommandDebug(ConfigGate command)
{
    return reinterpret_cast<const char *>(pgm_read_ptr(&gateCommandMapping[static_cast<uint8_t>(command)].commandDebug));
}