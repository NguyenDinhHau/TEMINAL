#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "MKL46Z4.h"
#include "app.h"
#include "flash.h"
#include "uart.h"
#include "queue.h"
#include "parse.h"

//static void clearData(uint8_t * data);
static volatile ptr_funtion g_func_reset;
static uint8_t g_isCheck = 1;

void App(void)
{
    SCB->VTOR = APP_ISP_ADDRESS;  /*Hold vector table offset*/
    __set_MSP(*(volatile uint32_t *)APP_ISP_ADDRESS);
    g_func_reset = (ptr_funtion)*(volatile int *)APP_HANDLE_ADDRESS; /*get adddress of reset handle of app*/
    g_func_reset();  /*call function reset handle */
} 
void Boot(void)
{
    addData_str_t *addData; 
    uint8_t *buff;
    uint8_t index = 0;
    srec_parser_status_enum_t status;

    UART0_Init();
    UART0_EnableInterrupt();
    Queue_Init();
    addData = (addData_str_t *)malloc(sizeof(addData_str_t));

    UART0_SendString("Erase Flash \r\n");
    if(Erase_Multi_Sector(APP_ISP_ADDRESS, SIZE))
    {
         UART0_SendString("Erase done \r\n");
    }
    UART0_SendString("Send your Srecord \r\n");
    while(g_isCheck)
    {
        if(!Queue_IsEmpty())
        {
        Queue_PopData(&buff);
        status = Srec_Parse(&buff[0],&addData[0]);
            if(START_DATA  == status)
            {
                for(index = 0; index < addData->dataLengh; index = index+4)
                {
                    __disable_irq();
                    Program_LongWord_8B(addData->add + index,&addData->data[index]);
                    __enable_irq();
                }
            }
            else
            {
                if(END_DATA == status)
                {
                    UART0_SendString("Done! Press reset button to run app \r\n");
                    g_isCheck = 0;
                }
                if(ERROR_UNKNOWN == status)
                {
                    UART0_SendString("ERROR FIRST CHARACTER! hold your Button and Press reset button to Boot Again \r\n");
                    g_isCheck = 0;
                }
                if(ERROR_CHECKSUM == status)
                {
                    UART0_SendString("ERROR CHECKSUM! hold your Button and Press reset button to Boot Again \r\n");
                    g_isCheck = 0;
                }
            }
        Queue_Pop();
        }
    }
}