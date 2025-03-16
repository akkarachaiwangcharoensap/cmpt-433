#include "drum_beat.h"
#include "audio_mixer.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

wavedata_t bass_drum;
wavedata_t snare_drum;
wavedata_t hi_hat_drum;
wavedata_t splash_drum;

static DrumMode current_mode = DRUM_MODE_NONE;

static pthread_t drum_beat_thread;
static pthread_mutex_t drum_mutex = PTHREAD_MUTEX_INITIALIZER;

static int current_bpm = 120;
static bool stop_thread = false;
static bool is_initialized = false;

#define MAX_MODE_COUNT 3

void* drum_beat_func(void* arg) 
{
    (void)arg;
    int step = 0;
    while (!stop_thread) {
        pthread_mutex_lock(&drum_mutex);
        DrumMode mode = current_mode;
        int bpm = current_bpm;
        pthread_mutex_unlock(&drum_mutex);
        if (mode == DRUM_MODE_NONE) {
            usleep(100000);
            continue;
        } 
        else if (mode == DRUM_MODE_ROCK) {
            // Reference: assignment description.
            /* Standard Rock Drum Beat:
             * Each loop iteration represents a half-beat (eighth note).
             * Measure layout (8 half-beats per 4/4 measure):
             *  Step 0 (Beat 1):    Hi‑hat + Base drum
             *  Step 1 (Beat 1.5):  Hi‑hat
             *  Step 2 (Beat 2):    Hi‑hat + Snare drum
             *  Step 3 (Beat 2.5):  Hi‑hat
             *  Step 4 (Beat 3):    Hi‑hat + Base drum
             *  Step 5 (Beat 3.5):  Hi‑hat
             *  Step 6 (Beat 4):    Hi‑hat + Snare drum
             *  Step 7 (Beat 4.5):  Hi‑hat
             */
            double halfBeatDurationSec = 60.0 / bpm / 2.0;
            unsigned int sleepMicro = (unsigned int)(halfBeatDurationSec * 1000000);
            switch (step) {
                case 0:
                    AudioMixer_queueSound(&bass_drum);
                    AudioMixer_queueSound(&hi_hat_drum);
                    break;
                case 1:
                    AudioMixer_queueSound(&hi_hat_drum);
                    break;
                case 2:
                    AudioMixer_queueSound(&hi_hat_drum);
                    AudioMixer_queueSound(&snare_drum);
                    break;
                case 3:
                    AudioMixer_queueSound(&hi_hat_drum);
                    break;
                case 4:
                    AudioMixer_queueSound(&bass_drum);
                    AudioMixer_queueSound(&hi_hat_drum);
                    break;
                case 5:
                    AudioMixer_queueSound(&hi_hat_drum);
                    break;
                case 6:
                    AudioMixer_queueSound(&hi_hat_drum);
                    AudioMixer_queueSound(&snare_drum);
                    break;
                case 7:
                    AudioMixer_queueSound(&hi_hat_drum);
                    break;
                default:
                    break;
            }
            step = (step + 1) % 8;
            usleep(sleepMicro);
        } 
        else if (mode == DRUM_MODE_CUSTOM) {
            // 16 steps per measure using sixteenth note timing.
            double sixteenthDurationSec = 60.0 / bpm / 4.0;
            unsigned int sleepMicro = (unsigned int)(sixteenthDurationSec * 1000000);
            if (step % 16 == 0) {
                AudioMixer_queueSound(&bass_drum);
            }
            if (step % 16 == 4) {
                AudioMixer_queueSound(&snare_drum);
            }
            if (step % 16 == 8) {
                AudioMixer_queueSound(&bass_drum);
            }
            if (step % 16 == 12) {
                AudioMixer_queueSound(&splash_drum);
            }
            if (step % 2 == 1) {
                AudioMixer_queueSound(&hi_hat_drum);
            }
            step = (step + 1) % 16;
            usleep(sleepMicro);
        }
    }

    return NULL;
}

void DrumBeat_init(void) 
{
    AudioMixer_readWaveFileIntoMemory("wave-files/100051__menegass__gui-drum-bd-hard.wav", &bass_drum);
    AudioMixer_readWaveFileIntoMemory("wave-files/100058__menegass__gui-drum-snare-hard.wav", &snare_drum);
    AudioMixer_readWaveFileIntoMemory("wave-files/100056__menegass__gui-drum-cyn-hard.wav", &hi_hat_drum);
    AudioMixer_readWaveFileIntoMemory("wave-files/100060__menegass__gui-drum-splash-hard.wav", &splash_drum);

    pthread_mutex_lock(&drum_mutex);
    current_mode = DRUM_MODE_ROCK;
    current_bpm = 120;
    pthread_mutex_unlock(&drum_mutex);

    // Create the drum beat thread.
    if (pthread_create(&drum_beat_thread, NULL, drum_beat_func, NULL) != 0) {
        perror("DrumBeat_init: Failed to create drum beat thread.\n");
        exit(EXIT_FAILURE);
    }

    stop_thread = false;
    is_initialized = true;
}

void DrumBeat_set_mode(DrumMode mode) 
{
    pthread_mutex_lock(&drum_mutex);
    current_mode = mode;
    pthread_mutex_unlock(&drum_mutex);
}

DrumMode DrumBeat_get_mode(void)
{
    DrumMode mode;
    pthread_mutex_lock(&drum_mutex);
    mode = current_mode;
    pthread_mutex_unlock(&drum_mutex);

    return mode;
}

void DrumBeat_next_mode(void) 
{
    DrumMode nextMode = (DrumMode)(current_mode + 1) % MAX_MODE_COUNT;
    DrumBeat_set_mode(nextMode);
}

void DrumBeat_set_bpm(int bpm) 
{
    if (bpm < 40 || bpm > 300) {
        fprintf(stderr, "ERROR: BPM must be between 40 and 300.\n");
        return;
    }

    pthread_mutex_lock(&drum_mutex);
    current_bpm = bpm;
    pthread_mutex_unlock(&drum_mutex);
}

int DrumBeat_get_bpm(void)
{
    int value;
    pthread_mutex_lock(&drum_mutex);
    value = current_bpm;
    pthread_mutex_unlock(&drum_mutex);

    return value;
}

void DrumBeat_cleanup(void) 
{
    printf("DrumBeat - Done.\n");
    assert(is_initialized);
    stop_thread = true;
    
    pthread_join(drum_beat_thread, NULL);
    pthread_mutex_destroy(&drum_mutex);

    AudioMixer_freeWaveFileData(&bass_drum);
    AudioMixer_freeWaveFileData(&snare_drum);
    AudioMixer_freeWaveFileData(&hi_hat_drum);
    AudioMixer_freeWaveFileData(&splash_drum);

    is_initialized = false;

    printf("DrumBeat - Done.\n");
}