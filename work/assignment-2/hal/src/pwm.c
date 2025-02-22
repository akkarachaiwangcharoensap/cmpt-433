#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

// PWM file locations for GPIO12
#define PWM_BASE_PATH                       "/dev/hat/pwm/GPIO12/"
#define PWM_DUTY_CYCLE_FILE PWM_BASE_PATH   "duty_cycle"
#define PWM_PERIOD_FILE     PWM_BASE_PATH   "period"
#define PWM_ENABLE_FILE     PWM_BASE_PATH   "enable"

#define PWM_ON_PERIOD 1000000   // 1,000,000 ns period (1 ms)
#define PWM_ON_DUTY   1000000   // 100% duty cycle

static bool is_initialized = false;

// (A value of -1 means “not yet set”.)
static int currentFrequency = -1;

// A helper function that writes an integer value to a given PWM sysfs file.
// PWM files: https://opencoursehub.cs.sfu.ca/bfraser/grav-cms/cmpt433/guides/files_byai/PWMGuide.pdf
static void write_pwm_value(const char *path, int value) 
{
    FILE *fp = fopen(path, "w");
    if (!fp) {
        perror("write_pwm_value: Error opening PWM file");
        exit(EXIT_FAILURE);
    }

    if (fprintf(fp, "%d", value) < 0) {
        perror("write_pwm_value: Error writing to PWM file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

static void Pwm_turn_off(void) 
{
    assert(is_initialized);

    // Disable PWM output to turn it off.
    write_pwm_value(PWM_ENABLE_FILE, 0);
    write_pwm_value(PWM_DUTY_CYCLE_FILE, 0);

    currentFrequency = 0;
}

// Set the PWM flashing frequency (in Hz). A 50% duty cycle is used.
// If frequency == 0, the PWM is disabled (LED off).
// If the PWM is already running at the requested frequency, do nothing.
void Pwm_set_frequency(int frequency) 
{
    assert(is_initialized);

    // Clamp frequency to [0, 500] Hz.
    if (frequency < 0)
        frequency = 0;
    if (frequency > 500)
        frequency = 500;

    // Do nothing if already set to the desired frequency.
    if (frequency == currentFrequency)
        return;

    currentFrequency = frequency;

    if (frequency == 0) {
        Pwm_turn_off();
        return;
    }

    // Compute the period in nanoseconds:
    // period = (1 second / frequency) in ns = 1,000,000,000 / frequency.
    int period = 1000000000 / frequency;
    int duty = period / 2; // 50% duty cycle

    // Configure the PWM:
    // Reset duty cycle, then set period and duty, and finally enable PWM.
    write_pwm_value(PWM_DUTY_CYCLE_FILE, 0);
    write_pwm_value(PWM_PERIOD_FILE, period);
    write_pwm_value(PWM_DUTY_CYCLE_FILE, duty);
    write_pwm_value(PWM_ENABLE_FILE, 1);
}

int Pwm_get_frequency(void) 
{
    return currentFrequency;
}

// Increase the PWM frequency by 1Hz (up to a maximum of 500Hz).
void Pwm_increase_frequency(void)
{
    // If currentFrequency is not yet set, assume 10Hz.
    int freq = (currentFrequency < 0) ? 10 : currentFrequency;
    if (freq < 500) {
        Pwm_set_frequency(freq + 1);
    }
}

// Decrease the PWM frequency by 1Hz (but not below 0Hz).
void Pwm_decrease_frequency(void)
{
    // If currentFrequency is not yet set, assume 10Hz.
    int freq = (currentFrequency < 0) ? 10 : currentFrequency;
    if (freq > 0) {
        Pwm_set_frequency(freq - 1);
    }
}

void Pwm_init(void) 
{
    printf("PWM - Initializing\n");
    assert(!is_initialized);
    srand(time(0));
    
    is_initialized = true;
    
    // Start flashing at 10Hz
    // (This sets currentFrequency to 10.)
    Pwm_set_frequency(10);
}

void Pwm_cleanup(void) 
{
    printf("PWM - Cleanup\n");
    assert(is_initialized);
    Pwm_turn_off();

    is_initialized = false;
    printf("PWM - Done.\n");
}