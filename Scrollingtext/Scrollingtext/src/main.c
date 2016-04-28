/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ledmatrix.c
**
** Beschrijving:	Simple HT16K33 Ledmatix demo.
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ledmatrix.c
**					avr-gcc -g -mmcu=atmega128 -o ledmatrix.elf ledmatrix.o
**					avr-objcopy -O ihex ledmatrix.elf ledmatrix.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************/
void twi_init(void)
/* 
short:			Init AVR TWI interface and set bitrate
inputs:			
outputs:	
notes:			TWI clock is set to 100 kHz
Version :    	DMK, Initial code
*******************************************************************/
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

/******************************************************************/
void twi_start(void)
/* 
short:			Generate TWI start condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

/******************************************************************/
void twi_stop(void)
/* 
short:			Generate TWI stop condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x10 | 0x04);
}

/******************************************************************/
void twi_tx(unsigned char data)
/* 
short:			transmit 8 bits data
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}



char res[]= {0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E};
int text[]= {
	0b00000000000000,
	0b00000000000000,
	0b00010111100010,
	0b00010100100010,
	0b00010100100010,
	0b00010100100010,
	0b01110111101110,
	0b00000000000000,
};
int * p;

int write(unsigned char data, unsigned char address){
	twi_start();
	twi_tx(0xE0);		// Display I2C addres + R/W bit
	twi_tx(address);	// Address
	twi_tx(data);		// data
	twi_stop();
}

int writev2(unsigned char data)
{
	twi_start();
	twi_tx(0xE0);		// Display I2C addres + R/W bit
	twi_tx(data);		// data
	twi_stop();	
}
	
void resetdisplay()
{
	int i;
	for(i =0;i < 8; i++)
		write(0x00,res[i]);
}

int * integerduplicate(int const * src, int len)
{
	p = malloc(len * sizeof(int));
	memcpy(p, src, len * sizeof(int));
	return p;
}

/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, trashing the HT16K33
Version :    	DMK, Initial code
*******************************************************************/
{
	
	twi_init();		// Init TWI interface

	// Init HT16K22. Page 32 datasheet
	writev2(0x21);	// Internal osc on (page 10 HT16K33)
	
	writev2(0xA0);	// HT16K33 pins all output

	writev2(0xE3);	// Display Dimming 4/16 duty cycle
	
	writev2(0x81);	// Display OFF - Blink On
	
	
	int bitshift=0, j, idx;
	int* copy;
	while (1)
	{
		resetdisplay();
		copy = integerduplicate(text,14);
		free(p);

		
		for (idx = 0; idx < 8; idx++)
		{
			int data = copy[idx];
			int x = (data >> bitshift) & 1;
			data = copy[idx]>>1;
			if (x == 1)
				data |= 1 << (bitshift+7);
			else
				data &= ~(1 << (bitshift+7));
			copy[idx] = data;
		}

	for(j = 0;j < 8;j++)
		if(bitshift == 10 && j < 7 && j > 1)
			write(copy[j]>>bitshift|0x80,res[j]);	
		else if (bitshift == 11 && j < 7 && j > 5)
			write(copy[j]>>bitshift|0x80,res[j]);
		else if (bitshift == 12 && j < 7 && j > 5)
			write(copy[j]>>bitshift+1|0x80,res[j]);
		else
			write(copy[j]>>bitshift,res[j]);
		
	bitshift++;	
	
	if (bitshift > 14)
	bitshift = 0;
	
	wait(200);
	}
	return 1;
}