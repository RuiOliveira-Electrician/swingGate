#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdint.h>
//------------------//Codigos//------------------//
#define timeForther 60

//------------------//Eeprom//------------------//
#define EEPROM_SIZE 11
#define EEPROM_RESET 0

#define Memory_Sensores 1       //
#define Time_Ring 3             // Tempo até o alame tocar
#define Time_past_Ring 4        // Tempo que falta até o alame tocar
#define Save_time_Minute 5      // Endereço da eeprom para gardar minuto para enviar sms
#define Save_time_Hour 6        // Endereço da eeprom para gardar hora para enviar sms
#define Save_time_Day 7         // Endereço da eeprom para gardar dia para enviar sms
#define Save_time_Month 8       // Endereço da eeprom para gardar mes para enviar sms
#define Memory_Send_SMS_State 9 // Endereço da eeprom para saber se o sms tem de ser enviado se == 1 tem de enviar

//------------------//Entradas//------------------//
#define buttonRadio 9
#define buttonInfrared 8
#define buttonInfrared_2 7

//------------------//Saidas//------------------//
#define Led_Red 18
#define Led_Yellow 19
#define Led_Green 14 //trocar do pino 22 para o 14

#define releOpen 5
#define releOpenLeft 3
#define releOpenRight 4

#endif