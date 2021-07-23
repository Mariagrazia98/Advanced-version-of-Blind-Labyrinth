/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: Blind Labrytinth game
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Mariagrazia Paladino- PoliTO 
 *----------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "joystick/joystick.h"
#include "screen/screen.h"
#include "RIT/RIT.h"
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
    
		SystemInit();                   /* System Initialization (i.e., PLL)  */
		LCD_Initialization();
    TP_Init();
    TouchPanel_Calibrate();

	
		joystick_init();                /* Joystick Initialization              */
    init_RIT(0x004C4B40);           /* RIT Initialization 50 msec           */    
    init_timer(1,0x017D7840);       /* timer1 per il movimento 1sec*25*10^6 */
    
		LCD_Clear(Blue);
		inizializzazione();							/* si disegna la schermata principale   */

    init_timer(0, 0x4E2 );          /* 50us * 25MHz = 1.25*10^3 = 0x4E2 => polling*/
		enable_timer(0);
	
    LPC_SC->PCON |= 0x1;            /* power-down    mode                    */
    LPC_SC->PCON &= ~(0x2);                        
    
  while (1)    
  {
        __ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
