/*
 * UDP Module
 *
 * Provide a simple UDP server that listens on port 12345 for incoming commands.
 * The module processes commands, interacting with the audio and a local NodeJS server:
 *   - "help" or "?" displays a help message with accepted commands.
 *   - "mode" retrieves or sets the drum-beat mode.
 *   - "volume" retrieves or sets the audio volume.
 *   - "tempo" retrieves or sets the tempo (BPM) for the drum beat.
 *   - "play" triggers playback of one of three sound files.
 *   - "stop" gracefully terminates the program.
 */
#ifndef _UDP_H_
#define _UDP_H_

void UDP_init(void);
void UDP_cleanup(void);

#endif