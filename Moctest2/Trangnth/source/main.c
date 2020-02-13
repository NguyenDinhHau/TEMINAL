#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "MKL46Z4.h"
#include "UART.h"
#include "QUEUE.h"
#include "SRECORD.h"

static char * g_data_ptr = NULL;
int main()
{
  UART_init();
  Interrup_UART();
  QueueInit();
    while(1)
    {
      if(!isEmpty())
       {
          g_data_ptr = (char*)PopData();
          
          if ((Check_Srecord(g_data_ptr)) == true)
          {
              Send_String(">> \r\n");
          }
          else
          {
              Send_String("ERROR \r\n");
             // break;
       }
     }
    }
}