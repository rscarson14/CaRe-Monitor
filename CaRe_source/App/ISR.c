#include "ISR.h"

ISR(ADC_vect)//when an A/D conversion is completed, this ISR will be called
{

	
	ADCDataBuffer[ADCDataBufferHeadPtr] = ADCW;//read in data
	IncrementRingBufferHeadPtr(ADCDataBufferHeadPtr, MAXIMUM_ADC_DATA_POINTS, ADCDataBufferCount);//update the buffer
	
	if(ADCDataBufferCount >= ADC_RESULTS_TO_WAKE){
		//TODO: wake and run the main thread now to process the waiting data
		//sleep_disable();
	}
	
	//toggleECGLED();

	
	TIFR0 |= (1<<OCF0A);
	
	return;
}

ISR(INT0_vect)
{
	pbPressed = True;
	if(mainState == Alarm)
	{
		silenceAlarm();	
	}
	EIFR &= ~(INTF0);//clear interrupt flag
	return;
}

ISR(USART_RX_vect)
{
	//UCSR0A &= ~(1<<RXC0);
	uartRxBuff[uartRxBufferHeadPtr] = UDR0;//reading this clears the IFG
	IncrementRingBufferHeadPtr(uartRxBufferHeadPtr, UART_RX_BUFF_LENGTH, uartRxBufferCount);
	return;
}
ISR(USART_TX_vect)
{
	//ifg cleared by executing this interrupt UCSR0A |= (1<<TXC0);//clear flag
	if(uartTxBufferCount)//send out next byte if there is one
	{
		UDR0 = uartTxBuff[uartTxBufferTailPtr];
		IncrementRingBufferTailPtr(uartTxBufferTailPtr, UART_TX_BUFF_LENGTH, uartTxBufferCount);	
	}
		
	return;
}

ISR(TIMER1_COMPA_vect)
{
	if(blinkStatusLED.blinking == True)
	{
		if(blinkStatusLED.counter >= blinkStatusLED.period)
		{
			toggleStatusLED();
			blinkStatusLED.counter = 0;
		}
		blinkStatusLED.counter++;
	}
	
	if(blinkRespLED.blinking == True)
	{
		if(blinkRespLED.counter >= blinkRespLED.period)
		{
			toggleRespLED();
			blinkRespLED.counter = 0;
		}
		blinkRespLED.counter++;
	}
	
	if(blinkECGLED.blinking == True)
	{
		if(blinkECGLED.counter >= blinkECGLED.period)
		{
			toggleECGLED();
			blinkECGLED.counter = 0;
		}
		blinkECGLED.counter++;
	}
	
	if(silenceSpeaker.blinking == True) //Needs to be above blinkSpeaker
	{
		turnOffSpeaker(); //silence speaker
		blinkSpeaker.blinking = False; //turn off speaker blinker
		if(silenceSpeaker.counter >= silenceSpeaker.period)
		{
			turnOnSpeaker(); //turn on speaker
			blinkSpeaker.blinking = True;
			silenceSpeaker.blinking = False;
			silenceSpeaker.counter = 0;
		}
		silenceSpeaker.counter++;
	}
	
	if(blinkSpeaker.blinking == True)
	{
		if(blinkSpeaker.counter >= blinkSpeaker.period)
		{
			toggleSpeaker();
			blinkSpeaker.counter = 0;
		}
		blinkSpeaker.counter++;
	}
	

	
}




ISR(TIMER1_COMPB_vect)
{
	while(1);
}

ISR(INT1_vect)
{
	while(1);
}

ISR(PCINT1_vect)
{
	while(1);
}
ISR(PCINT2_vect)
{
	while(1);
}

ISR(WDT_vect)
{
	while(1);
}

ISR(TIMER2_COMPA_vect)
{
	while(1);
}
ISR(TIMER2_COMPB_vect)
{
	while(1);
}
ISR(TIMER2_OVF_vect)
{
	while(1);
}
ISR(TIMER1_CAPT_vect)
{
	while(1);
}


ISR(TIMER1_OVF_vect)
{
	while(1);
}
ISR(TIMER0_COMPA_vect)
{
	while(1);
}
ISR(TIMER0_COMPB_vect)
{
	while(1);
}
ISR(TIMER0_OVF_vect)
{
	while(1);
}
ISR(SPI_STC_vect)
{
	while(1);
}
ISR(USART_UDRE_vect)
{
	while(1);
}
ISR(EE_READY_vect)
{
	while(1);
}
ISR(ANALOG_COMP_vect)
{
	while(1);
}
ISR(TWI_vect)
{
	while(1);
}
ISR(SPM_READY_vect)
{
	while(1);
}
ISR(BADISR_vect)//catchall for debugging etc.
{
	asm("NOP");
	return;
}
