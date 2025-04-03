#ifndef _SHARED_DATA_STRUCT_H_
#define _SHARED_DATA_STRUCT_H_

#include <stdbool.h>
#include <stdint.h>

// R5 Shared Memory Note
// - It seems that using a struct for the ATCM memory does not work 
//   (hangs when accessing memory via a struct pointer).
// - Therefore, using an array.

#define MSG_OFFSET 0
#define MSG_SIZE   32
#define NORMALIZED_X_ROTATION_OFFSET (MSG_OFFSET + sizeof(float))
#define NORMALIZED_Y_ROTATION_OFFSET (NORMALIZED_X_ROTATION_OFFSET + sizeof(float))
#define X_TARGET_OFFSET (NORMALIZED_Y_ROTATION_OFFSET + sizeof(float))
#define Y_TARGET_OFFSET (X_TARGET_OFFSET + sizeof(float))
#define FIRING_STATUS_OFFSET (Y_TARGET_OFFSET + sizeof(uint8_t))
#define FIRING_IN_RANGE_OFFSET (FIRING_STATUS_OFFSET + sizeof(uint8_t))
#define TERMINATE_PROGRAM_FLAG_OFFSET (FIRING_IN_RANGE_OFFSET + sizeof(uint8_t))

#define MEM_UINT8(addr) *(uint8_t*)(addr)
#define MEM_UINT32(addr) *(uint32_t*)(addr)
#define MEM_FLOAT(addr) (*(volatile float*)(addr))

#endif