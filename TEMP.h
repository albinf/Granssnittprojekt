/* 
 * File:   TEMP.h
 * Author: Albin
 *
 * Created on den 9 mars 2016, 12:04
 */

#ifndef TEMP_H
#define	TEMP_H


#define FOSC (8000000UL)
#define FCY (FOSC/2)

#include <libpic30.h>  // To be able to use __delay_ms();

#include <xc.h> // include processor files
#include <stdint.h>

void ReadADC();//Reads the value from ADC

void VoltageToTemp(); // Converts voltage to temperatur










#endif	/* TEMP_H */

