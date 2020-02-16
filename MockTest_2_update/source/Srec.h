#ifndef _SREC_H
#define _SREC_H

typedef struct {
    uint32_t add;
    uint8_t data[255];
    uint8_t dataLengh;
}addData_str_t;

typedef enum
{
    END_DATA                =   8,
    ERROR_CHECKSUM          =   7,
    ERROR_FIRST_CHARACTER   =   6,
    START_DATA              =   5,
    START                   =   4,
    DATA_LINE_COUNT         =   3
} srec_parser_status_enum;

uint8_t Srec_Parse(uint8_t *data, addData_str_t *copyData);

#endif
