#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <assert.h>

#include "drum_beat.h"
#include "audio_mixer.h"
#include "udp.h"

#define PORT 12345
#define BUF_SIZE 1024
#define UDP_PACKET_SIZE 1500

static bool stop_thread = false;

static char last_command[BUF_SIZE] = {0};
static int udp_sock;
static pthread_t udp_thread;

// Allow module to ensure it has been initialized (once!)
static bool is_initialized = false;

// Sound files
extern wavedata_t sound1;
extern wavedata_t sound2;
extern wavedata_t sound3;

// Sends a UDP message to the given client.
static void send_udp_message(const char *message, struct sockaddr_in *client_addr, socklen_t addr_len)
{
    sendto(udp_sock, message, strlen(message), 0, (struct sockaddr *)client_addr, addr_len);
}

// Handles the "help" command.
static void handle_help(struct sockaddr_in *client_addr, socklen_t addr_len)
{
    const char *help_msg =
        "Accepted commands:\n"
        "help or ?             -- show this help message\n"
        "mode <num>            -- set the drum-beat mode (e.g., 0 for standard rock, 1 for no beat)\n"
        "volume <num>          -- set the volume (e.g., 80)\n"
        "tempo <num>           -- set the tempo in BPM (e.g., 90)\n"
        "play <sound>          -- play a sound (1, 2, or 3)\n"
        "stop                  -- gracefully terminate the program\n"
        "<enter>               -- repeat the last non-blank command\n";
    send_udp_message(help_msg, client_addr, addr_len);
}

static void handle_mode(const char *command, struct sockaddr_in *client_addr, socklen_t addr_len)
{
    // Print the received command for debugging.
    printf("handle_mode received command: \"%s\"\n", command);

    // Duplicate the command string so that tokenization doesn't alter the original.
    char *cmd_copy = strdup(command);
    if (!cmd_copy) {
        perror("strdup failed");
        return;
    }

    // Tokenize the command.
    // Expected formats:
    // "mode" or "mode null"   -> return the current mode.
    // "mode <number>"         -> set the mode accordingly (0, 1, or 2).
    char *token = strtok(cmd_copy, " ");
    token = strtok(NULL, " ");  

    // No parameter.
    if (token == NULL || strcmp(token, "null") == 0) {
        DrumMode current = DrumBeat_get_mode();
        char msg[128];
        snprintf(msg, sizeof(msg), "%d", current);
        send_udp_message(msg, client_addr, addr_len);
    }
    // Handle valid mode.
    else {
        int mode_int = atoi(token);
        if (mode_int < 0 || mode_int >= 3) {
            send_udp_message("Usage: mode <0|1|2|null>\n", client_addr, addr_len);
            free(cmd_copy);
            return;
        }

        DrumBeat_set_mode((DrumMode)mode_int);
        char msg[128];
        snprintf(msg, sizeof(msg), "%d", mode_int);
        send_udp_message(msg, client_addr, addr_len);
    }

    free(cmd_copy);
}

// Handle getting current volume and setting the volume.
// volume null -> return current volume.
// volume {value} -> set volume.
static void handle_volume(const char *command, struct sockaddr_in *client_addr, socklen_t addr_len)
{
    // Print the received command for debugging.
    printf("handle_get_volume received command: \"%s\"\n", command);
    
    char *cmd_copy = strdup(command);
    if (!cmd_copy) {
        perror("strdup failed");
        return;
    }

    // Get token
    char *token = strtok(cmd_copy, " ");
    token = strtok(NULL, " ");

    // If we are getting "volume null", return the current volume.
    if (token == NULL || strcmp(token, "null") == 0) {
        int vol = AudioMixer_getVolume();
        char msg[128];
        snprintf(msg, sizeof(msg), "%d", vol);
        send_udp_message(msg, client_addr, addr_len);
    } 
    // Handle valid volume.
    else {
        int new_vol = atoi(token);
        AudioMixer_setVolume(new_vol);
        char msg[128];
        snprintf(msg, sizeof(msg), "%d", new_vol);
        send_udp_message(msg, client_addr, addr_len);
    }

    free(cmd_copy);
}

// Handles the "tempo" command.
static void handle_tempo(const char *command, struct sockaddr_in *client_addr, socklen_t addr_len)
{
    // Duplicate the command string since strtok modifies its input.
    char *cmd_copy = strdup(command);
    if (!cmd_copy) {
        perror("strdup failed");
        return;
    }

    // Tokenize the command. Expected formats:
    // "tempo" or "tempo null"   --> get the current tempo.
    // "tempo <number>"          --> set the new tempo.
    char *token = strtok(cmd_copy, " ");
    token = strtok(NULL, " ");

    if (token == NULL || strcmp(token, "null") == 0) {
        int current_bpm = DrumBeat_get_bpm();
        char msg[128];
        snprintf(msg, sizeof(msg), "%d", current_bpm);
        send_udp_message(msg, client_addr, addr_len);
    } 
    else {
        int bpm = atoi(token);
        DrumBeat_set_bpm(bpm);
        char msg[128];
        snprintf(msg, sizeof(msg), "%d", bpm);
        send_udp_message(msg, client_addr, addr_len);
    }

    free(cmd_copy);
}

