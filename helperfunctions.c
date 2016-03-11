//AUTHOR: JACOB HEJDERUP
include "helperfunctions.h"

int LimitModulo (int limit, int direction, int value) //Helperfunctions for puttning a limit on int
{
	value += direction;
	return value = value % limit;
}