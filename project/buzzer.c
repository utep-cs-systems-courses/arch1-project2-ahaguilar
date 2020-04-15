#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

//Counter to keep track of the notes in the Star Wars Theme song
static int counterStarWarsTheme = 0;

//Counter to keep track of the notes in the Beatles song.
static int counterBeatles = 0;

void buzzer_init(){
  /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
  */

  timerAUpmode();/* used to drive speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;/* enable output to speaker (P2.6) */
}

/*
  starWarsTheme is a method which calls the buzzer_set_period method
  from the buzzer.h file to produce the sound of the frequency specified on
  each case. When the method is called, the song from the Star Wars
  movie is played on the MSP430's speaker.
*/

void starWarsTheme(){

  switch(counterStarWarsTheme){
  case  0:
  case  6:
  case  7:
  case 11:
  case 16:
  case 20:
  case 31:
  case 32: buzzer_set_period(637); if(counterStarWarsTheme==32){ counterStarWarsTheme = 0; } else{   counterStarWarsTheme++;}; break;  // add some note here (1/(frequency #)/2); 
  case  1:
  case  8:
  case 13:
  case 17:
  case 24:
  case 27:
  case 30: buzzer_set_period(477); counterStarWarsTheme++; break;
  case  2:
  case  9:
  case 18:
  case 26: buzzer_set_period(425); counterStarWarsTheme++; break;
  case  3:
  case  5:
  case 10:
  case 12:
  case 19:
  case 22:
  case 25:
  case 29: buzzer_set_period(401); counterStarWarsTheme++; break;
  case  4:
  case 15: buzzer_set_period(358); counterStarWarsTheme++; break;
  case 14:
  case 21:
  case 28: buzzer_set_period(319); counterStarWarsTheme++; break;
  case 23: buzzer_set_period(301); counterStarWarsTheme++; break;
  }
}

/*
  beatlesSong is a method which calls the buzzer_set_period method
  from the buzzer.h file to produce the sound of the frequency specified on
  each case. When the method is called, the song Eleanor Rigby
  is played on the MSP430's speaker.
*/

void beatlesSong(){

  switch(counterBeatles){
  case  0:
  case  2:
  case  9:
  case 12:
  case 14:
  case 22: buzzer_set_period(568); counterBeatles++; break;
  case 1:
  case 4:
  case 10:
  case 13:
  case 16:
  case 32:
  case 41:buzzer_set_period(637); if(counterBeatles==41){ counterBeatles = 0; } else{ counterBeatles++;}; break;  // (1/(frequency #)/2); n4
  case 3:
  case 8:
  case 15:
  case 21:
  case 31:
  case 40: buzzer_set_period(506); counterBeatles++; break;
  case  5:
  case  6:
  case 11:
  case 17:
  case 18:
  case 23: buzzer_set_period(758); counterBeatles++; break;
  case 7:
  case 20:
  case 24:
  case 30:
  case 33:
  case 39: buzzer_set_period(379); counterBeatles++; break;
  case 19:
  case 26:
  case 28:
  case 35:
  case 37: buzzer_set_period(318); counterBeatles++; break;
  case 25:
  case 29:
  case 34:
  case 38: buzzer_set_period(337); counterBeatles++; break;
  case 27:
  case 36: buzzer_set_period(284); counterBeatles++; break;
  }
}


void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1;/* one half cycle */
}
