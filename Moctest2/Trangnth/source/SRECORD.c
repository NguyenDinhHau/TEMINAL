#include<stdio.h>
#include<stdbool.h>
#include<string.h>

static bool checkHexa(char *data);
static int sumOfAdDa(char *data);
static bool checkSumData(char *data);
static bool checkByteCount(char *data);
static int numberDataLine(char *data);
static bool sumDataByteCount(char *data,int a);
static bool checkFirstData(char *data);
static bool checkNumberDe(char a);
static bool checkNumberHexa(char a);
static int convertNumber(char num1, char num2);
int roll = 0;

/* check S*/
static bool checkFirstData(char *data)
{
  bool value = false;

  if(data[0]=='S')
  {
          value = true;
  }
  return value;
}
/* check number*/
static bool checkNumberDe(char a)
{
  bool value = false;

  if(a >= '0' && a<= '9')
  {
          value = true;
  }

  return value;
}
/* check hexa*/
static bool checkNumberHexa(char a)
{
  bool value = false;

  if(a >= 'A' && a<= 'F')
  {
          value = true;
  }

  return value;
}
/* convert from hexa to dec*/
static int convertNumber(char num1, char num2)
{
  int a = 0;

  if(checkNumberDe(num1)&&checkNumberDe(num2))
  {
    a =(num1-'0')*16 + (num2 - '0');
  }
  else if(checkNumberDe(num1)&&checkNumberHexa(num2))
  {
    a = ((num1-'0')*16) + (num2 - 'A')+10;
  }
  else if(checkNumberHexa(num1)&&checkNumberHexa(num2))
  {
    a = ((num1-'A')+10)*16 + (num2 - 'A')+10;
  }
  else if(checkNumberHexa(num1)&&checkNumberDe(num2))
  {
    a = ((num1-'A')+10)*16 + (num2 - '0');
  }

   return a;
}
/* check form of file*/
static bool checkHexa(char *data)
{
  bool value = true;
  int bitSet = 0;
  int i = 2;

  if(checkFirstData(data) && checkNumberDe(data[1]))
  {
    for(i = 2; i< strlen(data)-1;i++)
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
static int sumOfAdDa(char *data)
{
int sum = 0;
int i=0;

    for(i=2;i<strlen(data)-1;i+=2)
    {
       sum += convertNumber(data[i],data[i+1]);
    }

    return sum;
}
/* checksum*/
static bool checkSumData(char *data)
{
  bool value = false;
  int amountSum = 0;

  amountSum = sumOfAdDa(data);
  if((amountSum&0XFF)== 0XFF)
  {
    value  = true;
  }

  return value;
}
/* check byte count*/
static bool checkByteCount(char *data)
{
  bool value = false;
  int numberByte = 0;
  int count = 0;

  numberByte = convertNumber(data[2],data[3]);
  count = strlen(data)-5;
  if(numberByte == (count/2))
  {
    value = true;
  }

  return value;
}
/* return number line */
static int numberDataLine(char *data)
{
  int i = 4;
  int sum = 0;
  int numberHex  = 0;

  for(i=4;i<=strlen(data)-4;i++)
  {
    if(checkNumberDe(data[i]))
    {
      numberHex = data[i] - '0';
    }
    else
    {
      numberHex = data[i] -'A' + 10;
    }
    sum = sum*16 + numberHex;
  }

  return sum;
}
/* sum address of S count*/
static bool sumDataByteCount(char *data,int a)
{
  bool value = false;
  int numberOfDataLine = 0;

  numberOfDataLine = numberDataLine(data);
  if(numberOfDataLine)
  {
    if(numberOfDataLine == a)
    {
      value = true;
    }
  }

  return value;
}
/* check Srecord */
bool Check_Srecord(char *data)
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
  if(data[1]=='1'||data[1]=='2'||data[1]=='3')   /* Check S1, S2, S3 */
  {
    roll++;
  }
 if(data[1]=='5'||data[1]=='6'){   /* check S5, S6 */
    if(sumDataByteCount(data,roll)){
    }
    else{
     reValue =false;
    }
 }

  return reValue;
}