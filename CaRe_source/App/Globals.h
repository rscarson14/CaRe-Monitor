


#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdint.h>

#include "TypeDefines.h"

#define MAXIMUM_ADC_DATA_POINTS	30//two cycles of data

#define UART_TX_BUFF_LENGTH		25 //25 bytes can be queued in the TX buff
#define UART_RX_BUFF_LENGTH		25 //ditto for RX

#define IncrementRingBufferTailPtr(a,b,c)			if(c){			\
													a++;			\
													c--;			\
													if(a >= b){		\
														a = 0;		\
													}				\
													}				//increment the tail pointer(a) in a ring buffer of length (b), and update the data in buffer count (c)

#define IncrementRingBufferHeadPtr(a,b,c)			if(c<b)			\
													{				\
														a++;			\
														c++;			\
														if(a >= b){		\
															a = 0;		\
														}				\
													}					//increment the head pointer(a) in a ring buffer of length (b), and update the data in buffer count (c)
#define IncrementRingBufferPtr(a,b)					a++;				\
													if(a>=b)			\
													{					\
														a = 0;			\
													}			
													
#ifdef _GLOBALS_C_

	#define _MAIN_
	volatile State mainState = Init;//start out at initialize

	#define _ADC_DATA_BUFFER_//the ADC data buffer, this array will be filled by the ADC ISR

	volatile uint16_t ADCDataBuffer[MAXIMUM_ADC_DATA_POINTS];//consider the possibility of using only the 8 MSB of the ADC result for quicker operation
	volatile uint8_t ADCDataBufferTailPtr = 0;
	volatile uint8_t ADCDataBufferHeadPtr = 0;
	volatile uint8_t ADCDataBufferCount = 0;

	#define _UART_COMMS_

	volatile uint8_t uartTxBuff[UART_TX_BUFF_LENGTH];
	volatile uint8_t uartTxBufferHeadPtr = 0;
	volatile uint8_t uartTxBufferTailPtr = 0;
	volatile uint8_t uartTxBufferCount = 0;

	volatile uint8_t uartRxBuff[UART_RX_BUFF_LENGTH];
	volatile uint8_t uartRxBufferHeadPtr = 0;
	volatile uint8_t uartRxBufferTailPtr = 0;
	volatile uint8_t uartRxBufferCount = 0;

	#define _PUSH_BUTTON_
	
	volatile boolean pbPressed = False;
	
	#define _BLINKERS_
	
	volatile BLINKER blinkRespLED = {.blinking = False, .counter = 0, .period = 0};
	volatile BLINKER blinkECGLED = {.blinking = False, .counter = 0, .period = 0};
	volatile BLINKER blinkStatusLED = {.blinking = False, .counter = 0, .period = 0};
	volatile BLINKER blinkSpeaker = {.blinking = False, .counter = 0, .period = 0};
	volatile BLINKER silenceSpeaker = {.blinking = False, .counter = 0, .period = 0};
	
	
	
#endif
/*all .c files that are not globals.c*/
	#ifdef _MAIN_
	extern volatile State mainState;//start out at initialize
	#endif
		
	#ifdef _ADC_DATA_BUFFER_

	extern volatile uint16_t ADCDataBuffer[];//consider the possibility of using only the 8 MSB of the ADC result for quicker operation
	extern volatile uint8_t ADCDataBufferTailPtr;
	extern volatile uint8_t ADCDataBufferHeadPtr;
	extern volatile uint8_t ADCDataBufferCount;

	#endif

	#ifdef _UART_COMMS_

	extern volatile uint8_t uartTxBuff[];
	extern volatile uint8_t uartTxBufferHeadPtr;
	extern volatile uint8_t uartTxBufferTailPtr;
	extern volatile uint8_t uartTxBufferCount;

	extern volatile uint8_t uartRxBuff[];
	extern volatile uint8_t uartRxBufferHeadPtr;
	extern volatile uint8_t uartRxBufferTailPtr;
	extern volatile uint8_t uartRxBufferCount;

	#endif
	
	#ifdef _PUSH_BUTTON_
	
	extern volatile boolean pbPressed;	
	
	#endif
	
	#ifdef _BLINKERS_
	
	extern volatile BLINKER blinkRespLED;
	extern volatile BLINKER blinkECGLED;
	extern volatile BLINKER blinkStatusLED;
	extern volatile BLINKER blinkSpeaker;
	extern volatile BLINKER silenceSpeaker;
	
	#endif

#endif /* GLOBALS_H_ */