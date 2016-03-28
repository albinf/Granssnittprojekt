/*
*	NAME: helperfunctions.h
*	AUTHOR: Jacob Hejderup
*	PROJECT: 
*	DATE:
*	CODE REVISION:
*	PURPOSE OF FILE: A header file for helperfunctions. 
*	The purpose of the helperfunctions module is to make the code eaiser to read
*	and keep the code relative short.
*/


#ifndef HELPERFUNCTIONS_H
#define	HELPERFUNCTIONS_H
#include "gui.h"
#include <stdlib.h>
#include <xc.h>
#include <libpic30.h>


/***********************************************************************
*LimitModulo
*	Function Description: 
*		Add or subtract 1 out of value and puts a limit on value. 
*		when the value reaches the limit, the value resets to zero via modulo. 
*		The direction variable decides if value should be value + 1 or value  - 1. 
*		returns value after checking limit.
*
*	Input: int limit, int direction, int value
*	Output: int value
***********************************************************************/
int LimitModulo(int limit, int direction, int value);

/***********************************************************************
*LimitStop
*	Function Description: 
*		Add or subtract 1 out of value and puts a limit on value. 
*		when the value reaches the limit, the value gets set to lowerLimit or upperLimit 
*		depending if value is lower than lowerLimit or higher than upperlimit. 
*		The direction variable decides if value should be value + 1 or value  - 1. 
*		returns value after checking limit.
*
*	Input: int upperLimit, int lowerLimit, int direction, int value
*	Output: int value
***********************************************************************/
int LimitStop(int upperLimit, int lowerLimit, int direction, int value);

/***********************************************************************
*ChangeOnRelease
*	Function Description: 
*		Check if a button is pressed, if that button is pressed set button_pressed to 1 
*		and return 0. If that button is not pressed and button_pressed is 1, 
*		set the button_pressed to 0 and return 1. 
*		
*	Input: void
*	Output: int 0 or 1
***********************************************************************/
int ChangeOnRelease();

/***********************************************************************
*ipow
*	Function Description: 
*		Calculates base power of exp.
*		
*	Input: int base, int exp
*	Output: int value
***********************************************************************/
int ipow(int base, int exp);


#endif	/* HELPERFUNCTIONS_H */

