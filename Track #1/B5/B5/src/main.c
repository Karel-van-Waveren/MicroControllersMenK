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

typedef struct {
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x00, 100}, {0x01, 100}, {0x03, 100}, {0x07, 100}, {0xF, 100}, {0x1F, 100}, {0x3F, 100}, {0x7F, 100}, {0xFF,100},
	{0x00, 100},
	{0x00, 100}, {0x01, 100}, {0x03, 100}, {0x07, 100}, {0xF, 100}, {0x1F, 100}, {0x3F, 100}, {0x7F, 100}, {0xFF,100},
	{0x00, 100},
	{0x03, 100}, {0x06, 100}, {0x0C, 100}, {0x18, 100}, {0x30, 100}, {0x60, 100}, {0xC0, 100},
	{0x00, 100},
	{0x03, 100}, {0x06, 100}, {0x0C, 100}, {0x18, 100}, {0x30, 100}, {0x60, 100}, {0xC0, 100},
	{0x00, 100},
	{0xAA,  200}, {0x55,  200},
	{0xAA,  200}, {0x55,  200},
	{0xAA,  200}, {0x55,  200},
	{0x00, 100},
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

int main (void)
{
	
	DDRD = 0b11111111;					// PORTD all output
	
	while (1==1)
	{
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTD
			PORTD = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}

	return 1;
	
}
