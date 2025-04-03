#include "hal/accelerometer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <math.h>
#include <pthread.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <signal.h>

// I2C bus and sensor address
#define I2CDRV_LINUX_BUS "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x19

// Sensor registers (from datasheet)
#define REG_CTRL1      0x20    // Control register: enables sensor axes and sets data rate.

#define REG_OUT_X_L    0x28    // X-axis low byte
#define REG_OUT_X_H    0x29    // X-axis high byte
#define REG_OUT_Y_L    0x2A    // Y-axis low byte
#define REG_OUT_Y_H    0x2B    // Y-axis high byte
#define REG_OUT_Z_L    0x2C    // Z-axis low byte
#define REG_OUT_Z_H    0x2D    // Z-axis high byte

// Timing definitions (in microseconds)
#define SENSOR_READ_DELAY 100000    // Delay between sensor reads
#define I2C_UPDATE_DELAY  50000      // Delay after writing to sensor

// Range definitions for normalization
// Map the default value to 0, the provided MIN value to +1, and MAX value to -1.
#define MAX_ACCEL_X_VALUE   32768
#define DEFAULT_ACCEL_X_VALUE -86
#define MIN_ACCEL_X_VALUE   -32768

#define MAX_LEFT_VALUE_TILT 16200
#define MAX_RIGHT_VALUE_TILT -16200

#define MAX_UP_VALUE_TILT -16200
#define MAX_DOWN_VALUE_TILT 16200

#define MAX_ACCEL_Y_VALUE   32768
#define DEFAULT_ACCEL_Y_VALUE 200
#define MIN_ACCEL_Y_VALUE   -32768

#define MAX_ACCEL_Z_VALUE   32768
#define DEFAULT_ACCEL_Z_VALUE 16500
#define MIN_ACCEL_Z_VALUE   -32768

// Shake detection settings
#define SHAKE_THRESHOLD         0.50f
#define SHAKE_CHECK_INTERVAL    10000 // 10ms (100 Hz)

// Debounce interval (milliseconds) per axis
#define DEBOUNCE_DELAY_MS 500

// High-Performance / Low-Power mode 50 Hz, High-Performance Mode (14-bit resolution), Low-Power Mode 4 (14-bit resolution)
#define CONTROL_REGISTER_OPTION 0x47

// Global variables for accelerometer data and thread control.
static bool is_initialized = false;
static int i2c_fd;
static volatile bool stop_thread = false;
static int16_t x, y, z;

// Single mutex to protect x, y, z data.
static pthread_mutex_t lock_data = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t lock_i2c = PTHREAD_MUTEX_INITIALIZER;

// Thread ID for the sensor thread.
static pthread_t thread_sensor;
static pthread_t thread_shake;

// Global variables for per-axis shake detection.
static float prev_norm_x = 0.0f;
static float prev_norm_y = 0.0f; 
static float prev_norm_z = 0.0f;

static uint64_t last_trigger_x_ms = 0;
static uint64_t last_trigger_y_ms = 0;
static uint64_t last_trigger_z_ms = 0;

static AccelerometerCallback shake_x_callback = NULL;
static AccelerometerCallback shake_y_callback = NULL;
static AccelerometerCallback shake_z_callback = NULL;

// Helper function: Get current time in milliseconds using CLOCK_MONOTONIC.
static uint64_t get_time_ms(void) 
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)(ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL);
}

// Initialize the I2C bus and set the sensor address.
static int init_i2c_bus(char *bus, int address) 
{
    int i2c_file_desc = open(bus, O_RDWR);
    if (i2c_file_desc == -1) {
        printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
        perror("init_i2c_bus: Unable to initialize i2c bus");
        exit(EXIT_FAILURE);
    }

    if (ioctl(i2c_file_desc, I2C_SLAVE, address) == -1) {
        perror("init_i2c_bus: Unable to set I2C device to slave address.");
        exit(EXIT_FAILURE);
    }
    return i2c_file_desc;
}

// Write a single byte to an I2C register.
static void write_i2c_reg8(int i2c_fd, uint8_t reg_addr, uint8_t value) 
{
    uint8_t buf[2] = { reg_addr, value };
    if (write(i2c_fd, buf, 2) != 2) {
        perror("write_i2c_reg8: Failed to write register");
        exit(EXIT_FAILURE);
    }
}

