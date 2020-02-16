#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>

static bool checkHexa(uint8_t *data);
static uint32_t sumOfAdDa(uint8_t *data);
static bool checkSumData(uint8_t *data);
static bool checkByteCount(uint8_t *data);
static bool checkFirstData(uint8_t *data);
static bool checkNumberDe(uint8_t a);
static bool checkNumberHexa(uint8_t a);
uint8_t convertNumber(uint8_t num1, uint8_t num2);
uint32_t roll = 0;

/* check S*/
static bool checkFirstData(uint8_t *data)
{
  bool value = false;

  if(data[0]=='S')
  {
    value = true;
  }
  return value;
}
/* check number*/
static bool checkNumberDe(uint8_t a)
{
  bool value = false;

  if(a >= '0' && a<= '9')
  {
          value = true;
  }

  return value;
}

/* check hexa*/
static bool checkNumberHexa(uint8_t a)
{
  bool value = false;

  if(a >= 'A' && a<= 'F')
  {
          value = true;
  }

  return value;
}
uint8_t CharToHex(uint8_t data)
{
  uint8_t temp = 0;
  
  if(checkNumberDe(data))
  {
     temp = (data - '0');
  }
  else if(checkNumberHexa(data))
  {
    temp = (data - 'A' + 10u);
  }
  
  return temp;
}
uint8_t TwoCharToByte(uint8_t *dataPtr)
{
    uint8_t temp = 0;

    temp  = (CharToHex(*dataPtr)<<4u);
    temp |= (CharToHex(*(dataPtr+1)));

    return temp;
}
/* check form of file*/
static bool checkHexa(uint8_t *data)
{
  bool value = true;
  uint32_t bitSet = 0;
  uint32_t i = 2;

  if(checkFirstData(data) && checkNumberDe(data[1]))
  {
    for(i = 2; i< strlen((char *)data)-1;i++)
    {
      //printf("%c",data[i]);
      if(checkNumberDe(data[i]) )
      {
        bitSet = 1;
      }
      else if(checkNumberHexa(data[i]))
      {
        bitSet = 1;  
      }
      else
      {
        bitSet = 0;
      }
      if(bitSet==0)
      {
        value = false;
        break;
      }
    }
  }
  else
  {
      value = false;
  }

  return value;
}
/* sum of byte count + address + data + checksum */
static uint32_t sumOfAdDa(uint8_t *data)
{
uint32_t sum = 0;
uint32_t i=0;

    for(i=2;i<strlen((char *)data)-1;i+=2)
    {
       sum += convertNumber(data[i],data[i+1]);
    }

    return sum;
}
/* checksum*/
static bool checkSumData(uint8_t *data)
{
  bool value = false;
  uint32_t amountSum = 0;

  amountSum = sumOfAdDa(data);
  if((amountSum&0XFF)== 0XFF)
  {
    value  = true;
  }

  return value;
}
/* check byte count*/
static bool checkByteCount(uint8_t *data)
{
  bool value = false;
  uint32_t numberByte = 0;
  uint32_t count = 0;

  numberByte = convertNumber(data[2],data[3]);
  count = strlen((char*)data)-5;
  if(numberByte == (count/2))
  {
    value = true;
  }

  return value;
}
/* check Srecord */
bool Check_Srecord(uint8_t *data)
{
  bool reValue = true;

  if(!checkByteCount(data))    /* check byte count*/
  {
    reValue =false;
  }
  else if(!checkHexa(data))   /* check number type*/
  { 
    reValue =false;
  }
  else if(!checkSumData(data))   /* check Sum */
  {
    reValue =false;
  }

  return reValue;
}
void Sre_Par(Struc data)
{
  if(Check_Srecord(buff))
//      { 
//        type = buff[1];
//        switch(type)
//        {
//        case '1':
//          count_number_add = 4;
//          status = START_DATA;
//          break;
//        case '2':
//          count_number_add = 6;
//          status = START_DATA;
//          break;
//        case '3':
//          count_number_add = 8;
//          status = START_DATA;
//          break;
//        case '7':
//        case '8':
//        case '9':
//          status = END_OF_LINE;
//        } 
//        if(status == START_DATA)
//        {
//          clearData(addData->data);
//          count_parse = 0;
//          data_lengh = 0;
//          
//          for(i = 4; i<=strlen((char *)buff)-4;i=+2)
//          {
//            if(i < (4 + count_number_add))
//            {
//              addData->address <<= 8u;
//              addData->address |= convertNumber(buff[i],buff[i+1]);
//            }
//            if(i>=(4 + count_number_add))
//            {
//              addData->data[count_parse] = convertNumber(buff[i],buff[i+1]);
//              count_parse++;
//              data_lengh++;
//            }
//          }
}