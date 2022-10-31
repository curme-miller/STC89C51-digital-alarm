#include "Display.h"
#include "LCD1602.h"


char menu[16]="Time  Set  Timer";
char setting[12]="date or time";
static unsigned char code number[10] = {"0123456789"};

void display_menu()
{
	int i;
	write_command(LINE1);
	for(i=0; i<16; i++)
		write_data(menu[i]);
}

void display_time(short hour, short minute, short second, short month, short day)
{
	
	write_command(LINE1);
	write_data(number[month/10]);write_data(number[month%10]);write_data('M');
	write_data('\x20');
	write_data(number[day/10]);write_data(number[day%10]);write_data('D');
	
	write_command(LINE2);
	write_data(number[hour/10]);write_data(number[hour%10]);write_data('H');
	write_data('\x20');
	write_data(number[minute/10]);write_data(number[minute%10]);write_data('M');
	write_data('\x20');
	write_data(number[second/10]);write_data(number[second%10]);write_data('S');
	
}

void display_setting()
{
	int i;
	write_command(LINE1);
	for(i=0;i<12;i++)
		write_data(setting[i]);
}

void display_setting_date(short month, short day)
{
	write_command(LINE1);
	write_data(number[month/10]);write_data(number[month%10]);write_data('M');
	write_data('\x20');
	write_data(number[day/10]);write_data(number[day%10]);write_data('D');
	
}

void display_setting_time(short hour, short minute, short second)
{
	write_command(LINE1);
	write_data(number[hour/10]);write_data(number[hour%10]);write_data('H');
	write_data('\x20');
	write_data(number[minute/10]);write_data(number[minute%10]);write_data('M');
	write_data('\x20');
	write_data(number[second/10]);write_data(number[second%10]);write_data('S');
	
}

void display_timer(short minute, short second, short micro)
{
	write_command(LINE1);
	write_data(number[minute/10]);write_data(number[minute%10]);
	write_data(':');
	write_data(number[second/10]);write_data(number[second%10]);
	write_data(':');
	write_data(number[micro/10]);write_data(number[micro%10]);
}

void display_alarm()
{
	write_command(LINE1);
	write_data('!');
	write_command(LINE2);
	write_data('!');
}
