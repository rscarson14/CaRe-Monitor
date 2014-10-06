/*
 * Macros.h
 *
 * Created: 7/7/2014 6:21:09 PM
 *  Author: Mike
 */ 


#ifndef MACROS_H_
#define MACROS_H_
#define _BLINKERS_
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "TypeDefines.h"
#include "Globals.h"

#define ON 1
#define OFF 0

#define RESP_LED  PORTC3
#define ECG_LED PORTC4
#define STATUS_LED PORTC5
#define SPEAKER PORTD3
#define ANALOG PORTB2

void turnOnAnalog();
void turnOffAnalog();
void turnOnStatusLED();
void toggleStatusLED();
void turnOnRespLED();
void turnOnECGLED();
void turnOnSpeaker();
void turnOffStatusLED();
void turnOffRespLED();
void turnOffECGLED();
void turnOffSpeaker();
void startBlinkStatusLED();
void stopBlinkStatusLED();
void startBlinkRespLED();
void toggleRespLED();
void toggleECGLED();
void startBlinkECGLED();
void stopBlinkECGLED();
void toggleSpeaker();
void startBlinkSpeaker();
void stopBlinkSpeaker();
void silenceAlarm();
void startAlarm();
void chirpSpeaker();

uint8_t readSwitch();




#endif /* MACROS_H_ */