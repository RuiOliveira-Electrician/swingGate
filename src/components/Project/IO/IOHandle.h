#ifndef IO_HANDLE
#define IO_HANDLE

void IO_handlePins(String &serial);
void IO_handleInputs(String &serial);
void IO_handleOutputs(String &serial);

void setVar_onIO(String variableName, int value);

#endif