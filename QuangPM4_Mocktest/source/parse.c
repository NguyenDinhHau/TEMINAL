#include "MKL46Z4.h"
#include "parse.h"
#include "queue.h"
#include "uart0.h"
output_t output;
int g_line = 0;

/********************************************************
* Code
********************************************************/
/* Function to convert Hex to Dec */
int ConvertHetoDe(char srec)
{
    if((srec >= '0') && (srec <= '9'))
    {
        srec = (int)srec - '0'; /* casting to int */
    }
    if((srec >= 'A') && (srec <= 'F'))
    {
        srec = (int)srec - 'A' + 10;
    }
    return srec;
}
/* Function to check character : S, 4, Hex Check */
bool CheckChar(char *srec)
{
    int i = 2;
    int m = 0;
    bool retVal = true;
    m = strlen(srec) - 1;
    for(i = 2; (retVal == true)&&(i < m ); i++)
    {
        if ((( srec[i] >= '0' ) && ( srec[i] <= '9' )) || (( srec[i] >= 'A' ) && ( srec[i] <= 'F' )))
        {
            retVal =  true;
        }
        else
        {
            retVal = false;
        }
    }
    if(((srec[0] != 'S' )|| (srec[1] == '4' )) && retVal == true)
    {
        retVal = false;
    }
    return retVal;
}
/* Function to check byte count */
bool ByteCount(char *srec)
{
    float m = strlen(srec) - 5; /* because except 2 first + 2 last position and \n */
    float numberByte = 0;
    bool retVal = false;
    numberByte = ConvertHetoDe(srec[2])*16 + ConvertHetoDe(srec[3]);
    if(numberByte == m/2) /* because 2 position = 1 byte */
    {
        retVal = true;
    }
    else
    {
        retVal = false;
    }
    return retVal;
}
/* Function to check sum */
bool CheckSum(char *srec)
{
    bool retVal = false;
    float m = strlen(srec) - 1;
    int i = 2;
    int sumCheck = 0;
    for(i = 2; i < m; i += 2)
    {
        sumCheck += ConvertHetoDe(srec[i]) * 16 + ConvertHetoDe(srec[i + 1]);
    }
    if((sumCheck & 0xff ) == 0xff)
    {
        retVal = true;
    } 
    else
    {
        retVal = false;
    }
    return retVal;
}
/* check Srecord */
bool Parse_src(char *srec)
{
    bool retVal = true;
    if(CheckChar(srec))
    {
        if(ByteCount(srec))
        {
            if(CheckSum(srec))
            {
                retVal = true;
            }
        }
    }
    else
    {
        retVal = false;
    }
    return retVal;
}
output_t OutPut(char *srec)
{
    int i = 0;
    int j = 0;
    int m = 0;
    output.add = 0;
    output.length = 0;
    uint8_t temp = 0;
    /* printf data for type '1' */
    if(Parse_src(srec))
    {
        UART_Send_String(">>\r\n");
        if(srec[1] == '1')
        {
            for(i = 0; i < 4; i+= 2)
            {
                output.add <<= 8u;
                temp = ConvertHetoDe(srec[i+4])*16 + ConvertHetoDe(srec[i + 5]);
                output.add |= temp;
            }
        //output.add = '\0';
            for(j = 0; j < strlen(srec) - 11; j += 2 )
            {
                output.data[m] = ConvertHetoDe(srec[j+8]) * 16 + ConvertHetoDe(srec[j + 9]);/* set value for data array */
                m++;
          //output.data[j] = srec[j+8];
                output.length++;
            }
            output.data[m] = '\0';
        }
    /* printf data for type '2' */
        else if(srec[1] == '2')
        {
            for(i = 0; i < 6; i+=2)
            {
                output.add += ConvertHetoDe(srec[i+4]) * 16 + ConvertHetoDe(srec[i + 5]);
            }
            //output.add = '\0';
            for(j = 0; j < strlen(srec) - 13; j+= 2)
            {
                output.data[m] = ConvertHetoDe(srec[j+10]) * 16 + ConvertHetoDe(srec[j + 11]);/* set value for data array */
                m++;
                output.length++;
            }
            output.data[m] = '\0';
        }
    /* printf data for type '3' */
        else if(srec[1] == '3')
        {
            for(i = 0; i < 8; i+=2)
            {
                output.add += ConvertHetoDe(srec[i+4]) * 16 + ConvertHetoDe(srec[i + 5]);
            }
            //output.add = '\0';
            for(j = 0; j < strlen(srec) - 15; j+= 2)
            {
                output.data[m] = ConvertHetoDe(srec[j+12]) * 16 + ConvertHetoDe(srec[j + 13]);/* set value for data array */
                m++;
                output.length++;
            }
            //output.data[m] = '\0';
        }
        else if(srec[1] == '7' | srec[1] == '8' | srec[1] == '9')
        {
            UART_Send_String("Done");
        }
    }
    else
    {
        UART_Send_String("ERROR\r\n");
                //break;
    }
    return output;
}