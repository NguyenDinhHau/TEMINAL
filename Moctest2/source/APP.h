#ifndef _APP_H
#define _APP_H

#define APP_SFE_ADDRESS (0xA000u)
#define APP_HANDLE_ADDRESS     (0xA004u)
#define GREEN_LED_ON      GPIOD->PCOR |= (1 << 5)
#define GREEN_LED_OFF     GPIOD->PSOR |= (1 << 5)
#define RED_LED_ON    GPIOE->PCOR |= (1 << 29)
#define RED_LED_OFF   GPIOE->PSOR |= (1 << 29)
#define SIZE ((0x3FFFF-APP_SFE_ADDRESS)/1024)
#define END_OF_LINE 2
#define START_DATA 1

typedef void (*rest_handle_app)(void);

typedef struct
{
  uint32_t address;
  uint8_t data[40];
}add_data_str;

void App(void);
void Boot(void);

#endif