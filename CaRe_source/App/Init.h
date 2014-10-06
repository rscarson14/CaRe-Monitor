

#ifndef INIT_H_
#define INIT_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "TypeDefines.h"
#include "ADC_HAL.h"
#include "Serial_HAL.h"

void MasterInitialize();
void PortInit();
void ClockInit();

//I/O defines

//portD
#define POT_UD			7
#define POTINC			6
#define POTCS			5
#define BATSTAT_LED		4
#define AVCC_CTL		3
#define MONITER_EN		2
#define AT_TX			1
#define AT_RX			0

//portC
#define ALMOUT			5
#define LED3			4
#define LED2			3
#define GAINFBI			2
#define VBAT			1
#define VSIG			0


#endif /* INIT_H_ */