// Handles the "play" command.
static void handle_play(const char *command, struct sockaddr_in *client_addr, socklen_t addr_len)
{
    int sound_num;
    if (sscanf(command, "play %d", &sound_num) == 1) {
        char msg[128];
        switch (sound_num) {
            case 1:
                AudioMixer_queueSound(&sound1);
                snprintf(msg, sizeof(msg), "Playing sound 1\n");
                break;
            case 2:
                AudioMixer_queueSound(&sound2);
                snprintf(msg, sizeof(msg), "Playing sound 2\n");
                break;
            case 3:
                AudioMixer_queueSound(&sound3);
                snprintf(msg, sizeof(msg), "Playing sound 3\n");
                break;
            default:
                snprintf(msg, sizeof(msg), "Invalid sound number: %d. Use 1, 2, or 3.\n", sound_num);
                break;
        }
        send_udp_message(msg, client_addr, addr_len);
    } 
    else {
        send_udp_message("Usage: play <sound_number>\n", client_addr, addr_len);
    }
}

// Handles the "stop" command.
static void handle_stop(struct sockaddr_in *client_addr, socklen_t addr_len)
{
    send_udp_message("Program terminating.\n", client_addr, addr_len);

    extern bool stop_main_thread; 
    stop_main_thread = true;
    stop_thread = true;
}

// Reusing from assignment #2.
// The UDP listener thread: receives UDP packets and processes user commands.
static void *udp_listener(void *arg)
{
    (void)arg;
    
    struct sockaddr_in client_addr;
    socklen_t addr_len;
    char buffer[BUF_SIZE];

    while (!stop_thread) {
        // Reinitialize addr_len on every loop iteration.
        addr_len = sizeof(client_addr);
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recvfrom(
            udp_sock, 
            buffer, 
            sizeof(buffer) - 1, 
            0,
            (struct sockaddr *)&client_addr, &addr_len
        );

        if (bytes_received < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
                continue;
            else {
                perror("recvfrom");
                continue;
            }
        }

        buffer[bytes_received] = '\0';
        
        // Trim leading whitespace/newlines.
        char *command = buffer;
        while (*command == ' ' || *command == '\t' || *command == '\n' || *command == '\r') {
            command++;
        }
        
        // Remove trailing newlines.
        char *end = command + strlen(command) - 1;
        while (end > command && (*end == '\n' || *end == '\r')) {
            *end = '\0';
            end--;
        }
        
        // If the command is blank, repeat the last command (if any).
        if (strlen(command) == 0) {
            if (strlen(last_command) == 0) {
                send_udp_message("Unknown command.\n", &client_addr, addr_len);
                continue;
            } else {
                command = last_command;
            }
        } 
        else {
            // Save the non-blank command.
            strncpy(last_command, command, sizeof(last_command) - 1);
            last_command[sizeof(last_command) - 1] = '\0';
        }
        
        // Dispatch the command (case-insensitive).
        if (strcasecmp(command, "help") == 0 || strcasecmp(command, "?") == 0) {
            handle_help(&client_addr, addr_len);
        } else if (strncasecmp(command, "mode", 4) == 0) {
            handle_mode(command, &client_addr, addr_len);
        } else if (strncasecmp(command, "volume", 6) == 0) {
            handle_volume(command, &client_addr, addr_len);
        } else if (strncasecmp(command, "tempo", 5) == 0) {
            handle_tempo(command, &client_addr, addr_len);
        } else if (strncasecmp(command, "play", 4) == 0) {
            handle_play(command, &client_addr, addr_len);
        } else if (strcasecmp(command, "stop") == 0) {
            handle_stop(&client_addr, addr_len);
        } else {
            char unknown_msg[128];
            snprintf(unknown_msg, sizeof(unknown_msg), "Unknown command: %.100s\n", command);
            send_udp_message(unknown_msg, &client_addr, addr_len);
        }
    }
    
    return NULL;
}

void UDP_init(void)
{
    printf("UDP - Initializing\n");
    
    assert(!is_initialized);
    is_initialized = true;

    // Create a UDP socket.
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);
    
    if (bind(udp_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(udp_sock);
        exit(EXIT_FAILURE);
    }
    
    // Create the UDP listener thread.
    if (pthread_create(&udp_thread, NULL, udp_listener, NULL) != 0) {
        perror("pthread_create");
        close(udp_sock);
        exit(EXIT_FAILURE);
    }
}

void UDP_cleanup(void)
{
    printf("UDP - Cleanup\n");
    
    assert(is_initialized);
    is_initialized = false;
    stop_thread = true;

    pthread_cancel(udp_thread);
    pthread_join(udp_thread, NULL);
    
    close(udp_sock);
    printf("UDP - Done.\n");
}