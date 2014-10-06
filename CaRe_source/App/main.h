
#define _ADC_DATA_BUFFER_
#define _PUSH_BUTTON_
#define _MAIN_ //CLUNKY!!!! Fix later!

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>
#include "TypeDefines.h"
#include "Pot_HAL.h"
#include "Init.h"
#include "Globals.h"
#include "ADC_HAL.h"
#include "Filt.h"
#include "Macros.h"


#ifndef MAIN_H_
#define MAIN_H_

uint8_t respTimeThresh = 15;								//How long to allow resp. volume < respThresh before alarm	

#define SAMPLE_POINTS_TO_REMEMBER					1200	//dictates how many points of data we remember for each the heartbeat and breathing while we are sampling
#define ECG_THRESHOLD_VALUE							50		//dictates what we need to be over to count a heartbeat
#define PERCENTAGE_CALIBRATED_BREATH_THRESHOLD		75		//dictates what percentage of the calculated threshold counts as good enough to be a detected breath
#define PERCENTAGE_CALIBRATED_ECG_THRESHOLD			33
#define SLOW_HEART_RATE_PERIOD						450		//maximum number of samples between detected heart rates that is allowable
#define NUMBER_OF_TOO_SLOW_HEARTBEATS				5		//defines how many averages heart rates below the target threshold will trigger the alarm
#define NO_HEART_RATE_PERIOD						1500	//how many counts before 5s of no heart-beat is detected
#endif /* MAIN_H_ */