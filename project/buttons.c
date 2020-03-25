#include <msp430.h>
#include "buttons.h"
#include "buzzer.h"
#include "warsBuzz.h"

char state1,state2,state3,state4,play; //States to pick a song using the buttons on the green board
unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;
static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

static char switches(){
  char p=P2IN;
  P2IES |= (p & buttons);                 //swtich up
  P2IES &= (p | ~buttons);                //swithc down
  return p;
}

void switch_init(){
  P2REN |= buttons
  P2IE |= buttons;              //enable interrupts
  P2OUT |= buttons;
  P2DIR &= ~buttons;
  switches();
  led_update();
  switch_handler();              //Read the switches
}

void switch_handler(){
  char p=switches();
  //What song would play depending on the button press.
  state1=(p & S1) ? 0 : 1;
  state2=(p & S2) ? 0 : 1;
  state3=(p & S3) ? 0 : 1;
  state4=(p & S4) ? 0 : 1;

  if(state1 && play==0){
    play=1;
  }
  if(state2 && play==0){
    play=2;                      //Song 2
  }
  if(state3 && play==0){
    play=3;                      //Song 3
  }
  if(state4 && play==0){
    play=4;                      //Song 4
  }
  led_update();
}

void led_init(){
  P1DIR |= LEDS;// bits attached to leds are output
  led_changed = 1;
  led_update();
}

void led_update(){
  if (led_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];
    P1OUT &= (0xff^LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;     // set bit for on leds
    led_changed = 0;
  }
}
