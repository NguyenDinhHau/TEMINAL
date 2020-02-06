#include "MKL46Z4.h"
#include "head.h"

unsigned char led1_on  = 1 ;  /*Green on*/
unsigned char led1_off  = 2;  /*Green off*/
unsigned char led2_on  = 2;  /*Red on*/
unsigned char led2_off  = 3;  /*Red off*/

volatile unsigned char time_redLed = 0;
volatile unsigned char time_greenLed = 0;
/*configuring for E29 and D5 */
void Led_Init(void)
{
  /*Open clock gate for PIT, PORTE, PORTD */
  SIM->SCGC5 |= ( SIM_SCGC5_PORTE_MASK );
  SIM->SCGC5 |= ( SIM_SCGC5_PORTD_MASK );
  /* Set GPIO for D5 and E29 */
  PORTE->PCR[29] |= PORT_PCR_MUX(0x01);
  PORTD->PCR[5] |= PORT_PCR_MUX(0x01);
  FPTE->PDDR |= (1<<29);
  FPTD->PDDR |= (1<<5);
  /* turn on green led and red led */
  GREEN_LED_ON;
  RED_LED_ON;
}
/*Configuring for RTC*/
void RTC_Init(void)
{

  SIM->SCGC6   |= SIM_SCGC6_RTC_MASK;    /*Enable clock gate for RTC*/
  SIM->SOPT1  |= SIM_SOPT1_OSC32KSEL(3); /*Chosse LPO clock for RTC */
  RTC->SR &= ~RTC_SR_TCE_MASK;           /*Disable for Timer Counter*/
  RTC->CR |= RTC_CR_OSCE_MASK;           /*Osillator Enable*/
  RTC->TSR = 0x00000005;
  RTC->TPR |= 32768 -1000;               /*Write values for TPR*/
  RTC->SR |= RTC_SR_TCE_MASK;            /*Enable for Timer Counter*/

}
/*Blinking Green Led*/
void Set_GreenLed()
{
  if(time_greenLed == led1_on)
  {
    GREEN_LED_OFF;
  }
  else if(time_greenLed == (led1_off + led1_on))
  {
    GREEN_LED_ON;
    time_greenLed = 0;
  }
}
/*Blinking Red Led*/
void Set_RedLed()
{
  if(time_redLed == led2_on)
  {
    RED_LED_OFF;
  }
  else if(time_redLed == (led2_off + led2_on))
  {
    RED_LED_ON;
    time_redLed = 0;
  }
}
/*reset RTC*/
void ReSet_RTC(void)
{
  if(RTC->TPR ==0)
  {
    time_redLed++;
    time_greenLed++;
    RTC->SR &= ~RTC_SR_TCE_MASK;
    RTC->TPR |= 32768 -1000;
    RTC->SR |= RTC_SR_TCE_MASK;
  }
}

