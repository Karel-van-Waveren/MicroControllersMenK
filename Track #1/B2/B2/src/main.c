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


void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
int main (void)
{
	/* alle poorten op output zetten */
	DDRD = 0b11111111;
	while(1)
	{
		/* de led op 6 en 7 aan zetten */
		PORTD = 0x60;
		/* 500 ms wachten */
		wait(500);
		/* de leds uit zetten */
		PORTD = 0x00;
		/* 500 ms wachten */	
		wait(500);
	}
	
	return 1;

	/* Insert application code here, after the board has been initialized. */
}
