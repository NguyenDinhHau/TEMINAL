#define SIM_SCGC5           *((volatile unsigned int *)0x40048038u)
#define RED                 1 << 29
#define GREEN               1 << 5
#define PORT_E              1 << 13
#define PORT_D              1 << 12
#define PORTD_PCR_5          *((volatile unsigned int *)0x4004C014u)
#define PORTE_PCR_29         *((volatile unsigned int *)0x4004D074u)
#define PORT_PCR_MUX(x)     ((( unsigned int)((( unsigned int)(x)) << 8U))& 0x700U)
#define GPIOD_PDDR          *((volatile unsigned int *)0x400FF0D4u)
#define GPIOE_PDDR          *((volatile unsigned int *)0x400FF114u)
#define GPIOD_PSOR          *((volatile unsigned int *)0x400FF0C4u)
#define GPIOD_PCOR          *((volatile unsigned int *)0x400FF0C8u)
#define GPIOD_PTOR          *((volatile unsigned int *)0x400FF0CCu)
#define GPIOE_PSOR          *((volatile unsigned int *)0x400FF104u)
#define GPIOE_PCOR          *((volatile unsigned int *)0x400FF108u)
#define GPIOE_PTOR          *((volatile unsigned int *)0x400FF10Cu)
#define RED_ON              GPIOE_PCOR |= RED
#define RED_OFF             GPIOE_PSOR |= RED
#define RED_TOG             GPIOE_PTOR |= RED
#define GREEN_ON            GPIOD_PCOR |= GREEN
#define GREEN_OFF           GPIOD_PSOR |= GREEN
#define GREEN_TOG           GPIOD_PTOR |= GREEN

void init_led()
{
    /* Enable clock for PORTD, PORTE */
    SIM_SCGC5 |= PORT_D;
    SIM_SCGC5 |= PORT_E;
    /* Config PTD5, PTE29 as GPIO */
    PORTD_PCR_5 |= PORT_PCR_MUX(1);
    PORTE_PCR_29 |= PORT_PCR_MUX(1);
    /* Config PTD5, PTE29 as output */
    GPIOD_PDDR |= GREEN;
    GPIOE_PDDR |= RED;
    RED_ON;
    GREEN_ON;
}
void delay(int time_delay)
{
    unsigned long i;
    
    for (i = 0; i < time_delay; i++)
    {
    }
}
//int PWM(int factor)
//{
//  int status = 0;  
//  while(BUTTON_FLAG == FLAG)
//    {
//      status = 1;
//    }
//       if(status == 1)
//       {
//         factor = factor + 25; /*jum 25% reference 100% is max*/
//         if(factor > 100)
//         {
//          factor = 0;
//         }
//       }
//   return  factor;
//}
int main()
{
    init_led();
    while(1)
    {
     
        /* Delay about ~ 0.5s */
      RED_TOG;
        delay(3000000);
        GREEN_TOG;
        /* Delay about ~ 0.5s */
       
    }
    
}