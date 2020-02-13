#include"head.h"
/*this is intital register */
void initLed();
void delay(unsigned int time);   /*this is delay function*/

int main()
{
  initLed();
}

void initLed()
{
  /*Enable clock for PORTD, PORTC*/
  *(volatile unsigned int*)0x40048038 |=(1<<11);   /*port c*/
  *((volatile unsigned int*)0x40048038) |=(1<<12);   /* port d*/
  /*configure PTD29 as output and PTC3, PTC12 are input */
  *(volatile unsigned int*)0x400FF094 =(0<<3); /*port c3*/
  *(volatile unsigned int*)0x400FF094 =(0<<12); /*port c12*/
  *(volatile unsigned int*)0x400FF0D4 |=(1<<5); /*port d5*/
  /* Enable GPIO for D5, C12, C3 */
  *(volatile unsigned int*)0x4004C014 = PORT_PCR_MUX(1);  /* D5  led*/
  *(volatile unsigned int*)0x4004B030 = PORT_PCR_MUX(1);  /* C12 sw2*/
  *(volatile unsigned int*)0x4004B00C = PORT_PCR_MUX(1);  /* C3 sw1*/
  /*PULL Enable and PULL Select C12*/
  *(volatile unsigned int*)0x4004B030 |= (1<<1); 
  *(volatile unsigned int*)0x4004B030 |= (1<<0);
  /*PULL Enable and PULL Select C3*/
  *(volatile unsigned int*)0x4004B00C |=(1<<1);
  *(volatile unsigned int*)0x4004B00C |=(1<<0);
  
  GREEN_LED_OFF;
  
}
/*this is delay function*/
void delay(unsigned int time)
{
  unsigned int i = 0;
  
  for(i=0; i<time;i++)
  {
    /*nothing to do*/
  }
}
