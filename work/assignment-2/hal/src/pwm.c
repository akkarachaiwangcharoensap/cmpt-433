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

// Always on: we set duty_cycle == period.
#define PWM_ON_PERIOD 1000000   // 1,000,000 ns period
#define PWM_ON_DUTY   1000000   // 100% duty cycle

// Flashing at 4 Hz (50% duty cycle)
// A 250,000,000 ns period yields 4 cycles per second, with half the period “on.”
#define PWM_FLASH_PERIOD 250000000  // 250,000,000 ns (250 ms)
#define PWM_FLASH_DUTY   125000000   // 125,000,000 ns (125 ms on time)

// At flashSpeed == 0, we use the slowest flash (long period).
// At flashSpeed == 1, we use the fastest flash (short period).
#define PWM_FLASH_MAX_PERIOD 469754879  // Slow flash: ~2.13 Hz
#define PWM_FLASH_MIN_PERIOD 250000000  // Fast flash: 4 Hz

static bool is_initialized;

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

void Pwm_init(void) 
{
    printf("PWM - Initializing\n");
    assert(!is_initialized);
    srand(time(0));
    
    is_initialized = true;
}

void Pwm_turn_on(void) 
{
    assert(is_initialized);

    // Reset duty cycle first, then set period and duty cycle to achieve a full “on” state.
    write_pwm_value(PWM_DUTY_CYCLE_FILE, 0);
    write_pwm_value(PWM_PERIOD_FILE, PWM_ON_PERIOD);
    write_pwm_value(PWM_DUTY_CYCLE_FILE, PWM_ON_DUTY);
    write_pwm_value(PWM_ENABLE_FILE, 1);
}

void Pwm_turn_off(void) 
{
    assert(is_initialized);

    // Disable PWM output to turn it off.
    write_pwm_value(PWM_ENABLE_FILE, 0);
    // Optionally, reset duty cycle to 0.
    write_pwm_value(PWM_DUTY_CYCLE_FILE, 0);
}

bool Pwm_is_on(void) 
{
    assert(is_initialized);

    FILE *fp = fopen(PWM_ENABLE_FILE, "r");
    if (fp == NULL) {
        perror("Pwm_is_on: Error opening PWM enable file for reading.");
        return false;
    }

    int enabled = 0;
    if (fscanf(fp, "%d", &enabled) != 1) {
        perror("Pwm_is_on: Error reading PWM enable file.");
        fclose(fp);
        return false;
    }
   
    fclose(fp);
    return (enabled == 1);
}

bool Pwm_is_off(void) 
{
    return !Pwm_is_on();
}

void Pwm_flash(void) 
{
    assert(is_initialized);

    // Flash at given config.
    write_pwm_value(PWM_DUTY_CYCLE_FILE, 0);
    write_pwm_value(PWM_PERIOD_FILE, PWM_FLASH_PERIOD);
    write_pwm_value(PWM_DUTY_CYCLE_FILE, PWM_FLASH_DUTY);
    write_pwm_value(PWM_ENABLE_FILE, 1);
}

// The 'flashSpeed' parameter is a normalized value between 0.0 and 1.0,
// where 0.0 is the slowest flash (long period) and 1.0 is to the fastest (short period).
void Pwm_set_flash_speed(float flashSpeed) 
{
    assert(is_initialized);

    // Clamp flashSpeed to [0.0, 1.0]
    if (flashSpeed < 0.0f)
        flashSpeed = 0.0f;
    if (flashSpeed > 1.0f)
        flashSpeed = 1.0f;

    // Reference: https://en.wikipedia.org/wiki/Interpolation#:~:text=One%20of%20the%20simplest%20methods,=%200.1411%2C%20which%20yields%200.5252.&text=Linear%20interpolation%20is%20quick%20and,at%20the%20point%20xk.&text=In%20words%2C%20the%20error%20is,methods%20also%20produce%20smoother%20interpolants.
    // Calculate the period by linearly interpolating between the maximum and minimum allowed period. 
    int period = PWM_FLASH_MAX_PERIOD - (int)((PWM_FLASH_MAX_PERIOD - PWM_FLASH_MIN_PERIOD) * flashSpeed);
    int duty = period / 2; // 50% duty cycle for equal on/off times

    // Configure the PWM:
    // Reset the duty cycle to 0.
    // Set the period.
    write_pwm_value(PWM_DUTY_CYCLE_FILE, 0);
    write_pwm_value(PWM_PERIOD_FILE, period);

    // Set the new duty cycle.
    // Enable the PWM output.
    write_pwm_value(PWM_DUTY_CYCLE_FILE, duty);
    write_pwm_value(PWM_ENABLE_FILE, 1);
}

void Pwm_cleanup(void) 
{
    printf("PWM - Cleanup\n");
    assert(is_initialized);
    Pwm_turn_off();

    is_initialized = false;
    printf("PWM - Done.\n");
}