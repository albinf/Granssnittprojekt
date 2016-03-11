//AUTHOR: JACOB HEJDERUP
include "helperfunctions.h"

int LimitModulo (int limit, int direction, int value) //Helperfunctions for puttning a limit on int
{
	value += direction;
	return value = value % limit;
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
