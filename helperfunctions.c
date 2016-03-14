//AUTHOR: JACOB HEJDERUP
include "helperfunctions.h"

int LimitModulo (int limit, int direction, int value) //Helperfunctions for puttning a limit on int
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
	if(BUTTON_SOMETHING == 1)
	{
		button_pressed = 1;
		return 0;
	}
	if(BUTTON_SOMETHING == 0) && (button_pressed == 1)
	{
		button_pressed = 0;
		return 1;	
	}
	
}
