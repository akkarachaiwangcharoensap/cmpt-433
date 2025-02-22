#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <assert.h>

#include "hal/sampler.h"
#include "hal/light_sensor.h"

#define INITIAL_CAPACITY 2000
#define SAMPLER_DELAY 1000

// Reference: Assignment Description 1.3
#define DIP_THRESHOLD 0.1      // Voltage must drop by 0.1V to trigger a dip.
#define HYSTERESIS 0.03        // Hysteresis of 0.03V prevents immediate re-triggering.
#define SMOOTHING_ALPHA 0.1    // Exponential smoothing factor.

bool is_initialized = false;

// Thread
static pthread_t sampler_thread;
static bool stop_thread = false;
static pthread_mutex_t lock_thread;

static double *current_samples = NULL;
static int current_size = 0;
static int current_capacity = 0;

// Keep track of sample history
static double *history_samples = NULL;
static int history_size = 0;

// Statistics values
static long long total_samples_taken = 0;
static double total_sum = 0.0;

static void* sampling_func(void *arg) 
{
    (void)arg; // Not being used.
    double voltage;
    while (!stop_thread) {
        pthread_mutex_lock(&lock_thread);
        {
            voltage = LightSensor_read_voltage();

            // If the size exceeds the capacity, extend the capacity by reallocating new size.
            if (current_size >= current_capacity) {
                printf("sampling_func: reallocating more memory...\n");
                int new_capacity = (current_capacity == 0 ? INITIAL_CAPACITY : current_capacity * 2);
                double *new_array = realloc(current_samples, new_capacity * sizeof(double));
                if (new_array == NULL) {
                    perror("sampling_thread: Failed to reallocate more memory.");
                    exit(EXIT_FAILURE);
                }

                current_samples = new_array;
                current_capacity = new_capacity;
            }

            else if (current_size < current_capacity) {
                // Set the next element to the current reading.
                current_samples[current_size] = voltage;
                current_size++;
                total_samples_taken++;
                total_sum += voltage;
            }
        }
        pthread_mutex_unlock(&lock_thread);

        // Sample every 1ms
        usleep(1000);
    }

    return NULL;
}

void Sampler_init(void) 
{
    printf("Sampler - Initializing\n");

    assert(!is_initialized);
    srand(time(0));

    current_samples = malloc(INITIAL_CAPACITY * sizeof(double));
    if (current_samples == NULL) {
        perror("Sampler_init: Failed to allocate memory for current_samples.");
        exit(EXIT_FAILURE);
    }

    current_capacity = INITIAL_CAPACITY;
    current_size = 0;

    history_samples = NULL;
    history_size = 0;

    total_samples_taken = 0;
    total_sum = 0.0;

    pthread_mutex_init(&lock_thread, NULL);

    LightSensor_init();

    if (pthread_create(&sampler_thread, NULL, sampling_func, NULL) != 0) {
        perror("Sampler_init: Failed to create the sampler thread.");
        exit(EXIT_FAILURE);
    }

    stop_thread = false;
    is_initialized = true;
}

void Sampler_cleanup(void) 
{
    printf("Sampler - Cleanup\n");
    assert(is_initialized);
    is_initialized = false;
    stop_thread = true;

    pthread_cancel(sampler_thread);
    pthread_join(sampler_thread, NULL);
    pthread_mutex_lock(&lock_thread);
    {
        // Clean up allocated memory.
        free(current_samples);
        current_samples = NULL;
        current_size = 0;
        current_capacity = 0;

        free(history_samples);
        history_samples = NULL;
        history_size = 0;
    }
    pthread_mutex_unlock(&lock_thread);
    pthread_mutex_destroy(&lock_thread);

    printf("Sampler - Done.\n");

    LightSensor_cleanup();
}

