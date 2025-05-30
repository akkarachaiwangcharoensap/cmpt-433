#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>

#include <string.h>

#include "sharedDataLayout.h"

// General R5 Memomry Sharing Routine
// ----------------------------------------------------------------
#define ATCM_ADDR     0x79000000  // MCU ATCM (p59 TRM)
#define BTCM_ADDR     0x79020000  // MCU BTCM (p59 TRM)
#define MEM_LENGTH    0x8000

// Return the address of the base address of the ATCM memory region for the R5-MCU
volatile void* getR5MmapAddr(void)
{
    // Access /dev/mem to gain access to physical memory (for memory-mapped devices/specialmemory)
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        perror("ERROR: could not open /dev/mem; Did you run with sudo?");
        exit(EXIT_FAILURE);
    }

    // Inside main memory (fd), access the part at offset BTCM_ADDR:
    // (Get points to start of R5 memory after it's memory mapped)
    volatile void* pR5Base = mmap(0, MEM_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, BTCM_ADDR);
    if (pR5Base == MAP_FAILED) {
        perror("ERROR: could not map memory");
        exit(EXIT_FAILURE);
    }
    close(fd);

    return pR5Base;
}

void freeR5MmapAddr(volatile void* pR5Base)
{
    if (munmap((void*) pR5Base, MEM_LENGTH)) {
        perror("R5 munmap failed");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    printf("Sharing memory with R5\n");
    // printf("  LED should change speed every 5s.\n");
    // printf("  Press the button to see its state here.\n");

    // Get access to shared memory for my uses
    volatile void *pR5Base = getR5MmapAddr();

	printf("Contents of memory :\n");
	for (int i = 0; i < 50; i++) {
		volatile char* addr = pR5Base + i;
        char val = *addr;
        printf("Offset %d = %3d (char '%c')\n", i, val, val);
	}

    // Print out the mem contents:
    printf("From the R5, memory hold:\n");
    // Drive it
    for (int i = 0; true; i++) {
        // Set LED timing
        // MEM_UINT32(pR5Base + LED_DELAY_MS_OFFSET) = (i % 10 < 5) ? 100 : 250;
        printf("    %20s: %f\n", "X_MEASURE_OFFSET:", MEM_FLOAT(pR5Base + X_MEASURE_OFFSET));
        printf("    %20s: %f\n", "Y_MEASURE_OFFSET:", MEM_FLOAT(pR5Base + Y_MEASURE_OFFSET));

        // Timing
        sleep(1);
    }

    // Cleanup
    freeR5MmapAddr(pR5Base);
}