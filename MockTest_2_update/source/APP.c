/*******************************************************************************
 * Includes
 ******************************************************************************/
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
/*******************************************************************************
 * Codes
 ******************************************************************************/
static volatile ptr_funtion g_func_reset;
static uint8_t g_isCheck = 1;

/*This function to run your new app*/
void App(void)
{
    /*Hold vector table offset*/
    SCB->VTOR = APP_ISP_ADDRESS;
    __set_MSP(*(volatile uint32_t *)APP_ISP_ADDRESS);
    /*get adddress of reset handle of app*/
    g_func_reset = (ptr_funtion)*(volatile int *)APP_HANDLE_ADDRESS; 
    /*call function reset handle */
    g_func_reset();  
} 
/*This function to boot your new app*/
void Boot(void)
{
    addData_str_t *outputData_ptr; 
    uint8_t *buff_ptr;
    srec_parser_status_enum_t status;
    uint8_t index = 0;
    /* Configure UART0, Queue and Enable UART INTERRUPT */
    UART0_Init();
    UART0_EnableInterrupt();
    Queue_Init();
    /* allocate memory for outputdata*/
    outputData_ptr = (addData_str_t *)malloc(sizeof(addData_str_t));  
    /* Erase Flash */
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
        Queue_PopData(&buff_ptr);
        /* Parse address and data from buff_ptr to outputData_ptr, it will return a status*/
        status = Srec_Parse(&buff_ptr[0],&outputData_ptr[0]);
            if(START_DATA  == status)
            {    /* write data to flash */
                for(index = 0; index < outputData_ptr->dataLengh; index = index+4)
                {
                    __disable_irq();  /* disable all of interrupt to protect your flash*/
                    Program_LongWord_8B(outputData_ptr->add + index,&outputData_ptr->data[index]);
                    __enable_irq();   /* enable all of interrupt */
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
    free(outputData_ptr);   /* free memory for outputData_ptr*/
}
