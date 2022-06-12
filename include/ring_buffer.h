#pragma once
#include <stdint.h>
#include <stdio.h>

#define RING_BUFFER_SIZE 64

typedef struct RingBuffer {
    uint8_t buf[RING_BUFFER_SIZE];
    uint8_t* tailP;
    uint8_t* headP;
    uint8_t* endP;
    size_t elementCount;
    size_t size;
} RingBuffer;

void debugRingBuffer(RingBuffer* ringBuffer);
void RingBuffer_Init(RingBuffer* ringBuffer);
int RingBuffer_IsEmpty(RingBuffer* ringBuffer);
int RingBuffer_IsFull(RingBuffer* ringBuffer);
int RingBuffer_FreeSpace(RingBuffer* ringBuffer);
int RingBuffer_Write(RingBuffer* ringBuffer, uint8_t* data, uint8_t dataSize);
int RingBuffer_Read(RingBuffer* ringBuffer, uint8_t* data, uint8_t dataSize);
int RingBuffer_RemoveFromHead(RingBuffer* ringBuffer, uint8_t dataSize);

