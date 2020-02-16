#ifndef __APP_H__
#define __APP_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_ISP_ADDRESS (0xA000u)
#define APP_HANDLE_ADDRESS     (0xA004u)
#define SIZE ((0x3FFFF-APP_ISP_ADDRESS)/1024)

typedef void (*ptr_funtion)(void);
void boot();
void app();
void __disable_interrupt(void);
#endif