// Read multiple bytes from I2C starting from a register.
static void read_i2c_bytes(int i2c_fd, uint8_t start_reg, uint8_t *buffer, size_t len) 
{
    // Idea comes from: GPT-o3 mini-high model.
    // https://www.ti.com/lit/an/slvafl0/slvafl0.pdf?ts=1741509093379
    // Enable auto-increment by OR-ing the register address with 0x80 (most significant bit).
    // The device’s internal register pointer automatically moves to 
    // the next register after each byte is read.
    uint8_t reg = start_reg | 0x80;
    if (write(i2c_fd, &reg, 1) != 1) {
        perror("read_i2c_bytes: Failed to write register address");
        exit(EXIT_FAILURE);
    }

    if (read(i2c_fd, buffer, len) != (ssize_t)len) {
        perror("read_i2c_bytes: Failed to read bytes");
        exit(EXIT_FAILURE);
    }
}

// Sensor thread function: reads all axes at once.
// Reference: https://stackoverflow.com/questions/56756659/how-to-get-usable-accelerometer-readings
// Assignment 3: "general accelerometer hints".
// Read raw accelerometer data (x, y, z) from the sensor.
static void* read_sensor_thread(void *arg) 
{
    (void)arg;
    uint8_t buffer[6];
    while (!stop_thread) {
        // Protect the I2C transaction.
        pthread_mutex_lock(&lock_i2c);
        write_i2c_reg8(i2c_fd, REG_CTRL1, CONTROL_REGISTER_OPTION);
        usleep(I2C_UPDATE_DELAY);
        read_i2c_bytes(i2c_fd, REG_OUT_X_L, buffer, 6);
        pthread_mutex_unlock(&lock_i2c);

        // Combine low and high bytes (little-endian)
        // Ex: high byte: 0x12, low byte: 0x34 
        // left shift by 8 bits: 0x1200, combine using OR: 0x1234
        // gives you the raw reading of x value.
        int16_t raw_x = (int16_t)((buffer[1] << 8) | buffer[0]);
        int16_t raw_y = (int16_t)((buffer[3] << 8) | buffer[2]);
        int16_t raw_z = (int16_t)((buffer[5] << 8) | buffer[4]);

        // Update sensor data under protection.
        pthread_mutex_lock(&lock_data);
        x = raw_x;
        y = raw_y;
        z = raw_z;
        pthread_mutex_unlock(&lock_data);
        
        usleep(SENSOR_READ_DELAY);
    }

    return NULL;
}

// Accessor functions to retrieve raw accelerometer values.
int16_t Accelerometer_getX(void) 
{
    int16_t value;
    pthread_mutex_lock(&lock_data);
    value = x;
    pthread_mutex_unlock(&lock_data);
    return value;
}

int16_t Accelerometer_getY(void) 
{
    int16_t value;
    pthread_mutex_lock(&lock_data);
    value = y;
    pthread_mutex_unlock(&lock_data);
    return value;
}

int16_t Accelerometer_getZ(void) 
{
    int16_t value;
    pthread_mutex_lock(&lock_data);
    value = z;
    pthread_mutex_unlock(&lock_data);
    return value;
}

// Map each raw reading to a normalized value between -1 and 1.
static float normalize_x(int16_t raw) 
{
    if (raw >= DEFAULT_ACCEL_X_VALUE)
        return (float)(raw - DEFAULT_ACCEL_X_VALUE) / (MAX_ACCEL_X_VALUE - DEFAULT_ACCEL_X_VALUE);
    return (float)(raw - DEFAULT_ACCEL_X_VALUE) / (DEFAULT_ACCEL_X_VALUE - MIN_ACCEL_X_VALUE);
}

static float normalize_y(int16_t raw) 
{
    if (raw >= DEFAULT_ACCEL_Y_VALUE)
        return (float)(raw - DEFAULT_ACCEL_Y_VALUE) / (MAX_ACCEL_Y_VALUE - DEFAULT_ACCEL_Y_VALUE);
    return (float)(raw - DEFAULT_ACCEL_Y_VALUE) / (DEFAULT_ACCEL_Y_VALUE - MIN_ACCEL_Y_VALUE);
}

static float normalize_z(int16_t raw) 
{
    if (raw >= DEFAULT_ACCEL_Z_VALUE)
        return (float)(raw - DEFAULT_ACCEL_Z_VALUE) / (MAX_ACCEL_Z_VALUE - DEFAULT_ACCEL_Z_VALUE);
    return (float)(raw - DEFAULT_ACCEL_Z_VALUE) / (DEFAULT_ACCEL_Z_VALUE - MIN_ACCEL_Z_VALUE);
}

// Check if the change in normalized axis value 
// exceeds the threshold and the debounce period has passed
bool check_axis_shake(float current, float *prev, uint64_t *last_trigger_ms, float threshold) 
{
    float diff = fabs(current - *prev);
    uint64_t now_ms = get_time_ms();
    bool shaken = false;
    if (diff > threshold && (now_ms - *last_trigger_ms > DEBOUNCE_DELAY_MS)) {
        shaken = true;
        *last_trigger_ms = now_ms;
    }
    *prev = current;
    return shaken;
}

