/*
 * File:   main.c
 * Author: Mikael
 *
 * Created on den 27 februari 2016, 14:13
 */

#include "xc.h"

// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)



#include <libpic30.h>  // To be able to use __delay_ms();
#include <stdio.h>
#include "lcd.h"


#define FOSC (8000000UL)
#define FCY (FOSC/2)

#define CW 1
#define CCW 2
#define Idlemove 3

char str[17];
int riktning = 0;
void _ISR _INT3Interrupt(void)
{
    if(_INT3IF){

        if(_RD7 == 0){
            riktning = CW;
        }
        else{
            riktning = CCW;
        }

    }
        _INT3IF = 0;
    
}

void init(void){
    _INT3IE = 1;
    _INT3EP = 1;//NEGATIV FLANK
}
int main(void)
{
    init();
    lcd_init();
    while(1){

        static unsigned char state = 0;

        switch(state){

            case 0: // HOME SCREEN WRITE
                lcd_clear();
                sprintf(str,"Temp: %d | Config",riktning);
                lcd_gotoxy(0,1);
                lcd_putstring(str);
                lcd_gotoxy(0,2);
                lcd_putstring("[|||||       ]");

                lcd_choice(riktning, state);
                if(riktning == 1){

                    state = 0;
                }
                break;
            case 1://Config
                lcd_clear();
                
                lcd_gotoxy(0,1);
                lcd_putstring("Min:xx | Max:xx");
                lcd_gotoxy(0,2);
                lcd_putstring("Back");
                lcd_choice(riktning, state);
                
                break;
            case 2:

                break;
        }
       

    }
}

