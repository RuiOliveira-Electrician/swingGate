#include "SerialPc.h"

void setupSerialPc(String &serial)
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  getDebugAdress(serial, __FILE__, __func__, __LINE__);
  serial += F("SerialPc started");
  serial += F("\n");
}

void handleSerialPc(String &serial)
{
  if (Serial.available())
  {
    String textString = "";
    while (Serial.available())
    {
      delay(10);
      char a = Serial.read(); // ler um dado recebido do computador (Ps:o computtador envia dados Tipo_Tem_0_1 CHAR)  e grava na variavel a(Variavel Tipo_Tem_0_1 CHAR)
      textString += a;        // Encrementar a variavel a(Variavel Tipo_Tem_0_1 CHAR) a textString(Variavel Tipo_Tem_0_1 STRING) -> textString += a <=> textString = textString + a -> Exemplo: A += B <=> A = A + B <=> O RESULTADO É "AB"
    }
    textString.trim();
    serial = F("Serial: ");
    serial += textString;
    serial += F("   Return: ");
    handleSerialAvailable(serial, textString);
  }
}

void handleSerialAvailable(String &serial, String textString)
{
  String textString_Editado = textString;
  //-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ (Fazer Reset) /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-//
  if (textString == F("Reset"))
  {
    serial += F("Reset");
  }
  else if (textString == F("Direita"))
  {
    serial += F("Direita");
    setVar_onIO("releOpen", 1);
    setVar_onIO("releOpenLeft", 1);
    setVar_onIO("releOpenRight", 1);
    delay(1000);
    setVar_onIO("releOpen", 0);
    setVar_onIO("releOpenLeft", 0);
    setVar_onIO("releOpenRight", 0);
  }
  else if (textString == F("Esquerda"))
  {
    serial += F("Esquerda");
    setVar_onIO("releOpen", 1);
    delay(1000);
    setVar_onIO("releOpen", 0);
  }
  else
  {
    serial += F("none");
  }
  serial += F("\n");
}