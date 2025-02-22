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

#include "hal/sampler.h"
#include "hal/pwm.h"

#include "udp.h"

#define PORT 12345
#define BUF_SIZE 1024
#define UDP_PACKET_SIZE 1500

static bool stop_thread = false;

// Global buffer to store the last non-blank command.
static char last_command[BUF_SIZE] = {0};
static int udp_sock;
static pthread_t udp_thread;

// Allow module to ensure it has been initialized (once!)
static bool is_initialized = false;

// Sends a UDP message to the given client.
static void send_udp_message(const char *message, struct sockaddr_in *client_addr, socklen_t addr_len)
{
    sendto(udp_sock, message, strlen(message), 0, (struct sockaddr *)client_addr, addr_len);
}

// Handles the "help" command.
static void handle_help(struct sockaddr_in *client_addr, socklen_t addr_len)
{
    const char *help_msg =
        "Accepted command examples:\n"
        "count -- get the total number of samples taken.\n"
        "length -- get the number of samples taken in the previously completed second.\n"
        "dips -- get the number of dips in the previously completed second.\n"
        "history -- get all the samples in the previously completed second.\n"
        "stop -- cause the server program to end.\n"
        "<enter> -- repeat last command.\n";
    send_udp_message(help_msg, client_addr, addr_len);
}

// Handles the "count" command.
static void handle_count(struct sockaddr_in *client_addr, socklen_t addr_len)
{
    long long count = Sampler_getNumSamplesTaken();
    char msg[128];
    snprintf(msg, sizeof(msg), "# samples taken total: %lld\n", count);
    send_udp_message(msg, client_addr, addr_len);
}

// Handles the "length" command.
static void handle_length(struct sockaddr_in *client_addr, socklen_t addr_len)
{
    int len = Sampler_getHistorySize();
    char msg[128];
    snprintf(msg, sizeof(msg), "# samples taken last second: %d\n", len);
    send_udp_message(msg, client_addr, addr_len);
}

// Handles the "dips" command.
static void handle_dips(struct sockaddr_in *client_addr, socklen_t addr_len)
{
    int dips = Sampler_getDips();
    char msg[128];
    snprintf(msg, sizeof(msg), "# Dips: %d\n", dips);
    send_udp_message(msg, client_addr, addr_len);
}

// Handles the "history" command.
static void handle_history(struct sockaddr_in *client_addr, socklen_t addr_len)
{
    int size;
    double *history = Sampler_getHistory(&size);
    if (size <= 0) {
        send_udp_message("No history data available.\n", client_addr, addr_len);
        free(history);
        return;
    }
    
    char packet_buf[UDP_PACKET_SIZE];
    int packet_len = 0;
    int count_in_line = 0;
    packet_buf[0] = '\0';
    
    for (int i = 0; i < size; i++) {
        char sample_str[32];
        snprintf(sample_str, sizeof(sample_str), "%.3f", history[i]);
        
        char formatted[40];
        if (count_in_line > 0) {
            snprintf(formatted, sizeof(formatted), ", %s", sample_str);
        } else {
            snprintf(formatted, sizeof(formatted), "%s", sample_str);
        }

        int formatted_len = strlen(formatted);
        
        if (packet_len + formatted_len >= UDP_PACKET_SIZE - 1) {
            send_udp_message(packet_buf, client_addr, addr_len);
            packet_buf[0] = '\0';
            packet_len = 0;
        }
        
        strcat(packet_buf, formatted);
        packet_len += formatted_len;
        count_in_line++;
        
        if (count_in_line >= 10) {
            if (packet_len + 1 >= UDP_PACKET_SIZE - 1) {
                send_udp_message(packet_buf, client_addr, addr_len);
                packet_buf[0] = '\0';
                packet_len = 0;
            } else {
                strcat(packet_buf, "\n");
                packet_len += 1;
            }
            count_in_line = 0;
        }
    }
    
    if (packet_len > 0) {
        send_udp_message(packet_buf, client_addr, addr_len);
    }

    free(history);
}

// Handles the "stop" command.
static void handle_stop(struct sockaddr_in *client_addr, socklen_t addr_len)
{
    send_udp_message("Program terminating.\n", client_addr, addr_len);

    extern bool stop_main_thread; 
    stop_main_thread = true;
    stop_thread = true;
}

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
        } else {
            // Save the non-blank command.
            strncpy(last_command, command, sizeof(last_command) - 1);
            last_command[sizeof(last_command) - 1] = '\0';
        }
        
        // Dispatch the command (case-insensitive).
        if (strcasecmp(command, "help") == 0 || strcasecmp(command, "?") == 0) {
            handle_help(&client_addr, addr_len);
        } else if (strcasecmp(command, "count") == 0) {
            handle_count(&client_addr, addr_len);
        } else if (strcasecmp(command, "length") == 0) {
            handle_length(&client_addr, addr_len);
        } else if (strcasecmp(command, "dips") == 0) {
            handle_dips(&client_addr, addr_len);
        } else if (strcasecmp(command, "history") == 0) {
            handle_history(&client_addr, addr_len);
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