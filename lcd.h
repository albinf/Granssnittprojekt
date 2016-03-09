#ifndef LCD_H
#define	LCD_H

#define FOSC (8000000UL)
#define FCY (FOSC/2)

#include <libpic30.h>  // To be able to use __delay_ms();

#include <xc.h> // include processor files
#include <stdint.h>

#define LCD_DATA_LAT        LATE		// Lower 8 bits used.
#define LCD_DATA_TRIS       TRISE

#define LCD_CONTROL_E_LAT     _LATD4
#define LCD_CONTROL_E_TRIS    _TRISD4

#define LCD_CONTROL_RW_LAT    _LATD5
#define LCD_CONTROL_RW_TRIS    _TRISD5

#define LCD_CONTROL_RS_LAT    _LATB15
#define LCD_CONTROL_RS_TRIS    _TRISB15

#define CW 1
#define CCW 2

void lcd_init(void);

void lcd_clear(void);
void lcd_gotoxy(int8_t x, int8_t y);
void lcd_putchar(char c);
void lcd_putstring(char *str);
void lcd_choice(int val, char state);

#endif

