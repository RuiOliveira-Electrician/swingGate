#include "Gate.h"

void handleGate(String &serial)
{
    if (commandSensorInfrared())
    {
        timerGateCloseAutomatic.reset();
    }
    if ((((commandBoard() || commandRadio()) && timerCommandClick.hasEndedDelay()) || isgateReadyToCloseAutomatic()))
    {
        if (timerCommandClick.hasEndedDelay())
        {
            timerCommandClick.reset();
            getDebugAdress(serial, __FILE__, __func__, __LINE__);
            serial += F("Radio clicado");
            serial += F("\n");
        }
        if (isgateReadyToCloseAutomatic())
        {
            getDebugAdress(serial, __FILE__, __func__, __LINE__);
            serial += F("Portao fechado pelo tempo maximo");
            serial += F("\n");
        }
        timerGateCloseAutomatic.reset();
        checkGateStopedWhenOpening(serial);

        if (isgateClose())
        {
            memoryGateStop = false;
            configGate = ConfigGate::setOpen;
            timerGate.edit(timeToGate, Timer::Scale::second, false);
            timerGate.force();
        }
        else if (isgateOpen())
        {
            memoryGateStop = false;
            configGate = ConfigGate::setClose;
            timerGate.edit(timeToGate, Timer::Scale::second, false);
            timerGate.force();
        }
    }

    if (isgateOpening())
    {
        gateOpen(serial);
    }
    else if (isgateClosing())
    {
        gateClose(serial);
    }
}