#ifndef _PARSE_H_
#define _PARSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
typedef struct
{
    uint32_t add;
    uint8_t data[255];
    uint16_t length;
    
}output_t;
int ConvertHetoDe(char srec);
bool CheckChar(char *srec);
bool ByteCount(char *srec);
bool CheckSum(char *srec);
bool Parse_src(char *srec);
bool CheckCountLine(char *srec,int sum);
int DataLineNum(char *srec);
output_t OutPut(char *srec);



#endif
