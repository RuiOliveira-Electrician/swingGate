#ifndef GATE_GLOBALS
#define GATE_GLOBALS

extern Timer timerGate;
extern Timer timerToEarlyGate;
extern Timer timerGateCloseAutomatic;
extern Timer timerGateBlocked;
extern Timer timerCommandClick;

extern uint8_t memorySensorInfraredActivated;

extern boolean memoryGateStop;
extern uint8_t memoryGateTime;
extern uint8_t memoryGateBlocked, contGateBlocked;

extern Timer timerDebug;

enum ConfigGate
{
  close,
  setOpen,
  openRight,
  waitTimeToOpenInBetween,
  openLeft,
  waitTimeToOpenRightIsDone,
  openRightIsDone,
  waitTimeToOpenLeftIsDone,
  openLeftIsDone,
  saveEepromIsOpen,
  open,
  setClose,
  closeRight,
  waitTimeToCloseInBetween,
  closeLeft,
  waitTimeToCloseRightIsDone,
  closeRightIsDone,
  waitTimeToCloseLeftIsDone,
  closeLeftIsDone,
  saveEepromIsClose,

  gateStopedWhenOpening,

  numCommands,
};
extern enum ConfigGate configGate;

struct GateCommandMapping
{
  ConfigGate command;
  const char *commandDebug;
};
extern const GateCommandMapping gateCommandMapping[static_cast<uint8_t>(ConfigGate::numCommands)];

#endif