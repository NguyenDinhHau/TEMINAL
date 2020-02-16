#ifndef _UART_H_
#define _UART_H_

#define SIM_SCGC4               *((volatile unsigned int *)0x40048034u)
#define SIM_SCGC5               *((volatile unsigned int *)0x40048038u)

#define SIM_SOPT2               *((volatile unsigned int *)0x40048004u)
#define MCG_C1                  *((volatile unsigned char *)0x40064000u)
#define MCG_C2                  *((volatile unsigned char *)0x40064001u)

#define MCG_SC                  *((volatile unsigned int *)0x40064008u)

#define UART0_C4                *((volatile unsigned char *)0x4006A00Au)
#define UART0_BDL               *((volatile unsigned char *)0x4006A001u)
#define UART0_BDH               *((volatile unsigned char *)0x4006A000u)
#define UART0_C2                *((volatile unsigned char *)0x4006A003u)
#define UART0_D                 *((volatile unsigned char *)0x4006A007u)
#define UART0_S1                *((volatile unsigned char*)0x4006A004u)

#define PORTA_PCR_1             *((volatile unsigned int *)0x40049004u)
#define PORTA_PCR_2             *((volatile unsigned int *)0x40049008u)
#define PORT_A                  0x1 << 9
#define PORT_C                  1 << 11

#define TE                      (1 << 3)
#define RE                      (1 << 2)

void UART_Init();
void UART_Send_Char(char data);
void UART_Send_String(char *ptr_str);
char UART_GetChar();
void delay(int time);
void UART_Interrup_Init();
#endif
