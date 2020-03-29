#include <msp430.h>
#include "state_machine.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "libTimer.h"

char switch_state_down, switch_state_changed;


static char switch_update_interrupt_sense(){

  char p2val = P2IN;

  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p2val & SWITCHES);   /* if switch up, sense down */
  P1IES &= (p2val | ~SWITCHES);  /* if switch down, sense up */
  return p2val;
}

void state_advance() {
  char p2val = switch_update_interrupt_sense();

  /* Initial State */
  if(p2val & SW1 && p2val & SW2 && p2val & SW3 && p2val & SW4){
    buzzer_set_period(0);
    switch_state_down = 0;
  }
  
  else if(!(p2val & SW1)){
    void toggle();
    switch_state_down = 1;
    
  }
  
  /* If switch 2 is pressed start playing the Star Wars Theme */
  else if(!(p2val & SW2)){
    starWarsTheme();      /* Plays the star wars theme */
    switch_state_down = 1;
  }
  else if(!(p2val & SW3)){
    void binary_counter();
    switch_state_down = 1;
  }
  /* If switch 4 is pressed music stops and dim red led */
  else if(!(p2val & SW4)){
    //Stop music
    buzzer_set_period(0);
    switch_state_down = 0;
  }
  if(switch_state_down){
    switch_state_changed = 1;
    led_update();
}
  else {
    switch_state_changed = 1;
    led_update();
    dim_led();
  }
}

void dim_led(){

  unsigned int j;

  for(j = 1; j < 1200; j++){    // Increasing Intensity
      P1OUT |= LED_RED;         // LED ON
      delay(j);               // Delay for ON Time
      P1OUT &= ~LED_RED;        // LED OFF
      delay(1200-j);           // OFF Time = Period - ON Time
    }

  for(j = 1200; j > 1; j--){    // Decreasing Intensity
      P1OUT |= LED_RED;         // LED ON
      delay(j);               // Delay for ON Time
      P1OUT &= ~LED_RED;        // LED OFF
      delay(1200-j);           // OFF Time = Period - ON Time
    }
  switch_state_changed = 0;
}

void delay(unsigned int t){          // Custom delay function
  unsigned int i;
  for(i = t; i > 0; i--)
    __delay_cycles(1);          // __delay_cycles accepts only constants !
}

void toggle() {
  static char state = 0;
  switch (state) {
  case 0:
    red_on   = 0;
    green_on = 0;
    state    = 1;
    break;
  case 1:
    red_on   = 0;
    green_on = 1;
    state    = 2;
    break;

  case 2:
    red_on   = 1;
    green_on = 0;
    state    = 3;
    break;

  case 3:
    red_on   = 1;
    green_on = 1;
    state    = 0;
    break;
  }
}
void binary_counter(){
  for(;;){
    P1OUT = (BIT0 & BIT6);
    __delay_cycles(1000000);
    P1OUT = BIT6;
    __delay_cycles(1000000);
    P1OUT = BIT0;
    __delay_cycles(1000000);
    P1OUT = (BIT0 ^ BIT6);
    __delay_cycles(1000000);
  }
}
