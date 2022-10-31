#include "Delay.h"

/**
Delay function
**/
void Delay1ms(int s)		//@12.000MHz
{
	unsigned char i, j;
	i = 12*s;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}