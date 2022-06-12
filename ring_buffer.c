#include <stdio.h>
#include <stdint.h>
#include "ring_buffer.h"


void debugRingBuffer(RingBuffer* ringBuffer);

 int main_() // don't use this as entry point
//int main() // use this as entry point (for debugging purposes)
{
    RingBuffer buf1, buf2;
    debugRingBuffer(&buf1);
    debugRingBuffer(&buf2);
    return 0;
}

// int main()
void debugRingBuffer(RingBuffer* ringBuffer)
{
    RingBuffer_Init(ringBuffer);

    // uint8_t data[3] = { 1, 2, 3 };

    // RingBuffer_Write(ringBuffer, data, 3);

    // uint8_t out2[3];
    // RingBuffer_Read(ringBuffer, out2, 3);

    // printf("%d %d %d\n", out2[0], out2[1], out2[2]);

    // return 0;

    uint8_t arr[RING_BUFFER_SIZE];
    for (uint8_t i = 0; i < RING_BUFFER_SIZE ; i++)
    {
        arr[i] = i;
    }

    RingBuffer_Write(ringBuffer, arr, RING_BUFFER_SIZE);
    // printf("got here :)\n");

    // return 0;
    // printf("%d\n", RingBuffer_IsEmpty());
    // return 0;
    uint8_t out[RING_BUFFER_SIZE];
    RingBuffer_Read(ringBuffer, out, RING_BUFFER_SIZE);
    for (int i = 0; i < RING_BUFFER_SIZE ; i++)
    {
        printf("%u ", out[i]);
    }
    printf("\n");
    uint8_t arr5[RING_BUFFER_SIZE];
    for (uint8_t i = 0; i < RING_BUFFER_SIZE ; i++)
    {
        arr5[i] = i;
    }

    RingBuffer_Write(ringBuffer, arr5, RING_BUFFER_SIZE);

    printf("After filling once\n");

    uint8_t out5[RING_BUFFER_SIZE];
    RingBuffer_Read(ringBuffer, out5, RING_BUFFER_SIZE);
    for (int i = 0; i < RING_BUFFER_SIZE ; i++)
    {
        printf("%u ", out5[i]);
    }
    printf("\n");
}

void RingBuffer_Init(RingBuffer* ringBuffer)
{
   ringBuffer->headP = ringBuffer->buf; 
   ringBuffer->tailP = ringBuffer->buf; 
   ringBuffer->size = RING_BUFFER_SIZE;
   ringBuffer->elementCount = 0;
   ringBuffer->endP = ringBuffer->buf + (ringBuffer->size - 1);
}

int RingBuffer_IsEmpty(RingBuffer* ringBuffer)
{
    return !ringBuffer->elementCount;
}

int RingBuffer_IsFull(RingBuffer* ringBuffer)
{
    return ringBuffer->elementCount == ringBuffer->size;
}

int RingBuffer_FreeSpace(RingBuffer* ringBuffer)
{
    return ringBuffer->size - ringBuffer->elementCount;
}

int RingBuffer_Write(RingBuffer* ringBuffer, uint8_t* data, uint8_t dataSize)
{
    if (RingBuffer_FreeSpace(ringBuffer) < dataSize)
    {
        printf("Not enough space in ringbuffer!\n");
        return 0;
    }

    for (int i = 0; i < dataSize; i++)
    {
        *(ringBuffer->headP) = *(data++);

        if (ringBuffer->headP == ringBuffer->endP)
        {
            ringBuffer->headP = ringBuffer->buf;
        }
        else
        {
            ringBuffer->headP++;
        }

        ringBuffer->elementCount++;
    }

    return 1;
}

int RingBuffer_Read(RingBuffer* ringBuffer, uint8_t* data, uint8_t dataSize)
{
    size_t count = 0;

    while (!RingBuffer_IsEmpty(ringBuffer) && dataSize > 0)
    {
        *(data++) = *(ringBuffer->tailP);

        if (ringBuffer->tailP == ringBuffer->endP)
        {
            ringBuffer->tailP = ringBuffer->buf;
        }
        else
        {
            ringBuffer->tailP++;
        }

        count++;
        dataSize--;

        ringBuffer->elementCount--;
    }

    return count;
}

int RingBuffer_RemoveFromHead(RingBuffer* ringBuffer, uint8_t dataSize)
{
  if (RingBuffer_IsEmpty(ringBuffer))
  {
    return 0;
  }

  int count = 0;

  while (dataSize)
  {
    if (ringBuffer->headP == ringBuffer->buf)
    {
      ringBuffer->headP = ringBuffer->endP;
    }
    else if (ringBuffer->headP == ringBuffer->tailP)
    {
      return count;
    }

    ringBuffer->headP--;
    ringBuffer->elementCount--;

    count++;
    dataSize--;
  }

  return count;
}





















