#ifndef _PARSE_H
#define _PARSE_H

#define GREEN_LED_ON      GPIOD->PCOR |= (1 << 5)
#define GREEN_LED_OFF     GPIOD->PSOR |= (1 << 5)
#define RED_LED_ON        GPIOE->PCOR |= (1 << 29)
#define RED_LED_OFF       GPIOE->PSOR |= (1 << 29)

void LED_Init(void);
void SW_Init(void);

#endif