void Accelerometer_register_shake_x_callback(AccelerometerCallback callback)
{
    shake_x_callback = callback;
}

void Accelerometer_register_shake_y_callback(AccelerometerCallback callback)
{
    shake_y_callback = callback;
}

void Accelerometer_register_shake_z_callback(AccelerometerCallback callback)
{
    shake_z_callback = callback;
}

bool Accelerometer_check_shake_x(void) 
{
    float norm = normalize_x(Accelerometer_getX());

    // Trigger a callback when x axis reaches certain threshold.
    return check_axis_shake(norm, &prev_norm_x, &last_trigger_x_ms, SHAKE_THRESHOLD);
}


bool Accelerometer_check_shake_y(void) 
{
    float norm = normalize_y(Accelerometer_getY());

    // Trigger a callback when x axis reaches certain threshold.
    return check_axis_shake(norm, &prev_norm_y, &last_trigger_y_ms, SHAKE_THRESHOLD);
}


bool Accelerometer_check_shake_z(void) 
{
    float norm = normalize_z(Accelerometer_getZ());

    // Trigger a callback when x axis reaches certain threshold.
    return check_axis_shake(norm, &prev_norm_z, &last_trigger_z_ms, SHAKE_THRESHOLD);
}

float Accelerometer_get_normalized_x_rotation(void)
{
    int16_t raw_x = Accelerometer_getX();
    return (float)raw_x / (float)MAX_LEFT_VALUE_TILT;
}

float Accelerometer_get_normalized_y_rotation(void) 
{
    int16_t raw_y = Accelerometer_getY();
    return (float)raw_y / (float)MAX_DOWN_VALUE_TILT;
}

static void check_shake_x(void) 
{
    float norm = normalize_x(Accelerometer_getX());

    // Trigger a callback when x axis reaches certain threshold.
    if (check_axis_shake(norm, &prev_norm_x, &last_trigger_x_ms, SHAKE_THRESHOLD) && shake_x_callback != NULL)
        shake_x_callback();
}

static void check_shake_y(void) 
{
    float norm = normalize_y(Accelerometer_getY());

    // Trigger a callback when y axis reaches certain threshold.
    if (check_axis_shake(norm, &prev_norm_y, &last_trigger_y_ms, SHAKE_THRESHOLD) && shake_y_callback != NULL)
        shake_y_callback();
}

static void check_shake_z(void) 
{
    float norm = normalize_z(Accelerometer_getZ());

    // Trigger a callback when y axis reaches certain threshold.
    if (check_axis_shake(norm, &prev_norm_z, &last_trigger_z_ms, SHAKE_THRESHOLD) && shake_z_callback != NULL)
        shake_z_callback();
}

static void* shake_checker_thread(void *arg) 
{
    (void)arg;
    while (!stop_thread) {
        check_shake_x();
        check_shake_y();
        check_shake_z();

        usleep(SHAKE_CHECK_INTERVAL);
    }

    return NULL;
}

// Initialize the accelerometer and start the sensor thread.
void Accelerometer_init(void) 
{
    printf("Accelerometer - Initializing\n");
    assert(!is_initialized);
    
    i2c_fd = init_i2c_bus(I2CDRV_LINUX_BUS, I2C_DEVICE_ADDRESS);

    stop_thread = false;

    // Initialize mutex for sensor data.
    pthread_mutex_init(&lock_data, NULL);

    // Initialize the I2C mutex.
    pthread_mutex_init(&lock_i2c, NULL);

    // Create the sensor thread.
    if (pthread_create(&thread_sensor, NULL, read_sensor_thread, NULL) != 0) {
        perror("Accelerometer_init: Failed to create sensor thread");
        exit(EXIT_FAILURE);
    }

    // Create the shake checker thread.
    if (pthread_create(&thread_shake, NULL, shake_checker_thread, NULL) != 0) {
        perror("Accelerometer_init: Failed to create shake thread");
        exit(EXIT_FAILURE);
    }

    is_initialized = true;
    srand(time(0));
}

// Clean up the accelerometer resources.
void Accelerometer_cleanup(void) 
{
    printf("Accelerometer - Cleanup\n");
    assert(is_initialized);
    stop_thread = true;

    pthread_cancel(thread_sensor);
    pthread_join(thread_sensor, NULL);

    pthread_cancel(thread_shake);
    pthread_join(thread_shake, NULL);

    pthread_mutex_destroy(&lock_data);
    pthread_mutex_destroy(&lock_i2c);
    
    close(i2c_fd);
    is_initialized = false;
    printf("Accelerometer - Done.\n");
}