/***************************************************************************
*
*
* WTP.c
*
* Created by Shubham Gupta 
* Copyright (c) shubhamgupta.org  and/or its affiliates.
* All rights reserved.
***************************************************************************/

#include "WTP.h"


////////////////////////////////// Water prop temperature////////////////

/*
Makes data line low
*/
void OneWireAssert(unsigned char *pin)
{
	setValue(pin,AB_LOW);
	setDirection(pin,AB_OUTPUT);
	//PORTD&=~(1<<PD2);//low
	//DDRD|=(1<<PD2);//output
	
}

/*
Releases the data line and the external pullup makes it HIGH
*/
void OneWireFree(unsigned char *pin)
{
	setDirection(pin,AB_INPUT);
	//DDRD&=~(1<<PD2);//input
}

/*
Reads the logic data i.e. 0 or 1 present on the DATA line
*/ 
uint8_t OneWireRead(unsigned char *pin)
{
	return (digitalRead(pin)); // check pin 
}

uint8_t DS18B20Reset(unsigned char *pin)
{
	OneWireAssert(pin);
	
	_delay_us(500);
	
	OneWireFree(pin);
	
	uint8_t i;
	
	for(i=0;i<40;i++)
	{
		if(OneWireRead(pin)==0) break;
		_delay_us(2);
	}
	
	if(i==40)
		return	0;
		
	for(i=0;i<30;i++)
	{
		if(OneWireRead(pin)==1) break;
		_delay_us(10);
	}
	
	return 1;
	
}

void DS18B20Write(unsigned char *pin ,uint8_t byte)
{
	for(uint8_t i=0;i<8;i++)
	{
		OneWireAssert(pin);
		
		_delay_us(2);
		
		if(byte & 0b00000001)
		{
			OneWireFree(pin);
		}
		
		_delay_us(70);
		
		OneWireFree(pin);
		
		_delay_us(1);
		
		byte=byte>>1;
	}
}

uint8_t DS18B20Read(unsigned char *pin)
{
	uint8_t byte=0x00;
	
	for(uint8_t i=0;i<8;i++)
	{
		byte=byte>>1;
		
		OneWireAssert(pin);
		
		_delay_us(2);
		
		OneWireFree(pin);
		
		_delay_us(15);
		
		if(digitalRead(pin)) // check pin 
			byte|=0b10000000;
		
		_delay_us(60);
			
	}
	
	return byte;
}



uint8_t ds18b20_scratch_pad[9];

uint8_t DS18B20ReadScratchPad(unsigned char *pin)
{
	DS18B20Reset(pin);
	
	DS18B20Write(pin,0xCC);
	
	DS18B20Write(pin,0xBE);
	
	for(uint8_t i=0;i<8;i++)
	{
		ds18b20_scratch_pad[i]=DS18B20Read(pin);
	}
}

uint16_t AB_STEM_Read_DS18B20(unsigned char *pin) // main function that return Temperature
{
	DS18B20Reset(pin);
	
	DS18B20Write(pin,0xCC);
	
	DS18B20Write(pin,0x44);
	
	uint8_t i;
	
	for(i=0;i<100;i++)
	{
		if(DS18B20Read(pin)!=0)
			break;
			
		_delay_ms(10);
	}
	
	if(i==200)
		return	0;
		
	DS18B20ReadScratchPad(pin);
	
	return ((((ds18b20_scratch_pad[1]&0b00001111)<<8)|ds18b20_scratch_pad[0])>>4);
	
}

int main()
{
	int wtpValue=0;
	
	while(1)
	{
		wtpValue=AB_STEM_Read_DS18B20("PD_4")	;	///// gives you the Temperature
	}

		return 0;
}
