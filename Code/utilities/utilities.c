#include "LPC17xx.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../timer/timer.h"
#include "../screen/screen.h"
#include "../RIT/RIT.h"

/**********************************************************************************
dati
**********************************************************************************/

unsigned const char mappa [13][15]=   {{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
											 {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
											 {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
											 {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
											 {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
											 {1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
											 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
											 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
											 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
											 {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
											 {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
											 {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
											 {2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}};
unsigned char percorso [13][15];/* tiene traccia delle celle in cui è passato il robot settandole a 1 */
uint8_t posizione[2];  /* posizione del robot	*/
uint8_t move; 				 /* MOVE=1 => MOVE, MOVE=0 => EXPLORE */
uint8_t direzione;	   /* direzione del robot => 3:NORD- 2:EST - 1:SUD - 0:OVEST*/
uint8_t vittoria;			 /* flag che indica il termine del gioco */
uint8_t partita;			 /* flag che indica se la partita è iniziata */
											 
/**********************************************************************************
funzioni
**********************************************************************************/

/* verificaOstacolo verifica la presenza di ostacoli nel raggio di 5 caselle */							 
void verificaOstacolo(void){
	uint8_t j;
  int i = 0;
  uint8_t x = posizione[0];
  uint8_t y = posizione[1];
    
  if (direzione == 3 || direzione == 0){ 
    i = -1;
  } else{ 
    i = 1;
  }
  
  if (direzione == 3 || direzione == 1){ //N-S
		for(j=1; j<=5; ++j){
			if( x+j*i >= 0 && x+j*i < 13 && mappa[x+i*j][y]==1) {
					coloraCella((x+j*i)*14+70, y*14+15, Red);
					break;
			}
		}
  }
  
  if (direzione == 2 || direzione == 0){ //E-O
		for(j=1; j<=5; ++j){
				if( (y+i*j >=0 && y+i*j < 15) && mappa[x][y+i*j]== 1) {
					coloraCella(x*14+70, (y+i*j)*14+15, Red);
					break;
				}
			}
  }	
}

/* muovi permette di far andare avanti il robot */
void muovi(void){
	
	int i;
  uint8_t x = posizione[0];
  uint8_t y = posizione[1];


	if (direzione == 3 || direzione == 0){  //Nord-Ovest 
	i = -1;
	} 
	else{ //S-E 
	i = 1;
	}
	
	if (direzione == 3 || direzione == 1){ //Nord-Sud
		if((x+i >= 0 && x+i < 13) && mappa[x+i][y] != 1) {
				coloraCella(posizione[0]*14+70, posizione[1]*14+15, (uint16_t) Cyan );
				percorso[posizione[0]][posizione[1]]=1;
				posizione[0] = posizione[0] + i;
				disegnaRobot();
			  verificaOstacolo();
		}
	}
	else{ //Est-Ovest
		if((y+i >= 0 && y+i < 15) && mappa[x][y+i] != 1) {
				coloraCella(posizione[0]*14+70, posizione[1]*14+15, (uint16_t) Cyan);
				percorso[posizione[0]][posizione[1]]=1;
				posizione[1] = posizione[1] + i;
				disegnaRobot();
				verificaOstacolo();
		}
	}
	
	if (mappa[posizione[0]][posizione[1]]==2) { /* il robot ha raggiunto una delle caselle di uscita */
		vittoria=1;
		GUI_Text(80, 47, (uint8_t *) " YOU WON! ", Blue, Magenta);	
		disable_RIT(); /* per disabilitare il joystick si disabilita il RIT */
		soluzione();	 /* viene mostrata lo soluzione */
	}
}



