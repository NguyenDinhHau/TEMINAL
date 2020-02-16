#ifndef GPIO_H
#define GPIO_H

#define PORT_C            (0x1<<11)
#define SW_1              (0x1<<3)
#define CHECK_BUTTON      *(( volatile unsigned int*)0x400FF090)
#define PORTC_PCR_3       *(( volatile unsigned int*)0x4004B00Cu)
#define GPIOC_PDDR        *(( volatile unsigned int*)0x400FF094u)
#define SET_PE_PS         (0x1<<1 |0x1<<0)
#define SIM_SCGC5         *(( volatile unsigned int*)0x40048038u)

void init_button();
#endif