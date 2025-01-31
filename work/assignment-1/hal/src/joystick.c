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

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "hal/joystick.h"

#include <pthread.h>

// Device bus and address
#define I2CDRV_LINUX_BUS "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x48

// Register in TLA2024
#define REG_CONFIGURATION 0x01
#define REG_DATA 0x00

// These values are retrieved from reading directly from the joystick data.
#define MAX_JOYSTICK_VERTICAL_VALUE 1616
#define DEFAULT_JOYSTICK_VERTICAL_VALUE 816
#define MIN_JOYSTICK_VERTICAL_VALUE 16

#define MAX_JOYSTICK_HORIZONTAL_VALUE 1616
#define DEFAULT_JOYSTICK_HORIZONTAL_VALUE 848
#define MIN_JOYSTICK_HORIZONTAL_VALUE 0

// Manual configurable
#define JOYSTICK_SENSITIVITY 0.25f

// Configuration reg contents for continuously sampling different channels
#define TLA2024_CHANNEL_CONF_Y 0x83C2
#define TLA2024_CHANNEL_CONF_X 0x83D2

#define I2C_UPDATE_DELAY 50000
#define I2C_READ_DELAY 100000

struct Joystick {
    pthread_t read_thread;
    int i2c_file_desc;
    bool stop_thread;
    pthread_mutex_t lock;

    float vertical_value;
    float horizontal_value;
};

// Allow module to ensure it has been initialized (once!)
static bool is_initialized = false;

// Initialize i2c bus, the function is from the i2c guide.
static int init_i2c_bus(char* bus, int address)
{
    int i2c_file_desc = open(bus, O_RDWR);
    if (i2c_file_desc == -1) {
        printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
        perror("init_i2c_bus: Unable to initialize i2c bus \n");
        exit(EXIT_FAILURE);
    }

    if (ioctl(i2c_file_desc, I2C_SLAVE, address) == -1) {
        perror("init_i2c_bus: Unable to set I2C device to slave address.");
        exit(EXIT_FAILURE);
    }

    return i2c_file_desc;
}

// Write to i2c, the function is from the i2c guide.
static void write_i2c_reg16(int i2c_file_desc, uint8_t reg_addr, uint16_t value)
{
    int tx_size = 1 + sizeof(value);
    uint8_t buff[tx_size];
    buff[0] = reg_addr;
    buff[1] = (value & 0xFF);
    buff[2] = (value & 0xFF00) >> 8;
    int bytes_written = write(i2c_file_desc, buff, tx_size);
    if (bytes_written != tx_size) {
        perror("write_i2c_reg16: Unable to write i2c register.");
        exit(EXIT_FAILURE);
    }
}

// Read from i2c, the function is from the i2c guide.
static uint16_t read_i2c_reg16(int i2c_file_desc, uint8_t reg_addr)
{
    // To read a register, must first write the address.
    int bytes_written = write(i2c_file_desc, &reg_addr, sizeof(reg_addr));
    if (bytes_written != sizeof(reg_addr)) {
        perror("read_i2c_reg16: Unable to write i2c register.");
        exit(EXIT_FAILURE);
    }

    // Read and return the value.
    uint16_t value = 0;
    int bytes_read = read(i2c_file_desc, &value, sizeof(value));
    if (bytes_read != sizeof(value)) {
        perror("read_i2c_reg16: Unable to read i2c register.");
        exit(EXIT_FAILURE);
    }

    return value;
}

// Normalize the value, return -1 to 1 range.
// Reference: stackoverflow link goes here.
static float normalize_value(int value, int min, int max, int default_value)
{
    return 2.0f * (value - default_value) / (max - min);
}

