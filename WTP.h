/***************************************************************************
*
*
* WTP.h
*
* Created by Shubham Gupta 
* Copyright (c) shubhamgupta.org  and/or its affiliates.
* All rights reserved.
***************************************************************************/

#ifndef __WTP_HEADER_H__
#define __WTP_HEADER_H__

#include "pins.h"


////////// Water prop temperature//////

#define ONE_WIRE_PORT	PORTD
#define ONE_WIRE_DDR	DDRD
#define ONE_WIRE_PIN	PIND
#define ONE_WIRE_POS	PD2

void AB_STEM_init_DS18B20();
void OneWireAssert(unsigned char *pin);
void OneWireFree(unsigned char *pin);
uint8_t OneWireRead(unsigned char *pin);

uint8_t DS18B20Reset(unsigned char *pin);
void DS18B20Write(unsigned char *pin,uint8_t byte);
uint8_t DS18B20ReadScratchPad(unsigned char *pin);
uint8_t DS18B20Read(unsigned char *pin);
uint16_t AB_STEM_Read_DS18B20(unsigned char *pin);



















#endif //__WTP_HEADER_H__