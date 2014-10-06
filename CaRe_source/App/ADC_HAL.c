
#define _ADC_HAL_C_
#include "ADC_HAL.h"

/* Notes on the ADC: the ADC is initialized in free running mode by default when ADCInit() is called,
*  A subsequent call of ADCStartRead() will cause the ADC to continuously read data until ADCStopRead() is called.
*  The ISR will take the result of the ADC conversion and store it in the buffer set aside in globals.h
*/

void ADCStartRead(uint8_t adcChannel)	//call this to start ADC reading
{
	ADMUX &= 0xF0;						//clear out the lower nibble to remove any leftover settings from a previous channel 
										//selection
	
	ADMUX |= (adcChannel&0x0F);			//set the lower nibble, clear the upper nibble of the passed variable to ensure that 
										//vital settings are preserved
										
	ADCSRA &= ~(1<<ADIFG);					//clear lingering interrupt flag
	
	//ADCSRA |= (1<<ADC_EN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE);			//start conversion now, also set interrupt enable and ad_en to be sure we are going
	
	ADCSRA |= (1<<ADSC);
	ADCSRA |= (1<<ADATE);
	ADCSRA |= (1<<ADIE);
	ADCSRA |= (1<<ADC_EN);
	
	TCCR0B |= (1<<CS02);//enable timer that will autotrigger our sampling
	
	return;
}

void ADCStopRead()						//call this to end all ADC reading
{
	ADCSRA &= ~((1<<ADC_EN) + (1<<ADIE) + (1<<ADATE) + (1<<ADSC) );			//turn off ADC alltogether, and disable the interrupt
	
	TCCR0B &= ~(1<<CS02);
	
	return;
}

void ADCInit()							//call this to set the registers with the defined values above
{
		
	ADMUX = ADMUX_SETTING;				//explanations for these settings can be seen in the ADC_HAL.h file

	ADCSRA = ADCSRA_SETTING;
	
	ADCSRB = ADCSRB_SETTING;
	
	return;
}