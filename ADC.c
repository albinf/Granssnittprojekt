#include "ADC.h"


void ADC_INIT(void){
    AD1CHS = 9;
    AD1CON2bits.VCFG = 0x0 ;//internal
    AD1CON3bits.ADCS = 0xFF ;
    AD1CON1bits.SSRC = 0x0 ;
    AD1CON3bits.SAMC = 0b10000 ;
    AD1CON1bits.FORM = 0b00 ;
    AD1CON2bits.SMPI = 0x0 ;
    AD1CON1bits.ADON = 1 ;
    //__delay_us(20);
    uint16_t i;
    for(i = 0; i < 1000;i++){};
    AD1PCFGbits.PCFG9 = 0 ; // ENABLE ADC
}
uint16_t ADC_READ(void){
    uint16_t i ;
    AD1CON1bits.SAMP = 1 ;           //Start sampling
    for (i = 0 ; i < 1000 ; i++) ; //Sample delay, conversion start automatically

    AD1CON1bits.SAMP = 0 ;           //Start sampling
    for (i = 0 ; i < 1000 ; i++) ; //Sample delay, conversion start automatically
    while (!AD1CON1bits.DONE) ;       //Wait for conversion to complete

    return ADC1BUF0;
}
