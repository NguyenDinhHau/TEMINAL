#include "MKL46Z4.h"
#include "uart0.h"
#include "queue.h"
#include <stdio.h>

static char *readPtr = NULL;
static char g_data = 0;
static volatile uint8_t g_index = 0;

void UART_Init()
{
    /* Enable port A */
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    /* Enable clock gate UART */
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
     /* config PTDA 1, 2 to TX, RX*/
    PORTA->PCR[1] |= PORT_PCR_MUX(2); /* UART0_RX */
    PORTA->PCR[2] |= PORT_PCR_MUX(2); /* UART0_TX */
    
    UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
    /*Select clock 4Mhz */
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(3);
    /* Divide Factor is 1 */
     MCG_SC &= ~ (7 << 1);

    MCG->C1 |= MCG_C1_IRCLKEN(1);
    MCG->C2 |= MCG_C2_IRCS(1);

    /* Select OSR and SBR for baud rate 115200 */
    UART0_C4 = 0;
    UART0_C4 = 4;/* set OSR */
    UART0_BDL = 7;/* set SBR */
    UART0_BDH = 0x00;
    UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK );
}
void UART_Send_Char(char data) /* Funtion to send a character */
{
    while(!(UART0->S1 & UART0_S1_TDRE_MASK));
    {;}
    UART0->D = data;
}
void UART_Send_String(char *ptr_str)/* Funtion to send a string */ // can thêm tham so length, tao loop
{
    while(*ptr_str != 0)
    {
        UART_Send_Char(*ptr_str ++);
    }
}
void delay(int time)
{
    int i = 0;
    for(i = 0; i < time ; i++)
    {

    }
}
char UART_GetChar()
{
    /* Wait until character has been received */
    while (!(UART0->S1 & UART0_S1_RDRF_MASK));
    /* Return the 8-bit data from the receiver */
    return UART0->D;
}
void UART_Interrup_Init()
{
    UART0->C2 &= ~ UART_C2_RIE_MASK;
    UART0->C2 |= UART_C2_RIE_MASK ;
    /* Set priority for UART0 */
    NVIC_SetPriority(UART0_IRQn,2);
    /* Enable interrupt UART0*/
    NVIC_EnableIRQ(UART0_IRQn);
}
void UART0_IRQHandler(void)
{
    /* Push the first queue */
    if (readPtr == NULL)
    {
         //queue_push();
         queue_Pushdata(&readPtr);
    }
    g_data = UART_GetChar(); /* Save data */
    if (0 != g_data)
    {
        if(g_data != 0x0A) /* push until meet \n , next line*/
        {
            readPtr[g_index++] = g_data;
        }
        else
        {
            readPtr[g_index++] = '\0';
            g_index = 0;/* add new queue if meet new line*/
            queue_push();
            queue_Pushdata(&readPtr);
        }
    }
}