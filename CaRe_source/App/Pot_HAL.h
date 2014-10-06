#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#ifndef POT_HAL_H_
#define POT_HAL_H_

#define POT_UD			7
#define POTINC			6
#define POTCS			5


#define SELECT_POT			PORTD &= ~(1<<POTCS)
#define DESELECT_POT		PORTD |= (1<<POTCS)
#define SELECT_INCREMENT	PORTD |= (1<<POT_UD)
#define SELECT_DECREMENT	PORTD &= ~(1<<POT_UD)

#define INCREMENT_POT	PORTD ^= (1<<POTINC);	\
						PORTD ^= (1<<POTINC);

void IncreaseGain(uint8_t amount);
void DecreaseGain(uint8_t amount);
void DeselectPot();
void SelectPot();


#endif /* POT_HAL_H_ */