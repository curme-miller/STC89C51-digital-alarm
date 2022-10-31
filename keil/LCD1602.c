#include "LCD1602.h"
#include <REGX51.H>

/**
LCD1602
**/
sbit E = P1^0;
sbit RS = P1^2;
sbit RW = P1^1;
sbit IS_BUSY = P0^7;

void delay1602(int x, int y)
{
    int i, j;
    for (i = 0; i < x; i++)
	    for (j = 0; j < y; j++);
}
void adjust_busy()
{
  unsigned char temp = 1;
	unsigned int i = 100;
	while (temp && i)
	{
	  P0 = 0xff;
		E = 0;
		delay1602(7, 7);
		RS = 0;
		RW = 1; 
		delay1602(5, 5);
		E = 1;
		delay1602(5, 5);
		temp = IS_BUSY;
		delay1602(15, 15);
		E = 0;  
		i--; 
	}
}
void write_command(int com)
{
  adjust_busy();
	E = 0;
	RS = 0;
	RW = 0;
	P0 = com;
	delay1602(5, 5);
	E = 1;
	delay1602(25, 25);   
	E = 0; 
}
void write_data(int dat)
{
  adjust_busy();
	E = 0;
	RS = 1;
	RW = 0;
	P0 = dat;
	delay1602(5, 5);
	E = 1;
	delay1602(25, 25);   
	E = 0; 
}

void clear1602()
{
  write_command(0x01);
	write_command(0x06);
	write_command(0x0c);
}
void LCD_init()
{
  write_command(0x38);
	delay1602(20, 20);
	write_command(0x0c);
	delay1602(20, 20);
	write_command(0x06);    
}