#include "MKL46Z4.h"
#include "head.h"

int main(void)
{
  Led_Init();
  RTC_Init();

  while(1)
  {
    ReSet_RTC();
    Set_GreenLed();
    Set_RedLed();
  }
}


