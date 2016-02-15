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

enum states {
	LED_SLOW,
	LED_FAST
};

enum states state = LED_SLOW;

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}
int main (void)
{
	DDRD = 0b11111111;	
	DDRC = 0b00000000;
	while (1)
	{
		if(PINC & 0x01)//Switch from slow to fast or fast to slow if pinc is pressed
		{
			if(state == LED_SLOW)
				state = LED_FAST;
			else
				state = LED_SLOW; 
		}
		switch(state){
		case LED_SLOW:
		PORTD = 0x40;
		wait( 500 );
		PORTD = 0x00;
		wait( 500 );
		break;
		case LED_FAST:
		PORTD = 0x40;
		wait( 125 );
		PORTD = 0x00;
		wait( 125 );
		break;	
		}
	}
	return 1;
}
