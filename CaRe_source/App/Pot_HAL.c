#include "Pot_HAL.h"

void IncreaseGain(uint8_t amount)
{
	uint8_t i;
	SELECT_INCREMENT;
	for(i=amount;i>0;i--)
	{
		INCREMENT_POT;
	}
	return;
}

void DecreaseGain(uint8_t amount)
{
	uint8_t i;
	SELECT_DECREMENT;
	for(i=amount;i>0;i--)
	{
		INCREMENT_POT;
	}
	return;
}

void DeselectPot()
{
	
	DESELECT_POT;
	return;
}

void SelectPot()
{
	SELECT_POT;
	return;	
}
