/*
 * Manage the LCD screen (pages) by providing functions to 
 * update and cycle between different screens.
 */

#ifndef LCD_SCREENS_H
#define LCD_SCREENS_H

void status_screen(void);
void update_audio_screen(void);
void update_accel_screen(void);
void update_current_screen(void);
void cycle_screen(void);

#endif