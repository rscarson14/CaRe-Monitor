
#ifndef FILT_H_
#define FILT_H_

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "Globals.h"
#include "TypeDefines.h"

#define RESP_FILT_ORDER 150
#define ECG_FILT_ORDER 162

uint8_t RespFilt(uint16_t *rawData);
uint8_t ECGFilt(uint16_t *rawData);

#endif /* FILT_H_ */