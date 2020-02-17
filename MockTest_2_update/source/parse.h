#ifndef _PARSE_H
#define _PARSE_H

typedef struct {
    uint32_t add;
    uint8_t data[255];
    uint8_t dataLengh;
}addData_str_t;

typedef enum
{
    END_DATA                =  0x00,
    ERROR_CHECKSUM,
    ERROR_UNKNOWN,
    START_DATA,
    START,
    DATA_LINE_COUNT
} srec_parser_status_enum_t;

srec_parser_status_enum_t Srec_Parse(uint8_t *data, addData_str_t *outPut_Data);

#endif
