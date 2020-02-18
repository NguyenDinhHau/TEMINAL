#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include "parse.h"

static uint16_t s_error = 0;

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

static uint8_t Srec_ConvertTwoCharToByte(uint8_t *data)
{
    uint8_t temp = 0;

    temp  = (Srec_ConvertCharToHex(*data)<<4u);
    temp |= (Srec_ConvertCharToHex(*(data+1)));

    return temp;
}

srec_parser_status_enum_t Srec_Parse(uint8_t *data, addData_str_t *outPut_Data)
{
    uint32_t checkSum = 0;
    uint8_t byteCount = 0;
    uint8_t addlength = 0;
    srec_parser_status_enum_t status;
    uint8_t type = -1;
    uint8_t index = 0;
    uint8_t index_data = 0;
    uint8_t temp = 0;

    if(data[0] == 'S')
    {
        type = Srec_ConvertCharToHex(data[1]);
    }
    else
    {
        status = ERROR_UNKNOWN;
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
      checkSum = 0;
      index_data = 0;
      outPut_Data->add = 0;
      outPut_Data->dataLengh = 0;
      byteCount   = (Srec_ConvertTwoCharToByte(&data[2]));
      checkSum    += byteCount;
      outPut_Data->dataLengh = byteCount - (addlength/2) - 1u;
      for(index = 4; index <= strlen((char *)data)-4; index+=2)
      {
       if(index < (addlength + 4))
       {
           outPut_Data->add <<=8u;
           temp = Srec_ConvertTwoCharToByte(&data[index]);
           outPut_Data->add |= temp;
           checkSum += temp;
       }
       else if(index >= (addlength + 4))
       {
           temp = Srec_ConvertTwoCharToByte(&data[index]);
           outPut_Data->data[index_data] = temp;
           checkSum    += temp;
           index_data ++;
       }
      }
      checkSum += Srec_ConvertTwoCharToByte(&data[strlen((char *)data)-3]);

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