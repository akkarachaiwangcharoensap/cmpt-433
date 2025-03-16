/* 
 * Generate drum beats using an audio mixer (none, rock, and custom).
 * Allow control over the beat pattern and tempo (BPM). 
 * The drum beat processing runs on a dedicated thread that 
 * schedules sound playback based on the selected mode and BPM.
 */
#ifndef DRUM_BEAT_H
#define DRUM_BEAT_H

#include "audio_mixer.h"

typedef enum {
    DRUM_MODE_NONE,
    DRUM_MODE_ROCK,
    DRUM_MODE_CUSTOM
} DrumMode;

void DrumBeat_init(void);

void DrumBeat_set_mode(DrumMode mode);
DrumMode DrumBeat_get_mode(void);

void DrumBeat_set_bpm(int bpm);
int DrumBeat_get_bpm(void);

void DrumBeat_next_mode(void);
void DrumBeat_cleanup(void);

#endif
