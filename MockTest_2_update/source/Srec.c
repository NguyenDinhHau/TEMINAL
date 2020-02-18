/*******************************************************************************
 * Includes
 ******************************************************************************/
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include "parse.h"
/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint16_t s_error = 0;
/* this function to convert a char to hexa */
static uint8_t Srec_ConvertCharToHex(uint8_t data)
{
    uint8_t temp = 0;

    if(data >= '0' && data <= '9')
    {
        temp = (data - '0');
    }
    else  if(data >= 'A' && data <= 'F')
    {
         temp = (data - 'A' + 10u);
    }
    else
    {
        s_error++;
    }

    return temp;
}
/* this function to convert two char to a byte */
static uint8_t Srec_ConvertTwoCharToByte(uint8_t *data)
{
    uint8_t temp = 0;

    temp  = (Srec_ConvertCharToHex(*data)<<4u);
    temp |= (Srec_ConvertCharToHex(*(data+1)));

    return temp;
}
/* this function to parse address and data from buff to outputdata */
srec_parser_status_enum_t Srec_Parse(uint8_t *data, addData_str_t *outPutData)
{
    uint32_t checkSum = 0;
    uint8_t byteCount = 0;
    uint8_t addressLength = 0;
    srec_parser_status_enum_t status;
    uint8_t type = -1;
    uint8_t index = 0;
    uint8_t index_data = 0;
    uint8_t temp = 0;

    if(data[0] == 'S')
    {   /* get type */
        type = Srec_ConvertCharToHex(data[1]);
    }
    else
    {
        status = ERROR_UNKNOWN;
    }
    /* check type */
    switch (type)
    {
        case 0:
            addressLength   = 2u;
            status          = START;
            break;
        case 1:
        case 2:
        case 3:
            status          = START_DATA;
            addressLength   = (type + 1u)*2;
            break;
        case 4:
            break;
        case 5:
        case 6:
            addressLength   = (type - 3u)*2;
            status          = DATA_LINE_COUNT;
            break;
        case 7:
        case 8:
        case 9:
            status          = END_DATA;
            addressLength   = (11u - type)*2;
            break;
        default:
            status          = ERROR_UNKNOWN;
            break;
    }
    checkSum = 0;
    index_data = 0;
    outPutData->add = 0;
    outPutData->dataLengh = 0;
    /* calculate bytecoun*/
    byteCount   = (Srec_ConvertTwoCharToByte(&data[2]));
    checkSum    += byteCount;
    outPutData->dataLengh = byteCount - (addressLength/2) - 1u;
    /* Parse address and data from dataBuff to output */
    for(index = 4; index <= strlen((char *)data)-4; index+=2)
    {  /* Parse address */
       if(index < (addressLength + 4))
       {
           outPutData->add <<=8u;
           temp = Srec_ConvertTwoCharToByte(&data[index]);
           outPutData->add |= temp;
           checkSum += temp;
       }
       /* Parse data */
       else if(index >= (addressLength + 4))
       {
           temp = Srec_ConvertTwoCharToByte(&data[index]);
           outPutData->data[index_data] = temp;
           checkSum    += temp;
           index_data ++;
       }
    }
    checkSum += Srec_ConvertTwoCharToByte(&data[strlen((char *)data)-3]);
    /* Checksum */
    if(0xFF != (uint8_t)checkSum)
    {
        status = ERROR_CHECKSUM;
    }
    else if(s_error != 0)
    {
        status = ERROR_UNKNOWN;
    }

    return status;
}
