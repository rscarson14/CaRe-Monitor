/*
 * Serial_HAL.h
 *
 * Created: 4/9/2014 10:53:44 PM
 *  Author: Zac
 */ 


#ifndef SERIAL_HAL_H_
#define SERIAL_HAL_H_


#define _UART_COMMS_ //get access to UART buffers

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "TypeDefines.h"
#include "Globals.h"

void SerialInit();
void SendDecimalNumber(uint16_t num);
void SendString(char str[], uint8_t length);
uint8_t RetrieveChar();
boolean LoadChar(uint8_t character);
void StartTx();

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);


#endif /* SERIAL_HAL_H_ */