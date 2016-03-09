/* 
 * File:   ADC.h
 * Author: Albin
 *
 * Created on den 9 mars 2016, 12:13
 */

#ifndef ADC_H
#define	ADC_H
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <libpic30.h>  // To be able to use __delay_ms();


void ADC_INIT(void);
uint16_t ADC_READ(void);






#endif	/* ADC_H */

