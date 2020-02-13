#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include "MKL46Z4.h"
#include "APP.h"
#include "Flash.h"
#include "UART.h"
#include "QUEUE.h"
#include "SRECORD.h"

static void clearData(uint8_t * data,uint8_t * temp_data);
static volatile rest_handle_app func_reset;
static uint8_t isCheck = 1;

void App(void)
{
  SCB->VTOR = APP_SFE_ADDRESS;  /*Hold vector table offset*/
 // *(volatile int *)APP_HANDLE_ADDRESS;  /*get first stack address*/
  func_reset = (rest_handle_app)*(volatile int *)APP_HANDLE_ADDRESS; /*get adddress of reset handle of app*/
  func_reset();  /*call function reset handle */
}
void Boot(void)
{
  add_data_str *addData; 
  uint8_t *buff;
  uint8_t type = 0;
  uint8_t i = 0;
  uint8_t index = 0;
  uint8_t count_parse = 0;
  uint8_t data_lengh =0;
  uint8_t status = 0;
  uint8_t count_number_add = 0;
  uint8_t data_temp[40];

  UART_init();
  Interrup_UART();
  QueueInit();

  Send_String("Erase Flash \r\n");
  if(Erase_Multi_Sector(APP_SFE_ADDRESS,  SIZE))
  {
    Send_String("Erase done \r\n");
  }
  Send_String("Send your Srecord \r\n");
  while(isCheck)
  {

    if(!Queue_isEmpty())
    {
     PopData(&buff);
      queue_pop();
      //Send_String(buff);
      
      if(Check_Srecord(buff))
      { 
        type = buff[1];
        switch(type)
        {
        case '1':
          count_number_add = 4;
          status = START_DATA;
          break;
        case '2':
          count_number_add = 6;
          status = START_DATA;
          break;
        case '3':
          count_number_add = 8;
          status = START_DATA;
          break;
        case '7':
        case '8':
        case '9':
          status = END_OF_LINE;
        } 
        if(status == START_DATA)
        {
          clearData(addData->data,data_temp);
          count_parse = 0;
          data_lengh = 0;
          
          for(i = 4; i<=strlen((char *)buff)-4;i=+2)
          {
            if(i < (4 + count_number_add))
            {
              addData->address <<= 8u;
              addData->address |= convertNumber(buff[i],buff[i+1]);
              //add_temp[i-4] = buff[i];
            }
            if(i>=(4 + count_number_add))
            {
              addData->data[count_parse] = convertNumber(buff[i],buff[i+1]);
              count_parse++;
              data_lengh++;
            }
          }
//          for(count_temp =0; count_temp < data_lengh; count_temp+=2)
//          {
//            addData.data[count_parse] = TwoCharToByte(&data_temp[count_temp]);
//            count_parse++;
//          }
          for(index = 0; index <data_lengh ;index+=4)
          {
            Program_LongWord_8B(addData->address+index,&addData->data[index]);
          }
          //Send_String(data_temp);
          //Send_String(add_temp);
          //Send_String("\r\n");
        }
      }
      else
      {
        Send_String("Your Srecord Error \r\n");
        //isCheck = 0;
      }
      if(END_OF_LINE == status)
      {
        Send_String("Done");
      }
     }
   }
 }
static void clearData(uint8_t * data,uint8_t * temp_data)
{
  uint8_t i = 0;
  
  for(i=0; i<40; i++)
  {
    data[i] = '\0';
    temp_data[i] = '\0';
  }
}