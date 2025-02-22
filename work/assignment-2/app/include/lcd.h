#ifndef _LCD_H_
#define _LCD_H_

void Lcd_init();
void Lcd_cleanup();

void Lcd_updateScreenMultiple(char* messages[], int numMessages);

#endif