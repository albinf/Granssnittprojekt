/*
*	NAME: helperfunctions.c
*	AUTHOR: Jacob Hejderup
*	PROJECT: 
*	DATE:
*	CODE REVISION:
*	PURPOSE OF FILE: A c file for helperfunctions. 
*	The purpose of the helperfunctions module is to make the code eaiser to read
*	and keep the code relative short.
*/
#include "helperfunctions.h"


int LimitModulo(int limit, int direction, int value)
{
        value += direction;
	value = value % limit;
	return value < 0 ? value + limit : value;
}
int LimitStop(int upperLimit, int lowerLimit, int direction, int value)
{
	value += direction;
	if(value >= upperLimit)
	{
		value = upperLimit;
	}
	else if(value <= lowerLimit)
	{
		value = lowerLimit;
	}
	return value;
}
int ChangeOnRelease()
{
    static int button_pressed = 0;
	if(PORTAbits.RA3 == 1)
	{
		button_pressed = 1;
		return 0;
	}
        else if((PORTAbits.RA3 == 0) && (button_pressed == 1))
	{
		button_pressed = 0;
		return 1;
	}
        else
        {
            return 0;
        }

}

int ipow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}
