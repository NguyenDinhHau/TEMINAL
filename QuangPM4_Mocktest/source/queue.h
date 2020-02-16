#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>
/********************************************
 * Definitions
 *******************************************/
#define MAX_QUEUE_SIZE  2

typedef struct
{
    char data[100];
}queue_data_t;

typedef struct
{
    uint8_t read;
    uint8_t write;
    uint8_t size;
    queue_data_t index[MAX_QUEUE_SIZE];
}queue_t;

void queue_init(void);

bool queue_isFull(void);

bool queue_check_Empty(void);

void queue_push(void);

void queue_Pushdata(char **data_push);

void queue_POP_Data(char **data_pop);

void queue_pop(void);


#endif
