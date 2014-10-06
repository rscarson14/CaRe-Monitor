
#include <avr/io.h>
#include <stdint.h>

#define _ADC_DATA_BUFFER_
#include "Globals.h"

#ifndef ADC_HAL_H_
#define ADC_HAL_H_

//universal defines here
#define ADC_RESULT				ADCH<<8|ADCL	//can call ADC_RESULT instead of the individual registers in main code now

#define ADC_RESULTS_TO_WAKE		0x00			//placeholder, this value is the number of results the ADC must queue
//before something is done with the waiting data


#ifdef _ADC_HAL_C_ //this is only true in ADC_HAL.c file


//ADMUX Register Values, p262 of Data sheet:
#define ADC_REF_AREF			0x00	//aref pin
#define ADC_REF_AVCC_EXT_CAP	0x40	//avcc with an extern capacitor at AREF
#define ADC_REF_INTERNAL_1_1	0xC0	//internal 1.1V with external cap at AREF		

#define ADC_RESULT_RIGHT_ADJUST	0x00	//use LSB's of two result registers

#define ADMUX_SETTING			ADC_REF_AVCC_EXT_CAP|ADC_RESULT_RIGHT_ADJUST

//aDCSRA Register Values, p263 of datasheet:
#define ADC_EN					7	//setting this value enables the ADC, and vice-versa
//#define ADSC					6	//set to start conversion, reads as 0b1 if a conversion is in progress, cannot be cleared
//#define ADATE					5	//allows ADC to be triggered automatically, source for trigger set by ADTS
#define ADIFG					4	//IFG
//#define ADIE					3	//IE
#define ADPS_2					0x00	//ADPS Bits select the prescaler from the system clock to the ADC clock 
//0x01 is functionally identical to 0x00
#define ADPS_4					0x02
#define ADPS_8					0x03
#define ADPS_16					0x04
#define ADPS_32					0x05
#define ADPS_64					0x06
#define ADPS_128				0x07

#define ADCSRA_SETTING			(1<<ADC_EN)|(1<<ADATE)|(1<<ADIE)|ADPS_128

//ADCSRB Settings, p265:
//#define ACME					0x40	//used for negative input of comparator, no conceivable need to set this bit
#define ADTS_FREE_RUN			0x00	//ADTS selects the trigger for automatic ADC reading
#define ADTS_ANALOG_COMARATOR	0x01
#define ADTS_IRQ0				0x02
#define ADTS_T0_CMA				0x03	//timer 0 compare match a
#define ADTS_T0_OVERFLOW		0x04
#define ADTS_T1_CMA				0x05
#define ADTS_T1_OVERFLOW		0x06
#define ADTS_T1_CAPTURE_EVENT	0x07

#define ADCSRB_SETTING			ADTS_T0_CMA		//the ADC will sample as fast as soon as a conversion is completed continuously, until ADC En is cleared
												//typical conversion take 13 ADC clock cycles (only exception is the first one)

//functions
void ADCStartRead(uint8_t adcChannel);//call this to start ADC reading
void ADCStopRead();//call this to end all ADC reading
void ADCInit();//call this to set the registers with the defined values above

#else //all other .c files that include this header need access only to these functions

extern void ADCStartRead(uint8_t adcChannel);//call this to start ADC reading
extern void ADCStopRead();//call this to end all ADC reading
extern void ADCInit();//call this to set the registers with the defined values above

#endif
#endif /* ADC_HAL_H_ */