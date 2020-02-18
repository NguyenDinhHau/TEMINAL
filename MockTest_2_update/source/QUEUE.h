#ifndef _QUEUE_H_
#define _QUEUE_H_

#define DATA_SIZE   255
#define QUEUE_SIZE  4

typedef struct
{
    uint8_t data[DATA_SIZE];
}queue_element_str_t;

typedef struct
{
    uint8_t read;
    uint8_t write;
    uint8_t count;
    queue_element_str_t a[QUEUE_SIZE];
} queue_str_t;

void Queue_Init(void);
bool Queue_IsFull(void);
bool Queue_IsEmpty(void);
void Queue_GetFreeSpaceData(uint8_t ** outBuff);
void Queue_Push(void);
void Queue_PopData(uint8_t ** outBuff);
void Queue_Pop(void);

#endif