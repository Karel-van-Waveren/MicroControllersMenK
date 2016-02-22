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
#include <asf.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

ISR( INT0_vect)
{
	PORTC = PORTC<<1;
}	





int main (void)
{
	DDRD = 0b00000000;		
	DDRC = 0b11111111;
	EICRA |= 0x0B;				// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;				// Enable INT1 & INT0
	sei();
	
	PORTC=0x01;
	
	while(1)
	{
		
	}
	return 1;
}
