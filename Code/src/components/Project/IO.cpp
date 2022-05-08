#include "IO.h"

boolean memoryReleOpen = false;
boolean memoryReleOpenLeft = false;
boolean memoryReleOpenRight = false;

void setVar_onIO(String variableName, int value)
{
  if (variableName == "releOpen")
    memoryReleOpen = value;
  else if (variableName == "releOpenLeft")
    memoryReleOpenLeft = value;
  else if (variableName == "releOpenRight")
    memoryReleOpenRight = value;
}

void handlePins(String &serial)
{
  handleInputs(serial);
  handleOutputs(serial);
}

void setupPort(String &serial)
{
  setupInputs(serial);
  setupOutputs(serial);
}
//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ INPUTS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
void setupInputs(String &serial)
{
  pinMode(buttonRadio, INPUT);
  pinMode(buttonBoard, INPUT);
  pinMode(buttonInfrared, INPUT);

  getDebugAdress(serial, __FILE__, __func__, __LINE__);
  serial += F("Inputs started");
  serial += F("\n");
}

void handleInputs(String &serial)
{
}

uint8_t commandRadio()
{
  return digitalRead(buttonRadio);
}
uint8_t commandBoard()
{
  return !digitalRead(buttonBoard);
}
uint8_t commandSensorInfrared()
{
  return !digitalRead(buttonInfrared);
}

//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ OUTPUTS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
void setupOutputs(String &serial)
{
  pinMode(releOpen, OUTPUT);
  pinMode(releOpenLeft, OUTPUT);
  pinMode(releOpenRight, OUTPUT);
  digitalWrite(releOpen, LOW);
  digitalWrite(releOpenLeft, LOW);
  digitalWrite(releOpenRight, LOW);

  getDebugAdress(serial, __FILE__, __func__, __LINE__);
  serial += F("Outputs started");
  serial += F("\n");
}


void handleOutputs(String &serial)
{
  //  //-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ Rele /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
  digitalWrite(releOpen, memoryReleOpen);
  digitalWrite(releOpenLeft, memoryReleOpenLeft);
  digitalWrite(releOpenRight, memoryReleOpenRight);
}
