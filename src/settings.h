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

////------------------//Entradas//------------------//
#define BUTTONBOARD 9
#define BUTTONRADIO 10
#define GATEINFRARED 7

//------------------//Saidas//------------------//
#define RELEOPEN 4
#define RELEOPENLEFT 3
#define RELEOPENRIGHT 5

#endif