void Sampler_moveCurrentDataToHistory(void) 
{
    pthread_mutex_lock(&lock_thread);
    {
        // Free previous history.
        if (history_samples != NULL) {
            free(history_samples);
        }

        // Copy current samples to the new history.
        if (current_size > 0) {
            history_samples = malloc(current_size * sizeof(double));
            if (history_samples == NULL) {
                perror("Sampler_moveCurrentDataToHistory: Failed to allocate memory for history_samples.");
                exit(EXIT_FAILURE);
            }

            memcpy(history_samples, current_samples, current_size * sizeof(double));
            history_size = current_size;
        } 
        // If no new data.
        else {
            history_samples = NULL;
            history_size = 0;
        }
        
        // Reset states once the data is moved.
        current_size = 0;
    }
    pthread_mutex_unlock(&lock_thread);
}

int Sampler_getHistorySize(void) 
{
    int size;
    pthread_mutex_lock(&lock_thread);
    size = history_size;
    pthread_mutex_unlock(&lock_thread);
    return size;
}

int Sampler_getDips(void) 
{
    int dips = 0;
    double *samples = NULL;
    int n = 0;

    // Copy history safely.
    pthread_mutex_lock(&lock_thread);
    {
        n = history_size;
        if (n > 0) {
            samples = malloc(n * sizeof(double));
            if (samples == NULL) {
                perror("Sampler_getDips: Failed to allocate memory for samples copy.");
                pthread_mutex_unlock(&lock_thread);
                exit(EXIT_FAILURE);
            }
            memcpy(samples, history_samples, n * sizeof(double));
        }
    }
    pthread_mutex_unlock(&lock_thread);

    if (n == 0 || samples == NULL) {
        free(samples);
        return 0;
    }

    // https://en.wikipedia.org/wiki/Exponential_smoothing
    // Compute exponential smoothing of the samples.
    double smoothed_avg = samples[0];
    bool in_dip = false;

    for (int i = 0; i < n; i++) {
        double sample = samples[i];
        
        // Update smoothed average
        if (i > 0) {
            smoothed_avg = SMOOTHING_ALPHA * sample + (1 - SMOOTHING_ALPHA) * smoothed_avg;
        }
        
        // Calculate the current thresholds.
        double dip_trigger_threshold = smoothed_avg - DIP_THRESHOLD;
        double dip_reset_threshold   = smoothed_avg - (DIP_THRESHOLD - HYSTERESIS);

        // Assuming that lower light levels yield lower voltages:
        // If not in a dip and the sample falls at or below the dip trigger, count a dip.
        if (!in_dip && sample <= dip_trigger_threshold) {
            dips++;
            in_dip = true;
        }
        // Once in a dip, wait until the reading rises to the reset threshold before allowing a new dip.
        else if (in_dip && sample >= dip_reset_threshold) {
            in_dip = false;
        }
    }

    free(samples);
    return dips;
}

// Get a copy of the samples in the sample history.
// Returns a newly allocated array and sets `size` to be the
// number of elements in the returned array (output-only parameter).
// The calling code must call free() on the returned pointer.
// Note: It provides both data and size to ensure consistency.
double* Sampler_getHistory(int *size) 
{
    double *result = NULL;
    pthread_mutex_lock(&lock_thread);
    {
        int n = history_size;
        if (n > 0) {
            result = malloc(n * sizeof(double));
            if (result == NULL) {
                perror("Sampler_getHistory: Failed to allocate memory for result.");
                exit(EXIT_FAILURE);
            }
            memcpy(result, history_samples, n * sizeof(double));
        }
        *size = n;
    }
    pthread_mutex_unlock(&lock_thread);
    return result;
}

double Sampler_getAverageReading(void) 
{
    double avg;
    pthread_mutex_lock(&lock_thread);
    {
        avg = (total_samples_taken > 0) ? (total_sum / total_samples_taken) : 0.0;
    }
    pthread_mutex_unlock(&lock_thread);
    return avg;
}

long long Sampler_getNumSamplesTaken(void)
{
    long long num;
    pthread_mutex_lock(&lock_thread);
    {
        num = total_samples_taken;
    }
    pthread_mutex_unlock(&lock_thread);
    return num;
}