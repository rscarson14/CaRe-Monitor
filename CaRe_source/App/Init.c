/*
 * Init.c
 *
 * Created: 4/9/2014 10:00:59 PM
 *  Author: Zac
 */ 

//fuses left to default for now pending crystal availability
#include "Init.h"

void MasterInitialize()//called on startup, will call the port setup etc. as well as find the appropriate setting for the pot
{
	cli();//disable interrupts
	
	ADCInit();
	
	PortInit();//these init values (clock and port) are taken directly from our old code
	
	ClockInit();
	
	SerialInit();
		
	sei();//enable interrupts
	
	return;
}

void PortInit()
{
	PORTB = (0<<PORTB7)|(0<<PORTB6)|(0<<PORTB5)|(0<<PORTB4)|(0<<PORTB3)|(1<<PORTB2)|(0<<PORTB1)|(0<<PORTB0); //GPIO
	DDRB = (1<<DDB7)|(1<<DDB6)|(1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
		
	PORTC = (0<<PORTC6)|(0<<PORTC5)|(0<<PORTC4)|(0<<PORTC3)|(0<<PORTC2)|(0<<PORTC1)|(0<<PORTC0); //no portc.7
	DDRC = (0<<DDC6)|(1<<DDC5)|(1<<DDC4)|(1<<DDC3)|(0<<DDC2)|(0<<DDC1)|(0<<DDC0);
		
	PORTD = (0<<PORTD7)|(0<<PORTD6)|(0<<PORTD5)|(0<<PORTD4)|(0<<PORTD3)|(0<<PORTD2)|(0<<PORTD1)|(0<<PORTD0);
	DDRD = (1<<DDD7)|(1<<DDD6)|(1<<DDD5)|(1<<DDD4)|(1<<DDD3)|(0<<DDD2)|(1<<DDD1)|(0<<DDD0);
	
	EICRA = (0<<ISC11)|(0<<ISC10)|(1<<ISC01)|(1<<ISC00);//rising edge interrupt on int0
	EIMSK = (1<<INT0);//enable Interrupt 0
	PCICR = 0x00;
	
	return;
}

void ClockInit()
{
	
	
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 62.500 kHz
	// Mode: CTC top=OCR0A
	// OC0A output: Disconnected
	// OC0B output: Disconnected
	// Timer Period: 3.344 ms
	TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (1<<WGM01) | (0<<WGM00);
	TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00); //Disabled at startup->Enagled in ADCStartRead()
	TCNT0=0x00;
	OCR0A=0xD0;
	OCR0B=0x00;
	 
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 62.500 kHz
	// Mode: CTC top=OCR1A
	// OC1A output: Disconnected
	// OC1B output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 1 s
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0xF4;
	OCR1AL=0x24;
	OCR1BH=0x00;
	OCR1BL=0x00;
	
	// Timer/Counter 1 Interrupt(s) initialization
	TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (1<<OCIE1A) | (0<<TOIE1);
/*
	TCCR0A = 0x00;//timer0 off
	TCCR0B = 0x00;
	
	TCNT0 = 0x00;
	
	OCR0A = 0x00;
	OCR0B = 0x00;
	
	TCCR1A = 0x00;//timer1 at 200kHz, counting to 10 (200Hz)
	TCCR1B = 0x0A;
	
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	
	ICR1H = 0x00;
	ICR1L = 0x00;
	
	OCR1AH = 0x27;//compare to 0x2710 (10000) to get 20Hz
	OCR1AL = 0x10;
	
	OCR1BH = 0x00;
	OCR1BL = 0x00;
	
	ASSR = 0x00;	//timer2
	TCCR2A = 0x00;
	TCCR2B = 0x00;
	TCNT2 = 0x00;
	OCR2A = 0x00;
	OCR2B = 0x00;
	
	TIMSK0 = 0x00;
	
	TIMSK1 = (1<<OCIE1A);//20Hz interrupt enabled
	
	TIMSK2 = 0x00;
*/
	return;
}

