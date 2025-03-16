#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "hal/gpio.h"
#include "hal/joystick.h"
#include "hal/rotary_statemachine.h"
#include "hal/accelerometer.h"
#include "hal/lcd.h"
#include "hal/periodTimer.h"
#include "audio_mixer.h"
#include "drum_beat.h"
#include "lcd_screens.h"
#include "udp.h"

// Shared global statistics.
Period_statistics_t g_audioStats;
Period_statistics_t g_accelStats;

// Global flag to allow CTRL+C termination.
volatile bool stop_main_thread = false;

// Sound data declarations.
wavedata_t sound1, sound2, sound3;

// Signal handler for CTRL+C
void sigint_handler(int signum)
{
    (void)signum;
    stop_main_thread = true;
}

void on_accelerometer_x_shaken(void) 
{
    AudioMixer_queueSound(&sound1);
}

void on_accelerometer_y_shaken(void) 
{
    AudioMixer_queueSound(&sound2);
}

void on_accelerometer_z_shaken(void) 
{
    AudioMixer_queueSound(&sound3);
}

void on_rotary_clockwise(void) 
{
    int bpm = DrumBeat_get_bpm();
    int newBPM = bpm + 5;
    DrumBeat_set_bpm(newBPM);
}

void on_rotary_counter_clockwise(void)
{
    int bpm = DrumBeat_get_bpm();
    int newBPM = bpm - 5;
    DrumBeat_set_bpm(newBPM);
}

void on_rotary_push_button_down(void)
{
    DrumBeat_next_mode();
}

void on_joystick_pressed_up(void) 
{
    int volume = AudioMixer_getVolume();
    int newVolume = volume + 5;
    AudioMixer_setVolume(newVolume);
}

void on_joystick_pressed_down(void) 
{
    int volume = AudioMixer_getVolume();
    int newVolume = volume - 5;
    AudioMixer_setVolume(newVolume);
}

void on_joystick_push_button_down(void)
{
    cycle_screen();
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) != 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Initialize hardware and subsystems.
    UDP_init();
    Gpio_init();
    Period_init();
    Lcd_init();
    Accelerometer_init();
    AudioMixer_init();
    DrumBeat_init();
    RotaryStateMachine_init();
    Joystick_init();

    // Register callbacks.
    Joystick_register_pressed_down_callback(on_joystick_pressed_down);
    Joystick_register_pressed_up_callback(on_joystick_pressed_up);
    Joystick_register_push_button_down_callback(on_joystick_push_button_down);

    RotaryStateMachine_register_clockwise_callback(on_rotary_clockwise);
    RotaryStateMachine_register_counter_clockwise_callback(on_rotary_counter_clockwise);
    RotaryStateMachine_register_push_button_down_callback(on_rotary_push_button_down);

    Accelerometer_register_shake_x_callback(on_accelerometer_x_shaken);
    Accelerometer_register_shake_y_callback(on_accelerometer_y_shaken);
    Accelerometer_register_shake_z_callback(on_accelerometer_z_shaken);

    // Load sound files.
    AudioMixer_readWaveFileIntoMemory("wave-files/100051__menegass__gui-drum-bd-hard.wav", &sound1);
    AudioMixer_readWaveFileIntoMemory("wave-files/100053__menegass__gui-drum-cc.wav", &sound2);
    AudioMixer_readWaveFileIntoMemory("wave-files/100059__menegass__gui-drum-snare-soft.wav", &sound3);
    
    // Display the initial screen.
    update_current_screen();
        
    // Once per second, update stats, print status, and update LCD screens.
    while (!stop_main_thread) {
        int mode = DrumBeat_get_mode();
        int bpm = DrumBeat_get_bpm();
        int volume = AudioMixer_getVolume();

        // Mark events to update the stats.
        Period_markEvent(PERIOD_EVENT_AUDIO_MIXER);
        Period_markEvent(PERIOD_EVENT_ACCELEROMETER);

        // Retrieve and clear the latest timing statistics.
        Period_getStatisticsAndClear(PERIOD_EVENT_AUDIO_MIXER, &g_audioStats);
        Period_getStatisticsAndClear(PERIOD_EVENT_ACCELEROMETER, &g_accelStats);

        printf("M%d %dbpm vol:%d ", mode, bpm, volume);
        printf("Audio[%.3f, %.3f] avg %.3f/%d ", 
               g_audioStats.minPeriodInMs, g_audioStats.maxPeriodInMs, 
               g_audioStats.avgPeriodInMs, g_audioStats.numSamples);
        printf("Accel[%.3f, %.3f] avg %.3f/%d\n", 
               g_accelStats.minPeriodInMs, g_accelStats.maxPeriodInMs, 
               g_accelStats.avgPeriodInMs, g_accelStats.numSamples);

        // Update the LCD screen
        update_current_screen();

        sleep(1);  // Wait one second between updates.
    }
    
    // Cleanup.
    RotaryStateMachine_cleanup();
    DrumBeat_cleanup();
    Joystick_cleanup();

    AudioMixer_freeWaveFileData(&sound1);
    AudioMixer_freeWaveFileData(&sound2);
    AudioMixer_freeWaveFileData(&sound3);
    AudioMixer_cleanup();
    
    Accelerometer_cleanup();
    Lcd_cleanup();
    Period_cleanup();
    Gpio_cleanup();
    UDP_cleanup();

    return 0;
}