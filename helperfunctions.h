//AUTHOR: JACOB HEJDERUP
#ifndef HELPERFUNCTIONS_H_INCLUDED 
#define HELPERFUNCTIONS_H_INCLUDED

int LimitModulo(int limit, int direction, int value);// Starts from 0 after reaching max limit

int LimitStop(int upperLimit, int lowerLimit, int direction, int value); // stops when reaching max limit, or min limit
