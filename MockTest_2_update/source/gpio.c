#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "MKL46Z4.h"
#include "gpio.h"

void LED_Init(void)
{
    /* Enable clock gate for PORTD, PORTE */
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
    /* Enable clock gate for PORTC */
    SIM->SCGC5 |= (1 << 11);

    /* Configure of PTC3 as GPIO*/
    PORTC->PCR[3] |= PORT_PCR_MUX(1);
    PORTC->PCR[3] |= PORT_PCR_PE(1);
    PORTC->PCR[3] |= PORT_PCR_PS(1);
    /* Configure PTC3 as Input */
    GPIOC->PDDR &= ~(1 << 3);
}
