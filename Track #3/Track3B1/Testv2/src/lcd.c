/*
 * lcd.c
 *
 * Created: 2/23/2016 10:53:39 AM
 *  Author: marnix
 */ 
#include <asf.h>
#include <util/delay.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void)
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			
}

void lcd_command ( unsigned char dat )
{
		// First nibble.
		PORTC = dat;
		PORTC &= ~(1<<LCD_RS);
		lcd_strobe_lcd_e();

		// Second nibble
		PORTC = (dat<<4);
		PORTC &= ~(1<<LCD_RS);
		lcd_strobe_lcd_e();
}

void init()
{
	DDRC = 0xFF;
	PORTC = 0x00;
	lcd_command(0x02); //initialiseren van lcd
	lcd_command(0x28);
	lcd_command(0x0C);
	lcd_command(0x06);
	lcd_command(0x80);
}

void lcd_write_char(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_writeLine1 ( char *str )
{
	// eerst de eerste 8 karakters = regel 1
	// eerste pos regel 1
	for(;*str; str++){
		lcd_write_char(*str);
	}
}
