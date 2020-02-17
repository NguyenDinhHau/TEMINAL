#ifndef _UART_H_
#define _UART_H_

void UART0_Init(void);                     /*Configure for UART0*/
void UART0_EnableInterrupt(void);          /*Enable UART0_INTERRUPT*/
void UART0_SendChar(char data);            /*Send a char from UART*/
void UART0_SendString(char *ptr_str);      /*Send a string from UART*/
uint8_t UART0_GetChar(void);               /*Get Data*/

#endif  /*_UART_H_*/