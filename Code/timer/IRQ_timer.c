#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../screen/screen.h"
#include "../utilities/utilities.h"
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern uint8_t partita;
extern uint8_t vittoria;

void TIMER0_IRQHandler (void)
{
	
  getDisplayPoint(&display, Read_Ads7846(), &matrix );

  if(partita==0 && display.x >=15 && display.x <=225 && display.y>=70 && display.y<=252){ /* Touch to start a new game */
		partita=1;
		inizioPartita();
	}

	if (partita==1){
		if(display.x>=15 && display.x<=87 && display.y>=270 && display.y<=310 && vittoria==0){  /* CLEAR*/
			pulisciLabirinto();
		}
		else if (display.x>=153 && display.x<=225 && display.y>=270 && display.y<=310){ /* RESTART */
			inizializzazione();
		}
	}
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************

******************************************************************************/
void TIMER1_IRQHandler (void)
{
	muovi();
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
