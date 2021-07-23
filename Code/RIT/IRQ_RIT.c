#include <stdint.h>
#include "lpc17xx.h"
#include "RIT.h"
#include "../screen/screen.h"
#include "../utilities/utilities.h"
#include "../timer/timer.h"

#include "../GLCD/GLCD.h"


extern uint8_t direzione;
extern uint8_t move;
extern uint8_t posizione[2];


void RIT_IRQHandler (void)
{          
  static int select=0;

	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){        /* Joystick Select pressed */
		select++;
		switch(select){
			case 1:
					if (move == 1){
						move = 0; /* Explore mode */
						GUI_Text(80, 47, (uint8_t *) " Explore ",Blue , Magenta);
					}else{
						move = 1; /* Move mode */
						GUI_Text(80, 47, (uint8_t *) "  Move  ", Blue, Magenta);
					}
				break;
			default:
				break;
		}
	}
	else if ((LPC_GPIO1->FIOPIN & (1<<26)) == 0 && (LPC_GPIO1->FIOPIN & (1<<27))!= 0 && (LPC_GPIO1->FIOPIN & (1<<28)) != 0){ /* Only Joystick Down pressed   */
			select ++;
			direzione = 1;
		}
	else if ((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && (LPC_GPIO1->FIOPIN & (1<<26)) !=0 && (LPC_GPIO1->FIOPIN & (1<<29)) != 0  ){ /* Only Joystick Left pressed   */
			select ++;
			direzione = 0;
		}
	else if ((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && (LPC_GPIO1->FIOPIN & (1<<29)) != 0 && (LPC_GPIO1->FIOPIN & (1<<26)) != 0 ){ /* Only Joystick Right pressed   */
			select ++;
			direzione = 2;
		}
	else if ((LPC_GPIO1->FIOPIN & (1<<29)) == 0 && (LPC_GPIO1->FIOPIN & (1<<27)) != 0 && (LPC_GPIO1->FIOPIN & (1<<28)) != 0){ /*Only Joystick Up pressed   */
			select ++;
			direzione = 3;
		}
	else { /* quando nessun pin è attivo riporto tutto allo stato iniziale */
			select = 0;
			disable_timer(1);
			reset_timer(1);
	}
		
	if (select == 1 ){
		coloraCella(posizione[0]*14+70, posizione[1]*14+15, (uint16_t) White);
		disegnaRobot();
		verificaOstacolo();
		if (move == 1){ 
		enable_timer(1);
		}   
	}
	
	LPC_RIT->RICTRL |= 0x1;  /* clear interrupt flag */
  
  return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
