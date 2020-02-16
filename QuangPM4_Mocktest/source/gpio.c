/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MKL46Z4.h"
#include "gpio.h"
/******************************************************************************
 * code
 ******************************************************************************/

void init_button()
{
    /* Enable clock gate for PORTD, PORTC */
    SIM_SCGC5|= PORT_C;

    /* Configure multiplex of PTE29 and PTC3 as GPIO */
    PORTC_PCR_3 |= PORT_PCR_MUX(1);

    /* Configure input PTC 3 */
    GPIOC_PDDR &= ~SW_1;
    // *(( volatile unsigned long*)0x400FF094u) |= (0x0<<12);

    /* Set PE, PS of SW1 */
    PORTC_PCR_3 |= SET_PE_PS ;
}
