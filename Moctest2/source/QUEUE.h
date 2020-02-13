#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>
#define DATA_SIZE   100
#define QUEUE_SIZE  4

typedef struct
{
    uint8_t data[DATA_SIZE];
} queue_data_str_t;

typedef struct
{
    uint8_t read;
    uint8_t write;
    uint8_t count;
    queue_data_str_t a[QUEUE_SIZE];
} queue_str_t;

bool Queue_isFull(void);
bool Queue_isEmpty(void);
void QueueInit(void);
void queue_push(void);
void Pushdata(uint8_t **outBuff);
void PopData(uint8_t **outBuff);
void queue_pop(void);

#endif