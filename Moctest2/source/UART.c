#include<stdlib.h>
#include "MKL46Z4.h"
#include "UART.h"
#include "QUEUE.h"

static uint8_t g_buff;
static uint8_t *g_arr_buff;
static uint32_t g_count = 0;

void UART_init()
{
    /* Enable port A */
    SIM_SCGC5 |= PORT_A;
    /* Enable clock UART */
    SIM_SCGC4 |= (1 <<10);
    /*Open pin A1 and A2 for */
    PORTA_PCR_1 |= PORT_PCR_MUX(2);
    PORTA_PCR_2 |= PORT_PCR_MUX(2);
    UART0_C2  &= ~ ((1 << 3) | (1 <<2));

    /*Enble clock 4Mhz */
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(3);
     MCG_SC &= ~ (7 << 1);
    /* Enable internal reference clock */
    MCG_C1 |= MCG_C1_IRCLKEN(1);
    /* Select internal reference clock */
    MCG_C2 |= MCG_C2_IRCS(1);
    /* Divider Fast Clock */
    UART0_C4 = 0;
    UART0_C4 = 4;
    UART0_BDL = 7;
    UART0_BDH = 0x00;
    UART0_C2  |= (1 << 3) ;
    UART0_C2  |= (1 << 2);

}
void Send_char(uint8_t data)
{
    while(!(UART0_S1 & (1 << 7) ))
    {
    }
    UART0_D = data;
}
void Send_String(uint8_t *ptr_str)
{
    while(*ptr_str != 0)
    {
        Send_char(*ptr_str ++);
    }
}
void delay(uint32_t time)
{
    uint32_t i = 0;
    for(i = 0; i < time ; i++)
    {
    }
}
uint8_t UART0_GetChar()
{
    /* Wait until character has been received */
    while (!(UART0_S1 &  (1 << 5)));
    /* Return the 8-bit data from the receiver */
    return UART0_D;
}
void Interrup_UART()
{
    /* Enable interrupt for receiver */
    UART0_C2 &= ~ (1<<5);
    UART0_C2 |= (1<<5) ;
    /* Set priority for UART0 */
    NVIC_SetPriority(UART0_IRQn,2);
    /* Enable interrupt UART0*/
    NVIC_EnableIRQ(UART0_IRQn);
}

void UART0_IRQHandler()
{

    g_buff = UART0_GetChar(); /* Save data */
    if (g_arr_buff == NULL)
     {
        Pushdata(&g_arr_buff); /*allocatte memory for arr_buff*/
     }
    if (0 != g_buff) /* Check ACII character */
    {
      if('\n' != g_buff) /* Move to the next queue */
      {
          g_arr_buff[g_count++] = g_buff;
      }
      else
      {
        g_arr_buff[g_count++] = '\0';
          g_count = 0;
          queue_push();
          Pushdata(&g_arr_buff); /* add new queue */
      }
    }
}