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

#include "hal/light_sensor.h"

#include <pthread.h>

// Device bus and address
#define I2CDRV_LINUX_BUS "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x48

// Register in TLA2024
#define REG_CONFIGURATION 0x01
#define REG_DATA 0x00

// Configuration reg contents for continuously sampling different channels
#define TLA2024_CHANNEL_CONF_LIGHT 0x83E2

#define I2C_DELAY 10000

pthread_t read_thread;
static int i2c_file_desc;
static bool stop_thread = false;
pthread_mutex_t lock_thread;

static uint16_t light_value;

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
// Reference: https://stats.stackexchange.com/questions/70801/how-to-normalize-data-to-0-1-range
// static float normalize_value(int value, int min, int max, int default_value)
// {
//     return 2.0f * (value - default_value) / (max - min);
// }

// Read raw data and normalize value in a pthread using mutex lock/unlock.
static void* read_thread_func(void *arg)
{
    (void)arg;
    // Ensure the module is initialized.
    assert(is_initialized);
    
    while (!stop_thread) {
        // Read Light Sensor (Channel 2)
        write_i2c_reg16(i2c_file_desc, REG_CONFIGURATION, TLA2024_CHANNEL_CONF_LIGHT);
        usleep(I2C_DELAY);
        
        pthread_mutex_lock(&lock_thread);
        {
            uint16_t raw_light = read_i2c_reg16(i2c_file_desc, REG_DATA);
            light_value = ((raw_light & 0x0FF) << 8) | ((raw_light & 0xF00) >> 8);
            light_value = light_value >> 4;
        }
        pthread_mutex_unlock(&lock_thread);
    }

    return NULL;
}

// Initialize a Light sensor
void LightSensor_init(void)
{
    printf("Joystick - Initializing\n");
    assert(!is_initialized);

    i2c_file_desc = init_i2c_bus(I2CDRV_LINUX_BUS, I2C_DEVICE_ADDRESS);
    stop_thread = false;
    pthread_mutex_init(&lock_thread, NULL);

    // Create a read thread to handle light reading value.
    // Make sure the thread is created without issues.
    if (pthread_create(&read_thread, NULL, read_thread_func, NULL) != 0) {
        perror("LightSensor_init: Failed to create a read thread.");
        exit(EXIT_FAILURE);
    }

    is_initialized = true;
    srand(time(0));
}

float LightSensor_read_light()
{
    float value;
    pthread_mutex_lock(&lock_thread);
    {
        value = light_value;
    }
    pthread_mutex_unlock(&lock_thread);
    return value;
}

void LightSensor_cleanup()
{
    // Free any memory, close files.
    printf("LightSensor - Cleanup\n");
    assert(is_initialized);   
    is_initialized = false;
    
    // Close thread, file, destroy lock.
    stop_thread = true;
    
    pthread_join(read_thread, NULL);

    close(i2c_file_desc);
    pthread_mutex_destroy(&lock_thread);
    printf("LightSensor - Done.\n");
}
