#ifndef DISPLAY_H_ 
#define DISPLAY_H_

extern void display_menu();
extern void display_time(short hour, short minute, short second, short month, short day);
extern void display_setting();
extern void display_setting_date(short month, short day);
extern void display_setting_time(short hour, short minute, short second);
extern void display_timer(short hour, short minute, short second);
extern void display_alarm();

#endif