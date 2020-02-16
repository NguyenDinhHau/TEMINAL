#include "MKL46Z4.h"
#include "APP.h"

#define GREEN_LED_ON      GPIOD->PCOR |= (1 << 5)
#define GREEN_LED_OFF     GPIOD->PSOR |= (1 << 5)
#define RED_LED_ON    GPIOE->PCOR |= (1 << 29)
#define RED_LED_OFF   GPIOE->PSOR |= (1 << 29)

void GPIO_Init(void);
void SW_Init(void);

int main(void)
{
    GPIO_Init();
    SW_Init();
  /*  Led_Init();
*/       
    if((GPIOC->PDIR &(1<<3)) == 0)
    {
       Boot();
    }
    else
    {
      App();
    }
}

 void GPIO_Init(void)
{
    /* Enable clock for PORTD, PORTE */
    SIM->SCGC5 |= (1 << 12); 
    SIM->SCGC5 |= (1 << 13);
    
    /* Configure multiplex of PTD5 and PTE29 as GPIO */
    PORTD->PCR[5] |= PORT_PCR_MUX(1);
    PORTE->PCR[29] |= PORT_PCR_MUX(1);
    
    /* Configure PTD5 and PTE29 as output */
    GPIOD->PDDR |= (1 << 5);
    GPIOE->PDDR |= (1 << 29);

    /* Clear PTD5 and PTE29 */
    RED_LED_OFF;
    GREEN_LED_OFF;
}
/******************************************************************************/
void SW_Init(void)
{
  /* Enable clock for PORTC */
  SIM->SCGC5 |= (1 << 11);

  /* Configure of PTC3 as GPIO*/
  PORTC->PCR[3] |= PORT_PCR_MUX(1);
  PORTC->PCR[3] |= PORT_PCR_PE(1);
  PORTC->PCR[3] |= PORT_PCR_PS(1);
  /* set switch is pull up */
  GPIOC->PDDR &= ~(1 << 3);

}