#ifndef _UART_H_
#define _UART_H_

#define MAX_DATA_LINE 100;

#define SIM_SCGC4               *((volatile unsigned int *)0x40048034u)
#define SIM_SCGC5               *((volatile unsigned int *)0x40048038u)

#define PORT_A                  0x1 << 9
//#define UART0                   0x1 << 10
#define SIM_SOPT2               *((volatile unsigned int *)0x40048004u)    

#define MCG_C1                  *((volatile unsigned char *)0x40064000u)
#define MCG_C2                  *((volatile unsigned char *)0x40064001u)


#define MCG_SC                  *((volatile unsigned int *)0x40064008u)

#define UART0_C4                *((volatile unsigned char *)0x4006A00Au)
#define UART0_BDL               *((volatile unsigned char *)0x4006A001u)
#define UART0_BDH               *((volatile unsigned char *)0x4006A000u)

#define UART0_D                 *((volatile unsigned char *)0x4006A007u)
#define UART0_S1                *((volatile unsigned char*)0x4006A004u)
#define PORTA_PCR_1             *((volatile unsigned int *)0x40049004u)
#define PORTA_PCR_2             *((volatile unsigned int *)0x40049008u)
#define UART0_C2                *((volatile unsigned char *)0x4006A003u)


void UART_init();
void Send_char(uint8_t data);
void Send_String(uint8_t *ptr_str);
void delay(uint32_t time);
uint8_t UART0_GetChar();
void Interrup_UART();
void UART0_IRQHandler();

#endif  /*_UART_H_*/