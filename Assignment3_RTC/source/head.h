#ifndef _HEAD_
#define _HEAD_

#define GREEN_LED_ON   GPIOD->PCOR |= (1 << 5)  /* define led green on*/
#define GREEN_LED_OFF  GPIOD->PSOR |= (1 << 5)
#define RED_LED_ON     GPIOE->PCOR |= (1 << 29) /* define led red on*/
#define RED_LED_OFF    GPIOE->PSOR |= (1 << 29)

#define PERIOD 10000000U   /*Define period = 10Mhz*/

void Led_Init(void);
void RTC_Init(void);
void Set_GreenLed();
void Set_RedLed();
void ReSet_RTC(void);

#endif /* _HEAD_ */
