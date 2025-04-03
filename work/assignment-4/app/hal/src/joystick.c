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

#include <pthread.h>

#include "hal/gpio.h"
#include "hal/joystick.h"

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

// gpiofind GPIO5
// >> gpiochip2 15
#define GPIO_BUTTON_CHIP                    GPIO_CHIP_2
#define GPIO_BUTTON_NUMBER                  15

static pthread_t read_thread;
static pthread_t button_thread;

static int i2c_file_desc;
static bool stop_thread;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static float vertical_value;
static float horizontal_value;

static bool is_button_down = false;
static struct GpioLine *button_line;

// Allow module to ensure it has been initialized (once!)
static bool is_initialized = false;

static JoystickCallback on_pressed_up_callback = NULL;
static JoystickCallback on_pressed_down_callback = NULL;

static JoystickCallback on_button_push_down_callback = NULL;


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

void Joystick_register_pressed_up_callback(JoystickCallback callback)
{
    on_pressed_up_callback = callback;
}

void Joystick_register_pressed_down_callback(JoystickCallback callback)
{
    on_pressed_down_callback = callback;
}

void Joystick_register_push_button_down_callback(JoystickCallback callback)
{
    on_button_push_down_callback = callback;   
}

// Normalize the value, return -1 to 1 range.
// Reference: https://stats.stackexchange.com/questions/70801/how-to-normalize-data-to-0-1-range
static float normalize_value(int value, int min, int max, int default_value)
{
    return 2.0f * (value - default_value) / (max - min);
}

// Read raw data and normalize value in a pthread using mutex lock/unlock.
static void* read_func(void* arg)
{
    (void)arg;

    while (!stop_thread) {
        write_i2c_reg16(i2c_file_desc, REG_CONFIGURATION, TLA2024_CHANNEL_CONF_Y);
        // Delay to ensure ADC can update the data.
        usleep(I2C_UPDATE_DELAY);

        uint16_t raw_read_vertical = read_i2c_reg16(i2c_file_desc, REG_DATA);
        uint16_t raw_vertical_value = ((raw_read_vertical & 0x0FF) << 8) | ((raw_read_vertical & 0xF00) >> 8);
        raw_vertical_value = raw_vertical_value >> 4;

        // -1 corrects the direction: up is positive, down is negative.
        pthread_mutex_lock(&lock);
        {
            vertical_value = -1 * normalize_value(raw_vertical_value, MIN_JOYSTICK_VERTICAL_VALUE, MAX_JOYSTICK_VERTICAL_VALUE, DEFAULT_JOYSTICK_VERTICAL_VALUE);
        }
        pthread_mutex_unlock(&lock);

        // Read X Channel
        write_i2c_reg16(i2c_file_desc, REG_CONFIGURATION, TLA2024_CHANNEL_CONF_X);

        // Delay to ensure ADC can update the data.
        usleep(I2C_UPDATE_DELAY);

        uint16_t raw_read_horizontal = read_i2c_reg16(i2c_file_desc, REG_DATA);
        uint16_t raw_horizontal_value = ((raw_read_horizontal & 0x0FF) << 8) | ((raw_read_horizontal & 0xF00) >> 8);
        raw_horizontal_value = raw_horizontal_value >> 4;

        pthread_mutex_lock(&lock);
        {
            // direction: right is positive, left is negative.
            horizontal_value = normalize_value(raw_horizontal_value, MIN_JOYSTICK_HORIZONTAL_VALUE, MAX_JOYSTICK_HORIZONTAL_VALUE, DEFAULT_JOYSTICK_HORIZONTAL_VALUE);
        }
        pthread_mutex_unlock(&lock);

        // Reading button value.
        int value = gpiod_line_get_value((struct gpiod_line *)button_line);
        if (value < 0) {
            perror("Joystick read thread: Failed to read button state");
        } else {
            pthread_mutex_lock(&lock);
            {
                // Assuming an active low button (0 = pressed)
                is_button_down = (value == 0);
            }
            pthread_mutex_unlock(&lock);
        }

        // Trigger callbacks based on vertical direction.
        if (Joystick_is_down() && on_pressed_down_callback != NULL)
            on_pressed_down_callback();
            
        if (Joystick_is_up() && on_pressed_up_callback != NULL)
            on_pressed_up_callback();

        // Read ADC every I2C_READ_DELAY interval.
        usleep(I2C_READ_DELAY);
    }

    return NULL;
}

