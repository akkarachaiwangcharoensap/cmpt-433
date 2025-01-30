#include <stdio.h>
#include <stdbool.h>
#include "hal/led.h"
#include "hal/joystick.h"

// Device bus and address
#define I2CDRV_LINUX_BUS "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x48

// Register in TLA2024
#define REG_CONFIGURATION 0x01
#define REG_DATA 0x00

// Configuration reg contents for continuously sampling different channels
// #define TLA2024_CHANNEL_CONF_0 0x83C2

int main ()
{
    printf("Hello embedded world, from Aki!\n");

    Joystick *joystick = Joystick_init();

    if (joystick == NULL) {
        perror("main: Failed to initialize a joystick\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // float vertical_value = Joystick_read_vertical(joystick);
        // float horizontal_value = Joystick_read_horizontal(joystick);
        bool up = Joystick_is_up(joystick);
        bool down = Joystick_is_down(joystick);
        bool left = Joystick_is_left(joystick);
        bool right = Joystick_is_right(joystick);
        
        printf("up: %d\n", up);
        printf("down: %d\n", down);
        printf("left: %d\n", left);
        printf("right: %d\n", right);
        
        // fflush(stdout);

        sleep(1);
    }

    Joystick_cleanup(joystick);

    // LED *led_red = led_init(LED_RED);
    // if (led_red == NULL) {
    //     perror("main: Failed to initialize red LED\n");
    //     exit(EXIT_FAILURE);
    // }
    
    // led_turn_on(led_red);

    // printf("Red LED is %d\n", led_is_on(led_red));

    // led_cleanup(led_red);

    // int i2c_file_desc = init_i2c_bus(I2CDRV_LINUX_BUS, I2C_DEVICE_ADDRESS);

    // Select the channel
    // write_i2c_reg16(i2c_file_desc, REG_CONFIGURATION, TLA2024_CHANNEL_CONF_0);

    // while (true) {
    //     // Read the register
    //     uint16_t raw_read = read_i2c_reg16(i2c_file_desc, REG_DATA);
    //     printf("Raw reading: 0x%04x\n", raw_read);

    //     sleep(1);
    // }

    // Cleanup I2C access
    // close(i2c_file_desc);
    return 0;
}