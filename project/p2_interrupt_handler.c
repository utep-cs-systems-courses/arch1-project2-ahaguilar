#include <msp430.h>
#include "switches.h"
#include "buzzer.h"
#include "state_machine.h"

/* Switch on P2 (S1) */

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {           
    P2IFG &= ~SWITCHES;            /* clear pending sw interrupts */
    state_advance();               /* single handler for all switches */
  }
}
