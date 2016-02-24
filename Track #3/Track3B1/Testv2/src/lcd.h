/*
 * lcd.h
 *
 * Created: 2/23/2016 10:56:47 AM
 *  Author: marnix
 */ 


#ifndef LCD_H_
#define LCD_H_


extern void init();
extern void lcd_writeChar(char);
extern void lcd_writeLine1(char[]);
extern void lcd_command();
#endif /* LCD_H_ */