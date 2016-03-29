/* 
 * File:   main.c
 * Author: heja1414
 *
 * Created on den 16 mars 2016, 09:42
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include <libpic30.h>
#include "helperfunctions.h"
#include "userinput.h"
#include "lcd.h"
#include "temp.h"
#include "adc.h"
#include "gui.h"



/*
 * 
 */
#define FOSC (8000000UL)
#define FCY (FOSC/2)

// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON

#define CW -1
#define CCW 1
unsigned int temp = 0;

uint16_t ADC_10bit = 0b0000000000;
uint16_t i2c_event = 0;
int riktning = 0;
int ms_counter = 0;
int ms_counter2 = 0;
char start_read = 0;
char start_draw = 0;
struct input h_input;
struct displayData h_displayData;
void _ISR _T1Interrupt (void)//varje 1 ms
{

    ms_counter++;
    ms_counter2++;
    if(ms_counter == 50)
    {
        ms_counter = 0;
        start_read = 1;
    }
    if(ms_counter2 == 100){
        ms_counter2 = 0;
        start_draw = 1;
    }
    _T1IF = 0; // Clear interrupt flag
}
void _ISR _INT2Interrupt(void)
{
    i2c_event = 1;
}
void _ISR _INT3Interrupt(void)
{
        if(_RD7 == 0){ //clockwise
            if(!_INT3EP)
                riktning = CW;
            else
                riktning = CCW;
        }
        if(_RD7 == 1){ //counter clockwise
            if(!_INT3EP)
                riktning = CCW;
            else
                riktning = CW;
        }
        _INT3EP = !_INT3EP;

        _INT3IF = 0;
}

//RD7,RA14  encoder
//RA3 KNAPP på encoder
void init()
{
    TRISAbits.TRISA3 = 1;
    TRISDbits.TRISD15 = 0;
    _INT3IE = 1;
    _INT3EP = 0;//pos FLANK
    lcd_init();
    ADC_INIT();
    h_displayData = DisplayInit(h_displayData);
    h_input = UserInputInit(h_input);

    TMR1 = 0x0000;          // Clear timer counter.
    PR1 = 500-1;            // Interrupt every ms.
    T1CONbits.TCKPS = 0x1;  // Count at 4MHz/8.
    T1CONbits.TON = 1;      // Start timer.
    _T1IF = 0;              // Clear interrupt flag, just in case.
    _T1IE = 1;              // Enable timer interrupt.


    //SI2C1IF: Slave I2C1 Event Interrupt Flag Status bit
    //SI2C1IE: Slave I2C1 Event Interrupt Enable bit
    //I2C1CON
    //touch shield --->  VDD 0x5B slave adress
    // I2CxBRG = 0x25 // 100khz i2c clock rate
    // I2CxCON = 0b1000 0000 0000 0000
    //I2C1RCV recieve register
    //I2C1TRN transmitte registurs
   //  I2CxADD slav adress här.

    //  IRQ pinne för interrubt

    /*
     I2C1ADD = 0x5A;
     * I2C1CONbits.SEN = 1;
     *
     * I2C1TRN = I2C1ADD + R/W bit
     * I2C1CONbits.ACKEN = 1;
     *
     * I2C1TRN = DATA;
     * I2C1CONbits.ACKEN = 1;
     *
     * I2C1CONbits.PEN = 1;
     *
     * KOLLA FLAG I INTERRUBT O HÄMTA I2C1RCV
     *
     */




}

char str[17];

int main(int argc, char** argv) {
    init();
    char startfan;
    while(1)
    {
        if(start_read == 1){
            ADC_10bit = ADC_READ();
            temp = temp_calc(ADC_10bit);
            h_displayData = SplitNumber(temp);
            startfan = checktemp(h_displayData.heltals, h_input.tempMinLimit, h_input.tempMaxLimit);
            LATDbits.LATD15 = startfan;
            start_read = 0;
        }
        
        
        if(riktning != 0)
        {
            h_input = EncoderPosition(h_input, riktning);
            riktning = 0;
        }
        if( ChangeOnRelease())
        {
            lcd_clear();
            h_input = ConfirmSelection( h_input);
            
        }
        if(start_draw == 1){
            writewindow(h_input, h_displayData);
            start_draw = 0;
        }

    }
    return (EXIT_SUCCESS);
}

