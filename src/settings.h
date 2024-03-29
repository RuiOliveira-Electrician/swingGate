#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdint.h>

#define timeToGate 18              // sec
#define timeToEarlyGate 1          // sec
#define timeToGateBlocked 50       // sec
#define timeToGateCloseAutomatic 1 // min

//------------------//Eeprom//------------------//
#define EEPROM_SIZE 2
#define EEPROM_RESET 0

#define Memory_Gate 1

//------------------//Entradas//------------------//
#define buttonBoard 9
#define buttonRadio 10
#define buttonInfrared 7

//------------------//Saidas//------------------//
#define releOpen 4
#define releOpenLeft 3
#define releOpenRight 5

#endif