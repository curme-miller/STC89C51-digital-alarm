#ifndef LCD1602_H_
#define LCD1602_H_

#define LINE1  0x80
#define LINE2  0xc0

extern void LCD_init();
extern void write_command(int com);
extern void write_data(int dat);
extern void clear1602();


#endif