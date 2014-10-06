


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <avr/io.h>
#include <stdint.h>

#define True		1
#define False		!True

typedef uint8_t		boolean; //substitute type for c

typedef enum 
{
	Init,
	WaitForPB,
	Calibration,
	Sampling,
	Alarm
	
}State;

typedef struct 
{
	boolean blinking;
	uint16_t counter;
	uint16_t period;
}BLINKER;

#endif /* INCFILE1_H_ */