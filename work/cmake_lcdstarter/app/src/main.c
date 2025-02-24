// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include "badmath.h"
#include "hal/button.h"
#include "draw_stuff.h"

void foo() {
    int data[3];    
    for (int i = 0; i <= 3; i++) {
        data[i] = 10;
        printf("Value: %d\n", data[i]);
    }
}

int main()
{
    printf("Hello world with LCD!\n");

    // Initialize all modules; HAL modules first
    button_init();
    badmath_init();
    DrawStuff_init();

    // Main program logic:
    #if 0
    for (int i = 0; i < 10; i++) {
        printf("  -> Reading button time %d = %d\n", i, button_is_button_pressed());
    }

    for (int i = 0; i <= 35; i++) {
        int ans = badmath_factorial(i);
        printf("%4d! = %6d\n", i, ans);
    }
    #endif

    for (int i = 0; i < 100; i++) {
        char buff[1024];
        snprintf(buff, 1024, "Hello count: %3d", i);
        DrawStuff_updateScreen(buff);
    }
    

    // Cleanup all modules (HAL modules last)
    DrawStuff_cleanup();
    badmath_cleanup();
    button_cleanup();

    printf("!!! DONE !!!\n"); 

    // Some bad code to try out and see what shows up.
    #if 0
        // Test your linting setup
        //   - You should see a warning underline in VS Code
        //   - You should see compile-time errors when building (-Wall -Werror)
        // (Linting using clang-tidy; see )
        int x = 0;
        if (x = 10) {
        }
    #endif
    #if 0
        // Demonstrate -fsanitize=address (enabled in the root CMakeFiles.txt)
        // Compile and run this code. Should see warning at compile time; error at runtime.
        foo();

    #endif
}