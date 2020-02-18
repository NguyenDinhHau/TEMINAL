#ifndef _APP_H
#define _APP_H
/*******************************************************************************
 * Defines
 ******************************************************************************/
#define APP_ISP_ADDRESS (0xA000u)
#define APP_HANDLE_ADDRESS     (0xA004u)
#define SIZE ((0x3FFFF-APP_ISP_ADDRESS)/1024)
/*******************************************************************************
 * API
 ******************************************************************************/
typedef void (*ptr_funtion)(void);

void App(void);  /* new app*/
void Boot(void); /* boot app*/

#endif
