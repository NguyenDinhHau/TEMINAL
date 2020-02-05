#include "MKL46Z4.h"
#include "head.h"

unsigned char led1_on  = 1 ;  /*Green on*/
unsigned char led1_off  = 1;  /*Green off*/
unsigned char led2_on  = 2;  /*Red on*/
unsigned char led2_off  = 2;  /*Red off*/

void Led_Init(void);
void RTC_Init(void);
//void PIT_IRQHandler (void);
static void Set_GreenLed();
static void Set_RedLed();

volatile unsigned char time_redLed = 0;
volatile unsigned char time_greenLed = 0;

int main(void)
{
  Led_Init();
  RTC_Init();
  
  while(1)
  {
    if(RTC->TPR ==0)
    {
      time_redLed++;
      time_greenLed++;
      //GREEN_LED_TOG;
      RTC->SR &= ~RTC_SR_TCE_MASK;
      RTC->TPR |= 32768 -1000;
      RTC->SR |= RTC_SR_TCE_MASK;
    }
    Set_GreenLed();
    Set_RedLed();
    
  }
}
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
void RTC_Init(void)
{ 
  
  SIM->SCGC6   |= SIM_SCGC6_RTC_MASK;
  SIM->SOPT1  |= SIM_SOPT1_OSC32KSEL(3);
  RTC->SR &= ~RTC_SR_TCE_MASK;
  RTC->CR |= RTC_CR_OSCE_MASK;
  RTC->TSR = 0x00000005;
  RTC->TPR |= 32768 -1000;
  RTC->SR |= RTC_SR_TCE_MASK;
  
  
  /* configuring for PIT */
//  PIT->CHANNEL[0].TFLG     |= PIT_TFLG_TIF(1); 
//  PIT->MCR      &= !(PIT_MCR_MDIS_MASK);
//  PIT->CHANNEL[0].TCTRL   |= PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;
//  PIT->CHANNEL[0].LDVAL  |= PIT_LDVAL_TSV(PERIOD);
//  /*Enable IRQ for PIT*/
//  NVIC_EnableIRQ(PIT_IRQn);    
}

//void PIT_IRQHandler (void)
//{
//  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF(1);
//  time_redLed++;
//  time_greenLed++;
//  Set_GreenLed();
//  Set_RedLed();
//}
static void Set_GreenLed()
{
  if(time_greenLed == led1_off)
  {
    GREEN_LED_OFF;
  }
  else if(time_greenLed == (led1_off + led1_on))
  {
    GREEN_LED_ON;
    time_greenLed = 0;
  }
}
static void Set_RedLed()
{
  if(time_redLed == led2_off)
  {
    RED_LED_OFF;
  }
  else if(time_redLed == (led2_off + led2_on))
  {
    RED_LED_ON;
    time_redLed = 0;
  }
}
