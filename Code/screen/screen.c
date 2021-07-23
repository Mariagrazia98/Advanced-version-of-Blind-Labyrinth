#include "LPC17xx.h"
#include <string.h>
#include "lpc17xx.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../RIT/RIT.h"

extern char mappa[13][15];
extern char percorso [13][15];
extern uint8_t posizione[2];
extern uint8_t direzione;
extern uint8_t move;
extern uint8_t partita;
extern uint8_t vittoria;

void triangoloEst(uint8_t x, uint8_t y, uint16_t colore){
  int i;
	 for(i=0; i<7;++i){
			LCD_DrawLine(y, x+i, y+2*i, x+i, colore);
			LCD_DrawLine(y, x+13-i, y+2*i, x+13-i, colore);
		}	
}
void triangoloOvest(uint8_t x, uint8_t y, uint16_t colore){
	int i;
	for(i=0; i<7;++i){  
			LCD_DrawLine(y+13,x+i, y+13-2*i, x+i, colore);
			LCD_DrawLine(y+13,x+13-i,y+13-2*i, x+13-i,  colore);
		}
}


void triangoloSud(uint8_t x, uint8_t y ,uint16_t colore){
	int i;
		for(i=0; i<7;++i){
			LCD_DrawLine(y+i, x, y+i,x+2*i, colore);
			LCD_DrawLine(y+7+i,x,y+7+i, x+13-2*i, colore);
		}
}

void triangoloNord(uint8_t x, uint8_t y, uint16_t colore){
		int i;
		for(i=0; i<7;++i){
   		LCD_DrawLine(y+i,x+13,y+i, x+13-2*i, colore);
      LCD_DrawLine(y+7+i, x+2*i, y+7+i,x+13, colore);
		}
}

/* disegnaRobot permette di disegnare il robot*/
void disegnaRobot(){
		uint8_t x=posizione[0]*14+70;
		uint8_t y=posizione[1]*14+15;
		uint16_t c; //colore del robot
	  if (move == 1){
    c = Magenta;
		}
		else{
    c = Yellow;
		}
	  switch(direzione){
			case 0: /* OVEST */
					triangoloOvest(x,y,c);
				break;
      case 1: /* SUD */
					triangoloSud(x,y,c);
        break;
			case 2: /* EST */
					 triangoloEst(x,y,c);
				break;
			case 3: /* NORD */
					triangoloNord(x,y,c);
				break;
      default:
        break;
    }
}
/* inizializzazione disegna la schermata iniziale */
void inizializzazione(void){
	int j;
	
	partita=0;
	
	GUI_Text(60, 30, (uint8_t *) "Blind Labyrinth", Magenta, Blue);
	
	for (j=0; j<=182;++j){
		LCD_DrawLine(15, 70+j, 225, 70+j, White);
	}
	GUI_Text(80, 47, (uint8_t *) "          ", Blue, Blue); /* Elimina eventuale scritte della partita precedente */	
	
	for( j = 0; j <= 40; j++){ /* Bottone Clear */
					LCD_DrawLine(15, 270+j , 87, 270+j, Magenta);
	}
			
	for( j = 0; j <= 40; j++){ /* Bottone Reset*/
			LCD_DrawLine(153, 270+j , 225, 270+j, Magenta);
	}
	GUI_Text(31,282,(uint8_t *) "CLEAR", Blue, Magenta);	//31=15+16, 282=270+12
	GUI_Text(161,282,(uint8_t *) "RESTART", Blue, Magenta);
	
	GUI_Text(49+15,74+70,(uint8_t *) "Touch to start", Blue, White); // 49=(225-15-14*14)/2	
	GUI_Text(65+15,74+16+70,(uint8_t *) "a new game", Blue, White);	 // 65=(225-15-10*14)/2
	
}

/* inizioPartita setta le coordinate iniziale del robot e la sua direzione */
void inizioPartita(void){
	uint8_t j;
	uint8_t k;
	uint8_t l;
	
	for( j = 0; j < 32; j++){ /* Elimina la scritta "Touch to start a new game" */
			LCD_DrawLine(15, 74+70+j, 225, 74+70+j, White);
	}
	vittoria=0;
	enable_RIT();
	posizione[0] = 7;
	posizione[1] = 7;
	direzione=2; 
	move=1;
	disegnaRobot(); 
	GUI_Text(80, 47, (uint8_t *) "  Move  ",Blue , Magenta);
	
	for(k=0; k<13; ++k) {
		for(l=0; l<15; ++l){
			percorso[k][l]=0;
		}
	}
	
}

/* coloraCella colora una sola casella, le caselle sono 14px x 14px */
void coloraCella(uint8_t x, uint8_t y, uint16_t colore){
    uint8_t i;
				/* a seconda del colore passato:
			 se è bianco cancello il robot o l'ostacolo,
		   se è rosso disegno l'ostacolo,
			 se è ciano disegno la casella in cui è appena passato il robot,
			 se è verde disegno le caselle di uscita */
    for(i=0; i<14; ++i){
        LCD_DrawLine(y+i, x,y+i, x+13, colore);
    }
}

/* pulisciOstacoli pulisce gli ostacoli */
void pulisciLabirinto(){
	uint16_t colore=White;
	uint8_t i;
	uint8_t j;
	percorso[posizione[0]][posizione[1]] = 0;
	for(i=0; i<13; ++i) {
		for(j=0; j<15; ++j){
			if((mappa[i][j]==1 || percorso[i][j]==1) ) {
				coloraCella(i*14+70, j*14+15, colore); /* rimozione di tutti gli ostacoli e percorso in cui è passato il robot */
				percorso[i][j]=0;
			}
		}
	}
}

/* soluzione mostra gli ostacoli e le 4 uscite */
void soluzione(){
	uint8_t i;
	uint8_t j;
	for(i=0; i<13; ++i) {
		for(j=0; j<15; ++j){
			if(mappa[i][j]==1){
				coloraCella(i*14+70, j*14+15, Red);
			}
			else if (mappa[i][j]==2){
				coloraCella(i*14+70, j*14+15, Green);
			}
		}
	}
	disegnaRobot();
}





