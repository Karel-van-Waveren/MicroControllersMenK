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
	{0x06,200},{0x04f,200},{0x6D,200},{0x07,200},{0xEF,200}
};

	void wait(int ms){
		for (int i = 0; i<ms; i++)
		{
			_delay_ms( 1 );
		}
	}
	
	
int main (void)
{
	DDRD = 0b11111111;
	while (1)
	{
	
	int index = 0;
		while( pattern[index].delay !=0 )
		{
			PORTD = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
	
	}
	return 1;	
}
