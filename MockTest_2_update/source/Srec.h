#ifndef _SREC_H
#define _SREC_H

typedef struct {
    uint32_t add;
    uint8_t data[50];
    uint8_t dataLengh;
}addData_str_t;

typedef enum
{
    END_DATA                =   8,
    ERROR_CHECKSUM          =   7,
    ERROR_FIRST_CHARACTER   =   6,
    ERROR_DATA_TYPE         =   5,
    START_DATA              =   4,
    START                   =   3,
    DATA_LINE_COUNT         =   2
} srec_parser_status_enum;

uint8_t Srec_Parse(uint8_t *data, addData_str_t *copyData);

#endif
