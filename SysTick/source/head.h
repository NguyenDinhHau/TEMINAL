#ifndef _MKL46Z4_H_
#define _MKL46Z4_H_ 

#define PORT_PCR_MUX_MASK                        (0x700U)
#define PORT_PCR_MUX_SHIFT                       (8U)
#define PORT_PCR_MUX(x)                          (((unsigned int)(((unsigned int)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)

#define GREEN_LED_ON   *(volatile unsigned int *)0x400FF0C8 |= (1 << 5)  /* define led green on port d,5*/
#define GREEN_LED_OFF  *(volatile unsigned int *)0x400FF0C4 |= (1 << 5)  /*define led green off */
#define GREEN_LED_TOG  *(volatile unsigned int *)0x400FF0CC |= (1 << 5)  /*define toggle led green  */

#define SW1  *(volatile const unsigned int *)0x400FF090
#define SW2  *(volatile const unsigned int *)0x400FF090

#define MODE1 0
#define MODE2 1
#define DUTY 500UL

#endif
