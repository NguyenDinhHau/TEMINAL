#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include "MKL46Z4.h"
#include "uart.h"
#include "queue.h"

static uint8_t s_data;
static uint8_t *s_arr_buff_ptr;
static uint32_t s_count = 0;

void UART0_Init(void)
{
    /* Enable port A */
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    /* Enable clock gate UART */
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
     /* config PTDA 1, 2 as TX, RX*/
    PORTA->PCR[1] |= PORT_PCR_MUX(2); /* UART0_RX */
    PORTA->PCR[2] |= PORT_PCR_MUX(2); /* UART0_TX */
    
    UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
    /*Select clock 4Mhz */
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(3);
    /* Divide Factor is 1 */
     MCG->SC &= ~ (7 << 1);

    MCG->C1 |= MCG_C1_IRCLKEN(1);
    MCG->C2 |= MCG_C2_IRCS(1);

    /* Select OSR and SBR for baud rate 115200 */
    UART0->C4 = 0;
    UART0->C4 = 4;/* set OSR */
    UART0->BDL = 7;/* set SBR */
    UART0->BDH = 0x00;
    UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK );

}
void UART0_SendChar(char data)
{
    while(!(UART0->S1 & (1 << 7) ))
    {
    }
    UART0->D = data;
}
void UART0_SendString(char *ptr_str)
{
    while(*ptr_str != 0)
    {
        UART0_SendChar(*ptr_str ++);
    }
}

uint8_t UART0_GetChar(void)
{
    /* Wait until character has been received */
    while (!(UART0->S1 &  (1 << 5)));
    /* Return the 8-bit data from the receiver */
    return UART0->D;
}
void UART0_EnableInterrupt(void)
{
    /* Enable interrupt for receiver */
    UART0->C2 &= ~ (1<<5);
    UART0->C2 |= (1<<5) ;
    /* Enable interrupt UART0*/
    NVIC_EnableIRQ(UART0_IRQn);
}

void UART0_IRQHandler(void)
{

    s_data = UART0_GetChar(); /* Save data */
    if(s_arr_buff_ptr == NULL)
    {
        Queue_GetFreeSpaceData(&s_arr_buff_ptr);
    }
    if('\0' != s_data) /* Check ACII character */
    {
        if('\n' != s_data) /* Move to the next queue */
        {
            s_arr_buff_ptr[s_count++] = s_data;
        }
        else
        {
            s_arr_buff_ptr[s_count++] = '\0';
            s_count = 0;
            Queue_Push();
            Queue_GetFreeSpaceData(&s_arr_buff_ptr); /* add new queue */
        }
    }
}