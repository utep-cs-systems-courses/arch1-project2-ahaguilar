#include <msp430.h>
#include "buzzer.h"
#include "note_interrupt_handler.h"
#include "warsBuzz.h"
#include "buttons.h"
#include <libTimer.h>



int main(){

  switch_init();
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  led_init();
  buzzer_init();
  enableWDTInterrupts();/* enable wd timer */
  or_sr(0x18);/* CPU off, GIE on */

}