// Read raw data and normalize value in a pthread using mutex lock/unlock.
static void* read_thread(void* arg)
{
    Joystick *joystick = (Joystick*)arg;

    // Ensure joystick is initialized.
    assert(joystick != NULL);
    
    while (!joystick->stop_thread) {
        write_i2c_reg16(joystick->i2c_file_desc, REG_CONFIGURATION, TLA2024_CHANNEL_CONF_Y);
        // Delay to ensure ADC can update the data.
        usleep(I2C_UPDATE_DELAY);

        uint16_t raw_read_vertical = read_i2c_reg16(joystick->i2c_file_desc, REG_DATA);
        uint16_t vertical_value = ((raw_read_vertical & 0x0FF) << 8) | ((raw_read_vertical & 0xF00) >> 8);
        vertical_value = vertical_value >> 4;

        pthread_mutex_lock(&joystick->lock);
        {
            joystick->vertical_value = normalize_value(vertical_value, MIN_JOYSTICK_VERTICAL_VALUE, MAX_JOYSTICK_VERTICAL_VALUE, DEFAULT_JOYSTICK_VERTICAL_VALUE);
        }
        pthread_mutex_unlock(&joystick->lock);

        // Read X Channel
        write_i2c_reg16(joystick->i2c_file_desc, REG_CONFIGURATION, TLA2024_CHANNEL_CONF_X);

        // Delay to ensure ADC can update the data.
        usleep(I2C_UPDATE_DELAY);

        uint16_t raw_read_horizontal = read_i2c_reg16(joystick->i2c_file_desc, REG_DATA);
        uint16_t horizontal_value = ((raw_read_horizontal & 0x0FF) << 8) | ((raw_read_horizontal & 0xF00) >> 8);
        horizontal_value = horizontal_value >> 4;

        pthread_mutex_lock(&joystick->lock);
        {
            // -1 corrects the direction: left is negative, right is positive.
            joystick->horizontal_value = -1 * normalize_value(horizontal_value, MIN_JOYSTICK_HORIZONTAL_VALUE, MAX_JOYSTICK_HORIZONTAL_VALUE, DEFAULT_JOYSTICK_HORIZONTAL_VALUE);
        }
        pthread_mutex_unlock(&joystick->lock);

        // Read ADC every I2C_READ_DELAY interval.
        usleep(I2C_READ_DELAY);
    }

    return NULL;
}

// Initialize a Joystick
Joystick* Joystick_init()
{
    printf("Joystick - Initializing\n");
    assert(!is_initialized);

    // Heap allocation
    Joystick *joystick = (Joystick*)malloc(sizeof(Joystick));
    if (joystick == NULL) {
        perror("Joystick_init: Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }

    joystick->i2c_file_desc = init_i2c_bus(I2CDRV_LINUX_BUS, I2C_DEVICE_ADDRESS);
    joystick->stop_thread = false;
    pthread_mutex_init(&joystick->lock, NULL);

    // Create a read thread to handle reading joystick value.
    // Make sure the thread is created without issues.
    if (pthread_create(&joystick->read_thread, NULL, read_thread, joystick) != 0) {
        perror("Joystick_init: Failed to create a read thread.");
        exit(EXIT_FAILURE);
    }

    is_initialized = true;
    srand(time(0));

    return joystick;
}

float Joystick_read_horizontal(Joystick *joystick)
{
    // Ensure joystick is initialized.
    assert(joystick != NULL);

    pthread_mutex_lock(&joystick->lock);
    float value = joystick->horizontal_value;
    pthread_mutex_unlock(&joystick->lock);

    return value;
}

float Joystick_read_vertical(Joystick *joystick)
{
    // Ensure joystick is initialized.
    assert(joystick != NULL);

    pthread_mutex_lock(&joystick->lock);
    float value = joystick->vertical_value;
    pthread_mutex_unlock(&joystick->lock);

    return value;
}

bool Joystick_is_up(Joystick *joystick)
{
    // Ensure joystick is initialized.
    assert(joystick != NULL);

    float value = Joystick_read_vertical(joystick);
    return value > JOYSTICK_SENSITIVITY;
}

bool Joystick_is_down(Joystick *joystick)
{
    // Ensure joystick is initialized.
    assert(joystick != NULL);

    float value = Joystick_read_vertical(joystick);
    return value < -JOYSTICK_SENSITIVITY;
}

bool Joystick_is_left(Joystick *joystick)
{
    // Ensure joystick is initialized.
    assert(joystick != NULL);

    float value = Joystick_read_horizontal(joystick);
    return value < -JOYSTICK_SENSITIVITY;
}

bool Joystick_is_right(Joystick *joystick)
{
    // Ensure joystick is initialized.
    assert(joystick != NULL);

    float value = Joystick_read_horizontal(joystick);
    return value > JOYSTICK_SENSITIVITY;
}

void Joystick_cleanup(Joystick *joystick)
{
    // Free any memory, close files, ...
    printf("Joystick - Cleanup\n");

    assert(is_initialized);

    // Ensure joystick is available before any operation.
    assert(joystick != NULL);   

    // Close thread, file, destroy lock and free allocated heap memory.
    joystick->stop_thread = true;
    pthread_join(joystick->read_thread, NULL);

    close(joystick->i2c_file_desc);
    pthread_mutex_destroy(&joystick->lock);
    free(joystick);

    is_initialized = false;
}