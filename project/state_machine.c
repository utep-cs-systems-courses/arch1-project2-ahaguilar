#include <msp430.h>
#include "state_machine.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "libTimer.h"

char switch_state_down, switch_state_changed;
char switch0, switch1, switch2, switch3, switch4;

extern void toggle();
static char switch_update_interrupt_sense(){

  char p2val = P2IN;

  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p2val & SWITCHES);   /* if switch up, sense down */
  P1IES &= (p2val | ~SWITCHES);  /* if switch down, sense up */
  return p2val;
}

static char switch_option() {
  char p2val = switch_update_interrupt_sense();
  char switchState = 0;
  
  /* Initial State */
  if(p2val & SW1 && p2val & SW2 && p2val & SW3 && p2val & SW4){
    switchState = 0;
    return 0;
  }
  
  else if (!(p2val & SW1)){
    switchState = 1;
    return 1;
  }
  
  else if (!(p2val & SW2)){
    switchState = 2;
    return 2;
  }
  
  else if (!(p2val & SW3)){
    switchState = 3;
    return 3;
  }
  
  else if (!(p2val & SW4)){
    switchState = 4;
    return 4;
  }
  
  else return 0;
}

void state_advance() {
  char switchState = switch_option();
  switch (switchState) {
    // Initial State
  case 0:
    buzzer_set_period(0);
    switch_state_down = 0;
    break;
    
    // If switch 1 is pressed start playing La Bamba
  case 1:
    toggle();
    switch_state_down = 1;
    break;
    // Plays star wars song
  case 2:
    starWarsTheme();
    toggle();
    // reset_state();
    switch_state_down = 1;
    break;

  case 3:
    beatlesSong();
    reset_state();
    // dim_led_Green();
    switch_state_down = 1;
    break;
    
  case 4:
    //Stop music
    buzzer_set_period(0);
    reset_state();
    switch_state_down = 0;
    break;
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

void dim_led_Green(){

  unsigned int j;

  for(j = 1; j < 1200; j++){    // Increasing Intensity
      P1OUT |= LED_GREEN;         // LED ON
      delay(j);                 // Delay for ON Time
      P1OUT &= ~LED_GREEN;        // LED OFF
      delay(1200-j);           // OFF Time = Period - ON Time
    }
  
  for(j = 1200; j > 1; j--){    // Decreasing Intensity
      P1OUT |= LED_GREEN;         // LED ON
      delay(j);               // Delay for ON Time
      P1OUT &= ~LED_GREEN;        // LED OFF
      delay(1200-j);           // OFF Time = Period - ON Time
    }
  switch_state_changed = 0;
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
    __delay_cycles(1);          // __delay_cycles accepts only constants
}

/*void toggle() {
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
*/

void reset_state() {
  red_on = 0;
  green_on = 0;
  led_update();
}
