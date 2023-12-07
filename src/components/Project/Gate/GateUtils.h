#ifndef GATE_UTILS
#define GATE_UTILS

bool isgateOpen();
bool isgateClose();
bool isgateOpening();
bool isgateClosing();
bool isGateStopedWhenOpening();
bool isgateBlocked();
bool isgateReadyToCloseAutomatic();
bool isWaitingTimeToCloseOrOppenGate();
const char *getCommandDebug(ConfigGate command);

#endif