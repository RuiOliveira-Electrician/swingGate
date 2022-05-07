#include "IO.h"

NewTimer timerToBlinkLedGreen(10, "TenMillisSecond", 0);  // (*Dez MiliSegundo)
NewTimer timerToBlinkLedRed(10, "TenMillisSecond", 0);    // (*Dez MiliSegundo)
NewTimer timerToBlinkLedYellow(10, "TenMillisSecond", 0); // (*Dez MiliSegundo)

NewTimer aa(10, "TenMillisSecond", 0); // (*Dez MiliSegundo)

const uint8_t Time_to_Blink_Led_Velocity[4] = {
    200, // (*Dez MiliSegundo) //Tempo para piscar Led
    50,  // (*Dez MiliSegundo) //Tempo para piscar Led
    10,  // (*Dez MiliSegundo) //Tempo para piscar Led
};

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
  pinMode(buttonInfrared, INPUT);
  pinMode(buttonInfrared_2, INPUT);

  getDebugAdress(serial, __FILE__, __func__, __LINE__);
  serial += F("Inputs started");
  serial += F("\n");
}

void handleInputs(String &serial)
{
}

uint8_t commandRadio()
{
  return !digitalRead(buttonRadio);
}
uint8_t commandSensorInfrared()
{
  return !digitalRead(buttonInfrared);
}
uint8_t commandSensorInfrared_2()
{
  return digitalRead(buttonInfrared_2);
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

void Blink_Led(const __FlashStringHelper *type, const uint8_t velocity)
{
  uint8_t led = 255;
  String Type = type;
  if (Type == "Green")
  {
    timerToBlinkLedGreen.edit(Time_to_Blink_Led_Velocity[velocity], "TenMillisSecond");
    if (timerToBlinkLedGreen.checkTimer())
    {
      timerToBlinkLedGreen.reset();
      led = Led_Green;
    }
  }
  else if (Type == "Red")
  {
    timerToBlinkLedRed.edit(Time_to_Blink_Led_Velocity[velocity], "TenMillisSecond");
    if (timerToBlinkLedRed.checkTimer())
    {
      timerToBlinkLedRed.reset();
      led = Led_Red;
    }
  }
  else if (Type == "Yellow")
  {
    timerToBlinkLedYellow.edit(Time_to_Blink_Led_Velocity[velocity], "TenMillisSecond");
    if (timerToBlinkLedYellow.checkTimer())
    {
      timerToBlinkLedYellow.reset();
      led = Led_Yellow;
    }
  }
  else
  {
    return;
  }
  if (led != 255)
  {
    digitalWrite(led, !digitalRead(led));
  }
}

void handleOutputs(String &serial)
{
  //-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ Led Alarm On /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
  // if ((isAlarm_CallFristNumber() || isAlarm_Detecting()) && digitalRead(Led_Green) == false)
  //{
  //   digitalWrite(Led_Green, true);
  // }
  // else if (isAlarm_Activated() || isAlarm_Ringing())
  //{
  //   Blink_Led(F("Green"), 1);
  // }
  // else if (isWifiActive())
  //{
  //   Blink_Led(F("Green"), 2);
  // }
  // else if (!isWifiActive() && isAlarm_Off() && digitalRead(Led_Green) == true)
  //{
  //   digitalWrite(Led_Green, false);
  // }

  //  //-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ Led Error /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
  //  if (memoryLedError == 1)
  //  {
  //    Blink_Led(F("Red"), 2);
  //  }
  //  else if (isSetupGsmActive())
  //  {
  //    Blink_Led(F("Red"), 1);
  //  }
  //  else if (digitalRead(Led_Green) == true)
  //  {
  //    digitalWrite(Led_Red, false);
  //  }
  //  //-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ Led a desativar alarm /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
  //  if (isAlarm_BeingDeactivated())
  //  {
  //    Blink_Led(F("Yellow"), 1);
  //  }
  //  else if (digitalRead(Led_Yellow) != memoryLedMoney)
  //  {
  //    digitalWrite(Led_Yellow, memoryLedMoney);
  //  }
  //  //-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ Rele /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
  digitalWrite(releOpen, memoryReleOpen);
  digitalWrite(releOpenLeft, memoryReleOpenLeft);
  digitalWrite(releOpenRight, memoryReleOpenRight);
}
