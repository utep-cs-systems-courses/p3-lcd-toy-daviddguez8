#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "game_state_machine.h"

// function that handles interrupts
// from the periodic timer
// The timer fires an event 250 times/sec
void
wdtInterruptHandler()
{
  const u_int state1_limit = 250;
  const u_int state2_limit = 15;
  const u_int state3_limit = 15;
  static u_int main_count = 0;
  
  switch(state) {
  case 1:
    if(main_count >= state1_limit) {
      work_to_be_done = 1;
      main_count = 0;
    }
    break;
  case 2: //player shot
    if(main_count >= state2_limit) {
      work_to_be_done = 1;
      main_count = 0;
    }
    break;
  case 3:
    if(main_count >= state3_limit) {
      work_to_be_done = 1;
      main_count = 0;
    }
    break;
  }
  
  main_count++;
} 

