/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"

#define F_CPU 8000000;

unsigned int counter = 0;


void Lcd_WriteFirstLine(char * text){
	set_cursor(0,1);
	while(*text) {
		lcd_writeLine1(*text++);
	}
}


void Lcd_WriteSecondLine(char * text){
	set_cursor(0,2);
	while(*text) {
		lcd_writeLine1(*text++);
	}
}



ISR( TIMER2_OVF_vect )
{
	counter++;			// Increment counter
	TCNT2 = -2;
}

// Initialize timer2
//
void timer2Init( void )
{
	TCNT2 = -2;				// of  TCNT2=0xf6
	TIMSK |= (1 << TOIE2);			// T2 overflow interrupt enable, p. 162
	//TCCR2 = 0b00011111;		// counter, normal mode, run
	TCCR2 |= (1 << CS20) | (1 << CS21) | (1 << CS22) | (1 << WGM21) | (1 << COM20);
}



int main(void)
{
	DDRC = 0xFF; //PORTC als ouput
	DDRD = 0b00000000;

	timer2Init();

	sei();

	init(); //Initializeert LCD scherm in 4 bit mode
	char str[5];	
	lcd_writeLine1("Swag boy");
	while(1)
	{
		set_cursor(0,2);
		sprintf(str,"%d    ", counter); // schrijft de waarde van counter
		lcd_writeLine1(str);
	}
}
