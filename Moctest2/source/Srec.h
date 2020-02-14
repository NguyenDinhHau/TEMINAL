#ifndef _SREC_H
#define _SREC_H

typedef struct {
    uint32_t add;
    uint8_t data[50];
    uint8_t dataLengh;
}addData_str_t;

#define START 1
#define START_DATA 2
#define END_DATA 3
#define FIRST_DATA 4
#define DATA_LINE 5
#define CHECKSUM_ERROR 6

uint8_t CopyData(uint8_t *data, addData_str_t *copyData);

#endif
