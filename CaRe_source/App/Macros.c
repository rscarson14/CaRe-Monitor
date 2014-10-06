/*
 * Macros.c
 *
 * Created: 7/7/2014 6:20:06 PM
 *  Author: Mike
 */ 
#include "Macros.h"

void turnOnAnalog()
{
	PORTB &= ~(1<<ANALOG); //Active low
}

void turnOffAnalog()
{
	PORTB |= (1<<ANALOG); //Active low
}

void turnOnStatusLED()
{
	PORTC |= (1<<STATUS_LED);	
}

void turnOnRespLED()
{
	PORTC |= (1<<RESP_LED);
}

void turnOnECGLED()
{
	PORTC |= (1<<ECG_LED);
}

void toggleStatusLED()
{
	PORTC ^= (1<<STATUS_LED);
}

void toggleRespLED()
{
	PORTC ^= (1<<RESP_LED);
}

void toggleECGLED()
{
	PORTC ^= (1<<ECG_LED);
}

void turnOffStatusLED()
{
	PORTC &= ~(1<<STATUS_LED);	
}

void turnOffRespLED()
{
	PORTC &= ~(1<<RESP_LED);
}

void turnOffECGLED()
{
	PORTC &= ~(1<<ECG_LED);
}

void turnOnSpeaker()
{
	PORTD |= (1<<SPEAKER);
}

void toggleSpeaker()
{
	PORTD ^= (1<<SPEAKER);
}

void turnOffSpeaker()
{
	PORTD &= ~(1<<SPEAKER);
}

void startBlinkStatusLED()
{
	turnOnStatusLED();
	blinkStatusLED.blinking = True;
	blinkStatusLED.period = 1;
}

void stopBlinkStatusLED()
{
	turnOffStatusLED();
	blinkStatusLED.blinking = False;
}

void startBlinkRespLED()
{
	turnOnRespLED();
	blinkRespLED.blinking = True;
	blinkRespLED.period = 1;
}

void stopBlinkRespLED()
{
	turnOffRespLED();
	blinkRespLED.blinking = False;
}

void startBlinkECGLED()
{
	turnOnECGLED();
	blinkECGLED.blinking = True;
	blinkECGLED.period = 1;
}

void stopBlinkECGLED()
{
	turnOffECGLED();
	blinkECGLED.blinking = False;
}

void startBlinkSpeaker()
{
	turnOnSpeaker(); 
	blinkSpeaker.blinking = True;
	blinkSpeaker.period = 1;
}

void stopBlinkSpeaker()
{	
	turnOffSpeaker(); 
	blinkSpeaker.blinking = False;
}

void startAlarm() //identical to startBlinkSpeaker; consider removing
{
	turnOnSpeaker();
	blinkSpeaker.blinking = True;
	blinkSpeaker.period = 1;
}

void chirpSpeaker()
{
	uint16_t i = 300;
	turnOnSpeaker();
	while(i--);
	turnOffSpeaker();	
}

void silenceAlarm()
{
	turnOffSpeaker();
	silenceSpeaker.blinking = True;
	silenceSpeaker.period = 15;
}

uint8_t readSwitch()
{
	uint8_t result = 0;
	uint8_t retVal;

	result |= (PINB)&((1<<PINB0)|(1<<PINB1));
	
	if(result == 0b01)
	{
		retVal =  10;
	}
	if(result == 0b00)
	{
		retVal = 15;
	}
	if(result == 0b10)
	{
		retVal = 20;
	}
	return retVal;
}