static void* button_listener_func(void *arg)
{
    (void)arg;
    while (!stop_thread) {
        struct gpiod_line_bulk bulkEvents;
        int numEvents = Gpio_waitForLineChange(button_line, &bulkEvents);
        if (numEvents < 0) {
            perror("Joystick button thread: Error waiting for line change");
            continue;
        }

        for (int i = 0; i < numEvents; i++) {
            struct gpiod_line *line_handle = gpiod_line_bulk_get_line(&bulkEvents, i);
            struct gpiod_line_event event;
            if (gpiod_line_event_read(line_handle, &event) == -1) {
                perror("Joystick button thread: Error reading event");
                continue;
            }
            // Falling edge: a press, rising: not pressed.
            bool isRising = (event.event_type == GPIOD_LINE_EVENT_RISING_EDGE);
            pthread_mutex_lock(&lock);
            is_button_down = !isRising;
            pthread_mutex_unlock(&lock);
        }

        // Trigger callbacks based on vertical direction.
        if (Joystick_is_push_button_down() && on_button_push_down_callback != NULL)
            on_button_push_down_callback();
    }

    return NULL;
}

// Initialize a Joystick
void Joystick_init()
{
    printf("Joystick - Initializing\n");
    assert(!is_initialized);

    i2c_file_desc = init_i2c_bus(I2CDRV_LINUX_BUS, I2C_DEVICE_ADDRESS);
    stop_thread = false;
    pthread_mutex_init(&lock, NULL);

    // Create a read thread to handle reading joystick value.
    // Make sure the thread is created without issues.
    if (pthread_create(&read_thread, NULL, read_func, NULL) != 0) {
        perror("Joystick_init: Failed to create a read thread.");
        exit(EXIT_FAILURE);
    }

    button_line = Gpio_openForEvents(GPIO_BUTTON_CHIP, GPIO_BUTTON_NUMBER);
    if (!button_line) {
        perror("Joystick_init: Failed to open button GPIO line");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&button_thread, NULL, button_listener_func, NULL) != 0) {
        perror("Joystick_init: Failed to create button thread.");
        exit(EXIT_FAILURE);
    }

    is_initialized = true;
    srand(time(0));
}

float Joystick_read_horizontal(void)
{
    pthread_mutex_lock(&lock);
    float value = horizontal_value;
    pthread_mutex_unlock(&lock);

    return value;
}

float Joystick_read_vertical(void)
{
    pthread_mutex_lock(&lock);
    float value = vertical_value;
    pthread_mutex_unlock(&lock);

    return value;
}

bool Joystick_is_up(void) 
{
    return (Joystick_read_vertical() > JOYSTICK_SENSITIVITY);
}

bool Joystick_is_down(void) 
{
    return (Joystick_read_vertical() < -JOYSTICK_SENSITIVITY);
}

bool Joystick_is_left(void) 
{
    return (Joystick_read_horizontal() < -JOYSTICK_SENSITIVITY);
}

bool Joystick_is_right(void) 
{
    return (Joystick_read_horizontal() > JOYSTICK_SENSITIVITY);
}

bool Joystick_is_push_button_down(void) 
{
    pthread_mutex_lock(&lock);
    bool down = is_button_down;
    pthread_mutex_unlock(&lock);
    return down;
}

void Joystick_cleanup(void)
{
    // Free any memory, close files, ...
    printf("Joystick - Cleanup\n");
    assert(is_initialized);

    // Close thread, file, destroy lock and free allocated heap memory.
    stop_thread = true;

    pthread_cancel(read_thread);
    pthread_join(read_thread, NULL);
    
    pthread_cancel(button_thread);
    pthread_join(button_thread, NULL);
    
    pthread_mutex_destroy(&lock);

    Gpio_close(button_line);
    close(i2c_file_desc);

    is_initialized = false;
    printf("Joystick - Done.\n");
}
