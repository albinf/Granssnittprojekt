#include "lcd.h"

enum typeofdata
{
    COMMAND = 0,
    DATA
};

static void lcd_write(enum typeofdata type, uint8_t data)
{
    LCD_DATA_LAT = data;     		// Put data on databus
    LCD_CONTROL_RS_LAT = type;  // Pull RS high for data/low for command.
    LCD_CONTROL_E_LAT = 1;    	// Pull E high...
    __delay_us(1);							// ...wait at least 300ns...
    LCD_CONTROL_E_LAT = 0;      // ...and pull E down, this will clock the data in.    
    // Write complete.
    
    /* Instead of polling LCD busy bit, just busywait until it's done for sure. */
    __delay_us(60);     
    /* Clear display (and Return home command) needs ~1.6ms to execute,
       deal with that in their own functions. */
}

void lcd_init(void)
{
	__delay_ms(40);
        LCD_DATA_TRIS = 0x00;
        LCD_CONTROL_E_TRIS = 0;
        LCD_CONTROL_RW_TRIS = 0;
        LCD_CONTROL_RS_TRIS = 0;

        LCD_CONTROL_RS_LAT = 0;
        LCD_CONTROL_RW_LAT = 0;

        //ENTRY MODE SET
        lcd_write(COMMAND, 0b00000100);
        __delay_us(40);

        //DISPLAY ON/OFF CONTROL
        lcd_write(COMMAND, 0b00001100);
        __delay_us(40);

        //FUNCTION SET
        lcd_write(COMMAND, 0b00111100);
        __delay_us(40);

	lcd_clear();
}
void lcd_clear(void){

    LCD_CONTROL_RW_LAT = 0;

    lcd_write(COMMAND, 0b00000001);
    __delay_ms(2);

    lcd_write(COMMAND, 0b00000010);
    __delay_ms(2);
}
void lcd_choice(int val, char state){

    lcd_write(COMMAND, 0b00001111);
    __delay_us(40);
    if(state == 0)
        lcd_gotoxy(10,1);
    else if(state == 1){

        if(val == CW){
            lcd_gotoxy(5,1);
        }
        else if(val == CCW){
            lcd_gotoxy(14,1);
        }
    }


}
void lcd_putchar(char c){
    LCD_CONTROL_RW_LAT = 0;
    lcd_write(DATA,c);
    __delay_us(43);
}
void lcd_putstring(char *str){
    LCD_CONTROL_RW_LAT = 0;
    while(*str)
        lcd_putchar(*str++);

}
void lcd_gotoxy(int8_t x, int8_t y){
    int8_t P;

    lcd_write(COMMAND, 0b00000010);
    __delay_ms(2);
    if(y == 1){
        P = 0b10000000 + x;
        lcd_write(COMMAND,P);
    }
    else{

        P = 0b10000000 + x + 0x40;
        lcd_write(COMMAND,P);
    }
    __delay_us(43);
}
