#include "MKL46Z4.h"
#include "uart0.h"
#include "parse.h"
#include "queue.h"
#include "app.h"
#include "flash.h"

static volatile ptr_funtion g_func_reset;

void boot()
{
    uint8_t index = 0;
    char *writePtr; /* pointer to write/pop data */
    UART_Init();/* Init UART */
    UART_Interrup_Init();
    /* Init queue */
    queue_init();
    output_t output1;
    UART_Send_String("Erase Flash \r\n");
    if(Erase_Multi_Sector(APP_ISP_ADDRESS,  SIZE))
    {
        UART_Send_String("Erase done \r\n");
    }
    UART_Send_String("Send your Srecord \r\n");
    while(1)
    {
        if(queue_check_Empty() == false)
        {
             /* use writePtr point to data of the queue */
            queue_POP_Data(&writePtr);
            //UART_Send_String(writePtr);
//            ((Parse_src(writePtr)));
//            {
//                //UART_Send_String(">>\r\n");
//                //delay(120000);
//                //OutPut(writePtr);
//                output1 = OutPut(writePtr);
//                UART_Send_String((output1.data);
////                UART_Send_String("\r\n");
////                for(index = 0; index <output1.length ;index+=4)
////                {
////                    Program_LongWord_8B(output1.add+index, &output1.data[index]);
////                }
//            }
//            if(writePtr[1] == '1')
//            {
                output1 = OutPut(writePtr);
            for(index = 0; index <output1.length ;index+=4)
                {
                  __disable_irq();
                    Program_LongWord_8B(output1.add+index, &output1.data[index]);
                    __enable_irq();
                }
            //}
            
            queue_pop();
        }
    }
}
void app(void)
{
  __disable_irq();
    SCB->VTOR = APP_ISP_ADDRESS;  /*Hold vector table offset*/
   /*(volatile int *)APP_HANDLE_ADDRESS;  get first stack address*/
    g_func_reset = (ptr_funtion)*(volatile int *)APP_HANDLE_ADDRESS; /*get adddress of reset handle of app*/
    g_func_reset();  /*call function reset handle */
}