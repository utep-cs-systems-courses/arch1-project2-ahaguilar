#include <msp430.h>
#include "buzzer.h"
#include "warsBuzz.h"
#include "buttons.h"
#include "note_interrupt_handler.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){/* 100 interrupts/sec it made the notes a little slower */

  static char second_count = 0;
  if (++second_count == 100){
    notes();
    state_advance();
    second_count=0;
  }
}
