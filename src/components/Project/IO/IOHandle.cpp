#include "IO.h"

void IO_handlePins(String &serial)
{
  IO_handleInputs(serial);
  IO_handleOutputs(serial);
}

void IO_handleInputs(String &serial)
{
}

void IO_handleOutputs(String &serial)
{
  //  //-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ Rele /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
  digitalWrite(Output::releOpen, memoryReleOpen);
  digitalWrite(Output::releOpenLeft, memoryReleOpenLeft);
  digitalWrite(Output::releOpenRight, memoryReleOpenRight);
}

void setVar_onIO(String variableName, int value)
{
  if (variableName == "releOpen")
    memoryReleOpen = value;
  else if (variableName == "releOpenLeft")
    memoryReleOpenLeft = value;
  else if (variableName == "releOpenRight")
    memoryReleOpenRight = value;
}