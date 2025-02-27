// Reference: lecture slide
#include "DEV_Config.h"
#include "LCD_1in54.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include "lcd.h"

#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()
#include <stdbool.h>
#include <assert.h>

static UWORD *s_fb;
static bool is_initialized = false;

void Lcd_init()
{
    printf("Lcd - Initializing\n");
    assert(!is_initialized);

    // Exception handling:ctrl + c
    // signal(SIGINT, Handler_1IN54_LCD);
    
    // Module Init
	if(DEV_ModuleInit() != 0){
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

void Lcd_updateScreenMultiple(char* messages[], int numMessages)
{
    const int x = 5;
    const int startY = 70;
    const int lineHeight = 20;

    // Initialize the RAM frame buffer to be blank (white)
    Paint_NewImage(s_fb, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    // Loop through each message and print it on a separate line.
    for (int i = 0; i < numMessages; i++) {
        int y = startY + i * lineHeight;
        // Ensure that each message does NOT contain '\n'
        Paint_DrawString_EN(x, y, messages[i], &Font20, WHITE, BLACK);
    }

    // Calculate the window height based on the number of messages.
    int windowBottom = startY + numMessages * lineHeight;
    LCD_1IN54_DisplayWindows(x, startY, LCD_1IN54_WIDTH, windowBottom, s_fb);
}