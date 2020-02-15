#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include "Srec.h"

static uint8_t ConvertToHex(uint8_t data)
{
    uint8_t temp = 0;

    if(data >= '0' && data <= '9')
    {
        temp = (data - '0');
    }
    else
    {
        if(data >= 'A' && data <= 'F')
        {
            temp = (data - 'A' + 10u);
        }
    }

    return temp;
}

static uint8_t ConvertToByte(uint8_t *data)
{
    uint8_t temp = 0;

    temp  = (ConvertToHex(*data)<<4u);
    temp |= (ConvertToHex(*(data+1)));

    return temp;
}

uint8_t Srec_Parse(uint8_t *data, addData_str_t *copyData)
{
    uint32_t checkSum = 0;
    uint8_t byteCount = 0;
    uint8_t addlength = 0;
    uint8_t status = 0;
    uint8_t type = -1;
    uint8_t index = 0;
    uint8_t index_data = 0;
    uint8_t temp = 0;
    
    if(data[0] == 'S')
    {
        type = ConvertToHex(data[1]);
    }
    else
    {
        status = ERROR_FIRST_CHARACTER;
    }
    switch (type)
    {
        case 0:
            addlength   = 2u;
            status      = START;
            break;
        case 1:
        case 2:
        case 3:
            status      = START_DATA;
            addlength   = (type + 1u)*2;
            break;
        case 4:
            break;
        case 5:
        case 6:
            addlength   = (type - 3u)*2;
            status      = DATA_LINE_COUNT;
            break;
        case 7:
        case 8:
        case 9:
            status      = END_DATA;
            addlength   = (11u - type)*2;
            break;

    }
    byteCount   = (ConvertToByte(&data[2]));
    checkSum    += byteCount;
    copyData->dataLengh = byteCount - (addlength/2) - 1u;
    index_data = 0;
    copyData->add = 0;

    for(index = 4; index <= strlen((char *)data)-4; index+=2)
    {
     if(index < (addlength + 4))
     {
         copyData->add <<=8u;
         temp = ConvertToByte(&data[index]);
         copyData->add |= temp;
         checkSum += temp;
     }
     else if(index >= (addlength + 4))
     {
         temp = ConvertToByte(&data[index]);
         copyData->data[index_data] = temp;
         checkSum    += temp;
         index_data ++;
     }
    }
    checkSum += ConvertToByte(&data[strlen((char *)data)-3]);

    if(0xFF != (uint8_t)checkSum)
    {
        status = ERROR_CHECKSUM;
    }

    return status;
}