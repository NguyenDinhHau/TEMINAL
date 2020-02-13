#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>
#define DATA_SIZE   100
#define QUEUE_SIZE  10

typedef struct
{
    char data[DATA_SIZE];
} data_str_t;

typedef struct
{
    uint8_t front;
    uint8_t rear;
    uint8_t count;
    data_str_t queue_data[QUEUE_SIZE];
} queue_str_t;
void QueueInit();
bool isEmpty(void);
bool isFull(void);
void Pushdata(char data);
data_str_t * PopData();
#endif