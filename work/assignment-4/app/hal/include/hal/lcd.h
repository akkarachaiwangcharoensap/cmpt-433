/*
 * Provide initialization, update, and cleanup functions for managing an LCD display (multiple pages).
 */
#ifndef _LCD_H_
#define _LCD_H_

typedef struct {
    // 2D array of texts string in a page
    char **texts;
    // Num of texts (size)
    int numTexts; 
} Page;

void Lcd_init();
void Lcd_cleanup();

void Lcd_updateScreenMultiple(char* messages[], int numMessages);
void Lcd_updateScreenPage(Page page, int currentPage, int totalPages);
#endif