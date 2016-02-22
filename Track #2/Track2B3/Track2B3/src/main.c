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

uint8_t lookuptable[] =
{
	0x3F,0x06,0x5B,0x4f,0x66,0x6D,0x7D,0x07,0xFF,0xEF,0x77,0x7C,0x39,0x5E,0x79,0x71 //alle waardes voor alle cijfers
};

	void wait(int ms){
		for (int i = 0; i<ms; i++)
		{
			_delay_ms( 1 );
		}
	}
	
	void display(int i){ // een functie voor de lookuptable
		if(0 <= i && i <=15){
		PORTD = lookuptable[i];
		}
		else
		PORTD = 0x79;
 
	}
	
int main (void)
{

	DDRC = 0b00000000;
	DDRD = 0b11111111;
	int i = 0;
	while (1)
	{
		display(i);
		wait (100);
		if ( PINC & 0x01 && PINC & 0x02){
			i = 0;
		}
		else if(PINC & 0x01)
		{
			if(i <= 15)
			i++;
		}
		else if(PINC & 0x02)
		{
			if (i >= 0)
			i--;
		}
	}
	return 1;
}