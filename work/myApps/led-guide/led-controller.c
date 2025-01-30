#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LED_TRIGGER_FILE "/sys/class/leds/ACT/trigger"
#define LED_BRIGHTNESS_FILE "/sys/class/leds/ACT/brightness"

void set_led_trigger(const char *trigger) 
{
    FILE *pLedTriggerFile = fopen(LED_TRIGGER_FILE, "w");
    if (pLedTriggerFile == NULL) {
        perror("Error opening LED trigger file.");
        exit(EXIT_FAILURE);
    }

    int charWritten = fprintf(pLedTriggerFile, "%s", trigger);
    if (charWritten <= 0) {
        perror("Error writing to LED trigger file.");
        fclose(pLedTriggerFile);
        exit(EXIT_FAILURE);
    }

    fclose(pLedTriggerFile);
}

void set_led_brightness(int state) 
{
    FILE *pLedBrightnessFile = fopen(LED_BRIGHTNESS_FILE, "w");
    if (pLedBrightnessFile == NULL) {
        perror("Error opening LED brightness file.");
        exit(EXIT_FAILURE);
    }

    int charWritten = fprintf(pLedBrightnessFile, "%d", state);
    if (charWritten <= 0) {
        perror("Error writing to LED brightness file");
        fclose(pLedBrightnessFile);
        exit(EXIT_FAILURE);
    }

    fclose(pLedBrightnessFile);
}

void delay_ms(long milliseconds) 
{
    long seconds = milliseconds / 1000;
    long nanoseconds = (milliseconds % 1000) * 1000000;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, NULL);
}

int main()
{
    printf("Starting LED control program\n");

    printf("Set LED trigger to 'none'\n");
    set_led_trigger("none");

    delay_ms(100);

    for (int i = 0; i < 5; i++) {
        printf("Turn LED ON\n");
        set_led_brightness(1);
        delay_ms(500); 

        printf("Turn LED OFF\n");
        set_led_brightness(0);
        delay_ms(500);
    }

    printf("Exit program.");
    return 0;
}