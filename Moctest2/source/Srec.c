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

uint8_t CopyData(uint8_t *data, addData_str_t *copyData  )
{
    uint32_t checkSum = 0;
    uint8_t byteCount = 0;
    uint8_t addlength = 0;
    uint8_t status = 0;
    uint8_t type = -1;
    uint8_t offset = 0;
    uint8_t index = 0;
    uint8_t temp = 0;
    
    if(data[0] == 'S')
    {
        type = ConvertToHex(data[1]);
    }
    else
    {
        status = FIRST_DATA;
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
            addlength   = (type + 1u);
            break;
        case 4:
            break;
        case 5:
        case 6:
            addlength   = (type - 3u);
            status      = DATA_LINE;
            break;
        case 7:
        case 8:
        case 9:
            status      = END_DATA;
            addlength   = (11u - type);
            break;

    }
    byteCount   = (ConvertToByte(data + 2u));
    checkSum    += byteCount;
    copyData->data_lengh = byteCount - addlength - 1u;
    offset   = 4u;
    for (index = 0 ; index < addlength ; index++)
    {
        copyData->add <<= 8u;
        temp = ConvertToByte(data + offset);
        copyData->add |= temp;
        checkSum    += temp;
        offset      += 2u;
    }
    for (index = 0 ; index < copyData->data_lengh ; index++)
    {
        temp = ConvertToByte(data + offset);
        copyData->data[index] = temp;
        checkSum    += temp;
        offset      += 2u;
    }
    checkSum += ConvertToByte(data + offset);
    if(0xFF != checkSum)
    {
        status = CHECKSUM_ERROR;
    }

    return status;
}

