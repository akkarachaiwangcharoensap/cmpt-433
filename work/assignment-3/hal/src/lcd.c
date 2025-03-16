// Reference: lecture slide.
#include "DEV_Config.h"
#include "LCD_1in54.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "hal/lcd.h"

#include <stdio.h>      // printf()
#include <stdlib.h>     // exit(), malloc(), free()
#include <signal.h>     // signal()
#include <stdbool.h>
#include <assert.h>

UWORD *s_fb;
static bool is_initialized = false;

void Lcd_init()
{
    printf("Lcd - Initializing\n");
    assert(!is_initialized);

    // Module Init
    if (DEV_ModuleInit() != 0) {
        DEV_ModuleExit();
        exit(0);
    }
    
    // LCD Init
    DEV_Delay_ms(2000);
    LCD_1IN54_Init(HORIZONTAL);
    LCD_1IN54_Clear(WHITE);
    LCD_SetBacklight(1023);

    UDOUBLE Imagesize = LCD_1IN54_HEIGHT * LCD_1IN54_WIDTH * 2;
    s_fb = (UWORD *)malloc(Imagesize);
    if (s_fb == NULL) {
        perror("Failed to apply for black memory");
        exit(EXIT_FAILURE);
    }
    is_initialized = true;
}

void Lcd_cleanup()
{
    printf("Lcd - Cleanup\n");
    assert(is_initialized);
    is_initialized = false;

    LCD_SetBacklight(0);
    Paint_Clear(BLACK);

    // Module Exit
    free(s_fb);
    s_fb = NULL;
    
    DEV_ModuleExit();
    printf("Lcd - Done.\n");
}

/*
 * Lcd_updateScreenPage
 *  - Clears the display and renders all text lines for a given page.
 *  - Also displays a page indicator at the bottom.
 *
 * Parameters:
 *   page        : The Page structure containing an array of text strings.
 *   currentPage : The (0-based) index of the current page.
 *   totalPages  : Total number of pages.
 */
void Lcd_updateScreenPage(Page page, int currentPage, int totalPages)
{
    const int x = 5;
    const int startY = 70;
    const int lineHeight = 20;

    // Create a new image and clear it (white background)
    Paint_NewImage(s_fb, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    // Draw each text line for the page
    for (int i = 0; i < page.numTexts; i++) {
        int y = startY + i * lineHeight;
        Paint_DrawString_EN(x, y, page.texts[i], &Font20, WHITE, BLACK);
    }

    // Draw a page indicator at the bottom of the screen.
    char pageIndicator[30];
    snprintf(pageIndicator, sizeof(pageIndicator), "Page %d/%d", currentPage + 1, totalPages);
    int indicatorY = LCD_1IN54_HEIGHT - 20;
    Paint_DrawString_EN(x, indicatorY, pageIndicator, &Font16, WHITE, BLACK);

    // Update the display.
    LCD_1IN54_DisplayWindows(0, 0, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, s_fb);
}
