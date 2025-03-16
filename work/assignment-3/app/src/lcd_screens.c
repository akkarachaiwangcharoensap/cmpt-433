#include <LCD_1in54.h>
#include <stdio.h>

#include "lcd_screens.h"
#include "hal/lcd.h"
#include "drum_beat.h"
#include "audio_mixer.h"
#include "GUI_Paint.h"
#include "hal/periodTimer.h"

// Global shared statistics
extern Period_statistics_t g_audioStats;
extern Period_statistics_t g_accelStats;

// External frame buffer allocated in the LCD module.
extern UWORD *s_fb;

// Static variables to keep track of the current screen.
static int current_page = 0;
static const int total_pages = 3;

// Show the current beat (using the drum beat mode as a proxy),
// Volume at the bottom left, and BPM at the bottom right.
void status_screen(void)
{
    int currentMode = DrumBeat_get_mode();
    char beatName[32];
    snprintf(beatName, sizeof(beatName), "Beat %d", currentMode);
    int volume = AudioMixer_getVolume();
    int bpm = DrumBeat_get_bpm();

    Paint_NewImage(s_fb, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    // Center the beat name.
    int textWidth = 100;
    int centerX = (LCD_1IN54_WIDTH - textWidth) / 2;
    int centerY = (LCD_1IN54_HEIGHT - 20) / 2;
    Paint_DrawString_EN(centerX, centerY, beatName, &Font20, WHITE, BLACK);

    // Bottom left: Volume.
    char volStr[32];
    snprintf(volStr, sizeof(volStr), "Volume: %d", volume);
    Paint_DrawString_EN(5, LCD_1IN54_HEIGHT - 20, volStr, &Font16, WHITE, BLACK);

    // Bottom right: BPM.
    char bpmStr[32];
    snprintf(bpmStr, sizeof(bpmStr), "BPM: %d", bpm);
    int bpmX = LCD_1IN54_WIDTH - 100;
    Paint_DrawString_EN(bpmX, LCD_1IN54_HEIGHT - 20, bpmStr, &Font16, WHITE, BLACK);

    LCD_1IN54_DisplayWindows(0, 0, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, s_fb);
}

// Show the min/max/avg timing (in ms) for audio buffer events.
void update_audio_screen(void)
{
    // Use shared global g_audioStats.
    Paint_NewImage(s_fb, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    Paint_DrawString_EN(5, 10, "Audio Timing", &Font20, WHITE, BLACK);

    char minStr[32], maxStr[32], avgStr[32];
    snprintf(minStr, sizeof(minStr), "Min: %f ms", g_audioStats.minPeriodInMs);
    snprintf(maxStr, sizeof(maxStr), "Max: %f ms", g_audioStats.maxPeriodInMs);
    snprintf(avgStr, sizeof(avgStr), "Avg: %f ms", g_audioStats.avgPeriodInMs);

    Paint_DrawString_EN(5, 40, minStr, &Font16, WHITE, BLACK);
    Paint_DrawString_EN(5, 60, maxStr, &Font16, WHITE, BLACK);
    Paint_DrawString_EN(5, 80, avgStr, &Font16, WHITE, BLACK);

    LCD_1IN54_DisplayWindows(0, 0, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, s_fb);
}

// Show the min/max/avg timing (in ms) for accelerometer events.
void update_accel_screen(void)
{
    // Use shared global g_accelStats.
    Paint_NewImage(s_fb, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    Paint_DrawString_EN(5, 10, "Accel. Timing", &Font20, WHITE, BLACK);

    char minStr[32], maxStr[32], avgStr[32];
    snprintf(minStr, sizeof(minStr), "Min: %f ms", g_accelStats.minPeriodInMs);
    snprintf(maxStr, sizeof(maxStr), "Max: %f ms", g_accelStats.maxPeriodInMs);
    snprintf(avgStr, sizeof(avgStr), "Avg: %f ms", g_accelStats.avgPeriodInMs);

    Paint_DrawString_EN(5, 40, minStr, &Font16, WHITE, BLACK);
    Paint_DrawString_EN(5, 60, maxStr, &Font16, WHITE, BLACK);
    Paint_DrawString_EN(5, 80, avgStr, &Font16, WHITE, BLACK);

    LCD_1IN54_DisplayWindows(0, 0, LCD_1IN54_WIDTH, LCD_1IN54_HEIGHT, s_fb);
}

// Update the screen based on the current_page value.
void update_current_screen(void)
{
    switch (current_page) {
        case 0:
            status_screen();
            break;
        case 1:
            update_audio_screen();
            break;
        case 2:
            update_accel_screen();
            break;
        default:
            break;
    }
}

// Cycle to the next screen and update the LCD screen.
void cycle_screen(void)
{
    current_page = (current_page + 1) % total_pages;
    update_current_screen();
}