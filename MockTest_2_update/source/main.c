#include "MKL46Z4.h"
#include "app.h"
#include "gpio.h"

void GPIO_Init(void);
void SW_Init(void);

int main(void)
{
    LED_Init();
    SW_Init();
    if((GPIOC->PDIR &(1<<3)) == 0)
    {
       Boot();
    }
    else
    {
      App();
    }
}