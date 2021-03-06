/*
* Project name:
Demo4_5 : PWM with timer 1 Fast PWM mode at PORTB.5, PB.6 en PB.7
parallel, 3x, for RGB LED
* Author: Avans-TI, JW
* Revision History:
20101230: - initial release;
* Description:
This program gives an interrupt on each ms
* Test configuration:
MCU:             ATmega128
Dev.Board:       BIGAVR6
Oscillator:      External Clock 08.0000 MHz
Ext. Modules:    -
SW:              AVR-GCC
* NOTES:
- Turn ON the PORT LEDs at SW12.1 - SW12.8
*/
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

unsigned int sCount=0, minutes=0, hours=0;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

// Initialize timer 1: fast PWM at pin PORTB.6 (hundredth ms)
void timer1Init( void )
{
	OCR1A = 255;					// RED, default, off
	OCR1B = 255;					// GREEN, default, off
	OCR1C = 255;					// BLUE, default, off
	TCCR1A = 0b10101001;		// compare output OC1A,OC1B,OC1C
	TCCR1B = 0b00001011;		// fast PWM 8 bit, prescaler=64, RUN
}

// Set pulse width for RED on pin PB5, 0=off, 255=max
void setRed( unsigned char red )
{
	OCR1A = red;
}

void setGreen( unsigned char green )
{
	OCR1B = green;
}

void setBlue( unsigned char blue )
{
	OCR1C = blue;
}





// void setGreen( unsigned char green)
// void setBlue( unsigned char blue)

// Main program: Counting on T1
int main( void )
{
	DDRB = 0xFF;					// set PORTB for compare output
	timer1Init();
	wait(100);
	setRed (255);
	setGreen(255);
	setBlue(255);
	
	int deltaRed = 1;
	int deltaGreen = 1;
	int deltaBlue = 1;
	
	for (int red = 255; red>=0; red-=deltaRed)
	{
		setRed( red );				// 8-bits PWM on pin OCR1a
		deltaRed += 2;					// progressive steps up
		wait(10);					// delay of 100 ms (busy waiting)
	}
	wait(100);
	while (1)
	{


		// change some colors
		// RED

		
		for (int green = 255; green>=0; green-=deltaGreen)
		{
			setGreen( green );				// 8-bits PWM on pin OCR1a
			deltaGreen += 2;					// progressive steps up
			wait(10);					// delay of 100 ms (busy waiting)
		}
		
		wait(100);
		for (int red = 0; red<=255; red+=deltaRed)
		{
			setRed( red );				// 8-bits PWM on pin OCR1a
			deltaRed -= 2;					// progressive steps down
			wait(10);					// delay of 100 ms (busy waiting)
		}
		//setRed( 0 );
		deltaRed = 1;
		wait(100);
		for (int blue = 255; blue>=0; blue-=deltaBlue)
		{
			setBlue( blue );				// 8-bits PWM on pin OCR1a
			deltaBlue += 2;					// progressive steps up
			wait(10);					// delay of 100 ms (busy waiting)
		}
		wait(100);
		for (int green = 0; green<=255; green+=deltaGreen)
		{
			setGreen( green );				// 8-bits PWM on pin OCR1a
			deltaGreen -= 2;					// progressive steps down
			wait(10);					// delay of 100 ms (busy waiting)
		}
		//setRed( 0 );
		deltaGreen = 1;
		wait(100);

		for (int red = 255; red>=0; red-=deltaRed)
		{
			setRed( red );				// 8-bits PWM on pin OCR1a
			deltaRed += 2;					// progressive steps up
			wait(10);					// delay of 100 ms (busy waiting)
		}
		wait(100);
		for (int blue = 0; blue<=255; blue+=deltaBlue)
		{
			setBlue( blue );				// 8-bits PWM on pin OCR1a
			deltaBlue -= 2;					// progressive steps down
			wait(10);					// delay of 100 ms (busy waiting)
		}
		//setRed( 0 );
		deltaBlue = 1;
		wait(100);
		// GREEN
		// for (int gr = 0; gr<=255; gr+=delta)
		// . . .

		// BLUE
		// for (int blue = 0; blue<=255; blue+=delta)
		// . . .


		// YELLOW
		// for (int yellow= 0; yellow<=255; yellow += delta)
		// . . .


		// WHITE
		// for (int white = 0; white<=255; white += delta)
		// . . .
	}
}