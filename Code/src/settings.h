#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdint.h>
//------------------//Codigos//------------------//
#define timeForther 60

//------------------//Eeprom//------------------//
#define EEPROM_SIZE 11
#define EEPROM_RESET 0

#define Memory_Gate 1

//------------------//Entradas//------------------//
#define buttonRadio 9
#define buttonInfrared 7
#define buttonInfrared_2 8

//------------------//Saidas//------------------//
#define Led_Red 18
#define Led_Yellow 19
#define Led_Green 14 //trocar do pino 22 para o 14

#define releOpen 4
#define releOpenLeft 3
#define releOpenRight 5

#endif