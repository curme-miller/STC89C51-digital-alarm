#include <REGX51.H>
#include "Delay.h"
#include "TimerControl.h"
#include "Display.h"
#include "LCD1602.h"

static int num = 0, number = 0, ring_num = 0;
short hour = 16, minute = 59, second = 52, micro = 0, month = 10, day = 15;
short temp_minute = 0, temp_second = 0;
short flag = 0, ring = 0;

sbit MenuButton = P2^0;
sbit TimeButton = P2^1;
sbit SetButton = P2^2;
sbit TimerButton = P2^3;
sbit SS_1date = P2^4;
sbit TR_2time = P2^5;
sbit Clear_Hour = P2^6;
sbit Month_Minute = P2^7;
sbit Day_Second = P3^0;
sbit RING = P1^3;

void main()
{
	TMOD = 0x22;
	TH0 = 0x06;
	TL0 = 0x06;
	TH1 = 0x06;
	TL1 = 0x06;
	PT0 = 0;
	PT1 = 1;
	EA = 1;
	P2 = 0xff;
	P3_0 = 1;
	Delay1ms(500);
	LCD_init();
	Delay1ms(500);
	clear1602();
	Timer1(STOP);
	Timer0(STOP);
	RING = 0;
	Timer1(START);
	
	while(1)
	{
//		a:
		display_menu();
		if(TimeButton == 0)
		{
			clear1602();
			while(MenuButton)
			{
				display_time(hour, minute, second, month, day);			
			}
			clear1602();
		}
		else if(SetButton == 0)
		{
			clear1602();
			display_setting();
			while(1)
			{
				if(SS_1date == 0)
				{
					clear1602();
					display_setting_date(0, 0);
					while(MenuButton)
					{
						display_setting_date(month, day);
						if(!Month_Minute)
						{
							Delay1ms(20);
							++month;
							if(month >= 13) month = 1;
						}
						else if(!Day_Second)
						{
							Delay1ms(20);
							++day;
							if(day >= 31) day = 1;
						}
					}
					break;
				}
				else if(TR_2time == 0)
				{
					clear1602();
					display_setting_time(0, 0, 0);
					while(MenuButton)
					{
						display_setting_time(hour, minute, second);
						if(!Clear_Hour)
						{
							Delay1ms(20);
							++hour;
							if(hour >= 24) hour = 0;
						}
						else if(!Month_Minute)
						{
							Delay1ms(20);
							++minute;
							if(minute >= 60) minute = 0;
						}
						else if(!Day_Second)
						{
							Delay1ms(20);
							++second;
							if(second >= 60) second = 0;
						}
					}
					break;
				}
			}
			clear1602();
		}
		else if(TimerButton == 0)
		{
			clear1602();
			while(MenuButton)
			{
				if(!SS_1date && !flag)
				{flag=1;}
				else if(flag && !SS_1date)
				{flag = 0;number = 0;}
				if(!TR_2time)
				{temp_minute = 0;temp_second = 0;micro = 0;flag = 0;number = 0;}
				display_timer(temp_minute, temp_second, micro);
			}
			flag = 0;micro = 0;temp_minute = 0;temp_second = 0;
			clear1602();
		}
	}
	
}


Time1() interrupt 3
{
	++num;
	if(num >= 4000)
	{
		++second;
		num = 0;
	}
	if(second >= 60) {++minute;second = 0;}
	if(minute >= 60) {++hour;minute = 0;}
	if(hour >= 24) {++day;hour = 0;}
	if(day >= 30) {++month;day = 0;} 
	if(month >= 12) month = 0;
	
	if(!minute && !second)
	{
		ring = 1;
		Timer0(START);
	}
	if(ring == 0)
	{Timer0(STOP);}
	if(flag)
	{
		++number;
		if(number >= 400)
		{
			++micro;
			number = 0;
		}
		if(micro >= 10) {++temp_second;micro = 0;}
		if(temp_second >= 60) {++temp_minute;temp_second = 0;}
		if(temp_minute >= 60) {temp_minute = 0;}
	}
}

static int a=0, b=600;
Time0() interrupt 1
{
	++ring_num;
	if(a != 10 && ring_num >= 50)
	{
		ring_num = 0;
		RING = ~RING;
		++a;
	}
	else if(a >= 10)
	{
		RING = ~RING;
		--b;
		if(b <= 0)
		{
			a=0;
			b=200;
		}
	}
	if(!Clear_Hour)
	{
		ring = 0;
	}
}



