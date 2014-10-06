#include "Serial_HAL.h"


	
void SerialInit()
{
	//115200
	//8 bits
	//no parity
	#define F_OSC		16000000
	#define BAUD		115200
	#define UBBR_VALUE	16//(uint16_t)(F_OSC/(8*BAUD) - 1)	//page179
	//for information on USART, see pages 197 - 200 of the data sheet
	UBRR0H = (uint8_t)((UBBR_VALUE)>>8);
	UBRR0L = (uint8_t)(UBBR_VALUE);
	
	UCSR0A = (1<<U2X0);
	UCSR0B = (1<<RXCIE0)|(1<<TXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	stdout = &mystdout;
	//UCSR0C default values select what we want 
	
	return;
}
boolean LoadChar(uint8_t character)
{
	boolean retVal = True;//set false if an error occurs
	
	if(uartTxBufferCount < UART_TX_BUFF_LENGTH)
	{
		uartTxBuff[uartTxBufferHeadPtr] = character;
		IncrementRingBufferHeadPtr(uartTxBufferHeadPtr, UART_TX_BUFF_LENGTH, uartTxBufferCount);
	}
	else //buffer full, do not overflow
	{
		retVal = False;
	}
	return retVal;
}

uint8_t RetrieveChar()
{
	uint8_t retVal;
	retVal = uartRxBuff[uartRxBufferTailPtr];
	if(uartRxBufferCount)//do not increment pointer if buffer is empty
	{
		IncrementRingBufferTailPtr(uartRxBufferTailPtr, UART_RX_BUFF_LENGTH, uartRxBufferCount);
	}
	return retVal;
}

void SendString(char str[], uint8_t length)
{
	int8_t i;

	LoadChar('\n');
	LoadChar('\r');
	for(i=0; i<length; i++)
	{
		if(!LoadChar(str[i]))
		{
			break;//buffer too full
		}
	}
	StartTx();
	return;
}


void SendDecimalNumber(uint16_t num)
{
	const uint8_t decimalConversion[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	uint8_t thousands;
	uint8_t hundreds;
	uint8_t tens;
	uint8_t ones;
	
	
	thousands = num/1000;
	hundreds = (num-(thousands*1000))/100;
	tens = (num -(thousands*1000)-(hundreds*100))/10;
	ones = num - thousands*1000 - hundreds*100 - tens*10;

	if(thousands)
	{
		LoadChar(decimalConversion[thousands]);
	}
	
	if(hundreds)
	{
		LoadChar(decimalConversion[hundreds]);
	}
	if(tens)
	{
		LoadChar(decimalConversion[tens]);
	}
	LoadChar(decimalConversion[ones]);
	
	StartTx();	
	return;
}
void StartTx()
{	
	if(uartTxBufferCount)
	{
		while ( !( UCSR0A & (1<<UDRE0)) ){
		}
		UDR0 = uartTxBuff[uartTxBufferTailPtr];
		IncrementRingBufferTailPtr(uartTxBufferTailPtr, UART_TX_BUFF_LENGTH, uartTxBufferCount);
	}
	return;
}

static int uart_putchar(char c, FILE  *stream){
	while ( !( UCSR0A & (1<<UDRE0)) ){
	}
	UDR0 = c;
	return 0;
}
