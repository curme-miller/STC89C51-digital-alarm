#include "TimerControl.h"
#include <REGX51.H>

/**
Timer control
**/
void Timer1(short flag)
{
	if(flag == START)
	{
		TR1 = 1;
		ET1 = 1;
	}
	if(flag == STOP)
	{
		TR1 = 0;
		ET1 = 0;
	}
}

void Timer0(short flag)
{
	if(flag == START)
	{
		TR0 = 1;
		ET0 = 1;
	}
	if(flag == STOP)
	{
		TR0 = 0;
		ET0 = 0;
	}
}